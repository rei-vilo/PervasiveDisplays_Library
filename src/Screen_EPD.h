///
/// @file		Screen_EPD.h - SPECIAL EDITION FOR ENERGIA
/// @brief		Library header
/// @n
/// @n @b		Project LCD_screen Library Suite
/// @n @a		Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author		Rei VILO
/// @author		http://embeddedcomputing.weebly.com
/// @date		Sep 07, 2016
/// @version	109
///
/// @copyright  (c) Rei VILO, 2010-2016 - SPECIAL EDITION FOR ENERGIA
/// @copyright	All rights reserved
/// @n          http://embeddedcomputing.weebly.com/lcd_screen-library-suite
///
/// @n  Dual license:
/// *   For hobbyists and for personal usage: Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
/// *   For professionals or organisations or for commercial usage: All rights reserved
///
/// @n  For any enquiry about license, http://embeddedcomputing.weebly.com/contact
///
///
/// @see	ReadMe.txt for references
///


// Core library - IDE-based
// Core library - IDE-based
#if defined(ENERGIA) // LaunchPad, FraunchPad and StellarPad specific
#include "Energia.h"
#else
#error Paltform not supported
#endif // end IDE

#ifndef Screen_EPD_RELEASE
///
/// @brief	Library release number
///
#define Screen_EPD_RELEASE 107

// Other libraries
#include "LCD_screen_buffer.h"
#include "Pervasive_EPD_BoosterPack2.h"

#if LCD_SCREEN_BUFFER_RELEASE < 302
#error Required LCD_SCREEN_BUFFER_RELEASE 302
#endif

///
/// @brief	List of supported Persvasice Displays
///
enum eScreen_EPD_t
{
    eScreen_EPD_eTC_144_Mb, ///< eScreen_EPD_eTC_144_Mb
    eScreen_EPD_eTC_190_Mb, ///< eScreen_EPD_eTC_190_Mb
    eScreen_EPD_eTC_200_Mb, ///< eScreen_EPD_eTC_200_Mb
    eScreen_EPD_eTC_260_Mb, ///< eScreen_EPD_eTC_260_Mb

    eScreen_EPD_eTC_271_Ma, ///< eScreen_EPD_eTC_271_Ma
    eScreen_EPD_eTC_271_Mb, ///< eScreen_EPD_eTC_271_Mb
    eScreen_EPD_iTC_215, ///< eScreen_EPD_iTC_215
    eScreen_EPD_iTC_287, ///< eScreen_EPD_iTC_287
    eScreen_EPD_iTC_420, ///< eScreen_EPD_iTC_420
};



// Objects
//
///
/// @name   Screen Pervasive Displays class
/// @brief	Main and core class
/// @note   Supported and tested screens with switch configuration
///
/// *   eTC 144   switches = 0000 001x    http://www.pervasivedisplays.com/products/144
/// *   eTC 200   switches = 0000 001x    http://www.pervasivedisplays.com/products/200
///
/// *   eTC 190   switches = 0000 000x    http://www.pervasivedisplays.com/products/190
/// *   eTC 260   switches = 0000 000x    http://www.pervasivedisplays.com/products/260
/// *   eTC 271   switches = 0000 000x    http://www.pervasivedisplays.com/products/271b
///
/// *   iTC 215   switches = 1010 000x    http://www.pervasivedisplays.com/products/215
///
/// *   iTC 287   switches = 0101 010x    http://www.pervasivedisplays.com/products/287
/// *   iTC 420   switches = 0101 010x    http://www.pervasivedisplays.com/products/420
///
class Screen_EPD : public LCD_screen_buffer
{
  public:
    ///
    /// @brief	Constructor with default pins
    ///
    Screen_EPD(eScreen_EPD_t eScreen);

    ///
    /// @brief	Initialisation
    ///
    void begin();

    ///
    /// @brief	Request information about the screen
    /// @return	string with hardware version
    ///
    String WhoAmI();

    ///
    /// @brief	Clear the screen
    /// @param	colour default=white
    ///
    void clear(uint16_t colour = whiteColour);

    ///
    /// @brief	Invert screen
    /// @param	flag true to invert, false for normal screen
    ///
    void invert(boolean flag);

    ///
    /// @brief	Display
    ///
    void flush();

    ///
    /// @brief	Return last result code
    ///
    uint8_t getResult();

  private:
    // * Virtual =0 compulsory functions
    // Orientation
    void _setOrientation(uint8_t orientation) ; // compulsory
    void _orientCoordinates(uint16_t &x, uint16_t &y) ; // compulsory

    // Position
    void _setPoint(uint16_t x1, uint16_t y1, uint16_t colour); // compulsory

    // Write and Read

    // Touch

    // Energy

    // * Other functions specific to the screen

    // Screen independent variables
    bool _invert;
    Pervasive_EPD_BoosterPack2 _pdi_epd;
    uint8_t * _oldImage;
    uint8_t * _newImage;
    uint8_t _result;
    bool _flagBeginDone;

    uint16_t _widthBuffer, _heightBuffer;
    uint32_t _sizeBuffer;
    uint16_t _widthScreen, _heightScreen;
    eScreen_EPD_t _eScreen;
};

#endif
