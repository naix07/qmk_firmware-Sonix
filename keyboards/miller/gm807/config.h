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

#pragma once

// Exta button LEDs
#define LED_K4 A6
#define LED_K5 A7

// USB "Passthrough" LED
#define LED_USB_PORT D4

// LEDs and Resistor unpopulated
// Resistor pad is near the BT module
// LEDs: LED6-10
// Resistor: RA42 (Value: ? (probably an 82Ω))
#define LED_ENCODER D5

// RGB Matrix Config
#define SN32F2XX_RGB_MATRIX_ROWS MATRIX_ROWS
#define SN32F2XX_RGB_MATRIX_ROW_CHANNELS 3
#define SN32F2XX_RGB_MATRIX_ROW_PINS { C3, C1, C0, C6, C5, C4, C9, C8, C7, C12, C11, C10, B13, C14, C13, B14, B15, D3 }

#define SN32F2XX_RGB_MATRIX_COLS MATRIX_COLS
#define SN32F2XX_RGB_MATRIX_COL_PINS MATRIX_COL_PINS

#define MODULE_ITON_BT TRUE
#define ITON_BT_ENABLE_ACK TRUE
#define ITON_BT_ENABLE_LED_STATE TRUE

#define SHARED_MATRIX TRUE
