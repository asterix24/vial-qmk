/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2022 Daniele Basile <asterix24@gmail.com>
 *
 */

#include <stdint.h>
#include "keycode.h"
#include "quantum_keycodes.h"
#include "settings.h"
#include "leds_efx.h"

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _NUM
};


/*
┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
│Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
└───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│ │Num│ / │ * │ - │
├───┴┬──┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
│ Tab│  Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │ │Del│End│PgD│ │ 7 │ 8 │ 9 │   │
├────┴┬───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent│ └───┴───┴───┘ ├───┼───┼───┤ + │
│Ctrl │  A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │               │ 4 │ 5 │ 6 │   │
├────┬┴──┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤     ┌───┐     ├───┼───┼───┼───┤
│Shft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │     │ 1 │ 2 │ 3 │   │
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤Ent│
│Ctrl│GUI │Alt │                        │ Alt│ GUI│Menu│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │   │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘



   105  LAYOUT
Because we do not have enough pins on the blackpill module, we recycle the empty key position in layout, so the extra keys are placed at the left of the board,
but in this map we saw it scattered all over the keyboard layout.
 *
 *           |     | 0     | 1   | 2   | 3   | 4     | 5   | 6     | 7   | 8     | 9   | 10   | 11   | 12    | 13        | 14       | 15          | 16          | 17       | 18  | 19     | 20    |
 *  A0 |     |     | Esc   |     | F1  | F2  | F3    | F4  | F5    | F6  | F7    | F8  | F9   | F10  | F11   | F12       | PrtSc    | Scroll Lock | Pause Break | M1       | M2  | M3     | M4    |
 *  A1 | M1  | M2  | ~ `   | ! 1 | @ 2 | # 3 | $ 4   | % 5 | ^ 6   | & 7 | * 8   | ( 9 | ) 0  | _ -  | + =   | Backspace | Insert   | Home        | PgUp        | Num Lock | /   | *      | -     |
 *  A2 | M3  | M4  | Tab   | Q   | W   | E   | R     | T   | Y     | U   | I     | O   | P    | { [  | } ]   | Enter     | Delete   | End         | PgDn        | 7 Home   | 8 ↑ | 9 PgUp | +     |
 *  A3 | M5  | M6  | Ctrl  | A   | S   | D   | F     | G   | H     | J   | K     | L   | : ;  | \ '  | \     | M5        | X1 Extra | X2 Extra    | X3 Extra    | 4 ←      | 5   | 6 →    | M6    |
 *  A4 | M7  | M8  | Shift | Z   | X   | C   | V     | B   | N     | M   | < ,   | > . | ? /  |      | Shift |           | M8       | ↑           | M7          | 1 End    | 2 ↓ | 3 PgDn | Enter |
 *  A5 |    M9     | Ctrl  | Win | Alt | M9  | space | Fn  | space |     | AltGr | Win | Menu | Ctrl | Fn    |           | ←        | ↓           | →           | 0 Ins    |     | . Del  |       |
 *
 */


const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//  Base
// ,------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------,
// |           | Esc   |     | F1  | F2  | F3    | F4  | F5    | F6  | F7    | F8  | F9   | F10  | F11   | F12       | PrtSc    | Scroll Lock | Pause Break |                                 |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |  M1 |  M2 | ~ `   | ! 1 | @ 2 | # 3 | $ 4   | % 5 | ^ 6   | & 7 | * 8   | ( 9 | ) 0  | _ -  | + =   | Backspace | X1 Extra | X2 Extra    | X3 Extra    | Num Lock | /   | *      | -     |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |  M3 |  M4 | Tab   | Q   | W   | E   | R     | T   | Y     | U   | I     | O   | P    | { [  | } ]   | Enter     | Insert   |  Home       |  PgUp       | 7 Home   | 8 ↑ | 9 PgUp | +     |
// |-----------+-------+-----+-----+---------------------------------------------------------------------+           +------------------------------------------------------------------------,
// |  M5 |  M6 | Fn    | A   | S   | D   | F     | G   | H     | J   | K     | L   | : ;  | \ '  | \     |           | Delete   |  End        | PgDn        | 4 ←      | 5   | 6 →    |       |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |  M7 |  M8 | Shift | Z   | X   | C   | V     | B   | N     | M   | < ,   | > . | ? /  | ? /  |     Shift         |          | ↑           |             | 1 End    | 2 ↓ | 3 PgDn | Enter |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |  FN       | Ctrl  | Win | Alt |    space    | Fn  |      space  |  ←    | ↓   | ↑    | →    | AltGr |           | ←        | ↓           | →           |    0 Ins       |    , Del       |
// ,-----------+-------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------,


