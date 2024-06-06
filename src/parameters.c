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

/********************************************************************************************
 ************************************     Includes     *************************************
 *******************************************************************************************/

#include "parameters.h"
#include <stddef.h>
#include "cr_stack.h"
#include "i3_error.h"
#include "i3_log.h"

/* User code start [parameters.c: User Includes] */

#include "sl_bluetooth.h"
#include "sl_sensor_hall.h"
#include "sl_sensor_light.h"
#include "sl_sensor_rht.h"
#include "sl_imu.h"
#include "app.h"
#include "reach_silabs.h"
#include "nvm3_generic.h"

/* User code end [parameters.c: User Includes] */

/********************************************************************************************
 *************************************     Defines     **************************************
 *******************************************************************************************/

#define PARAM_EI_TO_NUM_PEI_RESPONSES(param_ex) ((param_ex.num_labels / 8) + ((param_ex.num_labels % 8) ? 1:0))

/* User code start [parameters.c: User Defines] */

#define PARAM_REPO_HASH_KEY 0xFFFFF

/* User code end [parameters.c: User Defines] */

/********************************************************************************************
 ***********************************     Data Types     ************************************
 *******************************************************************************************/

typedef struct {
  uint32_t pei_id;
  uint8_t data_type;
  uint8_t num_labels;
  const cr_ParamExKey *labels;
} cr_gen_param_ex_t;

/* User code start [parameters.c: User Data Types] */
/* User code end [parameters.c: User Data Types] */

/********************************************************************************************
 ********************************     Global Variables     *********************************
 *******************************************************************************************/

/* User code start [parameters.c: User Global Variables] */
/* User code end [parameters.c: User Global Variables] */

/********************************************************************************************
 *****************************     Local/Extern Variables     ******************************
 *******************************************************************************************/

