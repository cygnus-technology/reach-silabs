/*
 * Copyright (c) 2023-2024 i3 Product Development
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
 */

/********************************************************************************************
 *    _ ____  ___             _         _     ___              _                        _
 *   (_)__ / | _ \_ _ ___  __| |_  _ __| |_  |   \ _____ _____| |___ _ __ _ __  ___ _ _| |_
 *   | ||_ \ |  _/ '_/ _ \/ _` | || / _|  _| | |) / -_) V / -_) / _ \ '_ \ '  \/ -_) ' \  _|
 *   |_|___/ |_| |_| \___/\__,_|\_,_\__|\__| |___/\___|\_/\___|_\___/ .__/_|_|_\___|_||_\__|
 *                                                                  |_|
 *                           -----------------------------------
 *                          Copyright i3 Product Development 2023
 *
 * \brief "params.c" provides a trivial 'fake' parameter repository.
 *
 * Original Author: Chuck.Peplinski
 *
 ********************************************************************************************/

/**
 * @file      params.c
 * @brief     An example of support for the parameter service in a Cygnus 
 *            Reach enabled device.  This file is part of the application and
 *            NOT part of the core stack.  Different applications can expose
 *            different parameter sets using their own implementation of the
 *            reach callback functions illustrated here. The crcb_ callback
 *            functions are documented in cr_weak.c.
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 * The Cygngus Reach firmware stack is shared under an MIT license.
 */

#include "reach-server.h"  // configures Reach

#ifdef INCLUDE_PARAMETER_SERVICE

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "nvm3_default.h"

#include "cr_stack.h"
#include "i3_log.h"
#include "app_version.h"
#include "reach_silabs.h"

#include "sl_simple_led_instances.h"

#define MSG_BUFFER_SIZE	256

// There are 35 params defined in the .c file.
// One is write only so it is not transmitted.
// Set this to 34 to go over the 32 param request size.
#ifndef SKIP_ENUMS
  #define NUM_PARAMS      35
  #define NUM_EX_PARAMS   6
  // Variable data holding the parameter values.
  // The init function makes it valid.
  extern const cr_ParamExInfoResponse param_ex_desc[NUM_EX_PARAMS];
#else
    #define NUM_PARAMS      33
#endif

#define STACK_VERSION_PARAM_ID  23
#define STACK_VERSION_INDEX     11
#define PROTO_VERSION_PARAM_ID  25
#define PROTO_VERSION_INDEX     12

#define ACCESS_LEVEL_FULL       0x10

// const data describing the parameters, defined below, to be stored in flash.
extern const cr_ParameterInfo  param_desc[NUM_PARAMS];

// Variable data holding the parameter values.
// The init function makes it valid.
static cr_ParameterValue sCr_param_val[NUM_PARAMS];

static int read_param_from_nvm(const uint32_t pid, cr_ParameterValue *param);
static int write_param_to_nvm(const uint32_t pid, const cr_ParameterValue *param);

// This access control function is based on the challenge key.
// See device.c.  You can customize access control.
extern bool device_get_full_access_OK();

int  get_param_index_by_pid(int pid)
{
    for (int i=0; i<NUM_PARAMS; i++)
    {
        if (param_desc[i].id == pid)
            return i; 
    }
    return -1;
}

extern bool device_get_basic_access_OK();
static bool param_access_granted(const uint32_t pid)
{
    // access permissions can be made arbitrarily simple or complicated.
    // What is demonstrated here is a the requirement of a "full" challenge
    // key to access more parameters.
    if (device_get_full_access_OK())
        return true;  // you've got everything.

    int idx = get_param_index_by_pid(pid);
    if (idx < 0)  // parm does not exist.
        return false;

    if (device_get_basic_access_OK())
    {
        // if it's marked for full you can't get it.
        if (param_desc[idx].access & ACCESS_LEVEL_FULL)
            return false;
    }
    return true;
}

