///
/// @file hV_List_Boards.h
/// @brief List of boards for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n Content
/// * 2- List of pre-configured boards
///     * 2.1 Recommended boards
///     * 2.2 Other boards
///     * 2.3 Deprecated boards
///
/// @author Rei Vilo
/// @date 21 Nov 2024
/// @version 810
///
/// @copyright (c) Rei Vilo, 2010-2024
/// @copyright All rights reserved
/// @copyright For exclusive use with Pervasive Displays screens
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
/// * Viewer edition: for professionals or organisations
/// @n All rights reserved
///
/// * Documentation
/// @n All rights reserved
///

// SDK
#include "stdint.h"

// Options
#include "hV_List_Options.h"

#ifndef hV_LIST_BOARDS_RELEASE
///
/// @brief Release
///
#define hV_LIST_BOARDS_RELEASE 810

///
/// @brief Not connected pin
///
#define NOT_CONNECTED (uint8_t)0xff

#if (USE_EXT_BOARD == BOARD_EXT3)

///
/// @brief EXT3 board configuration structure
/// @note
/// * Pins 1 to 10 are common to all EXT boards
/// * Other pins are specific to each EXT board, optional or external
///
struct pins_t
{
    // ///< EXT3 and EXT3.1 pin 1 Black -> +3.3V
    // ///< EXT3 and EXT3.1 pin 2 Brown -> SPI SCK
    uint8_t panelBusy; ///< EXT3 and EXT3.1 pin 3 Red
    uint8_t panelDC; ///< EXT3 and EXT3.1 pin 4 Orange
    uint8_t panelReset; ///< EXT3 and EXT3.1 pin 5 Yellow
    // ///< EXT3 and EXT3.1 pin 6 Green -> SPI MISO
    // ///< EXT3 and EXT3.1 pin 7 Blue -> SPI MOSI
    uint8_t flashCS; ///< EXT3 and EXT3.1 pin 8 Violet
    uint8_t panelCS; ///< EXT3 and EXT3.1 pin 9 Grey
    // ///< EXT3 and EXT3.1 pin 10 White -> GROUND
    uint8_t panelCSS; ///< EXT3 and EXT3.1 pin 12 Grey2
    uint8_t flashCSS; ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
    // ///< EXT3-Touch pin 1 Brown -> I2C SDA
    // ///< EXT3-Touch pin 2 Black -> I2C SCL
    uint8_t touchInt; ///< EXT3-Touch pin 3 Red
    uint8_t touchReset; ///< EXT3-Touch pin 4 Orange
    uint8_t panelPower; ///< Optional power circuit
    uint8_t cardCS; ///< Separate SD-card board
    uint8_t cardDetect; ///< Separate SD-card board
};

///
/// @name 2.1 Recommended boards
/// @{