static int sCurrentParameter = 0;
static cr_ParameterValue sCr_param_val[NUM_PARAMS];
static const cr_ParameterInfo param_desc[] = {
  {
    .id = PARAM_USER_DEVICE_NAME,
    .name = "User Device Name",
    .has_description = true,
    .description = "The advertised BLE name",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_NONVOLATILE,
    .which_desc = cr_ParameterDataType_STRING + cr_ParameterInfo_uint32_desc_tag,
    .desc.string_desc.max_size = 29
  },
  {
    .id = PARAM_UPTIME,
    .name = "Uptime",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_INT64 + cr_ParameterInfo_uint32_desc_tag,
    .desc.int64_desc.has_units = true,
    .desc.int64_desc.units = "milliseconds"
  },
  {
    .id = PARAM_BUTTON_PRESSED,
    .name = "Button Pressed",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
    .desc.bool_desc.has_pei_id = true,
    .desc.bool_desc.pei_id = PARAM_EI_IDENTIFY_SWITCH
  },
  {
    .id = PARAM_IDENTIFY_LED,
    .name = "Identify LED",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
    .desc.bool_desc.has_pei_id = true,
    .desc.bool_desc.pei_id = PARAM_EI_IDENTIFY_LED
  },
  {
    .id = PARAM_COLOR_DEMO_RGB_STATE,
    .name = "Color Demo RGB State",
    .has_description = true,
    .description = "RGB representation of colors",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_BIT_FIELD + cr_ParameterInfo_uint32_desc_tag,
    .desc.bitfield_desc.bits_available = 3,
    .desc.bitfield_desc.has_pei_id = true,
    .desc.bitfield_desc.pei_id = PARAM_EI_RGB_STATE
  },
  {
    .id = PARAM_COLOR_DEMO_ENUMERATION,
    .name = "Color Demo Enumeration",
    .has_description = true,
    .description = "Human-readable RGB translation",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_ENUMERATION + cr_ParameterInfo_uint32_desc_tag,
    .desc.enum_desc.has_range_min = true,
    .desc.enum_desc.range_min = 0,
    .desc.enum_desc.has_range_max = true,
    .desc.enum_desc.range_max = 7,
    .desc.enum_desc.has_pei_id = true,
    .desc.enum_desc.pei_id = PARAM_EI_RGB_STATE_TRANSLATION
  },
  {
    .id = PARAM_IDENTIFY,
    .name = "Identify",
    .has_description = true,
    .description = "Turn on to blink the yellow LED",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
    .desc.bool_desc.has_default_value = true,
    .desc.bool_desc.default_value = false
  },
  {
    .id = PARAM_IDENTIFY_INTERVAL,
    .name = "Identify Interval",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_NONVOLATILE,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = 0.01,
    .desc.float32_desc.has_default_value = true,
    .desc.float32_desc.default_value = 1,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 60
  },
  {
    .id = PARAM_RELATIVE_HUMIDITY,
    .name = "Relative Humidity",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "%",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = 0.01,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 100,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 1
  },
  {
    .id = PARAM_TEMPERATURE,
    .name = "Temperature",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "\xC2\xB0 C",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = -57,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 99,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 1
  },
  {
    .id = PARAM_LIGHT_LEVEL,
    .name = "Light Level",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "lux",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = 0,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 1000,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 1
  },
  {
    .id = PARAM_UV_INDEX,
    .name = "UV Index",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "W/sq meter",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = 0,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 100,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 1
  },
  {
    .id = PARAM_MAGNETIC_FIELD_STRENGTH,
    .name = "Magnetic Field Strength",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "millitesla",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = 0,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 5000,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 1
  },
  {
    .id = PARAM_ACCELERATION_X_AXIS,
    .name = "Acceleration (X axis)",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "m/s",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = -50,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 50,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 2
  },
  {
    .id = PARAM_ACCELERATION_Y_AXIS,
    .name = "Acceleration (Y axis)",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "m/s",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = -50,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 50,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 2
  },
  {
    .id = PARAM_ACCELERATION_Z_AXIS,
    .name = "Acceleration (Z axis)",
    .has_description = true,
    .description = "Read from Thunderboard Sensor",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_FLOAT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.float32_desc.has_units = true,
    .desc.float32_desc.units = "m/s",
    .desc.float32_desc.has_range_min = true,
    .desc.float32_desc.range_min = -50,
    .desc.float32_desc.has_range_max = true,
    .desc.float32_desc.range_max = 50,
    .desc.float32_desc.has_precision = true,
    .desc.float32_desc.precision = 2
  },
  {
    .id = PARAM_TIMEZONE_ENABLED,
    .name = "Timezone Enabled",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_NONVOLATILE,
    .which_desc = cr_ParameterDataType_BOOL + cr_ParameterInfo_uint32_desc_tag,
    .desc.bool_desc.has_default_value = true,
    .desc.bool_desc.default_value = true
  },
  {
    .id = PARAM_TIMEZONE_OFFSET,
    .name = "Timezone Offset",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_NONVOLATILE,
    .which_desc = cr_ParameterDataType_INT32 + cr_ParameterInfo_uint32_desc_tag,
    .desc.int32_desc.has_units = true,
    .desc.int32_desc.units = "seconds",
    .desc.int32_desc.has_range_min = true,
    .desc.int32_desc.range_min = -43200,
    .desc.int32_desc.has_default_value = true,
    .desc.int32_desc.default_value = 0,
    .desc.int32_desc.has_range_max = true,
    .desc.int32_desc.range_max = 43200
  },
  {
    .id = PARAM_BT_DEVICE_ADDRESS,
    .name = "BT Device Address",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_RAM,
    .which_desc = cr_ParameterDataType_BYTE_ARRAY + cr_ParameterInfo_uint32_desc_tag,
    .desc.bytearray_desc.max_size = 6
  }
};

static cr_ParameterNotifyConfig sParamNotifyInit[] = {
  {
    .parameter_id = PARAM_IDENTIFY_LED,
    .minimum_notification_period = 302,
    .minimum_delta = 1
  },
  {
    .parameter_id = PARAM_IDENTIFY,
    .minimum_notification_period = 501,
    .minimum_delta = 1
  },
  {
    .parameter_id = PARAM_RELATIVE_HUMIDITY,
    .minimum_notification_period = 2010,
    .maximum_notification_period = 60000,
    .minimum_delta = 1
  },
  {
    .parameter_id = PARAM_TEMPERATURE,
    .minimum_notification_period = 2020,
    .maximum_notification_period = 60000,
    .minimum_delta = 0.2
  },
  {
    .parameter_id = PARAM_LIGHT_LEVEL,
    .minimum_notification_period = 1020,
    .maximum_notification_period = 60000,
    .minimum_delta = 20
  },
  {
    .parameter_id = PARAM_UV_INDEX,
    .minimum_notification_period = 3031,
    .maximum_notification_period = 60000,
    .minimum_delta = 1
  },
  {
    .parameter_id = PARAM_MAGNETIC_FIELD_STRENGTH,
    .minimum_notification_period = 3019,
    .maximum_notification_period = 60000,
    .minimum_delta = 0.2
  },
  {
    .parameter_id = PARAM_ACCELERATION_X_AXIS,
    .minimum_notification_period = 2037,
    .minimum_delta = 0.2
  },
  {
    .parameter_id = PARAM_ACCELERATION_Y_AXIS,
    .minimum_notification_period = 2047,
    .minimum_delta = 0.2
  },
  {
    .parameter_id = PARAM_ACCELERATION_Z_AXIS,
    .minimum_notification_period = 2057,
    .minimum_delta = 0.2
  }
};

