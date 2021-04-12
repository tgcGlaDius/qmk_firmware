#include QMK_KEYBOARD_H
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

#define INDIC_ROWS MATRIX_ROWS
#define INDIC_COLLS MATRIX_COLS
bool indic[INDIC_ROWS][INDIC_COLLS] = {{false,},};

#define CODESIZE sizeof(uint16_t)
#define ROW_SIZE (MATRIX_COLS*CODESIZE)
#define LAYER_SIZE (MATRIX_COLS*ROW_SIZE)

uint16_t readCodeAt(uint8_t layer, uint8_t row, uint8_t column){
    return pgm_read_word(&(keymaps[layer][row][column]));
    // return pgm_read_word( ((keymaps+(layer*LAYER_SIZE))+(row*ROW_SIZE))+(column+CODESIZE) );
}

void activateCode(uint16_t code){
    for(int r = 0; r<INDIC_ROWS; r++){
        for(int c = 0; c<INDIC_COLLS; c++){
            // uprintf("[0][%u][%u] = %u\n", r, c, readCodeAt(0,r,c));
            if(readCodeAt(0,r,c) == code){
                uprintf("indicating row: %u col: %u\n", r, c);
                indic[r][c] = true;
            }
        }
    }
}

void clearLeaderIndicator(void){
    for(int r = 0; r<INDIC_ROWS; r++){
        for(int c = 0; c<INDIC_COLLS; c++){
            indic[r][c] = false;
        }
    }
}

#define SEQ_ONE_KEY_HIGHLIGHT(key) if(leading){\
    if(leader_sequence_size == 0){\
        activateCode(key);\
    } \
} //create a define for leader key highlighting


LEADER_EXTERNS();

bool indicating = false;

void leader_start(void){
    clearLeaderIndicator();
}

void rgb_matrix_indicators_user(void){
    if(leading){
        for(int r = 0; r<INDIC_ROWS; r++){
            for(int c = 0; c<INDIC_COLLS; c++){
                if(indic[r][c]){
                    rgb_matrix_set_color((r*INDIC_COLLS)+c,255,255,255);
                }
            }
        }
    }
}

void matrix_scan_user(void){
    SEQ_ONE_KEY_HIGHLIGHT(KC_C);
    SEQ_ONE_KEY_HIGHLIGHT(KC_R);
    SEQ_ONE_KEY_HIGHLIGHT(KC_GESC);

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        //TODO: see process_leader.h for tips to implement leader key RGB indicator

        SEQ_ONE_KEY(KC_C){
            // uprintf("leader_sequence_size: %u\n", leader_sequence_size);
            register_code(KC_LCTL);
            tap_code(KC_F9);
            unregister_code(KC_LCTL);
        }

        SEQ_ONE_KEY(KC_R){
            register_code(KC_LSFT);
            tap_code(KC_F10);
            unregister_code(KC_LSFT);
        }

        SEQ_ONE_KEY(KC_D){
            register_code(KC_LSFT);
            tap_code(KC_F9);
            unregister_code(KC_LSFT);
        }

        SEQ_TWO_KEYS(KC_S, KC_S){
            // uprintf("leader_sequence_size: %u\n", leader_sequence_size);
            register_code(KC_LCTL);
            tap_code(KC_F2);
            unregister_code(KC_LCTL);
        }

        SEQ_ONE_KEY(KC_B){
            register_code(KC_LCTL);
            tap_code(KC_F8);
            unregister_code(KC_LCTL);
        }

        SEQ_TWO_KEYS(KC_E, KC_V){
            register_code(KC_LALT);
            tap_code(KC_F8);
            unregister_code(KC_LALT);
        }

        SEQ_ONE_KEY(KC_G){
            register_code(KC_LALT);
            tap_code(KC_INS);
            unregister_code(KC_LALT);
        }

    }
}