///
/// @brief Arduino Nano Matter with Silicon Labs MGM240P, tested
/// @note Numbers refer to pins
/// @note Recommended board
///
const pins_t boardArduinoNanoMatter =
{
    .panelBusy = 10, ///< EXT3 and EXT3.1 pin 3 Red -> D10
    .panelDC = 9, ///< EXT3 and EXT3.1 pin 4 Orange -> D9
    .panelReset = 8, ///< EXT3 and EXT3.1 pin 5 Yellow -> D8
    .flashCS = 7, ///< EXT3 and EXT3.1 pin 8 Violet -> D7
    .panelCS = 6, ///< EXT3 and EXT3.1 pin 9 Grey -> D6
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = 2, ///< Optional power circuit -> D2
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Raspberry Pi Pico and Pico W with default RP2040 configuration, tested
/// @note Numbers refer to GPIOs, not pins
/// @see https://github.com/earlephilhower/arduino-pico
/// @note Recommended board
///
const pins_t boardRaspberryPiPico_RP2040 =
{
    .panelBusy = 13, ///< EXT3 and EXT3.1 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 and EXT3.1 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 and EXT3.1 pin 5 Yellow -> GP11
    .flashCS = 10, ///< EXT3 and EXT3.1 pin 8 Violet -> GP10
    .panelCS = 17, ///< EXT3 and EXT3.1 pin 9 Grey -> GP17
    .panelCSS = 14, ///< EXT3 and EXT3.1 pin 12 Grey2 -> GP14
    .flashCSS = 15, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> GP15
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
    .panelBusy = 13, ///< EXT3 and EXT3.1 pin 3 Red -> D13 GPIO13
    .panelDC = 12, ///< EXT3 and EXT3.1 pin 4 Orange -> D12 GPIO12
    .panelReset = 11, ///< EXT3 and EXT3.1 pin 5 Yellow -> D11 GPIO11
    .flashCS = 10, ///< EXT3 and EXT3.1 pin 8 Violet -> D10 GPIO10
    .panelCS = 9, ///< EXT3 and EXT3.1 pin 9 Grey -> D9 GPIO9
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
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
    .panelBusy = 27, ///< EXT3 and EXT3.1 pin 3 Red -> GPIO27
    .panelDC = 26, ///< EXT3 and EXT3.1 pin 4 Orange -> GPIO26
    .panelReset = 25, ///< EXT3 and EXT3.1 pin 5 Yellow -> GPIO25
    .flashCS = 33, ///< EXT3 and EXT3.1 pin 8 Violet -> GPIO33
    .panelCS = 32, ///< EXT3 and EXT3.1 pin 9 Grey -> GPIO32
    .panelCSS = 4, ///< EXT3 and EXT3.1 pin 12 Grey2 -> GPIO4
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> GPIO0
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> GPIO10
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> GPIO9
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

/// @}

///
/// @name 2.2 Other boards
/// @{

///
/// @brief Raspberry Pi Pico Arduino Mbed-OS configuration, not recommended, tested
/// @warning Not recommended
/// @deprecated Use boardRaspberryPiPico_RP2040 instead (7.0.0)
/// @see https://github.com/arduino/ArduinoCore-mbed
///
const pins_t boardRaspberryPiPico_Arduino =
{
    .panelBusy = 13, ///< EXT3 and EXT3.1 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 and EXT3.1 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 and EXT3.1 pin 5 Yellow -> GP11
    .flashCS = 10, ///< EXT3 and EXT3.1 pin 8 Violet -> GP10
    .panelCS = 5, ///< EXT3 and EXT3.1 pin 9 Grey -> GP5
    .panelCSS = 14, ///< EXT3 and EXT3.1 pin 12 Grey2 -> GP14
    .flashCSS = 15, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> GP15
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
    .panelBusy = 13, ///< EXT3 and EXT3.1 pin 3 Red -> D13 GPIO13
    .panelDC = 12, ///< EXT3 and EXT3.1 pin 4 Orange -> D12 GPIO12
    .panelReset = 11, ///< EXT3 and EXT3.1 pin 5 Yellow -> D11 GPIO11
    .flashCS = 10, ///< EXT3 and EXT3.1 pin 8 Violet -> D10 GPIO10
    .panelCS = 9, ///< EXT3 and EXT3.1 pin 9 Grey -> D9 GPIO9
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
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
    .panelBusy = 16, ///< EXT3 and EXT3.1 pin 3 Red -> D13 GPIO16
    .panelDC = 15, ///< EXT3 and EXT3.1 pin 4 Orange -> D12 GPIO15
    .panelReset = 7, ///< EXT3 and EXT3.1 pin 5 Yellow -> D11 GPIO7
    .flashCS = 11, ///< EXT3 and EXT3.1 pin 8 Violet -> D10 GPI011
    .panelCS = 31, ///< EXT3 and EXT3.1 pin 9 Grey -> D9 GPIO31
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
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
/// #define SPI_CLOCK_PIN 13 ///< EXT3 and EXT3.1 pin 2 -> 13
/// #define SPI_CLOCK_MISO 11 ///< EXT3 and EXT3.1 pin 6 -> 11
/// #define SPI_CLOCK_MOSI 12 ///< EXT3 and EXT3.1 pin 7 -> 12
/// @endcode
///
const pins_t boardArduinoZero =
{
    .panelBusy = 4, ///< EXT3 and EXT3.1 pin 3 Red
    // On Arduino Zero, pins D4 and D2 are reversed
    .panelDC = 5, ///< EXT3 and EXT3.1 pin 4 Orange
    .panelReset = 6, ///< EXT3 and EXT3.1 pin 5 Yellow
    .flashCS = 7, ///< EXT3 and EXT3.1 pin 8 Violet
    .panelCS = 8, ///< EXT3 and EXT3.1 pin 9 Grey
    .panelCSS = 9, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = 10, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
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
    .panelBusy = 5, ///< EXT3 and EXT3.1 pin 3 Red -> D5
    .panelDC = 4, ///< EXT3 and EXT3.1 pin 4 Orange -> D4
    .panelReset = 3, ///< EXT3 and EXT3.1 pin 5 Yellow -> D3
    .flashCS = 2, ///< EXT3 and EXT3.1 pin 8 Violet -> D2
    .panelCS = 1, ///< EXT3 and EXT3.1 pin 9 Grey -> D1
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2 -> D6
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> D0
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Espressif ESP32-Pico-v4
/// @note Numbers refer to GPIOs not pins
/// @warning Specific SPI port with SCK=14 MISO=12 MOSI=13
///
const pins_t boardESP32PicoKitV4 =
{
    .panelBusy = 27, ///< EXT3 and EXT3.1 pin 3 Red -> GPIO27
    .panelDC = 26, ///< EXT3 and EXT3.1 pin 4 Orange -> GPIO26
    .panelReset = 25, ///< EXT3 and EXT3.1 pin 5 Yellow -> GPIO25
    .flashCS = 33, ///< EXT3 and EXT3.1 pin 8 Violet -> GPIO33
    .panelCS = 32, ///< EXT3 and EXT3.1 pin 9 Grey -> GPIO32
    .panelCSS = 4, ///< EXT3 and EXT3.1 pin 12 Grey2 -> GPIO4
    .flashCSS = 0, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> GPIO0
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
    .panelBusy = 25, ///< EXT3 and EXT3.1 pin 3 Red -> GPIO25
    .panelDC = 26, ///< EXT3 and EXT3.1 pin 4 Orange -> GPIO26
    .panelReset = 32, ///< EXT3 and EXT3.1 pin 5 Yellow -> GPIO32
    .flashCS = 33, ///< EXT3 and EXT3.1 pin 8 Violet -> GPIO33
    .panelCS = 27, ///< EXT3 and EXT3.1 pin 9 Grey -> GPIO27
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2 -> GPIO33
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> GPIO27
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
    .panelBusy = 26, ///< EXT3 and EXT3.1 pin 3 Red -> D0 GPIO26
    .panelDC = 27, ///< EXT3 and EXT3.1 pin 4 Orange -> D1 GPIO27
    .panelReset = 28, ///< EXT3 and EXT3.1 pin 5 Yellow -> D2 GPIO28
    .flashCS = 6, ///< EXT3 and EXT3.1 pin 8 Violet -> D4 GPIO6
    .panelCS = 29, ///< EXT3 and EXT3.1 pin 9 Grey -> D3 GPIO29
    .panelCSS = 7, ///< EXT3 and EXT3.1 pin 12 Grey2 -> D5 GPIO7
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> N/A
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> D6 GPIO0
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> D7 GPIO1
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Silicon Labs EFR32xG24 Explorer Kit (xG24-EK2703A) configuration, tested
/// @note Numbers refer to GPIOs, not pins
/// @see https://github.com/earlephilhower/arduino-pico
/// @note Recommended board
///
const pins_t boardSiLabsBG24Explorer =
{
    .panelBusy = 0x20, ///< EXT3 and EXT3.1 pin 3 Red -> PC00
    .panelDC = 0x28, ///< EXT3 and EXT3.1 pin 4 Orange -> PC08
    .panelReset = 0x10, ///< EXT3 and EXT3.1 pin 5 Yellow -> PB00
    .flashCS = 0x00, ///< EXT3 and EXT3.1 pin 8 Violet -> PA00
    .panelCS = 0x11, ///< EXT3 and EXT3.1 pin 9 Grey -> PB01
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2 -> P.0.
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> P.0.
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> PD05
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> PD04
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief STMicroelectronics Nucleo32 L431KC, tested
/// @warning D7/D8 shared with OSC32_IN/OSC32_OUT
///
const pins_t boardNucleo32L431KC =
{
    .panelBusy = 4, ///< EXT3 and EXT3.1 pin 3 Red
    .panelDC = 5, ///< EXT3 and EXT3.1 pin 4 Orange
    .panelReset = 6, ///< EXT3 and EXT3.1 pin 5 Yellow
    .flashCS = 9, ///< EXT3 and EXT3.1 pin 8 Violet
    .panelCS = 10, ///< EXT3 and EXT3.1 pin 9 Grey
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Teensy 3.x configuration, tested
///
const pins_t boardTeensy3x =
{
    .panelBusy = 14, ///< EXT3 and EXT3.1 pin 3 Red
    .panelDC = 15, ///< EXT3 and EXT3.1 pin 4 Orange
    .panelReset = 16, ///< EXT3 and EXT3.1 pin 5 Yellow
    .flashCS = 17, ///< EXT3 and EXT3.1 pin 8 Violet
    .panelCS = 18, ///< EXT3 and EXT3.1 pin 9 Grey
    .panelCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 20 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

/// @}

///
/// @name 2.3 Deprecated boards
/// @{

///
/// @brief Texas Instruments LaunchPad MSP430 and MSP432 configuration, tested
/// @deprecated Texas Instruments LaunchPad boards are deprecated (8.0.3)
///
const pins_t boardLaunchPad =
{
    .panelBusy = 11, ///< EXT3 and EXT3.1 pin 3 Red -> 11
    .panelDC = 12, ///< EXT3 and EXT3.1 pin 4 Orange -> 12
    .panelReset = 13, ///< EXT3 and EXT3.1 pin 5 Yellow -> 13
    .flashCS = 18, ///< EXT3 and EXT3.1 pin 8 Violet -> 18
    .panelCS = 19, ///< EXT3 and EXT3.1 pin 9 Grey -> 19
    .panelCSS = 39, ///< EXT3 and EXT3.1 pin 12 Grey2 -> 39
    .flashCSS = 38, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> 38
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red -> 8
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange -> 6
    .panelPower = NOT_CONNECTED, ///< Optional power circuit -> 2
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board -> 5
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

///
/// @brief Texas Instruments LaunchPad MSP430FR5994 LaunchPad with SD-card configuration, tested
/// @deprecated Texas Instruments LaunchPad boards are deprecated (8.0.3)
///
const pins_t boardMSP430FR5994 =
{
    .panelBusy = 11, ///< EXT3 and EXT3.1 pin 3 Red
    .panelDC = 12, ///< EXT3 and EXT3.1 pin 4 Orange
    .panelReset = 13, ///< EXT3 and EXT3.1 pin 5 Yellow
    .flashCS = 18, ///< EXT3 and EXT3.1 pin 8 Violet
    .panelCS = 19, ///< EXT3 and EXT3.1 pin 9 Grey
    .panelCSS = 39, ///< EXT3 and EXT3.1 pin 12 Grey2
    .flashCSS = 38, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = 47, ///< Included SD-card
    .cardDetect = 51 ///< Included SD-card
};

///
/// @brief Texas Instruments LaunchPad CC1352 configuration, tested
/// @deprecated Texas Instruments LaunchPad boards are deprecated (8.0.3)
///
const pins_t boardCC1352 =
{
    .panelBusy = 5, ///< EXT3 and EXT3.1 pin 3 Red
    .panelDC = 6, ///< EXT3 and EXT3.1 pin 4 Orange
    .panelReset = 19, ///< EXT3 and EXT3.1 pin 5 Yellow
    .flashCS = 24, ///< EXT3 and EXT3.1 pin 8 Violet
    .panelCS = 26, ///< EXT3 and EXT3.1 pin 9 Grey
    .panelCSS = 37, ///< EXT3 and EXT3.1 pin 12 Grey2 -> 37
    .flashCSS = 27, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> 27
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = NOT_CONNECTED, ///< Optional power circuit
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board
};

/// @}

#elif (USE_EXT_BOARD == BOARD_EXT4)

///
/// @brief EXT4 board configuration structure
/// @note
/// * Pins 1 to 10 are common to all EXT boards
/// * Pins 11 to 20 are specific to EXT4 board
/// * Other pins are optional or external
/// @warning Only valid with EXT4 board
///
struct pins_t
{
    // Shared
    // Common
    // ///< EXT3/EXT3.1/EXT4 pin 1 Black -> +3.3V
    // ///< EXT3/EXT3.1/EXT4 pin 2 Brown -> SPI SCK
    uint8_t panelBusy; ///< EXT3/EXT3.1/EXT4 pin 3 Red
    uint8_t panelDC; ///< EXT3/EXT3.1/EXT4 pin 4 Orange
    uint8_t panelReset; ///< EXT3/EXT3.1/EXT4 pin 5 Yellow
    // ///< EXT3/EXT3.1/EXT4 pin 6 Green -> SPI MISO
    // ///< EXT3/EXT3.1/EXT4 pin 7 Blue -> SPI MOSI
    uint8_t flashCS; ///< EXT3/EXT3.1/EXT4 pin 8 Violet
    uint8_t panelCS; ///< EXT3/EXT3.1/EXT4 pin 9 Grey
    // ///< EXT3/EXT3.1/EXT4 pin 10 White -> GROUND
    // End of Common

    // EXT3, EXT3.1 and EXT3-Touch, EXT4 specific
    uint8_t panelCSS; ///< EXT4 not available
    uint8_t flashCSS; ///< EXT4 pin 16 Yellow
    // ///< EXT4 pin 14 Blue -> I2C SDA
    // ///< EXT4 pin 15 Green -> I2C SCL
    uint8_t touchInt; ///< EXT4 not available
    uint8_t touchReset; ///< EXT4 not available
    uint8_t panelPower; ///< EXT4 pin 11 White
    // End of EXT3, EXT3.1 and EXT3-Touch specific

    // SD-card
    uint8_t cardCS; ///< Separate SD-card board
    uint8_t cardDetect; ///< Separate SD-card board
    // End of SD-card
    // End of Shared

    // EXT4 specific
    uint8_t button; ///< EXT4 pin 12 Grey
    uint8_t ledData; ///< EXT4 pin 13 Violet WS2813C
    // ///< EXT4 pin 14 Blue -> I2C SDA
    // ///< EXT4 pin 15 Green -> I2C SCL
    // ///< EXT4 pin 16 Yellow, see above
    uint8_t nfcFD; ///< EXT4 pin 17 Orange NFC NT3H2111_2211 !Field detect, I2C address = 0x55
    uint8_t imuInt1; ///< EXT4 pin 18 Red LIS2DH12 !INT2, I2C address = 0x19
    uint8_t imuInt2; ///< EXT4 pin 19 Brown LIS2DH12 !INT1, I2C address = 0x19
    uint8_t weatherInt; ///< EXT4 pin 20 Black HDC2080 !INT, I2C address = 0x40
    // End of EXT4 specific
};

///
/// @name 2.1 Recommended boards
/// @{

///
/// @brief Arduino Nano Matter with Silicon Labs MGM240P, tested
/// @details Variant of boardArduinoNanoMatter with panelPower, button and LED for EXT4
/// @note Numbers refer to pins
/// @note Recommended board
///
const pins_t boardArduinoNanoMatter =
{
    .panelBusy = 10, ///< EXT3 and EXT3.1 pin 3 Red -> D10
    .panelDC = 9, ///< EXT3 and EXT3.1 pin 4 Orange -> D9
    .panelReset = 8, ///< EXT3 and EXT3.1 pin 5 Yellow -> D8
    .flashCS = 7, ///< EXT3 and EXT3.1 pin 8 Violet -> D7
    .panelCS = 6, ///< EXT3 and EXT3.1 pin 9 Grey -> D6

    .panelCSS = NOT_CONNECTED, ///< EXT4 not available
    .flashCSS = 5, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2 -> D5
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = 2, ///< EXT4 pin 20 White -> D2
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board

    // EXT4 specific
    .button = 3, // EXT4 pin 12 Grey -> D3
    .ledData = 4, // EXT4 pin 13 Violet WS2813C -> D4
    // ///< EXT4 pin 14 Blue -> I2C SDA
    // ///< EXT4 pin 15 Green -> I2C SCL
    // ///< EXT4 pin 16 Yellow, see above
    .nfcFD = 17, // EXT4 pin 17 Orange NFC NT3H2111_2211 !Field detect, I2C address = 0x55 -> A3
    .imuInt1 = 16, // EXT4 pin 18 Red LIS2DH12 !INT1, I2C address = 0x19 -> A2
    .imuInt2 = 15, // EXT4 pin 19 Brown LIS2DH12 !INT2, I2C address = 0x19 -> A1
    .weatherInt = 14, // EXT4 pin 20 Black HDC2080 !INT, I2C address = 0x40 -> A0
    // End of EXT4 specific
};

///
/// @brief Silicon Labs EFR32xG24 Explorer Kit (xG24-EK2703A) configuration, tested
/// @details Variant of boardSiLabsBG24Explorer with panelPower, button and LED for EXT4
/// @note Numbers refer to pins
/// @note Recommended board
///
const pins_t boardSiLabsBG24Explorer =
{
    .panelBusy = 4, ///< EXT3 and EXT3.1 pin 3 Red -> PC03 D4 4
    .panelDC = 5, ///< EXT3 and EXT3.1 pin 4 Orange -> PC06 D5 5
    .panelReset = 6, ///< EXT3 and EXT3.1 pin 5 Yellow -> PB00 D6 6
    .flashCS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 8 Violet
    .panelCS = 13, ///< EXT3 and EXT3.1 pin 9 Grey -> PB03 A6 13
    .panelCSS = NOT_CONNECTED, ///< EXT4 not available
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT4 not available
    .touchReset = NOT_CONNECTED, ///< EXT4 not available
    .panelPower = 14, ///< EXT4 pin 20 White -> PB04 A7 14
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board

    // EXT4 specific
    .button = 11, // EXT4 pin 12 Grey -> PB01 A4 11
    .ledData = 12, // EXT4 pin 13 Violet WS2813C -> PB02 A5 12
    // ///< EXT4 pin 14 Blue -> I2C SDA
    // ///< EXT4 pin 15 Green -> I2C SCL
    // ///< EXT4 pin 16 Yellow, see above
    .nfcFD = NOT_CONNECTED, // EXT4 pin 17 Orange NFC NT3H2111_2211 !Field detect, I2C address = 0x55
    .imuInt1 = NOT_CONNECTED, // EXT4 pin 18 Red LIS2DH12 !INT1, I2C address = 0x19
    .imuInt2 = NOT_CONNECTED, // EXT4 pin 19 Brown LIS2DH12 !INT2, I2C address = 0x19
    .weatherInt = NOT_CONNECTED // EXT4 pin 20 Black HDC2080 !INT, I2C address = 0x40
    // End of EXT4 specific
};

///
/// @brief Raspberry Pi Pico and Pico W with default RP2040 configuration, tested
/// @details Variant of boardRaspberryPiPico_RP2040 with panelPower, button and LED for EXT4
/// @note Numbers refer to GPIOs, not pins
/// @see https://github.com/earlephilhower/arduino-pico
/// @note Recommended board
///
const pins_t boardRaspberryPiPico_RP2040 =
{
    .panelBusy = 13, ///< EXT3 and EXT3.1 pin 3 Red -> GP13
    .panelDC = 12, ///< EXT3 and EXT3.1 pin 4 Orange -> GP12
    .panelReset = 11, ///< EXT3 and EXT3.1 pin 5 Yellow -> GP11
    .flashCS = 10, ///< EXT3 and EXT3.1 pin 8 Violet -> GP10

    .panelCS = 17, ///< EXT4 pin 9 Grey -> GP17
    .panelCSS = NOT_CONNECTED, ///< EXT4 not available
    .flashCSS = 6, ///< EXT4 pin 20 Black2 -> GP6
    .touchInt = NOT_CONNECTED, ///< EXT4 not available
    .touchReset = NOT_CONNECTED, ///< EXT4 not available
    .panelPower = 14, ///< EXT4 pin 20 White -> GP14
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board

    // EXT4 specific
    .button = 15, // EXT4 pin 12 Grey -> GP15
    .ledData = 2, // EXT4 pin 13 Violet WS2813C -> GP2
    // ///< EXT4 pin 14 Blue -> I2C SDA
    // ///< EXT4 pin 15 Green -> I2C SCL
    // ///< EXT4 pin 16 Yellow, see above
    .nfcFD = 7, // EXT4 pin 17 Orange NFC NT3H2111_2211 !Field detect, I2C address = 0x55 -> GP7
    .imuInt1 = 8, // EXT4 pin 18 Red LIS2DH12 !INT2, I2C address = 0x19 -> GP8
    .imuInt2 = 9, // EXT4 pin 19 Brown LIS2DH12 !INT1, I2C address = 0x19 -> GP9
    .weatherInt = 3 // EXT4 pin 20 Black HDC2080 !INT, I2C address = 0x40 -> GP3
    // End of EXT4 specific
};

/// @}

///
/// @name 2.2 Other boards
/// @{

///
/// @brief Silicon Labs BGM220-EK4314A and BG22-EK4108A Explorer Kit configuration, tested
/// @details Variant of boardSiLabsBGM220Explorer with panelPower, button and LED for EXT4
/// @note Numbers refer to pins
///
const pins_t boardSiLabsBGM220Explorer =
{
    .panelBusy = 4, ///< EXT3 and EXT3.1 pin 3 Red -> PC00 D4 4
    .panelDC = 5, ///< EXT3 and EXT3.1 pin 4 Orange -> PC08 D5 5
    .panelReset = 6, ///< EXT3 and EXT3.1 pin 5 Yellow -> PB00 D6 6
    .flashCS = NOT_CONNECTED, ///< EXT3 and EXT3.1 pin 8 Violet
    .panelCS = 13, ///< EXT3 and EXT3.1 pin 9 Grey -> PB01 A6 13
    .panelCSS = NOT_CONNECTED, ///< EXT4 not available
    .flashCSS = NOT_CONNECTED, ///< EXT3 pin 20 or EXT3.1 pin 11 Black2
    .touchInt = NOT_CONNECTED, ///< EXT3-Touch pin 3 Red
    .touchReset = NOT_CONNECTED, ///< EXT3-Touch pin 4 Orange
    .panelPower = 14, ///< EXT4 pin 20 White -> PA00 A7 14
    .cardCS = NOT_CONNECTED, ///< Separate SD-card board
    .cardDetect = NOT_CONNECTED, ///< Separate SD-card board

    // EXT4 specific
    .button = 11, // EXT4 pin 12 Grey -> PD04 A4 11
    .ledData = 12, // EXT4 pin 13 Violet WS2813C -> PD05 A5 12
    // ///< EXT4 pin 14 Blue -> I2C SDA
    // ///< EXT4 pin 15 Green -> I2C SCL
    // ///< EXT4 pin 16 Yellow, see above
    .nfcFD = NOT_CONNECTED, // EXT4 pin 17 Orange NFC NT3H2111_2211 !Field detect, I2C address = 0x55
    .imuInt1 = NOT_CONNECTED, // EXT4 pin 18 Red LIS2DH12 !INT1, I2C address = 0x19
    .imuInt2 = NOT_CONNECTED, // EXT4 pin 19 Brown LIS2DH12 !INT2, I2C address = 0x19
    .weatherInt = NOT_CONNECTED // EXT4 pin 20 Black HDC2080 !INT, I2C address = 0x40
    // End of EXT4 specific
};

/// @}

///
/// @name 2.3 Deprecated boards
/// @{

/// @}

#endif // USE_EXT_BOARD

#endif // hV_LIST_BOARDS_RELEASE

