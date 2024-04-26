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

#pragma once

/* Enable I2C driver to manage leds and eeprom */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_BANK GPIOB
#define I2C1_SCL 6
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_BANK GPIOB
#define I2C1_SDA 7
#define I2C1_SDA_PAL_MODE 4
