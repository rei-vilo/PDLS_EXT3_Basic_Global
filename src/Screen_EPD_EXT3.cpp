//
// Screen_EPD_EXT3.cpp
// Library C++ code
// ----------------------------------
//
// Project Pervasive Displays Library Suite
// Based on highView technology
//
// Created by Rei Vilo, 28 Jun 2016
//
// Copyright (c) Rei Vilo, 2010-2023
// Licence Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
//
// Release 508: Added support for E2969CS0B and E2B98CS0B
// Release 527: Added support for ESP32 PSRAM
// Release 541: Improved support for ESP32
// Release 550: Tested Xiao ESP32-C3 with SPI exception
// Release 601: Added support for screens with embedded fast update
// Release 602: Improved functions structure
// Release 604: Improved stability
// Release 607: Improved screens names consistency
// Release 608: Added screen report
// Release 609: Added temperature management
// Release 613: Improved stability for BWR screens
// Release 700: Refactored screen and board functions
// Release 701: Improved functions names consistency
//

// Library header
#include "Screen_EPD_EXT3.h"

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

//
// === COG section
//

//
// === End of COG section
//

//
// === Class section
//
Screen_EPD_EXT3::Screen_EPD_EXT3(eScreen_EPD_EXT3_t eScreen_EPD_EXT3, pins_t board)
{
    u_eScreen_EPD_EXT3 = eScreen_EPD_EXT3;
    b_pin = board;
    u_newImage = 0; // nullptr
}

