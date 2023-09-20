///
/// @file hV_Utilities_EPD.h
/// @brief Driver for Pervasive Displays EXT3, EXT3-1 and EXT3-Touch boards
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// * Edition: Advanced
///
/// @author Rei Vilo
/// @date 21 Aug 2023
/// @version 700
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright All rights reserved
///
/// * Evaluation edition: for professionals or organisations, no commercial usage
/// * Commercial edition: for professionals or organisations, commercial usage
///

// SDK
#include "hV_HAL_Peripherals.h"

// Configuration
#include "hV_Configuration.h"

// Board
#include "hV_Board.h"

// Utilities
#include "hV_Utilities.h"

// Checks
#if (hV_CONFIGURATION_RELEASE < 700)
#error Required hV_CONFIGURATION_RELEASE 700
#endif // hV_CONFIGURATION_RELEASE

#if (hV_BOARD_RELEASE < 700)
#error Required hV_BOARD_RELEASE 700
#endif // hV_BOARD_RELEASE

#ifndef hV_UTILITIES_EPD_RELEASE
///
/// @brief Library release number
///
#define hV_UTILITIES_EPD_RELEASE 700

// Objects
//
///
/// @brief Class for Pervasive Displays e-paper displays
/// @details Shared common functions and variables
///
class hV_Utilities_EPD : public hV_Board
{
  public:
    hV_Utilities_EPD();

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

    ///
    /// @brief Invert screen
    /// @details Invert black and white colours
    /// @param flag true to invert, false for normal screen
    ///
    void invert(bool flag);

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

    // Screen dependent variables
#if (SRAM_MODE == USE_INTERNAL_MCU)

    uint8_t * _newImage;

#elif (SRAM_MODE == USE_EXTERNAL_SPI)

    uint32_t _newImage;

#endif // SRAM_MODE

    eScreen_EPD_EXT3_t _eScreen_EPD_EXT3;
    int8_t _temperature = 25;
    uint8_t _codeExtra;
    uint8_t _codeSize;
    uint8_t _codeType;
    uint16_t _bufferSizeV, _bufferSizeH, _bufferDepth;
    uint32_t _pageColourSize, _frameSize;
    bool _invert = false;

    /// @endcond
};

#endif // hV_UTILITIES_EPD_RELEASE
