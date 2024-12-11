//
// hV_Board.cpp
// Library C++ code
// ----------------------------------
//
// Project Pervasive Displays Library Suite
// Based on highView technology
//
// Created by Rei Vilo, 16 Aug 2023
//
// Copyright (c) Rei Vilo, 2010-2024
// Licence All rights reserved
//
// Release 700: Initial release
// Release 801: Improved double-panel screen management
// Release 804: Improved power management
// Release 810: Added support for EXT4
//

// Library header
#include "hV_Board.h"

hV_Board::hV_Board()
{
    b_fsmPowerScreen = FSM_OFF;
}

void hV_Board::b_begin(pins_t board, uint8_t family, uint16_t delayCS)
{
    b_pin = board;
    b_family = family;
    b_delayCS = delayCS;
    b_fsmPowerScreen = FSM_OFF;
}

void hV_Board::setPanelPowerPin(uint8_t panelPowerPin)
{
    b_pin.panelPower = panelPowerPin;
}

void hV_Board::b_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5)
{
    delay(ms1); // Wait for power stabilisation
    digitalWrite(b_pin.panelReset, HIGH); // RESET = HIGH
    delay(ms2);
    digitalWrite(b_pin.panelReset, LOW); // RESET = LOW
    delay(ms3);
    digitalWrite(b_pin.panelReset, HIGH); // RESET = HIGH
    delay(ms4);
    digitalWrite(b_pin.panelCS, HIGH); // CS = HIGH, unselect
    delay(ms5);
}

void hV_Board::b_waitBusy(bool state)
{
    // LOW = busy, HIGH = ready
    while (digitalRead(b_pin.panelBusy) != state)
    {
        delay(32); // non-blocking
    }
}

void hV_Board::b_suspend()
{
    if ((b_fsmPowerScreen & FSM_GPIO_MASK) == FSM_GPIO_MASK)
    {
        // Optional power circuit
        if (b_pin.panelPower != NOT_CONNECTED) // generic
        {
            digitalWrite(b_pin.panelPower, LOW);
        }
        b_fsmPowerScreen &= ~FSM_GPIO_MASK;
    }
}

void hV_Board::b_resume()
{
    // Target FSM_ON
    // Source FSM_SLEEP -> FSM_SLEEP
    //        FSM_OFF   -> FSM_SLEEP

    if ((b_fsmPowerScreen & FSM_GPIO_MASK) != FSM_GPIO_MASK)
    {
        // Optional power circuit
        if (b_pin.panelPower != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.panelPower, OUTPUT);
            digitalWrite(b_pin.panelPower, HIGH);
        }

        // Configure GPIOs
        pinMode(b_pin.panelBusy, INPUT);

        pinMode(b_pin.panelDC, OUTPUT);
        digitalWrite(b_pin.panelDC, HIGH);

        pinMode(b_pin.panelReset, OUTPUT);
        digitalWrite(b_pin.panelReset, HIGH);

        pinMode(b_pin.panelCS, OUTPUT);
        digitalWrite(b_pin.panelCS, HIGH); // CS# = 1

        if (b_pin.panelCSS != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.panelCSS, OUTPUT);
            digitalWrite(b_pin.panelCSS, HIGH);
        }

        // External SPI memory
        if (b_pin.flashCS != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.flashCS, OUTPUT);
            digitalWrite(b_pin.flashCS, HIGH);
        }
        if (b_pin.flashCSS != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.flashCSS, OUTPUT);
            digitalWrite(b_pin.flashCSS, HIGH);
        }

        // External SD card
        if (b_pin.cardCS != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.cardCS, OUTPUT);
            digitalWrite(b_pin.cardCS, HIGH);
        }
        if (b_pin.cardDetect != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.cardCS, INPUT);
        }

#if (USE_EXT_BOARD == BOARD_EXT4) // EXT4 GPIOs

        if (b_pin.button != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.button, INPUT_PULLUP);
        }

        if (b_pin.ledData != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.ledData, OUTPUT);
        }

        if (b_pin.nfcFD != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.nfcFD, INPUT);
        }

        if (b_pin.imuInt1 != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.imuInt1, INPUT);
        }

        if (b_pin.imuInt2 != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.imuInt2, INPUT);
        }

        if (b_pin.weatherInt != NOT_CONNECTED) // generic
        {
            pinMode(b_pin.weatherInt, INPUT);
        }

#endif // USE_EXT_BOARD

        b_fsmPowerScreen |= FSM_GPIO_MASK;
    }
}

void hV_Board::b_sendIndexFixed(uint8_t index, uint8_t data, uint32_t size)
{
    digitalWrite(b_pin.panelDC, LOW); // DC Low = Command
    digitalWrite(b_pin.panelCS, LOW); // CS High = Select Master

    delayMicroseconds(b_delayCS);
    hV_HAL_SPI_transfer(index);
    delayMicroseconds(b_delayCS);

    digitalWrite(b_pin.panelDC, HIGH); // DC High = Data

    delayMicroseconds(b_delayCS);
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data); // b_sendIndexFixed
    }
    delayMicroseconds(b_delayCS);

    digitalWrite(b_pin.panelCS, HIGH); // CS High = Unselect
}

void hV_Board::b_sendIndexFixedSelect(uint8_t index, uint8_t data, uint32_t size, uint8_t select)
{
    digitalWrite(b_pin.panelDC, LOW); // DC Low = Command
    b_select(select); // Select half of large screen

    delayMicroseconds(b_delayCS); // Longer delay for large screens
    hV_HAL_SPI_transfer(index);
    delayMicroseconds(b_delayCS); // Longer delay for large screens

    digitalWrite(b_pin.panelDC, HIGH); // DC High = Data

    delayMicroseconds(b_delayCS); // Longer delay for large screens
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data); // b_sendIndexFixed
    }
    delayMicroseconds(b_delayCS); // Longer delay for large screens

    digitalWrite(b_pin.panelCS, HIGH); // CS High = Unselect Master
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, HIGH); // CSS High = Unselect Slave
    }
}

