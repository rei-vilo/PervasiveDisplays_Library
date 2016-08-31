//
// LCD_screen_buffer.cpp
// Class library C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project LCD_screen Library Suite
//
// Created by Rei VILO, Jun 28, 2016
// http://embedXcode.weebly.com
//
//
// Copyright © Rei VILO, 2013-2016
// License All rights reserved
//
// See LCD_screen_buffer.h and ReadMe.txt for references
//
// Last update: Jun 28, 2016 release    101 Initial release

// Library header
#include "LCD_screen_buffer.h"

// Code
LCD_screen_buffer::LCD_screen_buffer()
{

}

void LCD_screen_buffer::clear(uint16_t colour)
{
    uint8_t oldOrientation = _orientation;
    bool oldPenSolid = _penSolid;
    setOrientation(0);
    setPenSolid();
    rectangle(0, 0, screenSizeX() - 1, screenSizeY() - 1, colour);
    setOrientation(oldOrientation);
    setPenSolid(oldPenSolid);
}

void LCD_screen_buffer::line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour)
{
    //    Serial.print("LCD_screen_buffer::line \t");
    //    Serial.print(x1, DEC);
    //    Serial.print("\t");
    //    Serial.print(y1, DEC);
    //    Serial.print("\t");
    //    Serial.print(x2, DEC);
    //    Serial.print("\t");
    //    Serial.print(y2, DEC);
    //    Serial.println();

    if ((x1 == x2) and (y1 == y2))
    {
        _setPoint(x1, y1, colour);
    }
    else if (x1 == x2)
    {
        if (y1 > y2)
        {
            _swap(y1, y2);
        }
        for (uint16_t y = y1; y < y2; y++)
        {
            _setPoint(x1, y, colour);
        }
    }
    else if (y1 == y2)
    {
        if (x1 > x2)
        {
            _swap(x1, x2);
        }
        for (uint16_t x = x1; x < x2; x++)
        {
            _setPoint(x, y1, colour);
        }
    }
    else
    {
        int16_t wx1 = (int16_t)x1;
        int16_t wx2 = (int16_t)x2;
        int16_t wy1 = (int16_t)y1;
        int16_t wy2 = (int16_t)y2;

        boolean flag = abs(wy2 - wy1) > abs(wx2 - wx1);
        if (flag)
        {
            _swap(wx1, wy1);
            _swap(wx2, wy2);
        }

        if (wx1 > wx2)
        {
            _swap(wx1, wx2);
            _swap(wy1, wy2);
        }

        int16_t dx = wx2 - wx1;
        int16_t dy = abs(wy2 - wy1);
        int16_t err = dx / 2;
        int16_t ystep;

        if (wy1 < wy2)
        {
            ystep = 1;
        }
        else
        {
            ystep = -1;
        }

        for (; wx1 <= wx2; wx1++)
        {
            if (flag)
            {
                _setPoint(wy1, wx1, colour);
            }
            else
            {
                _setPoint(wx1, wy1, colour);
            }

            err -= dy;
            if (err < 0)
            {
                wy1 += ystep;
                err += dx;
            }
        }
    }
}

void LCD_screen_buffer::point(uint16_t x1, uint16_t y1, uint16_t colour)
{
    _setPoint(x1, y1, colour);
}

void LCD_screen_buffer::rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour)
{
    if (_penSolid == false)
    {
        line(x1, y1, x1, y2, colour);
        line(x1, y1, x2, y1, colour);
        line(x1, y2, x2, y2, colour);
        line(x2, y1, x2, y2, colour);
    }
    else
    {
        if (x1 > x2)
        {
            _swap(x1, x2);
        }
        if (y1 > y2)
        {
            _swap(y1, y2);
        }
        for (uint16_t x = x1; x < x2; x++)
        {
            for (uint16_t y = y1; y < y2; y++)
            {
                _setPoint(x, y, colour);
            }
        }
    }
}

