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
 * @file      time.c
 * @brief     A minimal implementation of Reach data access.  Auto-generated by a Python script.
 * @copyright 2023-2024 i3 Product Development. All Rights Reserved.
 *
 * Original Author: Chuck Peplinski
 * Script Author: Joseph Peplinski
 *
 *
 ********************************************************************************************/

#include "definitions.h"

#ifdef INCLUDE_TIME_SERVICE

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "i3_log.h"
#include "app_version.h"
#include "cr_stack.h"

// Extra includes and forward declarations here.
// User code start [T1]
static int64_t time_offset = 0;
#include "reach_silabs.h"
// User code end [T1]


int crcb_time_get(cr_TimeGetResponse *response)
{
  // User code start [T2]
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
  // User code end [T2]
  return 0;
}

int crcb_time_set(const cr_TimeSetRequest *request)
{
  // User code start [T3]
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
  // User code end [T3]
  return 0;
}

// Local variables and functions here
// User code start [T4]
// User code end [T4]
#endif