void Screen_EPD_EXT3::begin()
{
    u_codeExtra = (u_eScreen_EPD_EXT3 >> 16) & 0xff;
    u_codeSize = (u_eScreen_EPD_EXT3 >> 8) & 0xff;
    u_codeType = u_eScreen_EPD_EXT3 & 0xff;
    _screenColourBits = 2; // BWR and BWRY

    // Configure board
    switch (u_codeSize)
    {
        case 0x58: // 5.81"
        case 0x74: // 7.40"

            u_begin(b_pin, FAMILY_MEDIUM, 50);
            break;

        case 0x96: // 9.69"
        case 0xB9: // 11.98"

            u_begin(b_pin, FAMILY_LARGE, 0);
            break;

        default:

            u_begin(b_pin, FAMILY_SMALL, 50);
            break;
    }

    switch (u_codeSize)
    {
        case 0x15: // 1.54"

            _screenSizeV = 152; // vertical = wide size
            _screenSizeH = 152; // horizontal = small size
            _screenDiagonal = 154;
            break;

        case 0x21: // 2.13"

            _screenSizeV = 212; // vertical = wide size
            _screenSizeH = 104; // horizontal = small size
            _screenDiagonal = 213;
            break;

        case 0x26: // 2.66"

            _screenSizeV = 296; // vertical = wide size
            _screenSizeH = 152; // horizontal = small size
            _screenDiagonal = 266;
            break;

        case 0x27: // 2.71" and 2.71"-Touch

            _screenSizeV = 264; // vertical = wide size
            _screenSizeH = 176; // horizontal = small size
            _screenDiagonal = 271;
            break;

        case 0x28: // 2.87"

            _screenSizeV = 296; // vertical = wide size
            _screenSizeH = 128; // horizontal = small size
            _screenDiagonal = 287;
            break;

        case 0x29: // 2.92"

            _screenSizeV = 384; // vertical = wide size
            _screenSizeH = 168; // horizontal = small size
            _screenDiagonal = 292;
            break;

        case 0x37: // 3.70" and 3.70"-Touch

            _screenSizeV = 416; // vertical = wide size
            _screenSizeH = 240; // horizontal = small size
            _screenDiagonal = 370;
            break;

        case 0x41: // 4.17"

            _screenSizeV = 300; // vertical = wide size
            _screenSizeH = 400; // horizontal = small size
            _screenDiagonal = 417;
            break;

        case 0x43: // 4.37"

            _screenSizeV = 480; // vertical = wide size
            _screenSizeH = 176; // horizontal = small size
            _screenDiagonal = 437;
            break;

        case 0x56: // 5.65"

            _screenSizeV = 600; // v = wide size
            _screenSizeH = 448; // h = small size
            _screenDiagonal = 565;
            break;

        case 0x58: // 5.81"

            _screenSizeV = 720; // v = wide size
            _screenSizeH = 256; // h = small size
            _screenDiagonal = 581;
            break;

        case 0x74: // 7.40"

            _screenSizeV = 800; // v = wide size
            _screenSizeH = 480; // h = small size
            _screenDiagonal = 741;
            break;

        case 0x96: // 9.69"

            _screenSizeV = 672; // v = wide size
            _screenSizeH = 960; // Actually, 960 = 480 x 2, h = small size
            _screenDiagonal = 969;
            break;

        case 0xB9: // 11.98"

            _screenSizeV = 768; // v = wide size
            _screenSizeH = 960; // Actually, 960 = 480 x 2, h = small size
            _screenDiagonal = 1198;
            break;

        default:

            break;
    } // u_codeSize

    u_bufferDepth = _screenColourBits; // 2 colours
    u_bufferSizeV = _screenSizeV; // vertical = wide size
    u_bufferSizeH = _screenSizeH / 8; // horizontal = small size 112 / 8; 1 bit per pixel

    // Force conversion for two unit16_t multiplication into uint32_t.
    // Actually for 1 colour; BWR requires 2 pages.
    u_pageColourSize = (uint32_t)u_bufferSizeV * (uint32_t)u_bufferSizeH;

    // u_frameSize = u_pageColourSize, except for 9.69 and 11.98
    // 9.69 and 11.98 combine two half-screens, hence two frames with adjusted size
    switch (u_codeSize)
    {
        case 0x96: // 9.69"
        case 0xB9: // 11.98"

            u_frameSize = u_pageColourSize / 2;
            break;

        default:

            u_frameSize = u_pageColourSize;
            break;
    } // u_codeSize

#if defined(BOARD_HAS_PSRAM) // ESP32 PSRAM specific case

    if (u_newImage == 0)
    {
        static uint8_t * _newFrameBuffer;
        _newFrameBuffer = (uint8_t *) ps_malloc(u_pageColourSize * u_bufferDepth);
        u_newImage = (uint8_t *) _newFrameBuffer;
    }

#else // default case

    if (u_newImage == 0)
    {
        static uint8_t * _newFrameBuffer;
        _newFrameBuffer = new uint8_t[u_pageColourSize * u_bufferDepth];
        u_newImage = (uint8_t *) _newFrameBuffer;
    }

#endif // ESP32 BOARD_HAS_PSRAM

    memset(u_newImage, 0x00, u_pageColourSize * u_bufferDepth);

    // Initialise the /CS pins
    pinMode(b_pin.panelCS, OUTPUT);
    digitalWrite(b_pin.panelCS, HIGH); // CS# = 1

    // New generic solution
    pinMode(b_pin.panelDC, OUTPUT);
    pinMode(b_pin.panelReset, OUTPUT);
    pinMode(b_pin.panelBusy, INPUT); // All Pins 0

    // Initialise Flash /CS as HIGH
    if (b_pin.flashCS != NOT_CONNECTED)
    {
        pinMode(b_pin.flashCS, OUTPUT);
        digitalWrite(b_pin.flashCS, HIGH);
    }

    // Initialise slave panel /CS as HIGH
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        pinMode(b_pin.panelCSS, OUTPUT);
        digitalWrite(b_pin.panelCSS, HIGH);
    }

    // Initialise slave Flash /CS as HIGH
    if (b_pin.flashCSS != NOT_CONNECTED)
    {
        pinMode(b_pin.flashCSS, OUTPUT);
        digitalWrite(b_pin.flashCSS, HIGH);
    }

    // Initialise SD-card /CS as HIGH
    if (b_pin.cardCS != NOT_CONNECTED)
    {
        pinMode(b_pin.cardCS, OUTPUT);
        digitalWrite(b_pin.cardCS, HIGH);
    }

    // Initialise SPI
    _settingScreen = {4000000, MSBFIRST, SPI_MODE0};

#if defined(ENERGIA)

    SPI.begin();
    SPI.setBitOrder(_settingScreen.bitOrder);
    SPI.setDataMode(_settingScreen.dataMode);
    SPI.setClockDivider(SPI_CLOCK_MAX / min(SPI_CLOCK_MAX, _settingScreen.clock));

#else

#if defined(ARDUINO_XIAO_ESP32C3)

    // Board Xiao ESP32-C3 crashes if pins are specified.
    SPI.begin(8, 9, 10); // SCK MISO MOSI

#elif defined(ARDUINO_NANO_ESP32)

    // Board Arduino Nano ESP32 arduino_nano_nora v2.0.11
    SPI.begin();

#elif defined(ARDUINO_ARCH_ESP32)

    // Board ESP32-Pico-DevKitM-2 crashes if pins are not specified.
    SPI.begin(14, 12, 13); // SCK MISO MOSI

#else

    SPI.begin();

#endif // ARDUINO_ARCH_ESP32

    SPI.beginTransaction(_settingScreen);

