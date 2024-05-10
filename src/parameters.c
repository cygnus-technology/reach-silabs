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
 *
 ********************************************************************************************/

#include "definitions.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "i3_log.h"
#include "app_version.h"
#include "cr_stack.h"

#define PARAM_EI_TO_NUM_PEI_RESPONSES(param_ex) ((param_ex.num_labels / 8) + ((param_ex.num_labels % 8) ? 1:0))

// Extra includes and forward declarations here.
// User code start [P1]

#include "sl_bluetooth.h"
#include "sl_sensor_hall.h"
#include "sl_sensor_light.h"
#include "sl_sensor_rht.h"
#include "sl_imu.h"
#include "app.h"

#include "cr_stack.h"
#include "definitions.h"
#include "i3_log.h"
#include "reach_silabs.h"

#define PARAM_REPO_USE_NVM_STORAGE

#ifdef PARAM_REPO_USE_NVM_STORAGE
#include "nvm3_generic.h"

#define PARAM_REPO_HASH_KEY 0xFFFFF

static uint32_t calculate_nvm_hash(void);

static bool nvm_reset_required = false;
static bool nvm_failed = false;
#endif // PARAM_REPO_USE_NVM_STORAGE

char get_cli_text_color_response[] = TEXT_BLACK;

char* param_repo_get_cli_text_color(void)
{
    memcpy(get_cli_text_color_response, TEXT_BLACK, sizeof(TEXT_BLACK));
    switch (sCr_param_val[PARAM_COMMAND_LINE_COLOR].value.enum_value)
    {
    case CLI_COLOR_OFF:
        memset(get_cli_text_color_response, 0, sizeof(get_cli_text_color_response));
        break;
    default:
        // Change one character to get the color right
        get_cli_text_color_response[3] = '0' + sCr_param_val[PARAM_COMMAND_LINE_COLOR].value.enum_value;
        break;
    }
    return get_cli_text_color_response;
}

int param_repo_reset_nvm(void);
int app_handle_param_repo_pre_init(void);
int app_handle_param_repo_init(cr_ParameterValue *data, const cr_ParameterInfo *desc);
int app_handle_param_repo_post_init(void);
int app_handle_param_repo_read(cr_ParameterValue *data);
int app_handle_param_repo_write(cr_ParameterValue *data);
// User code end [P1]

static int sFindIndexFromPid(uint32_t pid, uint32_t *index)
{
    uint32_t idx;
    for (idx = 0; idx < NUM_PARAMS; idx++)
    {
        if (param_desc[idx].id == pid)
        {
            *index = idx;
            return 0;
        }
    }
    return cr_ErrorCodes_INVALID_ID;
}

static int sFindIndexFromPeiId(uint32_t pei_id, uint32_t *index)
{
    uint32_t idx;
    for (idx = 0; idx < NUM_EX_PARAMS; idx++)
    {
        if (param_ex_desc[idx].pei_id == pei_id)
        {
            *index = idx;
            return 0;
        }
    }
    return cr_ErrorCodes_INVALID_ID;
}

