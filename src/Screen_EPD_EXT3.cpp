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
// Copyright (c) Rei Vilo, 2010-2024
// Licence Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
// For exclusive use with Pervasive Displays screens
// Portions (c) Pervasive Displays, 2010-2024
//
// Release 508: Added support for 969_CS_0B and B98_CS_0B
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
// Release 800: Read OTP memory
// Release 801: Improved OTP implementation
// Release 802: Added references to application notes
// Release 802: Refactored CoG functions
// Release 803: Added types for string and frame-buffer
// Release 804: Improved power management
// Release 805: Improved stability
// Release 806: New library for Wide temperature only
//

// Library header
#include "Screen_EPD_EXT3.h"

//
// === COG section
//
/// @cond
/// @see
/// * ApplicationNote_Small_Size_Mono_v02_220606
/// * ApplicationNote_Small_Size_Spectra_v06_220606
/// * ApplicationNote_EPD343_Mono(E2343PS0Bx)_240320a.pdf
/// * ApplicationNote_EPD580_Mono(E2581CS0BX)_240130.pdf
/// * ApplicationNote_EPD580_Spectra_with_IST7136_210205.pdf
/// * ApplicationNote_EPD740_Mono_with_IST7136_210323.pdf
/// * ApplicationNote_EPD740_Spectra_with_IST7136_201123.pdf
/// * ApplicationNote_EPD970_Spectra_with_IST7136_201123.pdf
/// * ApplicationNote_EPD1200_Mono_with_G2.1_IST7136_211130.pdf
/// * ApplicationNote_EPD1200_Spectra_with_IST7136_shortFPC_210325.pdf
/// * ApplicationNote_EPD970_Spectra_with_G2.1_200903.pdf
/// * ApplicationNote_EPD565_Spectra_with_G2.1_210325_E2565JS08x_.pdf
/// * ApplicationNote_EPD580_Mono_with_G2.1_210325_E2581CS08x_.pdf
/// * ApplicationNote_EPD740_Mono_with_G2.1_210325_E2741CS08x_.pdf
/// * ApplicationNote_EPD740_Spectra_with_G2.1_171024.pdf
/// * ApplicationNote_EPD740_Spectra_with_G2.1_210325_E2741FS08x E2741GS08x_.pdf
/// * ApplicationNote_EPD970_Mono_with_G2.1_210325_E2969CS08x_.pdf
/// * ApplicationNote_EPD1200_Mono_with_G2.1_210325_E2B98CS08x_.pdf
/// * ApplicationNote_EPD1200_Spectra_with_G2.1_171106.pdf

//
// --- Large screens with C or J film
//
void Screen_EPD_EXT3::COG_LargeCJ_reset()
{
    b_reset(200, 20, 200, 200, 5); // large
}

void Screen_EPD_EXT3::COG_LargeCJ_getDataOTP()
{
    // Application note § none
    // Application note § 1.5 Read MTP data
    // Application note § 1.6 Read MTP data
    uint16_t _readBytes = 0;
    uint8_t ui8 = 0; // dummy
    u_flagOTP = false;

    COG_LargeCJ_reset();
    if (b_family == FAMILY_LARGE)
    {
        digitalWrite(b_pin.panelCSS, HIGH);    // Unselect slave panel
    }

    // Read OTP
    switch (u_codeDriver)
    {
        case DRIVER_B:

            _readBytes = 128;

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xb9);
            delay(5);
            break;

        case DRIVER_8:

            _readBytes = 80;

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa1);
            digitalWrite(b_pin.panelDC, HIGH); // Data
            hV_HAL_SPI3_write(0x00);
            digitalWrite(b_pin.panelCS, HIGH); // Unselect

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa7);
            digitalWrite(b_pin.panelDC, HIGH); // Data
            hV_HAL_SPI3_write(0x80);
            digitalWrite(b_pin.panelCS, HIGH); // Unselect

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa3);
            digitalWrite(b_pin.panelDC, HIGH); // Data
            hV_HAL_SPI3_write(0x00);
            hV_HAL_SPI3_write(0x40);
            digitalWrite(b_pin.panelCS, HIGH); // Unselect

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa8);
            delay(5);
            break;

        default:

            mySerial.println();
            mySerial.println(formatString("hV * OTP failed for screen %i-%cS-0%c", u_codeSize, u_codeFilm, u_codeDriver));
            while (0x01);
            break;
    }

    digitalWrite(b_pin.panelDC, HIGH); // Data
    ui8 = hV_HAL_SPI3_read(); // Dummy
    // hV_HAL_log(LEVEL_DEBUG, "Dummy read 0x%02x", ui8);

    // Populate COG_data
    for (uint16_t index = 0; index < _readBytes; index += 1)
    {
        COG_data[index] = hV_HAL_SPI3_read(); // Read OTP
    }

    // End of OTP reading
    digitalWrite(b_pin.panelCS, HIGH); // Unselect

    // Check
    if (u_codeDriver == DRIVER_B)
    {
        // No check for DRIVER_B
    }
    else if (u_codeDriver == DRIVER_8)
    {
        if (COG_data[0] == 0xa5)
        {
            mySerial.println(formatString("hV . OTP check passed - First 0x%02x as expected", COG_data[0]));
        }
        else
        {
            mySerial.println(formatString("hV * OTP check failed - First 0x%02x, expected 0x%02x", COG_data[0], 0xa5));
            while (0x01);
        }
    }

    u_flagOTP = true;
}

void Screen_EPD_EXT3::COG_LargeCJ_initial()
{
    // Application note § 3.1 Initial flow chart

    COG_LargeCJ_reset();

    if (u_codeDriver == DRIVER_B)
    {
        b_sendCommandDataSelect8(0x01, COG_data[0x10], PANEL_CS_BOTH); // DCTL
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // No DCTL here
    }
}

