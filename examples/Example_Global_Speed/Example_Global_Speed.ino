///
/// @file Example_Global_Speed.ino
/// @brief Protocol for speed test
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Dec 2022
/// @version 604
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright All Rights Reserved
///
/// @see ReadMe.md for references
/// @n
///
/// Release 542: First release
/// Release 604: Global and fast variants
///

// SDK
#if defined(ENERGIA)  // LaunchPad specific
#include "Energia.h"
#else  // Arduino general
#include "Arduino.h"
#endif  // SDK

// Set parameters

// Include application, user and local libraries
#include "SPI.h"

// Define structures and classes
#include "PDLS_EXT3_Basic.h"
// Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_271, boardRaspberryPiPico_RP2040);
Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_370, boardRaspberryPiPico_RP2040);

// #include "PDLS_EXT3_Basic_Fast.h"
// Screen_EPD_EXT3_Fast myScreen(eScreen_EPD_EXT3_271_09_Fast, boardRaspberryPiPico_RP2040);
// Screen_EPD_EXT3_Fast myScreen(eScreen_EPD_EXT3_370_0C_Fast, boardRaspberryPiPico_RP2040);

uint8_t fontVery, fontLarge, fontMedium, fontSmall;
uint8_t myOrientation = ORIENTATION_LANDSCAPE;

// Prototypes

// Utilities
///
/// @brief Wait with countdown
/// @param second duration, s
///
void wait(uint8_t second) {
  for (uint8_t i = second; i > 0; i--) {
    Serial.print(formatString(" > %i  \r", i));
    delay(1000);
  }
  Serial.print("         \r");
}

// Functions
/// @brief Perform the speed test
void performTest() {
  uint32_t chrono;

  myScreen.clear();
  myScreen.setOrientation(myOrientation);  // ORIENTATION_LANDSCAPE);

  uint16_t x = myScreen.screenSizeX();
  uint16_t y = myScreen.screenSizeY();
  uint16_t dx = 0;
  uint16_t dy = 0;
  uint16_t dz = y / 2;
  String text = "";
  String release = "";

  myScreen.selectFont(fontLarge);

  // 0
  dy = (dz - myScreen.characterSizeY()) / 2;
  text = myScreen.WhoAmI() + " - " + String(SCREEN_EPD_EXT3_RELEASE);
  Serial.println(text);
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
  Serial.println(text);
  dx = (x - myScreen.stringSizeX(text)) / 2;
  myScreen.gText(dx, dy, text);
  myScreen.dRectangle(0, dz * 1, x, dz, myColours.black);

  myScreen.flush();
}

// Add setup code
///
/// @brief Setup
///
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== " __FILE__);
  Serial.println("=== " __DATE__ " " __TIME__);
  Serial.println();

  Serial.print("begin... ");
  myScreen.begin();
  Serial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

  fontLarge = Font_Terminal12x16;
  Serial.println("Speed... ");

  myScreen.clear();
  performTest();
  wait(8);

  Serial.println("White... ");
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
void loop() {
  delay(1000);
}
