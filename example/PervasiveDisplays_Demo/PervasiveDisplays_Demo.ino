///
/// @mainpage	Pervasive Displays Ext Gen 2
///
/// @details	Library for Pervasive Displays e-paper screens
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei VILO
/// @author		http://embeddedcomputing.weebly.com
/// @date		Jun 28, 2016
/// @version	120
///
/// @copyright  (c) Rei VILO, 2010-2016 - SPECIAL EDITION FOR ENERGIA
/// @copyright	All rights reserved
/// @n          http://embeddedcomputing.weebly.com/lcd_screen-library-suite
///
/// @see		ReadMe.txt for references
///


///
/// @file		PervasiveDisplays_Demo.ino
/// @brief		Main sketch
///
/// @details	<#details#>
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei VILO
/// @author		http://embeddedcomputing.weebly.com
/// @date		Jun 28, 2016
/// @version	120
///
/// @copyright  (c) Rei VILO, 2010-2016 - SPECIAL EDITION FOR ENERGIA
/// @copyright	All rights reserved
/// @n          http://embeddedcomputing.weebly.com/lcd_screen-library-suite
///
/// @see		ReadMe.txt for references
/// @n
///


// Core library for code-sense - IDE-based
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif // end IDE

// Set parameters


// Include application, user and local libraries
#include <SPI.h>
#include "Pervasive_EPD_BoosterPack2.h"
#include "Screen_EPD.h"

//#if Screen_EPD_RELEASE < 120
//#error Required Screen_EPD_RELEASE 120
//#endif

// Define structures and classes


// Define variables and constants
// . switches = 0000 001x
//Screen_EPD myScreen(eScreen_EPD_eTC_144_Mb);    // ok
//Screen_EPD myScreen(eScreen_EPD_eTC_200_Mb);    // ok

// . switches = 0000 000x
//Screen_EPD myScreen(eScreen_EPD_eTC_190_Mb);    // ok
//Screen_EPD myScreen(eScreen_EPD_eTC_260_Mb);    // ok
Screen_EPD myScreen(eScreen_EPD_eTC_271_Mb);    // ok

// . switches = 1010 000x
//Screen_EPD myScreen(eScreen_EPD_iTC_215);         // ok

// . switches = 0101 010x
//Screen_EPD myScreen(eScreen_EPD_iTC_287);       // ok
//Screen_EPD myScreen(eScreen_EPD_iTC_420);       // ok
//Screen_EPD myScreen(eScreen_EPD_iTC_287_BWR);       // ok
//Screen_EPD myScreen(eScreen_EPD_iTC_420_BWR);       // ok


// Prototypes


// Add setup code
void setup()
{
    Serial.begin(9600);
    delay(500);

    Serial.println("*** EPD Extension Board Gen2");
    Serial.println("EPD EXT may interfere with UART");
    Serial.println("---");
    delay(100);

    Serial.println("1. Initialising screen");
    myScreen.begin();
    Serial.print("Result = 0x");
    Serial.println(myScreen.getResult(), HEX);
    Serial.print("Screen = ");
    Serial.println(myScreen.WhoAmI());

    Serial.println("2. Generating picture");

    for (uint8_t orientation = 0; orientation < 4; orientation++)
    {
        myScreen.setOrientation(orientation);

        myScreen.setFontSolid(false);
        myScreen.setFontSize(1);
        myScreen.gText(10, 10, formatString("orient=%i", orientation));

        myScreen.setFontSize(0);
        myScreen.gText(10, 20, "/abcdef", blackColour, whiteColour);

        Serial.println(formatString(". orientation = %i", orientation));
        myScreen.dLine(0, 0, myScreen.screenSizeX(), 1, blackColour);
    }

    myScreen.setPenSolid(false);
    myScreen.dRectangle(myScreen.screenSizeX() / 2, myScreen.screenSizeY() / 2, 40, 20, blackColour);

    myScreen.setPenSolid(true);
    myScreen.circle(myScreen.screenSizeX() / 2, myScreen.screenSizeY() / 2, 20, greyColour);

    myScreen.setPenSolid(false);
    myScreen.dRectangle(0, 0, myScreen.screenSizeX(), myScreen.screenSizeY(), blackColour);

    Serial.println("3. Displaying picture");
    myScreen.flush();
    Serial.print("Result = 0x");
    Serial.println(myScreen.getResult(), HEX);

    Serial.println();
    Serial.println("*** End");
}


// Add loop code
void loop()
{

}