void Screen_EPD_EXT3::COG_LargeCJ_sendImageData()
{
    // 9.69 and 11.98 combine two half-screens, hence two frames with adjusted (u_pageColourSize >> 1) size
    uint32_t u_subPageColourSize = (u_pageColourSize >> 1);

    FRAMEBUFFER_TYPE blackBuffer = s_newImage;
    FRAMEBUFFER_TYPE redBuffer = s_newImage + u_pageColourSize;

    // Application note § 4. Input image to the EPD
    // Application note § 3.2 Send image to the EPD
    if (u_codeDriver == DRIVER_B)
    {
        // Send image data
        b_sendIndexDataSelect(0x13, &COG_data[0x15], 6, PANEL_CS_BOTH); // DUW
        b_sendIndexDataSelect(0x90, &COG_data[0x0c], 4, PANEL_CS_BOTH); // DRFW

        // Master
        b_sendIndexDataSelect(0x12, &COG_data[0x12], 3, PANEL_CS_MASTER); // RAM_RW
        b_sendIndexDataSelect(0x10, blackBuffer, u_subPageColourSize, PANEL_CS_MASTER); // First frame

        b_sendIndexDataSelect(0x12, &COG_data[0x12], 3, PANEL_CS_MASTER); // RAM_RW

        switch (u_codeFilm)
        {
            case FILM_C:

                b_sendIndexFixedSelect(0x11, 0x00, u_subPageColourSize, PANEL_CS_MASTER); // Second frame = dummy
                break;

            default:

                b_sendIndexDataSelect(0x11, redBuffer, u_subPageColourSize, PANEL_CS_MASTER); // Second frame
                break;
        }

        // Slave
        b_sendIndexDataSelect(0x12, &COG_data[0x12], 3, PANEL_CS_SLAVE); // RAM_RW
        b_sendIndexDataSelect(0x10, blackBuffer + u_subPageColourSize, u_subPageColourSize, PANEL_CS_SLAVE); // First frame

        b_sendIndexDataSelect(0x12, &COG_data[0x12], 3, PANEL_CS_SLAVE); // RAM_RW

        switch (u_codeFilm)
        {
            case FILM_C:

                b_sendIndexFixedSelect(0x11, 0x00, u_subPageColourSize, PANEL_CS_SLAVE); // Second frame = dummy
                break;

            default:

                b_sendIndexDataSelect(0x11, redBuffer + u_subPageColourSize, u_subPageColourSize, PANEL_CS_SLAVE); // Second frame
                break;
        }
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // Send image data
        b_sendIndexDataSelect(0x13, &COG_data[0x16], 6, PANEL_CS_BOTH); // DUW
        b_sendIndexDataSelect(0x90, &COG_data[0x0c], 4, PANEL_CS_BOTH); // DRFW

        // Master
        b_sendIndexDataSelect(0x12, &COG_data[0x13], 3, PANEL_CS_MASTER); // RAM_RW
        b_sendIndexDataSelect(0x10, blackBuffer, u_subPageColourSize, PANEL_CS_MASTER); // First frame

        b_sendIndexDataSelect(0x12, &COG_data[0x13], 3, PANEL_CS_MASTER); // RAM_RW

        switch (u_codeFilm)
        {
            case FILM_C:

                b_sendIndexFixedSelect(0x11, 0x00, u_subPageColourSize, PANEL_CS_MASTER); // Second frame = dummy
                break;

            default:

                b_sendIndexDataSelect(0x11, redBuffer, u_subPageColourSize, PANEL_CS_MASTER); // Second frame
                break;
        }

        // Slave
        b_sendIndexDataSelect(0x12, &COG_data[0x13], 3, PANEL_CS_SLAVE); // RAM_RW
        b_sendIndexDataSelect(0x10, blackBuffer + u_subPageColourSize, u_subPageColourSize, PANEL_CS_SLAVE); // First frame

        b_sendIndexDataSelect(0x12, &COG_data[0x13], 3, PANEL_CS_SLAVE); // RAM_RW

        switch (u_codeFilm)
        {
            case FILM_C:

                b_sendIndexFixedSelect(0x11, 0x00, u_subPageColourSize, PANEL_CS_SLAVE); // Second frame = dummy
                break;

            default:

                b_sendIndexDataSelect(0x11, redBuffer + u_subPageColourSize, u_subPageColourSize, PANEL_CS_SLAVE); // Second frame
                break;
        }
    }
}