static int requested_pei_id = -1;
static int current_pei_index = 0;
static int current_pei_key_index = 0;
static const cr_ParamExKey __cr_gen_pei_identify_switch_labels[] = {
  {
    .id = 0,
    .name = "Not Identifying"
  },
  {
    .id = 1,
    .name = "Identifying"
  }
};

static const cr_ParamExKey __cr_gen_pei_identify_led_labels[] = {
  {
    .id = 0,
    .name = "Off"
  },
  {
    .id = 1,
    .name = "Illuminated"
  }
};

static const cr_ParamExKey __cr_gen_pei_timezone_labels[] = {
  {
    .id = 0,
    .name = "Non-Timezoned"
  },
  {
    .id = 1,
    .name = "Timezoned"
  }
};

static const cr_ParamExKey __cr_gen_pei_rgb_state_labels[] = {
  {
    .id = 0,
    .name = "Red"
  },
  {
    .id = 1,
    .name = "Green"
  },
  {
    .id = 2,
    .name = "Blue"
  }
};

static const cr_ParamExKey __cr_gen_pei_rgb_state_translation_labels[] = {
  {
    .id = 0,
    .name = "Off"
  },
  {
    .id = 1,
    .name = "Red"
  },
  {
    .id = 2,
    .name = "Green"
  },
  {
    .id = 3,
    .name = "Yellow"
  },
  {
    .id = 4,
    .name = "Blue"
  },
  {
    .id = 5,
    .name = "Magenta"
  },
  {
    .id = 6,
    .name = "Cyan"
  },
  {
    .id = 7,
    .name = "White"
  }
};

static const cr_gen_param_ex_t param_ex_desc[] = {
  {
    .pei_id = PARAM_EI_IDENTIFY_SWITCH,
    .data_type = cr_ParameterDataType_BOOL,
    .num_labels = 2,
    .labels = __cr_gen_pei_identify_switch_labels
  },
  {
    .pei_id = PARAM_EI_IDENTIFY_LED,
    .data_type = cr_ParameterDataType_BOOL,
    .num_labels = 2,
    .labels = __cr_gen_pei_identify_led_labels
  },
  {
    .pei_id = PARAM_EI_TIMEZONE,
    .data_type = cr_ParameterDataType_BOOL,
    .num_labels = 2,
    .labels = __cr_gen_pei_timezone_labels
  },
  {
    .pei_id = PARAM_EI_RGB_STATE,
    .data_type = cr_ParameterDataType_BIT_FIELD,
    .num_labels = 3,
    .labels = __cr_gen_pei_rgb_state_labels
  },
  {
    .pei_id = PARAM_EI_RGB_STATE_TRANSLATION,
    .data_type = cr_ParameterDataType_ENUMERATION,
    .num_labels = 8,
    .labels = __cr_gen_pei_rgb_state_translation_labels
  }
};

/* User code start [parameters.c: User Local/Extern Variables] */

char get_cli_text_color_response[] = TEXT_BLACK;
static bool nvm_reset_required = false;
static bool nvm_failed = false;

/* User code end [parameters.c: User Local/Extern Variables] */

/********************************************************************************************
 ***************************     Local Function Declarations     ****************************
 *******************************************************************************************/

static int sFindIndexFromPid(uint32_t pid, uint32_t *index);
static int sFindIndexFromPeiId(uint32_t pei_id, uint32_t *index);

/* User code start [parameters.c: User Local Function Declarations] */

static uint32_t calculate_nvm_hash(void);
char* param_repo_get_cli_text_color(void);
int param_repo_reset_nvm(void);
int app_handle_param_repo_pre_init(void);
int app_handle_param_repo_init(cr_ParameterValue *data, const cr_ParameterInfo *desc);
int app_handle_param_repo_post_init(void);
int app_handle_param_repo_read(cr_ParameterValue *data);
int app_handle_param_repo_write(cr_ParameterValue *data);

