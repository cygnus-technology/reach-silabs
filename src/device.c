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
 *                       Copyright i3 Product Development 2023-2024
 *
 * \brief Provides the device info service to a Reach-enabled application.
 *
 ********************************************************************************************/

/**
 * @file      device.c
 * @brief     An example of support for the required device service in a Cygnus 
 *            Reach enabled device.  This file is part of the application and
 *            NOT part of the core stack.  Different applications can must
 *            expose their own device description using their own implementation
 *            of the reach callback functions illustrated here. The crcb_
 *            callback functions are documented in cr_weak.c.
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 * The Cygngus Reach firmware stack is shared under an MIT license.
 */

#include "reach-server.h"  // configures Reach

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "cr_stack.h"
#include "i3_log.h"
#include "app_version.h"
#include "reach_silabs.h"
#include "reach-server.h"  // determines configuration


// This is intended to live in flash
const cr_DeviceInfoResponse test1_di = 
{
    .protocol_version       = cr_ReachProtoVersion_CURRENT_VERSION,
    .device_name            = "Jack Reacher",
    .manufacturer           = "i3 Product Development",
    .device_description     = "This is a test of Jack Reacher's System.",
    .firmware_version       = "-1.-1.-1", // to be overwritten
    .services               = 0,
    .parameter_metadata_hash    = 22, // this will be overwritten
    .has_application_identifier = 0,  // false
    .application_identifier     = {0},
    .endpoints                  = 0,
};

/// Challenge Key based Access Control: 
/// The handling of access control using the challenge key is up 
/// to the device specific implementation.  This demonstration 
/// codes two layers of access control.  The complete lockout of 
/// access is handled at the Reach level using 
/// crcb_challenge_key_is_valid(). More fine grained access 
/// control is handled at the level of these crcb callbacks. 

#ifdef DEMO_ACCESS_CONTROL
  /// set this to expose only a limited set of parameters by 
  /// default. 
  static bool sDev_challenge_key_required = true;

  #ifdef LONG_KEYS
     // The keys must be null terminated, at most 32 chars including the null.
    static const char sDev_basic_access_key[REACH_LONG_STRING_LEN] = "0123456789012345678901234567890";
    static const char sDev_full_access_key[REACH_LONG_STRING_LEN] = "9876543210987654321098765432109";
  #else
    static const char sDev_basic_access_key[REACH_LONG_STRING_LEN] = "basic";
    static const char sDev_full_access_key[REACH_LONG_STRING_LEN] = "full";
  #endif

  // In this demo, basic access is always available.
  static bool sDev_basic_access_OK = true;
  // full access is granted via the challenge key.
  static bool sDev_full_access_OK = false;
#else
  // all access all the time
  static bool sDev_challenge_key_required = false;
  static const char sDev_basic_access_key[REACH_LONG_STRING_LEN] = "basic";
  static const char sDev_full_access_key[REACH_LONG_STRING_LEN] = "full";
  static bool sDev_basic_access_OK = true;
  static bool sDev_full_access_OK = true;
#endif  // def DEMO_ACCESS_CONTROL

bool device_get_basic_access_OK() {
    return sDev_basic_access_OK;
}
bool device_get_full_access_OK() {
    return sDev_full_access_OK;
}

