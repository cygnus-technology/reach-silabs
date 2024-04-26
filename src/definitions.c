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
 * @file      definitions.c
 * @brief     A minimal implementation of Reach data access.  Auto-generated by a Python script.
 * @copyright 2023-2024 i3 Product Development. All Rights Reserved.
 *
 * Original Author: Chuck Peplinski
 * Script Author: Joseph Peplinski
 *
 * Generated with version 0.0.1 of c_code_generator.py
 *
 ********************************************************************************************/

#include "definitions.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "i3_log.h"
#include "app_version.h"
#include "cr_stack.h"

const cr_DeviceInfoResponse device_info = 
{
    .device_name        = "Thunderboard",
    .manufacturer       = "Silicon Labs",
    .device_description = "A demo of Reach features",
    // .protocol_version   = cr_ReachProtoVersion_CURRENT_VERSION,
    .services           = cr_ServiceIds_PARAMETER_REPO | cr_ServiceIds_FILES | cr_ServiceIds_COMMANDS | cr_ServiceIds_CLI | cr_ServiceIds_TIME
};

cr_ParameterValue sCr_param_val[NUM_PARAMS];

const cr_ParameterInfo param_desc[NUM_PARAMS] = {
    {
        .id                = PARAM_USER_DEVICE_NAME,
        .name              = "User Device Name",
        .which_desc        = cr_ParameterDataType_STRING + cr_ParameterInfo_uint32_desc_tag,
        .desc.string_desc.has_default_value = false,
        .desc.string_desc.default_value = "Test",
        .desc.string_desc.max_size = 26,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .has_description   = true,
        .description       = "Advertised BLE name",
    },
    {
        .id                = PARAM_UPTIME,
        .name              = "Uptime",
        .which_desc         = cr_ParameterDataType_INT64 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .desc.int64_desc.has_units = true,
        .desc.int64_desc.units = "milliseconds",
    },
    {
        .id                = PARAM_BUTTON_PRESSED,
        .name              = "Momentary Pushbutton",
        .which_desc        = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
        .desc.bool_desc.has_pei_id        = true,
        .desc.bool_desc.pei_id            = 4,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
    },
    {
        .id                = PARAM_LED_ON,
        .name              = "LED On",
        .which_desc        = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
        .desc.bool_desc.has_pei_id        = true,
        .desc.bool_desc.pei_id            = 5,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
    },
    {
        .id                = PARAM_IDENTIFY,
        .name              = "Identify",
        .which_desc        = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
        .desc.bool_desc.pei_id = 3,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Blinks the yellow LED",
    },
    {
        .id                = PARAM_IDENTIFY_INTERVAL,
        .name              = "Identify Interval",
        .which_desc         = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .has_description   = true,
        .description       = "Time between Identify blinks",
        .desc.float32_desc.has_units = true,
        .desc.float32_desc.units             = "seconds",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = 0.01,
        .desc.float32_desc.has_default_value = true,
        .desc.float32_desc.default_value     = 1,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 60,
        .desc.float32_desc.has_precision = true,
        .desc.float32_desc.precision = 2,
    },
    {
        .id                = PARAM_CLI_TEXT_RGB_STATE,
        .name              = "CLI Text RGB State",
        .which_desc        = cr_ParameterDataType_BIT_FIELD + cr_ParameterInfo_uint32_desc_tag,
        .desc.bitfield_desc.bits_available = 3,
        .desc.bitfield_desc.has_pei_id = true,
        .desc.bitfield_desc.pei_id = 1,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Controls command line color",
    },
    {
        .id                = PARAM_CLI_TEXT_COLOR,
        .name              = "CLI Text Color",
        .which_desc         = cr_ParameterDataType_ENUMERATION + cr_ParameterInfo_uint32_desc_tag,
        .desc.enum_desc.has_pei_id = true,
        .desc.enum_desc.pei_id = 0,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Controls command line color",
    },
    {
        .id                = PARAM_RELATIVE_HUMIDITY,
        .name              = "Relative Humidity",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units        = true,
        .desc.float32_desc.units             = "%",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = 0.01,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 50,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 100,
        .desc.float32_desc.has_precision = true,
        .desc.float32_desc.precision = 1,
    },
    {
        .id                = PARAM_TEMPERATURE,
        .name              = "Temperature",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units         = true,
        .desc.float32_desc.units             = "\xC2\xB0 C",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = -57,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 20,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 60,
        .desc.float32_desc.has_precision = true,
        .desc.float32_desc.precision = 1,
    },
    {
        .id                = PARAM_LIGHT_LEVEL,
        .name              = "Light Level",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units         = true,
        .desc.float32_desc.units             = "lux",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = 0,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 300,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 1000,
        .desc.float32_desc.has_precision = true,
        .desc.float32_desc.precision = 1,
    },
    {
        .id                = PARAM_UV_INDEX,
        .name              = "UV Index",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units         = true,
        .desc.float32_desc.units             = "W/square meter",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = 0.0,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 0,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 100,
        .desc.float32_desc.has_precision = true,
        .desc.float32_desc.precision = 1,
    },
    {
        .id                = PARAM_MAGNETIC_FIELD_READING,
        .name              = "Magnetic Field Reading",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units         = true,
        .desc.float32_desc.units             = "millitesla",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = -5000.0,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 0,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 5000,
        .desc.float32_desc.has_precision = true,
        .desc.float32_desc.precision = 0,
    },
    {
        .id                = PARAM_ACCELERATION_X_AXIS,
        .name              = "Acceleration (X axis)",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units         = true,
        .desc.float32_desc.units             = "\xE3\x8E\xA8",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = -50.0,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 0,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 50,
        .desc.float32_desc.has_precision     = true,
        .desc.float32_desc.precision         = 2,
    },
    {
        .id                = PARAM_ACCELERATION_Y_AXIS,
        .name              = "Acceleration (Y axis)",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units         = true,
        .desc.float32_desc.units             = "\xE3\x8E\xA8",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = -50.0,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 0,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 50,
        .desc.float32_desc.has_precision     = true,
        .desc.float32_desc.precision         = 2,
    },
    {
        .id                = PARAM_ACCELERATION_Z_AXIS,
        .name              = "Acceleration (Z axis)",
        .which_desc        = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .desc.float32_desc.has_units         = true,
        .desc.float32_desc.units             = "\xE3\x8E\xA8",
        .desc.float32_desc.has_range_min     = true,
        .desc.float32_desc.range_min         = -50.0,
        .desc.float32_desc.has_default_value = false,
        .desc.float32_desc.default_value     = 0,
        .desc.float32_desc.has_range_max     = true,
        .desc.float32_desc.range_max         = 50,
        .desc.float32_desc.has_precision     = true,
        .desc.float32_desc.precision         = 2,
    },
    {
        .id                = PARAM_TIMEZONE_ENABLED,
        .name              = "Timezone Mode",
        .which_desc        = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .desc.bool_desc.has_default_value = true,
        .desc.bool_desc.default_value     = true,
        .desc.bool_desc.has_pei_id        = true,
        .desc.bool_desc.pei_id            = 2,
    },
    {
        .id                = PARAM_TIMEZONE_OFFSET,
        .name              = "Timezone Offset",
        .which_desc         = cr_ParameterDataType_INT32 + cr_ParameterInfo_uint32_desc_tag,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .has_description   = true,
        .description       = "The offset from UTC",
        .desc.int32_desc.has_units = true,
        .desc.int32_desc.units             = "seconds",
        .desc.int32_desc.has_range_min     = true,
        .desc.int32_desc.range_min         = -43200,
        .desc.int32_desc.has_default_value = true,
        .desc.int32_desc.default_value     = 0,
        .desc.int32_desc.has_range_max     = true,
        .desc.int32_desc.range_max         = 43200,
    },
    {
        .id                = PARAM_BT_DEVICE_ADDRESS,
        .name              = "BT Device Address",
        .which_desc         = cr_ParameterDataType_BYTE_ARRAY + cr_ParameterInfo_uint32_desc_tag,
        .desc.bytearray_desc.max_size     = 6,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
    }
};