void init_param_repo()
{
    int rval = 0;
    // rval = app_handle_param_repo_pre_init();
    // User code start [P2]
    rval = app_handle_param_repo_pre_init();
    // User code end [P2]
    if (rval)
    {
        I3_LOG(LOG_MASK_ERROR, "App-specific param repo pre-init failed (error %d), continuing with init", rval);
    }
    memset(sCr_param_val, 0, sizeof(sCr_param_val));
    for (int i = 0; i < NUM_PARAMS; i++)
    {
        sCr_param_val[i].parameter_id = param_desc[i].id;

        // the PID directly maps to the parameter type, just to make it easy.
        switch ((param_desc[i].which_desc - cr_ParameterInfo_uint32_desc_tag))
        {
        case cr_ParameterDataType_UINT32:
            if (param_desc[i].desc.uint32_desc.has_default_value)
                sCr_param_val[i].value.uint32_value = param_desc[i].desc.uint32_desc.default_value;
            break;
        case cr_ParameterDataType_INT32:
            if (param_desc[i].desc.int32_desc.has_default_value)
                sCr_param_val[i].value.int32_value = param_desc[i].desc.int32_desc.default_value;
            break;
        case cr_ParameterDataType_FLOAT32:
            if (param_desc[i].desc.float32_desc.has_default_value)
                sCr_param_val[i].value.float32_value = param_desc[i].desc.float32_desc.default_value;
            break;
        case cr_ParameterDataType_UINT64:
            if (param_desc[i].desc.uint64_desc.has_default_value)
                sCr_param_val[i].value.uint64_value = param_desc[i].desc.uint64_desc.default_value;
            break;
        case cr_ParameterDataType_INT64:
            if (param_desc[i].desc.int64_desc.has_default_value)
                sCr_param_val[i].value.int64_value = param_desc[i].desc.int64_desc.default_value;
            break;
        case cr_ParameterDataType_FLOAT64:
            if (param_desc[i].desc.float64_desc.has_default_value)
                sCr_param_val[i].value.float64_value = param_desc[i].desc.float64_desc.default_value;
            break;
        case cr_ParameterDataType_BOOL:
            if (param_desc[i].desc.bool_desc.has_default_value)
                sCr_param_val[i].value.bool_value = param_desc[i].desc.bool_desc.default_value;
            break;
        case cr_ParameterDataType_STRING:
            if (param_desc[i].desc.string_desc.has_default_value)
            {
                memset(sCr_param_val[i].value.string_value, 0, sizeof(sCr_param_val[i].value.string_value));
                memcpy(sCr_param_val[i].value.string_value, param_desc[i].desc.string_desc.default_value, sizeof(param_desc[i].desc.string_desc.default_value));
            }
            break;
        case cr_ParameterDataType_ENUMERATION:
            if (param_desc[i].desc.enum_desc.has_default_value)
                sCr_param_val[i].value.enum_value = param_desc[i].desc.enum_desc.default_value;
            break;
        case cr_ParameterDataType_BIT_FIELD:
            if (param_desc[i].desc.bitfield_desc.has_default_value)
                sCr_param_val[i].value.bitfield_value = param_desc[i].desc.bitfield_desc.default_value;
            break;
        case cr_ParameterDataType_BYTE_ARRAY:
            if (param_desc[i].desc.bytearray_desc.has_default_value)
            {
                sCr_param_val[i].value.bytes_value.size = param_desc[i].desc.bytearray_desc.default_value.size;
                memcpy(sCr_param_val[i].value.bytes_value.bytes, param_desc[i].desc.bytearray_desc.default_value.bytes, sizeof(param_desc[i].desc.bytearray_desc.default_value.bytes));
            }
            else
            {
                sCr_param_val[i].value.bytes_value.size = param_desc[i].desc.bytearray_desc.max_size;
                memset(sCr_param_val[i].value.bytes_value.bytes, 0, sCr_param_val[i].value.bytes_value.size);
            }
            break;
        default:
            affirm(0);  // should not happen.
            break;
        }  // end switch

        // Convert from description type identifier to value type identifier
        sCr_param_val[i].which_value = (param_desc[i].which_desc - cr_ParameterInfo_uint32_desc_tag) + cr_ParameterValue_uint32_value_tag;

        if (param_desc[i].storage_location == cr_StorageLocation_STORAGE_LOCATION_INVALID || param_desc[i].storage_location > cr_StorageLocation_NONVOLATILE_EXTENDED)
        {
            I3_LOG(LOG_MASK_ERROR, "At param index %d, invalid storage location %d.",
                   i, param_desc[i].storage_location);
        }

        // rval = app_handle_param_repo_init(&sCr_param_val[i], &param_desc[i]);
        // User code start [P3]
        rval = app_handle_param_repo_init(&sCr_param_val[i], &param_desc[i]);
        // User code end [P3]

        if (rval != 0)
        {
            I3_LOG(LOG_MASK_ERROR, "At param index %d, failed to initialize data (error %d)", i, rval);
        }

    } // end for

    // rval = app_handle_param_repo_post_init();
    // User code start [P4]
    rval = app_handle_param_repo_post_init();
    // User code end [P4]
    if (rval)
    {
        I3_LOG(LOG_MASK_ERROR, "App-specific param repo pre-init failed (error %d), continuing with init", rval);
    }
}

const char* param_repo_get_ex_label(uint32_t pei_id, uint32_t value)
{
    uint32_t index = 0;
    int rval = sFindIndexFromPeiId(pei_id, &index);
    if (rval) 
        return 0;

    for (int i = 0; i < param_ex_desc[index].num_labels; i++)
    {
        if (value == param_ex_desc[index].labels[i].id) return param_ex_desc[index].labels[i].name;
    }
    return 0;
}