#endif // ENERGIA

    // Reset
    switch (u_codeSize)
    {
        case 0x56: // 5.65"
        case 0x58: // 5.81"
        case 0x74: // 7.40"

            b_reset(200, 20, 200, 50, 5); // medium
            break;

        case 0x96: // 9.69"
        case 0xB9: // 11.98"

            b_reset(200, 20, 200, 200, 5); // large
            break;

        default:

            b_reset(5, 5, 10, 5, 5); // small
            break;
    } // u_codeSize

    // Standard
    hV_Screen_Buffer::begin();

    setOrientation(0);
    if (f_fontMax() > 0)
    {
        f_selectFont(0);
    }
    f_fontSolid = false;

    _penSolid = false;
    u_invert = false;

    // Report
    Serial.println(formatString("= Screen %s %ix%i", WhoAmI().c_str(), screenSizeX(), screenSizeY()));
    Serial.println(formatString("= PDLS %s v%i.%i.%i", SCREEN_EPD_EXT3_VARIANT, SCREEN_EPD_EXT3_RELEASE / 100, (SCREEN_EPD_EXT3_RELEASE / 10) % 10, SCREEN_EPD_EXT3_RELEASE % 10));

    clear();
}

String Screen_EPD_EXT3::WhoAmI()
{
    char work[64] = {0};
    u_WhoAmI(work);

    return formatString("iTC %i.%02i\"%s", _screenDiagonal / 100, _screenDiagonal % 100, work);
}

uint8_t Screen_EPD_EXT3::flushMode(uint8_t updateMode)
{
    updateMode = checkTemperatureMode(updateMode);

    switch (updateMode)
    {
        case UPDATE_FAST:
        case UPDATE_GLOBAL:

            _flushGlobal();
            break;

        default:

            Serial.println("* PDLS - UPDATE_NONE invoked");
            break;
    }

    return updateMode;
}

void Screen_EPD_EXT3::flush()
{
    flushMode(UPDATE_GLOBAL);
}

