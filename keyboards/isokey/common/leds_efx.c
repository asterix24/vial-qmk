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
 * Copyright 2024 Daniele Basile <asterix24@gmail.com>
 *
 */
#include <leds_efx.h>
#include <lp5569.h>

const uint8_t uno_addr[] = {0x0C, 0x13, 0x1A};
const uint8_t uno[]      = {
    0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x08, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80, 0x01, 0x00, 0x00, 0x92, 0x01, 0x24, 0x00, 0x49, 0x9F, 0x89, 0x40, 0x00, 0x42, 0x3C, 0x43, 0x3C, 0x66, 0x00, 0xA0, 0x02, 0xC0, 0x00, 0x9F, 0x8A, 0x40, 0x00, 0x42, 0x3C, 0x43, 0x3C, 0x66, 0x00, 0xA0, 0x02, 0xC0, 0x00, 0x9F, 0x8B, 0x40, 0x00, 0x42, 0x3C, 0x43, 0x3C, 0x66, 0x00, 0xA0, 0x02, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t due_addr[] = {0x0C, 0x15, 0x1C};
const uint8_t due[]      = {
    0x01, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x02, 0x00, 0x10, 0x00, 0x80, 0x00, 0x01, 0x00, 0x08, 0x00, 0x40, 0x00, 0x92, 0x01, 0x24, 0x00, 0x49, 0x9C, 0x03, 0x9C, 0x85, 0x40, 0x00, 0x9D, 0x80, 0x40, 0x3C, 0x9D, 0xC0, 0x4C, 0x00, 0xA0, 0x02, 0xC0, 0x00, 0x9F, 0x84, 0x40, 0x00, 0xE0, 0x80, 0x40, 0x0F, 0x66, 0x00, 0xA0, 0x02, 0xC0, 0x00, 0x9F, 0x88, 0x40, 0x00, 0xE0, 0x80, 0x40, 0x0A, 0x66, 0x00, 0xA0, 0x02, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t isokey_left[] = {
    0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x08, 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80, 0x01, 0x00, 0x01, 0xFF, 0x9F, 0x89, 0x28, 0x64, 0x29, 0x64, 0x5A, 0x00, 0x9C, 0x00, 0x9C, 0x88, 0x40, 0x00, 0x9D, 0x80, 0x40, 0x05, 0x9D, 0x80, 0x40, 0x14, 0x9D, 0x80, 0x40, 0x50, 0x9D, 0xC0, 0x9D, 0xC0, 0x48, 0x00, 0xA0, 0x06, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const uint8_t addr_isokey_left[] = {0x0A, 0x1C, 0x1D};

static uint8_t default_level = 200;

static const struct {
    uint8_t addr;
    uint8_t pwm0;
    uint8_t pwm1;
    uint8_t pwm2;
} led_map[] = {
    {TML_LEFT_ADDR, REG_D0_PWM, REG_D1_PWM, REG_D2_PWM},  /* LED_EXTRA_M0_RGB led 0, 1  , 2 */
    {TML_LEFT_ADDR, REG_D3_PWM, REG_D4_PWM, REG_D5_PWM},  /* LED_EXTRA_M1_RGB led 3, 4  , 5 */
    {TML_LEFT_ADDR, REG_D6_PWM, REG_D7_PWM, REG_D8_PWM},  /* LED_EXTRA_M2_RGB led 6, 7  , 8 */
    {TML_RIGHT_ADDR, REG_D3_PWM, 0, 0},                   /* LED_CAPS_LOCK:   led 12 */
    {TML_RIGHT_ADDR, REG_D4_PWM, 0, 0},                   /* LED_NUM_LOCK:    led 13 */
    {TML_RIGHT_ADDR, REG_D5_PWM, 0, 0},                   /* LED_SCROLL_LOCK: led 14 */
    {TML_RIGHT_ADDR, REG_D6_PWM, REG_D7_PWM, REG_D8_PWM}, /* LED_M7_RGB:      led 15, 16 , 17 */
    {TML_RIGHT_ADDR, REG_D0_PWM, 0, 0},                   /* LED_CNTL_M0:     led 9 */
    {TML_RIGHT_ADDR, REG_D1_PWM, 0, 0},                   /* LED_CNTL_M1:     led 10 */
    {TML_RIGHT_ADDR, REG_D2_PWM, 0, 0},                   /* LED_CNTL_M2:     led 11 */
    {0, 0, 0, 0},                                         /* end */
};

void leds_efx_setLed(isokey_led_t led, uint8_t status) {
    uint8_t lev = status ? default_level : 0;
    if (led_map[led].pwm0 != 0) lp5569_setLed(led_map[led].addr, led_map[led].pwm0, lev);
    if (led_map[led].pwm1 != 0) lp5569_setLed(led_map[led].addr, led_map[led].pwm1, lev);
    if (led_map[led].pwm2 != 0) lp5569_setLed(led_map[led].addr, led_map[led].pwm2, lev);
}

void leds_efx_update(uint8_t level) {
    default_level = level;
    uprintf("level[%d]\n", default_level);
}

void leds_efx_levelUp(void) {
    uint8_t lev   = default_level;
    default_level = default_level > 255 ? 255 : lev + 10;
    leds_efx_update(default_level);
}

void leds_efx_levelDown(void) {
    uint8_t lev   = default_level;
    default_level = default_level < 10 ? 0 : lev - 10;
    leds_efx_update(default_level);
}
void leds_efx_mgr(uint8_t prog, uint8_t enable) {
    if (enable) {
        lp5569_loadPrg(RIGHT, isokey_left, sizeof(isokey_left), addr_isokey_left, sizeof(addr_isokey_left));
        lp5569_loadPrg(LEFT, isokey_left, sizeof(isokey_left), addr_isokey_left, sizeof(addr_isokey_left));
        // lp5569_loadPrg(LEFT, uno, sizeof(uno), uno_addr, sizeof(uno_addr));
    }
}

void leds_efx_init(void) {
    lp5569_init();
}
