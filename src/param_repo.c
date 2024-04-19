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
 * @file      param_repo.c
 * @brief     An example of functions to handle reading and writing parameters with Reach
 * @copyright (c) Copyright 2023-2024 i3 Product Development. All Rights Reserved.
 *
 * Original Author: Joseph Peplinski
 *
 ********************************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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

static int64_t time_offset = 0;

char get_cli_text_color_response[] = TEXT_BLACK;

char * param_repo_get_cli_text_color(void)
{
  memcpy(get_cli_text_color_response, TEXT_BLACK, sizeof(TEXT_BLACK));
  switch (sCr_param_val[PARAM_CLI_TEXT_COLOR].value.enum_value)
  {
    case CLI_TEXT_COLOR_DISABLED:
      memset(get_cli_text_color_response, 0, sizeof(get_cli_text_color_response));
      break;
    default:
      // Change one character to get the color right
      get_cli_text_color_response[3] = '0' + sCr_param_val[PARAM_CLI_TEXT_COLOR].value.enum_value;
      break;
  }
  return get_cli_text_color_response;
}

int param_repo_reset_nvm(void)
{
  for (uint16_t i = 0; i < NUM_PARAMS; i++)
  {
    if (param_desc[i].storage_location != cr_StorageLocation_NONVOLATILE)
      continue;
    cr_ParameterValue param;
    param.parameter_id = sCr_param_val[i].parameter_id;
    param.which_value = sCr_param_val[param.parameter_id].which_value;
    param.timestamp = (uint32_t) rsl_get_system_uptime();
    I3_LOG(LOG_MASK_PARAMS, "Resetting ID %u, type %u", param.parameter_id, param.which_value);
    // Fill in default value if it's defined
    switch (param.which_value)
    {
      case cr_ParameterValue_uint32_value_tag:
                if (param_desc[i].desc.uint32_desc.has_default_value)
                    sCr_param_val[i].value.uint32_value = param_desc[i].desc.uint32_desc.default_value;
        break;
      case cr_ParameterValue_int32_value_tag:
                if (param_desc[i].desc.int32_desc.has_default_value)
                    sCr_param_val[i].value.int32_value = param_desc[i].desc.int32_desc.default_value;
        break;
      case cr_ParameterValue_float32_value_tag:
                if (param_desc[i].desc.float32_desc.has_default_value)
                    sCr_param_val[i].value.float32_value = param_desc[i].desc.float32_desc.default_value;
        break;
      case cr_ParameterValue_uint64_value_tag:
                if (param_desc[i].desc.uint64_desc.has_default_value)
                    sCr_param_val[i].value.uint64_value = param_desc[i].desc.uint64_desc.default_value;
        break;
      case cr_ParameterValue_int64_value_tag:
                if (param_desc[i].desc.int64_desc.has_default_value)
                    sCr_param_val[i].value.int64_value = param_desc[i].desc.int64_desc.default_value;
        break;
      case cr_ParameterValue_float64_value_tag:
                if (param_desc[i].desc.float64_desc.has_default_value)
                    sCr_param_val[i].value.float64_value = param_desc[i].desc.float64_desc.default_value;
        break;
      case cr_ParameterValue_bool_value_tag:
                if (param_desc[i].desc.bool_desc.has_default_value)
                    sCr_param_val[i].value.bool_value = param_desc[i].desc.bool_desc.default_value;
                break;
            case cr_ParameterValue_string_value_tag:
                if (param_desc[i].desc.string_desc.has_default_value)
                {
                    memset(sCr_param_val[i].value.string_value, 0, sizeof(sCr_param_val[i].value.string_value));
                    memcpy(sCr_param_val[i].value.string_value, param_desc[i].desc.string_desc.default_value, sizeof(param_desc[i].desc.string_desc.default_value));
                }
        break;
      case cr_ParameterValue_enum_value_tag:
                if (param_desc[i].desc.enum_desc.has_default_value)
                    sCr_param_val[i].value.enum_value = param_desc[i].desc.enum_desc.default_value;
        break;
      case cr_ParameterValue_bitfield_value_tag:
                if (param_desc[i].desc.bitfield_desc.has_default_value)
                    sCr_param_val[i].value.bitfield_value = param_desc[i].desc.bitfield_desc.default_value;
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
  int rval = (int) nvm3_getObjectInfo(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, &type, &object_length);
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
    if (rval != 0)
        I3_LOG(LOG_MASK_ERROR, "Failed to erase invalid param repo hash, error %d", rval);
  }
  else
  {
    uint32_t hash = calculate_nvm_hash();
    uint32_t stored_hash = 0;
    rval = (int) nvm3_readData(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, (uint8_t *) &stored_hash, sizeof(stored_hash));
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
      int rval = (int) nvm3_getObjectInfo(nvm3_defaultHandle, data->parameter_id, &type, &object_length);
      if (rval || type != NVM3_OBJECTTYPE_DATA || object_length != sizeof(cr_ParameterValue))
      {
        // Key doesn't exist or is the incorrect size, don't trust any keys after this
        I3_LOG(LOG_MASK_ERROR, "NVM parameter data discovery failed for ID %u.  rval: %d  length: %u", data->parameter_id, rval, object_length);
        nvm_reset_required = true;
      }
      else
      {
        rval = (int) nvm3_readData(nvm3_defaultHandle, data->parameter_id, (uint8_t *) &temp, sizeof(temp));
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
      rval = (int) nvm3_writeData(nvm3_defaultHandle, data->parameter_id, (uint8_t *) data, sizeof(*data));
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
    int rval = (int) nvm3_writeData(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, (uint8_t *) &hash, sizeof(uint32_t));
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
  if (!crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, data->parameter_id))
      return cr_ErrorCodes_INVALID_ID;

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
      for (int i = 0; i < (int) sizeof(address.addr); i++)
        data->value.bytes_value.bytes[i] = address.addr[sizeof(address) - i - 1];
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
      data->value.float32_value = ((float) rh) / 1000;
      break;
    }
    case PARAM_TEMPERATURE:
    {
      uint32_t rh;
      int32_t t;
      sl_sensor_rht_get(&rh, &t);
      data->value.float32_value = ((float) t) / 1000;
      break;
    }
    case PARAM_LIGHT_LEVEL:
    case PARAM_UV_INDEX:
    {
      sl_sensor_light_get(&sCr_param_val[PARAM_LIGHT_LEVEL].value.float32_value, &sCr_param_val[PARAM_UV_INDEX].value.float32_value);
//          data->value.float32_value = ((float) t) / 1000;
      break;
    }
    case PARAM_MAGNETIC_FIELD_READING:
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
      sCr_param_val[PARAM_ACCELERATION_X_AXIS].value.float32_value = 9.81 * (float) temp[0] / 1000;
      sCr_param_val[PARAM_ACCELERATION_Y_AXIS].value.float32_value = 9.81 * (float) temp[1] / 1000;
      sCr_param_val[PARAM_ACCELERATION_Z_AXIS].value.float32_value = 9.81 * (float) temp[2] / 1000;
      break;
    }
    case PARAM_BUTTON_PRESSED:
      data->value.bool_value = app_get_button_pressed();
      break;
    case PARAM_LED_ON:
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
  if (!crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, data->parameter_id))
      return cr_ErrorCodes_INVALID_ID;

  if (0 == (param_desc[data->parameter_id].access & cr_AccessLevel_WRITE))
  {
      I3_LOG(LOG_MASK_ERROR, "parameter write to %d not allowed, read only.", data->parameter_id);
      return cr_ErrorCodes_PERMISSION_DENIED;
  }