void Screen_EPD_EXT3::COG_LargeCJ_update()
{
    // Application note § 3.1 Initial flow chart
    // Application note § 3.3 DC/DC soft-start
    // Application note § 4. Send updating command
    if (u_codeDriver == DRIVER_B)
    {
        // Initial COG
        b_sendCommandDataSelect8(0x05, 0x7d, PANEL_CS_BOTH);
        delay(200);
        b_sendCommandDataSelect8(0x05, 0x00, PANEL_CS_BOTH);
        delay(10);

        b_sendCommandDataSelect8(0xd8, COG_data[0x1c], PANEL_CS_BOTH); // MS_SYNC
        b_sendCommandDataSelect8(0xd6, COG_data[0x1d], PANEL_CS_BOTH); // BVSS

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_BOTH);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_BOTH);
        delay(100);

        // Master
        b_sendCommandDataSelect8(0x44, 0x00, PANEL_CS_MASTER);
        b_sendCommandDataSelect8(0x45, 0x80, PANEL_CS_MASTER);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_MASTER);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_MASTER);
        delay(100);

        b_sendCommandDataSelect8(0x44, 0x06, PANEL_CS_MASTER);
        uint8_t indexTemperature = u_temperature * 2 + 0x50; // Temperature 0x82@25C
        b_sendCommandDataSelect8(0x45, indexTemperature, PANEL_CS_MASTER);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_MASTER);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_MASTER);
        delay(100);

        // SLAVE
        b_sendCommandDataSelect8(0x44, 0x00, PANEL_CS_SLAVE);
        b_sendCommandDataSelect8(0x45, 0x80, PANEL_CS_SLAVE);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_SLAVE);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_SLAVE);
        delay(100);

        b_sendCommandDataSelect8(0x44, 0x06, PANEL_CS_SLAVE);
        b_sendCommandDataSelect8(0x45, indexTemperature, PANEL_CS_SLAVE);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_SLAVE);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_SLAVE);
        delay(100);

        // After
        b_sendCommandDataSelect8(0x60, COG_data[0x0b], PANEL_CS_BOTH); // TCON
        b_sendCommandDataSelect8(0x61, COG_data[0x1b], PANEL_CS_MASTER); // STV_DIR Master only
        // No DCTL here
        b_sendCommandDataSelect8(0x02, COG_data[0x11], PANEL_CS_BOTH); // VCOM
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // Initial COG
        b_sendCommandDataSelect8(0x05, 0x7d, PANEL_CS_BOTH);
        delay(200);
        b_sendCommandDataSelect8(0x05, 0x00, PANEL_CS_BOTH);
        delay(10);

        b_sendCommandDataSelect8(0xc2, 0x3f, PANEL_CS_BOTH);
        delay(1);

        b_sendCommandDataSelect8(0xd8, COG_data[0x1d], PANEL_CS_BOTH); // MS_SYNC
        b_sendCommandDataSelect8(0xd6, COG_data[0x1e], PANEL_CS_BOTH); // BVSS

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_BOTH);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_BOTH);
        delay(100);

        uint8_t data03[2] = {0x00, COG_data[0x12]}; // OSC
        b_sendIndexDataSelect(0x03, data03, 2, PANEL_CS_BOTH); // OSC mtp_0x12

        // Master
        b_sendCommandDataSelect8(0x44, 0x00, PANEL_CS_MASTER);
        b_sendCommandDataSelect8(0x45, 0x80, PANEL_CS_MASTER);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_MASTER);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_MASTER);
        delay(100);

        b_sendCommandDataSelect8(0x44, 0x06, PANEL_CS_MASTER);
        uint8_t indexTemperature = u_temperature * 2 + 0x50; // Temperature 0x82@25C
        b_sendCommandDataSelect8(0x45, indexTemperature, PANEL_CS_MASTER);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_MASTER);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_MASTER);
        delay(100);

        // Slave
        b_sendCommandDataSelect8(0x44, 0x00, PANEL_CS_SLAVE);
        b_sendCommandDataSelect8(0x45, 0x80, PANEL_CS_SLAVE);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_SLAVE);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_SLAVE);
        delay(100);

        b_sendCommandDataSelect8(0x44, 0x06, PANEL_CS_SLAVE);
        b_sendCommandDataSelect8(0x45, indexTemperature, PANEL_CS_SLAVE);

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_SLAVE);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_SLAVE);
        delay(100);

        // After
        b_sendCommandDataSelect8(0x60, COG_data[0x0b], PANEL_CS_BOTH); // TCON
        b_sendCommandDataSelect8(0x61, COG_data[0x1c], PANEL_CS_MASTER); // STV_DIR Master only
        b_sendCommandDataSelect8(0x01, COG_data[0x10], PANEL_CS_BOTH); // DCTL
        b_sendCommandDataSelect8(0x02, COG_data[0x11], PANEL_CS_BOTH); // VCOM
    }

    // DC/DC Soft-start
    // Application note § 3.3 DC/DC soft-start
    // DRIVER_B = 0x28, DRIVER_8 = 0x20
    uint8_t offsetFrame = (u_codeDriver == DRIVER_B) ? 0x28 : 0x20;

    // Filter for register 0x09
    uint8_t _filter09 = 0xff;

    switch (u_eScreen_EPD)
    {
        case eScreen_EPD_969_CS_08:
        case eScreen_EPD_B98_CS_08:

            _filter09 = 0xfb;
            break;

        default:

            _filter09 = 0xff;
            break;
    }

    for (uint8_t stage = 0; stage < 4; stage += 1)
    {
        uint8_t offset = offsetFrame + 0x08 * stage;
        uint8_t FORMAT = COG_data[offset] & 0x80;
        uint8_t REPEAT = COG_data[offset] & 0x7f;

        if (FORMAT > 0) // Format 1
        {
            uint8_t PHL_PHH[2];
            PHL_PHH[0] = COG_data[offset + 1]; // PHL_INI
            PHL_PHH[1] = COG_data[offset + 2]; // PHH_INI
            uint8_t PHL_VAR = COG_data[offset + 3];
            uint8_t PHH_VAR = COG_data[offset + 4];
            uint8_t BST_SW_a = COG_data[offset + 5] & _filter09;
            uint8_t BST_SW_b = COG_data[offset + 6] & _filter09;
            uint8_t DELAY_SCALE = COG_data[offset + 7] & 0x80;
            uint16_t DELAY_VALUE = COG_data[offset + 7] & 0x7f;

            for (uint8_t i = 0; i < REPEAT; i += 1)
            {
                b_sendCommandDataSelect8(0x09, BST_SW_a, PANEL_CS_BOTH);
                PHL_PHH[0] += PHL_VAR; // PHL
                PHL_PHH[1] += PHH_VAR; // PHH
                b_sendIndexDataSelect(0x51, PHL_PHH, 2, PANEL_CS_BOTH);
                b_sendCommandDataSelect8(0x09, BST_SW_b, PANEL_CS_BOTH);

                if (DELAY_SCALE > 0)
                {
                    delay(DELAY_VALUE); // ms
                }
                else
                {
                    delayMicroseconds(10 * DELAY_VALUE); //10 us
                }
            }
        }
        else // Format 2
        {
            uint8_t BST_SW_a = COG_data[offset + 1] & _filter09;
            uint8_t BST_SW_b = COG_data[offset + 2] & _filter09;
            uint8_t DELAY_a_SCALE = COG_data[offset + 3] & 0x80;
            uint16_t DELAY_a_VALUE = COG_data[offset + 3] & 0x7f;
            uint8_t DELAY_b_SCALE = COG_data[offset + 4] & 0x80;
            uint16_t DELAY_b_VALUE = COG_data[offset + 4] & 0x7f;

            for (uint8_t i = 0; i < REPEAT; i += 1)
            {
                b_sendCommandDataSelect8(0x09, BST_SW_a, PANEL_CS_BOTH);

                if (DELAY_a_SCALE > 0)
                {
                    delay(DELAY_a_VALUE); // ms
                }
                else
                {
                    delayMicroseconds(10 * DELAY_a_VALUE); // 10 us
                }

                b_sendCommandDataSelect8(0x09, BST_SW_b, PANEL_CS_BOTH);

                if (DELAY_b_SCALE > 0)
                {
                    delay(DELAY_b_VALUE); // ms
                }
                else
                {
                    delayMicroseconds(10 * DELAY_b_VALUE); // 10 us
                }
            }
        }
    }

    // Display Refresh Start
    // Application note § 4. Send updating command
    b_waitBusy();
    b_sendCommandDataSelect8(0x15, 0x3c, PANEL_CS_BOTH);
}

void Screen_EPD_EXT3::COG_LargeCJ_powerOff()
{
    // Application note § 5. Turn-off DC/DC

    // DC-DC off
    b_waitBusy();

    switch (u_eScreen_EPD)
    {
        case eScreen_EPD_969_CS_08:
        case eScreen_EPD_969_JS_08:
        case eScreen_EPD_B98_CS_08:
        case eScreen_EPD_B98_FS_08:
        case eScreen_EPD_B98_GS_08:

            b_sendCommandDataSelect8(0x09, 0x7f, PANEL_CS_BOTH);
            delay(20);
            b_sendCommandDataSelect8(0x05, 0x7d, PANEL_CS_BOTH);
            b_sendCommandDataSelect8(0x09, 0x00, PANEL_CS_BOTH);
            delay(200);
            break;

        case eScreen_EPD_969_CS_0B:
        case eScreen_EPD_969_JS_0B:
        case eScreen_EPD_B98_JS_0B:

            b_sendCommandDataSelect8(0x09, 0x7f, PANEL_CS_BOTH);
            b_sendCommandDataSelect8(0x05, 0x3d, PANEL_CS_BOTH);
            b_sendCommandDataSelect8(0x09, 0x7e, PANEL_CS_BOTH);
            delay(15);
            b_sendCommandDataSelect8(0x09, 0x00, PANEL_CS_BOTH);
            break;

        case eScreen_EPD_B98_CS_0B:

            b_sendCommandDataSelect8(0x09, 0x7b, PANEL_CS_BOTH);
            b_sendCommandDataSelect8(0x05, 0x3d, PANEL_CS_BOTH);
            b_sendCommandDataSelect8(0x09, 0x7a, PANEL_CS_BOTH);
            delay(15);
            b_sendCommandDataSelect8(0x09, 0x00, PANEL_CS_BOTH);
            break;

        default:

            break;
    }
}
//
// --- End of Large screens with C or J film
//