[_BASE] = LAYOUT_full_105_iso(
 KC_ESC  ,           KC_F1   , KC_F2 , KC_F3  , KC_F4  , KC_F5  , KC_F6   , KC_F7   , KC_F8  , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_PSCR  , LGUI(KC_K) ,LGUI(KC_L), M1_SW   , M2_SW   , M3_SW   , M4_SW   , \
 KC_GRV  , KC_1    , KC_2    , KC_3  , KC_4   , KC_5   , KC_6   , KC_7    , KC_8    , KC_9   , KC_0    , KC_MINS , KC_EQL  , KC_BSPC ,LCTL(KC_C),LCTL(KC_X),LCTL(KC_V), KC_NUM  , KC_PSLS , KC_PAST , KC_PMNS , \
 KC_TAB  , KC_Q    , KC_W    , KC_E  , KC_R   , KC_T   , KC_Y   , KC_U    , KC_I    , KC_O   , KC_P    , KC_LBRC , KC_RBRC , KC_ENT  , KC_INS   , KC_HOME   , KC_PGUP , KC_P7   , KC_P8   , KC_P9   , KC_PPLS , \
 MO(_FN) , KC_A    , KC_S    , KC_D  , KC_F   , KC_G   , KC_H   , KC_J    , KC_K    , KC_L   , KC_SCLN , KC_QUOT , KC_BSLS , M5_SW   , KC_DEL   , KC_END    , KC_PGDN , KC_P4   , KC_P5   , KC_P6   , M6_SW   , \
 KC_LSFT , KC_Z    , KC_X    , KC_C  , KC_V   , KC_B   , KC_N   , KC_M    , KC_COMM , KC_DOT , KC_SLSH , KC_SLSH , KC_RSFT , M8_SW   , KC_UP    , M7_SW     , KC_P1   , KC_P2   , KC_P3   , KC_PENT , \
 KC_LCTL, KC_LGUI , KC_LALT , MO(_NUM), KC_SPC , MO(_FN), KC_SPC          , KC_ALGR , KC_RGUI, KC_RCTL , MO(_FN) , KC_DEL  , KC_LEFT , KC_DOWN  , KC_RGHT   , KC_P0   , KC_COMMA \
),

//  Alternate FN
// ,------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------,
// |           |       |     |     |     |       |     |       |     |       |     |      |      |       |           |          |             |             |                                 |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     |       |     |       |     |      |      |       |           |  LED_EFX |   LOGO      |             |          |     |        |       |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     |       |     |       |     |      |      |       |           | Track Nx | Paue/play   |  Vol up     |         |     |        |       |
// |-----------+-------+-----+-----+---------------------------------------------------------------------+           +------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     | ←     | ↓   | ↑     | →   |      |      |       |           | Track Pv |  Vol Mut    | Vol down    |          |     |        |       |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     |       |     |       |     |      |      |                   |          |             |             |          |     |        |       |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |           |       |     |     |             |     |             |       |     |      |      |       |           |          |             |             |                |   . Del       |
// ,-----------+-------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------,
[_FN] = LAYOUT_full_105_iso (
_______, _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , LED_EFX , LOGO    , _______ , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MNXT , KC_MPLY , KC_VOLU  , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, _______ , _______ , _______ , _______ , KC_MPRV , KC_MUTE , KC_VOLD  , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_PGUP , _______ , _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , KC_HOME , KC_PGDN , KC_END  , _______ , _______ , _______ , _______ , _______ , _______  , KC_PDOT \
),

//  Alternative Numpad
// ,------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------,
// |           |       |     |     |     |       |     |       |     |     |      |      |       |       |           |          |             |             |                                 |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     |       |     |  7  |  8   |  9   |   /   |       |           |          |             |             |          |     |        |       |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     |       |     |  4  |  5   |  6   |   *   |       |           |          |             |             |         |     |        |       |
// |-----------+-------+-----+-----+---------------------------------------------------------------------+           +------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     |       |     |  1  |  2   |  3   |   -   |       |           |          |             |             |          |     |        |       |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |     |     |       |     |     |     |       |     |       |     |  0  |  ,   |  .   |   +   |                   |          |             |             |          |     |        |       |
// |-----------+-------+-----+-----+----------------------------------------------------------------------------------------------------------------------------------------------------------,
// |           |       |     |     |             |     |             |     |      |      |       |       |           |          |             |             |                |               |
// ,-----------+-------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------,
[_NUM] = LAYOUT_full_105_iso (
_______, _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , _______ ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , KC_P7   , KC_P8    , KC_P9   , KC_PSLS , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , KC_P4   , KC_P5    , KC_P6   , KC_PAST , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , _______ , KC_P1   , KC_P2    , KC_P3   , KC_PMNS , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
_______, _______ , _______ , _______ , _______ , _______ , KC_P0   , KC_COMMA, KC_PDOT  , KC_PPLS , _______ , _______ , _______ , _______ , _______ , _______  , _______ \
),

};

static uint8_t efx_status;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Keycode is special function, peek the string to send from
  // the table
  if (keycode == LED_EFX) {
    if (record->event.pressed) {
      uprintf("Enable efx=%d\n", efx_status);
      leds_efx_mgr(0, efx_status);
      efx_status = !efx_status;
    }
    return true;
  }

  if (keycode == LOGO) {
    if (record->event.pressed) {
      SEND_STRING("https://blog.asterix.cloud");
    }
    return true;
  }

  int16_t key = keycode - M1_SW;
  if (key >= 0 && key <= (LOGO - M1_SW)) {
    if (record->event.pressed) {
      for (uint8_t i = 0;  i < isokey_key_table[key].len; i++) {
        tap_code_delay(isokey_key_table[key].codes[i], isokey_key_table[key].delay);
      }
    }
  }

  return true;
}

