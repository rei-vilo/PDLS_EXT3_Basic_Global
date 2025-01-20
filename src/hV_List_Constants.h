///
/// @file hV_List_Constants.h
/// @brief List of constants for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Jan 2025
/// @version 812
///
/// @copyright (c) Rei Vilo, 2010-2025
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

#ifndef hV_LIST_CONSTANTS_RELEASE
///
/// @brief Release
///
#define hV_LIST_CONSTANTS_RELEASE 812

///
/// * General parameters
///
/// @name Specific features
/// @note Numbers are bit-based and or-combinable
/// @{
#define FEATURE_FAST 0x01 ///< With embedded fast update
#define FEATURE_TOUCH 0x02 ///< With capacitive touch panel
#define FEATURE_OTHER 0x04 ///< With other feature
#define FEATURE_WIDE_TEMPERATURE 0x08 ///< With wide operating temperature
#define FEATURE_RED 0x10 ///< With red colour
#define FEATURE_RED_YELLOW 0x20 ///< With red and yellow colours
#define FEATURE_BW 0x00 ///< Monochrome
#define FEATURE_BWR 0x10 ///< With red colour
#define FEATURE_BWRY 0x20 ///< With red and yellow colours
#define FEATURE_HIGH_DEFINITION 0x40 ///< With high definition
/// @}

///
/// @name Update mode
/// @note Numbers are sequential and exclusive
/// @deprecated Partial update is removed. Use fast update instead (7.0.0).
/// @{
#define UPDATE_NONE 0x00 ///< No update
#define UPDATE_GLOBAL 0x01 ///< Global update, default
#define UPDATE_FAST 0x02 ///< Fast update
#define UPDATE_PARTIAL 0x03 ///< Partial update, deprecated
/// @}

///
/// @name Screens families
/// @note Numbers are sequential and exclusive
/// @{
#define FAMILY_SMALL 0x01 ///< Small screens
#define FAMILY_MEDIUM 0x02 ///< Medium-sized screens
#define FAMILY_LARGE 0x03 ///< Large screens with two controllers
/// @}

///
/// @name Large screens sub-panels selection
/// @note Numbers are sequential and exclusive
/// @{
#define PANEL_CS_MASTER 0x01 ///< Large screens sub-panels: first panel only
#define PANEL_CS_SLAVE 0x02 ///< Large screens sub-panels: second panel only
#define PANEL_CS_BOTH 0x03 ///< Large screens sub-panels: both panels
/// @}

///
/// @name Scopes for power profile
/// @note Numbers are sequential and exclusive
/// @{
#define POWER_SCOPE_NONE 0x00 ///< Nothing suspended
#define POWER_SCOPE_GPIO_ONLY 0x01 ///< GPIO only and if panelPower defined
#define POWER_SCOPE_BUS_GPIO 0x11 ///< Both bus and GPIO suspended
/// @}

///
/// @name Modes for power profile
/// @note Numbers are sequential and exclusive
/// @{
#define POWER_MODE_AUTO 0x00 ///< Managed by the screen library
#define POWER_MODE_MANUAL 0x01 ///< Managed by the application code
/// @}

///
/// @name Power and GPIO state
/// @note Numbers are sequential and exclusive, except MASK
/// @{
#define FSM_OFF 0x00 ///< Bus off, GPIO off or undefined
#define FSM_ON 0x11 ///< Bus on, GPIO on or defined
#define FSM_SLEEP 0x10 ///< Bus on, GPIO and Power off or undefined
#define FSM_GPIO_MASK 0x01 ///< Mask for GPIO on or defined
#define FSM_BUS_MASK 0x10 ///< Mask for bus on
/// @}

///
/// @name Partial update state
/// @deprecated Use fast update instead (6.1.0).
/// @note Numbers are sequential and exclusive
/// @{
#define PARTIAL_OFF 0x00 ///< Non-activated
#define PARTIAL_ON 0x01 ///< Activated but not populated
#define PARTIAL_READY 0x02 ///< Activated and populated
/// @}

///
/// @name Continuity mode state
/// @note Numbers are sequential and exclusive
///
/// @{
#define CONTINUITY_OFF 0x00 ///< Non-activated
#define CONTINUITY_ON 0x01 ///< Activated but not initialised
#define CONTINUITY_READY 0x02 ///< Activated and initialised
/// @}

///
/// @name Touch events
/// @note Numbers are sequential and exclusive
///
/// @{
#define TOUCH_EVENT_NONE 0 ///< No touch event
#define TOUCH_EVENT_PRESS 1 ///< Touch press event
#define TOUCH_EVENT_RELEASE 2 ///< Touch release event
#define TOUCH_EVENT_MOVE 3 ///< Touch move event
/// @}
///

///
/// @name Results
/// @note Numbers are sequential and exclusive
///
/// @{
#define RESULT_SUCCESS 0 ///< Success
#define RESULT_ERROR 1 ///< Error
/// @}
///

///
/// @name Orientation constants
/// @note Numbers are sequential and exclusive
/// @{
///
#define ORIENTATION_PORTRAIT 6 ///< Portrait or vertical, higher than large
#define ORIENTATION_LANDSCAPE 7 ///< Landscape or horizontal, larger than high
/// @}
///

#endif // hV_LIST_CONSTANTS_RELEASE

