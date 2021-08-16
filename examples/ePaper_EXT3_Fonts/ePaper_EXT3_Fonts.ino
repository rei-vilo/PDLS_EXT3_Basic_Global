///
/// @file ePaper_EXT3_Palette.ino
/// @brief Example of features for basic edition
///
/// @image html T2_PALET.jpg
/// @image latex T2_PALET.PDF width=10cm
///
/// @details Library for Pervasive Displays EXT3 - Basic edition
///
/// @author Rei Vilo
/// @date 02 Aug 2021
/// @version 507
///
/// @copyright (c) Rei Vilo, 2010-2021
/// @copyright CC = BY SA NC
///
/// @see ReadMe.txt for references
/// @n
///

// SDK
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#else // Arduino general
#include "Arduino.h"
#endif // end IDE

// Set parameters

// Include application, user and local libraries
#include "SPI.h"
#include "PDLS_EXT3_Basic.h"

// #include "hV_Configuration.h"
// #include "hV_Colours565.h"
// #include "hV_Utilities.h"
// #include "ePaper_EXT3_Basic_Library.h"


// Define structures and classes

// Define variables and constants
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_154, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_213, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_266, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_271, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_287, boardLaunchPad);
Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_370, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_417, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_437, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_565, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_581, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_741, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_969, boardLaunchPad);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_B98, boardLaunchPad);

// Prototypes

// Utilities
///
/// @brief Wait with countdown
/// @param second duration, s
///
void wait(uint8_t second)
{
    for (uint8_t i = second; i > 0; i--)
    {
        Serial.print(formatString(" > %i  \r", i));
        delay(1000);
    }
    Serial.print("         \r");
}

///
/// @brief Flush screen and display time
///
void flush_ms()
{
    uint32_t chrono = (uint32_t)millis();
    myScreen.flush();
    Serial.print(millis() - chrono);
    Serial.println(" ms");
}

// Functions
///
/// @brief Fonts test screen
/// @param flag true = default = perform flush, otherwise no
///
/// @image html T2_FONTS..jpg
/// @image latex T2_FONTS.PDF width=10cm
///
void displayFonts(bool flag = true)
{
    uint16_t y = 10;
    myScreen.setOrientation(7);

    // #if (USE_FONT_MODE == USE_FONT_TERMINAL)
    myScreen.selectFont(Font_Terminal12x16);

    myScreen.gText(10, y, myScreen.WhoAmI(), myColours.red);
    y += myScreen.characterSizeY();
    myScreen.gText(10, y, formatString("%i x %i", myScreen.screenSizeX(), myScreen.screenSizeY()), myColours.red);
    y += myScreen.characterSizeY();
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal6x8);
    myScreen.gText(10, y, "Terminal6x8");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal8x12);
    myScreen.gText(10, y, "Terminal8x12");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal12x16);
    myScreen.gText(10, y, "Terminal12x16");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal16x24);
    myScreen.gText(10, y, "Terminal16x24");
    y += myScreen.characterSizeY();

    // #elif (USE_FONT_MODE == USE_FONT_HEADER)
    //
    // #elif (USE_FONT_MODE == USE_FONT_FLASH)
    //
    // #else
    // #error USE_FONT_MODE not defined
    // #endif

    if (flag)
    {
        flush_ms();
    }
}

// Add setup code
///
/// @brief Setup
///
void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println();
    Serial.println("=== " __FILE__);
    Serial.println("=== " __DATE__ " " __TIME__);
    Serial.println();

    Serial.print("begin... ");
    myScreen.begin();
    Serial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    Serial.print("Fonts... ");
    myScreen.clear();
    displayFonts();
    wait(8);

    Serial.print("White... ");
    myScreen.clear();
    flush_ms();

    Serial.println("=== ");
    Serial.println();

#if defined(ARDUINO_ARCH_PIDUINO)
    exit(0);
#endif
}

// Add loop code
///
/// @brief Loop, empty
///
void loop()
{
    delay(1000);
}
