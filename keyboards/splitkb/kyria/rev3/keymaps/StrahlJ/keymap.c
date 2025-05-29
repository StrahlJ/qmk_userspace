/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "sendstring_german.h"
#include "autocorrect_data.h"

enum layers {
    _QWERTZ = 0,
    _NAV,
    _SYM,
    _BRACS,
    _FUNCTION,
    _GAMING,
    _MOUSE
};


// Aliases for readability
#define QWERTZ   DF(_QWERTZ)
#define SYM1     OSL(_SYM)
#define BRACS    OSL(_BRACS)
#define NAV      MO(_NAV)
#define FKEYS    OSL(_FUNCTION)
#define GAMING   TG(_GAMING)
#define MOUSE	 TG(_MOUSE)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)
#define OSLSFT   OSM(MOD_LSFT)
#define OSRSFT   OSM(MOD_RSFT)
#define OSCTL    OSM(MOD_LCTL)

enum unicode_names {
    SNEK,
};

const uint32_t PROGMEM unicode_map[] = {
    [SNEK]  = 0x1F40D,
};

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTZ
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Z  |   U  |   I  |   O  |   P  |  Lead  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  |Ö     |  Ctrl  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Y  |   X  |   C  |   V  |   B  |  (   |  [   |  |   /  |   {  |   N  |   M  | , ;  | . :  | -  _ | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Nav  | LGUI | LAlt/| Space|Bracs |  | Sym1 | BKSP | RGUI | ALTGr| Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTZ] = LAYOUT(
     KC_TAB  , DE_Q ,  DE_W   ,  DE_E  ,   DE_R ,   DE_T ,                                            DE_Z,    DE_U ,  DE_I ,   DE_O ,  DE_P , QK_LEAD,
     CTL_ESC , DE_A ,  DE_S   ,  DE_D  ,   DE_F ,   DE_G ,                                            DE_H,    DE_J ,  DE_K ,   DE_L ,DE_ODIA, OSCTL,
     OSLSFT , DE_Y ,  DE_X   ,  DE_C  ,   DE_V ,   DE_B , DE_LPRN,   DE_LBRC,    DE_SLSH  , DE_LCBR , DE_N,    DE_M ,DE_COMM, DE_DOT ,DE_MINS, OSRSFT,
                                 NAV    , KC_LGUI, ALT_ENT, KC_SPC , BRACS ,      SYM1    , KC_BSPC ,KC_RGUI, KC_RALT, KC_APP
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | Mouse| Func |C Lck | AC   |      |                              | PgDwn| PgUp | Home | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |N Lck |      | Pwr  |                              |   ←  |  ↓   |   ↑  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |Reboot|ClrROM| Sclck|      |      |      |      |  |Gaming|      | M Stp|M Play|M Prv |M Nxt |VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      QK_LLCK, MOUSE, FKEYS  , KC_CAPS, AC_TOGG , _______,                                     KC_PGDN, KC_PGUP, KC_HOME,   KC_END,  KC_VOLU, KC_DEL,
      _______, _______, _______, KC_NUM, _______, KC_PWR,                                     KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_VOLD, KC_INS,
      _______, QK_RBT, EE_CLR, KC_SCRL, _______, _______, _______, _______, GAMING, _______,KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Symbol Layer 1: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Lock   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   %    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  /   |  *   |   -  |  +   |  ?   |                              |   !  |  .   |  ,   |  =   |  &  |   \     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   §  |  €   |  $   |   @  |  _   |   #  |      |  |      |      |   |  |  :   |  ;   |  ^   |   °  |  ~     |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      QK_LLCK, DE_1,     DE_2,   DE_3,    DE_4,    DE_5,                                        DE_6,    DE_7,    DE_8,    DE_9,    DE_0, DE_PERC ,
      _______, DE_SLSH, DE_ASTR, DE_MINS, DE_PLUS, DE_QUES,                                     DE_EXLM, DE_DOT, DE_COMM, DE_EQL, DE_AMPR, DE_BSLS,
      _______, DE_SECT, DE_EURO, DE_DLR, DE_AT, DE_UNDS, DE_HASH, _______, _______, _______, DE_PIPE, DE_COLN, DE_SCLN, DE_CIRC, DE_DEG, DE_TILD,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Bracket Layer: Parans, Bracs and Qouts
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |  Ü     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |   {  |   [  |  (   |      |                              |      |  "   |  '   |      |      |  Ä     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |   }  |   ]  |  )   |      |      | Lock |  |      |      |      |  "   |  '   |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BRACS] = LAYOUT(
      QK_LLCK, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, DE_UDIA,
      _______, DE_LABK, DE_LCBR, DE_LBRC, DE_LPRN, _______,                                     _______, DE_DQUO, DE_QUOT, DE_ACUT , DE_GRV, DE_ADIA,
      _______, DE_RABK, DE_RCBR, DE_RBRC, DE_RPRN, _______, _______, _______, _______, _______, _______, _______, _______,_______ , _______, DE_SS,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  F9  | F10  | F11  | F12  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | Shift| Ctrl |  Alt |  GUI |      |                              |      |  F5  |  F6  |  F7  |  F8  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |  F1  |  F2  |  F3  |  F4  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,
      _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,                                     _______, KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Gaming Layer
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |   ESC  |      |   Q  |  W   |  E   |  R   |                              |      |      | Up   |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |LShft |   A  |  S   |  D   |  F   |                              |      | Left | Down | Right|      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        | Cntr |      |      |      |  G   |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
     [_GAMING] = LAYOUT(
       KC_ESC, _______, DE_Q, DE_W, DE_E, DE_R,                                     _______, _______, KC_UP, _______, _______, _______,
       _______, KC_LSFT, DE_A, DE_S, DE_D, DE_F,                                     _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
       _______, KC_LCTL, _______, _______, DE_G, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),

// /*
//  * Mouse Layer
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |WHL L | WHL D| WHL U|WHL R|      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      | RBTN | MBTN | LBTN |      |                              |Left  | Down |  Up  | Rght |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
     [_MOUSE] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______, _______,
       _______, _______, MS_BTN2, MS_BTN3, MS_BTN1, _______,                                     MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

// Caps Word
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case DE_A ... DE_Z:
        case DE_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case DE_1 ... DE_0:
        case KC_BSPC:
        case KC_DEL:
        case DE_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// Combos
// const uint16_t PROGMEM sz_combo[] = {DE_S, DE_Z, COMBO_END};
// const uint16_t PROGMEM aoe_combo[] = {DE_A, DE_ODIA, COMBO_END};
// const uint16_t PROGMEM uoe_combo[] = {DE_U, DE_ODIA, COMBO_END};
//
// combo_t key_combos[] = {
//     COMBO(sz_combo, DE_SS),
//     COMBO(aoe_combo, DE_ADIA),
//     COMBO(uoe_combo, DE_UDIA),
// };

// Overrides
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t back_ko = ko_make_basic(MOD_MASK_CTRL, KC_LEFT, KC_WBAK);
const key_override_t fwd_ko = ko_make_basic(MOD_MASK_CTRL, KC_RIGHT, KC_WFWD);
const key_override_t refresh_ko = ko_make_basic(MOD_MASK_CTRL, KC_DOWN, KC_WREF);
const key_override_t br_up_ko = ko_make_basic(MOD_MASK_CTRL, KC_VOLU, KC_BRIU);
const key_override_t br_dwn_ko = ko_make_basic(MOD_MASK_CTRL, KC_VOLD, KC_BRID);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &back_ko,
    &fwd_ko,
    &refresh_ko,
    &br_up_ko,
    &br_dwn_ko
};

// Leader
void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_L, KC_K)) {
        SEND_STRING("loadkeys de-latin1");
    } else if (leader_sequence_two_keys(DE_M, DE_R)) {
        tap_code16(DM_REC1);
    } else if (leader_sequence_three_keys(DE_M, DE_M, DE_R)) {
        tap_code16(DM_REC2);
    } else if (leader_sequence_two_keys(DE_M, DE_P)) {
        tap_code16(DM_PLY1);
    } else if (leader_sequence_three_keys(DE_M, DE_M, DE_P)) {
        tap_code16(DM_PLY2);
    } else if (leader_sequence_two_keys(DE_M, DE_S)) {
        tap_code16(DM_RSTP);
    } else if (leader_sequence_two_keys(DE_S, DE_S)) {
        tap_code16(UM(SNEK));
    }


}

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */


// #ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTZ:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _BRACS:
            oled_write_P(PSTR("Bracets\n"), false);
            break;
        case _FUNCTION:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _GAMING:
            oled_write_P(PSTR("Gaming\n"), false);
            break;
        case _MOUSE:
        	oled_write_P(PSTR("Mouse\n"), false);
        	break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    uint8_t cosm = get_oneshot_mods();
    oled_write_P(PSTR("Oneshot: "), false);
    oled_write_P((cosm & MOD_MASK_SHIFT) ? PSTR("SHIFT ") : PSTR("      "), false);
    oled_write_P((cosm & MOD_MASK_CTRL) ? PSTR("CTRL \n") : PSTR("     \n"), false);

    oled_write_P(is_caps_word_on() ? PSTR("Caps Wrd ") : PSTR("         "), false);
    oled_write_P(leader_sequence_active() ? PSTR("Leader \n\n") : PSTR("       \n\n"), false);

    oled_write_P(autocorrect_is_enabled() ? PSTR("Autocorrect\n") : PSTR("           \n"), false);

    // Write host Keyboard LED Status to OLEDs
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK \n") : PSTR("       \n"), false);

    static char wpm_str[4];

    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_write_P(PSTR("WPM: "), false);
    oled_write(wpm_str, false);
}

void render_logo(void) {
    // clang-format off
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    // clang-format on
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

// void render_boot(bool bootloader) {
//     if (is_keyboard_master()) {
//         oled_clear();
//         for (int i = 0; i < 16; i++) {
//             oled_set_cursor(0, i);
//             if (bootloader) {
//                 oled_write_P(PSTR("Awaiting New Firmware "), false);
//             } else {
//                 oled_write_P(PSTR("Rebooting "), false);
//             }
//         }
//
//         oled_render_dirty(true);
//     }
// }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        /*static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);

        oled_write_P(PSTR("Kyria rev3.1\n\n"), false);*/

       render_status();

    } else {
        render_logo();
    }
    return false;
}

// bool shutdown_user(bool jump_to_bootloader) {
//     render_boot(jump_to_bootloader);
//     return true;
// }

// #endif

/* Rotary Encoder
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
*/
