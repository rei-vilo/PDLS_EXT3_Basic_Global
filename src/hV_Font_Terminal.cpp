//
// hV_Font_Terminal.cpp
// C++ code
// ----------------------------------
//
// Project highView Library Suite
//
// Created by Rei Vilo, 31 Dec 2013
//
// Copyright (c) Rei Vilo, 2010-2021
// Licence All rights reserved
//
// * Basic edition: for hobbyists and for personal usage
// Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
//
// * Advanced edition: for professionals or organisations, no commercial usage
// All rights reserved
//
// * Commercial edition: for professionals or organisations, commercial usage
// All rights reserved
//

#include "hV_Font_Terminal.h"
//#include "hV_Utilities.h"

// The Arduino IDE doesn't allow to select the libraries, hence this condition.
#if (FONT_MODE == USE_FONT_TERMINAL)

// Code
// Font functions
//hV_Font_Terminal::hV_Font_Terminal()
void hV_Font_Terminal::_f_begin()
{
    _f_fontSize       = 0;
    _f_fontNumber     = MAX_FONT_SIZE;
    _f_fontSolid      = true;
    _f_fontSpaceX     = 1;

    // Take first font
    _f_selectFont(0);
}

uint8_t hV_Font_Terminal::_f_addFont(font_s fontName)
{
    return _f_fontNumber;
}

void hV_Font_Terminal::_f_setFontSolid(bool flag)
{
    _f_fontSolid = flag;
}

void hV_Font_Terminal::_f_selectFont(uint8_t size)
{
    if (size < MAX_FONT_SIZE)
    {
        _f_fontSize = size;
    }
    else
    {
        _f_fontSize = MAX_FONT_SIZE - 1;
    }

    switch (_f_fontSize)
    {
        case 0:
            // kind, height, maxWidth, first, number
            _f_font = { 0x40, 8, 6, 32, 224 };
            break;

        case 1:
            _f_font = { 0x40, 12, 8, 32, 224 };
            break;

        case 2:
            _f_font = { 0x40, 16, 12, 32, 224 };
            break;

        case 3:
            _f_font = { 0x40, 24, 16, 32, 224 };
            break;

        default:
            break;
    }
}

uint8_t hV_Font_Terminal::_f_fontMax()
{
    return MAX_FONT_SIZE;
}

void hV_Font_Terminal::_f_setFontSpaceX(uint8_t number)
{
    _f_fontSpaceX = number;
}

void hV_Font_Terminal::_f_setFontSpaceY(uint8_t number)
{
    _f_fontSpaceY = number;
}

uint8_t hV_Font_Terminal::_f_getCharacter(uint8_t character, uint16_t index)
{
#if (MAX_FONT_SIZE > 0)
    if (_f_fontSize == 0)
    {
        return Terminal6x8e[character][index];
    }
#if (MAX_FONT_SIZE > 1)
    else if (_f_fontSize == 1)
    {
        return Terminal8x12e[character][index];
    }
#if (MAX_FONT_SIZE > 2)
    else if (_f_fontSize == 2)
    {
        return Terminal12x16e[character][index];
    }
#if (MAX_FONT_SIZE > 3)
    else if (_f_fontSize == 3)
    {
        return Terminal16x24e[character][index];
    }
#endif // end MAX_FONT_SIZE > 3
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
    else
    {
        return 0;
    }
#endif // end MAX_FONT_SIZE > 0
}

uint16_t hV_Font_Terminal::_f_characterSizeX(uint8_t character)
{
    return _f_font.maxWidth;
}

uint16_t hV_Font_Terminal::_f_characterSizeY()
{
    return _f_font.height;
}

uint16_t hV_Font_Terminal::_f_stringSizeX(String text)
{
    return (uint16_t) text.length() * _f_font.maxWidth;
}

uint8_t hV_Font_Terminal::_f_stringLengthToFitX(String text, uint16_t pixels)
{
    uint8_t index = 0;

    // Monospaced font
    index = pixels / _f_font.maxWidth - 1;
    if (index > text.length())
    {
        index = text.length();
    }
    return index;
}

uint8_t hV_Font_Terminal::_f_getFontKind()
{
    return _f_font.kind; // monospaced
}
uint8_t hV_Font_Terminal::_f_getFontMaxWidth()
{
    return _f_font.maxWidth;
}

#endif // USE_FONT_TERMINAL
