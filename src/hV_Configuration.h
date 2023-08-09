///
/// @file hV_Configuration.h
/// @brief Configuration of the options for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n Content
/// * 1- List of supported Pervasive Displays screens
/// * 2- List of pre-configured boards
/// * 3- Font mode, internal MCU for basic edition
/// * 4- Maximum number of fonts
/// * 5- SRAM memory, internal MCU for basic edition
/// * 6- Use self for basic edition
/// * 7- Touch mode, activated or not
/// * 8- Haptic feedback mode, not implemented
/// * 9. Set GPIO expander mode, not implemented
/// * 10. String object for basic edition
/// * 11. Set storage mode, not implemented
///
/// @author Rei Vilo
/// @date 21 Aug 2023
/// @version 613
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright All rights reserved
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
/// @see https://creativecommons.org/licenses/by-sa/4.0/
///
/// @n Consider the Evaluation or Commercial editions for professionals or organisations and for commercial usage
///
/// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///

// SDK
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#else // Arduino general
#include "Arduino.h"
#endif // SDK

// Constants
#include "hV_Constants.h"

#if (hV_CONSTANTS_RELEASE < 607)
#error Required hV_CONSTANTS_RELEASE 607
#endif // hV_CONSTANTS_RELEASE

#ifndef hV_CONFIGURATION_RELEASE
///
/// @brief Release
///
#define hV_CONFIGURATION_RELEASE 613

///
/// @name 1- List of supported Pervasive Displays screens
///
/// @note Legacy screens are listed in the corresponding screen libraries
/// @{
///
#define eScreen_EPD_EXT3_t uint32_t ///< screen type

///
/// * Monochrome screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/
///
#define eScreen_EPD_EXT3_154 (uint32_t)0x1500 ///< reference xE2154CSxxx
#define eScreen_EPD_EXT3_213 (uint32_t)0x2100 ///< reference xE2213CSxxx
#define eScreen_EPD_EXT3_266 (uint32_t)0x2600 ///< reference xE2266CSxxx
#define eScreen_EPD_EXT3_271 (uint32_t)0x2700 ///< reference xE2271CSxxx
#define eScreen_EPD_EXT3_287 (uint32_t)0x2800 ///< reference xE2287CSxxx
#define eScreen_EPD_EXT3_290 (uint32_t)0x2900 ///< reference xE2290CSxxx
#define eScreen_EPD_EXT3_370 (uint32_t)0x3700 ///< reference xE2370CSxxx
#define eScreen_EPD_EXT3_417 (uint32_t)0x4100 ///< reference xE2417CSxxx
#define eScreen_EPD_EXT3_437 (uint32_t)0x4300 ///< reference xE2437CSxxx
#define eScreen_EPD_EXT3_565 (uint32_t)0x5600 ///< reference xE2565CSxxx
#define eScreen_EPD_EXT3_581 (uint32_t)0x580B ///< reference xE2581CS0Bx
#define eScreen_EPD_EXT3_741 (uint32_t)0x740B ///< reference xE2741CS0Bx
#define eScreen_EPD_EXT3_969 (uint32_t)0x960B ///< reference xE2969CS0Bx
#define eScreen_EPD_EXT3_B98 (uint32_t)0xB90B ///< reference xE2B98CS0Bx

