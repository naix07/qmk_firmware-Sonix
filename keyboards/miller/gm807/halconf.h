/* Copyright 2021 1Conan (@1Conan)
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

#ifdef BLUETOOTH_ITON_BT
/*
 * GPIO and SPI IRQs needs to be set to 0 to avoid erratic behavior
 */

/**
 * PAL driver settings
 */
#define PAL_USE_CALLBACKS TRUE
#define SN32_GPIOA_IRQ_PRIORITY 0

/**
 * SPI driver settings
 */
#define HAL_USE_SPI TRUE
#define SPI_USE_MUTUAL_EXCLUSION FALSE
#define SPI_USE_WAIT FALSE
#define SPI_USE_ASSERT_ON_ERROR FALSE
#define SPI_SELECT_MODE SPI_SELECT_MODE_NONE

#define SN32_SPI_SPI0_IRQ_PRIORITY 0
#endif

#define HAL_USE_PWM TRUE

#include_next <halconf.h>