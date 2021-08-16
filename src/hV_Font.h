///
/// @file hV_Font.h
/// @brief Font structure
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology 
///
/// @author Rei Vilo
/// @date 02 Aug 2021
/// @version 507
///
/// @copyright (c) Rei Vilo, 2010-2021
/// @copyright All rights reserved
///
/// * Basic edition: for hobbyists and for personal usage
/// @n Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// * Advanced edition: for professionals or organisations, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///
/// @warning 8- and 16-bit limitations
///
/// Some 8- and 16-bit platforms limit arrays to 16 KB. Some header fonts require higher arrays.
/// 
/// - Use a 32-bit platform in that case (USE_FONT_HEADER).
/// - Use small fonts on a 8- and 16-bit platform (USE_FONT_HEADER).
/// - Save the fonts to the external SPI Flash memory (USE_FONT_FLASH).
/// 
/// For the last option, 
/// 
/// - Use hV_Fonts_Manager on a 32-bit platform to save the fonts on the external SPI Flash memory.
/// - Flash the compiled Fonts_3.hex on the external SPI Flash with Segger J-Flash or similar
/// 

// SDK
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#else // Arduino general
#include "Arduino.h"
#endif // end IDE

// Configuration
#include "hV_Configuration.h"

// The Arduino IDE doesn't allow to select the libraries, hence this condition.
#if (FONT_MODE == USE_FONT_TERMINAL)

#ifndef hV_FONT_HEADER_STRUCTURE_RELEASE
///
/// @brief hV_Font release number
///
#define hV_FONT_HEADER_STRUCTURE_RELEASE 401

///
/// @brief Structure for character width
///
struct width_s
{
    uint16_t pixel; ///< width in pixel
    uint16_t index; ///< relative address
};

///
/// @brief Structure for font
/// @note
/// * Kind of font: see details below
/// * Height: set during font generation
/// * Width: *width array: characters index and length
/// * maxWidth: to be calculated
/// * Bytes per character: see *width array
/// * Character definition: see *table array
///
/// @n Font kind
/// * 0x4-..0x1- 0b7654
/// - b7 = 0x8- = high definition, 2 bits per pixel
/// - b6 = 0x4- = Monospace
/// - b5 = 0x2- = Sans Serif
/// - b4 = 0x1- = Serif
/// * 0x-1..0x-f 0b3210
/// - b3 = 0x-8 = d8 = italic
/// - b2 = 0x-4 = d4 = bold
/// - b10 = 0x-0..0x-3 = d0..d3 = variant number
///
/// @bug font_s.table needs to be uint8_t instead of unsigned short
/// @n Otherwise on TM4C129, font_s.table written as uint16_t
///
struct font_s
{
    uint8_t kind; ///< font description
    uint8_t height; ///< general height in pixels
    uint8_t maxWidth; ///< maximum width in pixels from *width array
    uint8_t first; ///< number of first character, usually 32
    uint8_t number; ///< number of characters, usually 96 or 224
};

#endif // USE_FONT_TERMINAL

#endif // hV_FONT_HEADER_STRUCTURE_RELEASE
