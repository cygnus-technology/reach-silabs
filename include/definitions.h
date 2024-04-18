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
 * @file      definitions.h
 * @brief     A minimal implementation of Reach data access.  Auto-generated by a Python script.
 * @copyright 2023-2024 i3 Product Development. All Rights Reserved.
 *
 * Original Author: Chuck Peplinski
 * Script Author: Joseph Peplinski
 *
 * Generated with version 0.0.1 of c_code_generator.py
 *
 ********************************************************************************************/

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#include "reach.pb.h"

#define INCLUDE_PARAMETER_SERVICE
#define NUM_PARAMS                19
#define NUM_EX_PARAMS             2
#define INCLUDE_FILE_SERVICE
#define NUM_FILES                 3
#define INCLUDE_COMMAND_SERVICE
#define NUM_COMMANDS              8
#define INCLUDE_CLI_SERVICE
#define INCLUDE_TIME_SERVICE

typedef enum {
    PARAM_USER_DEVICE_NAME,
    PARAM_UPTIME,
    PARAM_BUTTON_PRESSED,
    PARAM_LED_ON,
    PARAM_IDENTIFY,
    PARAM_IDENTIFY_INTERVAL,
    PARAM_CLI_TEXT_RGB_STATE,
    PARAM_CLI_TEXT_COLOR,
    PARAM_RELATIVE_HUMIDITY,
    PARAM_TEMPERATURE,
    PARAM_LIGHT_LEVEL,
    PARAM_UV_INDEX,
    PARAM_MAGNETIC_FIELD_READING,
    PARAM_ACCELERATION_X_AXIS,
    PARAM_ACCELERATION_Y_AXIS,
    PARAM_ACCELERATION_Z_AXIS,
    PARAM_TIMEZONE_ENABLED,
    PARAM_TIMEZONE_OFFSET,
    PARAM_BT_DEVICE_ADDRESS,
} param_t;

typedef enum {
    CLI_TEXT_COLOR_DISABLED,
    CLI_TEXT_COLOR_RED,
    CLI_TEXT_COLOR_GREEN,
    CLI_TEXT_COLOR_YELLOW,
    CLI_TEXT_COLOR_BLUE,
    CLI_TEXT_COLOR_MAGENTA,
    CLI_TEXT_COLOR_CYAN,
    CLI_TEXT_COLOR_WHITE,
} cli_text_color_t;

typedef enum {
    CLI_TEXT_RGB_STATE_BIT_RED   = (0x1 << 0),
    CLI_TEXT_RGB_STATE_BIT_GREEN = (0x1 << 1),
    CLI_TEXT_RGB_STATE_BIT_BLUE  = (0x1 << 2),
} cli_text_rgb_state_t;

typedef enum {
    FILE_IO_TXT,
    FILE_CYGNUS_REACH_LOGO_PNG,
    FILE_DEV_NULL,
} file_t;

typedef enum {
    COMMAND_RESET_DEFAULTS,
    COMMAND_CLICK_FOR_WISDOM,
    COMMAND_NO_LOGGING,
    COMMAND_MUCH_LOGGING,
    COMMAND_NOTIFICATIONS_ON,
    COMMAND_NOTIFICATIONS_OFF,
    COMMAND_REMOTE_CLI_ON,
    COMMAND_REMOTE_CLI_OFF,
} command_t;

extern cr_ParameterValue sCr_param_val[NUM_PARAMS];
extern const cr_ParameterInfo param_desc[NUM_PARAMS];
extern const cr_ParamExInfoResponse param_ex_desc[NUM_EX_PARAMS];
extern cr_FileInfo file_descriptions[NUM_FILES];
extern const cr_CommandInfo command_desc[NUM_COMMANDS];

int app_handle_param_repo_pre_init(void);
int app_handle_param_repo_init(cr_ParameterValue *data, const cr_ParameterInfo *desc);
int app_handle_param_repo_post_init(void);
int app_handle_param_repo_read(cr_ParameterValue *data);
int app_handle_param_repo_write(cr_ParameterValue *data);

#endif // _DEFINITIONS_H