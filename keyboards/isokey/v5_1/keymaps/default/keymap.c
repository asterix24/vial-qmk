// Copyright 2024 Daniele Basile <asterix24@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _DB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DB] = LAYOUT_ortho_5x7_5x9 (
        KC_B,KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
             KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
             KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
        KC_B,KC_A,KC_B,KC_A,KC_B,KC_A,KC_B,
        KC_B,KC_A,KC_B,     KC_B,KC_A,
// - ------------------------------------------------
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,KC_D,KC_A,
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,KC_D,     KC_H,
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,KC_D,KC_A,KC_H,
        KC_D,KC_H,KC_A,KC_D,KC_X,KC_Y,     KC_A,
             KC_H,KC_A,     KC_X,     KC_D,KC_A,KC_H
    )
};
