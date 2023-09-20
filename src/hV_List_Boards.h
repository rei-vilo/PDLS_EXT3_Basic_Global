///
/// @file hV_List_Boards.h
/// @brief List of boards for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Sep 2023
/// @version 700
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright All rights reserved
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
///
/// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///

// SDK
#include "stdint.h"

#ifndef hV_LIST_BOARDS_RELEASE
///
/// @brief Release
///
#define hV_LIST_BOARDS_RELEASE 700

///
/// @brief Not connected pin
///
#define NOT_CONNECTED (uint8_t)0xff

///
/// @brief Board configuration structure
///
struct pins_t
{
    // ///< EXT3 and EXT3-1 pin 1 Black -> +3.3V
    // ///< EXT3 and EXT3-1 pin 2 Brown -> SPI SCK
    uint8_t panelBusy; ///< EXT3 and EXT3-1 pin 3 Red
    uint8_t panelDC; ///< EXT3 and EXT3-1 pin 4 Orange
    uint8_t panelReset; ///< EXT3 and EXT3-1 pin 5 Yellow
    // ///< EXT3 and EXT3-1 pin 6 Green -> SPI MISO
    // ///< EXT3 and EXT3-1 pin 7 Blue -> SPI MOSI
    uint8_t flashCS; ///< EXT3 and EXT3-1 pin 8 Violet
    uint8_t panelCS; ///< EXT3 and EXT3-1 pin 9 Grey
    // ///< EXT3 and EXT3-1 pin 10 White -> GROUND
    uint8_t panelCSS; ///< EXT3 and EXT3-1 pin 12 Grey2
    uint8_t flashCSS; ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    // ///< EXT3-Touch pin 1 Brown -> I2C SDA
    // ///< EXT3-Touch pin 2 Black -> I2C SCL
    uint8_t touchInt; ///< EXT3-Touch pin 3 Red
    uint8_t touchReset; ///< EXT3-Touch pin 4 Orange
    uint8_t panelPower; ///< Optional power circuit
    uint8_t cardCS; ///< Separate SD-card board
    uint8_t cardDetect; ///< Separate SD-card board
};

///
/// @name Recommended boards
/// @{

