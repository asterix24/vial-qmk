/* Copyright 2021 Harry Herring, Ivan Organista
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define STATUS_LED_A_PIN D2
#define STATUS_LED_B_PIN D3

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* VIAL Keyboard UID */
#define VIAL_KEYBOARD_UID {0xC1, 0x9B, 0x8E, 0x7B, 0x43, 0xD7, 0x61, 0xEE}

/* VIAL Unlock combo keys */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 }

/* Encoder default values and delay */
#define VIAL_ENCODER_DEFAULT { KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }
#define VIAL_ENCODER_KEYCODE_DELAY 10