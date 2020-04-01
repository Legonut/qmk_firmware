/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

#define TAPPING_TERM 150

/* key matrix */
#define DIODE_DIRECTION ROW2COL

// Rows are doubled-up
#define MATRIX_COLS 13
#define MATRIX_COL_PINS { C3, C4, C5, C6, C7, A7, A6, A5, A4, A3, A2, A1, A0 }

// wiring of each half
#define MATRIX_ROWS 5
#define MATRIX_ROW_PINS { D7, D1, D5, D6, C2 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef IOS_DEVICE_ENABLE
  #define RGBLIGHT_LIMIT_VAL 40
#elif RGBLIGHT_FULL_POWER
  #define RGBLIGHT_LIMIT_VAL 255
#else
  #define RGBLIGHT_LIMIT_VAL 120
#endif
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS RGBLIGHT_LIMIT_VAL

#define LED_HITS_TO_REMEMBER 5

#define RGBLIGHT_ANIMATIONS

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for Helix keyboard
//  120  RGBoff, OLEDoff
//  120  OLED
//  330  RGB 6
//  300  RGB 32
//  310  OLED & RGB 32
  #define USB_MAX_POWER_CONSUMPTION 500
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif
