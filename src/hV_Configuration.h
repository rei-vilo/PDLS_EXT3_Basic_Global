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
/// @date 21 Nov 2023
/// @version 702
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
#include "hV_HAL_Peripherals.h"

// List of options
#include "hV_List_Options.h"

// List of constants
#include "hV_List_Constants.h"

// List of boards
#include "hV_List_Boards.h"

// List of screens
#include "hV_List_Screens.h"

// Checks
#if (hV_LIST_CONSTANTS_RELEASE < 700)
#error Required hV_LIST_CONSTANTS_RELEASE 700
#endif // hV_LIST_CONSTANTS_RELEASE

#if (hV_LIST_BOARDS_RELEASE < 700)
#error Required hV_LIST_BOARDS_RELEASE 700
#endif // hV_LIST_BOARDS_RELEASE

#if (hV_LIST_SCREENS_RELEASE < 702)
#error Required hV_LIST_SCREENS_RELEASE 702
#endif // hV_LIST_SCREENS_RELEASE

#ifndef hV_CONFIGURATION_RELEASE
///
/// @brief Release
///
#define hV_CONFIGURATION_RELEASE 702

///
/// @name 1- List of supported Pervasive Displays screens
/// @see hV_List_Screens.h
///

///
/// @name 2- List of pre-configured boards
/// @see hV_List_Boards.h
///

///
/// @name 3- Font mode, internal MCU or external SPI Flash
/// @name 4- Maximum number of fonts
/// @name 5- SRAM memory, internal MCU or external SPI
/// @name 6- Use self or virtual object
/// @name 7- Touch mode, activated or not
/// @name 8- Haptic feedback mode, activated or not
/// @name 9. Set GPIO expander mode, not implemented
/// @name 10. String object of char array options for string.
/// @name 11. Set storage mode, serial console by default
///
/// @see hV_List_Options.h
///

#endif // hV_CONFIGURATION_RELEASE

