//
// hV_Utilities_PDLS.cpp
// Library C++ code
// ----------------------------------
//
// Project Pervasive Displays Library Suite
// Based on highView technology
//
// Created by Rei Vilo, 21 Mar 2024
//
// Copyright (c) Rei Vilo, 2010-2025
// Licence All rights reserved
//
// Release 800: Read OTP memory
// Release 801: Added number of colours
// Release 803: Added types for string and frame-buffer
// Release 804: Improved power management
// Release 805: Improved stability
// Release 806: New library for Wide temperature only
// Release 810: Added support for EXT4 and EPDK-Matter
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
    u_temperature = 25; // Default = 25 °C
}

void hV_Utilities_PDLS::u_WhoAmI(char * answer)
{
    memcpy(answer, 0x00, strlen(answer));

    switch (u_codeFilm)
    {
        case FILM_P: // Film P, Embedded fast update

            strcat(answer, "-Fast");
            break;

        case FILM_K: // Film K, Wide temperature and embedded fast update

            strcat(answer, "-Wide");
            break;

        case FILM_H: // Film H, Freezer

            strcat(answer, "-Freezer");
            break;

        case FILM_J: // Film J, BWR, "Spectra"
        case FILM_E: // Film E, BWR, deprecated
        case FILM_F: // Film F, BWR, deprecated

            strcat(answer, "-BWR");
            break;

        case FILM_G: // Film G, BWY, deprecated

            strcat(answer, "-BWY");
            break;

        case FILM_Q: // Film Q, BWRY, "Spectra 4"

            strcat(answer, "-BWRY");
            break;

        case FILM_C: ///< Film C, Standard

            strcat(answer, "-BW");
            break;

        default:

            strcat(answer, "-?");
            break;
    }

    switch (u_codeExtra)
    {
        case EXTRA_TOUCH:

            strcat(answer, "+Touch");
            break;

        case EXTRA_DEMO:

            strcat(answer, "+Demo");
            break;

        default:

            break;
    }

    strcat(answer, " ");

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

uint8_t hV_Utilities_PDLS::screenColours()
{
    uint8_t result;

    switch (u_codeFilm)
    {
        case FILM_C: // Film C, Standard
        case FILM_P: // Film P, Embedded fast update
        case FILM_K: // Film K, Wide temperature and embedded fast update

            result = 2;
            break;

        case FILM_J: // Film J, BWR, "Spectra"
        case FILM_E: // Film E, BWR, deprecated
        case FILM_F: // Film F, BWR, deprecated
        case FILM_G: // Film G, BWY, deprecated

            result = 3;
            break;

        case FILM_Q: // Film Q, BWRY, "Spectra 4"

            result = 4;
            break;

        default:

            result = 0; // Error
            break;
    }

    return result;
}

void hV_Utilities_PDLS::u_screenNumber(char * answer)
{
    memcpy(answer, 0x00, strlen(answer));

    // strcpy(answer, u_codeSize);
    sprintf(answer, "%i-%cS-0%c", u_codeSize, u_codeFilm, u_codeDriver);

    switch (u_codeExtra)
    {
        case EXTRA_TOUCH:

            strcat(answer, "-Touch");
            break;

        case EXTRA_DEMO:

            strcat(answer, "-Demo");
            break;

        default:

            break;
    }
}

STRING_TYPE hV_Utilities_PDLS::screenNumber()
{
    char work[64] = {0};
    u_screenNumber(work);

    return formatString("%s", work);
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
    switch (u_codeFilm)
    {
        case FILM_P: // Film P, Embedded fast update

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

        case FILM_K: // Film K, Wide temperature and embedded fast update

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

        case FILM_H: // HS series

            // Freezer 	HS 	Global update below 0 °C 	FU: - 	GU: -25 to +30 °C
            updateMode = UPDATE_GLOBAL;
            if ((u_temperature < -25) or (u_temperature > 30))
            {
                updateMode = UPDATE_NONE;
            }
            break;

        case FILM_J: // Film J, BWR, "Spectra"
        case FILM_E: // Film E, BWR, deprecated
        case FILM_F: // Film F, BWR, deprecated
        case FILM_G: // Film G, BWY, deprecated
        case FILM_Q: // Film Q, BWRY, "Spectra 4"

            // BWR  JS 	Red colour 	FU: - 	GU: 0 to +40 °C
            // BWRY  QS 	Red and yellow colours 	FU: - 	GU: 0 to +40 °C
            if ((u_temperature < 0) or (u_temperature > 40))
            {
                updateMode = UPDATE_NONE;
            }
            break;

        default: // Film C, Standard

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

void hV_Utilities_PDLS::setPowerProfile(uint8_t mode, uint8_t scope)
{
    u_suspendMode = mode;
    u_suspendScope = scope;

    if (b_pin.panelPower == NOT_CONNECTED)
    {
        u_suspendMode = POWER_MODE_MANUAL;
        u_suspendScope = POWER_SCOPE_NONE;
    }
}

void hV_Utilities_PDLS::debugVariant(uint8_t contextFilm)
{
    mySerial.println();

    switch (contextFilm)
    {
        case FILM_P: // BW, Embedded fast update

            mySerial.println(formatString("hV * Screen %i-%cS-0%c with no fast update", u_codeSize, u_codeFilm, u_codeDriver));
            break;

        case FILM_K: // BW, wide temperature and embedded fast update

            mySerial.println(formatString("hV * Screen %i-%cS-0%c with no wide temperature and embedded fast update", u_codeSize, u_codeFilm, u_codeDriver));
            break;

        case FILM_Q: // BWRY

            mySerial.println(formatString("hV * Screen %i-%cS-0%c is not black-white-red-yellow", u_codeSize, u_codeFilm, u_codeDriver));
            break;

        default:

            mySerial.println(formatString("hV * Screen %i-%cS-0%c is not supported", u_codeSize, u_codeFilm, u_codeDriver));
            break;
    } // u_codeFilm

    switch (u_codeFilm)
    {
        case FILM_P: // BW, Embedded fast update

            mySerial.println(formatString("hV * Use PDLS_EXT3_%s_%s instead", "Basic", "Fast"));
            break;

        case FILM_K: // BW, wide temperature and embedded fast update

            mySerial.println(formatString("hV * Use PDLS_EXT3_%s_%s instead", "Basic", "Wide"));
            break;

        case FILM_Q: // BWRY

            mySerial.println(formatString("hV * Use PDLS_EXT3_%s_%s instead", "Basic", "BWRY"));
            break;

        default:

            mySerial.println(formatString("hV * Use PDLS_EXT3_%s_%s instead", "Basic", "Global"));
            break;
    } // u_codeFilm

    mySerial.println();
    while (0x01);
}
