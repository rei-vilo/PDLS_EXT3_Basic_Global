///
/// @file hV_HAL_Peripherals.h
/// @brief Light hardware abstraction layer for peripherals
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
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

#ifndef hV_HAL_PERIPHERALS_RELEASE
///
/// @brief Release
///
#define hV_HAL_PERIPHERALS_RELEASE 805

///
/// @brief SDK library
/// @see References
/// * Arduino SDK https://www.arduino.cc/reference/en/
/// * Energia SDK https://energia.nu/reference/
///
#include <Arduino.h>

///
/// @brief SDK other libraries
///
#include <SPI.h>
#include <Wire.h>

///
/// @brief Other libraries
///
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#define mySerial Serial

///
/// @brief General initialisation
///
void hV_HAL_begin();

///
/// @brief Configure and start SPI
/// @param speed SPI speed in Hz, 8000000 = default
/// @note Other parameters are
/// * Bit order: MSBFIRST
/// * Data mode: SPI_MODE0
/// @note With check for unique initialisation
///
void hV_HAL_SPI_begin(uint32_t speed = 8000000);

///
/// @brief End SPI
/// @note With check for unique deinitialisation
///
void hV_HAL_SPI_end();

///
/// @brief Combined write and read of a single byte
/// @param data byte
/// @return read byte
/// @warning No check for previous initialisation
///
uint8_t hV_HAL_SPI_transfer(uint8_t data);

///
/// @name 3-wire SPI bus
/// @warning
/// * Arduino does not support 3-wire SPI, bit-bang simulation
/// * Viewer: For compatibility only, not implemented in Linux
/// @note hV_HAL_SPI3_begin() sets the pins for 3-wire SPI.
/// @{

#if defined(ENERGIA)

#define SCK 7
#define MOSI 15

#endif // ENERGIA 

///
/// @brief Configure 3-wire SPI
/// @note Select default SCK as clock and MOSI as data (SDIO)
///
void hV_HAL_SPI3_begin();

///
/// @brief Set the 3-wire SPI pins
/// @param pinClock clock, default = SCK
/// @param pinData combined data, default = MOSI
/// @note For manual configuration only
/// @warning SCK and MOSI provided by Arduino SDK
/// * Some boards require manual configuration
///
void hV_HAL_SPI3_define(uint8_t pinClock = SCK, uint8_t pinData = MOSI);

///
/// @brief Read a single byte
/// @return read byte
/// @note Configure the clock pin as output and data pin as input.
/// @warning /CS to be managed externally.
///
uint8_t hV_HAL_SPI3_read();

///
/// @brief Write a single byte
/// @param data byte
/// @note Configure the clock and data pins as output.
/// @warning /CS to be managed externally.
///
void hV_HAL_SPI3_write(uint8_t value);

/// @}

///
/// @name Wire bus
///
/// @{

///
/// @brief Configure and start Wire bus
/// @note Master mode only
/// @note With check for unique initialisation
///
void hV_HAL_Wire_begin();

///
/// @brief End Wire bus
/// @note With check for unique deinitialisation
///
void hV_HAL_Wire_end();

///
/// @brief Combined write and read
///
/// @param[in] address I2C device address
/// @param[in] dataWrite buffer to write
/// @param[in] sizeWrite number of bytes
/// @param[out] dataRead buffer to read
/// @param[in] sizeRead number of bytes
/// @note If sizeRead = 0, no read performed
/// @warning No check for previous initialisation
///
void hV_HAL_Wire_transfer(uint8_t address, uint8_t * dataWrite, size_t sizeWrite, uint8_t * dataRead = 0, size_t sizeRead = 0);

/// @}

#endif // hV_HAL_PERIPHERALS_RELEASE

