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
 * Copyright 2023 Daniele Basile <asterix24@gmail.com>
 *
 */

#include "settings.h"
#include "keycode.h"

const isokey_key_t isokey_key_table[] = {
    /* M1_SW */ {1, 50, {KC_PMNS}},
    /* M2_SW */ {1, 50, {KC_PPLS}},
    /* M3_SW */ {2, 50, {KC_M, KC_S}},  // EDA_MS , // move selected
    /* M4_SW */ {2, 50, {KC_S, KC_I}},  // EDA_SI , // Selction inside
    /* M5_SW */ {2, 50, {KC_S, KC_L}},  // EDA_SL , // Selection line
    /* M6_SW */ {1, 50, {KC_DEL}},
    /* M7_SW */ {3, 50, {KC_T, KC_O, KC_L}},  // EDA_TOL , // Component Arrange group
    /* M8_SW */
    {3,
     50,
     {
         KC_T,
         KC_G,
         KC_A,
     }},                                // EDA_TGA, // Repoure All
    /* FN_SW */ {0, 0, {KC_LSFT }},
    /* END  {0, 0, {}}, */
};

void settings_init(void) { }
