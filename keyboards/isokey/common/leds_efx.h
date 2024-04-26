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

#ifndef _LEDS_EFX_H_
#define _LEDS_EFX_H_

#include "lp5569.h"

typedef enum {
	ALL = TML_GLOBAL_ADDR,
	LEFT = TML_LEFT_ADDR,
	RIGHT = TML_RIGHT_ADDR,
} isokey_led_dev_t;

typedef enum {
    LED_EXTRA_M0_RGB , // led 0  , 1  , 2
    LED_EXTRA_M1_RGB , // led 3  , 4  , 5
    LED_EXTRA_M2_RGB , // led 6  , 7  , 8
    LED_CAPS_LOCK    , // led 12
    LED_NUM_LOCK     , // led 13
    LED_SCROLL_LOCK  , // led 14
    LED_M7_RGB       , // led 15 , 16 , 17
    LED_CNTL_M0      , // led 9
    LED_CNTL_M1      , // led 10
    LED_CNTL_M2      , // led 11

    LED_CNT
} isokey_led_t;

extern const uint8_t uno[80];
extern const uint8_t uno_addr[3];

extern const uint8_t due[80];
extern const uint8_t due_addr[3];

extern const uint8_t addr_isokey_left[3];
extern const uint8_t isokey_left[80];

void leds_efx_LoadPrg(isokey_led_dev_t dev, const uint8_t *prg, size_t prg_len, const uint8_t *prg_addr, size_t prg_addr_len);
void leds_efx_mgr(uint8_t prog, uint8_t enable);
void leds_efx_setLed(isokey_led_t led, uint8_t status);
void leds_efx_update(uint8_t level);
void leds_efx_levelUp(void);
void leds_efx_levelDown(void);


void leds_efx_init(void);

#endif /* _LEDS_EFX_H_ */
