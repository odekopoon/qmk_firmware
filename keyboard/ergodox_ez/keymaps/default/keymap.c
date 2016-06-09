#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

// Custom Aliases
// ref: ../../quantum/keymap_common.h
#define A(kc)     LALT(kc)
#define C(kc)     LCTL(kc)
#define G(kc)     LGUI(kc)
#define C_S(kc)   kc | 0x0100 | 0x0200 // `Ctrl + Shift + kc`(= `kc | 0x1400`)
#define G_S(kc)   kc | 0x0800 | 0x0200 // `Gui + Shift + kc` (= `kc | 0x5000`)
#define G_A(kc)   kc | 0x0800 | 0x0400 // `Gui + Alt + kc`   (= `kc | 0x6000`)
#define G_S_T(kc) MT(0x8 | 0x2, kc)  // `Gui + Alt` or kc  (= `MT(0x12, kc)`)
#define G_A_T(kc) MT(0x8 | 0x4, kc)  // `Gui + Alt` or kc  (= `MT(0x14, kc)`)

enum {
    ALFRED_DASH = 1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * - IMETGL = Toggle IME (Shift + Command + Space)
 * - KANA   = IME ON (GUI + Shift + J)  // iTerm2: Must set Key Mappings to 'Do Not Remap Modifiers'
 * - EISU   = IME OFF (GUI + Shift + ;) // iTerm2: Require the same setting as KANA
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   [  |           |  ]   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Cmd    |A / L2|   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| KANA |           | EISU |------+------+------+------+------+--------|
 * | ~L1    |Z / L1|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |/ / L1|    ~L1 |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv   |      |AltShf| LAlt | LCtrl|                                       | RCtrl| RAlt |   [  |   ]  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  |IMETGL|       | Alt  | Esc  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   |LShft |       | RShft|        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_TRNS,
        KC_TAB,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,
        KC_LGUI,        LT(MDIA,KC_A),KC_S,   KC_D,   KC_F,   KC_G,
        MO(SYMB),       LT(SYMB,KC_Z),KC_X,   KC_C,   KC_V,   KC_B,   C_S(KC_J),
        KC_GRV,         KC_TRNS,      A(KC_LSFT),  KC_LALT,KC_LCTRL,
                                              ALT_T(KC_APP),  G_S(KC_SPC),
                                                              KC_TRNS,
                                              KC_SPC,KC_BSPC, KC_LSFT,
        // right hand
             KC_TRNS,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_RBRC,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,   KC_K,   KC_L,   LT(MDIA, KC_SCLN),GUI_T(KC_QUOT),
             C_S(KC_SCLN),     KC_N,   KC_M,   KC_COMM,KC_DOT, LT(SYMB, KC_SLSH),MO(SYMB),
                                  KC_RCTRL,KC_LALT,KC_LBRC,KC_RBRC,        KC_TRNS,
             KC_LALT,     KC_ESC,
             KC_TRNS,
             KC_RSFT, KC_TAB, KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_TRNS, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_TRNS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 *  - CmdShF4 = Take a screenshot of part of your screen
 *  - AltCmdI = Web Inspector(Safari) / Developper Tool(Chrome)
 *  - AltCmdU = View Source(Safari/Chrome)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | CmdSfF4|      |      |      |      |      | RESET|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | AltCmdI|      |      | MsUp |      |      |      |           |      | PgUp |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | AltCmdU|      |MsLeft|MsDown|MsRght|      |------|           |------| PgDn | Left | Down | Right|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Dash |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 | Lclk | Rclk |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       G_S(KC_4), KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, RESET,
       G_A(KC_I), KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       G_A(KC_U), KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       M(ALFRED_DASH),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_PGUP, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
        case ALFRED_DASH:
        if (record->event.pressed) {
          return MACRO( D(LCTL), D(SPC), U(SPC), U(LCTL), T(D), T(A), T(S), T(H), T(SPC), END );
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

void light_led_on_pressed(void) {

    ergodox_right_led_3_off();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (matrix_is_on(row, col)) {

          action_t action = layer_switch_get_action((keypos_t){ .row = row, .col = col });

          if(IS_MOD(action.code)) {
            ergodox_right_led_3_on();
            break
          }
        }
      }
    }
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

    light_led_on_pressed();

};