///
/// * Colour black-white-red screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/
///
#define eScreen_EPD_EXT3_154_BWR (uint32_t)0x101500 ///< reference xE2154CSxxx
#define eScreen_EPD_EXT3_213_BWR (uint32_t)0x102100 ///< reference xE2213CSxxx
#define eScreen_EPD_EXT3_266_BWR (uint32_t)0x102600 ///< reference xE2266CSxxx
#define eScreen_EPD_EXT3_271_BWR (uint32_t)0x102700 ///< reference xE2271CSxxx
#define eScreen_EPD_EXT3_287_BWR (uint32_t)0x102800 ///< reference xE2287CSxxx
#define eScreen_EPD_EXT3_290_BWR (uint32_t)0x102900 ///< reference xE2290CSxxx
#define eScreen_EPD_EXT3_370_BWR (uint32_t)0x103700 ///< reference xE2370CSxxx
#define eScreen_EPD_EXT3_417_BWR (uint32_t)0x104100 ///< reference xE2417CSxxx
#define eScreen_EPD_EXT3_437_BWR (uint32_t)0x104300 ///< reference xE2437CSxxx
#define eScreen_EPD_EXT3_565_BWR (uint32_t)0x105600 ///< reference xE2565CSxxx
#define eScreen_EPD_EXT3_581_0B_BWR (uint32_t)0x10580B ///< reference xE2581CS0Bx
#define eScreen_EPD_EXT3_741_0B_BWR (uint32_t)0x10740B ///< reference xE2741CS0Bx
#define eScreen_EPD_EXT3_969_0B_BWR (uint32_t)0x10960B ///< reference xE2969CS0Bx
#define eScreen_EPD_EXT3_B98_0B_BWR (uint32_t)0x10B90B ///< reference xE2B98CS0Bx

///
/// * Colour black-white-red-yellow screens
/// @note Global update mode
/// @see https://www.pervasivedisplays.com/products/
///
#define eScreen_EPD_EXT3_154_BWRY (uint32_t)0x20150F ///< reference xE2154QS0Fx
#define eScreen_EPD_EXT3_213_BWRY (uint32_t)0x20210F ///< reference xE2213QS0Fx
#define eScreen_EPD_EXT3_266_BWRY (uint32_t)0x20260F ///< reference xE2266QS0Fx

/// * Monochrome touch screens with embedded fast update
/// @note Global and fast update modes
/// @deprecated Partial update is deprecated. Use fast update instead (6.1.0).
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=tp
///
#define eScreen_EPD_EXT3_271_09_Touch (uint32_t)0x032709 ///< reference xTP271PGH0x
#define eScreen_EPD_EXT3_270_09_Touch (uint32_t)0x032709 ///< reference xTP270PGH0x, legacy name
#define eScreen_EPD_EXT3_370_0C_Touch (uint32_t)0x03370C ///< reference xTP370PGH0x
#define eScreen_EPD_EXT3_270_Touch (uint32_t)0x032709 ///< reference xTP270PGH0x, legacy name
#define eScreen_EPD_EXT3_271_Touch (uint32_t)0x032709 ///< reference xTP271PGH0x, legacy name
#define eScreen_EPD_EXT3_370_Touch (uint32_t)0x03370C ///< reference xTP370PGH0x, legacy name

/// * Monochrome screens with embedded fast update
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_etc_itc=pu
///
#define eScreen_EPD_EXT3_154_0C_Fast (uint32_t)0x01150C ///< reference xE2154PS0Cx
#define eScreen_EPD_EXT3_213_0E_Fast (uint32_t)0x01210E ///< reference xE2213PS0Ex
#define eScreen_EPD_EXT3_266_0C_Fast (uint32_t)0x01260C ///< reference xE2266PS0Cx
#define eScreen_EPD_EXT3_271_09_Fast (uint32_t)0x012709 ///< reference xE2271PS09x
#define eScreen_EPD_EXT3_270_09_Fast (uint32_t)0x012709 ///< reference xE2271PS09x, legacy name
#define eScreen_EPD_EXT3_287_09_Fast (uint32_t)0x012809 ///< reference xE2287PS09x
#define eScreen_EPD_EXT3_370_0C_Fast (uint32_t)0x01370C ///< reference xE2370PS0Cx
#define eScreen_EPD_EXT3_417_0D_Fast (uint32_t)0x01410D ///< reference xE2417PS0Dx
#define eScreen_EPD_EXT3_437_0C_Fast (uint32_t)0x01430C ///< reference xE2437PS0Cx
/// @todo eScreen_EPD_EXT3_581_0B_Fast not tested
#define eScreen_EPD_EXT3_581_0B_Fast (uint32_t)0x01580B ///< reference xE2581PS0Bx, not tested
/// @todo eScreen_EPD_EXT3_741_0B_Fast not tested
#define eScreen_EPD_EXT3_741_0B_Fast (uint32_t)0x01740B ///< reference xE2741PS0Bx, not tested
/// @todo eScreen_EPD_EXT3_969_0B_Fast not tested
#define eScreen_EPD_EXT3_969_0B_Fast (uint32_t)0x01960B ///< reference xE2969PS0Bx, not tested
/// @todo eScreen_EPD_EXT3_B98_0B_Fast not tested
#define eScreen_EPD_EXT3_B98_0B_Fast (uint32_t)0x01B90B ///< reference xE2B98PS0Bx, not tested

