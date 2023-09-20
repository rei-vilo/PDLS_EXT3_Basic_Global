///
/// @file hV_Colours565.h
/// @brief Class Library for 5-6-5 coded colours
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @author Rei Vilo
/// @date 21 Jun 2023
/// @version 611
///
/// @copyright (c) Rei Vilo, 2010-2023
/// @copyright Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
///

// SDK
#include "hV_HAL_Peripherals.h"

#ifndef hV_COLOURS_RELEASE
///
/// @brief Library release number
///
#define hV_COLOURS_RELEASE 611

///
/// @class hV_Colours565
/// @brief for 5-6-5 coded colours = 64K colours
/// @details red: 5 bits, green: 6 bits, blue: 5 bits
///
class hV_Colours565
{
  public:
    ///
    /// @brief Constructor
    ///
    hV_Colours565();

    ///
    /// @name Colours constants
    /// @note Both syntaxes are valid
    /// * myColours.black and
    /// * hV_Colours565::black
    /// with extern hV_Colours565 myColours; declared below
    ///
    // Colours RGB=565                 Red  Green Blue
    //                                 4321054321043210
    /// @{

    static const uint16_t black    = 0b0000000000000000; ///< black
    static const uint16_t white    = 0b1111111111111111; ///< white
    static const uint16_t red      = 0b1111100000000000; ///< red
    static const uint16_t green    = 0b0000011111100000; ///< green
    static const uint16_t blue     = 0b0000000000011111; ///< blue
    static const uint16_t yellow   = 0b1111111111100000; ///< yellow
    static const uint16_t cyan     = 0b0000011111111111; ///< cyan
    static const uint16_t orange   = 0b1111101111100000; ///< orange
    static const uint16_t magenta  = 0b1111100000001111; ///< magenta
    static const uint16_t violet   = 0b1111100000011111; ///< violet
    static const uint16_t grey     = 0b0111101111101111; ///< grey
    static const uint16_t darkGrey = 0b0011100111100111; ///< dark grey
    static const uint16_t brown    = 0b0111100000000000; ///< brown

    /// American-English variants
    static const uint16_t gray     = 0b0111101111101111; ///< American-English variant for grey
    static const uint16_t darkGray = 0b0011100111100111; ///< American-English variant for dark grey

    // e-Paper specific colours
    static const uint16_t darkRed  = 0b0011100000000000; ///< dark red for BWR and BWRY colour screens
    static const uint16_t lightRed = 0b1111100011100011; ///< light red for BWR and BWRY colour screens
    static const uint16_t darkYellow  = 0b0011100011100000; ///< dark yellow for BWRY colour screens
    static const uint16_t lightYellow = 0b1111111111100011; ///< light yellow for BWRY colour screens

    /// @}
};

///
/// @brief Instantiated object
/// @details myColours
///
extern hV_Colours565 myColours;

#endif // hV_COLOURS_RELEASE