// Populate a parameter value structure
int crcb_parameter_read(const uint32_t pid, cr_ParameterValue *data)
{
    int rval = 0;
    affirm(data != NULL);
    uint32_t idx;
    rval = sFindIndexFromPid(pid, &idx);
    if (0 != rval) 
        return rval;

    //rval = app_handle_param_repo_read(&sCr_param_val[idx]);
    // User code start [P5]
    rval = app_handle_param_repo_read(&sCr_param_val[idx]);
    // User code end [P5]

    *data = sCr_param_val[idx];
    return rval;
}

int crcb_parameter_write(const uint32_t pid, const cr_ParameterValue *data)
{
    int rval = 0;
    uint32_t idx;
    rval = sFindIndexFromPid(pid, &idx);
    if (0 != rval) return rval;
    I3_LOG(LOG_MASK_PARAMS, "Write param, pid %d (%d)", idx, data->parameter_id);
    I3_LOG(LOG_MASK_PARAMS, "  timestamp %d", data->timestamp);
    I3_LOG(LOG_MASK_PARAMS, "  which %d", data->which_value);

    // rval = app_handle_param_repo_write((cr_ParameterValue *) data);
    // User code start [P6]
    rval = app_handle_param_repo_write((cr_ParameterValue *)data);
    // User code end [P6]

    if (rval != 0)
    {
        // Invalid data or NVM storage failed
        return rval;
    }
    sCr_param_val[idx].timestamp = data->timestamp;
    sCr_param_val[idx].which_value = data->which_value;

    switch ((data->which_value - cr_ParameterValue_uint32_value_tag))
    {
    case cr_ParameterDataType_UINT32:
        sCr_param_val[idx].value.uint32_value = data->value.uint32_value;
        break;
    case cr_ParameterDataType_INT32:
        sCr_param_val[idx].value.int32_value = data->value.int32_value;
        break;
    case cr_ParameterDataType_FLOAT32:
        sCr_param_val[idx].value.float32_value = data->value.float32_value;
        break;
    case cr_ParameterDataType_UINT64:
        sCr_param_val[idx].value.uint64_value = data->value.uint64_value;
        break;
    case cr_ParameterDataType_INT64:
        sCr_param_val[idx].value.int64_value = data->value.int64_value;
        break;
    case cr_ParameterDataType_FLOAT64:
        sCr_param_val[idx].value.float64_value = data->value.float64_value;
        break;
    case cr_ParameterDataType_BOOL:
        sCr_param_val[idx].value.bool_value = data->value.bool_value;
        break;
    case cr_ParameterDataType_STRING:
        memcpy(sCr_param_val[idx].value.string_value,
               data->value.string_value, REACH_PVAL_STRING_LEN);
        sCr_param_val[idx].value.string_value[REACH_PVAL_STRING_LEN - 1] = 0;
        I3_LOG(LOG_MASK_PARAMS, "String value: %s",
               sCr_param_val[idx].value.string_value);
        break;
    case cr_ParameterDataType_BIT_FIELD:
        sCr_param_val[idx].value.bitfield_value = data->value.bitfield_value;
        break;
    case cr_ParameterDataType_ENUMERATION:
        sCr_param_val[idx].value.enum_value = data->value.enum_value;
        break;
    case cr_ParameterDataType_BYTE_ARRAY:
        memcpy(sCr_param_val[idx].value.bytes_value.bytes,
               data->value.bytes_value.bytes,
               REACH_PVAL_BYTES_LEN);
        if (data->value.bytes_value.size > REACH_PVAL_BYTES_LEN)
        {
            LOG_ERROR("Parameter write of bytes has invalid size %d > %d",
                      data->value.bytes_value.size, REACH_PVAL_BYTES_LEN);
            sCr_param_val[idx].value.bytes_value.size = REACH_PVAL_BYTES_LEN;
        }
        else
        {
            sCr_param_val[idx].value.bytes_value.size = data->value.bytes_value.size;
        }
        LOG_DUMP_MASK(LOG_MASK_PARAMS, "bytes value",
                      sCr_param_val[idx].value.bytes_value.bytes,
                      sCr_param_val[idx].value.bytes_value.size);
        break;
    default:
        LOG_ERROR("Parameter write which_value %d not recognized.",
                  data->which_value);
        rval = 1;
        break;
    }  // end switch
    return rval;
}


int crcb_parameter_get_count()
{
    int i;
    int numAvailable = 0;
    for (i = 0; i < NUM_PARAMS; i++)
    {
        if (crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, param_desc[i].id)) 
            numAvailable++;
    }
    return numAvailable;
}