const cr_ParamExInfoResponse param_ex_desc[NUM_EX_PARAMS] = {
    {
        .pei_id = 0,
        .data_type = cr_ParameterDataType_ENUMERATION,
        .keys_count = 8,
        .keys = {
            {CLI_TEXT_COLOR_DISABLED, "Disabled"},
            {CLI_TEXT_COLOR_RED,      "Red"},
            {CLI_TEXT_COLOR_GREEN,    "Green"},
            {CLI_TEXT_COLOR_YELLOW,   "Yellow"},
            {CLI_TEXT_COLOR_BLUE,     "Blue"},
            {CLI_TEXT_COLOR_MAGENTA,  "Magenta"},
            {CLI_TEXT_COLOR_CYAN,     "Cyan"},
            {CLI_TEXT_COLOR_WHITE,    "White"}
        }
    },
    {
        .pei_id = 1,
        .data_type = cr_ParameterDataType_BIT_FIELD,
        .keys_count = 3,
        .keys = {
            {CLI_TEXT_RGB_STATE_BIT_RED,   "Red"},
            {CLI_TEXT_RGB_STATE_BIT_GREEN, "Green"},
            {CLI_TEXT_RGB_STATE_BIT_BLUE,  "Blue"}
        }
    },
    {
        .pei_id = 2,
        .data_type = cr_ParameterDataType_BOOL,
        .keys_count = 2,
        .keys = {
            {0, "Non-timezoned"},
            {1, "Timezoned"}
    }
    },
    {
        .pei_id = 3,
        .data_type = cr_ParameterDataType_BOOL,
        .keys_count = 2,
        .keys = {
            {0, "Not Identifying"},
            {1, "Identifying"}
        }
    },
    {
        .pei_id = 4,
        .data_type = cr_ParameterDataType_BOOL,
        .keys_count = 2,
        .keys = {
            {0, "Not Pressed"},
            {1, "Pressed"}
        }
    },
    {
        .pei_id = 5,
        .data_type = cr_ParameterDataType_BOOL,
        .keys_count = 2,
        .keys = {
            {0, "Off"},
            {1, "On"}
        }
    },
};

