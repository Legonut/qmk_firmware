#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "common/ssd1306.h"
#endif

extern keymap_config_t keymap_config;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _NUMPAD,
    _NAV_F,
    _KB_CONTROL
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD,
  NAVF,
  KBCTRL,
  RGBRST
};

//LM(layer, mod) layer switch with modifier
//LT(layer, kc) layer when held key when tapped

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define FN_ESC  LT(_FN, KC_ESC)

#define TAPPING_TOGGLE 2
// Define your non-alpha grouping in this define's LAYOUT, and all your BASE_LAYERS will share the same mod/macro columns
  /* Base Layout
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |BCK SP|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |Nv/Esc|      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |LSFT/(|      |      |      |      |      |      |  | Del  |      |      |      |      |      |RSFT/)|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |Qwerty|KbCtrl|BCK SP|Numpad|  |Enter |Space |      |      |      |      |XXXXXX|
   * `-------------+------+------+------+------+------|  |------+------+------+------+------+-------------'
   *               |XXXXXX|XXXXXX|      |BCK SP|Numpad|  |Enter |Space |      |XXXXXX|XXXXXX|
   *               `------+------'      `-------------'  `-------------'      `-------------'
   */
#define BASE_LAYOUT( \
  _XX, _00, _01, _02, _03, _04, _05,    _06, _07, _08, _09, _10, _11, \
       _12, _13, _14, _15, _16, _17,    _18, _19, _20, _21, _22, _23, _24, \
       _25, _26, _27, _28, _29, _30,    _31, _32, _33, _34, _35, _36, _37, \
       _38, _39, _40, _41, _42, _43,         _44, _45, _46, _47, _48, \
                                                  _49, _50, _51, _52 \
) \
LAYOUT( \
      _XX,                 _00,     _01,         _02,     _03,             _04,     _05,           _06,    _07,    _08, _09,   _10,  _11, KC_BSPC, \
      KC_TAB,              _12,     _13,         _14,     _15,             _16,     _17,           _18,    _19,    _20, _21,   _22,  _23, _24, \
      LT(_NAV_F, KC_ESC),  _25,     _26,         _27,     _28,             _29,     _30,           _31,    _32,    _33, _34,   _35,  _36, _37, \
      KC_LSPO,             _38,     _39,         _40,     _41,             _42,     _43,           KC_DEL, _44,    _45, _46,   _47,  _48, KC_RSPC, \
      KC_LCTL,             KC_LGUI, TT(_QWERTY), KC_LALT, TT(_KB_CONTROL), KC_BSPC, TT(_NUMPAD),   KC_ENT, KC_SPC, _49, _50,   _51,  _52, KC_ENT, \
                                    XXXXXXX,     XXXXXXX,                  KC_BSPC, TT(_NUMPAD),   KC_ENT, KC_SPC,      KC_NO, KC_NO \
)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |  =   |  |   7  |   8  |   9  |   0  |   -  |   =  |______|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|   Q  |   W  |   E  |   R  |   T  |  [   |  |   ]  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|   A  |   S  |   D  |   F  |   G  |PRTSCR|  |  INS |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|   Z  |   X  |   C  |   V  |   B  |PAUSE |  |______|   N  |   M  |   ,  |   .  |   /  |______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|______|______|______|______|______|______|  |______|______| ALT  | WIN  | MENU | CTRL |______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *               |______|______|      |______|______|  |______|______|      |______|______|
   *               `-------------'      `-------------'  `-------------'      `-------------'
   */
  [_QWERTY] = BASE_LAYOUT( \
      KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_EQL,     KC_6,    KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, \
              KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC,    KC_RBRC, KC_Y, KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
              KC_A, KC_S, KC_D, KC_F, KC_G, KC_PSCR,    KC_INS,  KC_H, KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
              KC_Z, KC_X, KC_C, KC_V, KC_B, KC_PAUS,             KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                                                                       KC_RALT, KC_RWIN, KC_APP,  KC_RCTL \
  ),

  /* Num Pad
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|  |NUM LK|XXXXXX|XXXXXX|  /   |  *   |XXXXXX|______|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|  |CAPSLK|XXXXXX|  7   |  8   |  9   |  -   |XXXXXX|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|  |SCRLLK|XXXXXX|  4   |  5   |  6   |  +   |XXXXXX|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|  |______|XXXXXX|  1   |  2   |  3   |XXXXXX|______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|______|______|______|______|______|______|  |______|______|  0   |  0   |  .   |XXXXXX|______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *               |______|______|      |______|______|  |______|______|      |______|______|
   *               `-------------'      `-------------'  `-------------'      `-------------'
   */
  [_NUMPAD] = BASE_LAYOUT( \
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NLCK, KC_NO, KC_NO,   KC_PSLS, KC_PAST, KC_NO,  \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_CAPS, KC_NO, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_NO, \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_SLCK, KC_NO, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_NO, \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,             KC_NO, KC_KP_1, KC_KP_2, KC_KP_3, KC_NO, \
                                                                          KC_KP_0, KC_KP_0, KC_PDOT, KC_NO \
  ),

  /* Nav/F Keys
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |XXXXXX|  f1  |  f2  |  f3  |  f4  |  f5  |  f6  |  |  f7  |  f8  |  f9  |  f10 |  f11 |  f12 |______|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|  |XXXXXX|XXXXXX| HOME |  UP  | END  | PGUP |XXXXXX|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|  |XXXXXX|XXXXXX|  LT  |  DN  | RT   | PGDN |XXXXXX|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|  |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|______|______|______|______|______|______|  |______|______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *               |______|______|      |______|______|  |______|______|      |______|______|
   *               `-------------'      `-------------'  `-------------'      `-------------'
   */
  [_NAV_F] = BASE_LAYOUT( \
      KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,    KC_F7, KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_NO, \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, \
             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,           KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO, \
                                                                         KC_NO,   KC_NO,   KC_NO,   KC_NO \
  ),

  /* KB CONTROL
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |RESET |RGBTOG|STATIC|BREATH|RAINBW|SWIRL |SNAKE |  |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|______|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|XXXXXX|KNIGHT|XMAS  |GRAD  |TEST  |XXXXXX|  |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |______|HUE + |SAT + |BRGHT+|XXXXXX|XXXXXX|CYCLE+|  |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|HUE - |SAT - |BRGHT-|XXXXXX|XXXXXX|CYCLE-|  |______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |______|______|______|______|______|______|______|  |______|______|XXXXXX|XXXXXX|XXXXXX|XXXXXX|______|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *               |______|______|      |______|______|  |______|______|      |______|______|
   *               `-------------'      `-------------'  `-------------'      `-------------'
   */
  [_KB_CONTROL] = BASE_LAYOUT( \
      RESET, RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  \
             KC_NO,   RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T,  KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
             RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,   KC_NO,    RGB_MOD,     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
             RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,   KC_NO,    RGB_RMOD,           KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
                                                                                      KC_NO, KC_NO, KC_NO, KC_NO \
  )

};


// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

  switch (keycode) {
    case QWERTY:
//      if (record->event.pressed) {
//        persistent_default_layer_set(1UL<<_QWERTY);
//      }
      return false;
      break;
    case NUMPAD:
      return false;
      break;
    case NAVF:
//      if (record->event.pressed) {
//        layer_on(_FN);
//      } else {
//        layer_off(_FN);
//      }
      return false;
      break;
    case KBCTRL:
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    led_test_init();
    iota_gfx_task();  // this is what updates the display continuously
  #endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(35);
__attribute__ ((weak))
void led_test_init(void) {}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_FN (1<<_FN)
#define L_ADJ (1<<_ADJ)
#define L_ADJ_TRI (L_ADJ|L_FN)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_FN:
           matrix_write_P(matrix, PSTR("FN"));
           break;
        case L_ADJ:
        case L_ADJ_TRI:
           matrix_write_P(matrix, PSTR("ADJ"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