// return a number that changes if the parameter descriptions have changed.
uint32_t crcb_compute_parameter_hash(void)
{
    // Note that the layout of the structure param_desc differs by compiler.
    // The hash computed on windows won't match that computed on SiLabs.
    uint32_t *ptr = (uint32_t *)param_desc;
    // LOG_DUMP_MASK(LOG_MASK_PARAMS, "Raw Params", cptr, sizeof(param_desc));

    // The hash should be different based on access permission
    uint32_t hash = 0;
    for (size_t jj = 0; jj < NUM_PARAMS; jj++)
    {
        if (crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, jj))
        {
            for (size_t i = 0; i < (sizeof(cr_ParameterInfo) / sizeof(uint32_t)); i++) 
                hash ^= ptr[i];
        }
    }

#ifdef NUM_EX_PARAMS
    for (int i = 0; i < NUM_EX_PARAMS; i++)
    {
        hash ^= param_ex_desc[i].pei_id;
        hash ^= (uint32_t)param_ex_desc[i].data_type;
        hash ^= (uint32_t)param_ex_desc[i].num_labels;
        for (int j = 0; j < param_ex_desc[i].num_labels; j++)
        {
            ptr = (uint32_t *)&param_ex_desc[i].labels[j];
            for (size_t k = 0; k < (sizeof(cr_ParamExKey) / sizeof(uint32_t)); k++) 
                hash ^= ptr[i];
        }
    }

    I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x includes EX.\n",
           __FUNCTION__, hash);
#else
    I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x excludes EX.\n",
           __FUNCTION__, hash);
#endif // NUM_EX_PARAMS

    return hash;
}

static int sCurrentParameter = 0;

// Resets the application's pointer into the parameter table such that
// the next call to crcb_parameter_discover_next() will return the
// description of this parameter.
int crcb_parameter_discover_reset(const uint32_t pid)
{
    int rval = 0;
    uint32_t idx;
    rval = sFindIndexFromPid(pid, &idx);
    if (0 != rval)
    {
        sCurrentParameter = 0;
        I3_LOG(LOG_MASK_PARAMS, "dp reset(%d) reset > defaults to %d", pid, sCurrentParameter);
        return rval;
    }
    sCurrentParameter = idx;
    return 0;
}

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
    while (!crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, param_desc[sCurrentParameter].id))
    {
        I3_LOG(LOG_MASK_PARAMS, "%s: sCurrentParameter (%d) skip, access not granted",
               __FUNCTION__, sCurrentParameter);
        sCurrentParameter++;
        if (sCurrentParameter >= NUM_PARAMS)
        {
            I3_LOG(LOG_MASK_PARAMS, "%s: skipped to sCurrentParameter (%d) >= NUM_PARAMS (%d)",
                   __FUNCTION__, sCurrentParameter, NUM_PARAMS);
            return cr_ErrorCodes_NO_DATA;
        }
    }
    *ppDesc = param_desc[sCurrentParameter];
    sCurrentParameter++;
    return 0;
}

// In parallel to the parameter discovery, use this to find out
// about enumerations and bitfields
static int requested_pei_id = -1;
static int current_pei_index = 0;
static int current_pei_key_index = 0;

int crcb_parameter_ex_get_count(const int32_t pid)
{
#ifdef NUM_EX_PARAMS
    if (pid < 0)  // all
    {
        int rval = 0;
        for (int i = 0; i < NUM_EX_PARAMS; i++) 
            rval += PARAM_EI_TO_NUM_PEI_RESPONSES(param_ex_desc[i]);
        return rval;
    }

    for (int i = 0; i < NUM_EX_PARAMS; i++)
    {
        if ((int)param_ex_desc[i].pei_id == pid)
            return PARAM_EI_TO_NUM_PEI_RESPONSES(param_ex_desc[i]);
    }
    return 0;
#else
    return 0;
#endif // NUM_EX_PARAMS
}

int crcb_parameter_ex_discover_reset(const int32_t pid)
{
#ifdef NUM_EX_PARAMS
    requested_pei_id = pid;
    if (pid < 0) current_pei_index = 0;
    else
    {
        current_pei_index = -1;
        for (int i = 0; i < NUM_EX_PARAMS; i++)
        {
            if ((int)param_ex_desc[i].pei_id == pid)
            {
                current_pei_index = i;
                break;
            }
        }
    }
    current_pei_key_index = 0;
#endif // NUM_EX_PARAMS
    return 0;
}

