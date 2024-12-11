///
/// @file hV_Utilities_PDLS.h
/// @brief Driver for Pervasive Displays EXT3, EXT3.1, EXT3-Touch and EXT4 boards
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// * Edition: Advanced
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
#include "hV_HAL_Peripherals.h"

// Configuration
#include "hV_Configuration.h"

// Board
#include "hV_Board.h"

// Utilities
#include "hV_Utilities_Common.h"

// Checks
#if (hV_HAL_PERIPHERALS_RELEASE < 810)
#error Required hV_HAL_PERIPHERALS_RELEASE 810
#endif // hV_HAL_PERIPHERALS_RELEASE

#if (hV_CONFIGURATION_RELEASE < 810)
#error Required hV_CONFIGURATION_RELEASE 810
#endif // hV_CONFIGURATION_RELEASE

#if (hV_BOARD_RELEASE < 810)
#error Required hV_BOARD_RELEASE 810
#endif // hV_BOARD_RELEASE

#ifndef hV_UTILITIES_PDLS_RELEASE
///
/// @brief Library release number
///
#define hV_UTILITIES_PDLS_RELEASE 810

// Objects
//
///
/// @brief Class for Pervasive Displays e-paper displays
/// @details Shared common functions and variables
///
class hV_Utilities_PDLS : public hV_Board
{
  public:
    hV_Utilities_PDLS();

    ///
    /// @brief Set temperature in Celsius
    /// @details Set the temperature for update
    /// @param temperatureC temperature in °C, default = 25 °C
    /// @note Refer to data-sheets for authorised operating temperatures
    ///
    void setTemperatureC(int8_t temperatureC = 25);

    ///
    /// @brief Set temperature in Fahrenheit
    /// @details Set the temperature for update
    /// @param temperatureF temperature in °F, default = 77 °F = 25 °C
    /// @note Refer to data-sheets for authorised operating temperatures
    ///
    void setTemperatureF(int16_t temperatureF = 77);

    ///
    /// @brief Check the mode against the temperature
    ///
    /// @param updateMode expected update mode
    /// @return uint8_t recommended mode
    /// @note If required, defaulting to UPDATE_GLOBAL or UPDATE_NONE
    /// @warning Default temperature is 25 °C, otherwise set by setTemperatureC() or setTemperatureF()
    ///
    uint8_t checkTemperatureMode(uint8_t updateMode);

    /// @brief Set the power profile
    /// @param mode default = POWER_MODE_AUTO, otherwise POWER_MODE_MANUAL
    /// @param scope default = POWER_SCOPE_GPIO_ONLY, otherwise POWER_SCOPE_NONE
    /// @note If panelPower is NOT_CONNECTED, (POWER_MODE_AUTO, POWER_SCOPE_GPIO_ONLY) defaults to (POWER_MODE_MANUAL, POWER_SCOPE_NONE)
    ///
    void setPowerProfile(uint8_t mode = POWER_MODE_AUTO, uint8_t scope = POWER_SCOPE_GPIO_ONLY);

    ///
    /// @brief Invert screen
    /// @details Invert black and white colours
    /// @param flag true to invert, false for normal screen
    ///
    void invert(bool flag);

    ///
    /// @brief Get number of colours
    ///
    /// @return uint8_t number of colours
    /// * 2 = monochrome
    /// * 3 = black-white-red or black-white-yellow
    /// * 4 = black-white-red-yellow
    ///
    uint8_t screenColours();

    ///
    /// @brief Screen number
    /// @return Screen number as string
    ///
    virtual STRING_TYPE screenNumber();

    ///
    /// @brief Recommend variant for film
    /// @param uint8_t Context film
    /// @note exit() called after
    ///
    void debugVariant(uint8_t contextFilm);

    /// @cond
  protected:

    ///
    /// @brief Initialisation
    ///
    void u_begin(pins_t board, uint8_t family, uint16_t delayCS);

    ///
    /// @brief Screen extra specifications for WhoAmI()
    /// @param[out] answer Screen extra specifications
    ///
    void u_WhoAmI(char * answer);

    ///
    /// @brief Screen number for screenNumber
    /// @param[out] answer Screen specifications
    /// @note Format is size-film-driver[-Touch|-Demo]
    ///
    void u_screenNumber(char * answer);

    // Screen dependent variables
    eScreen_EPD_t u_eScreen_EPD;
    int8_t u_temperature = 25;
    uint16_t u_codeSize;
    uint8_t u_codeFilm;
    uint8_t u_codeDriver;
    uint8_t u_codeExtra;
    uint16_t u_bufferSizeV, u_bufferSizeH, u_bufferDepth;
    uint32_t u_pageColourSize;
    bool u_invert = false;
    bool u_flagOTP = false;
    uint8_t u_suspendMode = POWER_MODE_AUTO;
    uint8_t u_suspendScope = POWER_SCOPE_GPIO_ONLY;

    /// @endcond
};

#endif // hV_UTILITIES_PDLS_RELEASE