//
// --- Medium screens with C or J film
//
void Screen_EPD_EXT3::COG_MediumCJ_reset()
{
    // Application note § 2. Power on COG driver
    b_reset(200, 20, 200, 50, 5); // medium
}

void Screen_EPD_EXT3::COG_MediumCJ_getDataOTP()
{
    // Application note § none
    // Application note § 1.5 Read MTP data
    // Application note § 1.6 Read MTP data
    uint16_t _readBytes = 0;
    uint8_t ui8 = 0; // dummy
    u_flagOTP = false;

    COG_MediumCJ_reset();
    if (b_family == FAMILY_LARGE)
    {
        digitalWrite(b_pin.panelCSS, HIGH);    // Unselect slave panel
    }

    // Read OTP
    switch (u_codeDriver)
    {
        case DRIVER_B:

            _readBytes = 128;

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xb9);
            delay(5);
            break;

        case DRIVER_8:

            _readBytes = 80;

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa1);
            digitalWrite(b_pin.panelDC, HIGH); // Data
            hV_HAL_SPI3_write(0x00);
            digitalWrite(b_pin.panelCS, HIGH); // Unselect

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa7);
            digitalWrite(b_pin.panelDC, HIGH); // Data
            hV_HAL_SPI3_write(0x80);
            digitalWrite(b_pin.panelCS, HIGH); // Unselect

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa3);
            digitalWrite(b_pin.panelDC, HIGH); // Data
            hV_HAL_SPI3_write(0x00);
            hV_HAL_SPI3_write(0x40);
            digitalWrite(b_pin.panelCS, HIGH); // Unselect

            digitalWrite(b_pin.panelDC, LOW); // Command
            digitalWrite(b_pin.panelCS, LOW); // Select
            hV_HAL_SPI3_write(0xa8);
            delay(5);
            break;

        default:

            mySerial.println();
            mySerial.println(formatString("hV * OTP failed for screen %i-%cS-0%c", u_codeSize, u_codeFilm, u_codeDriver));
            while (0x01);
            break;
    }

    digitalWrite(b_pin.panelDC, HIGH); // Data
    ui8 = hV_HAL_SPI3_read(); // Dummy
    // hV_HAL_log(LEVEL_DEBUG, "Dummy read 0x%02x", ui8);

    // Populate COG_data
    for (uint16_t index = 0; index < _readBytes; index += 1)
    {
        COG_data[index] = hV_HAL_SPI3_read(); // Read OTP
    }

    // End of OTP reading
    digitalWrite(b_pin.panelCS, HIGH); // Unselect

    // Check
    if (u_codeDriver == DRIVER_B)
    {
        // No check for DRIVER_B
    }
    else if (u_codeDriver == DRIVER_8)
    {
        if (COG_data[0] == 0xa5)
        {
            mySerial.println(formatString("hV . OTP check passed - First 0x%02x as expected", COG_data[0]));
        }
        else
        {
            mySerial.println();
            mySerial.println(formatString("hV * OTP check failed - First 0x%02x, expected 0x%02x", COG_data[0], 0xa5));
            while (0x01);
        }
    }

    u_flagOTP = true;
}

void Screen_EPD_EXT3::COG_MediumCJ_initial()
{
    // Application note § 3.1 Initial flow chart
    COG_MediumCJ_reset();

    // Soft reset
    // Work settings
    if (u_codeDriver == DRIVER_B)
    {
        b_sendCommandData8(0x01, COG_data[0x10]); // DCTL
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // No DCTL here
    }
}

void Screen_EPD_EXT3::COG_MediumCJ_sendImageData()
{
    // Application note § 4. Input image to the EPD
    // Application note § 3.2 Send image to the EPD
    FRAMEBUFFER_TYPE blackBuffer = s_newImage;
    FRAMEBUFFER_TYPE redBuffer = s_newImage + u_pageColourSize;

    if (u_codeDriver == DRIVER_B)
    {
        // Send image data
        b_sendIndexData(0x13, &COG_data[0x15], 6); // DUW
        b_sendIndexData(0x90, &COG_data[0x0c], 4); // DRFW
        b_sendIndexData(0x12, &COG_data[0x12], 3); // RAM_RW
        b_sendIndexData(0x10, blackBuffer, u_pageColourSize); // First frame

        b_sendIndexData(0x12, &COG_data[0x12], 3); // RAM_RW

        switch (u_codeFilm)
        {
            case FILM_C:

                b_sendIndexFixed(0x11, 0x00, u_pageColourSize); // Second frame = dummy
                break;

            default:

                b_sendIndexData(0x11, redBuffer, u_pageColourSize); // Second frame
                break;
        }
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // Send image data
        b_sendIndexData(0x13, &COG_data[0x16], 6); // DUW
        b_sendIndexData(0x90, &COG_data[0x0c], 4); // DRFW
        b_sendIndexData(0x12, &COG_data[0x13], 3); // RAM_RW
        b_sendIndexData(0x10, blackBuffer, u_pageColourSize); // First frame

        b_sendIndexData(0x12, &COG_data[0x13], 3); // RAM_RW

        switch (u_codeFilm)
        {
            case FILM_C:

                b_sendIndexFixed(0x11, 0x00, u_pageColourSize); // Second frame = dummy
                break;

            default:

                b_sendIndexData(0x11, redBuffer, u_pageColourSize); // Second frame
                break;
        }
    }
}

