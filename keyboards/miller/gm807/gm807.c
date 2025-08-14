/* Copyright 2021 Harrison Chan (Xelus)
 * Copyright 2022 1Conan <me@1conan.com>
 * Copyright 2024 mintyleaf
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

#include <quantum.h>
#include <connection.h>
#include "SN32F240B.h"
#include "rgb_matrix.h"
#include "gm807.h"

#ifdef MODULE_ITON_BT
    #include "iton_bt.h"
#endif

uint32_t last_update_time = 0;

uint32_t ev_connected = 0;
uint32_t ev_connecting = 0;
uint32_t ev_pairing = 0;
uint32_t ev_disconnected = 0;
uint32_t ev_battery_level = 0;

uint32_t battery_level = 0;
uint32_t bt_profile = 0;

void board_init(void) {
    // Needed for LED_CAPS_LOCK_PIN indicator to work
    SN_SYS0->EXRSTCTRL_b.RESETDIS = 1;
    SN_SYS0->SWDCTRL_b.SWDDIS = 1;
}

void keyboard_pre_init_kb(void) {
    // turn off LEDs on two buttons near encoder
    gpio_set_pin_output(LED_K4);
    gpio_write_pin_low(LED_K4);
    gpio_set_pin_output(LED_K5);
    gpio_write_pin_low(LED_K5);

    // Turn off LED on the USB PORT of the USB hub
    gpio_set_pin_output(LED_USB_PORT);
    gpio_write_pin_low(LED_USB_PORT);

    // Turn off output for encoder LEDs
    gpio_set_pin_output(LED_ENCODER);
    gpio_write_pin_low(LED_ENCODER);

#ifdef MODULE_ITON_BT
    iton_bt_init();
#endif

    keyboard_pre_init_user();
}

#ifdef BLUETOOTH_ENABLE
void iton_bt_connection_successful() {
    connection_set_host(CONNECTION_HOST_BLUETOOTH);
    ev_connected  = 1500;
    ev_pairing    = 0;
    ev_connecting = 0;
}

void iton_bt_entered_pairing() {
    ev_pairing    = 1;
    ev_connected  = 0;
    ev_connecting = 0;
}

void iton_bt_enters_connection_state() {
    ev_connecting = 1;
    ev_connected  = 0;
    ev_pairing    = 0;
}

void iton_bt_disconnected() {
    ev_disconnected = 1500;
    ev_connected    = 0;
    ev_pairing      = 0;
    ev_connecting   = 0;
}

void iton_bt_battery_level(uint8_t level) {
    battery_level    = level;
    ev_battery_level = 1500;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KEY_USB_LED:
                gpio_write_pin(LED_USB_PORT, !gpio_read_pin(LED_USB_PORT));
                break;
            case BT_PAIR:
#ifdef MODULE_ITON_BT
                iton_bt_enter_pairing();
#endif
                break;
            case BT_PRO1:
#ifdef MODULE_ITON_BT
                iton_bt_switch_profile(0);
                bt_profile = 0;
#endif
                break;
            case BT_PRO2:
#ifdef MODULE_ITON_BT
                iton_bt_switch_profile(1);
                bt_profile = 1;
#endif
                break;
            case BT_PRO3:
#ifdef MODULE_ITON_BT
                iton_bt_switch_profile(2);
                bt_profile = 2;
#endif
                break;
            case BT_BATT:
#ifdef MODULE_ITON_BT
                iton_bt_query_battery_level();
#endif
                break;
            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}

bool rgb_matrix_indicators_kb() {

#ifdef BLUETOOTH_ENABLE
if (connection_get_host() == CONNECTION_HOST_BLUETOOTH) {
    uint32_t current_time = timer_read();                    // Get the current time in milliseconds
    uint32_t elapsed      = current_time - last_update_time; // Calculate elapsed time

    // Update the last update time for the next call
    last_update_time = current_time;

    if (ev_connected > 0 && elapsed < ev_connected) {
        uint8_t profile_index = 34 + bt_profile;
        if ((ev_connected / 250) % 2 == 0) {
            rgb_matrix_set_color(profile_index, RGB_GREEN);
        } else {
            rgb_matrix_set_color(profile_index, RGB_OFF);
        }
        ev_connected -= elapsed;
    }

    if (ev_connecting > 0) {
        uint8_t profile_index = 34 + bt_profile;
        if ((current_time / 125) % 2 == 0) {
            rgb_matrix_set_color(profile_index, RGB_YELLOW);
        } else {
            rgb_matrix_set_color(profile_index, RGB_OFF);
        }
    }

    if (ev_pairing > 0) {
        uint8_t profile_index = 43;
        if ((current_time / 62) % 2 == 0) {
            rgb_matrix_set_color(profile_index, RGB_BLUE);
        } else {
            rgb_matrix_set_color(profile_index, RGB_OFF);
        }
    }

    if (ev_disconnected > 0 && elapsed < ev_disconnected) {
        uint8_t profile_index = 34 + bt_profile;
        if ((ev_disconnected / 250) % 2 == 0) {
            rgb_matrix_set_color(profile_index, RGB_RED);
        } else {
            rgb_matrix_set_color(profile_index, RGB_OFF);
        }
        ev_disconnected -= elapsed;
    }

    if (ev_battery_level > 0 && elapsed < ev_battery_level) {
        ev_battery_level -= elapsed;
        if (battery_level == 4) {
            rgb_matrix_set_color(68, RGB_GREEN);
        } else if (battery_level == 3) {
            rgb_matrix_set_color(68, RGB_YELLOW);
        } else if (battery_level == 2) {
            rgb_matrix_set_color(68, RGB_ORANGE);
        } else if (battery_level == 1) {
            rgb_matrix_set_color(68, RGB_RED);
        } else {
            rgb_matrix_set_color(68, RGB_OFF);
        }
    }
}
#endif
rgb_matrix_indicators_user();
return false;
}
