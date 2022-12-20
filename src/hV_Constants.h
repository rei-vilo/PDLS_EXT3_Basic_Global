///
/// @file hV_Constants.h
/// @brief Constants for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Dec 2022
/// @version 604

///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright All rights reserved
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
///
/// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///

// SDK
// #include "hV_HAL_Peripherals.h"
#include "stdint.h"

#ifndef hV_CONSTANTS_RELEASE
///
/// @brief Release
///
#define hV_CONSTANTS_RELEASE 604
#endif // hV_CONSTANTS_RELEASE

///
/// @name 1- List of supported Pervasive Displays screens
/// @
/// @note Legacy screens are listed in the corresponding screen libraries
/// @{
///
/// * General parameters
///
/// @brief Specific features
/// @{
#define FEATURE_FAST 0x01 ///< with capacitive touch panel
#define FEATURE_TOUCH 0x02 ///< with embedded fast update 
#define FEATURE_ARMOR 0x04 ///< with protection
/// @}

/// @brief Update mode
/// @{
#define UPDATE_GLOBAL 0x00 ///< Global update, default
#define UPDATE_FAST 0x01 ///< Fast update
#define UPDATE_PARTIAL 0x02 ///< Partial update
/// @}

/// @brief Large screens sub-panels selection
/// @{
#define PANEL_CS_MAIN 0x01 ///< Large screens sub-panels: first panel only
#define PANEL_CS_SECOND 0x02 ///< Large screens sub-panels: second panel only
#define PANEL_CS_BOTH 0x03 ///< Large screens sub-panels: both panels
/// @}

/// @brief Power state
/// @{
#define FSM_POWER_UNKNOWN 0x00 ///< Unknown
#define FSM_POWER_ON 0x01 ///< On
#define FSM_POWER_SLEEP 0x02 ///< Off or sleep
/// @}

/// @brief Partial update state
/// @{
#define PARTIAL_OFF 0x00 ///< non-activated
#define PARTIAL_ON 0x01 ///< activated but not populated
#define PARTIAL_READY 0x02 ///< activated and populated
/// @}

