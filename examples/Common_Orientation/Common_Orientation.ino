///
/// @file Common_Orientation.ino
/// @brief Example of features for basic edition
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 20 Mar 2023
/// @version 607
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
///
/// @see ReadMe.txt for references
/// @n
///

// Screen
#include "PDLS_EXT3_Basic.h"

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
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_154, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_213, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_266, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_271, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_287, boardRaspberryPiPico_RP2040);
Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_370, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_417, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_437, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_565, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_581, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_741, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_969, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_B98, boardRaspberryPiPico_RP2040);

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

// Functions
///
/// @brief Orientation test screen
/// @param flag true = default = perform flush, otherwise no
///
/// @image html T2_ORIEN.jpg
/// @image latex T2_ORIEN.PDF width=10cm
///
void displayOrientation(bool flag = true)
{
    myScreen.selectFont(Font_Terminal8x12);

    for (uint8_t i = 0; i < 4; i++)
    {
        myScreen.setOrientation(i);
        myScreen.gText(10, 10, formatString("> Orientation %i", i));
    }

    myScreen.flush();
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

    Serial.println("begin... ");
    myScreen.begin();
    Serial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    Serial.println("Orientation... ");
    myScreen.clear();
    displayOrientation();
    wait(8);

    Serial.println("White... ");
    myScreen.clear();
    myScreen.flush();

    Serial.println("=== ");
    Serial.println();
}

// Add loop code
///
/// @brief Loop, empty
///
void loop()
{
    delay(1000);
}
