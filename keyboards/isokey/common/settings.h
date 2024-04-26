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

enum isokey_keycodes {
  QMKBEST = SAFE_RANGE,
  M1_SW,  // Special function
  M2_SW,  // Special function
  M3_SW,  // Special function
  M4_SW,  // Special function
  M5_SW,  // Special function
  M6_SW,  // Special function
  M7_SW,  // Special function
  M8_SW,  // Special function
  FN_SW,  // Special function
  LED_EFX,// Start/strop led efx
  LOGO,   // https://isokey.asterix.cloud  > this should be always the last! <
};


typedef struct {
    uint8_t len;
    uint16_t delay;
    uint8_t codes[5];
} isokey_key_t;


extern const isokey_key_t isokey_key_table[];

void settings_init(void);

#endif /* ISOKEY_SETTINGS_H */