int crcb_parameter_ex_discover_next(cr_ParamExInfoResponse *pDesc)
{
    affirm(pDesc);
#ifdef NUM_EX_PARAMS
    if (current_pei_index < 0)
    {
        I3_LOG(LOG_MASK_PARAMS, "%s: No more ex params.", __FUNCTION__);
        return cr_ErrorCodes_INVALID_ID;
    }
    else
    {
        pDesc->pei_id = param_ex_desc[current_pei_index].pei_id;
        pDesc->data_type = param_ex_desc[current_pei_index].data_type;
        pDesc->keys_count = param_ex_desc[current_pei_index].num_labels - current_pei_key_index;
        if (pDesc->keys_count > 8) 
            pDesc->keys_count = 8;
        memcpy(&pDesc->keys, &param_ex_desc[current_pei_index].labels[current_pei_key_index], pDesc->keys_count * sizeof(cr_ParamExKey));
        current_pei_key_index += pDesc->keys_count;
        if (current_pei_key_index >= param_ex_desc[current_pei_index].num_labels)
        {
            if (requested_pei_id == -1)
            {
                // Advance to the next pei_id index
                current_pei_index++;
                if (current_pei_index >= NUM_EX_PARAMS) current_pei_index = -1;
            }
            else
            {
                // Out of data for the selected pei_id
                current_pei_index = -1;
            }
            current_pei_key_index = 0;
        }
    }
    return 0;
#else
    return cr_ErrorCodes_INVALID_ID;
#endif // NUM_EX_PARAMS
}

// User functions here
// User code start [P7]

int param_repo_reset_nvm(void)
{
    for (uint16_t i = 0; i < NUM_PARAMS; i++)
    {
        if (param_desc[i].storage_location != cr_StorageLocation_NONVOLATILE) continue;
        cr_ParameterValue param;
        param.parameter_id = sCr_param_val[i].parameter_id;
        param.which_value = sCr_param_val[param.parameter_id].which_value;
        param.timestamp = (uint32_t)rsl_get_system_uptime();
        I3_LOG(LOG_MASK_PARAMS, "Resetting ID %u, type %u", param.parameter_id, param.which_value);
        // Fill in default value if it's defined
        switch (param.which_value)
        {
        case cr_ParameterValue_uint32_value_tag:
            if (param_desc[i].desc.uint32_desc.has_default_value) sCr_param_val[i].value.uint32_value = param_desc[i].desc.uint32_desc.default_value;
            break;
        case cr_ParameterValue_int32_value_tag:
            if (param_desc[i].desc.int32_desc.has_default_value) sCr_param_val[i].value.int32_value = param_desc[i].desc.int32_desc.default_value;
            break;
        case cr_ParameterValue_float32_value_tag:
            if (param_desc[i].desc.float32_desc.has_default_value) sCr_param_val[i].value.float32_value = param_desc[i].desc.float32_desc.default_value;
            break;
        case cr_ParameterValue_uint64_value_tag:
            if (param_desc[i].desc.uint64_desc.has_default_value) sCr_param_val[i].value.uint64_value = param_desc[i].desc.uint64_desc.default_value;
            break;
        case cr_ParameterValue_int64_value_tag:
            if (param_desc[i].desc.int64_desc.has_default_value) sCr_param_val[i].value.int64_value = param_desc[i].desc.int64_desc.default_value;
            break;
        case cr_ParameterValue_float64_value_tag:
            if (param_desc[i].desc.float64_desc.has_default_value) sCr_param_val[i].value.float64_value = param_desc[i].desc.float64_desc.default_value;
            break;
        case cr_ParameterValue_bool_value_tag:
            if (param_desc[i].desc.bool_desc.has_default_value) sCr_param_val[i].value.bool_value = param_desc[i].desc.bool_desc.default_value;
            break;
        case cr_ParameterValue_string_value_tag:
            if (param_desc[i].desc.string_desc.has_default_value)
            {
                memset(sCr_param_val[i].value.string_value, 0, sizeof(sCr_param_val[i].value.string_value));
                memcpy(sCr_param_val[i].value.string_value, param_desc[i].desc.string_desc.default_value, sizeof(param_desc[i].desc.string_desc.default_value));
            }
            break;
        case cr_ParameterValue_enum_value_tag:
            if (param_desc[i].desc.enum_desc.has_default_value) sCr_param_val[i].value.enum_value = param_desc[i].desc.enum_desc.default_value;
            break;
        case cr_ParameterValue_bitfield_value_tag:
            if (param_desc[i].desc.bitfield_desc.has_default_value) sCr_param_val[i].value.bitfield_value = param_desc[i].desc.bitfield_desc.default_value;
            break;
        case cr_ParameterValue_bytes_value_tag:
            if (param_desc[i].desc.bytearray_desc.has_default_value)
            {
                sCr_param_val[i].value.bytes_value.size = param_desc[i].desc.bytearray_desc.default_value.size;
                memcpy(sCr_param_val[i].value.bytes_value.bytes, param_desc[i].desc.bytearray_desc.default_value.bytes, sizeof(param_desc[i].desc.bytearray_desc.default_value.bytes));
            }
            else
            {
                sCr_param_val[i].value.bytes_value.size = param_desc[i].desc.bytearray_desc.max_size;
                memset(sCr_param_val[i].value.bytes_value.bytes, 0, sCr_param_val[i].value.bytes_value.size);
            }
            break;
        default:
            affirm(0);  // should not happen.
            break;
        }
        int rval = crcb_parameter_write(param.parameter_id, &param);
        if (rval)
        {
            I3_LOG(LOG_MASK_ERROR, "Failed to reset parameter '%s', error %d", param_desc[i].name, rval);
            return rval;
        }
    }
    return 0;
}

