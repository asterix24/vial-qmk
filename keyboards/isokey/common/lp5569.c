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

#include "lp5569.h"
#include "i2c_master.h"
#include "print.h"

#include <stdint.h>


void lp5569_setLed(uint8_t addr, uint8_t pwm_map, uint8_t lev) {
  if (i2c_writeReg(addr, pwm_map, &lev, 1, 100) != I2C_STATUS_SUCCESS) {
    i2c_writeReg(addr, pwm_map, &lev, 1, 100);
  }
}

void lp5569_status(void) {
  uint16_t timeout = 100;
  uint8_t pc, map;
  i2c_readReg(0x32, REG_PC1, &pc, sizeof(pc), timeout);
  i2c_readReg(0x32, REG_ENG1_MAP_LSB, &map, sizeof(map), timeout);

  uint8_t a,b;
  i2c_readReg(TML_LEFT_ADDR, REG_STATUS_IRQ, &a, sizeof(map), timeout);
  i2c_readReg(TML_LEFT_ADDR, 0x83, &b, sizeof(map), timeout);
  uint8_t c,d;
  i2c_readReg(TML_RIGHT_ADDR, REG_STATUS_IRQ, &c, sizeof(map), timeout);
  i2c_readReg(TML_RIGHT_ADDR, 0x83, &d, sizeof(map), timeout);

  uprintf("st %02x, %02x, %02x, %02x, %02x, %02x\n", a&0xe7, b&0x3, c&0xe7, d&0x3, pc, map);
}

void lp5569_loadPrg(uint8_t dev, const uint8_t *prg, size_t prg_len, const uint8_t *prg_addr, size_t prg_addr_len) {
  uint16_t timeout = 100;
  uint8_t val = LOAD_PRG1|LOAD_PRG2|LOAD_PRG3;
  i2c_writeReg(dev, REG_CNTRL2, &val, sizeof(val), timeout);
  do {
    i2c_readReg(dev, REG_STATUS_IRQ, &val, sizeof(val), timeout);
  } while (val & 0x2);

  for (uint8_t i = 0; i < prg_addr_len; i++) {
    i2c_writeReg(dev, REG_PROG1_START+i, &prg_addr[i], 1, timeout);
    val = 0;
    i2c_writeReg(dev, REG_PC1+i, &val, 1, timeout);
  }

  int chunk = prg_len;
  for(uint8_t j=0; j<16; j++) {
    uint8_t c = MIN(32, chunk);
    i2c_writeReg(dev, REG_PROG_PAGE_SEL, &j, 1, timeout);
    i2c_writeReg(dev, REG_PROG_MEM_BASE, &prg[j*32], c, timeout);
    chunk -= 32;
    if (chunk < 0)
      break;
  }
  val = RUN_PRG1|RUN_PRG2|RUN_PRG3;
  i2c_writeReg(dev, REG_CNTRL1, &val, sizeof(val), timeout);
  i2c_writeReg(dev, REG_CNTRL2, &val, sizeof(val), timeout);
}


/**
 * @brief    Initialize the LEDs driver
 * @return    None
 */
void lp5569_init(void) {
  uint8_t val;
  uint16_t timeout = 100; //ms

  // Reset Chip
  val = 0xFF;
  i2c_writeReg(TML_GLOBAL_ADDR, REG_RESET, &val, sizeof(val), timeout);
  // Enable Chip
  val = 0x40;
  i2c_writeReg(TML_GLOBAL_ADDR, REG_CONFIG, &val, sizeof(val), timeout);

  wait_ms(100);

  val = 0x58;
  i2c_writeReg(TML_LEFT_ADDR, REG_MISC, &val, sizeof(val), timeout);
  val = 0x59;
  i2c_writeReg(TML_RIGHT_ADDR, REG_MISC, &val, sizeof(val), timeout);
  val = EN_CLK_OUT;
  i2c_writeReg(TML_RIGHT_ADDR, REG_INT_GPIO, &val, sizeof(val), timeout);

  uprintf("Init LP5569\n");
}

