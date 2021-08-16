///
/// @file hV_Screen_Buffer.h
/// @brief Class Generic LCD with buffer class library
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

#ifndef hV_SCREEN_BUFFER_RELEASE
///
/// @brief Library release number
///
#define hV_SCREEN_BUFFER_RELEASE 507

#include "hV_Configuration.h"

// Other libraries
#include "hV_Colours565.h"
#include "hV_Utilities.h"

#if (FONT_MODE == USE_FONT_TERMINAL)
#include "hV_Font_Terminal.h"

#else
#error FONT_MODE not defined
#endif // FONT_MODE

///
/// @brief Generic class for buffered LCD
///
#warning USE_hV_SCREEN == USE_hV_SCREEN_SELF
#warning FONT_MODE == USE_FONT_TERMINAL
class hV_Screen_Buffer : protected hV_Font_Terminal
{
  public:
    ///
    /// @brief Constructor
    ///
    hV_Screen_Buffer();

    /// @name General
    /// @{

    ///
    /// @brief Initialisation
    ///
    virtual void begin();

    ///
    /// @brief Request information about the screen
    /// @return string with hardware version
    ///
    virtual String WhoAmI() = 0; // compulsory

    ///
    /// @brief Clear the screen
    /// @param colour 16-bit colour, default = white
    ///
    virtual void clear(uint16_t colour = myColours.black);

    ///
    /// @brief Send frame-buffer to display
    ///
    virtual void flush() = 0; // compulsory

    ///
    /// @brief Set orientation
    /// @param orientation orientation,
    /// * 0 = default
    /// * 1 = right rotated
    /// * 2 = reverse default
    /// * 3 = left rotated
    /// * ORIENTATION_PORTRAIT = 6 = check portrait
    /// * ORIENTATION_LANDSCAPE = 7 = check landscape
    ///
    virtual void setOrientation(uint8_t orientation);

    ///
    /// @brief Get orientation
    /// @return orientation orientation:
    /// * 0 = portrait
    /// * 1 = right rotated landscape
    /// * 2 = reverse portrait
    /// * 3 = left rotated landscape
    ///
    uint8_t getOrientation();

    ///
    /// @brief Screen size, x-axis
    /// @return horizontal size of the screen, in pixels
    /// @note 240 means 240 pixels and thus 0..239 coordinates (decimal)
    ///
    virtual uint16_t screenSizeX();

    ///
    /// @brief Screen size, y-axis
    /// @return vertical size of the screen, in pixels
    /// @note 240 means 240 pixels and thus 0..239 coordinates (decimal)
    ///
    virtual uint16_t screenSizeY();

    ///
    /// @brief Screen size, diagonal
    /// @return diagonal size of the screen, in inches x 100
    /// @note 320 means 3.20"
    ///
    virtual uint16_t screenDiagonal();
    ///

    /// @brief Screen colour depth
    /// @return colour depth, in bits
    /// @note Examples: BW=1, BWR=2, RGB565=16
    ///
    /// @n @b More: @ref Coordinate
    ///
    virtual uint8_t screenColourBits();

    /// @}

    /// @name Graphics
    ///
    /// @{

