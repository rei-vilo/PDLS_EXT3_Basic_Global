//
// hV_Screen_Buffer.cpp
// Class library C++ code
// ----------------------------------
//
// Project Pervasive Displays Library Suite
// Based on highView technology
//
// Created by Rei Vilo, 28 Jun 2016
//
// Copyright (c) Rei Vilo, 2010-2024
// Licence Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
// For exclusive use with Pervasive Displays screens
//
// See hV_Screen_Buffer.h for references
//
// Release 520: Added use of hV_HAL_Peripherals
// Release 523: Fixed rounded rectangles
// Release 526: Improved touch management
// Release 700: Refactored screen and board functions
// Release 703: Improved orientation function
// Release 801: Improved functions names consistency
// Release 805: Added large variant for gText()
//

// Library header
#include "hV_Screen_Buffer.h"
//#include "QuickDebug.h"

// Code
hV_Screen_Buffer::hV_Screen_Buffer()
{
    f_fontSize = 0;
    f_fontNumber = 0;
    f_fontSolid = true;
    f_fontSpaceX = 1;
    v_penSolid = false;
}

void hV_Screen_Buffer::begin()
{
    f_begin(); // hV_Font_...
}

void hV_Screen_Buffer::clear(uint16_t colour)
{
    uint8_t oldOrientation = v_orientation;
    bool oldPenSolid = v_penSolid;
    setOrientation(0);
    setPenSolid();
    rectangle(0, 0, screenSizeX() - 1, screenSizeY() - 1, colour);
    setOrientation(oldOrientation);
    setPenSolid(oldPenSolid);
}

void hV_Screen_Buffer::flush()
{
    ;
}

void hV_Screen_Buffer::setOrientation(uint8_t orientation)
{
    switch (orientation)
    {
        case ORIENTATION_PORTRAIT:

            v_orientation = 0;
            s_setOrientation(v_orientation);
            if (screenSizeX() > screenSizeY())
            {
                v_orientation += 1;
                s_setOrientation(v_orientation);
            }
            break;

        case ORIENTATION_LANDSCAPE:

            v_orientation = 2;
            s_setOrientation(v_orientation);
            if (screenSizeX() < screenSizeY())
            {
                v_orientation += 1;
                s_setOrientation(v_orientation);
            }
            break;

        default:

            v_orientation = orientation % 4;
            s_setOrientation(v_orientation);
            break;
    }
}

uint8_t hV_Screen_Buffer::getOrientation()
{
    return v_orientation;
}

uint16_t hV_Screen_Buffer::screenSizeX()
{
    switch (v_orientation)
    {
        case 1:
        case 3:

            return v_screenSizeV; // _maxX
            break;

        // case 0:
        // case 2:
        default:

            return v_screenSizeH; // _maxX
            break;
    }
    return 0;
}

uint16_t hV_Screen_Buffer::screenSizeY()
{
    switch (v_orientation)
    {
        case 1:
        case 3:

            return v_screenSizeH; // _maxY
            break;

        // case 0:
        // case 2:
        default:

            return v_screenSizeV; // _maxY
            break;
    }
    return 0;
}

uint16_t hV_Screen_Buffer::screenDiagonal()
{
    return v_screenDiagonal;
}

uint8_t hV_Screen_Buffer::screenColourBits()
{
    return v_screenColourBits;
}

void hV_Screen_Buffer::circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t colour)
{
    int16_t f = 1 - radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * radius;
    int16_t x = 0;
    int16_t y = radius;

    if (v_penSolid == false)
    {
        point(x0, y0 + radius, colour);
        point(x0, y0 - radius, colour);
        point(x0 + radius, y0, colour);
        point(x0 - radius, y0, colour);

        while (x < y)
        {
            if (f >= 0)
            {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }

            x++;
            ddF_x += 2;
            f += ddF_x;

            point(x0 + x, y0 + y, colour);
            point(x0 - x, y0 + y, colour);
            point(x0 + x, y0 - y, colour);
            point(x0 - x, y0 - y, colour);
            point(x0 + y, y0 + x, colour);
            point(x0 - y, y0 + x, colour);
            point(x0 + y, y0 - x, colour);
            point(x0 - y, y0 - x, colour);
        }
    }
    else
    {
        while (x < y)
        {
            if (f >= 0)
            {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }

            x++;
            ddF_x += 2;
            f += ddF_x;

            line(x0 + x, y0 + y, x0 - x, y0 + y, colour); // bottom
            line(x0 + x, y0 - y, x0 - x, y0 - y, colour); // top
            line(x0 + y, y0 - x, x0 + y, y0 + x, colour); // right
            line(x0 - y, y0 - x, x0 - y, y0 + x, colour); // left
        }

        setPenSolid(true);
        rectangle(x0 - x, y0 - y, x0 + x, y0 + y, colour);
    }
}