/// * Monochrome screens with embedded fast update and wide temperature
/// @note Global and fast update modes
/// @see https://www.pervasivedisplays.com/products/?_sft_temperature_range=m15c-to-p60c
///
#define eScreen_EPD_EXT3_154_0C_Wide (uint32_t)0x09150C ///< reference xE2154KS0Cx
#define eScreen_EPD_EXT3_213_0E_Wide (uint32_t)0x09210E ///< reference xE2213KS0Ex
#define eScreen_EPD_EXT3_266_0C_Wide (uint32_t)0x09260C ///< reference xE2266KS0Cx
#define eScreen_EPD_EXT3_271_09_Wide (uint32_t)0x092709 ///< reference xE2271KS09x
/// @todo eScreen_EPD_EXT3_287_09_Wide not tested
#define eScreen_EPD_EXT3_287_09_Wide (uint32_t)0x092809 ///< reference xE2287PS09x, not tested
#define eScreen_EPD_EXT3_370_0C_Wide (uint32_t)0x09370C ///< reference xE2370KS0Cx
#define eScreen_EPD_EXT3_417_0D_Wide (uint32_t)0x09410D ///< reference xE2417KS0Dx
/// @todo eScreen_EPD_EXT3_437_0C_Wide not tested
#define eScreen_EPD_EXT3_437_0C_Wide (uint32_t)0x09430C ///< reference xE2437KS0Cx, not tested
#define eScreen_EPD_EXT3_581_06_Wide (uint32_t)0x09580B ///< reference xE2581KS0Bx
/// @todo eScreen_EPD_EXT3_741_0B_Wide not tested
#define eScreen_EPD_EXT3_741_0B_Wide (uint32_t)0x09740B ///< reference xE2741KS0Bx, not tested
/// @todo eScreen_EPD_EXT3_969_0B_Wide not tested
#define eScreen_EPD_EXT3_969_0B_Wide (uint32_t)0x09960B ///< reference xE2969KS0Bx, not tested
/// @todo eScreen_EPD_EXT3_B98_0B_Wide not tested
#define eScreen_EPD_EXT3_B98_0B_Wide (uint32_t)0x09B90B ///< reference xE2B98KS0Bx, not tested

///
/// @brief Frame-buffer sizes
/// @details Frame-buffer size = width * height / 8 * depth, uint32_t
/// @n Depth = 2 for black-white-red screens and monochrome screens
///
#define frameSize_EPD_EXT3_150 (uint32_t)(10000)
#define frameSize_EPD_EXT3_154 (uint32_t)(5776)
#define frameSize_EPD_EXT3_213 (uint32_t)(5512)
#define frameSize_EPD_EXT3_266 (uint32_t)(11248)
#define frameSize_EPD_EXT3_270 (uint32_t)(11616) ///< legacy name
#define frameSize_EPD_EXT3_271 (uint32_t)(11616)
#define frameSize_EPD_EXT3_287 (uint32_t)(9472)
#define frameSize_EPD_EXT3_370 (uint32_t)(24960)
#define frameSize_EPD_EXT3_417 (uint32_t)(30000)
#define frameSize_EPD_EXT3_437 (uint32_t)(21120)
#define frameSize_EPD_EXT3_565 (uint32_t)(33600)
#define frameSize_EPD_EXT3_581 (uint32_t)(46080)
#define frameSize_EPD_EXT3_741 (uint32_t)(96000)
#define frameSize_EPD_EXT3_969 (uint32_t)(161280)
#define frameSize_EPD_EXT3_B98 (uint32_t)(184320)
/// @}

///
/// @name 2- List of pre-configured boards
/// @{

///
/// @brief Not connected pin
///
#define NOT_CONNECTED (uint8_t)0xff