void Screen_EPD_EXT3::_flushGlobal()
{
    uint8_t * blackBuffer = u_newImage;
    uint8_t * redBuffer = u_newImage + u_pageColourSize;

    // Three groups:
    // + small: up to 4.37 included
    // + medium: 5.65, 5.81 and 7.4
    // + large: 9.69 and 11,98
    // switch..case does not allow variable declarations
    //
    if ((u_codeSize == 0x56) or (u_codeSize == 0x58) or (u_codeSize == 0x74))
    {
        b_reset(200, 20, 200, 50, 5);

        // Send image data
        if (u_codeSize == 0x56)
        {
            uint8_t data1_565[] = {0x00, 0x37, 0x00, 0x00, 0x57, 0x02}; // DUW
            b_sendIndexData(0x13, data1_565, 6); // DUW
            uint8_t data2_565[] = {0x00, 0x37, 0x00, 0x97}; // DRFW
            b_sendIndexData(0x90, data2_565, 4); // DRFW
            uint8_t data3_565[] = {0x37, 0x00, 0x14}; // RAM_RW
            b_sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        else if (u_codeSize == 0x58)
        {
            uint8_t data1_565[] = {0x00, 0x1f, 0x50, 0x00, 0x1f, 0x03}; // DUW
            b_sendIndexData(0x13, data1_565, 6); // DUW
            uint8_t data2_565[] = {0x00, 0x1f, 0x00, 0xc9}; // DRFW
            b_sendIndexData(0x90, data2_565, 4); // DRFW
            uint8_t data3_565[] = {0x1f, 0x50, 0x14}; // RAM_RW
            b_sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        else if (u_codeSize == 0x74)
        {
            uint8_t data1_565[] = {0x00, 0x3b, 0x00, 0x00, 0x1f, 0x03}; // DUW
            b_sendIndexData(0x13, data1_565, 6); // DUW
            uint8_t data2_565[] = {0x00, 0x3b, 0x00, 0xc9}; // DRFW
            b_sendIndexData(0x90, data2_565, 4); // DRFW
            uint8_t data3_565[] = {0x3b, 0x00, 0x14}; // RAM_RW
            b_sendIndexData(0x12, data3_565, 3); // RAM_RW
        }

        if (u_codeType == 0x0B)
        {
            // y1 = 7 - (y1 % 8);
            uint8_t dtcl = 0x08; // 0=IST, 8=IST
            b_sendIndexData(0x01, &dtcl, 1); // DCTL 0x10 of MTP
        }

        b_sendIndexData(0x10, blackBuffer, u_frameSize); // First frame

        if (u_codeSize == 0x56)
        {
            uint8_t data3_565[] = {0x37, 0x00, 0x14}; // RAM_RW
            b_sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        else if (u_codeSize == 0x58)
        {
            uint8_t data3_565[] = {0x1f, 0x50, 0x14}; // RAM_RW
            b_sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        else if (u_codeSize == 0x74)
        {
            uint8_t data3_565[] = {0x3b, 0x00, 0x14}; // RAM_RW
            b_sendIndexData(0x12, data3_565, 3); // RAM_RW
        }
        b_sendIndexData(0x11, redBuffer, u_frameSize); // Second frame

        // Initial COG
        uint8_t data4_565[] = {0x7d};
        b_sendIndexData(0x05, data4_565, 1);
        delay_ms(200);
        uint8_t data5_565[] = {0x00};
        b_sendIndexData(0x05, data5_565, 1);
        delay_ms(10);
        uint8_t data6_565[] = {0x3f};
        b_sendIndexData(0xc2, data6_565, 1);
        delay_ms(1);
        uint8_t data7_565[] = {0x00};
        b_sendIndexData(0xd8, data7_565, 1); // MS_SYNC mtp_0x1d
        uint8_t data8_565[] = {0x00};
        b_sendIndexData(0xd6, data8_565, 1); // BVSS mtp_0x1e
        uint8_t data9_565[] = {0x10};
        b_sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        b_sendIndexData(0xa7, data5_565, 1);
        delay_ms(100);
        // uint8_t data10_565[] = {0x00, 0x02 };
        if (u_codeSize == 0x56)
        {
            uint8_t data10_565[] = {0x00, 0x02}; // OSC
            b_sendIndexData(0x03, data10_565, 2); // OSC mtp_0x12
        }
        else if (u_codeSize == 0x58)
        {
            uint8_t data10_565[] = {0x00, 0x01}; // OSC
            b_sendIndexData(0x03, data10_565, 2); // OSC mtp_0x12
        }
        else if (u_codeSize == 0x74)
        {
            uint8_t data10_565[] = {0x00, 0x01}; // OSC
            b_sendIndexData(0x03, data10_565, 2); // OSC mtp_0x12
        }
        b_sendIndexData(0x44, data5_565, 1);
        uint8_t data11_565[] = {0x80};
        b_sendIndexData(0x45, data11_565, 1);
        b_sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        b_sendIndexData(0xa7, data7_565, 1);
        delay_ms(100);
        uint8_t data12_565[] = {0x06};
        b_sendIndexData(0x44, data12_565, 1);
        uint8_t data13_565[] = {0x82};
        data13_565[0] = u_temperature * 2 + 0x50; // u_temperature
        b_sendIndexData(0x45, data13_565, 1); // Temperature 0x82@25C
        b_sendIndexData(0xa7, data9_565, 1);
        delay_ms(100);
        b_sendIndexData(0xa7, data7_565, 1);
        delay_ms(100);
        uint8_t data14_565[] = {0x25};
        b_sendIndexData(0x60, data14_565, 1); // TCON mtp_0x0b
        // uint8_t data15_565[] = {0x01 };
        if (u_codeSize == 0x56)
        {
            uint8_t data15_565[] = {0x01}; // STV_DIR
            b_sendIndexData(0x61, data15_565, 1); // STV_DIR mtp_0x1c
        }
        else if (u_codeSize == 0x58)
        {
            uint8_t data15_565[] = {0x00}; // STV_DIR
            b_sendIndexData(0x61, data15_565, 1); // STV_DIR mtp_0x1c
        }
        else if (u_codeSize == 0x74)
        {
            uint8_t data15_565[] = {0x00}; // STV_DIR
            b_sendIndexData(0x61, data15_565, 1); // STV_DIR mtp_0x1c
        }
        uint8_t data16_565[] = {0x00};
        b_sendIndexData(0x01, data16_565, 1); // DCTL mtp_0x10
        uint8_t data17_565[] = {0x00};
        b_sendIndexData(0x02, data17_565, 1); // VCOM mtp_0x11

        // DC-DC soft-start
        uint8_t index51_565[] = {0x50, 0x01, 0x0a, 0x01};
        b_sendIndexData(0x51, &index51_565[0], 2);
        uint8_t index09_565[] = {0x1f, 0x9f, 0x7f, 0xff};

        for (int value = 1; value <= 4; value++)
        {
            b_sendIndexData(0x09, &index09_565[0], 1);
            index51_565[1] = value;
            b_sendIndexData(0x51, &index51_565[0], 2);
            b_sendIndexData(0x09, &index09_565[1], 1);
            delay_ms(2);
        }
        for (int value = 1; value <= 10; value++)
        {
            b_sendIndexData(0x09, &index09_565[0], 1);
            index51_565[3] = value;
            b_sendIndexData(0x51, &index51_565[2], 2);
            b_sendIndexData(0x09, &index09_565[1], 1);
            delay_ms(2);
        }
        for (int value = 3; value <= 10; value++)
        {
            b_sendIndexData(0x09, &index09_565[2], 1);
            index51_565[3] = value;
            b_sendIndexData(0x51, &index51_565[2], 2);
            b_sendIndexData(0x09, &index09_565[3], 1);
            delay_ms(2);
        }
        for (int value = 9; value >= 2; value--)
        {
            b_sendIndexData(0x09, &index09_565[2], 1);
            index51_565[2] = value;
            b_sendIndexData(0x51, &index51_565[2], 2);
            b_sendIndexData(0x09, &index09_565[3], 1);
            delay_ms(2);
        }
        b_sendIndexData(0x09, &index09_565[3], 1);
        delay_ms(10);

        // Display Refresh Start
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        }
        uint8_t data18_565[] = {0x3c};
        b_sendIndexData(0x15, data18_565, 1); //Display Refresh
        delay_ms(5);

        // DC-DC off
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        }
        uint8_t data19_565[] = {0x7f};
        b_sendIndexData(0x09, data19_565, 1);
        uint8_t data20_565[] = {0x7d};
        b_sendIndexData(0x05, data20_565, 1);
        b_sendIndexData(0x09, data5_565, 1);
        delay_ms(200);

        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        }
        digitalWrite(b_pin.panelDC, LOW);
        digitalWrite(b_pin.panelCS, LOW);
        digitalWrite(b_pin.panelReset, LOW);
        // digitalWrite(PNLON_PIN, LOW); // PANEL_OFF# = 0
    }
    else if ((u_codeSize == 0x96) or (u_codeSize == 0xB9))
    {
        b_reset(200, 20, 200, 200, 5);

        // Send image data
        if (u_codeSize == 0x96)
        {
            uint8_t data1_970[] = {0x00, 0x3b, 0x00, 0x00, 0x9f, 0x02}; // DUW
            b_sendIndexDataBoth(0x13, data1_970, 6); // DUW for Both Master and Slave
            uint8_t data2_970[] = {0x00, 0x3b, 0x00, 0xa9}; // DRFW
            b_sendIndexDataBoth(0x90, data2_970, 4); // DRFW for Both Master and Slave
        }
        else if (u_codeSize == 0xB9)
        {
            uint8_t data1_970[] = {0x00, 0x3b, 0x00, 0x00, 0x1f, 0x03}; // DUW
            b_sendIndexDataBoth(0x13, data1_970, 6); // DUW for Both Master and Slave
            uint8_t data2_970[] = {0x00, 0x3b, 0x00, 0xc9}; // DRFW
            b_sendIndexDataBoth(0x90, data2_970, 4); // DRFW for Both Master and Slave
        }

        uint8_t data3_970[] = {0x3b, 0x00, 0x14};

        if (u_codeType == 0x0B)
        {
            uint8_t dtcl = 0x08; // 0=IST, 8=IST
            b_sendIndexDataBoth(0x01, &dtcl, 1); // DCTL 0x10 of MTP
        }

        // Master
        b_sendIndexDataMaster(0x12, data3_970, 3); // RAM_RW

        b_sendIndexDataMaster(0x10, blackBuffer, u_frameSize); // First frame

        b_sendIndexDataMaster(0x12, data3_970, 3); // RAM_RW

        b_sendIndexDataMaster(0x11, redBuffer, u_frameSize); // Second frame

        // Slave
        b_sendIndexDataSlave(0x12, data3_970, 3); // RAM_RW
        b_sendIndexDataSlave(0x10, blackBuffer + u_frameSize, u_frameSize); // First frame

        b_sendIndexDataSlave(0x12, data3_970, 3); // RAM_RW
        b_sendIndexDataSlave(0x11, redBuffer + u_frameSize, u_frameSize); // Second frame

        // Initial COG
        uint8_t data4_970[] = {0x7d};
        b_sendIndexDataBoth(0x05, data4_970, 1);
        delay_ms(200);
        uint8_t data5_970[] = {0x00};
        b_sendIndexDataBoth(0x05, data5_970, 1);
        delay_ms(10);
        uint8_t data6_970[] = {0x3f};
        b_sendIndexDataBoth(0xc2, data6_970, 1);
        delay_ms(1);
        uint8_t data7_970[] = {0x80};
        b_sendIndexDataBoth(0xd8, data7_970, 1); // MS_SYNC
        uint8_t data8_970[] = {0x00};
        b_sendIndexDataBoth(0xd6, data8_970, 1); // BVSS
        uint8_t data9_970[] = {0x10};
        b_sendIndexDataBoth(0xa7, data9_970, 1);
        delay_ms(100);
        b_sendIndexDataBoth(0xa7, data5_970, 1);
        delay_ms(100);

        // --- 9.69 and 11.9 specific
        if (u_codeSize == 0x96)
        {
            uint8_t data10_970[] = {0x00, 0x11}; // OSC
            b_sendIndexDataBoth(0x03, data10_970, 2); // OSC
        }
        else if (u_codeSize == 0xB9)
        {
            uint8_t data10_970[] = {0x00, 0x12}; // OSC
            b_sendIndexDataBoth(0x03, data10_970, 2); // OSC
        }

        b_sendIndexDataMaster(0x44, data5_970, 1); // Master
        uint8_t data11_970[] = {0x80};
        b_sendIndexDataMaster(0x45, data11_970, 1); // Master
        b_sendIndexDataMaster(0xa7, data9_970, 1); // Master
        delay_ms(100);
        b_sendIndexDataMaster(0xa7, data5_970, 1); // Master
        delay_ms(100);
        uint8_t data12_970[] = {0x06};
        b_sendIndexDataMaster(0x44, data12_970, 1); // Master
        uint8_t data13_970[] = {0x82};
        // uint8_t data13_970[] = {getTemperature(0x50, 0x82) };
        data13_970[0] = u_temperature * 2 + 0x50; // u_temperature
        b_sendIndexDataMaster(0x45, data13_970, 1); // Temperature 0x82@25C   0°C = 0x50, 25°C = 0x82
        b_sendIndexDataMaster(0xa7, data9_970, 1); // Master
        delay_ms(100);
        b_sendIndexDataMaster(0xa7, data5_970, 1); // Master
        delay_ms(100);

        b_sendIndexDataSlave(0x44, data5_970, 1); // Slave
        b_sendIndexDataSlave(0x45, data11_970, 1); // Slave
        b_sendIndexDataSlave(0xa7, data9_970, 1); // Slave
        delay_ms(100);
        b_sendIndexDataSlave(0xa7, data5_970, 1); // Slave
        delay_ms(100);
        b_sendIndexDataSlave(0x44, data12_970, 1); // Slave
        b_sendIndexDataSlave(0x45, data13_970, 1); // Temperature 0x82@25C   0°C = 0x50, 25°C = 0x82
        b_sendIndexDataSlave(0xa7, data9_970, 1); // Slave
        delay_ms(100);
        b_sendIndexDataSlave(0xa7, data5_970, 1); // Master
        delay_ms(100);

        uint8_t data14_970[] = {0x25};
        b_sendIndexData(0x60, data14_970, 1); // TCON
        uint8_t data15_970[] = {0x01};
        b_sendIndexDataMaster(0x61, data15_970, 1); // STV_DIR for Master
        uint8_t data16_970[] = {0x00};
        b_sendIndexDataBoth(0x01, data16_970, 1); // DCTL
        uint8_t data17_970[] = {0x00};
        b_sendIndexDataBoth(0x02, data17_970, 1); // VCOM

        // DC-DC soft-start
        uint8_t index51_970[] = {0x50, 0x01, 0x0a, 0x01};
        b_sendIndexDataBoth(0x51, &index51_970[0], 2);
        uint8_t index09_970[] = {0x1f, 0x9f, 0x7f, 0xff};

        for (int value = 1; value <= 4; value++)
        {
            b_sendIndexDataBoth(0x09, &index09_970[0], 1);
            index51_970[1] = value;
            b_sendIndexDataBoth(0x51, &index51_970[0], 2);
            b_sendIndexDataBoth(0x09, &index09_970[1], 1);
            delay_ms(2);
        }
        for (int value = 1; value <= 10; value++)
        {
            b_sendIndexDataBoth(0x09, &index09_970[0], 1);
            index51_970[3] = value;
            b_sendIndexDataBoth(0x51, &index51_970[2], 2);
            b_sendIndexDataBoth(0x09, &index09_970[1], 1);
            delay_ms(2);
        }
        for (int value = 3; value <= 10; value++)
        {
            b_sendIndexDataBoth(0x09, &index09_970[2], 1);
            index51_970[3] = value;
            b_sendIndexDataBoth(0x51, &index51_970[2], 2);
            b_sendIndexDataBoth(0x09, &index09_970[3], 1);
            delay_ms(2);
        }
        for (int value = 9; value >= 2; value--)
        {
            b_sendIndexDataBoth(0x09, &index09_970[2], 1);
            index51_970[2] = value;
            b_sendIndexDataBoth(0x51, &index51_970[2], 2);
            b_sendIndexDataBoth(0x09, &index09_970[3], 1);
            delay_ms(2);
        }
        b_sendIndexDataBoth(0x09, &index09_970[3], 1);
        delay_ms(10);

        // Display Refresh Start
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        }
        uint8_t data18_970[] = {0x3c};
        b_sendIndexDataBoth(0x15, data18_970, 1); // Display Refresh
        delay_ms(5);

        // DC/DC off
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        }
        uint8_t data19_970[] = {0x7f};
        b_sendIndexDataBoth(0x09, data19_970, 1);
        uint8_t data20_970[] = {0x7d};
        b_sendIndexDataBoth(0x05, data20_970, 1);
        b_sendIndexDataBoth(0x09, data5_970, 1);
        delay_ms(200);
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        }
        digitalWrite(b_pin.panelDC, LOW);
        digitalWrite(b_pin.panelCS, LOW);

        if (b_pin.panelCSS != NOT_CONNECTED)
        {
            digitalWrite(b_pin.panelCSS, LOW);
        }

        digitalWrite(b_pin.panelReset, LOW);
        // digitalWrite(PNLON_PIN, LOW); // PANEL_OFF# = 0

        if (b_pin.panelCSS != NOT_CONNECTED)
        {
            digitalWrite(b_pin.panelCSS, HIGH); // CSS# = 1
        }
    }
    else // small, including 420 and 437
    {
        b_reset(5, 5, 10, 5, 5);

        uint8_t data9[] = {0x0e};
        b_sendIndexData(0x00, data9, 1); // Soft-reset
        delay_ms(5);

        uint8_t data7[] = {0x19};
        data7[0] = u_temperature; // u_temperature
        b_sendIndexData(0xe5, data7, 1); // Input Temperature 0°C = 0x00, 22°C = 0x16, 25°C = 0x19
        uint8_t data6[] = {0x02};
        b_sendIndexData(0xe0, data6, 1); // Active Temperature


        uint8_t index00_work[2] = {0xcf, 0x8d}; // PSR, all except 4.2"
        if (u_codeSize == 0x42)
        {
            index00_work[0] = 0x0f;
            index00_work[1] = 0x89;
        }

   if (u_codeSize == 0x29)
    {
        b_sendCommandData8(0x4d, 0x55);
        b_sendCommandData8(0xe9, 0x02);
    }
    else
    {
        b_sendIndexData(0x00, index00_work, 2); // PSR
    }

        // Send image data
        b_sendIndexData(0x10, blackBuffer, u_frameSize); // First frame
        b_sendIndexData(0x13, redBuffer, u_frameSize); // Second frame

        delay_ms(50);
        uint8_t data8[] = {0x00};
        b_sendIndexData(0x04, data8, 1); // Power on
        delay_ms(5);
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        };

        while (digitalRead(b_pin.panelBusy) != HIGH);
        b_sendIndexData(0x12, data8, 1); // Display Refresh
        delay_ms(5);
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        };

        b_sendIndexData(0x02, data8, 1); // Turn off DC/DC
        delay_ms(5);
        while (digitalRead(b_pin.panelBusy) != HIGH)
        {
            delay(100);
        };
        digitalWrite(b_pin.panelDC, LOW);
        digitalWrite(b_pin.panelCS, LOW);

        digitalWrite(b_pin.panelReset, LOW);
        // digitalWrite(PNLON_PIN, LOW);
    }
    digitalWrite(b_pin.panelCS, HIGH); // CS# = 1
}

