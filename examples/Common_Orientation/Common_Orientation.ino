///
/// @file Common_Palette.ino
/// @brief Example of features for basic edition
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 16 Aug 2021
/// @version 508
///
/// @copyright (c) Rei Vilo, 2010-2022
/// @copyright Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
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

    Serial.print("begin... ");
    myScreen.begin();
    Serial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    Serial.print("Orientation... ");
    myScreen.clear();
    displayOrientation();
    wait(8);

    Serial.print("White... ");
    myScreen.clear();
    myScreen.flush();

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