    ///
    /// @brief Draw circle
    /// @param x0 center, point coordinate, x-axis
    /// @param y0 center, point coordinate, y-axis
    /// @param radius radius
    /// @param colour 16-bit colour
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    virtual void circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t colour);

    ///
    /// @brief Draw line, rectangle coordinates
    /// @param x1 top left coordinate, x-axis
    /// @param y1 top left coordinate, y-axis
    /// @param x2 bottom right coordinate, x-axis
    /// @param y2 bottom right coordinate, y-axis
    /// @param colour 16-bit colour
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    virtual void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);

    ///
    /// @brief Draw line, vector coordinates
    /// @param x0 point coordinate, x-axis
    /// @param y0 point coordinate, y-axis
    /// @param dx length, x-axis
    /// @param dy height, y-axis
    /// @param colour 16-bit colour
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    virtual void dLine(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);

    ///
    /// @brief Set pen opaque
    /// @param flag default = true = opaque = solid, false = wire frame
    ///
    virtual void setPenSolid(bool flag = true);

    ///
    /// @brief Draw triangle, rectangle coordinates
    /// @param x1 first point coordinate, x-axis
    /// @param y1 first point coordinate, y-axis
    /// @param x2 second point coordinate, x-axis
    /// @param y2 second point coordinate, y-axis
    /// @param x3 third point coordinate, x-axis
    /// @param y3 third point coordinate, y-axis
    /// @param colour 16-bit colour
    /// @note If two points are equal, draw a line
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    virtual void triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour);

    ///
    /// @brief Draw rectangle, rectangle coordinates
    /// @param x1 top left coordinate, x-axis
    /// @param y1 top left coordinate, y-axis
    /// @param x2 bottom right coordinate, x-axis
    /// @param y2 bottom right coordinate, y-axis
    /// @param colour 16-bit colour
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    virtual void rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);

    ///
    /// @brief Draw rectangle, vector coordinates
    /// @param x0 point coordinate, x-axis
    /// @param y0 point coordinate, y-axis
    /// @param dx length, x-axis
    /// @param dy height, y-axis
    /// @param colour 16-bit colour
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    virtual void dRectangle(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);

    ///
    /// @brief Draw pixel
    /// @param x1 point coordinate, x-axis
    /// @param y1 point coordinate, y-axis
    /// @param colour 16-bit colour
    ///
    /// @n @b More: @ref Coordinate, @ref Colour
    ///
    virtual void point(uint16_t x1, uint16_t y1, uint16_t colour);

    /// @}

    /// @name Text
    /// @{

    ///
    /// @brief Select font number
    /// @param font default=0, 0..fontMax()-1
    ///
    virtual void selectFont(uint8_t font);

    ///
    /// @brief Get font number
    /// @return Number of the font, 0..fontMax()-1
    ///
    virtual uint8_t getFont();

    ///
    /// @brief Add a font
    /// @param fontName name of the font
    /// @return number of the font, 0 otherwise
    /// @note Previously selectFont()
    /// @n @b More: @ref Fonts
    ///
    virtual uint8_t addFont(font_s fontName);

    ///
    /// @brief Set transparent or opaque text
    /// @param flag default = 1 = opaque = solid, false = transparent
    ///
    virtual void setFontSolid(bool flag = true);

    ///
    /// @brief Set additional spaces between two characters, horizontal axis
    /// @param number of spaces default = 1 pixel
    ///
    virtual void setFontSpaceX(uint8_t number = 1);

    ///
    /// @brief Set additional spaces between two characters, vertical axis
    /// @param number of spaces default = 1 pixel
    ///
    virtual void setFontSpaceY(uint8_t number = 1);

    ///
    /// @brief Character size, x-axis
    /// @param character character to evaluate, default=0=font general size
    /// @return horizontal size of character for current font, in pixels
    /// @note With setSpaceX included
    /// @note In variable font, each character has a specific size.
    /// The general size is indicative.
    /// @note Previously fontSizeX()
    /// @n @b More: @ref Fonts
    ///
    virtual uint16_t characterSizeX(uint8_t character = 0x00);

    ///
    /// @brief Character size, y-axis
    /// @return vertical size for current font, in pixels
    /// @note Previously fontSizeY()
    /// @n @b More: @ref Fonts
    ///
    virtual uint16_t characterSizeY();

    ///
    /// @brief String size, x-axis
    /// @param text string to evaluate
    /// @return horizontal size of the string for current font, in pixels
    /// @n @b More: @ref Fonts
    ///
    virtual uint16_t stringSizeX(String text);

    ///
    /// @brief Number of characters to fit a size, x-axis
    /// @param text string to evaluate
    /// @param pixels number of pixels to fit in
    /// @return number of characters to be displayed inside the pixels
    /// @n @b More: @ref Fonts
    ///
    virtual uint8_t stringLengthToFitX(String text, uint16_t pixels);

    ///
    /// @brief Number of fonts
    /// @return number of fonts available
    /// @note First font is numbered 0, second 1, ...
    /// @n The latest font is numbered fontMax()-1
    ///
    virtual uint8_t fontMax();

    ///
    /// @brief Draw ASCII Text (pixel coordinates) with selection of size
    /// @param x0 point coordinate, x-axis
    /// @param y0 point coordinate, y-axis
    /// @param text text string
    /// @param textColour 16-bit colour, default = white
    /// @param backColour 16-bit colour, default = black
    /// @note Previously gText() with ix and iy
    ///
    /// @n @b More: @ref Colour, @ref Fonts, @ref Coordinate
    ///
    virtual void gText(uint16_t x0, uint16_t y0,
                       String text,
                       uint16_t textColour = myColours.black,
                       uint16_t backColour = myColours.white);
    /// @}

  protected:
    /// @cond
    ///
    // * Virtual =0 compulsory functions
    // Orientation
    ///
    /// @brief Set orientation
    /// @param orientation same as setOrientation()
    ///
    virtual void _setOrientation(uint8_t orientation) = 0; // compulsory

    ///
    /// @brief Orient coordinates and check within screen
    /// @param[out] x1 x coordinate
    /// @param[out] y1 y coordinate
    /// @return false=success, true=error
    ///
    virtual bool _orientCoordinates(uint16_t & x1, uint16_t & y1) = 0; // compulsory

    // Position
    ///
    /// @brief Set point
    /// @param x1 x coordinate
    /// @param y1 y coordinate
    /// @param colour 16-bit colour
    /// @n @b More: @ref Colour, @ref Coordinate
    ///
    virtual void _setPoint(uint16_t x1, uint16_t y1, uint16_t colour) = 0; // compulsory

    // Write and Read

    // Other functions
    // required by triangle()
    ///
    /// @brief Triangle utility
    /// @param x1 first point coordinate, x-axis
    /// @param y1 first point coordinate, y-axis
    /// @param x2 second point coordinate, x-axis
    /// @param y2 second point coordinate, y-axis
    /// @param x3 third point coordinate, x-axis
    /// @param y3 third point coordinate, y-axis
    /// @param colour 16-bit colour
    ///
    void _triangleArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour);

    // required by gText()
    ///
    /// @brief Get definition for line of character
    /// @param character character 32~255
    /// @param index column index
    /// @return definition for line of character
    ///
    uint8_t _getCharacter(uint8_t character, uint8_t index);

    // Variables provided by hV_Screen_Virtual
    bool _penSolid;
    uint16_t _screenWidth, _screenHeigth, _screenDiagonal;
    uint8_t _orientation;
    uint16_t _screenColourBits;
    /// @endcond
};

#endif // hV_SCREEN_BUFFER_RELEASE
