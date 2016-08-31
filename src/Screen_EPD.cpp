//
// Screen_EPD.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project new_Template_screen
//
// Created by Rei VILO, Jun 28, 2016
// embedXcode.weebly.com
//
//
// Copyright © Rei VILO, 2013-2016
// License All rights reserved
//
// See Template_screen.h and ReadMe.txt for references
//


// Library header
#include "Screen_EPD.h"


// Class
Screen_EPD::Screen_EPD(eScreen_EPD_t eScreen)
{
    _flagBeginDone = false;
    _eScreen = eScreen;

    switch (_eScreen)
    {
        case eScreen_EPD_eTC_144_Mb:

            _widthScreen =  96 ; // x = wide size
            _heightScreen = 128; // y = small size
            break;

        case eScreen_EPD_eTC_190_Mb:

            _widthScreen =  128 ; // x = wide size
            _heightScreen = 144; // y = small size
            break;

        case eScreen_EPD_eTC_200_Mb:

            _widthScreen =  96 ; // x = wide size
            _heightScreen = 200; // y = small size
            break;

        case eScreen_EPD_eTC_260_Mb:

            _widthScreen =  128; // x = wide size
            _heightScreen = 232; // y = small size
            break;

        case eScreen_EPD_eTC_271_Mb:

            _widthScreen = 176;  // x = wide size
            _heightScreen = 264; // y = small size
            break;

        case eScreen_EPD_iTC_215:

            _widthScreen =  208 ; // x = wide size
            _heightScreen = 112; // y = small size
            break;

        case eScreen_EPD_iTC_287:

            _widthScreen =  296 ; // x = wide size
            _heightScreen = 128; // y = small size
            break;

        case eScreen_EPD_iTC_420:

            _widthScreen =  300 ; // x = wide size
            _heightScreen = 400; // y = small size
            break;

        default:
            Serial.println(". Screen_EPD");
            break;
    }

    _widthBuffer = _widthScreen; // x = wide size
    _heightBuffer = _heightScreen / 8; // 112 / 8;
    _sizeBuffer = _widthBuffer * _heightBuffer;
}

void Screen_EPD::begin()
{
    // http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

    // Framebuffer initialisation
    if (!_flagBeginDone)
    {
        uint8_t * _newFrameBuffer = new uint8_t[_sizeBuffer];
        uint8_t * _oldFrameBuffer = new uint8_t[_sizeBuffer];
        _flagBeginDone = true;

        _oldImage = (uint8_t *) _oldFrameBuffer;
        _newImage = (uint8_t *) _newFrameBuffer;
    }

    memset(_newImage, 0x00, _sizeBuffer);
    memset(_oldImage, 0x00, _sizeBuffer);

    // Screen initialisation
    switch (_eScreen)
    {
        case eScreen_EPD_eTC_144_Mb:

            _result = _pdi_epd.begin(dr_eTC_G2_Aurora_Mb, EPD_144_BW, USE_Temperature_Sensor);
            break;

        case eScreen_EPD_eTC_190_Mb:

            _result = _pdi_epd.begin(dr_eTC_G2_Aurora_Mb, EPD_190_BW, USE_Temperature_Sensor);
            break;

        case eScreen_EPD_eTC_200_Mb:

            _result = _pdi_epd.begin(dr_eTC_G2_Aurora_Mb, EPD_200_BW, USE_Temperature_Sensor);
            break;

        case eScreen_EPD_eTC_260_Mb:

            _result = _pdi_epd.begin(dr_eTC_G2_Aurora_Mb, EPD_260_BW, USE_Temperature_Sensor);
            break;

        case eScreen_EPD_eTC_271_Mb:

            _result = _pdi_epd.begin(dr_eTC_G2_Aurora_Mb, EPD_271_BW, USE_Temperature_Sensor);
            break;

        case eScreen_EPD_iTC_215:

            _result = _pdi_epd.begin(dr_iTC_Drivers, EPD_215_BW, USE_Temperature_Sensor);
            break;

        case eScreen_EPD_iTC_287:

            _result = _pdi_epd.begin(dr_iTC_Drivers, EPD_287_BW, USE_Temperature_Sensor);
            break;

        case eScreen_EPD_iTC_420:

            _result = _pdi_epd.begin(dr_iTC_Drivers, EPD_420_BW, USE_Temperature_Sensor);
            break;

        default:
            Serial.println(". begin");
            break;
    }

    // Standard
    //    setBacklight(true);
    setOrientation(0);
    setFontSize(0);

    _screenWidth = _heightScreen;
    _screenHeigth = _widthScreen;
    _penSolid = false;
    _fontSolid = false;
    _touchTrim = 0; // no touch
    _invert = false;
    clear();

    //    _page = 0;
}

void Screen_EPD::flush()
{
    _result = _pdi_epd.EPD_display_GU_from_pointer(_oldImage, _newImage);
    memcpy(_oldImage, _newImage, _sizeBuffer);
}