void hV_Screen_Buffer::dLine(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour)
{
    line(x0, y0, x0 + dx - 1, y0 + dy - 1, colour);
}

void hV_Screen_Buffer::line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour)
{
    if ((x1 == x2) and (y1 == y2))
    {
        s_setPoint(x1, y1, colour);
    }
    else if (x1 == x2)
    {
        if (y1 > y2)
        {
            swap(y1, y2);
        }
        for (uint16_t y = y1; y <= y2; y++)
        {
            s_setPoint(x1, y, colour);
        }
    }
    else if (y1 == y2)
    {
        if (x1 > x2)
        {
            swap(x1, x2);
        }
        for (uint16_t x = x1; x <= x2; x++)
        {
            s_setPoint(x, y1, colour);
        }
    }
    else
    {
        int16_t wx1 = (int16_t)x1;
        int16_t wx2 = (int16_t)x2;
        int16_t wy1 = (int16_t)y1;
        int16_t wy2 = (int16_t)y2;

        bool flag = abs(wy2 - wy1) > abs(wx2 - wx1);
        if (flag)
        {
            swap(wx1, wy1);
            swap(wx2, wy2);
        }

        if (wx1 > wx2)
        {
            swap(wx1, wx2);
            swap(wy1, wy2);
        }

        int16_t dx = wx2 - wx1;
        int16_t dy = abs(wy2 - wy1);
        int16_t err = dx / 2;
        int16_t ystep;

        if (wy1 < wy2)
        {
            ystep = 1;
        }
        else
        {
            ystep = -1;
        }

        for (; wx1 <= wx2; wx1++)
        {
            if (flag)
            {
                s_setPoint(wy1, wx1, colour);
            }
            else
            {
                s_setPoint(wx1, wy1, colour);
            }

            err -= dy;
            if (err < 0)
            {
                wy1 += ystep;
                err += dx;
            }
        }
    }
}

void hV_Screen_Buffer::setPenSolid(bool flag)
{
    v_penSolid = flag;
}

void hV_Screen_Buffer::point(uint16_t x1, uint16_t y1, uint16_t colour)
{
    s_setPoint(x1, y1, colour);
}

void hV_Screen_Buffer::rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour)
{
    if (v_penSolid == false)
    {
        line(x1, y1, x1, y2, colour);
        line(x1, y1, x2, y1, colour);
        line(x1, y2, x2, y2, colour);
        line(x2, y1, x2, y2, colour);
    }
    else
    {
        if (x1 > x2)
        {
            swap(x1, x2);
        }
        if (y1 > y2)
        {
            swap(y1, y2);
        }
        for (uint16_t x = x1; x <= x2; x++)
        {
            for (uint16_t y = y1; y <= y2; y++)
            {
                s_setPoint(x, y, colour);
            }
        }
    }
}

void hV_Screen_Buffer::dRectangle(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour)
{
    rectangle(x0, y0, x0 + dx - 1, y0 + dy - 1, colour);
}

void hV_Screen_Buffer::s_triangleArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour)
{
    int16_t wx1 = (int16_t)x1;
    int16_t wy1 = (int16_t)y1;
    int16_t wx2 = (int16_t)x2;
    int16_t wy2 = (int16_t)y2;
    int16_t wx3 = (int16_t)x3;
    int16_t wy3 = (int16_t)y3;
    int16_t wx4 = wx1;
    int16_t wy4 = wy1;
    int16_t wx5 = wx1;
    int16_t wy5 = wy1;

    bool changed1 = false;
    bool changed2 = false;

    int16_t dx1 = abs(wx2 - wx1);
    int16_t dy1 = abs(wy2 - wy1);

    int16_t dx2 = abs(wx3 - wx1);
    int16_t dy2 = abs(wy3 - wy1);

    int16_t signx1 = (wx2 >= wx1) ? +1 : -1;
    int16_t signx2 = (wx3 >= wx1) ? +1 : -1;

    int16_t signy1 = (wy2 >= wy1) ? +1 : -1;
    int16_t signy2 = (wy3 >= wy1) ? +1 : -1;

    if (dy1 > dx1)
    {
        swap(dx1, dy1); // swap values
        changed1 = true;
    }

    if (dy2 > dx2)
    {
        swap(dx2, dy2); // swap values
        changed2 = true;
    }

    int16_t e1 = 2 * dy1 - dx1;
    int16_t e2 = 2 * dy2 - dx2;

    for (int i = 0; i <= dx1; i++)
    {
        line(wx4, wy4, wx5, wy5, colour);

        while (e1 >= 0)
        {
            if (changed1)
            {
                wx4 += signx1;
            }
            else
            {
                wy4 += signy1;
            }
            e1 = e1 - 2 * dx1;
        }

        if (changed1)
        {
            wy4 += signy1;
        }
        else
        {
            wx4 += signx1;
        }

        e1 = e1 + 2 * dy1;

        while (wy5 != wy4)
        {
            while (e2 >= 0)
            {
                if (changed2)
                {
                    wx5 += signx2;
                }
                else
                {
                    wy5 += signy2;
                }
                e2 = e2 - 2 * dx2;
            }

            if (changed2)
            {
                wy5 += signy2;
            }
            else
            {
                wx5 += signx2;
            }

            e2 = e2 + 2 * dy2;
        }
    }
}

void hV_Screen_Buffer::triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour)
{
    if ((x1 == x2) and (y1 == y2))
    {
        line(x3, y3, x1, y1, colour);
    }
    else if ((x1 == x3) and (y1 == y3))
    {
        line(x2, y2, x3, y3, colour);
    }
    else if ((x2 == x3) and (y2 == y3))
    {
        line(x1, y1, x2, y2, colour);
    }
    else if (v_penSolid)
    {
        bool b = true;

        // Graham Scan + Andrew's Monotone Chain Algorithm
        // Sort by ascending y
        while (b)
        {
            b = false;
            if ((b == false) and (y1 > y2))
            {
                swap(x1, x2);
                swap(y1, y2);
                b = true;
            }
            if ((b == false) and (y2 > y3))
            {
                swap(x3, x2);
                swap(y3, y2);
                b = true;
            }
        }

        if (y2 == y3)
        {
            s_triangleArea(x1, y1, x2, y2, x3, y3, colour);
        }
        else if (y1 == y2)
        {
            s_triangleArea(x3, y3, x1, y1, x2, y2, colour);
        }
        else
        {
            uint16_t x4 = (uint16_t)((int32_t)x1 + (y2 - y1) * (x3 - x1) / (y3 - y1));
            uint16_t y4 = y2;

            s_triangleArea(x1, y1, x2, y2, x4, y4, colour);

#if defined(ESP8266)
            delay(1);
#else
            delayMicroseconds(1000); // delay(1);
#endif // ESP8266

            delayMicroseconds(1000); // delay(1);
            s_triangleArea(x3, y3, x2, y2, x4, y4, colour);

#if defined(ESP8266)
            delay(1);
#else
            delayMicroseconds(1000); // delay(1);
#endif // ESP8266
        }
    }
    else
    {
        line(x1, y1, x2, y2, colour);
        line(x2, y2, x3, y3, colour);
        line(x3, y3, x1, y1, colour);
    }
}

//
// === Font section
//
void hV_Screen_Buffer::setFontSolid(bool flag)
{
    f_setFontSolid(flag);
}

uint8_t hV_Screen_Buffer::addFont(font_s fontName)
{
    return f_addFont(fontName);
}

void hV_Screen_Buffer::selectFont(uint8_t font)
{
    f_selectFont(font);
}

uint8_t hV_Screen_Buffer::getFont()
{
    return f_fontSize;
}

uint8_t hV_Screen_Buffer::fontMax()
{
    return f_fontMax();
}

uint16_t hV_Screen_Buffer::characterSizeX(uint8_t character)
{
    uint16_t result = 0;
    if ((f_font.kind & 0x40) == 0x40) // Monospaced font
    {
        result = f_font.maxWidth + f_fontSpaceX;
    }
    else
    {
        result = f_characterSizeX(character);
    }

    return result;
}

