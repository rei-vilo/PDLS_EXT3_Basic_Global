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
// Release 800: Read OTP memory
// Release 801: Improved OTP implementation
//

// Library header
#include "Screen_EPD_EXT3.h"

#define DEBUG_OTP 1

//
// === COG section
//
/// @cond
/// @see
/// * ApplicationNote_Small_Size_Mono_v02_220606
/// * ApplicationNote_Small_Size_Spectra_v06_220606

void Screen_EPD_EXT3::COG_initialLarge()
{
    // Application note § 3.1 Initial flow chart

    // Soft reset
    // Work settings
}

void Screen_EPD_EXT3::COG_initialMedium()
{
    // Application note § 3.1 Initial flow chart

    // Soft reset
    // Work settings
}

void Screen_EPD_EXT3::COG_initialSmall()
{
    // Application note § 3. Set environment temperature and PSR

    // Soft reset
    // Work settings
}

void Screen_EPD_EXT3::COG_getDataOTP()
{
    // Application note § none
    // Application note § 1.5 Read MTP data
    // Application note § 1.6 Read MTP data
    uint16_t u_readBytes;
    uint8_t ui8; // dummy

    if ((b_family == FAMILY_MEDIUM) or (b_family == FAMILY_LARGE))
    {
        // GPIO
        COG_reset(); // Although not mentioned, reset to ensure stable state
        if (b_family == FAMILY_LARGE)
        {
            digitalWrite(b_pin.panelCSS, HIGH);    // Unselect slave panel
        }

        // Read OTP
        switch (u_codeDriver)
        {
            case DRIVER_B:

                u_readBytes = 128;

                digitalWrite(b_pin.panelDC, LOW); // Command
                digitalWrite(b_pin.panelCS, LOW); // Select
                hV_HAL_SPI3_write(0xb9);
                delay(5);
                break;

            case DRIVER_8:

                u_readBytes = 80;

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
        // mySerial.println(formatString("hV = Dummy read 0x%02x", ui8);

        // Populate COG_initialData
        for (uint16_t index = 0; index < u_readBytes; index += 1)
        {
            COG_initialData[index] = hV_HAL_SPI3_read(); // Read OTP
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
            if (COG_initialData[0] == 0xa5)
            {
                mySerial.println(formatString("hV . OTP check passed - First 0x%02x as expected", COG_initialData[0]));
            }
            else
            {
                mySerial.println(formatString("hV * OTP check failed - First 0x%02x, expected 0x%02x", COG_initialData[0], 0xa5));
                while (0x01);
            }
        }

        u_flagOTP = true;
    }
    else if (b_family == FAMILY_SMALL) // FAMILY_SMALL
    {
        u_readBytes = 2;

        switch (u_codeSize)
        {
            case SIZE_370:
            case SIZE_417:
            case SIZE_437:

                COG_initialData[0] = 0x0f;
                COG_initialData[1] = 0x89;
                break;

            default:

                COG_initialData[0] = 0xcf;
                COG_initialData[1] = 0x8d;
                break;
        }
        u_flagOTP = true;
    }
    else
    {
        mySerial.println();
        mySerial.println(formatString("hV * OTP failed for screen %i-%cS-0%c", u_codeSize, u_codeFilm, u_codeDriver));

        while (0x01);
    }

#if (DEBUG_OTP == 1)
    uint8_t debugIndex = u_readBytes;

    mySerial.print(formatString("const uint8_t debugOTP[%i] =", debugIndex));
    mySerial.println();
    mySerial.print("{");
    for (uint16_t index = 0; index < debugIndex; index += 1)
    {
        if ((index % 8) == 0)
        {
            mySerial.println();
            mySerial.print("   ");
        }

        mySerial.print(formatString("0x%02x", COG_initialData[index]));
        mySerial.print(formatString("%s ", (index + 1 < debugIndex ? "," : " "))); // no comma on last value

        if (((index + 1) % 8) == 0)
        {
            mySerial.print(formatString(" // 0x%04x..%04x", index - 7, index));
        }
    }
    mySerial.println();

    mySerial.print(formatString("} // %i", debugIndex));
    mySerial.println();
#endif // DEBUG_OTP
}

void Screen_EPD_EXT3::COG_reset()
{
    // Application note § 2. Power on COG driver
    switch (u_codeSize)
    {
        case SIZE_343: // 3.43"
        case SIZE_565: // 5.65"
        case SIZE_581: // 5.81"
        case SIZE_741: // 7.41"

            b_reset(200, 20, 200, 50, 5); // medium
            break;

        case SIZE_969: // 9.69"
        case SIZE_1198: // 11.98"

            b_reset(200, 20, 200, 200, 5); // large
            break;

        default:

            b_reset(5, 5, 10, 5, 5); // small
            break;
    } // u_codeSize
}

void Screen_EPD_EXT3::COG_sendImageDataGlobal()
{
    // Application note § 4. Input image to the EPD
    // Application note § 3.2 Send image to the EPD

}

void Screen_EPD_EXT3::COG_updateMedium()
{
#if (SRAM_MODE == USE_INTERNAL_MCU)

    uint8_t * blackBuffer = u_newImage;
    uint8_t * redBuffer = u_newImage + u_pageColourSize;

#elif (SRAM_MODE == USE_EXTERNAL_SPI)

    uint32_t blackBuffer = u_newImage;
    uint32_t redBuffer = u_newImage + u_pageColourSize;

#endif // SRAM_MODE

    // Application note § 5. Send updating command
    // Application note § 3.3 DC/DC soft-start
    // Application note § 4. Send updating command
    COG_reset();

    uint8_t _flagDriver8 = (u_codeDriver == DRIVER_8);

    if (u_codeDriver == DRIVER_B)
    {
        b_sendCommandData8(0x01, COG_initialData[0x10]); // DCTL

        // Send image data
        b_sendIndexData(0x13, &COG_initialData[0x15], 6); // DUW
        b_sendIndexData(0x90, &COG_initialData[0x0c], 4); // DRFW
        b_sendIndexData(0x12, &COG_initialData[0x12], 3); // RAM_RW

#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexData(0x10, blackBuffer, u_frameSize); // First frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSRAM(0x10, blackBuffer, u_frameSize); // First frame
#endif

        b_sendIndexData(0x12, &COG_initialData[0x12], 3); // RAM_RW

#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexData(0x11, redBuffer, u_frameSize); // Second frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSRAM(0x11, redBuffer, u_frameSize); // Second frame
#endif

        // Initial COG
        b_sendCommandData8(0x05, 0x7d);
        delay(200);
        b_sendCommandData8(0x05, 0x00);
        delay(10);
        b_sendCommandData8(0xd8, COG_initialData[0x1c]); // MS_SYNC
        b_sendCommandData8(0xd6, COG_initialData[0x1d]); // BVSS

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

        b_sendCommandData8(0x60, COG_initialData[0x0b]); // TCON
        b_sendCommandData8(0x61, COG_initialData[0x1b]); // STV_DIR
        // No DCTL here
        b_sendCommandData8(0x02, COG_initialData[0x11]); // VCOM
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // No DCTL here

        // Send image data
        b_sendIndexData(0x13, &COG_initialData[0x16], 6); // DUW
        b_sendIndexData(0x90, &COG_initialData[0x0c], 4); // DRFW
        b_sendIndexData(0x12, &COG_initialData[0x13], 3); // RAM_RW

#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexData(0x10, blackBuffer, u_frameSize); // First frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSRAM(0x10, blackBuffer, u_frameSize); // First frame
#endif

        b_sendIndexData(0x12, &COG_initialData[0x13], 3); // RAM_RW

#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexData(0x11, redBuffer, u_frameSize); // Second frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSRAM(0x11, redBuffer, u_frameSize); // Second frame
#endif

        // Initial COG
        b_sendCommandData8(0x05, 0x7d);
        delay(200);
        b_sendCommandData8(0x05, 0x00);
        delay(10);

        b_sendCommandData8(0xc2, 0x3f);
        delay(1);

        b_sendCommandData8(0xd8, COG_initialData[0x1d]); // MS_SYNC
        b_sendCommandData8(0xd6, COG_initialData[0x1e]); // BVSS

        b_sendCommandData8(0xa7, 0x10);
        delay(100);
        b_sendCommandData8(0xa7, 0x00);
        delay(100);

        uint8_t data03[2] = {0x00, COG_initialData[0x12]}; // OSC
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

        b_sendCommandData8(0x60, COG_initialData[0x0b]); // TCON
        b_sendCommandData8(0x61, COG_initialData[0x1c]); // STV_DIR
        b_sendCommandData8(0x01, COG_initialData[0x10]); // DCTL
        b_sendCommandData8(0x02, COG_initialData[0x11]); // VCOM
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
        uint8_t FORMAT = COG_initialData[offset] & 0x80;
        uint8_t REPEAT = COG_initialData[offset] & 0x7f;

        // typedef struct
        // {
        //     uint8_t FORMAT_REPEAT;   0
        //     uint8_t PHLINI_BSTSWa;   1
        //     uint8_t PHHINI_BSTSWb;   2
        //     uint8_t PHLVAR_DELAYa;   3
        //     uint8_t PHHVAR_DELAYb;   4
        //     uint8_t BSTSWa_RESERVE;  5
        //     uint8_t BSTSWb_RESERVE;  6
        //     uint8_t DELAY_RESERVE;   7
        // } COG_SOFT_START_DEF;

        if (FORMAT > 0) // Format 1
        {
            uint8_t PHL_PHH[2];
            PHL_PHH[0] = COG_initialData[offset + 1]; // PHL_INI
            PHL_PHH[1] = COG_initialData[offset + 2]; // PHH_INI
            uint8_t PHL_VAR = COG_initialData[offset + 3];
            uint8_t PHH_VAR = COG_initialData[offset + 4];
            uint8_t BST_SW_a = COG_initialData[offset + 5] & _filter09;
            uint8_t BST_SW_b = COG_initialData[offset + 6] & _filter09;
            uint8_t DELAY_SCALE = COG_initialData[offset + 7] & 0x80;
            uint16_t DELAY_VALUE = COG_initialData[offset + 7] & 0x7f;

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
            uint8_t BST_SW_a = COG_initialData[offset + 1] & _filter09;
            uint8_t BST_SW_b = COG_initialData[offset + 2] & _filter09;
            uint8_t DELAY_a_SCALE = COG_initialData[offset + 3] & 0x80;
            uint16_t DELAY_a_VALUE = COG_initialData[offset + 3] & 0x7f;
            uint8_t DELAY_b_SCALE = COG_initialData[offset + 4] & 0x80;
            uint16_t DELAY_b_VALUE = COG_initialData[offset + 4] & 0x7f;

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
    b_waitBusy();
    b_sendCommandData8(0x15, 0x3c);

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

    // b_waitBusy();
    digitalWrite(b_pin.panelDC, LOW);
    digitalWrite(b_pin.panelCS, HIGH); // CS high = Unselect Master
    digitalWrite(b_pin.panelCS, HIGH); // CSS High = Unselect Slave
}

void Screen_EPD_EXT3::COG_updateLarge()
{
#if (SRAM_MODE == USE_INTERNAL_MCU)

    uint8_t * blackBuffer = u_newImage;
    uint8_t * redBuffer = u_newImage + u_pageColourSize;

#elif (SRAM_MODE == USE_EXTERNAL_SPI)

    uint32_t blackBuffer = u_newImage;
    uint32_t redBuffer = u_newImage + u_pageColourSize;

#endif // SRAM_MODE

    // Application note § 5. Send updating command
    // Application note § 3.3 DC/DC soft-start
    // Application note § 4. Send updating command
    COG_reset();

    if (u_codeDriver == DRIVER_B)
    {
        b_sendCommandDataSelect8(0x01, COG_initialData[0x10], PANEL_CS_BOTH); // DCTL

        // Send image data
        b_sendIndexDataSelect(0x13, &COG_initialData[0x15], 6, PANEL_CS_BOTH); // DUW
        b_sendIndexDataSelect(0x90, &COG_initialData[0x0c], 4, PANEL_CS_BOTH); // DRFW

        // Master
        b_sendIndexDataSelect(0x12, &COG_initialData[0x12], 3, PANEL_CS_MASTER); // RAM_RW

#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x10, blackBuffer, u_frameSize, PANEL_CS_MASTER); // First frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x10, blackBuffer, u_frameSize); // First frame
#endif

        b_sendIndexDataSelect(0x12, &COG_initialData[0x12], 3, PANEL_CS_MASTER); // RAM_RW
#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x11, redBuffer, u_frameSize, PANEL_CS_MASTER); // Second frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x11, redBuffer, u_frameSize, PANEL_CS_MASTER); // Second frame
#endif

        // Slave
        b_sendIndexDataSelect(0x12, &COG_initialData[0x12], 3, PANEL_CS_SLAVE); // RAM_RW
#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x10, blackBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // First frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x10, blackBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // First frame
#endif

        b_sendIndexDataSelect(0x12, &COG_initialData[0x12], 3, PANEL_CS_SLAVE); // RAM_RW
#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x11, redBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // Second frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x11, redBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // Second frame
#endif

        // Initial COG
        b_sendCommandDataSelect8(0x05, 0x7d, PANEL_CS_BOTH);
        delay(200);
        b_sendCommandDataSelect8(0x05, 0x00, PANEL_CS_BOTH);
        delay(10);

        b_sendCommandDataSelect8(0xd8, COG_initialData[0x1c], PANEL_CS_BOTH); // MS_SYNC
        b_sendCommandDataSelect8(0xd6, COG_initialData[0x1d], PANEL_CS_BOTH); // BVSS

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
        b_sendCommandDataSelect8(0x60, COG_initialData[0x0b], PANEL_CS_BOTH); // TCON
        b_sendCommandDataSelect8(0x61, COG_initialData[0x1b], PANEL_CS_MASTER); // STV_DIR Master only
        // No DCTL here
        b_sendCommandDataSelect8(0x02, COG_initialData[0x11], PANEL_CS_BOTH); // VCOM
    }
    else if (u_codeDriver == DRIVER_8)
    {
        // No DCTL here

        // Send image data
        b_sendIndexDataSelect(0x13, &COG_initialData[0x16], 6, PANEL_CS_BOTH); // DUW
        b_sendIndexDataSelect(0x90, &COG_initialData[0x0c], 4, PANEL_CS_BOTH); // DRFW

        // Master
        b_sendIndexDataSelect(0x12, &COG_initialData[0x13], 3, PANEL_CS_MASTER); // RAM_RW

#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x10, blackBuffer, u_frameSize, PANEL_CS_MASTER); // First frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x10, blackBuffer, u_frameSize); // First frame
#endif

        b_sendIndexDataSelect(0x12, &COG_initialData[0x13], 3, PANEL_CS_MASTER); // RAM_RW
#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x11, redBuffer, u_frameSize, PANEL_CS_MASTER); // Second frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x11, redBuffer, u_frameSize, PANEL_CS_MASTER); // Second frame
#endif

        // Slave
        b_sendIndexDataSelect(0x12, &COG_initialData[0x13], 3, PANEL_CS_SLAVE); // RAM_RW
#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x10, blackBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // First frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x10, blackBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // First frame
#endif

        b_sendIndexDataSelect(0x12, &COG_initialData[0x13], 3, PANEL_CS_SLAVE); // RAM_RW
#if (SRAM_MODE == USE_INTERNAL_MCU)
        b_sendIndexDataSelect(0x11, redBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // Second frame
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
        b_sendIndexDataSelectSRAM(0x11, redBuffer + u_frameSize, u_frameSize, PANEL_CS_SLAVE); // Second frame
#endif

        // Initial COG
        b_sendCommandDataSelect8(0x05, 0x7d, PANEL_CS_BOTH);
        delay(200);
        b_sendCommandDataSelect8(0x05, 0x00, PANEL_CS_BOTH);
        delay(10);

        b_sendCommandDataSelect8(0xc2, 0x3f, PANEL_CS_BOTH);
        delay(1);

        b_sendCommandDataSelect8(0xd8, COG_initialData[0x1d], PANEL_CS_BOTH); // MS_SYNC
        b_sendCommandDataSelect8(0xd6, COG_initialData[0x1e], PANEL_CS_BOTH); // BVSS

        b_sendCommandDataSelect8(0xa7, 0x10, PANEL_CS_BOTH);
        delay(100);
        b_sendCommandDataSelect8(0xa7, 0x00, PANEL_CS_BOTH);
        delay(100);

        uint8_t data03[2] = {0x00, COG_initialData[0x12]}; // OSC
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
        b_sendCommandDataSelect8(0x60, COG_initialData[0x0b], PANEL_CS_BOTH); // TCON
        b_sendCommandDataSelect8(0x61, COG_initialData[0x1c], PANEL_CS_MASTER); // STV_DIR Master only
        b_sendCommandDataSelect8(0x01, COG_initialData[0x10], PANEL_CS_BOTH); // DCTL
        b_sendCommandDataSelect8(0x02, COG_initialData[0x11], PANEL_CS_BOTH); // VCOM
    }

    // DC/DC Soft-start
    // Application note § 3.3 DC/DC soft-start
    // DRIVER_B = 0x28, DRIVER_8 = 0x20
    uint8_t offsetFrame = (u_codeDriver == DRIVER_B) ? 0x28 : 0x20;

    // Filter for register 0x09
    uint8_t _filter09;

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
        uint8_t FORMAT = COG_initialData[offset] & 0x80;
        uint8_t REPEAT = COG_initialData[offset] & 0x7f;

        if (FORMAT > 0) // Format 1
        {
            uint8_t PHL_PHH[2];
            PHL_PHH[0] = COG_initialData[offset + 1]; // PHL_INI
            PHL_PHH[1] = COG_initialData[offset + 2]; // PHH_INI
            uint8_t PHL_VAR = COG_initialData[offset + 3];
            uint8_t PHH_VAR = COG_initialData[offset + 4];
            uint8_t BST_SW_a = COG_initialData[offset + 5] & _filter09;
            uint8_t BST_SW_b = COG_initialData[offset + 6] & _filter09;
            uint8_t DELAY_SCALE = COG_initialData[offset + 7] & 0x80;
            uint16_t DELAY_VALUE = COG_initialData[offset + 7] & 0x7f;

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
            uint8_t BST_SW_a = COG_initialData[offset + 1] & _filter09;
            uint8_t BST_SW_b = COG_initialData[offset + 2] & _filter09;
            uint8_t DELAY_a_SCALE = COG_initialData[offset + 3] & 0x80;
            uint16_t DELAY_a_VALUE = COG_initialData[offset + 3] & 0x7f;
            uint8_t DELAY_b_SCALE = COG_initialData[offset + 4] & 0x80;
            uint16_t DELAY_b_VALUE = COG_initialData[offset + 4] & 0x7f;

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
    b_waitBusy();
    b_sendCommandDataSelect8(0x15, 0x3c, PANEL_CS_BOTH);

    // DC/DC off
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

void Screen_EPD_EXT3::COG_updateSmall()
{
    uint8_t * blackBuffer = u_newImage;
    uint8_t * redBuffer = u_newImage + u_pageColourSize;

    // Application note § 5. Send updating command
    // Application note § 3.3 DC/DC soft-start
    // Application note § 4. Send updating command
    COG_reset();

    b_sendCommandData8(0x00, 0x0e); // Soft-reset
    delay(5);

    // Temperature
    b_sendCommandData8(0xe5, u_temperature); // Input Temperature 0°C = 0x00, 22°C = 0x16, 25°C = 0x19
    b_sendCommandData8(0xe0, 0x02); // Active Temperature

    b_sendIndexData(0x00, COG_initialData, 2); // PSR

    // Send image data
#if (SRAM_MODE == USE_INTERNAL_MCU)

    b_sendIndexData(0x10, blackBuffer, u_frameSize); // First frame
    b_sendIndexData(0x13, redBuffer, u_frameSize); // Second frame

#elif (SRAM_MODE == USE_EXTERNAL_SPI)

    b_sendIndexDataSRAM(0x10, blackBuffer, u_frameSize); // First frame
    b_sendIndexDataSRAM(0x13, redBuffer, u_frameSize); // Second frame

#endif // SRAM_MODE

    delay(50);
    b_sendCommand8(0x04); // Power on
    delay(5);
    b_waitBusy();
    b_sendCommand8(0x12); // Display Refresh
    delay(5);
    b_waitBusy();

    // b_sendIndexData(0x02, data8, 1); // Turn off DC/DC
    b_sendCommand8(0x02); // Turn off DC/DC
    b_waitBusy();

    // !!! Suspend
    digitalWrite(b_pin.panelDC, LOW);
    digitalWrite(b_pin.panelCS, LOW);

    digitalWrite(b_pin.panelReset, LOW);

    digitalWrite(b_pin.panelCS, HIGH); // CS# = 1
}

void Screen_EPD_EXT3::COG_powerOff()
{
    // Application note § 6. Turn-off DC/DC
    // Application note § 5. Turn-off DC/DC

}
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
    u_newImage = 0; // nullptr
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

            mySerial.println();
            mySerial.println(formatString("hV * Screen %i-%cS-0%c is not supported", u_codeSize, u_codeFilm, u_codeDriver));
            while (0x01);
            break;
    }

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

    // Check panelCSS for large screens
    if (((u_codeSize == SIZE_969) or (u_codeSize == SIZE_1198)) and (b_pin.panelCSS == NOT_CONNECTED))
    {
        mySerial.println();
        mySerial.println(formatString("hV * Required pin panelCSS is NOT_CONNECTED"));
        while (0x01);
    }

    // Report
    mySerial.println(formatString("hV = Screen %s %ix%i", WhoAmI().c_str(), screenSizeX(), screenSizeY()));
    mySerial.println(formatString("hV = Number %i-%cS-0%c", u_codeSize, u_codeFilm, u_codeDriver));
    mySerial.println(formatString("hV = PDLS %s v%i.%i.%i", SCREEN_EPD_EXT3_VARIANT, SCREEN_EPD_EXT3_RELEASE / 100, (SCREEN_EPD_EXT3_RELEASE / 10) % 10, SCREEN_EPD_EXT3_RELEASE % 10));
    mySerial.println();

    u_bufferDepth = v_screenColourBits; // 2 colours
    u_bufferSizeV = v_screenSizeV; // vertical = wide size
    u_bufferSizeH = v_screenSizeH / 8; // horizontal = small size 112 / 8, 1 bit per pixel

    // Force conversion for two unit16_t multiplication into uint32_t.
    // Actually for 1 colour; BWR requires 2 pages.
    u_pageColourSize = (uint32_t)u_bufferSizeV * (uint32_t)u_bufferSizeH;

    // u_frameSize = u_pageColourSize, except for 9.69 and 11.98
    // 9.69 and 11.98 combine two half-screens, hence two frames with adjusted size
    switch (u_codeSize)
    {
        case SIZE_969: // 9.69"
        case SIZE_B98: // 11.98"

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

    setTemperatureC(25); // 25 Celsius = 77 Fahrenheit
}

String Screen_EPD_EXT3::WhoAmI()
{
    char work[64] = {0};
    u_WhoAmI(work);

    return formatString("iTC %i.%02i\"%s", v_screenDiagonal / 100, v_screenDiagonal % 100, work);
}

void Screen_EPD_EXT3::resume()
{
    b_resume();

    // Check type and get tables
    if (u_flagOTP == false)
    {
        hV_HAL_SPI3_begin(); // Define 3-wire SPI pins
        COG_getDataOTP(); // 3-wire SPI read OTP memory
    }

    // Reset
    COG_reset();

    // Start SPI
    hV_HAL_SPI_begin(); // Standard 8 MHz
}

uint8_t Screen_EPD_EXT3::flushMode(uint8_t updateMode)
{
    updateMode = checkTemperatureMode(updateMode);

    switch (updateMode)
    {
        case UPDATE_FAST:
        case UPDATE_GLOBAL:

            s_flushGlobal();
            break;

        default:

            mySerial.println();
            mySerial.println("hV * UPDATE_NONE invoked");
            break;
    }

    return updateMode;
}

void Screen_EPD_EXT3::flush()
{
    flushMode(UPDATE_GLOBAL);
}

void Screen_EPD_EXT3::s_flushGlobal()
{
    // Three groups:
    // + small: up to 4.37 included
    // + medium: 3.43, 5.65, 5.81 and 7.41
    // + large: 9.69 and 11,98
    // switch..case does not allow variable declarations
    //
    switch (u_codeSize)
    {
        case SIZE_969:
        case SIZE_1198:

            // Initialise
            COG_initialLarge();

            // Send image data
            COG_sendImageDataGlobal();

            // Update
            COG_updateLarge();

            COG_powerOff();
            break;

        case SIZE_343:
        case SIZE_565:
        case SIZE_581:
        case SIZE_741:

            // Initialise
            COG_initialMedium();

            // Send image data
            COG_sendImageDataGlobal();

            // Update
            COG_updateMedium();

            COG_powerOff();
            break;

        default:

            // Initialise
            COG_initialSmall();

            // Send image data
            COG_sendImageDataGlobal();

            // Update
            COG_updateSmall();

            COG_powerOff();
            break;
    }

    digitalWrite(b_pin.panelCS, HIGH); // CS# = 1
}

void Screen_EPD_EXT3::clear(uint16_t colour)
{
    if (colour == myColours.red)
    {
        // physical red 0-1
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
        // physical black 0-0
        memset(u_newImage, 0x00, u_pageColourSize);
        memset(u_newImage + u_pageColourSize, 0x00, u_pageColourSize);
    }
    else
    {
        // physical white 1-0
        memset(u_newImage, 0xff, u_pageColourSize);
        memset(u_newImage + u_pageColourSize, 0x00, u_pageColourSize);
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
        bitClear(u_newImage[z1], b1);
        bitSet(u_newImage[u_pageColourSize + z1], b1);
    }
    else if ((colour == myColours.white) xor u_invert)
    {
        // physical black 0-0
        bitClear(u_newImage[z1], b1);
        bitClear(u_newImage[u_pageColourSize + z1], b1);
    }
    else if ((colour == myColours.black) xor u_invert)
    {
        // physical white 1-0
        bitSet(u_newImage[z1], b1);
        bitClear(u_newImage[u_pageColourSize + z1], b1);
    }
}

void Screen_EPD_EXT3::s_setOrientation(uint8_t orientation)
{
    v_orientation = orientation % 4;
}

bool Screen_EPD_EXT3::s_orientCoordinates(uint16_t & x, uint16_t & y)
{
    bool _flagResult = RESULT_ERROR; // false = success, true = error
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

