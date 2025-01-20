//
// hV_Font_Terminal.cpp
// C++ code
// ----------------------------------
//
// Project highView Library Suite
//
// Created by Rei Vilo, 31 Dec 2013
//
// Copyright (c) Rei Vilo, 2010-2025
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
// Release 803: Added types for string and frame-buffer
//

// Configuration
#include "hV_Configuration.h"

// The Arduino IDE does not allow to select the libraries, hence this condition.
#if (FONT_MODE == USE_FONT_TERMINAL)

// Font structure
#include "hV_Font_Terminal.h"

// Code
// Font functions
// hV_Font_Terminal::hV_Font_Terminal()
void hV_Font_Terminal::f_begin()
{
    f_fontSize = 0;
    f_fontNumber = MAX_FONT_SIZE;
    f_fontSolid = true;
    f_fontSpaceX = 1;

    // Take first font
    f_selectFont(0);
}

uint8_t hV_Font_Terminal::f_addFont(font_s fontName)
{
    return f_fontNumber;
}

void hV_Font_Terminal::f_setFontSolid(bool flag)
{
    f_fontSolid = flag;
}

void hV_Font_Terminal::f_selectFont(uint8_t size)
{
    if (size < MAX_FONT_SIZE)
    {
        f_fontSize = size;
    }
    else
    {
        f_fontSize = MAX_FONT_SIZE - 1;
    }

    switch (f_fontSize)
    {
        case 0:
            // kind, height, maxWidth, first, number
            f_font = { 0x40, 8, 6, 32, 224 };
            break;

        case 1:
            f_font = { 0x40, 12, 8, 32, 224 };
            break;

        case 2:
            f_font = { 0x40, 16, 12, 32, 224 };
            break;

        case 3:
            f_font = { 0x40, 24, 16, 32, 224 };
            break;

        default:
            break;
    }
}

uint8_t hV_Font_Terminal::f_fontMax()
{
    return MAX_FONT_SIZE;
}

void hV_Font_Terminal::f_setFontSpaceX(uint8_t number)
{
    f_fontSpaceX = number;
}

void hV_Font_Terminal::f_setFontSpaceY(uint8_t number)
{
    f_fontSpaceY = number;
}

uint8_t hV_Font_Terminal::f_getCharacter(uint8_t character, uint16_t index)
{
#if (MAX_FONT_SIZE > 0)
    if (f_fontSize == 0)
    {
        return Terminal6x8e[character][index];
    }
#if (MAX_FONT_SIZE > 1)
    else if (f_fontSize == 1)
    {
        return Terminal8x12e[character][index];
    }
#if (MAX_FONT_SIZE > 2)
    else if (f_fontSize == 2)
    {
        return Terminal12x16e[character][index];
    }
#if (MAX_FONT_SIZE > 3)
    else if (f_fontSize == 3)
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

uint16_t hV_Font_Terminal::f_characterSizeX(uint8_t character)
{
    return f_font.maxWidth;
}

uint16_t hV_Font_Terminal::f_characterSizeY()
{
    return f_font.height;
}

uint16_t hV_Font_Terminal::f_stringSizeX(STRING_CONST_TYPE text)
{
    uint16_t textWidth = 0;
    uint8_t textLength = 0;

    textLength = text.length();

    textWidth = (f_font.maxWidth + f_fontSpaceX) * textLength;

    return textWidth;
}

uint8_t hV_Font_Terminal::f_stringLengthToFitX(STRING_CONST_TYPE text, uint16_t pixels)
{
    uint8_t index = 0;
    uint16_t textWidth = 0;
    uint8_t textLength = 0;

    textLength = text.length();

    // Monospaced font
    index = pixels / f_font.maxWidth - 1;
    if (index > textLength)
    {
        index = textLength;
    }

    return index;
}

uint8_t hV_Font_Terminal::f_getFontKind()
{
    return f_font.kind; // monospaced
}
uint8_t hV_Font_Terminal::f_getFontMaxWidth()
{
    return f_font.maxWidth;
}

#endif // USE_FONT_TERMINAL