void Screen_EPD_EXT3::clear(uint16_t colour)
{
    if (colour == myColours.red)
    {
        // physical red 01
        memset(u_newImage, 0x00, u_pageColourSize);
        memset(u_newImage + u_pageColourSize, 0xff, u_pageColourSize);
    }
    else if (colour == myColours.grey)
    {
        for (uint16_t i = 0; i < u_bufferSizeV; i++)
        {
            uint16_t pattern = (i % 2) ? 0b10101010 : 0b01010101;
            for (uint16_t j = 0; j < u_bufferSizeH; j++)
            {
                u_newImage[i * u_bufferSizeH + j] = pattern;
            }
        }
        memset(u_newImage + u_pageColourSize, 0x00, u_pageColourSize);
    }
    else if (colour == myColours.darkRed)
    {
        // red = 0-1, black = 1-0, white 0-0
        for (uint16_t i = 0; i < u_bufferSizeV; i++)
        {
            uint16_t pattern1 = (i % 2) ? 0b10101010 : 0b01010101; // black
            uint16_t pattern2 = (i % 2) ? 0b01010101 : 0b10101010; // red
            for (uint16_t j = 0; j < u_bufferSizeH; j++)
            {
                u_newImage[i * u_bufferSizeH + j] = pattern1;
                u_newImage[i * u_bufferSizeH + j + u_pageColourSize] = pattern2;
            }
        }
    }
    else if (colour == myColours.lightRed)
    {
        // red = 0-1, black = 1-0, white 0-0
        for (uint16_t i = 0; i < u_bufferSizeV; i++)
        {
            uint16_t pattern1 = (i % 2) ? 0b00000000 : 0b00000000; // white
            uint16_t pattern2 = (i % 2) ? 0b01010101 : 0b10101010; // red
            for (uint16_t j = 0; j < u_bufferSizeH; j++)
            {
                u_newImage[i * u_bufferSizeH + j] = pattern1;
                u_newImage[i * u_bufferSizeH + j + u_pageColourSize] = pattern2;
            }
        }
    }
    else if ((colour == myColours.white) xor u_invert)
    {
        // physical black 00
        memset(u_newImage, 0x00, u_pageColourSize);
        memset(u_newImage + u_pageColourSize, 0x00, u_pageColourSize);
    }
    else
    {
        // physical white 10
        memset(u_newImage, 0xff, u_pageColourSize);
        memset(u_newImage + u_pageColourSize, 0x00, u_pageColourSize);
    }
}