#ifdef PARAM_REPO_USE_NVM_STORAGE
  if (!nvm_failed)
  {
    rval = (int) nvm3_writeData(nvm3_defaultHandle, data->parameter_id, (uint8_t*) data, sizeof(*data));
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
      if (data->value.string_value[0] == 0)
        rsl_set_advertised_name("Thunderboard Demo");
      else
        rsl_set_advertised_name(data->value.string_value);
      break;
    case PARAM_IDENTIFY:
      app_enable_identify(data->value.bool_value);
      break;
    case PARAM_IDENTIFY_INTERVAL:
      app_set_identify_interval(data->value.float32_value);
      break;
    case PARAM_CLI_TEXT_RGB_STATE:
      // RGB state and color mirror each other
      sCr_param_val[PARAM_CLI_TEXT_COLOR].value.enum_value = data->value.bitfield_value;
      break;
    case PARAM_CLI_TEXT_COLOR:
      // RGB state and color mirror each other
      sCr_param_val[PARAM_CLI_TEXT_RGB_STATE].value.bitfield_value = data->value.enum_value;
      break;
    default:
      // Do nothing with the data, and assume that it is valid
      break;
  }
  return rval;
}

#ifdef INCLUDE_TIME_SERVICE
int crcb_time_get(cr_TimeGetResponse *response)
{
  response->seconds_utc = (rsl_get_system_uptime() + time_offset) / 1000;
  response->has_timezone = sCr_param_val[PARAM_TIMEZONE_ENABLED].value.bool_value;
  if (!response->has_timezone)
  {
    response->seconds_utc += sCr_param_val[PARAM_TIMEZONE_OFFSET].value.int32_value;
  }
  else
  {
    response->timezone = sCr_param_val[PARAM_TIMEZONE_OFFSET].value.int32_value;
  }
  return 0;
}

int crcb_time_set(const cr_TimeSetRequest *request)
{
  time_offset = (request->seconds_utc * 1000) - rsl_get_system_uptime();
  if (request->has_timezone)
  {
    cr_ParameterValue param;
    param.parameter_id = PARAM_TIMEZONE_OFFSET;
    param.which_value = cr_ParameterValue_int32_value_tag;
    param.timestamp = (uint32_t) rsl_get_system_uptime();
    param.value.int32_value = request->timezone;
    crcb_parameter_write(PARAM_TIMEZONE_OFFSET, &param);
  }
  return 0;
}
#endif

#ifdef PARAM_REPO_USE_NVM_STORAGE
static uint32_t calculate_nvm_hash(void)
{
  uint32_t hash = 0;
  bool first_param_found = false;
  for (int i = 0; i < NUM_PARAMS; i++)
  {
    if (param_desc[i].storage_location != cr_StorageLocation_NONVOLATILE)
      continue;
    uint32_t *ptr = (uint32_t*) &param_desc[i];
    if (!first_param_found)
    {
      hash = ptr[0];
      first_param_found = true;
    }
    else
      hash ^= ptr[0];
    for (size_t i = 1; i < (sizeof(cr_ParameterInfo) / sizeof(uint32_t)); i++)
      hash ^= ptr[i];
  }
  return hash;
}
#endif // PARAM_REPO_USE_NVM_STORAGE

// Notice that turning on all of these notifications causes us to constantly read all of 
// the sensors which does slow things down.
#define NUM_INIT_NOTIFICATIONS  10
static const cr_ParameterNotifyConfig sParamNotifyInit[NUM_INIT_NOTIFICATIONS] =
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

#if NUM_SUPPORTED_PARAM_NOTIFY != 0

int crcb_parameter_notification_init(const cr_ParameterNotifyConfig **pNoteArray, size_t *pNum)
{
    *pNum = NUM_INIT_NOTIFICATIONS;
    *pNoteArray = sParamNotifyInit;
    return 0;
}

#endif // NUM_SUPPORTED_PARAM_NOTIFY != 0