void hV_Board::b_sendIndexData(uint8_t index, const uint8_t * data, uint32_t size)
{
    digitalWrite(b_pin.panelDC, LOW); // DC Low
    digitalWrite(b_pin.panelCS, LOW); // CS Low
    if (b_family == FAMILY_LARGE)
    {
        if (b_pin.panelCSS != NOT_CONNECTED)
        {
            digitalWrite(b_pin.panelCSS, LOW);
        }
        delayMicroseconds(450); // 450 + 50 = 500
    }
    delayMicroseconds(b_delayCS);
    hV_HAL_SPI_transfer(index);
    delayMicroseconds(b_delayCS);
    if (b_family == FAMILY_LARGE)
    {
        if (b_pin.panelCSS != NOT_CONNECTED)
        {
            delayMicroseconds(450); // 450 + 50 = 500
            digitalWrite(b_pin.panelCSS, HIGH);
        }
    }
    digitalWrite(b_pin.panelCS, HIGH); // CS High
    digitalWrite(b_pin.panelDC, HIGH); // DC High
    digitalWrite(b_pin.panelCS, LOW); // CS Low
    if (b_family == FAMILY_LARGE)
    {
        if (b_pin.panelCSS != NOT_CONNECTED)
        {
            digitalWrite(b_pin.panelCSS, LOW); // CSS Low
            delayMicroseconds(450); // 450 + 50 = 500
        }
    }
    delayMicroseconds(b_delayCS);
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data[i]);
    }
    delayMicroseconds(b_delayCS);
    digitalWrite(b_pin.panelCS, HIGH); // CS High
    if (b_family == FAMILY_LARGE)
    {
        if (b_pin.panelCSS != NOT_CONNECTED)
        {
            delayMicroseconds(450); // 450 + 50 = 500
            digitalWrite(b_pin.panelCSS, HIGH);
        }
    }
    delayMicroseconds(b_delayCS);
}

// Software SPI Master protocol setup
void hV_Board::b_sendIndexDataSelect(uint8_t index, const uint8_t * data, uint32_t size, uint8_t select)
{
    digitalWrite(b_pin.panelDC, LOW); // DC Low = Command
    b_select(select); // Select half of large screen

    delayMicroseconds(b_delayCS); // Longer delay for large screens
    hV_HAL_SPI_transfer(index);
    delayMicroseconds(b_delayCS); // Longer delay for large screens

    digitalWrite(b_pin.panelDC, HIGH); // DC High = Data

    delayMicroseconds(b_delayCS); // Longer delay for large screens
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data[i]);
    }
    delayMicroseconds(b_delayCS); // Longer delay for large screens

    digitalWrite(b_pin.panelCS, HIGH); // CS high = Unselect Master
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, HIGH); // CSS High = Unselect Slave
    }
}

void hV_Board::b_select(uint8_t select)
{
    switch (select)
    {
        case PANEL_CS_MASTER:

            digitalWrite(b_pin.panelCS, LOW); // CS Low = Select Master
            if (b_pin.panelCSS != NOT_CONNECTED)
            {
                digitalWrite(b_pin.panelCSS, HIGH); // CSS High = Unselect Slave
            }
            break;

        case PANEL_CS_SLAVE:

            digitalWrite(b_pin.panelCS, HIGH); // CS high = Unselect Master
            if (b_pin.panelCSS != NOT_CONNECTED)
            {
                digitalWrite(b_pin.panelCSS, LOW); // CSS Low = Select Slave
            }
            break;

        default:

            digitalWrite(b_pin.panelCS, LOW); // CS Low = Select Master
            if (b_pin.panelCSS != NOT_CONNECTED)
            {
                digitalWrite(b_pin.panelCSS, LOW); // CSS Low = Select Slave
            }
            break;
    }

    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        delayMicroseconds(450); // 450 + 50 = 500
    }
    delayMicroseconds(b_delayCS); // Longer delay for large screens
}

void hV_Board::b_sendCommandDataSelect8(uint8_t command, uint8_t data, uint8_t select)
{
    digitalWrite(b_pin.panelDC, LOW); // LOW = command
    b_select(select); // Select half of large screen

    hV_HAL_SPI_transfer(command);

    digitalWrite(b_pin.panelDC, HIGH); // HIGH = data
    hV_HAL_SPI_transfer(data);

    digitalWrite(b_pin.panelCS, HIGH);
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, HIGH);
    }
}

void hV_Board::b_sendCommand8(uint8_t command)
{
    digitalWrite(b_pin.panelDC, LOW);
    digitalWrite(b_pin.panelCS, LOW);

    hV_HAL_SPI_transfer(command);

    digitalWrite(b_pin.panelCS, HIGH);
}

void hV_Board::b_sendCommandData8(uint8_t command, uint8_t data)
{
    digitalWrite(b_pin.panelDC, LOW); // LOW = command
    digitalWrite(b_pin.panelCS, LOW);

    hV_HAL_SPI_transfer(command);

    digitalWrite(b_pin.panelDC, HIGH); // HIGH = data
    hV_HAL_SPI_transfer(data);

    digitalWrite(b_pin.panelCS, HIGH);
}

//
// === Miscellaneous section
//
pins_t hV_Board::getBoardPins()
{
    return b_pin;
}
//
// === End of Miscellaneous section
//
