///
/// @file Common_Persistent.ino
/// @brief Example of features for basic edition
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Jan 2023
/// @version 704
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

// --- Global
Screen_EPD_EXT3 myScreen(eScreen_EPD_266_CS_0C, boardRaspberryPiPico_RP2040);
Screen_EPD_EXT3 myScreen(eScreen_EPD_266_JS_0C, boardRaspberryPiPico_RP2040);

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
/// @brief Who am i? test screen
///
void displayPersistent()
{
    myScreen.setOrientation(ORIENTATION_LANDSCAPE);
    myScreen.selectFont(Font_Terminal8x12);
    uint16_t dy = myScreen.characterSizeY();
    uint16_t y = 4;

    myScreen.gText(4, y, myScreen.WhoAmI());
    y += dy;

    myScreen.gText(4, y, formatString("%i x %i", myScreen.screenSizeX(), myScreen.screenSizeY()));
    y += dy;

    myScreen.gText(4, y, formatString("PDLS %s v%i.%i.%i", SCREEN_EPD_EXT3_VARIANT, SCREEN_EPD_EXT3_RELEASE / 100, (SCREEN_EPD_EXT3_RELEASE / 10) % 10, SCREEN_EPD_EXT3_RELEASE % 10));
    y += dy;
    y += dy;

    myScreen.selectFont(Font_Terminal6x8);
    myScreen.gText(4, y, "Unplug when the LED is on");

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

    pinMode(LED_BUILTIN, OUTPUT);
    for (uint8_t i = 1; i < 7; i += 1)
    {
        digitalWrite(LED_BUILTIN, i % 2);
        delay(250);
    }

    mySerial.println("begin... ");
    myScreen.begin();
    mySerial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    mySerial.println("Who Am I... ");
    myScreen.clear();
    displayPersistent();
    wait(2);

    /*
      // To clear the screen
      myScreen.clear();
      myScreen.flush();
    */

    digitalWrite(LED_BUILTIN, HIGH);
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
