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
 * Copyright 2023 Daniele Basile <asteri24@gmail.com>
 *
 */

/** \brief Lock LED update callback - keyboard level
 *
 * \return Ignored for now.
 */

#include <led.h>
#include <leds_efx.h>
#include <print.h>

bool led_update_user(led_t led_state) {
    leds_efx_setLed(LED_CAPS_LOCK, led_state.caps_lock);
    leds_efx_setLed(LED_NUM_LOCK, led_state.num_lock);
    leds_efx_setLed(LED_SCROLL_LOCK, led_state.scroll_lock);

    uprintf("cl[%d] nl[%d] bs[%d]\n", led_state.caps_lock, led_state.num_lock, led_state.scroll_lock);

    return false;
}
