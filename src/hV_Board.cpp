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
// Copyright (c) Rei Vilo, 2010-2023
// Licence All rights reserved
//

// Library header
#include "hV_Board.h"

hV_Board::hV_Board()
{
    ;
}

void hV_Board::b_begin(pins_t board, uint8_t family, uint16_t delayCS)
{
    _pin = board;
    _family = family;
    _delayCS = delayCS;
}

void hV_Board::b_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5)
{
    delay(ms1); // delay 5ms
    digitalWrite(_pin.panelReset, HIGH); // RES# = 1
    delay(ms2); // delay 5ms
    digitalWrite(_pin.panelReset, LOW);
    delay(ms3);
    digitalWrite(_pin.panelReset, HIGH);
    delay(ms4);
    digitalWrite(_pin.panelCS, HIGH); // CS# = 1
    delay(ms5);
}

void hV_Board::b_waitBusy()
{
    // LOW = busy, HIGH = ready
    while (digitalRead(_pin.panelBusy) != HIGH)
    {
        delay(32); // non-blocking
    }
}

void hV_Board::b_suspend()
{
    // Not implemented
}

void hV_Board::b_resume()
{
    // Not implemented
}

void hV_Board::b_sendIndexFixed(uint8_t index, uint8_t data, uint32_t size)
{
    // Not implemented
}

void hV_Board::b_sendIndexData(uint8_t index, const uint8_t * data, uint32_t size)
{
    digitalWrite(_pin.panelDC, LOW); // DC Low
    digitalWrite(_pin.panelCS, LOW); // CS Low
    if (_family == FAMILY_LARGE)
    {
        if (_pin.panelCSS != NOT_CONNECTED)
        {
            digitalWrite(_pin.panelCSS, LOW);
        }
        delayMicroseconds(450); // 450 + 50 = 500
    }
    delayMicroseconds(50);
    SPI.transfer(index);
    delayMicroseconds(50);
    if (_family == FAMILY_LARGE)
    {
        if (_pin.panelCSS != NOT_CONNECTED)
        {
            delayMicroseconds(450);    // 450 + 50 = 500
            digitalWrite(_pin.panelCSS, HIGH);
        }
    }
    digitalWrite(_pin.panelCS, HIGH); // CS High
    digitalWrite(_pin.panelDC, HIGH); // DC High
    digitalWrite(_pin.panelCS, LOW); // CS Low
    if (_family == FAMILY_LARGE)
    {
        if (_pin.panelCSS != NOT_CONNECTED)
        {
            digitalWrite(_pin.panelCSS, LOW); // CSS Low
            delayMicroseconds(450); // 450 + 50 = 500
        }
    }
    delayMicroseconds(50);
    for (uint32_t i = 0; i < size; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(50);
    if (_family == FAMILY_LARGE)
    {
        if (_pin.panelCSS != NOT_CONNECTED)
        {
            delayMicroseconds(450); // 450 + 50 = 500
            digitalWrite(_pin.panelCSS, HIGH);
        }
    }
    digitalWrite(_pin.panelCS, HIGH); // CS High
}

// Software SPI Master protocol setup
void hV_Board::b_sendIndexDataMaster(uint8_t index, const uint8_t * data, uint32_t size)
{
    if (_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(_pin.panelCSS, HIGH); // CS slave HIGH
    }
    digitalWrite(_pin.panelDC, LOW); // DC Low = Command
    digitalWrite(_pin.panelCS, LOW); // CS Low = Select
    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);
    digitalWrite(_pin.panelCS, HIGH); // CS High = Unselect
    digitalWrite(_pin.panelDC, HIGH); // DC High = Data
    digitalWrite(_pin.panelCS, LOW); // CS Low = Select
    delayMicroseconds(500);

    for (uint32_t i = 0; i < size; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(500);
    digitalWrite(_pin.panelCS, HIGH); // CS High= Unselect
}

// Software SPI Slave protocol setup
void hV_Board::b_sendIndexDataSlave(uint8_t index, const uint8_t * data, uint32_t size)
{
    digitalWrite(_pin.panelCS, HIGH); // CS Master High
    digitalWrite(_pin.panelDC, LOW); // DC Low= Command
    if (_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(_pin.panelCSS, LOW); // CS slave LOW
    }

    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);

    if (_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(_pin.panelCSS, HIGH); // CS slave HIGH
    }

    digitalWrite(_pin.panelDC, HIGH); // DC High = Data

    if (_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(_pin.panelCSS, LOW); // CS slave LOW
    }

    delayMicroseconds(500);

    for (uint32_t i = 0; i < size; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(500);
    if (_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(_pin.panelCSS, HIGH); // CS slave HIGH
    }
}

void hV_Board::b_sendCommand8(uint8_t command)
{
    digitalWrite(_pin.panelDC, LOW);
    digitalWrite(_pin.panelCS, LOW);

    SPI.transfer(command);

    digitalWrite(_pin.panelCS, HIGH);
}

void hV_Board::b_sendCommandData8(uint8_t command, uint8_t data)
{
    digitalWrite(_pin.panelDC, LOW); // LOW = command
    digitalWrite(_pin.panelCS, LOW);

    SPI.transfer(command);

    digitalWrite(_pin.panelDC, HIGH); // HIGH = data
    SPI.transfer(data);

    digitalWrite(_pin.panelCS, HIGH);
}

//
// === Miscellaneous section
//
pins_t hV_Board::getBoardPins()
{
    return _pin;
}
//
// === End of Miscellaneous section
//
