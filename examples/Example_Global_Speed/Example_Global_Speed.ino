///
/// @file Example_Global_Speed.ino
/// @brief Protocol for speed test
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Mar 2024
/// @version 801
///
/// @copyright (c) Rei Vilo, 2010-2024
/// @copyright Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
/// @copyright For exclusive use with Pervasive Displays screens
///
/// @see ReadMe.md for references
/// @n
///
/// Release 542: First release
/// Release 604: Global and fast variants
/// Release 702: Added xE2150KS0Jx and xE2152KS0Jx
///

// Screen
#include "PDLS_EXT3_Basic_Global.h"
// #include "PDLS_EXT3_Basic_Fast.h"

// SDK
// #include <Arduino.h>
#include "hV_HAL_Peripherals.h"

// Include application, user and local libraries
// #include <SPI.h>

// Configuration
#include "hV_Configuration.h"

// Set parameters

// Define structures and classes

// Define constants and variables
Screen_EPD_EXT3 myScreen(eScreen_EPD_271_CS_09, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3_Fast myScreen(eScreen_EPD_271_PS_09, boardRaspberryPiPico_RP2040);

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
/// @brief Perform the speed test
///
void performTest()
{
    uint32_t chrono;

    myScreen.clear();
    myScreen.setOrientation(ORIENTATION_LANDSCAPE);

    uint16_t x = myScreen.screenSizeX();
    uint16_t y = myScreen.screenSizeY();
    uint16_t dx = 0;
    uint16_t dy = 0;
    uint16_t dz = y / 2;
    String text = "";

    myScreen.selectFont(Font_Terminal12x16);

    // 0
    dy = (dz - myScreen.characterSizeY()) / 2;
    text = myScreen.WhoAmI() + " - " + String(SCREEN_EPD_EXT3_RELEASE);
    mySerial.println(text);
    dx = (x - myScreen.stringSizeX(text)) / 2;
    myScreen.gText(dx, dy, text);
    myScreen.dRectangle(0, dz * 0, x, dz, myColours.black);

    chrono = millis();
    myScreen.flush();
    chrono = millis() - chrono;

    // 1
    dy += dz;
    text = formatString("Global update= %i ms", chrono);
    // text = formatString("Fast update= %i ms", chrono);
    mySerial.println(text);
    dx = (x - myScreen.stringSizeX(text)) / 2;
    myScreen.gText(dx, dy, text);
    myScreen.dRectangle(0, dz * 1, x, dz, myColours.black);

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

    mySerial.println("begin... ");
    myScreen.begin();
    mySerial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    mySerial.println("Speed... ");
    myScreen.clear();
    performTest();
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
