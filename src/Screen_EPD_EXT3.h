///
/// @file Screen_EPD_EXT3.h
/// @brief Driver for Pervasive Displays iTC monochrome and colour screens and EXT3 board
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n @b B-SML-G
/// * Edition: Basic
/// * Family: Small, Medium, Large
/// * Update: Global
/// * Feature: none
///
/// @author Rei Vilo
/// @date 20 Apr 2023
/// @version 608
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
///
/// The highView Library Suite is shared under the Creative Commons licence Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
///
/// @see https://creativecommons.org/licenses/by-sa/4.0/
///
/// @n Consider the Evaluation or Commercial editions for professionals or organisations and for commercial usage
///

// SDK
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#else // Arduino general
#include "Arduino.h"
#endif // SDK

// Configuration
#include "hV_Configuration.h"

#if (hV_CONFIGURATION_RELEASE < 600)
#error Required hV_CONFIGURATION_RELEASE 600
#endif // hV_CONFIGURATION_RELEASE

#ifndef SCREEN_EPD_EXT3_RELEASE
///
/// @brief Library release number
///
#define SCREEN_EPD_EXT3_RELEASE 608

// Other libraries
#include "SPI.h"
#include "hV_Screen_Buffer.h"

#if (hV_SCREEN_BUFFER_RELEASE < 523)
#error Required hV_SCREEN_BUFFER_RELEASE 523
#endif // hV_SCREEN_BUFFER_RELEASE

// Objects
//
///
/// @brief Class for Pervasive Displays iTC monochome and colour screens
/// @details Screen controllers
/// * LCD: proprietary, SPI
/// * touch: no touch
/// * fonts: no external Flash
///
/// @note All commands work on the frame-buffer,
/// to be displayed on screen with flush()
///
class Screen_EPD_EXT3 final : public hV_Screen_Buffer
{
  public:
    ///
    /// @brief Constructor with default pins
    /// @param eScreen_EPD_EXT3 size and model of the e-screen
    /// @param board board configuration
    /// @note To be used with begin() with no parameter
    ///
    Screen_EPD_EXT3(eScreen_EPD_EXT3_t eScreen_EPD_EXT3, pins_t board);

    ///
    /// @brief Initialisation
    /// @note Frame-buffer generated internally, not suitable for FRAM
    /// @warning begin() initialises SPI and I2C
    ///
    void begin();

    ///
    /// @brief Who Am I
    /// @return Who Am I string
    ///
    String WhoAmI();

    ///
    /// @brief Clear the screen
    /// @param colour default = white
    /// @note Clear next frame-buffer
    ///
    void clear(uint16_t colour = myColours.white);

    ///
    /// @brief Invert screen
    /// @param flag true to invert, false for normal screen
    ///
    void invert(bool flag);

    ///
    /// @brief Update the display, global update
    /// @note Send the frame-buffer to the screen and refresh the screen
    ///
    void flush();

    ///
    /// @brief Regenerate the panel
    /// @details White-to-black-to-white cycle to reduce ghosting
    ///
    void regenerate();

    ///
    /// @brief Draw pixel
    /// @param x1 point coordinate, x-axis
    /// @param y1 point coordinate, y-axis
    /// @param colour 16-bit colour
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    void point(uint16_t x1, uint16_t y1, uint16_t colour);

    ///
    /// @brief Read pixel colour
    /// @param x1 point coordinate, x-axis
    /// @param y1 point coordinate, y-axis
    /// @return 16-bit colour, bits 15-11 red, bits 10-5 green, bits 4-0 blue
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    uint16_t readPixel(uint16_t x1, uint16_t y1);

  protected:
    /// @cond

    ///
    /// @brief General reset
    /// @param ms1 delay after PNLON_PIN, ms
    /// @param ms2 delay after RESET_PIN HIGH, ms
    /// @param ms3 delay after RESET_PIN LOW, ms
    /// @param ms4 delay after RESET_PIN HIGH, ms
    /// @param ms5 delay after CS_PIN CSS_PIN HIGH, ms
    ///
    void _reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5);

    // * Virtual =0 compulsory functions
    // Screen-specific
    ///
    /// @brief Send data through SPI
    /// @param index register
    /// @param data data
    /// @param size number of bytes
    /// @note Valid for all except large screens
    ///
    void _sendIndexData(uint8_t index, const uint8_t * data, uint32_t size);

    ///
    /// @brief Send data through SPI to first half of large screens
    /// @param index register
    /// @param data data
    /// @param size number of bytes
    /// @note Valid only for 9.7 and 12.20" screens
    ///
    void _sendIndexDataMaster(uint8_t index, const uint8_t * data, uint32_t size);

    /// @brief Send data through SPI to second half of large screens
    /// @param index register
    /// @param data data
    /// @param size number of bytes
    /// @note Valid only for 9.7 and 12.20" screens
    ///
    void _sendIndexDataSlave(uint8_t index, const uint8_t * data, uint32_t size);

    // Orientation
    ///
    /// @brief Set orientation
    /// @param orientation 1..3, 6, 7
    ///
    void _setOrientation(uint8_t orientation); // compulsory

    ///
    /// @brief Check and orient coordinates, logical coordinates
    /// @param x x-axis coordinate, modified
    /// @param y y-axis coordinate, modified
    /// @return false = success, true = error
    ///
    bool _orientCoordinates(uint16_t & x, uint16_t & y); // compulsory

    // Position

    // Write and Read
    /// @brief Set point
    /// @param x1 x coordinate
    /// @param y1 y coordinate
    /// @param colour 16-bit colour
    /// @n @b More: @ref Colour, @ref Coordinate
    ///
    void _setPoint(uint16_t x1, uint16_t y1, uint16_t colour);

    /// @brief Get point
    /// @param x1 x coordinate
    /// @param y1 y coordinate
    /// @return colour 16-bit colour
    /// @n @b More: @ref Colour, @ref Coordinate
    ///
    uint16_t _getPoint(uint16_t x1, uint16_t y1);

    ///
    /// @brief Convert
    /// @param x1 x-axis coordinate
    /// @param y1 y-axis coordinate
    /// @return index for _newImage[]
    ///
    uint32_t _getZ(uint16_t x1, uint16_t y1);

    ///
    /// @brief Wait for ready
    /// @details Wait for _pin.panelBusy low
    ///
    void _waitBusy();
    void _sendCommand8(uint8_t command);

    // Energy
    // No energy

    // * Other functions specific to the screen

    // Screen independent variables
    uint8_t * _newImage;
    bool _invert;
    uint16_t _screenSizeV, _screenSizeH;

    // Screen dependent variables
    pins_t _pin;
    eScreen_EPD_EXT3_t _eScreen_EPD_EXT3;
    uint8_t _codeExtra;
    uint8_t _codeSize;
    uint8_t _codeType;
    uint16_t _bufferSizeV, _bufferSizeH, _bufferDepth;
    uint32_t _pageColourSize, _frameSize;

    // === Touch
    // No touch

    /// @endcond
};

#endif // SCREEN_EPD_EXT3_RELEASE