int app_handle_param_repo_pre_init(void)
{
#ifdef PARAM_REPO_USE_NVM_STORAGE
    // Get stored hash
    size_t object_length;
    uint32_t type;
    int rval = (int)nvm3_getObjectInfo(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, &type, &object_length);
    if (rval || type != NVM3_OBJECTTYPE_DATA)
    {
        // Key doesn't exist
        I3_LOG(LOG_MASK_WARN, "Failed to find param repo hash data", rval);
        nvm_reset_required = true;
    }
    else if (object_length != sizeof(uint32_t))
    {
        // Invalid hash format
        I3_LOG(LOG_MASK_ERROR, "Found param repo hash with incorrect size", rval);
        nvm_reset_required = true;
        int rval = nvm3_deleteObject(nvm3_defaultHandle, PARAM_REPO_HASH_KEY);
        if (rval != 0) I3_LOG(LOG_MASK_ERROR, "Failed to erase invalid param repo hash, error %d", rval);
    }
    else
    {
        uint32_t hash = calculate_nvm_hash();
        uint32_t stored_hash = 0;
        rval = (int)nvm3_readData(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, (uint8_t *)&stored_hash, sizeof(stored_hash));
        if (rval)
        {
            I3_LOG(LOG_MASK_ERROR, "Failed to read param repo hash, error %d", rval);
            nvm_reset_required = true;
        }
        else if (stored_hash != hash)
        {
            I3_LOG(LOG_MASK_WARN, "Stored param repo hash 0x%x does not match calculated hash 0x%x", stored_hash, hash);
            nvm_reset_required = true;
        }
    }
#endif // PARAM_REPO_USE_NVM_STORAGE
    return 0;
}

int app_handle_param_repo_init(cr_ParameterValue *data, const cr_ParameterInfo *desc)
{
    int rval = 0;
#ifdef PARAM_REPO_USE_NVM_STORAGE
    if (desc->storage_location == cr_StorageLocation_NONVOLATILE && !nvm_failed)
    {
        if (!nvm_reset_required)
        {
            cr_ParameterValue temp;
            size_t object_length;
            uint32_t type;
            int rval = (int)nvm3_getObjectInfo(nvm3_defaultHandle, data->parameter_id, &type, &object_length);
            if (rval || type != NVM3_OBJECTTYPE_DATA || object_length != sizeof(cr_ParameterValue))
            {
                // Key doesn't exist or is the incorrect size, don't trust any keys after this
                I3_LOG(LOG_MASK_ERROR, "NVM parameter data discovery failed for ID %u.  rval: %d  length: %u", data->parameter_id, rval, object_length);
                nvm_reset_required = true;
            }
            else
            {
                rval = (int)nvm3_readData(nvm3_defaultHandle, data->parameter_id, (uint8_t *)&temp, sizeof(temp));
                if (rval || temp.parameter_id != data->parameter_id)
                {
                    I3_LOG(LOG_MASK_ERROR, "Failed to get existing parameter data for %u, error %d.", data->parameter_id, rval);
                    nvm_reset_required = true;
                }
                else
                {
                    // Recovered data is good
                    *data = temp;
                }
            }
        }
        if (nvm_reset_required)
        {
            I3_LOG(LOG_MASK_WARN, "Writing default data to parameter %u", data->parameter_id);
            rval = (int)nvm3_writeData(nvm3_defaultHandle, data->parameter_id, (uint8_t *)data, sizeof(*data));
            if (rval)
            {
                I3_LOG(LOG_MASK_ERROR, "Failed to rewrite default value for parameter %u, error %d.  NVM marked as unusable.", rval);
                nvm_failed = true;
            }
        }
    }
#endif // PARAM_REPO_USE_NVM_STORAGE

    switch (data->parameter_id)
    {
    case PARAM_IDENTIFY_INTERVAL:
        rval = app_handle_param_repo_read(data);
        app_set_identify_interval(data->value.float32_value);
        break;
    case PARAM_USER_DEVICE_NAME:
        // Advertise the user device name if it's been set
        if (sCr_param_val[PARAM_USER_DEVICE_NAME].value.string_value[0] != 0)
        {
            rsl_set_advertised_name(sCr_param_val[PARAM_USER_DEVICE_NAME].value.string_value);
        }
        break;
    default:
        // Call the standard read function
        rval = app_handle_param_repo_read(data);
        break;
    }
    return rval;
}