void Screen_EPD::clear(uint16_t colour)
{
    switch (_eScreen)
    {
        case eScreen_EPD_eTC_144_Mb:
        case eScreen_EPD_eTC_190_Mb:
        case eScreen_EPD_eTC_200_Mb:
        case eScreen_EPD_eTC_260_Mb:
        case eScreen_EPD_eTC_271_Mb:

            if ((colour == greyColour) or (colour == grayColour))
            {
                for (uint8_t i = 0; i < _widthBuffer; i++)
                {
                    uint16_t pattern = (i % 2) ? 0b10101010 : 0b01010101;
                    for (uint8_t j = 0; j < _heightBuffer; j++)
                    {
                        _newImage[i * _heightBuffer + j] = pattern;
                    }
                }
            }
            else if ((colour == whiteColour) xor _invert)
            {
                memset(_newImage, 0xff, _sizeBuffer);
            }
            else
            {
                memset(_newImage, 0x00, _sizeBuffer);
            }
            break;

        case eScreen_EPD_iTC_215:
        case eScreen_EPD_iTC_287:
        case eScreen_EPD_iTC_420:

            if ((colour == greyColour) or (colour == grayColour))
            {
                for (uint8_t i = 0; i < _widthBuffer; i++)
                {
                    uint16_t pattern = (i % 2) ? 0b10101010 : 0b01010101;
                    for (uint8_t j = 0; j < _heightBuffer; j++)
                    {
                        _newImage[i * _heightBuffer + j] = pattern;
                    }
                }
            }
            else if ((colour != whiteColour) xor _invert)
            {
                memset(_newImage, 0xff, _sizeBuffer);
            }
            else
            {
                memset(_newImage, 0x00, _sizeBuffer);
            }
            break;

        default:
            Serial.println(". clear");
            break;
    }
}

String Screen_EPD::WhoAmI()
{
    switch (_eScreen)
    {
        case eScreen_EPD_eTC_144_Mb:

            return "eTC 1.44\" Mb";
            break;

        case eScreen_EPD_eTC_190_Mb:

            return "eTC 1.90\" Mb";
            break;

        case eScreen_EPD_eTC_200_Mb:

            return "eTC 2.00\" Mb";
            break;

        case eScreen_EPD_eTC_260_Mb:

            return "eTC 2.60\" Mb";
            break;

        case eScreen_EPD_eTC_271_Mb:

            return "eTC 2.71\" Mb";
            break;

        case eScreen_EPD_iTC_215:

            return "iTC 2.15\"";
            break;

        case eScreen_EPD_iTC_287:

            return "iTC 2.87\"";
            break;

        case eScreen_EPD_iTC_420:

            return "iTC 4.20\"";
            break;

        default:
            break;
    }
}

void Screen_EPD::invert(boolean flag)
{
    _invert = flag;
}

void Screen_EPD::_setOrientation(uint8_t orientation)
{
    switch (_eScreen)
    {
        case eScreen_EPD_eTC_271_Mb:
            orientation++;
            break;

        default:
            break;
    }
    _orientation = orientation % 4;
}

void Screen_EPD::_orientCoordinates(uint16_t &x, uint16_t &y)
{
    switch (_orientation)
    {
        case 1:                                                                 // checked
            x = _widthScreen - 1 - x ;
            // y = y;
            break;

        case 2:                                                                 // checked
            x = _heightScreen - 1  - x;
            y = _widthScreen  - 1 - y;
            _swap(x, y);
            break;

        case 3:                                                                 // checked
            // x = x;
            y = _heightScreen  - 1 - y;
            break;

        default:                                                                // checked
            _swap(x, y);
            break;
    }
}

void Screen_EPD::_setPoint(uint16_t x1, uint16_t y1, uint16_t colour)
{
    if ((x1 < 0) or (x1 >= screenSizeX()) or (y1 < 0) or (y1 >= screenSizeY()))
    {
        return;
    }

    if ((colour == greyColour) or (colour == grayColour))
    {
        colour = ((x1 + y1) % 2 == 0) ? blackColour : whiteColour;
    }

    _orientCoordinates(x1, y1);


    switch (_eScreen)
    {
        case eScreen_EPD_eTC_144_Mb:
        case eScreen_EPD_eTC_190_Mb:
        case eScreen_EPD_eTC_200_Mb:
        case eScreen_EPD_eTC_260_Mb:
        case eScreen_EPD_eTC_271_Mb:

            if ((colour == whiteColour) xor _invert)
            {
                bitSet(_newImage[x1 * _heightBuffer + (y1 >> 3)], 7 - (y1 % 8));
            }
            else
            {
                bitClear(_newImage[x1 * _heightBuffer + (y1 >> 3)], 7 - (y1 % 8));
            }
            break;

        case eScreen_EPD_iTC_215:
        case eScreen_EPD_iTC_287:
        case eScreen_EPD_iTC_420:

            if ((colour != whiteColour) xor _invert)
            {
                bitSet(_newImage[x1 * _heightBuffer + (y1 >> 3)], 7 - (y1 % 8));
            }
            else
            {
                bitClear(_newImage[x1 * _heightBuffer + (y1 >> 3)], 7 - (y1 % 8));
            }
            break;

        default:
            Serial.println(". _setPoint");
            break;
    }
}

// Utilities
uint8_t Screen_EPD::getResult()
{
    return _result;
}
