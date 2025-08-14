/* Copyright 2021 Harrison Chan (Xelus)
 * Copyright 2022 1Conan <me@1conan.com>
 * Copyright 2025 naix07
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
#include "color.h"
#include "connection.h"
#include "gm807.h"
#include "gpio.h"
#include "host.h"
#include "keycodes.h"
#include "led.h"
#include "rgb_matrix.h"
#include <quantum.h>

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤───┼───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │ │ K5│ K4│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤ └───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │Ctrl│GUI │Alt │                        │ Alt│ Fn │Menu│Ctrl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,      KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,     KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,      GU_TOGG, RGB_BRI_CTRL_TOG,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,                       KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, MO(_FN), KC_APP,  KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT(
        QK_BOOT,          _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______,     _______, _______, KEY_USB_LED,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     RM_SPDU, RM_SATU, RM_HUEU,
        BT_TOG,  BT_PRO1, BT_PRO2, BT_PRO3, _______, _______, _______, _______, _______, _______, BT_PAIR, _______, _______, _______,     RM_SPDD, RM_SATD, RM_HUED,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,     _______, _______,
        _______, _______, _______, _______, _______, BT_BATT, _______, _______, _______, _______, _______,          _______,                       RM_VALU,
        _______, _______, _______,                   _______,                                     _______, _______, _______, _______,     RM_PREV, RM_VALD, RM_NEXT
    )
};

bool control_brightness = false;
bool blinking_caps = false;
uint8_t blink_count = 0;
uint16_t last_blink_time = 0;
bool led_temp_state = false;

void connection_toggle_indicator(void) {
    blinking_caps = true;
    blink_count = 6; // on + off per blink
    last_blink_time = timer_read();
    led_temp_state = host_keyboard_led_state().caps_lock;
    led_update_ports((led_t){.caps_lock = led_temp_state});
}

void matrix_scan_user(void) {
    if (blinking_caps && timer_elapsed(last_blink_time) > 300) {
        led_temp_state = !led_temp_state;
        led_update_ports((led_t){.caps_lock = led_temp_state});
        last_blink_time = timer_read();
        blink_count--;

        if (blink_count == 0) {
            blinking_caps = false;
            led_update_ports(host_keyboard_led_state());
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (blinking_caps && !led_temp_state) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            rgb_matrix_set_color(i, RGB_OFF);
        }
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        if (control_brightness) {
            tap_code(KC_VOLU);
        } else {
            rgb_matrix_increase_val();
            if (rgb_matrix_get_val() == 255) {
                connection_toggle_indicator();
            }
        }
    } else {
        if (control_brightness) {
            tap_code(KC_VOLD);
        } else {
            rgb_matrix_decrease_val();
        }
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            if (record->event.pressed) {
                blinking_caps = false;
                led_update_ports(host_keyboard_led_state());
            }
            return true;
        case BT_TOG:
#ifdef BLUETOOTH_ENABLE
            if (record->event.pressed) {
                connection_set_host(connection_get_host() == CONNECTION_HOST_USB ? CONNECTION_HOST_BLUETOOTH : CONNECTION_HOST_USB);
                connection_toggle_indicator();
            }
#endif
            return false;
        case RGB_BRI_CTRL_TOG:
            if (record->event.pressed) {
                control_brightness = !control_brightness;
                gpio_write_pin(LED_K4, !control_brightness);
            }
            return false;
        case GU_TOGG:
            if (record->event.pressed) {
                keymap_config.no_gui = !keymap_config.no_gui;
                gpio_write_pin(LED_K5, keymap_config.no_gui);
            }
            return false;
        default:
            return true;
    }
}