/* User code end [parameters.c: User Local Function Declarations] */

/********************************************************************************************
 ********************************     Global Functions     *********************************
 *******************************************************************************************/

void parameters_init(void)
{
  /* User code start [Parameter Repository: Pre-Init]
   * Here is the place to do any initialization required before individual parameters are initialized */

  int rval = app_handle_param_repo_pre_init();
  if (rval)
  {
    I3_LOG(LOG_MASK_ERROR, "App-specific param repo pre-init failed (error %d), continuing with init", rval);
  }

  /* User code end [Parameter Repository: Pre-Init] */
  memset(sCr_param_val, 0, sizeof(sCr_param_val));
  for (int i = 0; i < NUM_PARAMS; i++)
  {
    sCr_param_val[i].parameter_id = param_desc[i].id;
    // Convert from description type identifier to value type identifier
    sCr_param_val[i].which_value = (param_desc[i].which_desc - cr_ParameterInfo_uint32_desc_tag) + cr_ParameterValue_uint32_value_tag;

    parameters_reset_param(sCr_param_val[i].parameter_id, false, 0);

    /* User code start [Parameter Repository: Parameter Init]
     * Here is the place to do any initialization specific to a certain parameter */

    rval = app_handle_param_repo_init(&sCr_param_val[i], &param_desc[i]);
    if (rval != 0)
    {
      I3_LOG(LOG_MASK_ERROR, "At param index %d, failed to initialize data (error %d)", i, rval);
    }

    /* User code end [Parameter Repository: Parameter Init] */

  } // end for

  /* User code start [Parameter Repository: Post-Init]
   * Here is the place to do any initialization required after parameters have been initialized */

  rval = app_handle_param_repo_post_init();
  if (rval)
  {
    I3_LOG(LOG_MASK_ERROR, "App-specific param repo post-init failed (error %d), continuing with init", rval);
  }

  /* User code end [Parameter Repository: Post-Init] */
}

int parameters_reset_param(param_t pid, bool write, uint32_t write_timestamp)
{
  uint32_t idx;
  int rval = sFindIndexFromPid(pid, &idx);
  if (rval)
    return rval;
  
  cr_ParameterValue param = {
    .parameter_id = sCr_param_val[idx].parameter_id,
    .which_value = sCr_param_val[idx].which_value
  };
  
  switch (param.which_value - cr_ParameterValue_uint32_value_tag)
  {
    case cr_ParameterDataType_UINT32:
      if (param_desc[idx].desc.uint32_desc.has_default_value)
        param.value.uint32_value = param_desc[idx].desc.uint32_desc.default_value;
      break;
    case cr_ParameterDataType_INT32:
      if (param_desc[idx].desc.int32_desc.has_default_value)
        param.value.int32_value = param_desc[idx].desc.int32_desc.default_value;
      break;
    case cr_ParameterDataType_FLOAT32:
      if (param_desc[idx].desc.float32_desc.has_default_value)
        param.value.float32_value = param_desc[idx].desc.float32_desc.default_value;
      break;
    case cr_ParameterDataType_UINT64:
      if (param_desc[idx].desc.uint64_desc.has_default_value)
        param.value.uint64_value = param_desc[idx].desc.uint64_desc.default_value;
      break;
    case cr_ParameterDataType_INT64:
      if (param_desc[idx].desc.int64_desc.has_default_value)
        param.value.int64_value = param_desc[idx].desc.int64_desc.default_value;
      break;
    case cr_ParameterDataType_FLOAT64:
      if (param_desc[idx].desc.float64_desc.has_default_value)
        param.value.float64_value = param_desc[idx].desc.float64_desc.default_value;
      break;
    case cr_ParameterDataType_BOOL:
      if (param_desc[idx].desc.bool_desc.has_default_value)
        param.value.bool_value = param_desc[idx].desc.bool_desc.default_value;
      break;
    case cr_ParameterDataType_STRING:
      if (param_desc[idx].desc.string_desc.has_default_value)
      {
        memcpy(param.value.string_value, param_desc[idx].desc.string_desc.default_value, sizeof(param_desc[idx].desc.string_desc.default_value));
      }
      break;
    case cr_ParameterDataType_ENUMERATION:
      if (param_desc[idx].desc.enum_desc.has_default_value)
        param.value.enum_value = param_desc[idx].desc.enum_desc.default_value;
      break;
    case cr_ParameterDataType_BIT_FIELD:
      if (param_desc[idx].desc.bitfield_desc.has_default_value)
        param.value.bitfield_value = param_desc[idx].desc.bitfield_desc.default_value;
      break;
    case cr_ParameterDataType_BYTE_ARRAY:
      if (param_desc[idx].desc.bytearray_desc.has_default_value)
      {
        param.value.bytes_value.size = param_desc[idx].desc.bytearray_desc.default_value.size;
        memcpy(param.value.bytes_value.bytes, param_desc[idx].desc.bytearray_desc.default_value.bytes, sizeof(param_desc[idx].desc.bytearray_desc.default_value.bytes));
      }
      else
      {
        param.value.bytes_value.size = param_desc[idx].desc.bytearray_desc.max_size;
      }
      break;
    default:
      affirm(0);  // should not happen.
      break;
  }  // end switch
  
  /* User code start [Parameter Repository: Parameter Reset]
   * Here is the place to add any application-specific behavior for handling parameter resets */
  /* User code end [Parameter Repository: Parameter Reset] */
  
  if (write)
  {
    param.timestamp = write_timestamp;
    rval = crcb_parameter_write(param.parameter_id, &param);
  }
  else
  {
    param.timestamp = sCr_param_val[idx].timestamp;
    sCr_param_val[idx] = param;
  }
  return rval;
}

