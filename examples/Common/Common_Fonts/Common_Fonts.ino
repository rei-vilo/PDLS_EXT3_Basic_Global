///
/// @file Common_Fonts.ino
/// @brief Example of features for basic edition
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Nov 2024
/// @version 810
///
/// @copyright (c) Rei Vilo, 2010-2024
/// @copyright Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
/// @copyright For exclusive use with Pervasive Displays screens
///
/// @see ReadMe.txt for references
/// @n
///

// Screen
#include "PDLS_EXT3_Basic_Global.h"

// SDK
// #include <Arduino.h>
#include "hV_HAL_Peripherals.h"

// Include application, user and local libraries
// #include <SPI.h>

// Configuration
#include "hV_Configuration.h"

// Set parameters

// Define structures and classes

// Define variables and constants
Screen_EPD_EXT3 myScreen(eScreen_EPD_266_CS_0C, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_266_JS_0C, boardRaspberryPiPico_RP2040);

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
        mySerial.print(formatString(" > %i  \r", i));
        delay(1000);
    }
    mySerial.print("         \r");
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

    myScreen.flush();
}

// Add setup code
///
/// @brief Setup
///
void setup()
{
    // mySerial = Serial by default, otherwise edit hV_HAL_Peripherals.h
    mySerial.begin(115200);
    delay(500);
    mySerial.println();
    mySerial.println("=== " __FILE__);
    mySerial.println("=== " __DATE__ " " __TIME__);
    mySerial.println();

    // Start
    mySerial.println("begin... ");
    myScreen.begin();
    mySerial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    mySerial.println("Fonts... ");
    myScreen.clear();
    displayFonts();
    wait(8);

    mySerial.println("White... ");
    myScreen.clear();
    myScreen.flush();

    mySerial.println("=== ");
    mySerial.println();
}

// Add loop code
///
/// @brief Loop, empty
///
void loop()
{
    delay(1000);
}
