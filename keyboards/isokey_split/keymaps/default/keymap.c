// Copyright 2024 Daniele Basile <asterix24@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤Alt│
      *               └───┤Bsp├───┐   ┌───┤Ent├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */
    [0] = LAYOUT_ortho_5x7_5x9 (
        KC_B,KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
             KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
             KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
             KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
        KC_B,KC_A,     KC_A,KC_B,KC_A,KC_B,
// - ------------------------------------------------
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,KC_D,     KC_H,
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,KC_D,     KC_H,
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,KC_D,
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,     KC_A,
        KC_D,KC_H,KC_A,KC_D,          KC_D,KC_A,KC_H
    )
};