const char *parameters_get_ei_label(int32_t pei_id, uint32_t enum_bit_position)
{
  uint32_t index = 0;
  if (sFindIndexFromPeiId(pei_id, &index) != 0)
    return 0;
  for (int i = 0; i < param_ex_desc[index].num_labels; i++)
  {
    if (enum_bit_position == param_ex_desc[index].labels[i].id)
      return param_ex_desc[index].labels[i].name;
  }
  return 0;
}

/* User code start [parameters.c: User Global Functions] */

char* parameters_get_cli_text_color(void)
{
  memcpy(get_cli_text_color_response, TEXT_BLACK, sizeof(TEXT_BLACK));
  switch (sCr_param_val[PARAM_COLOR_DEMO_ENUMERATION].value.enum_value)
  {
    case RGB_STATE_TRANSLATION_OFF:
      memset(get_cli_text_color_response, 0, sizeof(get_cli_text_color_response));
      break;
    default:
      // Change one character to get the color right
      get_cli_text_color_response[3] = '0' + sCr_param_val[PARAM_COLOR_DEMO_ENUMERATION].value.enum_value;
      break;
  }
  return get_cli_text_color_response;
}

int parameters_reset_nvm(void)
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
          memcpy(sCr_param_val[i].value.bytes_value.bytes, param_desc[i].desc.bytearray_desc.default_value.bytes,
              sizeof(param_desc[i].desc.bytearray_desc.default_value.bytes));
        }
        else
        {
          sCr_param_val[i].value.bytes_value.size = param_desc[i].desc.bytearray_desc.max_size;
          memset(sCr_param_val[i].value.bytes_value.bytes, 0, sCr_param_val[i].value.bytes_value.size);
        }
        break;
      default:
        affirm(0)
        ;  // should not happen.
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

/* User code end [parameters.c: User Global Functions] */

/********************************************************************************************
 *************************     Cygnus Reach Callback Functions     **************************
 *******************************************************************************************/

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

int crcb_parameter_discover_next(cr_ParameterInfo *ppDesc)
{
  if (sCurrentParameter >= NUM_PARAMS)
  {
    I3_LOG(LOG_MASK_PARAMS, "%s: sCurrentParameter (%d) >= NUM_PARAMS (%d)", __FUNCTION__, sCurrentParameter, NUM_PARAMS);
    return cr_ErrorCodes_NO_DATA;
  }
  while (!crcb_access_granted(cr_ServiceIds_PARAMETER_REPO, param_desc[sCurrentParameter].id))
  {
    I3_LOG(LOG_MASK_PARAMS, "%s: sCurrentParameter (%d) skip, access not granted", __FUNCTION__, sCurrentParameter);
    sCurrentParameter++;
    if (sCurrentParameter >= NUM_PARAMS)
    {
      I3_LOG(LOG_MASK_PARAMS, "%s: skipped to sCurrentParameter (%d) >= NUM_PARAMS (%d)", __FUNCTION__, sCurrentParameter, NUM_PARAMS);
      return cr_ErrorCodes_NO_DATA;
    }
  }
  *ppDesc = param_desc[sCurrentParameter];
  sCurrentParameter++;
  return 0;
}

