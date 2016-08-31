///
/// @file       LCD_screen_buffer.h
/// @brief      Class library header
/// @details	Generic LCD with buffer class library
/// @n
/// @n @b       Project LCD_screen Library Suite
/// @n @a       Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author     Rei VILO
/// @author     http://embedXcode.weebly.com
/// @date		Aug 03, 2016
/// @version	302
///
/// @copyright  (c) Rei VILO, 2010-2016 - SPECIAL EDITION FOR ENERGIA
/// @copyright  All rights reserved
/// @n          http://embeddedcomputing.weebly.com/lcd_screen-library-suite
///
/// @n  Dual license:
/// *   For hobbyists and for personal usage: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
/// *   For professionals or organisations or for commercial usage: All rights reserved
///
/// @n  For any enquiry about license, http://embeddedcomputing.weebly.com/contact
///
/// @see	ReadMe.txt for references
///

// Core library - IDE-based
#if defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
#include "Energia.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(CORE_TEENSY) // Teensy specific
#include "WProgram.h"
#elif defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(ARDUINO) // Arduino 1.0x and 1.5x specific
#include "Arduino.h"
#endif // end IDE

#ifndef LCD_SCREEN_BUFFER_RELEASE
///
/// @brief	Library release number
///
#define LCD_SCREEN_BUFFER_RELEASE 302

// Other libraries
#include "LCD_screen.h"

#if (LCD_SCREEN_RELEASE < 114)
#error Required LCD_SCREEN_RELEASE 114
#endif

///
/// @brief      Biggest font size
/// @details    Based on the MCU, by default=0
///
#if defined(__LM4F120H5QR__) || defined(__TM4C1230C3PM__) || defined(__TM4C129XNCZAD__) || defined(__32MX320F128H__) || defined(__MSP432P401R__) || defined(__32MX795F512L__)
#define MAX_FONT_SIZE 4
#elif defined(__MSP430F5529__) || defined(__AVR_ATmega2560__) || defined(__CC3200R1M1RGC__)
#define MAX_FONT_SIZE 2
#else
#define MAX_FONT_SIZE 1
#endif
#if (MAX_FONT_SIZE > 0)
#include "Terminal6e.h"
#if (MAX_FONT_SIZE > 1)
#include "Terminal8e.h"
#if (MAX_FONT_SIZE > 2)
#include "Terminal12e.h"
//#if (MAX_FONT_SIZE > 3)
//#include "Terminal16e.h"
//#endif
#endif
#endif
#endif

///
/// @brief	Generic class for LCD
///
class LCD_screen_buffer : public LCD_screen
{
  public:
    ///
    /// @brief	Constructor
    ///
    LCD_screen_buffer();

    /// @name	General
    /// @{

    ///
    /// @brief	Clear the screen
    ///
    void clear(uint16_t colour = blackColour);

    /// @}

    /// @name	Graphics
    /// @{

//    ///
//    /// @brief	Draw circle
//    /// @param	x0 center, point coordinate, x-axis
//    /// @param	y0 center, point coordinate, y-axis
//    /// @param	radius radius
//    /// @param	colour 16-bit colour
//    ///
//    virtual void circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t colour);

    ///
    /// @brief	Draw line, rectangle coordinates
    /// @param	x1 top left coordinate, x-axis
    /// @param	y1 top left coordinate, y-axis
    /// @param	x2 bottom right coordinate, x-axis
    /// @param	y2 bottom right coordinate, y-axis
    /// @param	colour 16-bit colour
    ///
    virtual void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);

