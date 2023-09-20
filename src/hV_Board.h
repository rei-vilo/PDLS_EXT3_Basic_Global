///
/// @file hV_Board.h
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

#ifndef hV_BOARD_RELEASE
///
/// @brief Library release number
///
#define hV_BOARD_RELEASE 700

// Objects
//
///
/// @brief Class for Pervasive Displays EXT3, EXT3-1 and EXT3-Touch boards
/// @details Functions for EXT3 board
/// * GPIO
/// * SPI for LCD and external Flash and SRAM memory
/// * I2C for touch and haptic feedback
///
class hV_Board
{
  public:
    ///
    /// @brief Constructor
    ///
    hV_Board();

    ///
    /// @brief Get the pins of the board
    /// @return pins_t pins of the board
    ///
    pins_t getBoardPins();

    /// @cond
  protected:

    ///
    /// @brief Initialisation
    /// @param board board configuration
    /// @param family screen family, default = FAMILY_SMALL
    /// @param delayCS delay for /CS, default = 50 ms
    /// @note Typical values are
    /// + FAMILY_SMALL and 0 ms
    /// + FAMILY_MEDIUM and 50 ms
    /// + FAMILY_LARGE and 50 ms
    ///
    void b_begin(pins_t board, uint8_t family = FAMILY_SMALL, uint16_t delayCS = 50);

    ///
    /// @brief General reset
    /// @param ms1 delay after PNLON_PIN, ms
    /// @param ms2 delay after RESET_PIN HIGH, ms
    /// @param ms3 delay after RESET_PIN LOW, ms
    /// @param ms4 delay after RESET_PIN HIGH, ms
    /// @param ms5 delay after CS_PIN CSS_PIN HIGH, ms
    ///
    void b_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5);

    ///
    /// @brief Send fixed value through SPI
    /// @param index register
    /// @param data data, one byte covers 8 pixels
    /// @param len number of bytes
    /// @note Valid for all except large screens
    ///
    void b_sendIndexFixed(uint8_t index, uint8_t data, uint32_t len);

    ///
    /// @brief Send data through SPI
    /// @param index register
    /// @param data data
    /// @param size number of bytes
    /// @note On large screens, b_sendIndexData() sends to both sub-panels
    ///
    void b_sendIndexData(uint8_t index, const uint8_t * data, uint32_t size);

    ///
    /// @brief Send data through SPI to first half of large screens
    /// @param index register
    /// @param data data
    /// @param size number of bytes
    /// @note Valid only for 9.7 and 12.20" screens
    ///
    void b_sendIndexDataMaster(uint8_t index, const uint8_t * data, uint32_t size);

    /// @brief Send data through SPI to second half of large screens
    /// @param index register
    /// @param data data
    /// @param size number of bytes
    /// @note Valid only for 9.7 and 12.20" screens
    ///
    void b_sendIndexDataSlave(uint8_t index, const uint8_t * data, uint32_t size);

    ///
    /// @brief Wait for ready
    /// @details Wait for panelBusy low
    ///
    void b_waitBusy();

    ///
    /// @brief Send a command
    /// @param command command
    /// @note If needed, set panelCS HIGH manually after
    ///
    void b_sendCommand8(uint8_t command);

    ///
    /// @brief Send a command and ane byte of data
    /// @param command command
    /// @param data uint8_t data
    /// @note panelDC is kept high, to be changed manually after
    ///
    void b_sendCommandData8(uint8_t command, uint8_t data);

    ///
    /// @brief Suspend
    ///
    void b_suspend();

    ///
    /// @brief Resume
    ///
    void b_resume();

    pins_t _pin;
    uint16_t _delayCS = 50; // ms
    uint8_t _family;

    /// @endcond
};

#endif // hV_BOARD_RELEASE