int crcb_parameter_read(const uint32_t pid, cr_ParameterValue *data)
{
  int rval = 0;
  affirm(data != NULL);
  uint32_t idx;
  rval = sFindIndexFromPid(pid, &idx);
  if (0 != rval)
    return rval;

  /* User code start [Parameter Repository: Parameter Read]
   * Here is the place to update the data from an external source, and update the return value if necessary */

  rval = app_handle_param_repo_read(&sCr_param_val[idx]);

  /* User code end [Parameter Repository: Parameter Read] */

  *data = sCr_param_val[idx];
  return rval;
}

int crcb_parameter_write(const uint32_t pid, const cr_ParameterValue *data)
{
  int rval = 0;
  uint32_t idx;
  rval = sFindIndexFromPid(pid, &idx);
  if (0 != rval)
    return rval;
  I3_LOG(LOG_MASK_PARAMS, "Write param, pid %d (%d)", idx, data->parameter_id);
  I3_LOG(LOG_MASK_PARAMS, "  timestamp %d", data->timestamp);
  I3_LOG(LOG_MASK_PARAMS, "  which %d", data->which_value);

  /* User code start [Parameter Repository: Parameter Write]
   * Here is the place to apply this change externally, and return an error if necessary */

  rval = app_handle_param_repo_write((cr_ParameterValue*) data);
  if (rval != 0)
  {
    // Invalid data or NVM storage failed
    return rval;
  }

  /* User code end [Parameter Repository: Parameter Write] */

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
    memcpy(sCr_param_val[idx].value.string_value, data->value.string_value, REACH_PVAL_STRING_LEN);
    sCr_param_val[idx].value.string_value[REACH_PVAL_STRING_LEN - 1] = 0;
    I3_LOG(LOG_MASK_PARAMS, "String value: %s", sCr_param_val[idx].value.string_value);
    break;
  case cr_ParameterDataType_BIT_FIELD:
    sCr_param_val[idx].value.bitfield_value = data->value.bitfield_value;
    break;
  case cr_ParameterDataType_ENUMERATION:
    sCr_param_val[idx].value.enum_value = data->value.enum_value;
    break;
  case cr_ParameterDataType_BYTE_ARRAY:
    memcpy(sCr_param_val[idx].value.bytes_value.bytes, data->value.bytes_value.bytes, REACH_PVAL_BYTES_LEN);
    if (data->value.bytes_value.size > REACH_PVAL_BYTES_LEN)
    {
      LOG_ERROR("Parameter write of bytes has invalid size %d > %d", data->value.bytes_value.size, REACH_PVAL_BYTES_LEN);
      sCr_param_val[idx].value.bytes_value.size = REACH_PVAL_BYTES_LEN;
    }
    else
    {
      sCr_param_val[idx].value.bytes_value.size = data->value.bytes_value.size;
    }
    LOG_DUMP_MASK(LOG_MASK_PARAMS, "bytes value", sCr_param_val[idx].value.bytes_value.bytes, sCr_param_val[idx].value.bytes_value.size);
    break;
  default:
    LOG_ERROR("Parameter write which_value %d not recognized.", data->which_value);
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

  I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x includes EX.\n", __FUNCTION__, hash);
#else
  I3_LOG(LOG_MASK_PARAMS, "%s: hash 0x%x excludes EX.\n", __FUNCTION__, hash);
#endif // NUM_EX_PARAMS

  return hash;
}

int crcb_parameter_notification_init(const cr_ParameterNotifyConfig **pNoteArray, size_t *pNum)
{
  *pNum = NUM_INIT_PARAMETER_NOTIFICATIONS;
  *pNoteArray = sParamNotifyInit;
  return 0;
}

int crcb_parameter_ex_get_count(const int32_t pid)
{
  if (pid < 0)  // all
  {
    int rval = 0;
    for (int i = 0; i < NUM_EX_PARAMS; i++)
      rval += PARAM_EI_TO_NUM_PEI_RESPONSES(param_ex_desc[i]);
    return rval;
  }

  for (int i=0; i<NUM_EX_PARAMS; i++)
  {
    if (param_ex_desc[i].pei_id == (param_ei_t) pid)
      return PARAM_EI_TO_NUM_PEI_RESPONSES(param_ex_desc[i]);
  }
  return 0;
}