// Utilities
void LCD_screen_buffer::_swap(uint16_t &a, uint16_t &b)
{
    uint16_t w = a;
    a = b;
    b = w;
}
void LCD_screen_buffer::_swap(int16_t &a, int16_t &b)
{
    int16_t w = a;
    a = b;
    b = w;
}
void LCD_screen_buffer::_swap(uint8_t &a, uint8_t &b)
{
    uint8_t w = a;
    a = b;
    b = w;
}

uint16_t LCD_screen_buffer::_check(uint16_t x0, uint16_t xmin, uint16_t xmax)
{
    if (xmin < xmax)
    {
        if (x0 < xmin)
        {
            return xmin;
        }
        else if (x0 > xmax)
        {
            return xmax;
        }
        else
        {
            return x0;
        }
    }
    else
    {
        if (x0 < xmax)
        {
            return xmax;
        }
        else if (x0 > xmin)
        {
            return xmin;
        }
        else
        {
            return x0;
        }
    }
}

// Area functions


// Font functions
void LCD_screen_buffer::setFontSolid(bool flag)
{
    _fontSolid = flag;
}

void LCD_screen_buffer::setFontSize(uint8_t size)
{
    if (size < MAX_FONT_SIZE)
    {
        _fontSize = size;
    }
    else
    {
        _fontSize = MAX_FONT_SIZE - 1;
    }
}

uint8_t LCD_screen_buffer::getFontSize()
{
    return _fontSize;
}


uint8_t LCD_screen_buffer::fontSizeX()
{
#if (MAX_FONT_SIZE > 0)
    if (_fontSize == 0)
    {
        return 6;
    }
#if (MAX_FONT_SIZE > 1)
    else if (_fontSize == 1)
    {
        return 8;
    }
#if (MAX_FONT_SIZE > 2)
    else if (_fontSize == 2)
    {
        return 12;
    }
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
#endif // end MAX_FONT_SIZE > 0
    else
    {
        return 0;
    }
}

uint8_t LCD_screen_buffer::fontSizeY()
{
#if (MAX_FONT_SIZE > 0)
    if (_fontSize == 0)
    {
        return 8;
    }
#if (MAX_FONT_SIZE > 1)
    else if (_fontSize == 1)
    {
        return 12;
    }
#if (MAX_FONT_SIZE > 2)
    else if (_fontSize == 2)
    {
        return 16;
    }
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
#endif // end MAX_FONT_SIZE > 0
    else
    {
        return 0;
    }
}

// Code
uint8_t LCD_screen_buffer::_getCharacter(uint8_t c, uint8_t i)
{

#if defined(ENERGIA)

#if (MAX_FONT_SIZE > 0)
    if (_fontSize == 0)
    {
        return Terminal6x8e[c][i];
    }
#if (MAX_FONT_SIZE > 1)
    else if (_fontSize == 1)
    {
        return Terminal8x12e[c][i];
    }
#if (MAX_FONT_SIZE > 2)
    else if (_fontSize == 2)
    {
        return Terminal12x16e[c][i];
    }
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
#endif // end MAX_FONT_SIZE > 0

    else
    {
        return 0;
    }

#else

#if (MAX_FONT_SIZE > 0)
    if (_fontSize == 0)
    {
        return pgm_read_byte(&Terminal6x8e[c][i]);
    }
#if (MAX_FONT_SIZE > 1)
    else if (_fontSize == 1)
    {
        return pgm_read_byte(&Terminal8x12e[c][i]);
    }
#if (MAX_FONT_SIZE > 2)
    else if (_fontSize == 2)
    {
        return pgm_read_byte(&Terminal12x16e[c][i]);
    }
#if (MAX_FONT_SIZE > 3)
    else if (_fontSize == 3)
    {
        return pgm_read_byte(&Terminal16x24e[c][i]);
    }
#endif // end MAX_FONT_SIZE > 3
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
#endif // end MAX_FONT_SIZE > 0

    else
    {
        return 0;
    }
#endif
}


