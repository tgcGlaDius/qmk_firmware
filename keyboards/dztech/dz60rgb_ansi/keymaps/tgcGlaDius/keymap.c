#include QMK_KEYBOARD_H
#include "leaderIndicator.h"
#include "print.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LEAD, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          RSFT_T(KC_UP),
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, LT(1, KC_LEFT),   LT(2, KC_DOWN),   RCTL_T(KC_RIGHT)
    ),
    [1] = LAYOUT_60_ansi(
        KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, KC_CALC, _______, KC_INS,  _______, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
        KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP,          _______,
        KC_MPRV,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, NK_TOGG, _______, _______, KC_END,  KC_PGDN,          KC_MNXT,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [2] = LAYOUT_60_ansi(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______, _______, _______, RESET,
        _______, RGB_M_P, _______, _______, _______, _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        DEBUG  , _______, _______,                            _______,                            _______, _______, _______, _______
    )
};

LEADER_HIGHLIGHT_STORE();

LEADER_EXTERNS();

void leader_start(void){
    clearLeaderIndicator();
}

void rgb_matrix_indicators_user(void){
    if(leading){
        highlightLeaderIdicator();
    }
}

void matrix_scan_user(void){
    if(leading){
        LEADER_CHECK_SEQ_LAYER();

        SEQ_ONE_KEY_HIGHLIGHT(KC_C);
        SEQ_ONE_KEY_HIGHLIGHT(KC_R);
        SEQ_ONE_KEY_HIGHLIGHT(KC_D);
        SEQ_TWO_KEYS_HIGHLIGHT(KC_S,KC_S);
        SEQ_ONE_KEY_HIGHLIGHT(KC_B);
        SEQ_TWO_KEYS_HIGHLIGHT(KC_E, KC_V);
        SEQ_ONE_KEY_HIGHLIGHT(KC_G);
        SEQ_ONE_KEY_HIGHLIGHT(KC_M);

    }

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_C){ // clion compile
            register_code(KC_LCTL);
            tap_code(KC_F9);
            unregister_code(KC_LCTL);
        }

        SEQ_ONE_KEY(KC_R){ // clion run
            register_code(KC_LSFT);
            tap_code(KC_F10);
            unregister_code(KC_LSFT);
        }

        SEQ_ONE_KEY(KC_D){ // clion debug
            register_code(KC_LSFT);
            tap_code(KC_F9);
            unregister_code(KC_LSFT);
        }

        SEQ_TWO_KEYS(KC_S, KC_S){ // clion stop running instance
            register_code(KC_LCTL);
            tap_code(KC_F2);
            unregister_code(KC_LCTL);
        }

        SEQ_ONE_KEY(KC_B){ // clion breakpoint
            register_code(KC_LCTL);
            tap_code(KC_F8);
            unregister_code(KC_LCTL);
        }

        SEQ_TWO_KEYS(KC_E, KC_V){ // clion debugger evaluate
            register_code(KC_LALT);
            tap_code(KC_F8);
            unregister_code(KC_LALT);
        }

        SEQ_ONE_KEY(KC_G){ // clion generate
            register_code(KC_LALT);
            tap_code(KC_INS);
            unregister_code(KC_LALT);
        }

        SEQ_ONE_KEY(KC_M){ // clion column select mode
            register_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(KC_INS);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
        }

    }
}