uint16_t hV_Screen_Buffer::characterSizeY()
{
    return f_characterSizeY();
}

uint16_t hV_Screen_Buffer::stringSizeX(String text)
{
    return f_stringSizeX(text);
}

uint8_t hV_Screen_Buffer::stringLengthToFitX(String text, uint16_t pixels)
{
    return f_stringLengthToFitX(text, pixels);
}

void hV_Screen_Buffer::setFontSpaceX(uint8_t number)
{
    f_setFontSpaceX(number);
}

void hV_Screen_Buffer::setFontSpaceY(uint8_t number)
{
    f_setFontSpaceY(number);
}

uint8_t hV_Screen_Buffer::s_getCharacter(uint8_t character, uint8_t index)
{
    return f_getCharacter(character, index);
}

void hV_Screen_Buffer::gText(uint16_t x0, uint16_t y0,
                             String text,
                             uint16_t textColour,
                             uint16_t backColour)
{
#if (FONT_MODE == USE_FONT_TERMINAL)

    uint8_t c;
    uint8_t line, line1, line2, line3;
    uint16_t x, y;
    uint8_t i, j, k;
#if (MAX_FONT_SIZE > 0)
    if (f_fontSize == 0)
    {
        for (k = 0; k < text.length(); k++)
        {
            c = text.charAt(k) - ' ';

            for (i = 0; i < 6; i++)
            {
                line = f_getCharacter(c, i);

                for (j = 0; j < 8; j++)
                    if (bitRead(line, j))
                    {
                        point(x0 + 6 * k + i, y0 + j, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        point(x0 + 6 * k + i, y0 + j, backColour);
                    }
            }
        }
    }
#if (MAX_FONT_SIZE > 1)
    else if (f_fontSize == 1)
    {
        for (k = 0; k < text.length(); k++)
        {
            c = text.charAt(k) - ' ';

            for (i = 0; i < 8; i++)
            {
                line = f_getCharacter(c, 2 * i);
                line1 = f_getCharacter(c, 2 * i + 1);

                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        point(x0 + 8 * k + i, y0 + j, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        point(x0 + 8 * k + i, y0 + j, backColour);
                    }
                    if (bitRead(line1, j))
                    {
                        point(x0 + 8 * k + i, y0 + 8 + j, textColour);
                    }
                    else if ((f_fontSolid) and (j < 4))
                    {
                        point(x0 + 8 * k + i, y0 + 8 + j, backColour);
                    }
                }
            }
        }
    }
#if (MAX_FONT_SIZE > 2)
    else if (f_fontSize == 2)
    {

        for (k = 0; k < text.length(); k++)
        {
            c = text.charAt(k) - ' ';

            for (i = 0; i < 12; i++)
            {
                line = f_getCharacter(c, 2 * i);
                line1 = f_getCharacter(c, 2 * i + 1);

                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        point(x0 + 12 * k + i, y0 + j, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        point(x0 + 12 * k + i, y0 + j, backColour);
                    }
                    if (bitRead(line1, j))
                    {
                        point(x0 + 12 * k + i, y0 + 8 + j, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        point(x0 + 12 * k + i, y0 + 8 + j, backColour);
                    }
                }
            }
        }
    }
#if (MAX_FONT_SIZE > 3)
    else if (f_fontSize == 3)
    {
        for (k = 0; k < text.length(); k++)
        {
            c = text.charAt(k) - ' ';
            for (i = 0; i < 16; i++)
            {
                line = f_getCharacter(c, 3 * i);
                line1 = f_getCharacter(c, 3 * i + 1);
                line2 = f_getCharacter(c, 3 * i + 2);
                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        point(x0 + 16 * k + i, y0 + j, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        point(x0 + 16 * k + i, y0 + j, backColour);
                    }
                    if (bitRead(line1, j))
                    {
                        point(x0 + 16 * k + i, y0 + 8 + j, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        point(x0 + 16 * k + i, y0 + 8 + j, backColour);
                    }
                    if (bitRead(line2, j))
                    {
                        point(x0 + 16 * k + i, y0 + 16 + j, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        point(x0 + 16 * k + i, y0 + 16 + j, backColour);
                    }
                }
            }
        }
    }
#endif // end MAX_FONT_SIZE > 3
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
#endif // end MAX_FONT_SIZE > 0
#endif // FONT_MODE
}

void hV_Screen_Buffer::gTextLarge(uint16_t x0, uint16_t y0,
                                  String text,
                                  uint16_t textColour,
                                  uint16_t backColour)
{
#if (FONT_MODE == USE_FONT_TERMINAL)

    uint8_t c;
    uint8_t line, line1, line2, line3;
    uint16_t x, y;
    uint8_t i, j, k;

    uint8_t ix = 2;
    uint8_t iy = 2;

    bool oldPenSolid = v_penSolid;
    setPenSolid(true);

#if (MAX_FONT_SIZE > 0)
    if (f_fontSize == 0)
    {
        for (k = 0; k < text.length(); k++)
        {
            x = x0 + 6 * k * ix;
            y = y0;
            c = text.charAt(k) - ' ';

            for (i = 0; i < 6; i++)
            {
                line = f_getCharacter(c, i);

                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        dRectangle(x + i * ix, y + j * iy, ix, iy, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        dRectangle(x + i * ix, y + j * iy, ix, iy, backColour);
                    }
                }
            }
        }
    }

#if (MAX_FONT_SIZE > 1)
    else if (f_fontSize == 1)
    {
        for (k = 0; k < text.length(); k++)
        {
            x = x0 + 8 * k * ix;
            y = y0;
            c = text.charAt(k) - ' ';

            for (i = 0; i < 8; i++)
            {
                line = f_getCharacter(c, 2 * i);
                line1 = f_getCharacter(c, 2 * i + 1);

                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        dRectangle(x + i * ix, y0 + j * iy, ix, iy, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        dRectangle(x + i * ix, y0 + j * iy, ix, iy, backColour);
                    }
                    if (bitRead(line1, j))
                    {
                        dRectangle(x + i * ix, y0 + (8 + j) * iy, ix, iy, textColour);
                    }
                    else if ((f_fontSolid) and (j < 4))
                    {
                        dRectangle(x + i * ix, y0 + (8 + j) * iy, ix, iy, backColour);
                    }
                }
            }
        }
    }