void Screen_EPD_EXT3::COG_MediumCJ_update()
{
    // Application note § 3.1 Initial flow chart
    // Application note § 3.3 DC/DC soft-start
    // Application note § 4. Send updating command
    if (u_codeDriver == DRIVER_B)
    {
        // Initial COG
        b_sendCommandData8(0x05, 0x7d);
        delay(200);
        b_sendCommandData8(0x05, 0x00);
        delay(10);
        b_sendCommandData8(0xd8, COG_data[0x1c]); // MS_SYNC
        b_sendCommandData8(0xd6, COG_data[0x1d]); // BVSS

        b_sendCommandData8(0xa7, 0x10);
        delay(100);
        b_sendCommandData8(0xa7, 0x00);
        delay(100);

        b_sendCommandData8(0x44, 0x00);
        b_sendCommandData8(0x45, 0x80);

        b_sendCommandData8(0xa7, 0x10);
        delay(100);
        b_sendCommandData8(0xa7, 0x00);
        delay(100);

        b_sendCommandData8(0x44, 0x06);
        uint8_t indexTemperature = u_temperature * 2 + 0x50;
        b_sendCommandData8(0x45, indexTemperature); // Temperature 0x82@25C

        b_sendCommandData8(0xa7, 0x10);
        delay(100);
        b_sendCommandData8(0xa7, 0x00);
        delay(100);

        b_sendCommandData8(0x60, COG_data[0x0b]); // TCON
        b_sendCommandData8(0x61, COG_data[0x1b]); // STV_DIR
        // No DCTL here
        b_sendCommandData8(0x02, COG_data[0x11]); // VCOM
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // Initial COG
        b_sendCommandData8(0x05, 0x7d);
        delay(200);
        b_sendCommandData8(0x05, 0x00);
        delay(10);

        b_sendCommandData8(0xc2, 0x3f);
        delay(1);

        b_sendCommandData8(0xd8, COG_data[0x1d]); // MS_SYNC
        b_sendCommandData8(0xd6, COG_data[0x1e]); // BVSS

        b_sendCommandData8(0xa7, 0x10);
        delay(100);
        b_sendCommandData8(0xa7, 0x00);
        delay(100);

        uint8_t data03[2] = {0x00, COG_data[0x12]}; // OSC
        b_sendIndexData(0x03, data03, 2); // OSC mtp_0x12
        b_sendCommandData8(0x44, 0x00);
        b_sendCommandData8(0x45, 0x80);

        b_sendCommandData8(0xa7, 0x10);
        delay(100);
        b_sendCommandData8(0xa7, 0x00);
        delay(100);

        b_sendCommandData8(0x44, 0x06);
        uint8_t indexTemperature = u_temperature * 2 + 0x50;
        b_sendCommandData8(0x45, indexTemperature); // Temperature 0x82@25C

        b_sendCommandData8(0xa7, 0x10);
        delay(100);
        b_sendCommandData8(0xa7, 0x00);
        delay(100);

        b_sendCommandData8(0x60, COG_data[0x0b]); // TCON
        b_sendCommandData8(0x61, COG_data[0x1c]); // STV_DIR
        b_sendCommandData8(0x01, COG_data[0x10]); // DCTL
        b_sendCommandData8(0x02, COG_data[0x11]); // VCOM
    }

    // DC/DC Soft-start
    // Application note § 3.3 DC/DC soft-start
    // DRIVER_B = 0x28, DRIVER_8 = 0x20
    uint8_t offsetFrame = (u_codeDriver == DRIVER_B) ? 0x28 : 0x20;

    // Filter for register 0x09
    uint8_t _filter09;

    switch (u_eScreen_EPD)
    {
        case eScreen_EPD_581_CS_08:

            _filter09 = 0xfb;
            break;

        default:

            _filter09 = 0xff;
            break;
    }

    for (uint8_t stage = 0; stage < 4; stage += 1)
    {
        uint8_t offset = offsetFrame + 0x08 * stage;
        // iPH[0] = COG_userData.SS[value].PHLINI_BSTSWa;
        // iPH[1] = COG_userData.SS[value].PHHINI_BSTSWb;
        uint8_t FORMAT = COG_data[offset] & 0x80;
        uint8_t REPEAT = COG_data[offset] & 0x7f;

        if (FORMAT > 0) // Format 1
        {
            uint8_t PHL_PHH[2];
            PHL_PHH[0] = COG_data[offset + 1]; // PHL_INI
            PHL_PHH[1] = COG_data[offset + 2]; // PHH_INI
            uint8_t PHL_VAR = COG_data[offset + 3];
            uint8_t PHH_VAR = COG_data[offset + 4];
            uint8_t BST_SW_a = COG_data[offset + 5] & _filter09;
            uint8_t BST_SW_b = COG_data[offset + 6] & _filter09;
            uint8_t DELAY_SCALE = COG_data[offset + 7] & 0x80;
            uint16_t DELAY_VALUE = COG_data[offset + 7] & 0x7f;

            for (uint8_t i = 0; i < REPEAT; i += 1)
            {
                b_sendCommandData8(0x09, BST_SW_a);
                PHL_PHH[0] += PHL_VAR; // PHL
                PHL_PHH[1] += PHH_VAR; // PHH
                b_sendIndexData(0x51, PHL_PHH, 2);
                b_sendCommandData8(0x09, BST_SW_b);

                if (DELAY_SCALE > 0)
                {
                    delay(DELAY_VALUE); // ms
                }
                else
                {
                    delayMicroseconds(10 * DELAY_VALUE); //10 us
                }
            }
        }
        else // Format 2
        {
            uint8_t BST_SW_a = COG_data[offset + 1] & _filter09;
            uint8_t BST_SW_b = COG_data[offset + 2] & _filter09;
            uint8_t DELAY_a_SCALE = COG_data[offset + 3] & 0x80;
            uint16_t DELAY_a_VALUE = COG_data[offset + 3] & 0x7f;
            uint8_t DELAY_b_SCALE = COG_data[offset + 4] & 0x80;
            uint16_t DELAY_b_VALUE = COG_data[offset + 4] & 0x7f;

            for (uint8_t i = 0; i < REPEAT; i += 1)
            {
                b_sendCommandData8(0x09, BST_SW_a);

                if (DELAY_a_SCALE > 0)
                {
                    delay(DELAY_a_VALUE); // ms
                }
                else
                {
                    delayMicroseconds(10 * DELAY_a_VALUE); // 10 us
                }

                b_sendCommandData8(0x09, BST_SW_b);

                if (DELAY_b_SCALE > 0)
                {
                    delay(DELAY_b_VALUE); // ms
                }
                else
                {
                    delayMicroseconds(10 * DELAY_b_VALUE); // 10 us
                }
            }
        }
    }

    // Display Refresh Start
    // Application note § 4. Send updating command
    b_waitBusy();
    b_sendCommandData8(0x15, 0x3c);
}

void Screen_EPD_EXT3::COG_MediumCJ_powerOff()
{
    // Application note § 6. Turn-off DC/DC
    // Application note § 5. Turn-off DC/DC

    // DC-DC off
    b_waitBusy();

    switch (u_eScreen_EPD)
    {
        case eScreen_EPD_565_JS_08:
        case eScreen_EPD_581_FS_08:
        case eScreen_EPD_741_CS_08:
        case eScreen_EPD_741_FS_08:
        case eScreen_EPD_741_GS_08:

            b_sendCommandData8(0x09, 0x7f);
            delay(20);
            b_sendCommandData8(0x05, 0x7d);
            b_sendCommandData8(0x09, 0x00);
            delay(200);
            break;

        case eScreen_EPD_581_JS_0B:
        case eScreen_EPD_741_CS_0B:
        case eScreen_EPD_741_JS_0B:

            b_sendCommandData8(0x09, 0x7f);
            b_sendCommandData8(0x05, 0x3d);
            b_sendCommandData8(0x09, 0x7e);
            delay(15);
            b_sendCommandData8(0x09, 0x00);
            break;

        case eScreen_EPD_581_CS_0B:

            b_sendCommandData8(0x09, 0x7b);
            b_sendCommandData8(0x05, 0x3d);
            b_sendCommandData8(0x09, 0x7a);
            delay(15);
            b_sendCommandData8(0x09, 0x00);
            break;

        default:

            break;
    }
}
//
// --- End of Medium screens with C or J film
//