///
/// @brief Board configuration structure
///
struct pins_t
{
    // ///< EXT3 and EXT3-1 pin 1 Black -> +3.3V
    // ///< EXT3 and EXT3-1 pin 2 Brown -> SPI SCK
    uint8_t panelBusy; ///< EXT3 and EXT3-1 pin 3 Red
    uint8_t panelDC; ///< EXT3 and EXT3-1 pin 4 Orange
    uint8_t panelReset; ///< EXT3 and EXT3-1 pin 5 Yellow
    // ///< EXT3 and EXT3-1 pin 6 Green -> SPI MISO
    // ///< EXT3 and EXT3-1 pin 7 Blue -> SPI MOSI
    uint8_t flashCS; ///< EXT3 and EXT3-1 pin 8 Violet
    uint8_t panelCS; ///< EXT3 and EXT3-1 pin 9 Grey
    // ///< EXT3 and EXT3-1 pin 10 White -> GROUND
    uint8_t panelCSS; ///< EXT3 and EXT3-1 pin 12 Grey2
    uint8_t flashCSS; ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    // ///< EXT3-Touch pin 1 Brown -> I2C SDA
    // ///< EXT3-Touch pin 2 Black -> I2C SCL
    uint8_t touchInt; ///< EXT3-Touch pin 3 Red
    uint8_t touchReset; ///< EXT3-Touch pin 4 Orange
    uint8_t panelPower; ///< Optional power circuit
    uint8_t cardCS; ///< Separate SD-card board
    uint8_t cardDetect; ///< Separate SD-card board
};

/// * Recommended boards

