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

#ifndef ISOKEY_SETTINGS_H
#define ISOKEY_SETTINGS_H

#include <stdint.h>
#include <lp5569.h>
#include "keycode.h"

#define M1_SW  KC_PMNS
#define M2_SW  KC_PPLS
#define M3_SW  KC_TRNS
#define M4_SW  KC_TRNS
#define M5_SW  KC_TRNS
#define M6_SW  KC_DEL
#define M7_SW  KC_TRNS
#define M8_SW  KC_TRNS
#define FN_SW  KC_TRNS

enum isokey_keycodes {
  QMKBEST = SAFE_RANGE,
  LED_EFX,// Start/strop led efx
  LOGO,   // https://isokey.asterix.cloud  > this should be always the last! <
};

#endif /* ISOKEY_SETTINGS_H */