void LCD_screen_buffer::gText(uint16_t x0, uint16_t y0,
                              String s,
                              uint16_t textColour, uint16_t backColour,
                              uint8_t ix, uint8_t iy)
{
    uint8_t c;
    uint8_t line, line1, line2, line3;
    uint16_t x, y;
    uint8_t i, j, k;
    if ((_fontSize == 0) and ((ix > 1) or (iy > 1)))
    {
        bool oldPenSolid = _penSolid;
        setPenSolid(true);

        for (k = 0; k < s.length(); k++)
        {
            x = x0 + 6 * k * ix;
            y = y0;
            c = s.charAt(k) - ' ';

            for (i = 0; i < 6; i++)
            {
                line = _getCharacter(c, i);
                for (j = 0; j < 8; j++)
                {
                    if (bitRead(line, j))
                    {
                        rectangle(x + i * ix, y + j * iy, x + i * ix + ix - 1, y + j * iy + iy - 1, textColour);
                    }
                    else if (_fontSolid)
                    {
                        rectangle(x + i * ix, y + j * iy, x + i * ix + ix - 1, y + j * iy + iy - 1, backColour);
                    }
                }
            }
        }
        setPenSolid(oldPenSolid);
    }
    else
    {

#if (MAX_FONT_SIZE > 0)
        if (_fontSize == 0)
        {

            for (k = 0; k < s.length(); k++)
            {
                c = s.charAt(k) - ' ';

                for (i = 0; i < 6; i++)
                {
                    line = _getCharacter(c, i);

                    for (j = 0; j < 8; j++)
                        if (bitRead(line, j))
                        {
                            point(x0 + 6 * k + i, y0 + j, textColour);
                        }
                        else if (_fontSolid)
                        {
                            point(x0 + 6 * k + i, y0 + j, backColour);
                        }
                }
            }
        }
#if (MAX_FONT_SIZE > 1)
        else if (_fontSize == 1)
        {

            for (k = 0; k < s.length(); k++)
            {
                c = s.charAt(k) - ' ';

                for (i = 0; i < 8; i++)
                {
                    line = _getCharacter(c, 2 * i);
                    line1 = _getCharacter(c, 2 * i + 1);

                    for (j = 0; j < 8; j++)
                    {
                        if (bitRead(line, j))
                        {
                            point(x0 + 8 * k + i, y0 + j, textColour);
                        }
                        else if (_fontSolid)
                        {
                            point(x0 + 8 * k + i, y0 + j, backColour);
                        }
                        if (bitRead(line1, j))
                        {
                            point(x0 + 8 * k + i, y0 + 8 + j, textColour);
                        }
                        else if ((_fontSolid) and (j < 4))
                        {
                            point(x0 + 8 * k + i, y0 + 8 + j, backColour);
                        }
                    }
                }
            }
        }
#if (MAX_FONT_SIZE > 2)
        else if (_fontSize == 2)
        {

            for (k = 0; k < s.length(); k++)
            {
                c = s.charAt(k) - ' ';

                for (i = 0; i < 12; i++)
                {
                    line = _getCharacter(c, 2 * i);
                    line1 = _getCharacter(c, 2 * i + 1);

                    for (j = 0; j < 8; j++)
                    {
                        if (bitRead(line, j))
                        {
                            point(x0 + 12 * k + i, y0 + j,    textColour);
                        }
                        else if (_fontSolid)
                        {
                            point(x0 + 12 * k + i, y0 + j,    backColour);
                        }
                        if (bitRead(line1, j))
                        {
                            point(x0 + 12 * k + i, y0 + 8 + j, textColour);
                        }
                        else if (_fontSolid)
                        {
                            point(x0 + 12 * k + i, y0 + 8 + j, backColour);
                        }
                    }
                }
            }
        }
#endif // end MAX_FONT_SIZE > 2
#endif // end MAX_FONT_SIZE > 1
#endif // end MAX_FONT_SIZE > 0

    }
}

// Non active functions
//
void LCD_screen_buffer::_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{

}
void LCD_screen_buffer::_closeWindow()
{

}
void LCD_screen_buffer::_fastFill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour)
{

}
void LCD_screen_buffer::_writeData88(uint8_t dataHigh8, uint8_t dataLow8)
{

}
void LCD_screen_buffer::_getRawTouch(uint16_t &x0, uint16_t &y0, uint16_t &z0)
{
    x0 = 0;
    y0 = 0;
    z0 = 0;
}
