
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
 * \brief Demonstrates access control in a Reach-enabled application.
 *
 ********************************************************************************************/

/**
 * @file      access.c
 * @brief     This file shows three possible levels of access 
 *            control.  "Free" access is the default.  There is
 *            no access control.  "Limited" access allows a user
 *            without a key to have some access.  "Locked down"
 *            mode requires a challenge key to get any
 *            information. This file is part of the application
 *            and NOT part of the core stack.
 * @copyright (c) Copyright 2023-2024 i3 Product Development. 
 * All Rights Reserved. The Cygngus Reach firmware stack is 
 * shared under an MIT license. 
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
#include "parameters.h"

// Demonstrate Access Control:
#define ACCESS_FREE         0   // no access control
#define ACCESS_LIMITED      1   // challenge key required for full access
#define ACCESS_LOCKED_DOWN  2   // challenge key required for any access
#define ACCESS_CONTROL_MODE     ACCESS_FREE

#if (ACCESS_CONTROL_MODE == ACCESS_FREE)
    // all access all the time: Weak functions do the job.
#endif // ACCESS_FREE


#if (ACCESS_CONTROL_MODE == ACCESS_LIMITED)
    /// Choose  this to expose only a limited set of parameters by 
    /// default.  In this example the CLI service and the 
    /// acceleration parameters are only available with a key. 
    static const char sDev_full_access_key[REACH_LONG_STRING_LEN] = "lemme in";

    // In this demo, basic access is always available.
    static bool sDev_basic_access_OK = true;
    // full access is granted via the challenge key.
    static bool sDev_full_access_OK  = false;

    bool device_get_basic_access_OK() {
        return sDev_basic_access_OK;
    }
    bool device_get_full_access_OK() {
        return sDev_full_access_OK;
    }

    bool crcb_challenge_key_is_valid(void) {
        // as false blocks most things, this is appropriate for lockdown. 
        return true;
    }

    void crcb_invalidate_challenge_key(void) {
        sDev_full_access_OK  = false;
    }

    /**
    * @brief   crcb_configure_access_control
    * @details Configure the device info response based on the 
    *          challenge key in the device info request.
    * @return  true if access is granted.
    */
    void crcb_configure_access_control(const cr_DeviceInfoRequest *request, cr_DeviceInfoResponse *pDi)
    {
        if (!request->has_challenge_key)
        {
            sDev_basic_access_OK = true;
            sDev_full_access_OK  = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, No key, limited access.\n", __FUNCTION__, pDi->device_name);
        }
        else if (!strncmp(sDev_full_access_key, request->challenge_key, REACH_LONG_STRING_LEN))
        {
            sDev_basic_access_OK = true;
            sDev_full_access_OK  = true; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, full access granted by key.\n", __FUNCTION__, pDi->device_name);
        }
        else
        {
            sDev_basic_access_OK = true;
            sDev_full_access_OK  = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, Wrong key, limited access.\n", __FUNCTION__, pDi->device_name);
        }

        if (!sDev_full_access_OK)
        {
            // remove CLI access
            pDi->services &= ~cr_ServiceIds_CLI;
        }
    }

    bool crcb_access_granted(const cr_ServiceIds service, const int32_t id)
    {
        // negative id checks whether this service is included.

        if (sDev_full_access_OK)
            return true;  // access everything

        if (service == cr_ServiceIds_CLI)
            return sDev_full_access_OK; // CLI only in full access mode

        if (service == cr_ServiceIds_PARAMETER_REPO)
        {
            switch (id)
            {
            case PARAM_ACCELERATION_X_AXIS: // acceleration is only available with full access
            case PARAM_ACCELERATION_Y_AXIS:
            case PARAM_ACCELERATION_Z_AXIS:
                return sDev_full_access_OK;
            default:
                break;
            }
        }
        return true;
    }
#endif // ACCESS_LIMITED



#if (ACCESS_CONTROL_MODE == ACCESS_LOCKED_DOWN)
    /// Choose this if you wish to require a challenge key to get 
    /// any info from the device.  Two challenge keys grant limited 
    /// or full access. 

    #ifdef LONG_KEYS
       // The keys must be null terminated, at most 32 chars including the null.
      static const char sDev_basic_access_key[REACH_LONG_STRING_LEN] = "0123456789012345678901234567890";
      static const char sDev_full_access_key[REACH_LONG_STRING_LEN] = "9876543210987654321098765432109";
    #else
      static const char sDev_basic_access_key[REACH_LONG_STRING_LEN] = "basic";
      static const char sDev_full_access_key[REACH_LONG_STRING_LEN] = "full";
    #endif

    static bool sDev_basic_access_OK = false;
    static bool sDev_full_access_OK = false;

    bool device_get_basic_access_OK() {
        return sDev_basic_access_OK;
    }
    bool device_get_full_access_OK() {
        return sDev_full_access_OK;
    }

    bool crcb_challenge_key_is_valid(void) {
        return sDev_full_access_OK || sDev_basic_access_OK;
    }

    void crcb_invalidate_challenge_key(void) {
        sDev_full_access_OK  = false;
        sDev_basic_access_OK = false;

    }

    bool crcb_access_grante(const cr_ServiceIds service, const uint32_t id)
    {
        if (!sDev_full_access_OK && !sDev_basic_access_OK)
            return false;

        if (sDev_full_access_OK)
            return true;

        // basic access:
        if (service != cr_ServiceIds_PARAMETER_REPO)
            return false;  // all other services blocked.

        switch (id)
        {
        case PARAM_ACCELERATION_X_AXIS: // acceleration is only available with full access
        case PARAM_ACCELERATION_Y_AXIS:
        case PARAM_ACCELERATION_Z_AXIS:
            return sDev_full_access_OK;
        default:
            break;
        }   
        return true;
    }

    void crcb_configure_access_control(const cr_DeviceInfoRequest *request, cr_DeviceInfoResponse *pDi)
    {
        if (!request->has_challenge_key)
        {
            sDev_basic_access_OK = false;
            sDev_full_access_OK  = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, No key, no access.\n", __FUNCTION__, pDi->device_name);
        }
        else if (!strncmp(sDev_full_access_key, request->challenge_key, REACH_LONG_STRING_LEN))
        {
            sDev_basic_access_OK = true;
            sDev_full_access_OK  = true; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, full access granted by key.\n", __FUNCTION__, pDi->device_name);
        }
        else if (!strncmp(sDev_basic_access_key, request->challenge_key, REACH_LONG_STRING_LEN))
        {
            sDev_basic_access_OK = true;
            sDev_full_access_OK  = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, basic access granted by key.\n", __FUNCTION__, pDi->device_name);
        }
        else
        {
            sDev_basic_access_OK = false;
            sDev_full_access_OK  = false; 
            i3_log(LOG_MASK_ALWAYS, "%s: %s, Wrong key, no access.\n", __FUNCTION__, pDi->device_name);
        }

        pDi->services = 0;
        if (sDev_basic_access_OK)
        {
            // only partial parameter access
          #ifdef INCLUDE_PARAMETER_SERVICE
            pDi->services |= cr_ServiceIds_PARAMETER_REPO;
          #endif
        }
        if (sDev_full_access_OK)
        {
            // everything
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
          #ifdef INCLUDE_CLI_SERVICE
            pDi->services |= cr_ServiceIds_CLI;
          #endif
        }
    }

#endif // ACCESS_CONTROL_MODE













