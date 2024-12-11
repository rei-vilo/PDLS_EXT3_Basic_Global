///
/// @file Common_Text.ino
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
/// @brief Characters test screen
/// @param flag true = default = perform flush, otherwise no
///
/// @image html T2_CHARA.jpg
/// @image latex T2_CHARA.PDF width=10cm
///
void displayCharacters(bool flag = true)
{
    myScreen.setOrientation(7);
    uint16_t x = myScreen.screenSizeX(); // 17
    uint16_t y = myScreen.screenSizeY(); // 14

    // #if (USE_FONT_MODE == USE_FONT_TERMINAL)
    myScreen.selectFont(Font_Terminal8x12);
    // #elif (USE_FONT_MODE == USE_FONT_HEADER)
    //
    // #elif (USE_FONT_MODE == USE_FONT_FLASH)
    //
    // #else
    // #error USE_FONT_MODE not defined
    // #endif

    uint8_t k;
    String text;
    uint16_t dx;

    for (uint8_t i = 1; i < 17; i++)
    {
        myScreen.gText(i * x / 17, 0, formatString(".%x", (i - 1)), myColours.red);
    }
    for (uint8_t j = 2; j < 16; j++)
    {
        myScreen.gText(0, (j - 1)*y / 15, formatString("%x.", (j)), myColours.red);
    }

    for (uint16_t i = 1; i < 17; i++)
    {
        for (uint8_t j = 2; j < 16; j++)
        {
            k = (i - 1) + j * 16;

            text = (String)char(k);
            dx = i * x / 17 + (x / 17 - myScreen.stringSizeX(text)) / 2;
            myScreen.gText(dx, (j - 1)*y / 15, text, myColours.black);
        }
    }

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

    mySerial.println("Characters... ");
    myScreen.clear();
    displayCharacters();
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