int app_handle_param_repo_post_init(void)
{
#ifdef PARAM_REPO_USE_NVM_STORAGE
    if (nvm_reset_required)
    {
        uint32_t hash = calculate_nvm_hash();
        int rval = (int)nvm3_writeData(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, (uint8_t *)&hash, sizeof(uint32_t));
        if (rval)
        {
            I3_LOG(LOG_MASK_ERROR, "Failed to rewrite param repo hash, error 0x%x.  NVM marked as unusable.", rval);
            nvm_failed = true;
        }
    }
#endif // PARAM_REPO_USE_NVM_STORAGE
    return 0;
}

// so that the status command can report how many reads have happened.
static uint32_t sNumParameterReads = 0;
void app_get_num_reads(uint32_t *numReads)
{
    *numReads = sNumParameterReads;
    sNumParameterReads = 0;
}

int app_handle_param_repo_read(cr_ParameterValue *data)
{
    int rval = 0;

    affirm(data);
    // we don't return permission denied because we don't want
    // to reveal features that are not permitted.
    if (!crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, data->parameter_id)) return cr_ErrorCodes_INVALID_ID;

    if (0 == (param_desc[data->parameter_id].access & cr_AccessLevel_READ))
    {
        I3_LOG(LOG_MASK_ERROR, "parameter read from %d not allowed, write only.", data->parameter_id);
        return cr_ErrorCodes_PERMISSION_DENIED;
    }

    sNumParameterReads++;

    switch (data->parameter_id)
    {
        // Parameters which may change without the param repo's knowledge
    case PARAM_BT_DEVICE_ADDRESS:
        bd_addr address;
        uint8_t address_type;
        sl_bt_system_get_identity_address(&address, &address_type);
        // Reverse byte order so that it displays nicely through Reach
        for (int i = 0; i < (int)sizeof(address.addr); i++) data->value.bytes_value.bytes[i] = address.addr[sizeof(address) - i - 1];
        data->value.bytes_value.size = sizeof(address.addr);
        break;
    case PARAM_UPTIME:
        data->value.int64_value = rsl_get_system_uptime();
        break;
    case PARAM_RELATIVE_HUMIDITY:
        {
            uint32_t rh;
            int32_t t;
            sl_sensor_rht_get(&rh, &t);
            data->value.float32_value = ((float)rh) / 1000;
            break;
        }
    case PARAM_TEMPERATURE:
        {
            uint32_t rh;
            int32_t t;
            sl_sensor_rht_get(&rh, &t);
            data->value.float32_value = ((float)t) / 1000;
            break;
        }
    case PARAM_LIGHT_LEVEL:
    case PARAM_UV_INDEX:
        {
            sl_sensor_light_get(&sCr_param_val[PARAM_LIGHT_LEVEL].value.float32_value, &sCr_param_val[PARAM_UV_INDEX].value.float32_value);
//          data->value.float32_value = ((float) t) / 1000;
            break;
        }
    case PARAM_MAGNETIC_FIELD_STRENGTH:
        {
            bool junk1, junk2;
            sl_sensor_hall_get(&data->value.float32_value, &junk1, &junk2);
            break;
        }
    case PARAM_ACCELERATION_X_AXIS:
    case PARAM_ACCELERATION_Y_AXIS:
    case PARAM_ACCELERATION_Z_AXIS:
        {
            int16_t temp[3];
            sl_imu_update();
            sl_imu_get_acceleration(temp);
            sCr_param_val[PARAM_ACCELERATION_X_AXIS].value.float32_value = 9.81 * (float)temp[0] / 1000;
            sCr_param_val[PARAM_ACCELERATION_Y_AXIS].value.float32_value = 9.81 * (float)temp[1] / 1000;
            sCr_param_val[PARAM_ACCELERATION_Z_AXIS].value.float32_value = 9.81 * (float)temp[2] / 1000;
            break;
        }
    case PARAM_BUTTON_PRESSED:
        data->value.bool_value = app_get_button_pressed();
        break;
    case PARAM_RGB_LED_STATE:
        data->value.bool_value = app_get_identify_led_on();
        break;
    case PARAM_IDENTIFY:
        data->value.bool_value = app_identify_enabled();
        break;
    default:
        // Do nothing with the data, and assume that it is valid
        break;
    }
    return rval;
}