const cr_ParameterNotifyConfig sParamNotifyInit[NUM_INIT_NOTIFICATIONS] =
{
    {
        .parameter_id                = 2,   // button pressed
        .minimum_notification_period = 501,
        .maximum_notification_period = 0,
        .minimum_delta               = 1,
    },
    {
        .parameter_id                = 3,   // LED on
        .minimum_notification_period = 302,
        .maximum_notification_period = 0,
        .minimum_delta               = 1,
    },
    {
        .parameter_id                = 8,   // relative Humidity
        .minimum_notification_period = 2010,
        .maximum_notification_period = 60000,
        .minimum_delta               = 1.0,
    },
    {
        .parameter_id                = 9,   // Temperature
        .minimum_notification_period = 2020,
        .maximum_notification_period = 60000,
        .minimum_delta               = 0.2,
    },
    {
        .parameter_id                = 10,  // Light level
        .minimum_notification_period = 1020,
        .maximum_notification_period = 60000,
        .minimum_delta               = 20.0,
    },
    {
        .parameter_id                = 11,  // UV Index
        .minimum_notification_period = 3031,
        .maximum_notification_period = 60000,
        .minimum_delta               = 1.0,
    },
    {
        .parameter_id                = 12,  // Magnetic Flux
        .minimum_notification_period = 3019,
        .maximum_notification_period = 60000,
        .minimum_delta               = 0.2,
    },
    {
        .parameter_id                = 13,  // Accel X
        .minimum_notification_period = 2037,
        .maximum_notification_period = 0,
        .minimum_delta               = 0.2,
    },
    {
        .parameter_id                = 14,  // Accel Y
        .minimum_notification_period = 2047,
        .maximum_notification_period = 0,
        .minimum_delta               = 0.2,
    },
    {
        .parameter_id                = 15,  // Accel Z
        .minimum_notification_period = 2057,
        .maximum_notification_period = 0,
        .minimum_delta               = 0.2,
    },
};

cr_FileInfo file_descriptions[NUM_FILES] = {
    {
        .file_id            = FILE_IO_TXT,
        .file_name          = "io.txt",
        .current_size_bytes = 512,
        .maximum_size_bytes = 2048,
        .access             = cr_AccessLevel_READ_WRITE,
        .storage_location   = cr_StorageLocation_NONVOLATILE,
        .require_checksum   = false,
    },
    {
        .file_id            = FILE_CYGNUS_REACH_LOGO_PNG,
        .file_name          = "cygnus-reach-logo.png",
        .current_size_bytes = 17900,
        .maximum_size_bytes = 17900,
        .access             = cr_AccessLevel_READ,
        .storage_location   = cr_StorageLocation_NONVOLATILE,
        .require_checksum   = false,
    },
    {
        .file_id            = FILE_DEV_NULL,
        .file_name          = "dev_null",
        .current_size_bytes = 100000,
        .maximum_size_bytes = 100000,
        .access             = cr_AccessLevel_READ_WRITE,
        .storage_location   = cr_StorageLocation_RAM,
        .require_checksum   = false,
    }
};

const cr_CommandInfo command_desc[NUM_COMMANDS] = {
    {
        .id   = COMMAND_RESET_DEFAULTS,
        .name = "Reset Defaults",
    },
    {
        .id   = COMMAND_CLICK_FOR_WISDOM,
        .name = "Click for Wisdom",
    },
    {
        .id   = COMMAND_NO_LOGGING,
        .name = "No Logging",
    },
    {
        .id   = COMMAND_MUCH_LOGGING,
        .name = "Much Logging",
    },
    {
        .id   = COMMAND_NOTIFICATIONS_ON,
        .name = "Notifications On",
    },
    {
        .id   = COMMAND_NOTIFICATIONS_OFF,
        .name = "Notifications Off",
    },
    {
        .id   = COMMAND_REMOTE_CLI_ON,
        .name = "remote CLI On",
    },
    {
        .id   = COMMAND_REMOTE_CLI_OFF,
        .name = "remote CLI Off",
    }
};


#ifdef INCLUDE_STREAM_SERVICE
const cr_StreamInfo streams_desc[NUM_STREAMS] = {
    {
        .stream_id      = 0,
        .access         = cr_AccessLevel_READ,
        .name           = "from device",
        .description    = "counting up for a test"
    },
    {
        .stream_id      = 1,
        .access         = cr_AccessLevel_READ_WRITE,
        .name           = "to device",
        .description    = "throw away receved data"
    }
};
#endif // def INCLUDE_STREAM_SERVICE

#ifdef INCLUDE_WIFI_SERVICE
cr_ConnectionDescription connections[NUM_WIFI_AP];
#endif  // def INCLUDE_WIFI_SERVICE


