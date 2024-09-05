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
/// * 12. Set debug options
///
/// @author Rei Vilo
/// @date 21 Aug 2024
/// @version 805
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
#if (hV_LIST_CONSTANTS_RELEASE < 801)
#error Required hV_LIST_CONSTANTS_RELEASE 801
#endif // hV_LIST_CONSTANTS_RELEASE

#if (hV_LIST_OPTIONS_RELEASE < 803)
#error Required hV_LIST_OPTIONS_RELEASE 803
#endif // hV_LIST_OPTIONS_RELEASE

#if (hV_LIST_BOARDS_RELEASE < 801)
#error Required hV_LIST_BOARDS_RELEASE 801
#endif // hV_LIST_BOARDS_RELEASE

#if (hV_LIST_SCREENS_RELEASE < 801)
#error Required hV_LIST_SCREENS_RELEASE 801
#endif // hV_LIST_SCREENS_RELEASE

#ifndef hV_CONFIGURATION_RELEASE
///
/// @brief Release
///
#define hV_CONFIGURATION_RELEASE 805

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
/// @name 12. Set debug options
///
/// @see hV_List_Options.h
///

///
/// @brief Type for frame-buffer
/// @details Based on SRAM_MODE selection
///
#define FRAMEBUFFER_TYPE uint8_t *

///
/// @brief Type for string
/// @details Based on STRING_MODE selection
///
#define STRING_TYPE String
#define STRING_CONST_TYPE String

#endif // hV_CONFIGURATION_RELEASE

