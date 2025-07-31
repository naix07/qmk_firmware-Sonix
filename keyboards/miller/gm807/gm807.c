/* Copyright 2021 Harrison Chan (Xelus)
 * Copyright 2022 1Conan <me@1conan.com>
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

#include "gm807.h"
#ifdef MODULE_ITON_BT
#include "iton_bt.h"
#endif
#include <quantum.h>

void keyboard_pre_init_kb(void)  {
    // turn off LEDs on two buttons near encoder
    setPinOutput(LED_K4);
    writePinLow(LED_K4);
    setPinOutput(LED_K5);
    writePinLow(LED_K5);

    // Turn off LED on the USB PORT of the USB hub
    setPinOutput(LED_USB_PORT);
    writePinLow(LED_USB_PORT);

    // Turn off output for encoder LEDs
    setPinOutput(LED_ENCODER);
    writePinLow(LED_ENCODER);

#ifdef MODULE_ITON_BT
    iton_bt_init();
#endif

    keyboard_pre_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case KEY_USB_LED:
                writePin(LED_USB_PORT, !readPin(LED_USB_PORT));
                break;
            case BT_PAIR:
#ifdef MODULE_ITON_BT
                iton_bt_enter_pairing();
#endif
                break;
            case BT_PRO1:
#ifdef MODULE_ITON_BT
                iton_bt_switch_profile(0);
#endif
                break;
            case BT_PRO2:
#ifdef MODULE_ITON_BT
                iton_bt_switch_profile(1);
#endif
                break;
            case BT_PRO3:
#ifdef MODULE_ITON_BT
                iton_bt_switch_profile(2);
#endif
                break;
            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}