int app_handle_param_repo_write(cr_ParameterValue *data)
{
    int rval = 0;
    // If needed, check if data is valid before allowing the write to occur
    // This is only necessary if there are limits on the parameter outside of min/max values (for example, needing to be a multiple of 5)
    // switch (data->parameter_id)
    // {
    //   default:
    //     break;
    // }

    // we don't return permission denied because we don't want
    // to reveal features that are not permitted.
    if (!crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, data->parameter_id)) return cr_ErrorCodes_INVALID_ID;

    if (0 == (param_desc[data->parameter_id].access & cr_AccessLevel_WRITE))
    {
        I3_LOG(LOG_MASK_ERROR, "parameter write to %d not allowed, read only.", data->parameter_id);
        return cr_ErrorCodes_PERMISSION_DENIED;
    }

#ifdef PARAM_REPO_USE_NVM_STORAGE
    if (!nvm_failed)
    {
        rval = (int)nvm3_writeData(nvm3_defaultHandle, data->parameter_id, (uint8_t *)data, sizeof(*data));
        if (rval)
        {
            I3_LOG(LOG_MASK_ERROR, "Failed to write new value for parameter %u, error %d.  NVM marked as unusable.", rval);
            nvm_failed = true;
        }
    }
#endif // PARAM_REPO_USE_NVM_STORAGE

    switch (data->parameter_id)
    {
    case PARAM_USER_DEVICE_NAME:
        if (data->value.string_value[0] == 0) rsl_set_advertised_name("Thunderboard Demo");
        else rsl_set_advertised_name(data->value.string_value);
        break;
    case PARAM_IDENTIFY:
        app_enable_identify(data->value.bool_value);
        break;
    case PARAM_IDENTIFY_INTERVAL:
        app_set_identify_interval(data->value.float32_value);
        break;
    case PARAM_COMMAND_LINE_COLOR:
        // RGB state and color mirror each other
        sCr_param_val[PARAM_COMMAND_LINE_COLOR].value.enum_value = data->value.bitfield_value;
        break;
    case PARAM_RGB_LED_STATE:
        // RGB state and color mirror each other
        sCr_param_val[PARAM_COMMAND_LINE_COLOR].value.bitfield_value = data->value.enum_value;
        break;
    default:
        // Do nothing with the data, and assume that it is valid
        break;
    }
    return rval;
}

#ifdef PARAM_REPO_USE_NVM_STORAGE
static uint32_t calculate_nvm_hash(void)
{
    uint32_t hash = 0;
    bool first_param_found = false;
    for (int i = 0; i < NUM_PARAMS; i++)
    {
        if (param_desc[i].storage_location != cr_StorageLocation_NONVOLATILE) continue;
        uint32_t *ptr = (uint32_t *)&param_desc[i];
        if (!first_param_found)
        {
            hash = ptr[0];
            first_param_found = true;
        }
        else hash ^= ptr[0];
        for (size_t i = 1; i < (sizeof(cr_ParameterInfo) / sizeof(uint32_t)); i++) hash ^= ptr[i];
    }
    return hash;
}
#endif // PARAM_REPO_USE_NVM_STORAGE


#ifdef NUM_INIT_NOTIFICATIONS
int crcb_parameter_notification_init(const cr_ParameterNotifyConfig **pNoteArray, size_t *pNum)
{
    *pNum = NUM_INIT_NOTIFICATIONS;
    *pNoteArray = sParamNotifyInit;
    return 0;
}

#endif // NUM_INIT_NOTIFICATIONS

// User code end [P7]