void Screen_EPD_EXT3::_setPoint(uint16_t x1, uint16_t y1, uint16_t colour)
{
    // Orient and check coordinates are within screen
    // _orientCoordinates() returns false = success, true = error
    if (_orientCoordinates(x1, y1) == RESULT_ERROR)
    {
        return;
    }

    // Convert combined colours into basic colours
    bool flagOdd = ((x1 + y1) % 2 == 0);

    if (colour == myColours.darkRed)
    {
        if (flagOdd)
        {
            colour = myColours.red; // red
        }
        else
        {
            colour = u_invert ? myColours.white : myColours.black; // white
        }
    }
    else if (colour == myColours.lightRed)
    {
        if (flagOdd)
        {
            colour = myColours.red; // red
        }
        else
        {
            colour = u_invert ? myColours.black : myColours.white; // black
        }
    }
    else if (colour == myColours.grey)
    {
        if (flagOdd)
        {
            colour = myColours.black; // black
        }
        else
        {
            colour = myColours.white; // white
        }
    }

    // Coordinates
    uint32_t z1 = _getZ(x1, y1);
    uint16_t b1 = _getB(x1, y1);

    // Basic colours
    if (colour == myColours.red)
    {
        // physical red 01
        bitClear(u_newImage[z1], b1);
        bitSet(u_newImage[u_pageColourSize + z1], b1);
    }
    else if ((colour == myColours.white) xor u_invert)
    {
        // physical black 00
        bitClear(u_newImage[z1], b1);
        bitClear(u_newImage[u_pageColourSize + z1], b1);
    }
    else if ((colour == myColours.black) xor u_invert)
    {
        // physical white 10
        bitSet(u_newImage[z1], b1);
        bitClear(u_newImage[u_pageColourSize + z1], b1);
    }
}

