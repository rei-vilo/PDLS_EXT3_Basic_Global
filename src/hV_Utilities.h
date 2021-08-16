///
/// @file hV_Utilities.h
/// @brief Utilities 
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology 
///
/// @author Rei Vilo
/// @date 11 Jan 2021
/// @version 507
///
/// @copyright (c) Rei Vilo, 2010-2021
/// @copyright Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// The highView Library Suite is shared under the Creative Commons licence Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0).
///
/// * Basic edition: for hobbyists and for personal usage
/// @n Creative Commons Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
///
/// @see https://creativecommons.org/licenses/by-nc-sa/4.0/
///
/// @n Consider the advanced or commercial editions for professionals or organisations and for commercial usage
///

// SDK
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#else // Arduino general
#include "Arduino.h"
#endif // end IDE

#ifndef hV_UTILITIES_RELEASE
///
/// @brief Library release number
///
#define hV_UTILITIES_RELEASE 507

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

///
/// @name Orientation Orientation constants
/// @{
///
#define ORIENTATION_PORTRAIT 6 ///< portrait or vertical, higher than large
#define ORIENTATION_LANDSCAPE 7 ///< landscape or horizontal, larger than high
/// @}
///

///
/// @name Utilities
///
/// @{

///
/// @brief Blocking delay
/// @param ms duration in ms
/// @note delay_ms() is blocking, as it doesn't use delay()
///
void delay_ms(uint32_t ms);

///
/// @brief Cosinus
/// @param degreesX100 angle in degrees, x100
/// @return cosinus value, x100
/// @note This function uses integers only.
///
int32_t cos32x100(int32_t degreesX100);

///
/// @brief Sinus
/// @param degreesX100 angle in degrees, x100
/// @return sinus value, x100
/// @note This function uses integers only.
///
int32_t sin32x100(int32_t degreesX100);

///
/// @brief Convert polar to rectangle coordinates
/// @param[in] centerX circle center, x coordinate
/// @param[in] centerY circle center, y coordinate
/// @param[in] angle angle, degrees 0..360°
/// @param[in] radius radius, pixels
/// @param[out] rectangularX x rectangular coordinate
/// @param[out] rectangularY y rectangular coordinate
///
void convertPolar2Rectangle(uint16_t centerX, uint16_t centerY, uint16_t angle, uint16_t radius, uint16_t & rectangularX, uint16_t & rectangularY);

/// @brief Convert rectangle to polar coordinates
/// @param[in] centerX circle center, x coordinate
/// @param[in] centerY circle center, y coordinate
/// @param[in] rectangularX x rectangular coordinate
/// @param[in] rectangularY y rectangular coordinate
/// @param[out] angle angle in degrees 0..360°
/// @param[out] radius radius in pixels
///
void convertRectangle2Polar(uint16_t centerX, uint16_t centerY, uint16_t rectangularX, uint16_t rectangularY, uint16_t & angle, uint16_t & radius);

///
/// @brief UTF-8 to ISO-8859-1 Converter
/// @param s UTF-8 string, input
/// @return ISO-8859-1 string, output
///
/// @see The Unicode Consortium. The Unicode Standard, Version 6.2.0,
/// (Mountain View, CA: The Unicode Consortium, 2012. ISBN 978-1-936213-07-8)
/// http://www.unicode.org/versions/Unicode6.2.0/
///
String utf2iso(String s);

///
/// @brief Format string
/// @details Based on vsprint
/// @param format format with standard codes
/// @param ... list of values
/// @return string with values formatted
/// @see http://www.cplusplus.com/reference/cstdio/printf/?kw=printf for codes
///
String formatString(const char * format, ...);

///
/// @brief Remove leading and ending characters
/// @param text input text
/// @return trimmed text
/// @note Removed characters are LF CR TAB SPACE '
///
String trimString(String text);

/// @}

///
/// @name Format
/// @brief Utilities to format float, 64-bit unsigned integer, hexadecimal and period into string
/// @{

///
/// @brief Convert hexadecimal to string
/// @param number hexadecimal value
/// @param size total number of digits, default=0=no check
/// @return formated string
///
String htoa(uint32_t number, uint8_t size = 0);

///
/// @brief Convert binary to string
/// @param number binary value
/// @param size total number of digits, default=0=no check
/// @return formated string
///
String btoa(uint32_t number, uint8_t size = 8);

///
/// @brief Convert time is ms to string
/// @param number ms
/// @param size total number of digits, default=0=free size, no check
/// @return formated string with time unit, ms, s, mn, h
/// @note Automatic selection of the time unit: ms, s, mn, h
/// @note In case of insufficient place or overflow, # is returned
///
String ttoa(uint32_t number, uint8_t size = 0);

///
/// @brief Convert int32_t to string
/// @param number value, int32_t, already multiplied by unit
/// @param unit default=1, 10 or 100
/// @param decimal number of decimal digits, default=0
/// @param size total number of digits, default=0=free size, no check
/// @note size >= integer digits + 1 for decimal separator . + decimal=decimal digits
/// @return formated string
/// @note In case of insufficient place or overflow, # is returned
///
String i32toa(int32_t number, int32_t unit = 1, uint8_t decimal = 0, uint8_t size = 0);

///
/// @brief Check value in range
/// @param value value to check
/// @param valueMin range minimum
/// @param valueMax range maximum
/// @return value within range
/// @note Assuming valueMin < valueMax
/// * if value < valueMin, return valueMin
/// * if value > valueMax, return valueMax
/// Otherwise, if valueMin > valueMax, valueMin and valueMax are swapped
///
uint16_t checkRange(uint16_t value, uint16_t valueMin, uint16_t valueMax);

///
/// @brief Update min and max values
/// @param value value to consider
/// @param valueMin minimum value to update if value < valueMin
/// @param valueMax maximum value to update if value > valueMax
/// @note valueMin < valueMax is assumed
///
void setMinMax(uint16_t value, uint16_t & valueMin, uint16_t & valueMax);

///
/// @brief Round-up
/// @param value value to round-up
/// @param modulo modulo
/// @return rounded-up value / modulo
/// @note Examples
/// * roundUp(7, 8) = 1;
/// * roundUp(8, 8) = 1;
/// * roundUp(9, 8) = 2;
///
uint32_t roundUp(uint32_t value, uint16_t modulo);

// Utilities
///
/// @brief Swap number, int16_t
/// @param a first number
/// @param b second number
///
void swap(int16_t & a, int16_t & b);

///
/// @brief Swap number, uint16_t
/// @param a first number
/// @param b second number
///
void swap(uint16_t & a, uint16_t & b);

///
/// @brief Swap number, uint8_t
/// @param a first number
/// @param b second number
///
void swap(uint8_t & a, uint8_t & b);

/// @}

#endif // hV_UTILITIES_RELEASE