///
/// @brief Raspberry Pi Pico and Pico W
/// @note Numbers refer to GPIOs, not pins
/// @see https://github.com/earlephilhower/arduino-pico
/// @note Recommended board
///
const pins_t boardRaspberryPiPico_RP2040 =
{
    ///< EXT3 and EXT3-1 pin 1 Black -> +3.3V
    ///< EXT3 and EXT3-1 pin 2 Brown -> SPI SCK GP18
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> GP11
    ///< EXT3 and EXT3-1 pin 6 Green -> SPI MISO GP16
    ///< EXT3 and EXT3-1 pin 7 Blue -> SPI MOSI GP19
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> GP10
    .panelCS = 17, ///< EXT3 and EXT3-1 pin 9 Grey -> GP17
    .panelCSS = 14, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GP14
    .flashCSS = 15, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GP15
    ///< EXT3 and EXT3-1 pin 10 White -> GROUND
    ///< EXT3-Touch pin 1 Brown -> I2C SDA GP5
    ///< EXT3-Touch pin 2 Black -> I2C SCL GP4
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GP2
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GP3
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Adafruit Feather nRF52840 configuration, tested
/// @note Recommended board
///
const pins_t boardFeatherNRF52840 =
{
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> D13 GPIO13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> D12 GPIO12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> D11 GPIO11
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> D10 GPIO10
    .panelCS = 9, ///< EXT3 and EXT3-1 pin 9 Grey -> D9 GPIO9
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D5 GPIO5
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D6 GPIO6
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Espressif ESP32-DevKitC
/// @note Numbers refer to GPIOs not pins
/// @note Recommended board
/// @warning Specific SPI port with SCK=14 MISO=12 MOSI=13
///
const pins_t boardESP32DevKitC =
{
    ///< EXT3 and EXT3-1 pin 1 Black -> +3.3V
    ///< EXT3 and EXT3-1 pin 2 Brown -> SPI SCK GPIO14
    .panelBusy = 27, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO27
    .panelDC = 26, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO26
    .panelReset = 25, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO25
    ///< EXT3 and EXT3-1 pin 6 Green -> SPI MISO GPIO12
    ///< EXT3 and EXT3-1 pin 7 Blue -> SPI MOSI GPIO13
    .flashCS = 33, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO33
    .panelCS = 32, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO32
    .panelCSS = 4, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO4
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO0
    ///< EXT3 and EXT3-1 pin 10 White -> GROUND
    ///< EXT3-Touch pin 1 Brown -> I2C SDA GPIO21
    ///< EXT3-Touch pin 2 Black -> I2C SCL GPIO22
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GPIO10
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GPIO9
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

/// * Other boards

///
/// @brief Texas Instruments LaunchPad MSP430 and MSP432 LaunchPad configuration, tested
///
const pins_t boardLaunchPad =
{
    .panelBusy = 11, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 13, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 18, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 19, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 39, ///< EXT3 and EXT3-1 pin 12 Grey2 -> 39
    .flashCSS = 38, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> 38
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> 8
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> 6
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board -> 5
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Texas Instruments LaunchPad MSP430FR5994 LaunchPad with SD-card configuration, tested
///
const pins_t boardMSP430FR5994 =
{
    .panelBusy = 11, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 13, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 18, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 19, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 39, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = 38, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = 47, ///< Included SD-card
    .cardDetect = 51 ///< Included SD-card
};

///
/// @brief Texas Instruments LaunchPad CC1352 configuration, tested
///
const pins_t boardCC1352 =
{
    .panelBusy = 5, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 6, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 19, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 24, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 26, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 37, ///< EXT3 and EXT3-1 pin 12 Grey2 -> 37
    .flashCSS = 27, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> 27
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Raspberry Pi Zero, 2B, 3B, 4B configuration with RasPiArduino, tested
/// @warning Not recommended
/// @see https://github.com/me-no-dev/RasPiArduino
///
const pins_t boardRaspberryPiZeroB_RasPiArduino =
{
    .panelBusy = 7, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO7 pin 26
    .panelDC = 8, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO8 pin 24
    .panelReset = 25, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO25 pin 22
    .flashCS = 22, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO22 pin 15
    .panelCS = 27, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO27 pin 13
    .panelCSS = 23, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO23 pin 16
    .flashCSS = 24, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO24 pin 18
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Raspberry Pi Pico Arduino mbed configuration, tested
/// @warning Not recommended
/// @see https://github.com/arduino/ArduinoCore-mbed
///
const pins_t boardRaspberryPiPico_Arduino =
{
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> GP11
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> GP10
    .panelCS = 5, ///< EXT3 and EXT3-1 pin 9 Grey -> GP5
    .panelCSS = 14, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GP14
    .flashCSS = 15, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GP15
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GP9
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GP8
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Adafruit Feather M0 and M4 configuration, tested
///
const pins_t boardFeatherM0M4 =
{
    .panelBusy = 13, ///< EXT3 and EXT3-1 pin 3 Red -> D13 GPIO13
    .panelDC = 12, ///< EXT3 and EXT3-1 pin 4 Orange -> D12 GPIO12
    .panelReset = 11, ///< EXT3 and EXT3-1 pin 5 Yellow -> D11 GPIO11
    .flashCS = 10, ///< EXT3 and EXT3-1 pin 8 Violet -> D10 GPIO10
    .panelCS = 9, ///< EXT3 and EXT3-1 pin 9 Grey -> D9 GPIO9
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D5 GPIO5
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D6 GPIO6
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Adafruit Feather nRF52832 configuration, tested
///
const pins_t boardFeatherNRF52832 =
{
    .panelBusy = 16, ///< EXT3 and EXT3-1 pin 3 Red -> D13 GPIO16
    .panelDC = 15, ///< EXT3 and EXT3-1 pin 4 Orange -> D12 GPIO15
    .panelReset = 7, ///< EXT3 and EXT3-1 pin 5 Yellow -> D11 GPIO7
    .flashCS = 11, ///< EXT3 and EXT3-1 pin 8 Violet -> D10 GPI011
    .panelCS = 31, ///< EXT3 and EXT3-1 pin 9 Grey -> D9 GPIO31
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D5 GPIO27
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D6 GPIO30
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Arduino Zero configuration, tested
/// @note In case of use of SERCOM
/// @code {.cpp}
/// #define SPI_CLOCK_PIN 13 ///< EXT3 and EXT3-1 pin 2 -> 13
/// #define SPI_CLOCK_MISO 11 ///< EXT3 and EXT3-1 pin 6 -> 11
/// #define SPI_CLOCK_MOSI 12 ///< EXT3 and EXT3-1 pin 7 -> 12
/// @endcode
///
const pins_t boardArduinoZero =
{
    .panelBusy = 4, ///< EXT3 and EXT3-1 pin 3 Red
    // On Arduino Zero, pins D4 and D2 are reversed
    .panelDC = 5, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 6, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 7, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 8, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = 9, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = 10, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief ST Nucleo 64, tested
///
const pins_t boardNucleo64 = boardArduinoZero;

///
/// @brief Particle Photon configuration, tested
/// @note D6 also CLK/SWCLK with D7 SWD/SWDIO
///
const pins_t boardParticlePhoton =
{
    .panelBusy = 5, ///< EXT3 and EXT3-1 pin 3 Red -> D5
    .panelDC = 4, ///< EXT3 and EXT3-1 pin 4 Orange -> D4
    .panelReset = 3, ///< EXT3 and EXT3-1 pin 5 Yellow -> D3
    .flashCS = 2, ///< EXT3 and EXT3-1 pin 8 Violet -> D2
    .panelCS = 1, ///< EXT3 and EXT3-1 pin 9 Grey -> D1
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2 -> D6
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> D0
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief RedBear Duo configuration, tested
///
const pins_t boardRedBearDuo = boardParticlePhoton;

///
/// @brief Espressif ESP32-Pico-v4
/// @note Numbers refer to GPIOs not pins
/// @warning Specific SPI port with SCK=14 MISO=12 MOSI=13
///
const pins_t boardESP32PicoKitV4 =
{
    .panelBusy = 27, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO27
    .panelDC = 26, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO26
    .panelReset = 25, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO25
    .flashCS = 33, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO33
    .panelCS = 32, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO32
    .panelCSS = 4, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO4
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO0
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GPIO10
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GPIO9
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Espressif ESP32-Pico-DevKitM-2
/// @note Numbers refer to GPIOs not pins
/// @warning Specific SPI port with SCK=14 MISO=12 MOSI=13
///
const pins_t boardESP32PicoDevKitM2 =
{
    .panelBusy = 25, ///< EXT3 and EXT3-1 pin 3 Red -> GPIO25
    .panelDC = 26, ///< EXT3 and EXT3-1 pin 4 Orange -> GPIO26
    .panelReset = 32, ///< EXT3 and EXT3-1 pin 5 Yellow -> GPIO32
    .flashCS = 33, ///< EXT3 and EXT3-1 pin 8 Violet -> GPIO33
    .panelCS = 27, ///< EXT3 and EXT3-1 pin 9 Grey -> GPIO27
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2 -> GPIO33
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> GPIO27
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GPIO19
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GPIO8
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Seeed Xiao RP240
/// @note Numbers refer to GPIOs not pins
///
const pins_t boardXiaoRP2040
{
    .panelBusy = 26, ///< EXT3 and EXT3-1 pin 3 Red -> D0 GPIO26
    .panelDC = 27, ///< EXT3 and EXT3-1 pin 4 Orange -> D1 GPIO27
    .panelReset = 28, ///< EXT3 and EXT3-1 pin 5 Yellow -> D2 GPIO28
    .flashCS = 6, ///< EXT3 and EXT3-1 pin 8 Violet -> D4 GPIO6
    .panelCS = 29, ///< EXT3 and EXT3-1 pin 9 Grey -> D3 GPIO29
    .panelCSS = 7, ///< EXT3 and EXT3-1 pin 12 Grey2 -> D5 GPIO7
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3-1 pin 11 Black2 -> N/A
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D6 GPIO0
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D7 GPIO1
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Teensy 3.x configuration, tested
///
const pins_t boardTeensy3x =
{
    .panelBusy = 14, ///< EXT3 and EXT3-1 pin 3 Red
    .panelDC = 15, ///< EXT3 and EXT3-1 pin 4 Orange
    .panelReset = 16, ///< EXT3 and EXT3-1 pin 5 Yellow
    .flashCS = 17, ///< EXT3 and EXT3-1 pin 8 Violet
    .panelCS = 18, ///< EXT3 and EXT3-1 pin 9 Grey
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 and EXT3-1 pin 20 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

/// @}

///
/// @name 3- Set font mode
/// @details From header files or from external flash
/// * Basic edition: Terminal font
/// * Evaluation edition: DejaVu font as header
/// * Commercial edition: DejaVu font as either header or external SPI Flash
/// @note USE_FONT_HEADER requires addFont()
/// @note Font Manager requires USE_FONT_HEADER
/// @warning 8- and 16-bit MCUs may limit the size of the fonts. Use 32-bit MCUs for optimal performance.
///
/// @{
#define USE_FONT_TERMINAL 1 ///< Use default Terminal fonts

#define FONT_MODE USE_FONT_TERMINAL ///< Selected option
/// @}

///
/// @brief 4- Maximum number of fonts
/// @details With MCU Flash, based on available memory, check performed at compilation
/// * USE_FONT_TERMINAL: 1..4
/// * USE_FONT_HEADER: 1..64
///
/// With SPI Flash, based on the fonts previously uploaded
/// * USE_FONT_FLASH: eg. 64
///
#if (FONT_MODE == USE_FONT_TERMINAL)
#define MAX_FONT_SIZE 4
#else
#define MAX_FONT_SIZE 64
#endif

///
/// @name 5- Set SRAM memory
/// @details From internal MCU or external SPI
/// * Basic edition: MCU internal SRAM
/// * Commercial edition: MCU internal SRAM
/// * Evaluation edition: MCU internal or SPI external SRAM
///
/// @{
#define USE_INTERNAL_MCU 1 ///< Use MCU internal

#define SRAM_MODE USE_INTERNAL_MCU ///< Selected option
/// @}

///
/// @name 6- Use virtual object
/// @details From hV_Screen_Virtual.h for extended compability
/// @note Declare additional variables if USE_hV_SCREEN_SELF
/// @n Virtual object requires ~1 kB bytes.
/// * Basic edition: self option
/// * Evaluation edition: virtual option
/// * Commercial edition: self and virtual options
/// @note Recommended: USE_hV_SCREEN_VIRTUAL
/// @warning Issues with virtual function on arm-none-eabi-g++ 4.9.3: use USE_hV_SCREEN_SELF instead.
/// @{
#define USE_hV_SCREEN_SELF 2 ///< Do not use virtual object

#define USE_hV_SCREEN USE_hV_SCREEN_SELF ///< Selected option
/// @}

///
/// @name 7- Set touch mode
/// @details Only two screens are ready for touch
/// * Basic edition: iTC 2.71 BW and iTC 3.70 BW
/// * Evaluation edition: iTC 2.71 BW and iTC 3.70 BW
/// * Commercial edition: iTC 2.71 BW and iTC 3.70 BW
/// @note Touch uses I2C and polling over interrupt
/// @{
#define USE_TOUCH_NONE 0 ///< Do not use touch
#define USE_TOUCH_YES 1 ///< Use touch

#define TOUCH_MODE USE_TOUCH_NONE ///< Selected option
/// @}

///
/// @brief 8- Set haptic feedback mode
/// * Basic edition: no haptic feedback
/// * Evaluation edition: ERM or LRA
/// * Commercial edition: ERM or LRA
///
/// @{
#define USE_HAPTICS_NONE 0 ///< No motor

#define HAPTICS_MODE USE_HAPTICS_NONE ///< Selected option
/// @}

///
/// @brief 9- Set GPIO expander mode
/// * Basic edition: no expander
/// * Evaluation edition: PCF8574 or PCA9536
/// * Commercial edition: PCF8574 or PCA9536
///
/// @{
#define USE_EXPANDER_NONE 0 ///< No I2C expander

#define EXPANDER_MODE USE_EXPANDER_NONE ///< Selected option
/// @}

///
/// @brief 10- Set string mode
/// * Basic edition: String object
/// * Evaluation edition: char array
/// * Commercial edition: String object or char array
///
/// @{
#define USE_STRING_OBJECT 1

#define STRING_MODE USE_STRING_OBJECT
/// @}

///
/// @brief 11- Storage mode
/// * Basic edition: none
/// * Evaluation edition: none
/// * Commercial edition: option
///
/// @{
#define USE_NONE 0 ///< No storage

#define STORAGE_MODE USE_NONE ///< Selected options
/// @}

#endif // hV_CONFIGURATION_RELEASE
