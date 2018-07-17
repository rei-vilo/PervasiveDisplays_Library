# LCD_screen for EPD Extension Kit Gen 2 (EXT2) Displays Library
LCD_screen for EPD Extension Kit Gen 2 (EXT2) by Pervasive Displays on Energia

### Content

The PervasiveDisplays Library supports the e-paper screens on the EPD Extension Kit Gen 2 (EXT2) BoosterPack from Pervasive Displays.

It runs on the following boards with Energia: LaunchPad MSP432, LaunchPad CC3200, LaunchPad TM4C123G. 

The library requires the **Pervasive_EPD_BoosterPack2** library.

> `#include "Pervasive_EPD_BoosterPack2.h"`

### Supported Screens

Screen | Pixels | Switches | Product Page
---- | ---- | ---- | ----
eTC 144 | 96 x 128 | `0000 001x` | http://www.pervasivedisplays.com/products/144
eTC 200 | 96 x 200 | `0000 001x` | http://www.pervasivedisplays.com/products/200
eTC 190 | 128 x 144 | `0000 000x` | http://www.pervasivedisplays.com/products/190
eTC 260 | 128 x 232 | `0000 000x` | http://www.pervasivedisplays.com/products/260
eTC 271 Ma | 176 x 264 | `0000 000x` | http://www.pervasivedisplays.com/products/271
eTC 271 Mb | 176 x 264 | `0000 000x` | http://www.pervasivedisplays.com/products/271
iTC 215 | 208 x 112 | `1010 000x` | http://www.pervasivedisplays.com/products/215
iTC 287 | 296 x 128 | `0101 010x` | http://www.pervasivedisplays.com/products/287
iTC 420 | 300 x 400 | `0101 010x` | http://www.pervasivedisplays.com/products/420
iTC 287 BWR | 296 x 128 | `0101 010x` | http://www.pervasivedisplays.com/products/287
iTC 420 BWR | 300 x 400 | `0101 010x` | http://www.pervasivedisplays.com/products/420

### Tutorials

General documentation is available at [LCD_screen Library Suite](http://embeddedcomputing.weebly.com/lcd_screen-library-suite.html).

### Installation

Three options.

##### Using the Boards Manager (recommended)

* Launch Energia 1.6.10E18.
* Call the menu **Sketck > Include Library > Manage Libraires...**.
* Select the library and click on **Install**.

![image](https://github.com/rei-vilo/PervasiveDisplays_Library/blob/master/Libraries.png)

##### Using the ZIP file

* Download the ZIP file.
* Call the menu **Sketch > Include Library > Add .ZIP Library...** 
* Select the .ZIP file and click on **Install**.



##### Using the ZIP file manually

* Download the ZIP file.
* Uncompress it.
* Place the resulting `PervasiveDisplays_Library` folder on the `Libraries` folder of the sketchbook.

### Licence


This work is licensed under 

* **© Rei Vilo, 2010-2016, All rights reserved** for professionals _or_ organisations _or_ for commercial use. 

* ![image](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png) [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/) for hobbyists _and_ for personal use.
