#ifndef REV2_H
#define REV2_H

#include "zen.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
    #include <avr/io.h>
    #include <avr/interrupt.h>
#endif
#endif

//void promicro_bootloader_jmp(bool program);

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05,             k55, k54, k53, k52, k51, k50, \
    k10, k11, k12, k13, k14, k15, k16    k66, k65, k64, k63, k62, k61, k60, \
    k20, k21, k22, k23, k24, k25, k26    k76, k75, k74, k73, k72, k71, k70, \
    k30, k31, k32, k33, k34, k35, k36    k86, k85, k84, k83, k82, k81, k80, \
    k40, k41, k42, k43, k44, k45, k46,   k96, k95, k94, k93, k92, k91, k90 \
    ) \
    { \
        { k00, k01, k02, k03, k04, k05, KC_NO }, \
        { k10, k11, k12, k13, k14, k15, k16 }, \
        { k20, k21, k22, k23, k24, k25, k26 }, \
        { k30, k31, k32, k33, k34, k35, k36 }, \
        { k40, k41, k42, k43, k44, k45, k46 }, \
        { k50, k51, k52, k53, k54, k55, KC_NO }, \
        { k60, k61, k62, k63, k64, k65, k66 }, \
        { k70, k71, k72, k73, k74, k75, k76 }, \
        { k80, k81, k82, k83, k84, k85, k86 }, \
        { k90, k91, k92, k93, k94, k95, k96 } \
    }


#define KC________ KC_TRNS
#define KC_RGB_MOD RGB_MOD
#define KC_FN FN
#define KC_ADJ ADJ
#define LAYOUT_kc( \
    k00, k01, k02, k03, k04, k05,             k55, k54, k53, k52, k51, k50, \
    k10, k11, k12, k13, k14, k15, k16    k66, k65, k64, k63, k62, k61, k60, \
    k20, k21, k22, k23, k24, k25, k26    k76, k75, k74, k73, k72, k71, k70, \
    k30, k31, k32, k33, k34, k35, k36    k86, k85, k84, k83, k82, k81, k80, \
    k40, k41, k42, k43, k44, k45, k46,   k96, k95, k94, k93, k92, k91, k90 \
  ) \
  LAYOUT( \
    KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05,                       KC_##K55, KC_##K54, KC_##K53, KC_##K52, KC_##K51, KC_##K50, \
    KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15,                       KC_##K65, KC_##K64, KC_##K63, KC_##K62, KC_##K61, KC_##K60, \
    KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25,                       KC_##K75, KC_##K74, KC_##K73, KC_##K72, KC_##K71, KC_##K70, \
    KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K16,   KC_##K66, KC_##K85, KC_##K84, KC_##K83, KC_##K82, KC_##K71, KC_##K71, \
    KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K26, KC_##K36,   KC_##K86, KC_##K76, KC_##K94, KC_##K93, KC_##K92, KC_##K91, KC_##K90, \
                                                      KC_##K45, KC_##K46,   KC_##K96, KC_##K95 \
  )


#endif
