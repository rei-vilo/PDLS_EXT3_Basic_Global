//
// hV_Utilities_PDLS.cpp
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
#include "hV_Utilities_PDLS.h"

hV_Utilities_PDLS::hV_Utilities_PDLS()
{
    ;
}

void hV_Utilities_PDLS::u_begin(pins_t board, uint8_t family, uint16_t delayCS)
{
    b_begin(board, family, delayCS);
}

void hV_Utilities_PDLS::u_WhoAmI(char * answer)
{
    memcpy(answer, 0x00, strlen(answer));

    if (u_codeExtra > 0)
    {
        strcat(answer, "-");
        if (u_codeExtra & FEATURE_FAST)
        {
            strcat(answer, "F");
        }
        if (u_codeExtra & FEATURE_TOUCH)
        {
            strcat(answer, "T");
        }
        if (u_codeExtra & FEATURE_OTHER)
        {
            strcat(answer, "b");
        }
        if (u_codeExtra & FEATURE_WIDE_TEMPERATURE)
        {
            strcat(answer, "W");
        }
        if (u_codeExtra & FEATURE_RED)
        {
            strcat(answer, "BWR");
        }
        if (u_codeExtra & FEATURE_RED_YELLOW)
        {
            strcat(answer, "BWRY");
        }
        strcat(answer, " ");
    }

    strcat(answer, "-");

#if (SRAM_MODE == USE_INTERNAL_MCU)
    strcat(answer, "i");
#elif (SRAM_MODE == USE_EXTERNAL_SPI)
    strcat(answer, "e");
#else
    strcat(answer, ".");
#endif // SRAM_MODE

#if (FONT_MODE == USE_FONT_HEADER)
    strcat(answer, "H");
#elif (FONT_MODE == USE_FONT_FLASH)
    strcat(answer, "F");
#elif (FONT_MODE == USE_FONT_TERMINAL)
    strcat(answer, "T");
#else
    strcat(answer, ".");
#endif // FONT_MODE
}

void hV_Utilities_PDLS::invert(bool flag)
{
    u_invert = flag;
}

//
// === Temperature section
//
void hV_Utilities_PDLS::setTemperatureC(int8_t temperatureC)
{
    u_temperature = temperatureC;

    // uint8_t u_temperature2;
    // if (u_temperature < 0)
    // {
    //     u_temperature2 = -u_temperature;
    //     u_temperature2 = (uint8_t)(~_temperature2) + 1; // 2's complement
    // }
    // else
    // {
    //     u_temperature2 = u_temperature;
    // }
    // indexE5_data[0] = u_temperature2;
}

void hV_Utilities_PDLS::setTemperatureF(int16_t temperatureF)
{
    int8_t temperatureC = ((temperatureF - 32) * 5) / 9; // C = (F - 32) * 5 / 9
    setTemperatureC(temperatureC);
}

uint8_t hV_Utilities_PDLS::checkTemperatureMode(uint8_t updateMode)
{
    // #define FEATURE_FAST 0x01 ///< With embedded fast update
    // #define FEATURE_TOUCH 0x02 ///< With capacitive touch panel
    // #define FEATURE_OTHER 0x04 ///< With other feature
    // #define FEATURE_WIDE_TEMPERATURE 0x08 ///< With wide operating temperature
    // #define FEATURE_RED 0x10 ///< With red colour
    // #define FEATURE_RED_YELLOW 0x20 ///< With red and yellow colours
    // #define FEATURE_BW 0x00 ///< Monochrome
    // #define FEATURE_BWR 0x10 ///< With red colour
    // #define FEATURE_BWRY 0x20 ///< With red and yellow colours
    // #define FEATURE_HIGH_DEFINITION 0x40 ///< With high definition

    switch (u_codeExtra & 0x19)
    {
        case FEATURE_FAST: // PS series

            // Fast 	PS 	Embedded fast update 	FU: +15 to +30 °C 	GU: 0 to +50 °C
            if (updateMode == UPDATE_FAST) // Fast update
            {
                if ((u_temperature < 15) or (u_temperature > 30))
                {
                    updateMode = UPDATE_GLOBAL;
                }
            }
            if (updateMode == UPDATE_GLOBAL) // Global update
            {
                if ((u_temperature < 0) or (u_temperature > 50))
                {
                    updateMode = UPDATE_NONE;
                }
            }
            break;

        case (FEATURE_FAST | FEATURE_WIDE_TEMPERATURE): // KS series

            // Wide 	KS 	Wide temperature and embedded fast update 	FU: 0 to +50 °C 	GU: -15 to +60 °C
            if (updateMode == UPDATE_FAST) // Fast update
            {
                if ((u_temperature < 0) or (u_temperature > 50))
                {
                    updateMode = UPDATE_GLOBAL;
                }
            }
            if (updateMode == UPDATE_GLOBAL) // Global update
            {
                if ((u_temperature < -15) or (u_temperature > 60))
                {
                    updateMode = UPDATE_NONE;
                }
            }
            break;

        case FEATURE_WIDE_TEMPERATURE: // HS series

            // Freezer 	HS 	Global update below 0 °C 	FU: - 	GU: -25 to +30 °C
            updateMode = UPDATE_GLOBAL;
            if ((u_temperature < -25) or (u_temperature > 30))
            {
                updateMode = UPDATE_NONE;
            }
            break;

        case FEATURE_BWR: // JS series
        // case FEATURE_RED: // JS series
        case FEATURE_BWRY: // QS series
        // case FEATURE_RED_YELLOW: // QS series

            // BWR  JS 	Red colour 	FU: - 	GU: 0 to +40 °C
            // BWRY  QS 	Red and yellow colours 	FU: - 	GU: 0 to +40 °C
            if ((u_temperature < 0) or (u_temperature > 40))
            {
                updateMode = UPDATE_NONE;
            }
            break;

        default: // CS series

            // Normal 	CS 	Global update above 0 °C 	FU: - 	GU: 0 to +50 °C
            updateMode = UPDATE_GLOBAL;
            if ((u_temperature < 0) or (u_temperature > 50))
            {
                updateMode = UPDATE_NONE;
            }
            break;
    }

    return updateMode;
}