void Screen_EPD_EXT3::_setOrientation(uint8_t orientation)
{
    _orientation = orientation % 4;
}

bool Screen_EPD_EXT3::_orientCoordinates(uint16_t & x, uint16_t & y)
{
    bool _flagResult = RESULT_ERROR; // false = success, true = error
    switch (_orientation)
    {
        case 3: // checked, previously 1

            if ((x < _screenSizeV) and (y < _screenSizeH))
            {
                x = _screenSizeV - 1 - x;
                _flagResult = RESULT_SUCCESS;
            }
            break;

        case 2: // checked

            if ((x < _screenSizeH) and (y < _screenSizeV))
            {
                x = _screenSizeH - 1 - x;
                y = _screenSizeV - 1 - y;
                swap(x, y);
                _flagResult = RESULT_SUCCESS;
            }
            break;

        case 1: // checked, previously 3

            if ((x < _screenSizeV) and (y < _screenSizeH))
            {
                y = _screenSizeH - 1 - y;
                _flagResult = RESULT_SUCCESS;
            }
            break;

        default: // checked

            if ((x < _screenSizeH) and (y < _screenSizeV))
            {
                swap(x, y);
                _flagResult = RESULT_SUCCESS;
            }
            break;
    }

    return _flagResult;
}

uint16_t Screen_EPD_EXT3::_getPoint(uint16_t x1, uint16_t y1)
{
    return 0x0000;
}

uint32_t Screen_EPD_EXT3::_getZ(uint16_t x1, uint16_t y1)
{
    uint32_t z1 = 0;
    // According to 11.98 inch Spectra Application Note
    // at http:// www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=245146
    if ((u_codeSize == 0x96) or (u_codeSize == 0xB9))
    {
        if (y1 >= (_screenSizeH >> 1))
        {
            y1 -= (_screenSizeH >> 1); // rebase y1
            z1 += (u_pageColourSize >> 1); // buffer second half
        }
        z1 += (uint32_t)x1 * (u_bufferSizeH >> 1) + (y1 >> 3);
    }
    else
    {
        z1 = (uint32_t)x1 * u_bufferSizeH + (y1 >> 3);
    }
    return z1;
}

uint16_t Screen_EPD_EXT3::_getB(uint16_t x1, uint16_t y1)
{
    uint16_t b1 = 0;

    b1 = 7 - (y1 % 8);

    return b1;
}

void Screen_EPD_EXT3::regenerate()
{
    clear(myColours.black);
    flush();

    delay(100);

    clear(myColours.white);
    flush();
}
//
// === End of Class section
//

//
// === Touch section
//

//
// === End of Touch section
//