///
/// @brief Raspberry Pi Pico and Pico W
/// @note Numbers refer to GPIOs, not pins
/// @see https://github.com/earlephilhower/arduino-pico
/// @note Recommended board
///
const pins_t boardRaspberryPiPico_RP2040 =
{
    ///< EXT3 and EXT3-1 pin 1 Black -> +3.3V
    ///< EXT3 and EXT3-1 pin 2 Brown -> SPI SCK GP18
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> GP11
    ///< EXT3 and EXT3-1 pin 6 Green -> SPI MISO GP16
    ///< EXT3 and EXT3-1 pin 7 Blue -> SPI MOSI GP19
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> GP10
    .panelCS = 17, ///< EXT3 and EXT3-1 pin 9 Grey -> GP17
    .panelCSS = 14, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GP14
    .flashCSS = 15, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GP15
    ///< EXT3 and EXT3-1 pin 10 White -> GROUND
    ///< EXT3-Touch pin 1 Brown -> I2C SDA GP5
    ///< EXT3-Touch pin 2 Black -> I2C SCL GP4
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GP2
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GP3
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Adafruit Feather nRF52840 configuration, tested
/// @note Recommended board
///
const pins_t boardFeatherNRF52840 =
{
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> D13 GPIO13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> D12 GPIO12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> D11 GPIO11
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> D10 GPIO10
    .panelCS = 9, ///< EXT3 and EXT3-1 pin 9 Grey -> D9 GPIO9
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D5 GPIO5
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D6 GPIO6
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Espressif ESP32-DevKitC
/// @note Numbers refer to GPIOs not pins
/// @note Recommended board
/// @warning Specific SPI port with SCK=14 MISO=12 MOSI=13
///
const pins_t boardESP32DevKitC =
{
    ///< EXT3 and EXT3-1 pin 1 Black -> +3.3V
    ///< EXT3 and EXT3-1 pin 2 Brown -> SPI SCK GPIO14
    .panelBusy = 27, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO27
    .panelDC = 26, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO26
    .panelReset = 25, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO25
    ///< EXT3 and EXT3-1 pin 6 Green -> SPI MISO GPIO12
    ///< EXT3 and EXT3-1 pin 7 Blue -> SPI MOSI GPIO13
    .flashCS = 33, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO33
    .panelCS = 32, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO32
    .panelCSS = 4, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO4
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO0
    ///< EXT3 and EXT3-1 pin 10 White -> GROUND
    ///< EXT3-Touch pin 1 Brown -> I2C SDA GPIO21
    ///< EXT3-Touch pin 2 Black -> I2C SCL GPIO22
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GPIO10
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GPIO9
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

/// @}

///
/// @name Other boards
/// @{
    
///
/// @brief Texas Instruments LaunchPad MSP430 and MSP432 LaunchPad configuration, tested
///
const pins_t boardLaunchPad =
{
    .panelBusy = 11, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 13, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 18, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 19, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 39, ///< EXT3 and EXT3-1 pin 12 Grey2 -> 39
    .flashCSS = 38, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> 38
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> 8
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> 6
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board -> 5
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Texas Instruments LaunchPad MSP430FR5994 LaunchPad with SD-card configuration, tested
///
const pins_t boardMSP430FR5994 =
{
    .panelBusy = 11, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 13, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 18, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 19, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 39, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = 38, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = 47, ///< Included SD-card
    .cardDetect = 51 ///< Included SD-card
};

///
/// @brief Texas Instruments LaunchPad CC1352 configuration, tested
///
const pins_t boardCC1352 =
{
    .panelBusy = 5, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 6, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 19, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 24, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 26, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 37, ///< EXT3 and EXT3-1 pin 12 Grey2 -> 37
    .flashCSS = 27, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> 27
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Raspberry Pi Zero, 2B, 3B, 4B configuration with RasPiArduino, tested
/// @warning Not recommended
/// @see https://github.com/me-no-dev/RasPiArduino
///
const pins_t boardRaspberryPiZeroB_RasPiArduino =
{
    .panelBusy = 7, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO7 pin 26
    .panelDC = 8, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO8 pin 24
    .panelReset = 25, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO25 pin 22
    .flashCS = 22, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO22 pin 15
    .panelCS = 27, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO27 pin 13
    .panelCSS = 23, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO23 pin 16
    .flashCSS = 24, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO24 pin 18
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Raspberry Pi Pico Arduino mbed configuration, tested
/// @warning Not recommended
/// @see https://github.com/arduino/ArduinoCore-mbed
///
const pins_t boardRaspberryPiPico_Arduino =
{
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> GP11
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> GP10
    .panelCS = 5, ///< EXT3 and EXT3-1 pin 9 Grey -> GP5
    .panelCSS = 14, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GP14
    .flashCSS = 15, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GP15
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GP9
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GP8
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Adafruit Feather M0 and M4 configuration, tested
///
const pins_t boardFeatherM0M4 =
{
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> D13 GPIO13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> D12 GPIO12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> D11 GPIO11
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> D10 GPIO10
    .panelCS = 9, ///< EXT3 and EXT3-1 pin 9 Grey -> D9 GPIO9
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D5 GPIO5
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D6 GPIO6
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Adafruit Feather nRF52832 configuration, tested
///
const pins_t boardFeatherNRF52832 =
{
    .panelBusy = 16, ///< EXT3 and EXT3-1 pin 3 Red -> D13 GPIO16
    .panelDC = 15, ///< EXT3 and EXT3-1 pin 4 Orange -> D12 GPIO15
    .panelReset = 7, ///< EXT3 and EXT3-1 pin 5 Yellow -> D11 GPIO7
    .flashCS = 11, ///< EXT3 and EXT3-1 pin 8 Violet -> D10 GPI011
    .panelCS = 31, ///< EXT3 and EXT3-1 pin 9 Grey -> D9 GPIO31
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D5 GPIO27
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D6 GPIO30
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Arduino Zero configuration, tested
/// @note In case of use of SERCOM
/// @code {.cpp}
/// #define SPI_CLOCK_PIN 13 ///< EXT3 and EXT3-1 pin 2 -> 13
/// #define SPI_CLOCK_MISO 11 ///< EXT3 and EXT3-1 pin 6 -> 11
/// #define SPI_CLOCK_MOSI 12 ///< EXT3 and EXT3-1 pin 7 -> 12
/// @endcode
///
const pins_t boardArduinoZero =
{
    .panelBusy = 4, ///< EXT3 and EXT3-1 pin 3 Red
    // On Arduino Zero, pins D4 and D2 are reversed
    .panelDC = 5, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 6, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 7, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 8, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 9, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = 10, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief ST Nucleo 64, tested
///
const pins_t boardNucleo64 = boardArduinoZero;

///
/// @brief Particle Photon configuration, tested
/// @note D6 also CLK/SWCLK with D7 SWD/SWDIO
///
const pins_t boardParticlePhoton =
{
    .panelBusy = 5, ///< EXT3 and EXT3-1 pin 3 Red -> D5
    .panelDC = 4, ///< EXT3 and EXT3-1 pin 4 Orange -> D4
    .panelReset = 3, ///< EXT3 and EXT3-1 pin 5 Yellow -> D3
    .flashCS = 2, ///< EXT3 and EXT3-1 pin 8 Violet -> D2
    .panelCS = 1, ///< EXT3 and EXT3-1 pin 9 Grey -> D1
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2 -> D6
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> D0
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief RedBear Duo configuration, tested
///
const pins_t boardRedBearDuo = boardParticlePhoton;

///
/// @brief Espressif ESP32-Pico-v4
/// @note Numbers refer to GPIOs not pins
/// @warning Specific SPI port with SCK=14 MISO=12 MOSI=13
///
const pins_t boardESP32PicoKitV4 =
{
    .panelBusy = 27, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO27
    .panelDC = 26, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO26
    .panelReset = 25, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO25
    .flashCS = 33, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO33
    .panelCS = 32, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO32
    .panelCSS = 4, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO4
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO0
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GPIO10
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GPIO9
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Espressif ESP32-Pico-DevKitM-2
/// @note Numbers refer to GPIOs not pins
/// @warning Specific SPI port with SCK=14 MISO=12 MOSI=13
///
const pins_t boardESP32PicoDevKitM2 =
{
    .panelBusy = 25, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO25
    .panelDC = 26, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO26
    .panelReset = 32, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO32
    .flashCS = 33, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO33
    .panelCS = 27, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO27
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO33
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO27
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GPIO19
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GPIO8
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Seeed Xiao RP240
/// @note Numbers refer to GPIOs not pins
///
const pins_t boardXiaoRP2040
{
    .panelBusy = 26, ///< EXT3 and EXT3-1 pin 3 Red -> D0 GPIO26
    .panelDC = 27, ///< EXT3 and EXT3-1 pin 4 Orange -> D1 GPIO27
    .panelReset = 28, ///< EXT3 and EXT3-1 pin 5 Yellow -> D2 GPIO28
    .flashCS = 6, ///< EXT3 and EXT3-1 pin 8 Violet -> D4 GPIO6
    .panelCS = 29, ///< EXT3 and EXT3-1 pin 9 Grey -> D3 GPIO29
    .panelCSS = 7, ///< EXT3 and EXT3-1 pin 12 Grey2 -> D5 GPIO7
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> N/A
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D6 GPIO0
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D7 GPIO1
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Teensy 3.x configuration, tested
///
const pins_t boardTeensy3x =
{
    .panelBusy = 14, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 15, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 16, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 17, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 18, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 20 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

/// @}

#endif // hV_LIST_BOARDS_RELEASE