//    ///
//    /// @brief	Set pen opaque
//    /// @param	flag default = true = opaque = solid, false = wire frame
//    ///
//    virtual void setPenSolid(bool flag = true);

    ///
    /// @brief	Draw rectangle, rectangle coordinates
    /// @param	x1 top left coordinate, x-axis
    /// @param	y1 top left coordinate, y-axis
    /// @param	x2 bottom right coordinate, x-axis
    /// @param	y2 bottom right coordinate, y-axis
    /// @param	colour 16-bit colour
    ///
    /// @n @b	More: @ref Coordinates, @ref Colours
    ///
    virtual void rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);

    ///
    /// @brief	Draw pixel
    /// @param	x1 point coordinate, x-axis
    /// @param	y1 point coordinate, y-axis
    /// @param	colour 16-bit colour
    ///
    /// @n @b	More: @ref Coordinates, @ref Colours
    ///
    virtual void point(uint16_t x1, uint16_t y1, uint16_t colour);

    /// @}

    /// @name	Text
    /// @{

    ///
    /// @brief	Select font size
    /// @param	size default = 0 = small, 1 = large
    /// @warning    Definition for this method is compulsory.
    ///
    virtual void setFontSize(uint8_t size);

    ///
    /// @brief	Get font size
    /// @return	font size, default = 0 = small, 1 = large
    ///
    uint8_t getFontSize();

    ///
    /// @brief	Set transparent or opaque text
    /// @param	flag default = 1 = opaque = solid, false = transparent
    /// @warning    Definition for this method is compulsory.
    ///
    virtual void setFontSolid(bool flag = true);

    ///
    /// @brief	Font size, x-axis
    /// @return	horizontal size of current font, in pixels
    ///
    virtual uint8_t fontSizeX();

    ///
    /// @brief	Font size, y-axis
    /// @return	vertical size of current font, in pixels
    ///
    virtual uint8_t fontSizeY();

    ///
    /// @brief	Draw ASCII Text (pixel coordinates) with selection of size
    /// @param	x0 point coordinate, x-axis
    /// @param	y0 point coordinate, y-axis
    /// @param	s text string
    /// @param	textColour 16-bit colour, default = black
    /// @param	backColour 16-bit colour, default = white
    /// @param	ix x-axis font size multiplier, default = 1
    /// @param	iy y-axis font size multiplier, default = 1
    ///
    /// @n @b	More: @ref Colours
    ///
    virtual void gText(uint16_t x0, uint16_t y0,
                       String s,
                       uint16_t textColour = blackColour, uint16_t backColour = whiteColour,
                       uint8_t ix = 1, uint8_t iy = 1);

    /// @}


  protected:
    // * Virtual =0 compulsory functions
    // Orientation
    virtual void _setOrientation(uint8_t orientation) = 0; // compulsory
    virtual void _orientCoordinates(uint16_t &x1, uint16_t &y1) = 0; // compulsory

    // Position
    void _setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void _closeWindow();
    virtual void _setPoint(uint16_t x1, uint16_t y1, uint16_t colour) = 0; // compulsory
    void _fastFill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);

    // Write and Read
    void _writeData88(uint8_t dataHigh8, uint8_t dataLow8);

    // Touch
    void _getRawTouch(uint16_t &x0, uint16_t &y0, uint16_t &z0); // = 0; // compulsory

    // Other functions
    // required by calibrateTouch
    //        void _displayTarget(uint16_t x0, uint16_t y0, uint16_t colour);

    // required by triangle()
    void _triangleArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour);

    // required by gText()
    uint8_t _getCharacter(uint8_t c, uint8_t i);

    // Energy
    uint32_t _msEnergy;
    uint32_t _chronoEnergy;
    bool     _stateEnergy;

    // required by setBacklight() and setBacklightPWM
    bool _flagIntensity;
    void _setIntensity(uint8_t intensity); // compulsory
    void _setBacklight(bool flag); // compulsory

    // Utilities
    void _swap(int16_t &a, int16_t &b);
    void _swap(uint16_t &a, uint16_t &b);
    void _swap(uint8_t &a, uint8_t &b);
    uint16_t _check(uint16_t x0, uint16_t xmin, uint16_t xmax);
};

#endif
