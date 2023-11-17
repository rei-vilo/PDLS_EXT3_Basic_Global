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
    b_pin = board;
    b_family = family;
    b_delayCS = delayCS;
}

void hV_Board::b_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5)
{
    delay(ms1); // delay 5ms
    digitalWrite(b_pin.panelReset, HIGH); // RES# = 1
    delay(ms2); // delay 5ms
    digitalWrite(b_pin.panelReset, LOW);
    delay(ms3);
    digitalWrite(b_pin.panelReset, HIGH);
    delay(ms4);
    digitalWrite(b_pin.panelCS, HIGH); // CS# = 1
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
    SPI.transfer(index);
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
        SPI.transfer(data[i]);
    }
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
}

// Software SPI Master protocol setup
void hV_Board::b_sendIndexDataBoth(uint8_t index, const uint8_t * data, uint32_t size)
{
    digitalWrite(b_pin.panelDC, LOW); // DC Low = Command
    digitalWrite(b_pin.panelCS, LOW); // CS Low = Select
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, LOW); // CS Low = Select
    }

    delayMicroseconds(b_delayCS); // Longer delay for large screens
    SPI.transfer(index);
    delayMicroseconds(b_delayCS); // Longer delay for large screens

    // digitalWrite(b_pin.panelCS, HIGH); // CS High = Unselect
    digitalWrite(b_pin.panelDC, HIGH); // DC High = Data
    // digitalWrite(b_pin.panelCS, LOW); // CS Low = Select

    delayMicroseconds(b_delayCS); // Longer delay for large screens
    for (uint32_t i = 0; i < size; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(b_delayCS); // Longer delay for large screens

    digitalWrite(b_pin.panelCS, HIGH); // CS High = Unselect
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, HIGH); //  CS High = Unselect
    }
}

void hV_Board::b_sendIndexDataMaster(uint8_t index, const uint8_t * data, uint32_t size)
{
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, HIGH); // CS slave HIGH
    }
    digitalWrite(b_pin.panelDC, LOW); // DC Low = Command
    digitalWrite(b_pin.panelCS, LOW); // CS Low = Select
    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);
    digitalWrite(b_pin.panelCS, HIGH); // CS High = Unselect
    digitalWrite(b_pin.panelDC, HIGH); // DC High = Data
    digitalWrite(b_pin.panelCS, LOW); // CS Low = Select
    delayMicroseconds(500);

    for (uint32_t i = 0; i < size; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(500);
    digitalWrite(b_pin.panelCS, HIGH); // CS High= Unselect
}

// Software SPI Slave protocol setup
void hV_Board::b_sendIndexDataSlave(uint8_t index, const uint8_t * data, uint32_t size)
{
    digitalWrite(b_pin.panelCS, HIGH); // CS Master High
    digitalWrite(b_pin.panelDC, LOW); // DC Low= Command
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, LOW); // CS slave LOW
    }

    delayMicroseconds(500);
    SPI.transfer(index);
    delayMicroseconds(500);

    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, HIGH); // CS slave HIGH
    }

    digitalWrite(b_pin.panelDC, HIGH); // DC High = Data

    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, LOW); // CS slave LOW
    }

    delayMicroseconds(500);

    for (uint32_t i = 0; i < size; i++)
    {
        SPI.transfer(data[i]);
    }
    delayMicroseconds(500);
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        digitalWrite(b_pin.panelCSS, HIGH); // CS slave HIGH
    }
}

void hV_Board::b_sendCommand8(uint8_t command)
{
    digitalWrite(b_pin.panelDC, LOW);
    digitalWrite(b_pin.panelCS, LOW);

    SPI.transfer(command);

    digitalWrite(b_pin.panelCS, HIGH);
}

void hV_Board::b_sendCommandData8(uint8_t command, uint8_t data)
{
    digitalWrite(b_pin.panelDC, LOW); // LOW = command
    digitalWrite(b_pin.panelCS, LOW);

    SPI.transfer(command);

    digitalWrite(b_pin.panelDC, HIGH); // HIGH = data
    SPI.transfer(data);

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
