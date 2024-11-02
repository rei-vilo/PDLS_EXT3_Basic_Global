//
// hV_HAL_Peripherals.cpp
// C++ code
// ----------------------------------
//
// Project highView Library Suite
//
// Created by Rei Vilo, 08 Jan 2024
//
// Copyright (c) Rei Vilo, 2010-2024
// Licence All rights reserved
//
// * Basic edition: for hobbyists and for basic usage
// Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
//
// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
// All rights reserved
//
// * Commercial edition: for professionals or organisations, commercial usage
// All rights reserved
//
// Release 800: Added 3-wire SPI
// Release 801: Added SPI configuration
// Release 803: Improved stability
// Release 804: Improved power management
// Release 805: Improved stability
//

// Library header
#include "hV_HAL_Peripherals.h"

//
// === General section
//
#if defined(ENERGIA)
///
/// @brief Proxy for SPISettings
/// @details Not implemented in Energia
/// @see https://www.arduino.cc/en/Reference/SPISettings
///
struct _SPISettings_s
{
    uint32_t clock; ///< in Hz, checked against SPI_CLOCK_MAX = 16000000
    uint8_t bitOrder; ///< LSBFIRST, MSBFIRST
    uint8_t dataMode; ///< SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
};
///
/// @brief SPI settings for screen
///
_SPISettings_s _settingScreen;
#else
///
/// @brief SPI settings for screen
///
SPISettings _settingScreen;
#endif // ENERGIA

#ifndef SPI_CLOCK_MAX
#define SPI_CLOCK_MAX 16000000
#endif

struct h_pinSPI3_t
{
    uint8_t pinClock;
    uint8_t pinData;
};

h_pinSPI3_t h_pinSPI3;

void hV_HAL_begin()
{
    // Empty
}
//
// === End of General section
//

//
// === GPIO section
//
void waitFor(uint8_t pin, uint8_t state)
{
    while (digitalRead(pin) != state)
    {
        delay(32); // non-blocking
    }
}
//
// === End of GPIO section
//

//
// === Time section
//

//
// === End of Time section
//

//
// === SPI section
//
bool flagSPI = false; // Some SPI implementations require unique initialisation

void hV_HAL_SPI_begin(uint32_t speed)
{
    if (flagSPI != true)
    {
        _settingScreen = {speed, MSBFIRST, SPI_MODE0};

#if defined(ENERGIA)

        SPI.begin();
        SPI.setBitOrder(_settingScreen.bitOrder);
        SPI.setDataMode(_settingScreen.dataMode);
        SPI.setClockDivider(SPI_CLOCK_MAX / min(SPI_CLOCK_MAX, _settingScreen.clock));

#else

#if defined(ARDUINO_XIAO_ESP32C3)

        // Board Xiao ESP32-C3 crashes if pins are specified.
        SPI.begin(8, 9, 10); // SCK MISO MOSI

#elif defined(ARDUINO_ESP32_PICO)

        // Board ESP32-Pico-DevKitM-2 crashes if pins are not specified.
        SPI.begin(14, 12, 13); // SCK MISO MOSI

#else // General case

        SPI.begin();

#endif // SPI specifics

        SPI.beginTransaction(_settingScreen);

#endif // ENERGIA

        flagSPI = true;
    }
}

void hV_HAL_SPI_end()
{
    if (flagSPI != false)
    {
        SPI.end();
        flagSPI = false;
    }
}

uint8_t hV_HAL_SPI_transfer(uint8_t data)
{
    return SPI.transfer(data);
}

//
// === End of SPI section
//

//
// === Wire section
//
bool flagWire = false; // Some Wire implementations require unique initialisation

void hV_HAL_Wire_begin()
{
    if (flagWire == false)
    {
        Wire.begin();

#if defined(ENERGIA)

#if defined(ENERGIA_ARCH_MSP430ELF)

        Wire.setClock(100000UL); // 100 kHz for MSP430

#endif // ENERGIA_ARCH_MSP430ELF

#else // ARDUINO

        Wire.setClock(400000L); // 400 kHz

#endif // ENERGIA ARDUINO
        flagWire = true;
    }
}

void hV_HAL_Wire_end()
{
    if (flagWire == true)
    {
        Wire.end();
        flagWire = true;
    }
}

void hV_HAL_Wire_transfer(uint8_t address, uint8_t * dataWrite, size_t sizeWrite, uint8_t * dataRead, size_t sizeRead)
{
    if (sizeWrite > 0)
    {
        Wire.beginTransmission(address);

        for (uint8_t index = 0; index < sizeWrite; index++)
        {
            Wire.write(dataWrite[index]);
        }

        Wire.endTransmission();

#if defined(ENERGIA)

        // Energia-MT I2C thread may hang
        delay(4);

#endif // ENERGIA
    }

    if (sizeRead > 0)
    {
        memset(dataRead, 0x00, sizeRead);
        Wire.requestFrom(address, sizeRead);
        while (Wire.available() < sizeRead)
        {
            delay(4);
        }

        for (uint8_t index = 0; index < sizeRead; index++)
        {
            dataRead[index] = Wire.read();
        }
    }
}
//
// === End of Wire section
//

//
// === 3-wire SPI section
//
void hV_HAL_SPI3_begin()
{
#if defined(ARDUINO_XIAO_ESP32C3)

    // Board Xiao ESP32-C3 crashes if pins are not specified.
    hV_HAL_SPI3_define(8, 9); // SCK SDA

#elif defined(ARDUINO_ESP32_PICO)

    // void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
    // Board ESP32-Pico-DevKitM-2 crashes if pins are not specified.
    hV_HAL_SPI3_define(14, 12); // SCK SDA

#else // General case

    hV_HAL_SPI3_define(SCK, MOSI); // SCK SDA

#endif // ARDUINO
}

void hV_HAL_SPI3_define(uint8_t pinClock, uint8_t pinData)
{
    h_pinSPI3.pinClock = pinClock;
    h_pinSPI3.pinData = pinData;
}

uint8_t hV_HAL_SPI3_read()
{
    uint8_t value = 0;

    pinMode(h_pinSPI3.pinClock, OUTPUT);
    pinMode(h_pinSPI3.pinData, INPUT);

    for (uint8_t i = 0; i < 8; ++i)
    {
        digitalWrite(h_pinSPI3.pinClock, HIGH);
        delayMicroseconds(1);
        value |= digitalRead(h_pinSPI3.pinData) << (7 - i);
        digitalWrite(h_pinSPI3.pinClock, LOW);
        delayMicroseconds(1);
    }

    return value;
}

void hV_HAL_SPI3_write(uint8_t value)
{
    pinMode(h_pinSPI3.pinClock, OUTPUT);
    pinMode(h_pinSPI3.pinData, OUTPUT);

    for (uint8_t i = 0; i < 8; i++)
    {
        digitalWrite(h_pinSPI3.pinData, !!(value & (1 << (7 - i))));
        delayMicroseconds(1);
        digitalWrite(h_pinSPI3.pinClock, HIGH);
        delayMicroseconds(1);
        digitalWrite(h_pinSPI3.pinClock, LOW);
        delayMicroseconds(1);
    }
}
//
// === End of 3-wire SPI section
//