#if (MAX_FONT_SIZE > 2)
    else if (f_fontSize == 2)
    {

        for (k = 0; k < text.length(); k++)
        {
            x = x0 + 12 * k * ix;
            y = y0;
            c = text.charAt(k) - ' ';

            for (i = 0; i < 12; i++)
            {
                line = f_getCharacter(c, 2 * i);
                line1 = f_getCharacter(c, 2 * i + 1);

                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        dRectangle(x + i * ix, y0 + j * iy, ix, iy, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        dRectangle(x + i * ix, y0 + j * iy, ix, iy, backColour);
                    }
                    if (bitRead(line1, j))
                    {
                        dRectangle(x + i * ix, y0 + (8 + j) * iy, ix, iy, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        dRectangle(x + i * ix, y0 + (8 + j) * iy, ix, iy, backColour);
                    }
                }
            }
        }
    }
#if (MAX_FONT_SIZE > 3)
    else if (f_fontSize == 3)
    {
        for (k = 0; k < text.length(); k++)
        {
            x = x0 + 16 * k * ix;
            y = y0;
            c = text.charAt(k) - ' ';

            for (i = 0; i < 16; i++)
            {
                line = f_getCharacter(c, 3 * i);
                line1 = f_getCharacter(c, 3 * i + 1);
                line2 = f_getCharacter(c, 3 * i + 2);
                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        dRectangle(x + i * ix, y0 + j * iy, ix, iy, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        dRectangle(x + i * ix, y0 + j * iy, ix, iy, backColour);
                    }
                    if (bitRead(line1, j))
                    {
                        dRectangle(x + i * ix, y0 + (8 + j) * iy, ix, iy, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        dRectangle(x + i * ix, y0 + (8 + j) * iy, ix, iy, backColour);
                    }
                    if (bitRead(line2, j))
                    {
                        dRectangle(x + i * ix, y0 + (16 + j) * iy, ix, iy, textColour);
                    }
                    else if (f_fontSolid)
                    {
                        dRectangle(x + i * ix, y0 + (16 + j) * iy, ix, iy, backColour);
                    }
                }
            }
        }
    }
#endif // end MAX_FONT_SIZE > 3
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
#endif // end MAX_FONT_SIZE > 0

    setPenSolid(oldPenSolid);

#endif // FONT_MODE
}
//
// === End of Font section
//

