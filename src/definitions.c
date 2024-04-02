/********************************************************************************************
 *    _ ____  ___             _         _     ___              _                        _
 *   (_)__ / | _ \_ _ ___  __| |_  _ __| |_  |   \ _____ _____| |___ _ __ _ __  ___ _ _| |_
 *   | ||_ \ |  _/ '_/ _ \/ _` | || / _|  _| | |) / -_) V / -_) / _ \ '_ \ '  \/ -_) ' \  _|
 *   |_|___/ |_| |_| \___/\__,_|\_,_\__|\__| |___/\___|\_/\___|_\___/ .__/_|_|_\___|_||_\__|
 *                                                                  |_|
 *                           -----------------------------------
 *                          Copyright i3 Product Development 2023
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
 * \brief A minimal implementation of Reach data access.  Auto-generated by a Python script.
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
    .protocol_version   = cr_ReachProtoVersion_CURRENT_VERSION,
    .services           = cr_ServiceIds_PARAMETER_REPO | cr_ServiceIds_FILES | cr_ServiceIds_COMMANDS | cr_ServiceIds_CLI | cr_ServiceIds_TIME
};

cr_ParameterValue sCr_param_val[NUM_PARAMS];

cr_ParameterInfo param_desc[NUM_PARAMS] = {
    {
        .id                = PARAM_USER_DEVICE_NAME,
        .name              = "User Device Name",
        .data_type         = cr_ParameterDataType_STRING,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .has_description   = true,
        .description       = "Up to 26 characters",
    },
    {
        .id                = PARAM_UPTIME,
        .name              = "Uptime",
        .data_type         = cr_ParameterDataType_INT64,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .units             = "milliseconds",
    },
    {
        .id                = PARAM_BUTTON_PRESSED,
        .name              = "Button Pressed",
        .data_type         = cr_ParameterDataType_BOOL,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard",
    },
    {
        .id                = PARAM_LED_ON,
        .name              = "LED On",
        .data_type         = cr_ParameterDataType_BOOL,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard",
    },
    {
        .id                = PARAM_IDENTIFY,
        .name              = "Identify",
        .data_type         = cr_ParameterDataType_BOOL,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Turn on to blink the green LED",
    },
    {
        .id                = PARAM_IDENTIFY_INTERVAL,
        .name              = "Identify Interval",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .has_description   = true,
        .description       = "Time between Identify blinks",
        .units             = "seconds",
        .has_range_min     = true,
        .range_min         = 0.01,
        .has_default_value = true,
        .default_value     = 1,
        .has_range_max     = true,
        .range_max         = 60,
    },
    {
        .id                = PARAM_CLI_TEXT_RGB_STATE,
        .name              = "CLI Text RGB State",
        .data_type         = cr_ParameterDataType_BIT_FIELD,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Controls command line color",
        .has_default_value = true,
        .default_value     = 0,
        .has_range_max     = true,
        .range_max         = 7,
    },
    {
        .id                = PARAM_CLI_TEXT_COLOR,
        .name              = "CLI Text Color",
        .data_type         = cr_ParameterDataType_ENUMERATION,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Controls command line color",
        .has_default_value = true,
        .default_value     = 0,
        .has_range_max     = true,
        .range_max         = 7,
    },
    {
        .id                = PARAM_RELATIVE_HUMIDITY,
        .name              = "Relative Humidity",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .units             = "%",
    },
    {
        .id                = PARAM_TEMPERATURE,
        .name              = "Temperature",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .units             = "\xC2\xB0 C",
    },
    {
        .id                = PARAM_LIGHT_LEVEL,
        .name              = "Light Level",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .units             = "lux",
    },
    {
        .id                = PARAM_UV_INDEX,
        .name              = "UV Index",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
    },
    {
        .id                = PARAM_MAGNETIC_FIELD_READING,
        .name              = "Magnetic Field Reading",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .units             = "millitesla",
    },
    {
        .id                = PARAM_ACCELERATION_X_AXIS,
        .name              = "Acceleration (X axis)",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .units             = "\xE3\x8E\xA8",
    },
    {
        .id                = PARAM_ACCELERATION_Y_AXIS,
        .name              = "Acceleration (Y axis)",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .units             = "\xE3\x8E\xA8",
    },
    {
        .id                = PARAM_ACCELERATION_Z_AXIS,
        .name              = "Acceleration (Z axis)",
        .data_type         = cr_ParameterDataType_FLOAT32,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
        .has_description   = true,
        .description       = "Read from Thunderboard Sensor",
        .units             = "\xE3\x8E\xA8",
    },
    {
        .id                = PARAM_TIMEZONE_ENABLED,
        .name              = "Timezone Enabled",
        .data_type         = cr_ParameterDataType_BOOL,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .has_description   = true,
        .description       = "(Time service)",
        .has_default_value = true,
        .default_value     = 1,
    },
    {
        .id                = PARAM_TIMEZONE_OFFSET,
        .name              = "Timezone Offset",
        .data_type         = cr_ParameterDataType_INT32,
        .access            = cr_AccessLevel_READ_WRITE,
        .storage_location  = cr_StorageLocation_NONVOLATILE,
        .has_description   = true,
        .description       = "(Time service) Offset from UTC",
        .units             = "seconds",
        .has_range_min     = true,
        .range_min         = -43200,
        .has_default_value = true,
        .default_value     = 0,
        .has_range_max     = true,
        .range_max         = 43200,
    },
    {
        .id                = PARAM_BT_DEVICE_ADDRESS,
        .name              = "BT Device Address",
        .data_type         = cr_ParameterDataType_BYTE_ARRAY,
        .size_in_bytes     = 6,
        .access            = cr_AccessLevel_READ,
        .storage_location  = cr_StorageLocation_RAM,
    }
};

cr_ParamExInfoResponse param_ex_desc[NUM_EX_PARAMS] = {
    {
        .associated_pid = PARAM_CLI_TEXT_COLOR,
        .data_type = cr_ParameterDataType_ENUMERATION,
        .enumerations_count = 8,
        .enumerations = {
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
        .associated_pid = PARAM_CLI_TEXT_RGB_STATE,
        .data_type = cr_ParameterDataType_BIT_FIELD,
        .enumerations_count = 3,
        .enumerations = {
            {CLI_TEXT_RGB_STATE_BIT_RED,   "Red"},
            {CLI_TEXT_RGB_STATE_BIT_GREEN, "Green"},
            {CLI_TEXT_RGB_STATE_BIT_BLUE,  "Blue"}
        }
    }
};

cr_FileInfo file_descriptions[NUM_FILES] = {
    {
        .file_id            = FILE_IO_TXT,
        .file_name          = "io.txt",
        .current_size_bytes = 512,
        .access             = cr_AccessLevel_READ_WRITE,
        .storage_location   = cr_StorageLocation_NONVOLATILE,
    },
    {
        .file_id            = FILE_CYGNUS_REACH_LOGO_PNG,
        .file_name          = "cygnus-reach-logo.png",
        .current_size_bytes = 17900,
        .access             = cr_AccessLevel_READ,
        .storage_location   = cr_StorageLocation_NONVOLATILE,
    }
};

cr_CommandInfo command_desc[NUM_COMMANDS] = {
    {
        .id   = COMMAND_RESET_DEFAULTS,
        .name = "Reset Defaults",
    },
    {
        .id   = COMMAND_CLICK_FOR_WISDOM,
        .name = "Click for Wisdom",
    }
};

// The stack will call this function.
// The const copy of the basis in flash is copied to RAM so that the device
// can overwrite varying data like SN and hash.
int crcb_device_get_info(const cr_DeviceInfoRequest *request, cr_DeviceInfoResponse *pDi)
{
    (void) request;
    // The app owns the memory here.
    // The address is returned so that the data can come from flash.
    // memcpy as the structure copy imposes a further address alignment requirement.
    // *pDi = device_info;
    memcpy(pDi, &device_info, sizeof(cr_DeviceInfoResponse));
    I3_LOG(LOG_MASK_REACH, "%s: %s\n", __FUNCTION__, device_info.device_name);

    sprintf(pDi->firmware_version, "%d.%d.%d", APP_MAJOR_VERSION, APP_MINOR_VERSION, APP_PATCH_VERSION);

    snprintf(pDi->device_name, REACH_DEVICE_NAME_LEN, "%s", cr_get_advertised_name());
    return 0;
}

void init_param_repo()
{
    int rval = 0;
    rval = app_handle_param_repo_pre_init();
    if (rval)
    {
        I3_LOG(LOG_MASK_ERROR, "App-specific param repo pre-init failed (error %d), continuing with init", rval);
    }
    memset(sCr_param_val, 0, sizeof(sCr_param_val));
    for (int i=0; i<NUM_PARAMS; i++)
    {
        sCr_param_val[i].parameter_id = param_desc[i].id;

        // the PID directly maps to the parameter type, just to make it easy.
        switch (param_desc[i].data_type)
        {
        case cr_ParameterDataType_UINT32:
            sCr_param_val[i].which_value = cr_ParameterValue_uint32_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.uint32_value = (uint32_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_INT32:
            sCr_param_val[i].which_value = cr_ParameterValue_sint32_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.sint32_value = (int32_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_FLOAT32:
            sCr_param_val[i].which_value = cr_ParameterValue_float32_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.float32_value = (float)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_UINT64:
            sCr_param_val[i].which_value = cr_ParameterValue_uint64_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.uint64_value = (uint64_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_INT64:
            sCr_param_val[i].which_value = cr_ParameterValue_sint64_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.sint64_value = (int64_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_FLOAT64:
            sCr_param_val[i].which_value = cr_ParameterValue_float64_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.float64_value = param_desc[i].default_value;
            break;
        case cr_ParameterDataType_BOOL:
            sCr_param_val[i].which_value = cr_ParameterValue_bool_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.bool_value = (bool)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_STRING:
            sCr_param_val[i].which_value = cr_ParameterValue_string_value_tag;
            break;
        case cr_ParameterDataType_ENUMERATION:
            sCr_param_val[i].which_value = cr_ParameterValue_enum_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.enum_value = (uint32_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_BIT_FIELD:
            sCr_param_val[i].which_value = cr_ParameterValue_bitfield_value_tag;
            if (param_desc[i].has_default_value)
                sCr_param_val[i].value.bitfield_value = (uint32_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_BYTE_ARRAY:
            sCr_param_val[i].value.bytes_value.size = param_desc[i].size_in_bytes;
            sCr_param_val[i].which_value = cr_ParameterValue_bytes_value_tag;
            break;
        default:
            affirm(0);  // should not happen.
            break;
        }  // end switch

        if (param_desc[i].storage_location == cr_StorageLocation_STORAGE_LOCATION_INVALID || param_desc[i].storage_location > cr_StorageLocation_NONVOLATILE_EXTENDED)
        {
          I3_LOG(LOG_MASK_ERROR, "At param index %d, invalid storage location %d.",
                 i, param_desc[i].storage_location);
        }

        rval = app_handle_param_repo_init(&sCr_param_val[i], &param_desc[i]);
        if (rval != 0)
            I3_LOG(LOG_MASK_ERROR, "At param index %d, failed to initialize data (error %d)", i, rval);

    } // end for
    rval = app_handle_param_repo_post_init();
    if (rval)
    {
        I3_LOG(LOG_MASK_ERROR, "App-specific param repo pre-init failed (error %d), continuing with init", rval);
    }
}

// Populate a parameter value structure
int crcb_parameter_read(const uint32_t pid, cr_ParameterValue *data)
{
    affirm(data != NULL);
    if (pid >= NUM_PARAMS)
        return cr_ErrorCodes_INVALID_PARAMETER;
    int rval = app_handle_param_repo_read(&sCr_param_val[pid]);
    *data = sCr_param_val[pid];
    return rval;
}

int crcb_parameter_write(const uint32_t pid, const cr_ParameterValue *data)
{   
    if (pid >= NUM_PARAMS)
        return cr_ErrorCodes_INVALID_PARAMETER;
    int rval = 0;
    I3_LOG(LOG_MASK_PARAMS, "Write param, pid %d (%d)", pid, data->parameter_id);
    I3_LOG(LOG_MASK_PARAMS, "  timestamp %d", data->timestamp);
    I3_LOG(LOG_MASK_PARAMS, "  which %d", data->which_value);
    rval = app_handle_param_repo_write((cr_ParameterValue *) data);
    if (rval != 0)
    {
        // Invalid data or NVM storage failed
        return rval;
    }
    sCr_param_val[pid].timestamp = data->timestamp;
    sCr_param_val[pid].which_value = data->which_value;

    switch (data->which_value)
    {
        case cr_ParameterValue_uint32_value_tag:
            sCr_param_val[pid].value.uint32_value = data->value.uint32_value;
            break;
        case cr_ParameterValue_sint32_value_tag:
            sCr_param_val[pid].value.sint32_value = data->value.sint32_value;
            break;
        case cr_ParameterValue_float32_value_tag:
            sCr_param_val[pid].value.float32_value = data->value.float32_value;
            break;
        case cr_ParameterValue_uint64_value_tag:
            sCr_param_val[pid].value.uint64_value = data->value.uint64_value;
            break;
        case cr_ParameterValue_sint64_value_tag:
            sCr_param_val[pid].value.sint64_value = data->value.sint64_value;
            break;
        case cr_ParameterValue_float64_value_tag:
            sCr_param_val[pid].value.float64_value = data->value.float64_value;
            break;
        case cr_ParameterValue_bool_value_tag:
            sCr_param_val[pid].value.bool_value = data->value.bool_value;
            break;
        case cr_ParameterValue_string_value_tag:
            memcpy(sCr_param_val[pid].value.string_value,
                   data->value.string_value, REACH_PVAL_STRING_LEN);
            sCr_param_val[pid].value.string_value[REACH_PVAL_STRING_LEN-1] = 0;
            I3_LOG(LOG_MASK_PARAMS, "String value: %s",
                   sCr_param_val[pid].value.string_value);
            break;
        case cr_ParameterValue_bitfield_value_tag:
            sCr_param_val[pid].value.bitfield_value = data->value.bitfield_value;
            break;
        case cr_ParameterValue_enum_value_tag:
            sCr_param_val[pid].value.enum_value = data->value.enum_value;
            break;
        case cr_ParameterValue_bytes_value_tag:
            memcpy(sCr_param_val[pid].value.bytes_value.bytes,
                   data->value.bytes_value.bytes, 
                   REACH_PVAL_BYTES_LEN);
            if (data->value.bytes_value.size > REACH_PVAL_BYTES_LEN)
            {
                LOG_ERROR("Parameter write of bytes has invalid size %d > %d",
                          data->value.bytes_value.size, REACH_PVAL_BYTES_LEN);
                sCr_param_val[pid].value.bytes_value.size = REACH_PVAL_BYTES_LEN;
            }
            else
            {
                sCr_param_val[pid].value.bytes_value.size = data->value.bytes_value.size;
            }
            LOG_DUMP_MASK(LOG_MASK_PARAMS, "bytes value",
                          sCr_param_val[pid].value.bytes_value.bytes,
                          sCr_param_val[pid].value.bytes_value.size);
            break;
        default:
            LOG_ERROR("Parameter write which_value %d not recognized.", 
                          data->which_value);
            rval = 1;
            break;
    }  // end switch
    return rval;
}

// return a number that changes if the parameter descriptions have changed.
uint32_t crcb_compute_parameter_hash(void)
{
    // Note that the layout of the structure param_desc differs by compiler.
    // The hash computed on windows won't match that computed on SiLabs.
    uint32_t *ptr = (uint32_t*)param_desc;
    // char *cptr = (char*)param_desc;
    size_t sz = sizeof(param_desc)/(sizeof(uint32_t));
    // LOG_DUMP_MASK(LOG_MASK_PARAMS, "Raw Params", cptr, sizeof(param_desc));

    uint32_t hash = ptr[0];
    for (size_t i= 1; i<sz; i++)
        hash ^= ptr[i];

#ifdef NUM_EX_PARAMS
    ptr = (uint32_t*)param_ex_desc;
    size_t sz1 = sizeof(param_ex_desc)/(sizeof(uint32_t));

    for (size_t i= 0; i<sz1; i++)
        hash ^= ptr[i];

    I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x over %d+%d = %d words.\n",
           __FUNCTION__, hash, sz, sz1, sz+sz1);
#else
    I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x over %d words.\n",
           __FUNCTION__, hash, sz);
#endif // NUM_EX_PARAMS

    return hash;
}

static int sCurrentParameter = 0;

// Gets the parameter description for the next parameter.
// Allows the stack to iterate through the parameter list.
// The caller provides a cr_ParameterInfo containing string pointers that will be overwritten.
// The app owns the string pointers which must not be on the stack.
int crcb_parameter_discover_next(cr_ParameterInfo *ppDesc)
{
    if (sCurrentParameter >= NUM_PARAMS)
    {
        I3_LOG(LOG_MASK_PARAMS, "%s: sCurrentParameter (%d) >= NUM_PARAMS (%d)",
               __FUNCTION__, sCurrentParameter, NUM_PARAMS);
        return cr_ErrorCodes_NO_DATA;
    }
    *ppDesc = param_desc[sCurrentParameter];
    sCurrentParameter++;
    return 0;
}


int crcb_parameter_get_count()
{
    return NUM_PARAMS;
}
// Resets the application's pointer into the parameter table such that
// the next call to crcb_parameter_discover_next() will return the
// description of this parameter.
int crcb_parameter_discover_reset(const uint32_t pid)
{
    if (pid >= NUM_PARAMS)
    {
        sCurrentParameter = 0;
        I3_LOG(LOG_MASK_PARAMS, "dp reset(%d) reset defaults to %d", pid, sCurrentParameter);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }
    sCurrentParameter = pid;
    I3_LOG(LOG_MASK_PARAMS, "dp reset to %d", sCurrentParameter);
    int i;
    sCurrentParameter = 0;  // in case none match
    for (i = 0; i < NUM_PARAMS; i++)
    {
        if (param_desc[i].id == pid) {
            sCurrentParameter = i;
            I3_LOG(LOG_MASK_PARAMS, "dp reset(%d) reset to %d", pid, sCurrentParameter);
            return 0;
        }
    }
    I3_LOG(LOG_MASK_PARAMS, "dp reset(%d) reset defaults to %d", pid, sCurrentParameter);
    return cr_ErrorCodes_INVALID_PARAMETER;
}

// In parallel to the parameter discovery, use this to find out 
// about enumerations and bitfields
static int sCurrentExParam = 0;
static int sRequestedParamPid = -1; // negative means all

int crcb_parameter_ex_get_count(const int32_t pid)
{
#ifdef NUM_EX_PARAMS
    if (pid < 0)  // all 
        return NUM_EX_PARAMS;

    int num_ex_msgs = 0;

    for (int i=0; i<NUM_EX_PARAMS; i++) {
        if ((int32_t)param_ex_desc[i].associated_pid == pid) {
            num_ex_msgs++;
        }
    }
    return num_ex_msgs;
#else
    return 0;
#endif // NUM_EX_PARAMS
}

int crcb_parameter_ex_discover_reset(const int32_t pid)
{
    // unlike the full params, reset of param_ex always goes to zero.
    sCurrentExParam = 0;
    sRequestedParamPid = pid;
    return 0;
}

int crcb_parameter_ex_discover_next(cr_ParamExInfoResponse *pDesc)
{
    affirm(pDesc);
    pDesc->enumerations_count = 0;
#ifdef NUM_EX_PARAMS
    if (sCurrentExParam>=NUM_EX_PARAMS)
    {
        I3_LOG(LOG_MASK_PARAMS, "%s: No more ex params.", __FUNCTION__);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    if (sRequestedParamPid < 0)
    {
        I3_LOG(LOG_MASK_PARAMS, "%s: For all, return param_ex %d.", __FUNCTION__, sCurrentExParam);
        *pDesc = param_ex_desc[sCurrentExParam];
        sCurrentExParam++;
        return 0;
    }

    for (int i=sCurrentExParam; i<NUM_EX_PARAMS; i++)
    {
        if ((int32_t)param_ex_desc[i].associated_pid == sRequestedParamPid)
        {
            I3_LOG(LOG_MASK_PARAMS, "%s: For pid %d, return param_ex %d.",
                   __FUNCTION__, sRequestedParamPid, sCurrentExParam);
            *pDesc = param_ex_desc[i];
            sCurrentExParam = i+1;;
            return 0;
        }
    }
    // should not get here.
    I3_LOG(LOG_MASK_PARAMS, "%s: No more ex params 2.", __FUNCTION__);
#endif // NUM_EX_PARAMS
    return cr_ErrorCodes_INVALID_PARAMETER;
}

int crcb_file_get_description(uint32_t fid, cr_FileInfo *file_desc)
{
    if (fid > NUM_FILES)
        return cr_ErrorCodes_BAD_FILE;
    *file_desc = file_descriptions[fid];
    return 0;
}

int crcb_file_get_file_count()
{
    return NUM_FILES;
}

static uint8_t sFid_index = 0;
int crcb_file_discover_reset(const uint8_t fid)
{
    if (fid > NUM_FILES)
    {
        I3_LOG(LOG_MASK_ERROR, "crcb_file_discover_reset(%d): invalid FID, using 0.", fid);
        sFid_index = 0;
        return cr_ErrorCodes_BAD_FILE;
    }
    sFid_index = fid;
    return 0;
}

int crcb_file_discover_next(cr_FileInfo *file_desc)
{
    if (sFid_index >= NUM_FILES)
    {
        I3_LOG(LOG_MASK_WARN, "%s: sFid_index (%d) >= NUM_FILES (%d)",
               __FUNCTION__, sFid_index, NUM_FILES);
        return cr_ErrorCodes_NO_DATA;
    }
    *file_desc = file_descriptions[sFid_index];
    sFid_index++;
    return 0;
}


uint8_t sCommandIndex = 0;

int crcb_get_command_count()
{
    return NUM_COMMANDS;
}

int crcb_command_discover_next(cr_CommandInfo *cmd_desc)
{
    if (sCommandIndex >= NUM_COMMANDS)
    {
        I3_LOG(LOG_MASK_REACH, "%s: Command index %d indicates discovery complete.",
               __FUNCTION__, sCommandIndex);
        return cr_ErrorCodes_NO_DATA;
    }
    *cmd_desc = command_desc[sCommandIndex++];
    return 0;
}

int crcb_command_discover_reset(const uint32_t cid)
{
    if (cid >= NUM_COMMANDS)
    {
        i3_log(LOG_MASK_ERROR, "%s: Command ID %d does not exist.",
               __FUNCTION__, cid);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }
    sCommandIndex = cid;
    return 0;
}

int __attribute__((weak)) app_handle_param_repo_pre_init(void)
{
    return 0;
}
int __attribute__((weak)) app_handle_param_repo_init(cr_ParameterValue *data, cr_ParameterInfo *desc)
{
    (void) desc;
    return app_handle_param_repo_read(data);
}

int __attribute__((weak)) app_handle_param_repo_post_init(void)
{
    return 0;
}

int __attribute__((weak)) app_handle_param_repo_read(cr_ParameterValue *data)
{
    (void) data;
    return 0;
}

int __attribute__((weak)) app_handle_param_repo_write(cr_ParameterValue *data)
{
    (void) data;
    return 0;
}