static void sConfigure_access_control(const cr_DeviceInfoRequest *request, cr_DeviceInfoResponse *pDi)
{
  #ifdef DEMO_ACCESS_CONTROL
    /// If you are interested in access control, feel very free to
    /// change what happens here.  This demo has pieces to support
    /// three levels of access (none, basic, full) and it's most
    /// recently been configured to provide either basic (no key) or
    /// full with a key.  The design intends you to configure this
    /// as you need it.   All of the access controls are in the
    /// application files, and not in the Reach stack files.
    /// The most recent demo work uses the AccessLevel member in the
    /// parameter description structure to indicate whether a
    /// parameter is visible in a given level.
    sDev_challenge_key_required = true;

    // In this demo, basic access is always available.
    sDev_basic_access_OK = true;
    // full access is granted via the challenge key.
    sDev_full_access_OK = false;


    // Check access control:
    if (sDev_challenge_key_required)
    {
        if (!request->has_challenge_key)
        {
            // sDev_basic_access_OK = false;
            sDev_full_access_OK = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, No key, no access.\n", __FUNCTION__, test1_di.device_name);
        }
        else if (!strncmp(sDev_basic_access_key, request->challenge_key, REACH_LONG_STRING_LEN))
        {
            sDev_basic_access_OK = true;
            sDev_full_access_OK = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, basic access granted by key.\n", __FUNCTION__, test1_di.device_name);
        }
        else if (!strncmp(sDev_full_access_key, request->challenge_key, REACH_LONG_STRING_LEN))
        {
            sDev_basic_access_OK = true;
            sDev_full_access_OK = true; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, full access granted by key.\n", __FUNCTION__, test1_di.device_name);
        }
        else
        {
            // sDev_basic_access_OK = false;
            sDev_full_access_OK = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, Wrong key, no access.\n", __FUNCTION__, test1_di.device_name);
        }
    }
    else
    {
        sDev_basic_access_OK = true;
        sDev_full_access_OK = true; 
        i3_log(LOG_MASK_ALWAYS, "%s: %s, full access granted without key.\n", __FUNCTION__, test1_di.device_name);
    }

    if (sDev_basic_access_OK)
    {
        pDi->services = 0;
      #ifdef INCLUDE_PARAMETER_SERVICE
        pDi->services |= cr_ServiceIds_PARAMETER_REPO;
      #endif
    }
    else 
    {
        pDi->services = 0;
      #ifdef INCLUDE_PARAMETER_SERVICE
        pDi->services |= cr_ServiceIds_PARAMETER_REPO;
      #endif
      #ifdef INCLUDE_FILE_SERVICE
        pDi->services |= cr_ServiceIds_FILES;
      #endif
      #ifdef INCLUDE_STREAM_SERVICE
        pDi->services |= cr_ServiceIds_STREAMS;
      #endif
      #ifdef INCLUDE_COMMAND_SERVICE
        pDi->services |= cr_ServiceIds_COMMANDS;
      #endif
      #ifdef INCLUDE_CLI_SERVICE
        // pDi->services |= cr_ServiceIds_CLI;
      #endif
      #ifdef INCLUDE_TIME_SERVICE
        pDi->services |= cr_ServiceIds_TIME;
      #endif
      #ifdef INCLUDE_WIFI_SERVICE
        pDi->services |= cr_ServiceIds_TIME;
      #endif
    }
    if (sDev_full_access_OK)
    {   // Add CLI with full access 
      #ifdef INCLUDE_CLI_SERVICE
        pDi->services |= cr_ServiceIds_CLI;
      #endif
    }

  #else

    sDev_challenge_key_required = false;
    sDev_basic_access_OK = true;
    sDev_full_access_OK = true;

    pDi->services = 0;
  #ifdef INCLUDE_PARAMETER_SERVICE
    pDi->services |= cr_ServiceIds_PARAMETER_REPO;
  #endif
  #ifdef INCLUDE_FILE_SERVICE
    pDi->services |= cr_ServiceIds_FILES;
  #endif
  #ifdef INCLUDE_STREAM_SERVICE
    pDi->services |= cr_ServiceIds_STREAMS;
  #endif
  #ifdef INCLUDE_COMMAND_SERVICE
    pDi->services |= cr_ServiceIds_COMMANDS;
  #endif
  #ifdef INCLUDE_CLI_SERVICE
    pDi->services |= cr_ServiceIds_CLI;
  #endif
  #ifdef INCLUDE_TIME_SERVICE
    pDi->services |= cr_ServiceIds_TIME;
  #endif
  #ifdef INCLUDE_WIFI_SERVICE
    pDi->services |= cr_ServiceIds_TIME;
  #endif


  #endif  // def DEMO_ACCESS_CONTROL

}

// The stack will call this function.
// The const copy of the basis in flash is copied to RAM so that the device
// can overwrite varying data like SN and hash.
int crcb_device_get_info(const cr_DeviceInfoRequest *request, cr_DeviceInfoResponse *pDi)
{
    // The app owns the memory here.
    // The address is returned so that the data can come from flash.
    // use memcpy as the structure copy imposes an unnecessary address alignment requirement.
    memcpy(pDi, &test1_di, sizeof(cr_DeviceInfoResponse));

    sConfigure_access_control(request, pDi);

    sprintf(pDi->firmware_version, "%s", get_app_version() );
    snprintf(pDi->device_name, REACH_DEVICE_NAME_LEN, "%s", rsl_get_advertised_name());
    return 0;
}

int crcb_ping_get_signal_strength(int8_t *rssi)
{
    sl_bt_connection_get_median_rssi(rsl_get_connection(), rssi);
    return 0;
}

/**
* @brief   crcb_challenge_key_is_valid
* @details Called by the stack in various places to check 
*          whether access is granted by the challenge key.
*           The access grant here is binary.  Finer control
*           based on the specific key is determined by the
*           overriding application specific implementation.
* @return  true if access is granted.
*/
bool crcb_challenge_key_is_valid(void)
{
    return sDev_basic_access_OK;
}

/**
* @brief   crcb_invalidate_challenge_key
* @details Called by the stack on disconnect or other condition 
*          that warrants invalidating access.
*/
void crcb_invalidate_challenge_key(void)
{
    if (sDev_challenge_key_required)
    {
        // sDev_basic_access_OK = false;
        sDev_full_access_OK  = false;
    }
}

/**
* @brief   crcb_enable_remote_cli
* @details As the logging utility is technically part of Reach, 
*          this callback lets the app block the remote CLI.
* @return  true if access is granted.
*/
bool crcb_enable_remote_cli(void)
{
    return sDev_full_access_OK;
}

