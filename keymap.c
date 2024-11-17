/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    return true;
}

enum custom_keycodes {
    M_CUT = SAFE_RANGE,
    M_COPY,
    M_PASTE, 
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_CUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x"));
            }
            break;
        case M_COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));
            }
            break;
        case M_PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("v"));
            }
            break;
    }
    return true;
}

enum combos {
    // right side //
    // top row
    DEL,
    REFRESH,
    PRINT_SCREEN,

    // home row
    CAPS,
    TAB,
    PLAY_PAUSE,

    // bottom row
    CUT,
    COPY,
    PASTE,

    // left side //
    // home row
    ENTER,
    BACKSPACE,
    ESC,
};

const uint16_t PROGMEM del_combo[]               = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM refresh_comboo[]          = {KC_E, KC_R, COMBO_END};
// const uint16_t PROGMEM print_screen_combo[]      = {KC_W, KC_E, KC_R, COMBO_END};

const uint16_t PROGMEM caps_combo[]              = {LALT_T(KC_S), LSFT_T(KC_D), COMBO_END};
// const uint16_t PROGMEM tab_combo[]               = {LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};
// const uint16_t PROGMEM play_pause_combo[]        = {LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM play_pause_combo[]        = {LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM print_screen_combo[]      = {LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), COMBO_END};

// const uint16_t PROGMEM cut_combo[]               = {KC_X, KC_C, COMBO_END};
// const uint16_t PROGMEM copy_combo[]              = {KC_C, KC_V, COMBO_END};
// const uint16_t PROGMEM paste_combo[]             = {KC_X, KC_C, KC_V, COMBO_END};

// const uint16_t PROGMEM enter_combo[]             = {RCTL_T(KC_J), RSFT_T(KC_K), COMBO_END};
// const uint16_t PROGMEM backspace_combo[]         = {RSFT_T(KC_K), RALT_T(KC_L), COMBO_END};
const uint16_t PROGMEM esc_combo[]               = {RCTL_T(KC_J), RSFT_T(KC_K), RALT_T(KC_L), COMBO_END};

combo_t key_combos[] = {
    [DEL]              = COMBO(del_combo, KC_DEL),
    [REFRESH]          = COMBO(refresh_comboo, KC_F5),
    [PRINT_SCREEN]     = COMBO(print_screen_combo, KC_PSCR),
    [CAPS]             = COMBO(caps_combo, KC_CAPS),
    // [TAB]              = COMBO(tab_combo, KC_TAB),
    [PLAY_PAUSE]       = COMBO(play_pause_combo, KC_MPLY),
    // [CUT]              = COMBO(cut_combo, MACRO_CUT),
    // [COPY]             = COMBO(copy_combo, MACRO_COPY),
    // [PASTE]            = COMBO(paste_combo, MACRO_PASTE),
    // [ENTER]            = COMBO(enter_combo, KC_ENT),
    // [BACKSPACE]        = COMBO(backspace_combo, KC_BSPC),
    [ESC]              = COMBO(esc_combo, KC_ESC),
};

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    return true;
}

// maybe extend (on KC_LGUI) have cut, copy, paste
enum layers {
    _BASE,
    _NUM,
    _SYM,
    _FUNC,
    _GAME,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,    LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,             KC_H, RCTL_T(KC_J), RSFT_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_LGUI, LT(_NUM,KC_SPC), KC_TAB,    KC_ENT, LT(_SYM,KC_BSPC), KC_RSFT
                                            //`--------------------------'  `--------------------------'
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, _______, KC_HOME,   KC_UP,  KC_END, _______,                      KC_MINS,    KC_7,    KC_8,    KC_9, KC_PAST, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, _______, LALT_T(KC_LEFT), LSFT_T(KC_DOWN), LCTL_T(KC_RGHT), _______,                       KC_EQL, RCTL_T(KC_4), RSFT_T(KC_5), RALT_T(KC_6), RGUI_T(KC_SLSH), XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, _______,   M_CUT,  M_COPY, M_PASTE, _______,                       KC_DOT,    KC_1,    KC_2,    KC_3, KC_PERC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______, _______, _______,    _______,   MO(_FUNC),    KC_0
                                            //`--------------------------'  `--------------------------'
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, KC_CIRC,   KC_LT,   KC_GT, KC_DQUO,  KC_GRV,                      KC_AMPR, KC_SLSH, KC_LBRC, KC_RBRC, KC_PERC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL,  KC_DLR,                      KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_BSLS, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_HASH, KC_QUES, KC_ASTR, KC_UNDS, KC_QUOT,                      KC_TILD, KC_COMM, KC_LCBR, KC_RCBR,   KC_AT, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______,   MO(_FUNC), _______,    _______, _______, _______
                                            //`--------------------------'  `--------------------------'
    ),

    [_FUNC] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______,                      _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,  QK_RBT, LALT_T(KC_MPRV), LSFT_T(KC_MNXT), LCTL_T(KC_MPLY), _______,                      _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, _______, TG(_GAME), KC_BRID, KC_BRIU, _______,                      _______,   KC_F1,   KC_F2,   KC_F3,  KC_F12, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______, _______, _______,     _______, _______, _______
                                            //`--------------------------'  `--------------------------'
    ),

    [_GAME] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                      _______, _______, _______, _______, _______, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,                      _______, _______, _______, _______, _______, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,                      _______, _______, _______, _______, _______, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                 KC_ESC,  KC_SPC,  TG(_BASE),    _______, _______, _______
                                            //`--------------------------'  `--------------------------'
    )
};