int crcb_parameter_ex_discover_reset(const int32_t pid)
{
  requested_pei_id = pid;
  if (pid < 0)
    current_pei_index = 0;
  else
  {
    current_pei_index = -1;
    for (int i=0; i<NUM_EX_PARAMS; i++)
    {
      if (param_ex_desc[i].pei_id == (param_ei_t) pid)
      {
        current_pei_index = i;
        break;
      }
    }
  }
  current_pei_key_index = 0;
  return 0;
}

int crcb_parameter_ex_discover_next(cr_ParamExInfoResponse *pDesc)
{
  affirm(pDesc);

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
        if (current_pei_index >= NUM_EX_PARAMS)
          current_pei_index = -1;
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
}

/* User code start [parameters.c: User Cygnus Reach Callback Functions] */
/* User code end [parameters.c: User Cygnus Reach Callback Functions] */

/********************************************************************************************
 *********************************     Local Functions     **********************************
 *******************************************************************************************/

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
  for (idx=0; idx<NUM_EX_PARAMS; idx++) {
    if (param_ex_desc[idx].pei_id == pei_id) {
      *index = idx;
      return 0;
    }
  }
  return cr_ErrorCodes_INVALID_ID;
}

/* User code start [parameters.c: User Local Functions] */

int app_handle_param_repo_pre_init(void)
{
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
    rval = (int) nvm3_readData(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, (uint8_t*) &stored_hash, sizeof(stored_hash));
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
  return 0;
}

int app_handle_param_repo_init(cr_ParameterValue *data, const cr_ParameterInfo *desc)
{
  int rval = 0;
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
        rval = (int) nvm3_readData(nvm3_defaultHandle, data->parameter_id, (uint8_t*) &temp, sizeof(temp));
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
      rval = (int) nvm3_writeData(nvm3_defaultHandle, data->parameter_id, (uint8_t*) data, sizeof(*data));
      if (rval)
      {
        I3_LOG(LOG_MASK_ERROR, "Failed to rewrite default value for parameter %u, error %d.  NVM marked as unusable.", rval);
        nvm_failed = true;
      }
    }
  }

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
  if (nvm_reset_required)
  {
    uint32_t hash = calculate_nvm_hash();
    int rval = (int) nvm3_writeData(nvm3_defaultHandle, PARAM_REPO_HASH_KEY, (uint8_t*) &hash, sizeof(uint32_t));
    if (rval)
    {
      I3_LOG(LOG_MASK_ERROR, "Failed to rewrite param repo hash, error 0x%x.  NVM marked as unusable.", rval);
      nvm_failed = true;
    }
  }
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
      sCr_param_val[PARAM_ACCELERATION_X_AXIS].value.float32_value = 9.81 * (float) temp[0] / 1000;
      sCr_param_val[PARAM_ACCELERATION_Y_AXIS].value.float32_value = 9.81 * (float) temp[1] / 1000;
      sCr_param_val[PARAM_ACCELERATION_Z_AXIS].value.float32_value = 9.81 * (float) temp[2] / 1000;
      break;
    }
    case PARAM_BUTTON_PRESSED:
      data->value.bool_value = app_get_button_pressed();
      break;
    case PARAM_IDENTIFY_LED:
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

  if (!nvm_failed)
  {
    rval = (int) nvm3_writeData(nvm3_defaultHandle, data->parameter_id, (uint8_t*) data, sizeof(*data));
    if (rval)
    {
      I3_LOG(LOG_MASK_ERROR, "Failed to write new value for parameter %u, error %d.  NVM marked as unusable.", rval);
      nvm_failed = true;
    }
  }

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
    case PARAM_COLOR_DEMO_RGB_STATE:
      // RGB state and color mirror each other, so manually write the other matching parameter
      sCr_param_val[PARAM_COLOR_DEMO_ENUMERATION].value.enum_value = data->value.bitfield_value;
      break;
    case PARAM_COLOR_DEMO_ENUMERATION:
      // RGB state and color mirror each other, so manually write the other matching parameter
      sCr_param_val[PARAM_COLOR_DEMO_RGB_STATE].value.bitfield_value = data->value.enum_value;
      break;
    default:
      // Do nothing with the data, and assume that it is valid
      break;
  }
  return rval;
}

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

/* User code end [parameters.c: User Local Functions] */