void init_param_repo()
{
    int rval = 0;

    // The data in this demo exercises all of the types.
    for (int i=0; i<NUM_PARAMS; i++)
    {
        sCr_param_val[i].parameter_id = param_desc[i].id;

        switch (param_desc[i].data_type)
        {
        case cr_ParameterDataType_UINT32: // pid 1, 23
            sCr_param_val[i].value.uint32_value = 1984;
            // To match the apps and protobufs, must use _value_tags!
            sCr_param_val[i].which_value = cr_ParameterValue_uint32_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.uint32_value = (uint32_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_INT32: // pid 3, 25
            sCr_param_val[i].value.sint32_value = -1999;
            sCr_param_val[i].which_value = cr_ParameterValue_sint32_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.sint32_value = (int32_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_FLOAT32: // pid 5, 27
            sCr_param_val[i].value.float32_value = 0.993;
            sCr_param_val[i].which_value = cr_ParameterValue_float32_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.float32_value = (float)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_UINT64:  // pid 7, 29
            sCr_param_val[i].value.uint64_value = 441;
            sCr_param_val[i].which_value = cr_ParameterValue_uint64_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.uint64_value = (uint64_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_INT64:  // pid 9
            sCr_param_val[i].value.sint64_value = -10853;
            sCr_param_val[i].which_value = cr_ParameterValue_sint64_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.sint64_value = (int64_t)param_desc[i].default_value;
            break;
        case cr_ParameterDataType_FLOAT64:  // pid 11
            sCr_param_val[i].value.float64_value = 0.51111111111;
            sCr_param_val[i].which_value = cr_ParameterValue_float64_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.float64_value = param_desc[i].default_value;
            break;
        case cr_ParameterDataType_BOOL:  // pid 13
            sCr_param_val[i].value.bool_value = true;
            sCr_param_val[i].which_value = cr_ParameterValue_bool_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.bool_value = param_desc[i].default_value;
            break;
        case cr_ParameterDataType_STRING:  // pid 15
            sprintf(sCr_param_val[i].value.string_value, "Flea bag");
            sCr_param_val[i].which_value = cr_ParameterValue_string_value_tag;
            break;
        case cr_ParameterDataType_ENUMERATION:  // 17
            sCr_param_val[i].value.enum_value = 3;
            sCr_param_val[i].which_value = cr_ParameterValue_enum_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.enum_value = param_desc[i].default_value;
            break;
        case cr_ParameterDataType_BIT_FIELD:  // 19
            sCr_param_val[i].value.bitfield_value = 0xDEAD;
            sCr_param_val[i].which_value = cr_ParameterValue_bitfield_value_tag;
            if (param_desc[i].has_default_value) 
                sCr_param_val[i].value.bitfield_value = param_desc[i].default_value;
            break;
        case cr_ParameterDataType_BYTE_ARRAY:  // 21
            sprintf((char*)sCr_param_val[i].value.bytes_value.bytes, "a byte array");
            sCr_param_val[i].value.bytes_value.size  = 13;
            sCr_param_val[i].which_value = cr_ParameterValue_bytes_value_tag;
            break;
        default:
            affirm(0);  // should not happen.
            break;
        }  // end switch

        // read any stored values from NVM
        switch (param_desc[i].storage_location) {
        default:
        case cr_StorageLocation_STORAGE_LOCATION_INVALID:
            i3_log(LOG_MASK_ERROR, "At param index %d, invalid storage location %d.",
                   i, param_desc[i].storage_location);
            break;
        case cr_StorageLocation_RAM:
        case cr_StorageLocation_RAM_EXTENDED:
            break;  // no need to read
        case cr_StorageLocation_NONVOLATILE_EXTENDED:
            // cr_StorageLocation_NONVOLATILE_EXTENDED is intended to 
            // support a system with more than one NVM region. 
            i3_log(LOG_MASK_ERROR, "At param index %d, NVM-EX not supported.", i);
            break;
        case cr_StorageLocation_NONVOLATILE:
            rval = read_param_from_nvm(param_desc[i].id, &sCr_param_val[i]);
            if (rval != 0) {
                // first time initialize.
                write_param_to_nvm(param_desc[i].id, &sCr_param_val[i]);
                i3_log(LOG_MASK_ALWAYS, "Initialized pid %d in NVM.", param_desc[i].id);
            }
            break;
        }
    } // end for

    // the LED is an example of a parameter that connects to HW.
    if (sCr_param_val[6].value.bool_value) 
        sl_led_turn_on(SL_SIMPLE_LED_INSTANCE(0));
    else
        sl_led_turn_off(SL_SIMPLE_LED_INSTANCE(0));

    // copy the stack version into the parameter data.
    const char *pStackVer = cr_get_reach_version();
    char *pVariableStackVer = sCr_param_val[STACK_VERSION_INDEX].value.string_value;
    sprintf(pVariableStackVer, pStackVer, strlen(pStackVer));

    sCr_param_val[PROTO_VERSION_INDEX].which_value = cr_ParameterValue_uint32_value_tag;
    sCr_param_val[PROTO_VERSION_INDEX].value.uint32_value = cr_ReachProtoVersion_CURRENT_VERSION;
}

// Populate a parameter value structure
int crcb_parameter_read(const uint32_t pid, cr_ParameterValue *data)
{
    affirm(data != NULL);
    if (!param_access_granted(pid))
    {
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    for (int i=0; i<NUM_PARAMS; i++) {
        if (sCr_param_val[i].parameter_id == pid) {
            *data = sCr_param_val[i];
            // to do: write timestamp to be used in notification.
            return 0;
        }
    }
    LOG_ERROR("Parameter %d not found.", pid);
    return cr_ErrorCodes_INVALID_PARAMETER;
}

int crcb_parameter_write(const uint32_t pid, const cr_ParameterValue *data)
{
    int rval = 0;
    int pid_index;

    if (!param_access_granted(pid))
    {
        // this is silent by intent
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    for (int i=0; i<NUM_PARAMS; i++) {
        if (sCr_param_val[i].parameter_id == pid) 
        {
            pid_index = i;
            I3_LOG(LOG_MASK_PARAMS, "Write param[%d], pid %d (%d)", 
                   i, pid, data->parameter_id);
            I3_LOG(LOG_MASK_PARAMS, "  timestamp %d", data->timestamp);
            I3_LOG(LOG_MASK_PARAMS, "  which %d", data->which_value);
            sCr_param_val[i].timestamp = data->timestamp;
            sCr_param_val[i].which_value = data->which_value;

            switch (data->which_value)
            {
            // To match the apps and protobufs, must use _value_tags!
            case cr_ParameterValue_uint32_value_tag:
                sCr_param_val[i].value.uint32_value = data->value.uint32_value;
                break;
            case cr_ParameterValue_sint32_value_tag:
                sCr_param_val[i].value.sint32_value = data->value.sint32_value;
                break;
            case cr_ParameterValue_float32_value_tag:
                sCr_param_val[i].value.float32_value = data->value.float32_value;
                break;
            case cr_ParameterValue_uint64_value_tag:
                sCr_param_val[i].value.uint64_value = data->value.uint64_value;
                break;
            case cr_ParameterValue_sint64_value_tag:
                sCr_param_val[i].value.sint64_value = data->value.sint64_value;
                break;
            case cr_ParameterValue_float64_value_tag:
                sCr_param_val[i].value.float64_value = data->value.float64_value;
                break;
            case cr_ParameterValue_bool_value_tag:
                sCr_param_val[i].value.bool_value = data->value.bool_value;
                break;
            case cr_ParameterValue_string_value_tag:
                memcpy(sCr_param_val[i].value.string_value,
                       data->value.string_value, REACH_PVAL_STRING_LEN);
                sCr_param_val[i].value.string_value[REACH_PVAL_STRING_LEN-1] = 0;
                I3_LOG(LOG_MASK_PARAMS, "String value: %s",
                       sCr_param_val[i].value.string_value);
                break;
            case cr_ParameterValue_bitfield_value_tag:
                sCr_param_val[i].value.bitfield_value = data->value.bitfield_value;
                break;
            case cr_ParameterValue_enum_value_tag:
                sCr_param_val[i].value.enum_value = data->value.enum_value;
                break;
            case cr_ParameterValue_bytes_value_tag:
                memcpy(sCr_param_val[i].value.bytes_value.bytes, 
                       data->value.bytes_value.bytes, 
                       REACH_PVAL_BYTES_LEN);
                if (data->value.bytes_value.size > REACH_PVAL_BYTES_LEN)
                {
                    LOG_ERROR("Parameter write of bytes has invalide size %d > %d", 
                              data->value.bytes_value.size, REACH_PVAL_BYTES_LEN);
                    sCr_param_val[i].value.bytes_value.size = REACH_PVAL_BYTES_LEN;
                }
                else
                {
                    sCr_param_val[i].value.bytes_value.size = data->value.bytes_value.size;
                }
                LOG_DUMP_MASK(LOG_MASK_PARAMS, "bytes value",
                              sCr_param_val[i].value.bytes_value.bytes,
                              sCr_param_val[i].value.bytes_value.size);
                break;
            default:
                LOG_ERROR("Parameter write which_value %d not recognized.", 
                              data->which_value);
                rval = 1;
                break;
            }  // end switch

            // act on specific writes
            if (pid == 13) {
                // bool controls LED.
                if (sCr_param_val[pid_index].value.bool_value)
                    sl_led_turn_on(SL_SIMPLE_LED_INSTANCE(0));
                else
                    sl_led_turn_off(SL_SIMPLE_LED_INSTANCE(0));
            }

            if (rval == 0) {

                // Store to NVM if appropriate
                switch (param_desc[i].storage_location) {
                default:
                case cr_StorageLocation_STORAGE_LOCATION_INVALID:
                    i3_log(LOG_MASK_ERROR, "%s: At param index %d, invalid storage location %d.",
                           __FUNCTION__, i, param_desc[i].storage_location);
                    break;
                case cr_StorageLocation_RAM:
                case cr_StorageLocation_RAM_EXTENDED:
                    break;  // no need to read
                case cr_StorageLocation_NONVOLATILE_EXTENDED:
                    // cr_StorageLocation_NONVOLATILE_EXTENDED is intended to 
                    // support a system with more than one NVM region. 
                    i3_log(LOG_MASK_ERROR, "%s: At param index %d, NVM-EX not supported.", __FUNCTION__, i);
                    break;
                case cr_StorageLocation_NONVOLATILE:
                    write_param_to_nvm(param_desc[i].id, &sCr_param_val[i]);
                    break;
                }
            }
            return 0;
        } // end if PID matches.
    }
    // exited the for loop without finding a match.
    I3_LOG(LOG_MASK_ERROR, "Parameter %d not found.", pid);
    return cr_ErrorCodes_INVALID_PARAMETER;
}

// return a number that changes if the parameter descriptions have changed.
// The client can cache the parameter descriptions based on this hash.
uint32_t crcb_compute_parameter_hash(void)
{
    // Note that the layout of the structure param_desc differs by compiler.
    // The hash computed on the client won't necessarily match that computed on the server.
    uint32_t *ptr = (uint32_t*)param_desc;
    size_t sz = sizeof(param_desc)/(sizeof(uint32_t));
    // LOG_DUMP_MASK(LOG_MASK_PARAMS, "Raw Params", cptr, sizeof(param_desc));

    uint32_t hash = ptr[0];
    for (size_t i= 1; i<sz; i++)
        hash ^= ptr[i];

  #ifndef SKIP_ENUMS
    ptr = (uint32_t*)param_ex_desc;
    size_t sz1 = sizeof(param_ex_desc)/(sizeof(uint32_t));

    for (size_t i= 0; i<sz1; i++)
        hash ^= ptr[i];

    I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x over %d+%d = %d words.\n",
           __FUNCTION__, hash, sz, sz1, sz+sz1);
  #else
    I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x over %d words.\n",
           __FUNCTION__, hash, sz);
  #endif  // ndef SKIP_ENUMS

    return hash;
}


// overriding the weak implemetation, this reports on our local repo.
// Gets a pointer to this parameter description.
static int parameter_get_description(const uint32_t pid, cr_ParameterInfo *pParam)
{
    affirm(pParam != NULL);

    if (!param_access_granted(pid))
    {
        i3_log(LOG_MASK_PARAMS, "%s(%d) Not granted.", __FUNCTION__, pid);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    for (int i=0; i<NUM_PARAMS; i++) {
        if (param_desc[i].id == pid) {
            memcpy(pParam, &param_desc[i], sizeof(cr_ParameterInfo));
            // and off any app specific access
            pParam->access &= cr_AccessLevel_READ_WRITE;
            return 0;
        }
    }
    return cr_ErrorCodes_INVALID_PARAMETER;
}

static int sCurrentParameter = 0;


// Gets the parameter description for the next parameter.
// Allows the stack to iterate through the parameter list.
// Implies an order in the parameter list that is known by the application,
// but not directly by the stack.  Parameter ID's need not be 
// continuous or in order.
// The caller provides a cr_ParameterInfo containing string pointers that will be overwritten.
// The app owns the string pointers which must not be on the stack.
int crcb_parameter_discover_next(cr_ParameterInfo *pDesc)
{
    int i;
    if (sCurrentParameter >= NUM_PARAMS)
    {
        I3_LOG(LOG_MASK_PARAMS, "%s: sCurrentParameter (%d) >= NUM_PARAMS (%d)", 
               __FUNCTION__, sCurrentParameter, NUM_PARAMS);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    for (i = sCurrentParameter; i < NUM_PARAMS; i++)
    {
        if (!param_access_granted(param_desc[i].id))
        {

            I3_LOG(LOG_MASK_PARAMS, "%s: pid %d, sCurrentParameter (%d) Not granted", 
                   __FUNCTION__, param_desc[i].id, i);
            sCurrentParameter++;
            continue;
        }
        break;
    }
    if (sCurrentParameter >= NUM_PARAMS)
    {
        I3_LOG(LOG_MASK_PARAMS, "%s: sCurrentParameter (%d) >= NUM_PARAMS (%d)", 
               __FUNCTION__, sCurrentParameter, NUM_PARAMS);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    I3_LOG(LOG_MASK_PARAMS, "%s: pid %d, Get description", 
                   __FUNCTION__, param_desc[sCurrentParameter].id);
    int rval = parameter_get_description(param_desc[sCurrentParameter].id, pDesc);
    sCurrentParameter++;
    return rval;
}

int crcb_parameter_get_count()
{
    if (device_get_full_access_OK())
    {
        i3_log(LOG_MASK_PARAMS, "%s: return %d.", __FUNCTION__, NUM_PARAMS);
        return NUM_PARAMS;
    }

    // this is a very simple 2 layer access control
    int i, numPermitted = 0;
    for (i=0; i<NUM_PARAMS; i++)
    {
        if (!(param_desc[i].access & ACCESS_LEVEL_FULL))
            numPermitted++;
    }
    return numPermitted;
}

// Resets the application's pointer into the parameter table such that
// the next call to crcb_parameter_discover_next() will return the
// description of this parameter.
int crcb_parameter_discover_reset(const uint32_t pid)
{
    int i;
    sCurrentParameter = 0;  // in case none match
    for (i = 0; i < NUM_PARAMS; i++)
    {
        if (!param_access_granted(param_desc[i].id))
        {
            i3_log(LOG_MASK_PARAMS, "%s: skip %d.", __FUNCTION__, param_desc[i].id);
            continue;
        }

        if (param_desc[i].id == pid)
        {
            sCurrentParameter = i;
            I3_LOG(LOG_MASK_PARAMS, "dp reset(%d) reset to %d", pid, sCurrentParameter);
            return 0;
        }
    }
    I3_LOG(LOG_MASK_PARAMS, "dp reset(%d) reset defaults to %d", pid, sCurrentParameter);
    return cr_ErrorCodes_INVALID_PARAMETER;
}

#ifndef SKIP_ENUMS
// In parallel to the parameter discovery, use this to find out 
// about enumerations and bitfields
// Stored separately to minimize parameter description size.
static int sCurrentExParam = 0;
static int sRequestedParamPid = -1; // negative means all

int crcb_parameter_ex_get_count(const int32_t pid)
{
    if (pid < 0)  // all 
        return NUM_EX_PARAMS;

    int num_ex_msgs = 0;

    for (int i=0; i<NUM_EX_PARAMS; i++) {
        if ((int32_t)param_ex_desc[i].associated_pid == pid) {
            num_ex_msgs++;
        }
    }
    return num_ex_msgs;
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
    return cr_ErrorCodes_INVALID_PARAMETER;
}
#endif  // ndef SKIP_ENUMS

// Just for testing, param[34] increments.  This is a demo feature.
static uint32_t sLastChanged = 0;
void generate_data_for_notify(uint32_t timestamp)
{
    uint32_t delta = timestamp - sLastChanged;
    if (delta < SYS_TICK_RATE)
        return;   // this parameter changes once per second.
    sCr_param_val[34].value.sint32_value++;
    sCr_param_val[34].timestamp = timestamp;
    sLastChanged = timestamp;

}

static int read_param_from_nvm(const uint32_t pid, cr_ParameterValue *param)
{
    int key = -1;
    size_t dataLen;
    uint32_t objectType;

    for (int i=0; i<NUM_PARAMS; i++) {
        if (sCr_param_val[i].parameter_id == pid) 
        {
            key = pid;
            break;
        }
    }
    if (key <0) {
        i3_log(LOG_MASK_ERROR, "%s: Requested PID %d not found.", __FUNCTION__, pid);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    nvm3_getObjectInfo(nvm3_defaultHandle, key, &objectType, &dataLen);
    if (objectType != NVM3_OBJECTTYPE_DATA) {
        i3_log(LOG_MASK_WARN, "%s: Requested PID %d not in NVM.", 
               __FUNCTION__, pid);
        return cr_ErrorCodes_READ_FAILED;
    }

    Ecode_t eCode = nvm3_readData(nvm3_defaultHandle, key, (uint8_t*)param, dataLen);
    if (ECODE_NVM3_OK != eCode) {
        i3_log(LOG_MASK_ERROR, "%s: NVM Read of PID %d failed with 0x%x.", 
               __FUNCTION__, pid, eCode);
        return cr_ErrorCodes_READ_FAILED;
    }
    return cr_ErrorCodes_NO_ERROR;
}

static int write_param_to_nvm(const uint32_t pid, const cr_ParameterValue *param)
{
    int key = -1;

    for (int i=0; i<NUM_PARAMS; i++) {
        if (sCr_param_val[i].parameter_id == pid) 
        {
            key = i;
            break;
        }
    }
    if (key <0) {
        i3_log(LOG_MASK_ERROR, "%s: PID %d not found.", __FUNCTION__, pid);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }

    Ecode_t eCode = nvm3_writeData(nvm3_defaultHandle, pid,
                                   (uint8_t*)param, sizeof(cr_ParameterValue));
    if (ECODE_NVM3_OK != eCode) {
        i3_log(LOG_MASK_ERROR, "%s: NVM Write of PID %d failed with 0x%x.", 
               __FUNCTION__, pid, eCode);
        return cr_ErrorCodes_READ_FAILED;
    }

    // Do repacking if needed
    if (nvm3_repackNeeded(nvm3_defaultHandle)) {
        i3_log(LOG_MASK_ALWAYS, "Repacking NVM");
        eCode = nvm3_repack(nvm3_defaultHandle);
        if (eCode != ECODE_NVM3_OK) {
            i3_log(LOG_MASK_ERROR, "%s: Error 0x%x repacking", __FUNCTION__, eCode);
        }
    }
    I3_LOG(LOG_MASK_REACH, "Wrote PID %d (index %d) to NVM", pid, key);
    return cr_ErrorCodes_NO_ERROR;
}

// ***********************************************************************************
// Constant parameter descriptions:
// ***********************************************************************************
// This is effectively a 'fake' parameter repository.
// The init function must be called to connect it to the system.
// This particular set of parameters is chosen to test functionality.

// Notice that parameter ID's are odd numbers.  This was done
// to prove that they can be discontinuous.
// ***********************************************************************************

const cr_ParameterInfo  param_desc[NUM_PARAMS] = {
    // A uint32 type with a description and a limited range.
    { // [0]
        .id =               1,
        .data_type =        cr_ParameterDataType_UINT32,
        .size_in_bytes =     0,
        .name =             "first param (1)",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "This parameter comes first",
        .units =            "unsigned int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        0,
        .range_max =        32767,
        .default_value =    1970,
        .storage_location = cr_StorageLocation_RAM
    },
    // A signed int with a description and a limited range.
    // units test a UTF-8 symbol
    { // [1]
        .id =               3,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "param #two",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "Eleven bits signed",
        .units =            "\xC2\xB0",  // degres in UTF-8
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM_EXTENDED
    },
    // A float with a limited range and a description.
    // Stored in non-volatile
    { // [2]
        .id =               5,
        .data_type =        cr_ParameterDataType_FLOAT32,
        .size_in_bytes =     0,
        .name =             "NV p5 %",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "float32",
        .units =            "%",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        0,
        .range_max =        100,
        .default_value =    66.66666666666667,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
    // A uint64 with a large linmited range.
    // By ifdef can test the "too long string" error.
    { // [3]
        .id =               7,
        .data_type =        cr_ParameterDataType_UINT64,
        .size_in_bytes =     0,
        .name =             "0 to 68719476736",
        .access =           cr_AccessLevel_READ_WRITE,
       // #define TOO_LONG_STRING
       #ifdef TOO_LONG_STRING
        // exercises an error case that we like to know works!
        .description =      "This parameter doesn't come first",
      #else
        .description =      "Parmenter no come foist!",
      #endif  // def TOO_LONG_STRING
        .units =            "unsigned long",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        0,
        .range_max =        68719476736,
        .default_value =    68719476736,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
    // An int64 with a limited range
    { // [4]
        .id =               9,
        .data_type =        cr_ParameterDataType_INT64,
        .size_in_bytes =     0,
        .name =             "+/- 68719476736",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "large int",
        .units =            "signed long",
        .has_description =  true,
        .has_range_min =    true,  // demo no max/min
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -68719476736,
        .range_max =        68719476735,
        .default_value =    -68719476736,
        .storage_location = cr_StorageLocation_RAM 
    },
    // double with limited range
    { // [5]
        .id =               11,
        .data_type =        cr_ParameterDataType_FLOAT64,
        .size_in_bytes =     0,
        .name =             "double 0-100",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "float64",
        .units =            "accurate",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        0,
        .range_max =        100,
        .default_value =    66.6666666666666666667,
        .storage_location = cr_StorageLocation_RAM 
    },
    // bool controls LED
    { // [6]
        .id =               13,
        .data_type =        cr_ParameterDataType_BOOL,
        .size_in_bytes =     0,
        .name =             "LED switch",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "On or off",
        .units =            "truth",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = true,
        .range_min =        0,
        .range_max =        1,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM 
    },
    // Test editing strings, stored in NVM.
    { // [7]
        .id =               15,
        .data_type =        cr_ParameterDataType_STRING,
        .size_in_bytes =     0,
        .name =             "String in NVM",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "string type",
        .units =            "words",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = false,
        .range_min =        1,
        .range_max =        0,
        .default_value =    0,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
#ifndef SKIP_ENUMS
    // Test enumeration, stored in NVM
    { // [8]
        .id =               17,
        .data_type =        cr_ParameterDataType_ENUMERATION,
        .size_in_bytes =     0,
        .name =             "enum in NVM",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "enum",
        .units =            "nums",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = true,
        .range_min =        1,
        .range_max =        0,
        .default_value =    3,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
    // Test bit field, stored in NVM
    { // [9]
        .id =               19,
        .data_type =        cr_ParameterDataType_BIT_FIELD,
        .size_in_bytes =     0,
        .name =             "bitfield in NVM",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "Turn me on deadman",
        .units =            "bits",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = true,
        .range_min =        1,
        .range_max =        0,
        .default_value =    5,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
#endif  // ndef SKIP_ENUMS

    // Test byte array                      
    { // [10]               
        .id =               21,
        .data_type =        cr_ParameterDataType_BYTE_ARRAY,
        .size_in_bytes =     0,
        .name =             "bytes in NVM",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "array of bytes",
        .units =            "data",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = false,
        .range_min =        1,
        .range_max =        0,
        .default_value =    0,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
    // Show the stack version [11] = [STACK_VERSION_INDEX]
    {
        .id =               STACK_VERSION_PARAM_ID,
        .data_type =        cr_ParameterDataType_STRING,
        .size_in_bytes =     REACH_PVAL_STRING_LEN,
        .name =             "C stack version",
        .access =           cr_AccessLevel_READ,
        .description =      "Updated in code",
        .units =            "version",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        999999,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // Show the proto version [12] = [PROTO_VERSION_INDEX]
        .id =               PROTO_VERSION_PARAM_ID,
        .data_type =        cr_ParameterDataType_UINT32,
        .size_in_bytes =     4,
        .name =             "proto file version",
        .access =           cr_AccessLevel_READ,
        .description =      "version of .proto file",
        .units =            "version",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = false,
        .range_min =        0,
        .range_max =        100,
        .default_value =    66.66666666666667,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
    // filler, NVM
    { // [13]
        .id =               27,
        .data_type =        cr_ParameterDataType_UINT64,
        .size_in_bytes =     0,
        .name =             "write only",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_WRITE,
        .description =      "This parameter is 13th",
        .units =            "37 bits",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        0,
        .range_max =        68719476736,
        .default_value =    68719476736,
        .storage_location = cr_StorageLocation_NONVOLATILE
    },
    { // [14]
        .id =               29,
        .data_type =        cr_ParameterDataType_INT64,
        .size_in_bytes =     0,
        .name =             "param #29",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_READ_WRITE,
        .description =      "38 bits signed",
        .units =            "38 bits signed",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -68719476736,
        .range_max =        68719476735,
        .default_value =    -68719476736,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [15]
        .id =               31,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "param #31",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_READ,
        .description =      "Read only,RAM-EX",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM_EXTENDED
    },
    // specifies max 1023 but no min.  Should be -32 bits
    { // [16]
        .id =               33,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "33 no min",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_READ_WRITE,
        .description =      "no min",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    // specifies min -1024 but no max.  Should be 32 bits
    { // [17]
        .id =               35,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "35 no max",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_READ_WRITE,
        .description =      "No max",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    false,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [18]
        .id =               37,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p37",
        .access =           cr_AccessLevel_READ_WRITE,  // isolated basic among fulls
        .description =      "+/- 1024",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [19]
        .id =               39,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p39 no desc",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  false,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [20]
        .id =               41,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p41",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [21]
        .id =               43,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p43",
        .access =           ACCESS_LEVEL_FULL | cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    // no max no min.  Should be +/- 32 bits.
    { // [22]
        .id =               45,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "no max no min",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "??",
        .units =            "signed int",
        .has_description =  false,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [23]
        .id =               47,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p47 no default",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [24]
        .id =               49,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p49 no default",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM-EX",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = false,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [25]
        .id =               51,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p51",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    51,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [26]
        .id =               53,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p53",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    53,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [27]
        .id =               55,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p55",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    55,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [28]
        .id =               57,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p57",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    57,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [29]
        .id =               59,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p59",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    59,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [30]
        .id =               61,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p61",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "Read write,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    61,
        .storage_location = cr_StorageLocation_RAM
    },
    { // [31]
        .id =               63,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p63",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "Read write,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    63,
        .storage_location = cr_StorageLocation_RAM
    },
    // If there were no write only params this would overflow one read request.
    { // [32]
        .id =               65,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p65",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "Read write,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    65,
        .storage_location = cr_StorageLocation_RAM
    },
    // When a write only param is not displayed this is still in one read request
    { // [33]
        .id =               67,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p67",
        .access =           cr_AccessLevel_READ,
        .description =      "Read only,RAM",
        .units =            "signed int",
        .has_description =  true,
        .has_range_min =    true,
        .has_range_max =    true,
        .has_default_value = true,
        .range_min =        -1024,
        .range_max =        1023,
        .default_value =    67,
        .storage_location = cr_StorageLocation_RAM
    },
    // Even with one write only this overflows one read request.
    { // [34]
        .id =               69,
        .data_type =        cr_ParameterDataType_INT32,
        .size_in_bytes =     0,
        .name =             "p69",
        .access =           cr_AccessLevel_READ_WRITE,
        .description =      "incrementing",
        .units =            "unsigned int",
        .has_description =  true,
        .has_range_min =    false,
        .has_range_max =    false,
        .has_default_value = true,
        .range_min =        0,
        .range_max =        1023,
        .default_value =    1,
        .storage_location = cr_StorageLocation_RAM
    },
};

#ifndef SKIP_ENUMS
const cr_ParamExInfoResponse param_ex_desc[NUM_EX_PARAMS] = {
    {
        13, // associated_pid
        cr_ParameterDataType_ENUMERATION, // data_type
        2,
        {
            {0, "dark"},
            {1, "light"}
        }
    },
    {
        17, // associated_pid
        cr_ParameterDataType_ENUMERATION, // data_type
        8,
        {
            {1, "one"},
            {2, "two"},
            {3, "three"},
            {4, "four"},
            {5, "five"},
            {6, "six"},
            {7, "seven"},
            {8, "eight"},

        }
    },
    {
        17, // associated_pid
        cr_ParameterDataType_ENUMERATION, // data_type
        8,
        {
            {9, "nine"},
            {10, "ten"},
            {11, "eleven"},
            {12, "twelve"},
            {13, "thirteen"},
            {14, "fourteen"},
            {15, "fifteen"},
            {16, "sixteen"},
        }
    },
    {
        17, // associated_pid
        cr_ParameterDataType_ENUMERATION, // data_type
        6,
        {
            {17, "seventeen"},
            {18, "eighteen"},
            {19, "nineteen"},
            {20, "twenty"},
            {21, "twentyone"},
            {22, "twentytwo"}
        }
    },
    {
        19, // associated_pid
        cr_ParameterDataType_BIT_FIELD, // data_type
        8,
        {
            {1, "one"},
            {2, "two"},
            {4, "four"},
            {8, "eight"},
            {16, "sixteen"},
            {32, "thirty two"},
            {64, "sixty four"},
            {128, "onetwentyeight"},

        }
    },
    {
        19, // associated_pid
        cr_ParameterDataType_BIT_FIELD, // data_type
        6,
        {
            {256, "1<<8"},
            {512, "1<<9"},
            {1024, "1<<10"},
            {2048, "1<<11"},
            {4096, "1<12"},
            {8192, "1<13"}
        }
    }
};
#endif  // ndef SKIP_ENUMS


#endif // def INCLUDE_PARAMETER_SERVICE


