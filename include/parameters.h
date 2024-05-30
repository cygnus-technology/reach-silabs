/********************************************************************************************
 *    _ ____  ___             _         _     ___              _                        _
 *   (_)__ / | _ \_ _ ___  __| |_  _ __| |_  |   \ _____ _____| |___ _ __ _ __  ___ _ _| |_
 *   | ||_ \ |  _/ '_/ _ \/ _` | || / _|  _| | |) / -_) V / -_) / _ \ '_ \ '  \/ -_) ' \  _|
 *   |_|___/ |_| |_| \___/\__,_|\_,_\__|\__| |___/\___|\_/\___|_\___/ .__/_|_|_\___|_||_\__|
 *                                                                  |_|
 *                           -----------------------------------
 *                          Copyright i3 Product Development 2024
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * \brief A minimal implementation of Reach data access.
 *
 * Original Author: Chuck Peplinski
 * Script Authors: Joseph Peplinski and Andrew Carlson
 *
 * Generated with version 1.0.0 of the C code generator
 *
 ********************************************************************************************/

#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

// Includes

#include <stdint.h>
/* User code start [parameters.h: User Includes] */
/* User code end [parameters.h: User Includes] */
// Defines

#define NUM_PARAMS 19
#define NUM_INIT_PARAMETER_NOTIFICATIONS 10
#define NUM_EX_PARAMS 5
/* User code start [parameters.h: User Defines] */
/* User code end [parameters.h: User Defines] */
// Data Types

typedef enum {
    PARAM_USER_DEVICE_NAME        = 0,
    PARAM_UPTIME                  = 1,
    PARAM_BUTTON_PRESSED          = 2,
    PARAM_IDENTIFY_LED            = 3,
    PARAM_COLOR_DEMO_RGB_STATE    = 4,
    PARAM_COLOR_DEMO_ENUMERATION  = 5,
    PARAM_IDENTIFY                = 6,
    PARAM_IDENTIFY_INTERVAL       = 7,
    PARAM_RELATIVE_HUMIDITY       = 8,
    PARAM_TEMPERATURE             = 9,
    PARAM_LIGHT_LEVEL             = 10,
    PARAM_UV_INDEX                = 11,
    PARAM_MAGNETIC_FIELD_STRENGTH = 12,
    PARAM_ACCELERATION_X_AXIS     = 13,
    PARAM_ACCELERATION_Y_AXIS     = 14,
    PARAM_ACCELERATION_Z_AXIS     = 15,
    PARAM_TIMEZONE_ENABLED        = 16,
    PARAM_TIMEZONE_OFFSET         = 17,
    PARAM_BT_DEVICE_ADDRESS       = 18,
} param_t;
typedef enum {
    PARAM_EI_IDENTIFY_SWITCH       = 0,
    PARAM_EI_IDENTIFY_LED          = 1,
    PARAM_EI_TIMEZONE              = 2,
    PARAM_EI_RGB_STATE             = 3,
    PARAM_EI_RGB_STATE_TRANSLATION = 4,
} param_ei_t;
typedef enum {
    RGB_STATE_INDICES_RED   = 0,
    RGB_STATE_INDICES_GREEN = 1,
    RGB_STATE_INDICES_BLUE  = 2,
} rgb_state_indices_t;
typedef enum {
    RGB_STATE_RED   = (0b1 << RGB_STATE_INDICES_RED),
    RGB_STATE_GREEN = (0b1 << RGB_STATE_INDICES_GREEN),
    RGB_STATE_BLUE  = (0b1 << RGB_STATE_INDICES_BLUE),
} rgb_state_t;
typedef enum {
    RGB_STATE_TRANSLATION_OFF     = 0,
    RGB_STATE_TRANSLATION_RED     = 1,
    RGB_STATE_TRANSLATION_GREEN   = 2,
    RGB_STATE_TRANSLATION_YELLOW  = 3,
    RGB_STATE_TRANSLATION_BLUE    = 4,
    RGB_STATE_TRANSLATION_MAGENTA = 5,
    RGB_STATE_TRANSLATION_CYAN    = 6,
    RGB_STATE_TRANSLATION_WHITE   = 7,
} rgb_state_translation_t;
/* User code start [parameters.h: User Data Types] */
/* User code end [parameters.h: User Data Types] */
// Global Variables

/* User code start [parameters.h: User Global Variables] */
/* User code end [parameters.h: User Global Variables] */
// Global Functions

void parameters_init(void);
const char *parameters_get_ei_label(int32_t pei_id, uint32_t enum_bit_position);
/* User code start [parameters.h: User Global Functions] */

char* parameters_get_cli_text_color(void);
int parameters_reset_nvm(void);

/* User code end [parameters.h: User Global Functions] */

#endif // _PARAMETERS_H_