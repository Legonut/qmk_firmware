#include "sol.h"


#ifdef SSD1306OLED
void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    //led_set_user(usb_led);
}
#endif

#ifdef RGB_MATRIX_ENABLE
  #define RC(R,C) {R | (C << 4)}
  // #  define RXY(R,C) { 224 / 4 * (R >= 5 ? R - 5 : R), 64 / 13 * (C + (R >= 5 ? 7 : 0)) }
  #define RXY(R,C) { 56 * (R >= 5 ? R - 5 : R), 4 * (C + (R >= 5 ? 7 : 0)) }
  #define RCM(R,C,M) {RC(R,C), RXY(R, C), M}
  #define ROW(R, m0, m1, m2, m3, m4, m5, m6) \
      RCM( R, 0, m0), \
      RCM( R, 1, m1), \
      RCM( R, 2, m2), \
      RCM( R, 3, m3), \
      RCM( R, 4, m4), \
      RCM( R, 5, m5), \
      RCM( R, 6, m6)

  #define MOD 1
  #define ___ 0
  #define G_RGB_LEDS { \
      ROW( 0, MOD, ___, ___, ___, ___, ___, ___), \
      ROW( 1, ___, ___, ___, ___, ___, ___, ___), \
      ROW( 2, ___, ___, ___, ___, ___, ___, ___), \
      ROW( 3, ___, ___, ___, ___, ___, ___, ___), \
      ROW( 4, MOD, MOD, MOD, ___, ___, ___, ___), \
      ROW( 5, ___, ___, ___, ___, ___, ___, ___), \
      ROW( 6, ___, ___, ___, ___, ___, ___, ___), \
      ROW( 7, ___, ___, ___, ___, ___, ___, ___), \
      ROW( 8, ___, ___, ___, ___, ___, ___, ___), \
      ROW( 9, ___, ___, ___, ___, ___, MOD, MOD)  \
  }
  const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = G_RGB_LEDS;

  #undef RC
  #undef MOD
  #undef ___
  #undef ROW
  #undef RCM
#endif

void matrix_init_kb(void) {

	matrix_init_user();
};