//
// --- Small screens with C or J film
//
void Screen_EPD_EXT3::COG_SmallCJ_reset()
{
    // Application note § 2. Power on COG driver
    b_reset(5, 5, 10, 5, 5); // small
}

void Screen_EPD_EXT3::COG_SmallCJ_getDataOTP()
{
    // Application note § none
    // Application note § 1.5 Read MTP data
    // Application note § 1.6 Read MTP data
    uint16_t _readBytes = 0;
    uint8_t ui8 = 0; // dummy
    u_flagOTP = false;

    _readBytes = 2;

    switch (u_codeSize)
    {
        case SIZE_370:
        case SIZE_417:
        case SIZE_437:

            COG_data[0] = 0x0f;
            COG_data[1] = 0x89;
            break;

        default:

            COG_data[0] = 0xcf;
            COG_data[1] = 0x8d;
            break;
    }

    u_flagOTP = true;
}

void Screen_EPD_EXT3::COG_SmallCJ_initial()
{
    // Application note § 3. Set environment temperature and PSR

    // Soft reset
    // Work settings
    COG_SmallCJ_reset();

    b_sendCommandData8(0x00, 0x0e); // Soft-reset
    delay(5);

    // Temperature
    b_sendCommandData8(0xe5, u_temperature); // Input Temperature 0°C = 0x00, 22°C = 0x16, 25°C = 0x19
    b_sendCommandData8(0xe0, 0x02); // Active Temperature

    b_sendIndexData(0x00, COG_data, 2); // PSR
}

void Screen_EPD_EXT3::COG_SmallCJ_sendImageData()
{
    // Application note § 4. Input image to the EPD
    FRAMEBUFFER_TYPE blackBuffer = s_newImage;
    FRAMEBUFFER_TYPE redBuffer = s_newImage + u_pageColourSize;

    // Send image data
    switch (u_codeFilm)
    {
        case FILM_C:

            b_sendIndexData(0x10, blackBuffer, u_pageColourSize); // First frame
            b_sendIndexFixed(0x13, 0x00, u_pageColourSize); // Second frame = dummy
            break;

        default:

            b_sendIndexData(0x10, blackBuffer, u_pageColourSize); // First frame
            b_sendIndexData(0x13, redBuffer, u_pageColourSize); // Second frame
            break;
    }
}

void Screen_EPD_EXT3::COG_SmallCJ_update()
{
    // Application note § 5. Send updating command
    // Application note § 3.3 DC/DC soft-start
    // Application note § 4. Send updating command

    // Display Refresh Start
    b_waitBusy();
    b_sendCommand8(0x04); // Power on
    b_waitBusy();
    b_sendCommand8(0x12); // Display Refresh
    delay(5);
    b_waitBusy();
}

void Screen_EPD_EXT3::COG_SmallCJ_powerOff()
{
    // Application note § 5. Turn-off DC/DC

    // DC-DC off
    b_sendCommand8(0x02); // Turn off DC/DC
    b_waitBusy();
}
//
// --- End of Small screens with C or J film
//
/// @endcond
//
// === End of COG section
//

//
// === Class section
//
Screen_EPD_EXT3::Screen_EPD_EXT3(eScreen_EPD_t eScreen_EPD_EXT3, pins_t board)
{
    u_eScreen_EPD = eScreen_EPD_EXT3;
    b_pin = board;
    s_newImage = 0; // nullptr
    COG_data[0] = 0;
}

void Screen_EPD_EXT3::begin()
{
    // u_eScreen_EPD = eScreen_EPD_EXT3;
    u_codeSize = SCREEN_SIZE(u_eScreen_EPD);
    u_codeFilm = SCREEN_FILM(u_eScreen_EPD);
    u_codeDriver = SCREEN_DRIVER(u_eScreen_EPD);
    u_codeExtra = SCREEN_EXTRA(u_eScreen_EPD);
    v_screenColourBits = 2; // BWR and BWRY

    // Checks
    switch (u_codeFilm)
    {
        case FILM_C: // Standard
        case FILM_H: // BW, Freezer
        case FILM_E: // BWR, deprecated
        case FILM_F: // BWR, deprecated
        case FILM_G: // BWY, deprecated
        case FILM_J: // BWR, "Spectra"

            break;

        default:

            debugVariant(FILM_C);
            break;
    }

    //
    // === Touch section
    //

    //
    // === End of touch section
    //

    //
    // === Large screen section
    //
    // Check panelCSS for large screens
    if (((u_codeSize == SIZE_969) or (u_codeSize == SIZE_1198)) and (b_pin.panelCSS == NOT_CONNECTED))
    {
        mySerial.println();
        mySerial.println("hV * Required pin panelCSS is NOT_CONNECTED");
        while (0x01);
    }
    //
    // === End of Large screen section
    //

    // Configure board
    switch (u_codeSize)
    {
        case SIZE_343: // 3.43"
        case SIZE_565: // 5.65"
        case SIZE_581: // 5.81"
        case SIZE_741: // 7.41"

            b_begin(b_pin, FAMILY_MEDIUM, 0);
            break;

        case SIZE_969: // 9.69"
        case SIZE_1198: // 11.98"

            b_begin(b_pin, FAMILY_LARGE, 50);
            break;

        default:

            b_begin(b_pin, FAMILY_SMALL, 0);
            break;
    }

    // Sizes
    switch (u_codeSize)
    {
        case SIZE_154: // 1.54"

            v_screenSizeV = 152; // vertical = wide size
            v_screenSizeH = 152; // horizontal = small size
            break;

        case SIZE_213: // 2.13"

            v_screenSizeV = 212; // vertical = wide size
            v_screenSizeH = 104; // horizontal = small size
            break;

        case SIZE_266: // 2.66"

            v_screenSizeV = 296; // vertical = wide size
            v_screenSizeH = 152; // horizontal = small size
            break;

        case SIZE_271: // 2.71" and 2.71"-Touch

            v_screenSizeV = 264; // vertical = wide size
            v_screenSizeH = 176; // horizontal = small size
            break;

        case SIZE_287: // 2.87"

            v_screenSizeV = 296; // vertical = wide size
            v_screenSizeH = 128; // horizontal = small size
            break;

        case SIZE_290: // 2.90"

            v_screenSizeV = 384; // vertical = wide size
            v_screenSizeH = 168; // horizontal = small size
            break;

        case SIZE_370: // 3.70" and 3.70"-Touch

            v_screenSizeV = 416; // vertical = wide size
            v_screenSizeH = 240; // horizontal = small size
            break;

        case SIZE_417: // 4.17"

            v_screenSizeV = 300; // vertical = wide size
            v_screenSizeH = 400; // horizontal = small size
            break;

        case SIZE_437: // 4.37"

            v_screenSizeV = 480; // vertical = wide size
            v_screenSizeH = 176; // horizontal = small size
            break;

        case SIZE_565: // 5.65"

            v_screenSizeV = 600; // v = wide size
            v_screenSizeH = 448; // h = small size
            break;

        case SIZE_581: // 5.81"

            v_screenSizeV = 720; // v = wide size
            v_screenSizeH = 256; // h = small size
            break;

        case SIZE_741: // 7.41"

            v_screenSizeV = 800; // v = wide size
            v_screenSizeH = 480; // h = small size
            break;

        case SIZE_969: // 9.69"

            v_screenSizeV = 672; // v = wide size
            v_screenSizeH = 960; // Actually, 960 = 480 x 2, h = small size
            break;

        case SIZE_1198: // 11.98"

            v_screenSizeV = 768; // v = wide size
            v_screenSizeH = 960; // Actually, 960 = 480 x 2, h = small size
            break;

        default:

            mySerial.println();
            mySerial.println(formatString("hV * Screen %i-%cS-0%c is not supported", u_codeSize, u_codeFilm, u_codeDriver));
            while (0x01);
            break;
    } // u_codeSize
    v_screenDiagonal = u_codeSize;

    // Report
    mySerial.println(formatString("hV = Screen %s", WhoAmI().c_str()));
    mySerial.println(formatString("hV = Size %ix%i", screenSizeX(), screenSizeY()));
    mySerial.println(formatString("hV = Number %i-%cS-0%c", u_codeSize, u_codeFilm, u_codeDriver));
    mySerial.println(formatString("hV = PDLS %s v%i.%i.%i", SCREEN_EPD_EXT3_VARIANT, SCREEN_EPD_EXT3_RELEASE / 100, (SCREEN_EPD_EXT3_RELEASE / 10) % 10, SCREEN_EPD_EXT3_RELEASE % 10));
    mySerial.println();

    u_bufferDepth = v_screenColourBits; // 2 colours
    u_bufferSizeV = v_screenSizeV; // vertical = wide size
    u_bufferSizeH = v_screenSizeH / 8; // horizontal = small size 112 / 8, 1 bit per pixel

    // Force conversion for two unit16_t multiplication into uint32_t.
    // Actually for 1 colour; BWR requires 2 pages.
    u_pageColourSize = (uint32_t)u_bufferSizeV * (uint32_t)u_bufferSizeH;

#if defined(BOARD_HAS_PSRAM) // ESP32 PSRAM specific case

    if (s_newImage == 0)
    {
        static uint8_t * _newFrameBuffer;
        _newFrameBuffer = (uint8_t *) ps_malloc(u_pageColourSize * u_bufferDepth);
        s_newImage = (uint8_t *) _newFrameBuffer;
    }

#else // default case

    if (s_newImage == 0)
    {
        static uint8_t * _newFrameBuffer;
        _newFrameBuffer = new uint8_t[u_pageColourSize * u_bufferDepth];
        s_newImage = (uint8_t *) _newFrameBuffer;
    }

#endif // ESP32 BOARD_HAS_PSRAM

    memset(s_newImage, 0x00, u_pageColourSize * u_bufferDepth);

    setTemperatureC(25); // 25 Celsius = 77 Fahrenheit
    b_fsmPowerScreen = FSM_OFF;
    if (b_pin.panelPower != NOT_CONNECTED)
    {
        setPowerProfile(POWER_MODE_AUTO, POWER_SCOPE_GPIO_ONLY);
    }

    // Turn SPI on, initialise GPIOs and set GPIO levels
    // Reset panel and get tables
    resume();

    // Fonts
    hV_Screen_Buffer::begin(); // Standard

    if (f_fontMax() > 0)
    {
        f_selectFont(0);
    }
    f_fontSolid = false;

    // Orientation
    setOrientation(0);

    v_penSolid = false;
    u_invert = false;

    //
    // === Touch section
    //

    //
    // === End of Touch section
    //
}

STRING_TYPE Screen_EPD_EXT3::WhoAmI()
{
    char work[64] = {0};
    u_WhoAmI(work);

    return formatString("iTC %i.%02i\"%s", v_screenDiagonal / 100, v_screenDiagonal % 100, work);
}

void Screen_EPD_EXT3::suspend(uint8_t suspendScope)
{
    if (((suspendScope & FSM_GPIO_MASK) == FSM_GPIO_MASK) and (b_pin.panelPower != NOT_CONNECTED))
    {
        if ((b_fsmPowerScreen & FSM_GPIO_MASK) == FSM_GPIO_MASK)
        {
            b_suspend();
        }
    }
}

void Screen_EPD_EXT3::resume()
{
    // Target   FSM_ON
    // Source   FSM_OFF
    //          FSM_SLEEP
    if (b_fsmPowerScreen != FSM_ON)
    {
        if ((b_fsmPowerScreen & FSM_GPIO_MASK) != FSM_GPIO_MASK)
        {
            b_resume(); // GPIO

            s_reset(); // Reset

            b_fsmPowerScreen |= FSM_GPIO_MASK;
        }

        // Check type and get tables
        if (u_flagOTP == false)
        {
            s_getDataOTP(); // 3-wire SPI read OTP memory

            s_reset(); // Reset
        }

        // Start SPI, with unicity check
        hV_HAL_SPI_begin(); // Standard 8 MHz
        // hV_HAL_SPI_begin(16000000); // Fast 16 MHz, with unicity check
    }
}

uint8_t Screen_EPD_EXT3::flushMode(uint8_t updateMode)
{
    updateMode = checkTemperatureMode(updateMode);

    switch (updateMode)
    {
        case UPDATE_FAST:
        case UPDATE_GLOBAL:

            s_flush();
            break;

        default:

            mySerial.println();
            mySerial.println("hV * UPDATE_NONE invoked");
            break;
    }

    return updateMode;
}

void Screen_EPD_EXT3::s_reset()
{
    switch (b_family)
    {
        case FAMILY_LARGE:

            COG_LargeCJ_reset();
            break;

        case FAMILY_MEDIUM:

            COG_MediumCJ_reset();
            break;

        case FAMILY_SMALL:

            COG_SmallCJ_reset();
            break;

        default:

            break;
    }
}

void Screen_EPD_EXT3::s_getDataOTP()
{
    hV_HAL_SPI_end(); // With unicity check

    hV_HAL_SPI3_begin(); // Define 3-wire SPI pins

    // Get data OTP
    switch (b_family)
    {
        case FAMILY_LARGE:

            COG_LargeCJ_getDataOTP();
            break;

        case FAMILY_MEDIUM:

            COG_MediumCJ_getDataOTP();
            break;

        case FAMILY_SMALL:

            COG_SmallCJ_getDataOTP();
            break;

        default:

            break;
    }
}

void Screen_EPD_EXT3::s_flush(uint8_t updateMode)
{
    // Resume
    if (b_fsmPowerScreen != FSM_ON)
    {
        resume();
    }

    // Three groups:
    // + small: up to 4.37 included
    // + medium: 3.43, 5.65, 5.81 and 7.41
    // + large: 9.69 and 11,98
    // switch..case does not allow variable declarations
    //
    switch (b_family)
    {
        case FAMILY_LARGE:

            COG_LargeCJ_initial(); // Initialise
            COG_LargeCJ_sendImageData(); // Send image data
            COG_LargeCJ_update(); // Update
            COG_LargeCJ_powerOff(); // Power off
            break;

        case FAMILY_MEDIUM:

            COG_MediumCJ_initial(); // Initialise
            COG_MediumCJ_sendImageData(); // Send image data
            COG_MediumCJ_update(); // Update
            COG_MediumCJ_powerOff(); // Power off
            break;

        case FAMILY_SMALL:

            COG_SmallCJ_initial(); // Initialise
            COG_SmallCJ_sendImageData(); // Send image data
            COG_SmallCJ_update(); // Update
            COG_SmallCJ_powerOff(); // Power off
            break;

        default:

            break;
    }

    // Turn SPI off and pull GPIOs low
    suspend();
}

void Screen_EPD_EXT3::flush()
{
    flushMode(UPDATE_GLOBAL);
}

void Screen_EPD_EXT3::clear(uint16_t colour)
{
    if (colour == myColours.red)
    {
        // physical red 0-1
        memset(s_newImage, 0x00, u_pageColourSize);
        memset(s_newImage + u_pageColourSize, 0xff, u_pageColourSize);
    }
    else if (colour == myColours.grey)
    {
        for (uint16_t i = 0; i < u_bufferSizeV; i++)
        {
            uint8_t pattern = (i % 2) ? 0b10101010 : 0b01010101;
            for (uint16_t j = 0; j < u_bufferSizeH; j++)
            {
                s_newImage[i * u_bufferSizeH + j] = pattern;
            }
        }
        memset(s_newImage + u_pageColourSize, 0x00, u_pageColourSize);
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
                s_newImage[i * u_bufferSizeH + j] = pattern1;
                s_newImage[i * u_bufferSizeH + j + u_pageColourSize] = pattern2;
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
                s_newImage[i * u_bufferSizeH + j] = pattern1;
                s_newImage[i * u_bufferSizeH + j + u_pageColourSize] = pattern2;
            }
        }
    }
    else if ((colour == myColours.white) xor u_invert)
    {
        // physical black 0-0
        memset(s_newImage, 0x00, u_pageColourSize);
        memset(s_newImage + u_pageColourSize, 0x00, u_pageColourSize);
    }
    else
    {
        // physical white 1-0
        memset(s_newImage, 0xff, u_pageColourSize);
        memset(s_newImage + u_pageColourSize, 0x00, u_pageColourSize);
    }
}

void Screen_EPD_EXT3::regenerate(uint8_t mode)
{
    clear(myColours.black);
    flush();
    delay(100);

    clear(myColours.white);
    flush();
    delay(100);
}

void Screen_EPD_EXT3::s_setPoint(uint16_t x1, uint16_t y1, uint16_t colour)
{
    // Orient and check coordinates are within screen
    if (s_orientCoordinates(x1, y1) == RESULT_ERROR)
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
    uint32_t z1 = s_getZ(x1, y1);
    uint16_t b1 = s_getB(x1, y1);

    // Basic colours
    if (colour == myColours.red)
    {
        // physical red 0-1
        bitClear(s_newImage[z1], b1);
        bitSet(s_newImage[u_pageColourSize + z1], b1);
    }
    else if ((colour == myColours.white) xor u_invert)
    {
        // physical black 0-0
        bitClear(s_newImage[z1], b1);
        bitClear(s_newImage[u_pageColourSize + z1], b1);
    }
    else if ((colour == myColours.black) xor u_invert)
    {
        // physical white 1-0
        bitSet(s_newImage[z1], b1);
        bitClear(s_newImage[u_pageColourSize + z1], b1);
    }
}

void Screen_EPD_EXT3::s_setOrientation(uint8_t orientation)
{
    v_orientation = orientation % 4;
}

bool Screen_EPD_EXT3::s_orientCoordinates(uint16_t & x, uint16_t & y)
{
    bool _flagResult = RESULT_ERROR;
    switch (v_orientation)
    {
        case 3: // checked, previously 1

            if ((x < v_screenSizeV) and (y < v_screenSizeH))
            {
                x = v_screenSizeV - 1 - x;
                _flagResult = RESULT_SUCCESS;
            }
            break;

        case 2: // checked

            if ((x < v_screenSizeH) and (y < v_screenSizeV))
            {
                x = v_screenSizeH - 1 - x;
                y = v_screenSizeV - 1 - y;
                swap(x, y);
                _flagResult = RESULT_SUCCESS;
            }
            break;

        case 1: // checked, previously 3

            if ((x < v_screenSizeV) and (y < v_screenSizeH))
            {
                y = v_screenSizeH - 1 - y;
                _flagResult = RESULT_SUCCESS;
            }
            break;

        default: // checked

            if ((x < v_screenSizeH) and (y < v_screenSizeV))
            {
                swap(x, y);
                _flagResult = RESULT_SUCCESS;
            }
            break;
    }

    return _flagResult;
}

uint32_t Screen_EPD_EXT3::s_getZ(uint16_t x1, uint16_t y1)
{
    uint32_t z1 = 0;
    // According to 11.98 inch Spectra Application Note
    // at http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=245146
    switch (u_codeSize)
    {
        case SIZE_969:
        case SIZE_1198:

            if (y1 >= (v_screenSizeH >> 1))
            {
                y1 -= (v_screenSizeH >> 1); // rebase y1
                z1 += (u_pageColourSize >> 1); // buffer second half
            }
            z1 += (uint32_t)x1 * (u_bufferSizeH >> 1) + (y1 >> 3);
            break;

        default:

            z1 = (uint32_t)x1 * u_bufferSizeH + (y1 >> 3);
            break;
    }
    return z1;
}

uint16_t Screen_EPD_EXT3::s_getB(uint16_t x1, uint16_t y1)
{
    uint16_t b1 = 0;

    b1 = 7 - (y1 % 8);

    return b1;
}

uint16_t Screen_EPD_EXT3::s_getPoint(uint16_t x1, uint16_t y1)
{
    return 0x0000;
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

