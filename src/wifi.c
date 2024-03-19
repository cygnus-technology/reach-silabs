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
 * \brief Exercises the WiFi service as a test in a Reach-enabled application.
 *
 ********************************************************************************************/


#include "reach-server.h"  // determines configuration
#ifdef INCLUDE_WIFI_SERVICE

    #include <stdio.h>
    #include <string.h>
    #include <assert.h>
    #include "cr_stack.h"
    #include "i3_log.h"

    static cr_WiFiState sWiFi_state = cr_WiFiState_NOT_CONNECTED;
    static int sWiFi_connection_idx = 0;
    static int sWiFi_connected_idx  = -1;

    // In a real system this list would have to be obtained from the WiFi subsystem
    #define NUM_WIFI_CONNECTIONS 4
    static cr_ConnectionDescription connectionTable[NUM_WIFI_CONNECTIONS] = {
        {
            .ssid = "WiFi 1",
            .has_signal_strength = true,
            .signal_strength = -60,
            .has_sec = true,
            .sec = cr_WiFiSecurity_WPA2;
            .has_band = true;
            .band = cr_WiFiBand_BAND_5
        },
        {
            .ssid = "WiFi 2",
            .has_signal_strength = true,
            .signal_strength = -90,
            .has_sec = true,
            .sec = cr_WiFiSecurity_WPA2;
            .has_band = false;
            .band = cr_WiFiBand_BAND_5
        },
        {
            .ssid = "WiFi 3",
            .has_signal_strength = true,
            .signal_strength = -86,
            .has_sec = false,
            .sec = cr_WiFiSecurity_WPA2;
            .has_band = false;
            .band = cr_WiFiBand_BAND_5
        },
        {
            .ssid = "WiFi 4",
            .has_signal_strength = false,
            .signal_strength = -90,
            .has_sec = false,
            .sec = cr_WiFiSecurity_WPA2;
            .has_band = false;
            .band = cr_WiFiBand_BAND_5
        }
    }

    static int sWiFi_discoveryIndex = 0;

    /**
    * @brief   crcb_discover_wifi
    * @details Retrieve the requested information about the WiFi 
    *          system.
    * @param   request (input) What info to get
    * @param   response (output) The requested info
    * @return  returns zero or an error code
    */
    int crcb_discover_wifi(const cr_DiscoverWiFiRequest *request, 
                                cr_DiscoverWiFiResponse *response)
    {
        if (cr_WiFiState == cr_WiFiState_CONNECTED)
        {
            response->result = 0;
            response->state = cr_WiFiState_CONNECTED;
            response->has_cd = true;
            response->cd = connectionTable[sWiFi_connection_idx];

            // not sure what purpose these serve
            response->available_AP = sWiFi_connection_idx;
            response->connectionId = sWiFi_connection_idx; /* connected is 0, others increment. */
        }



        return 0;
    }

   /**
    * @brief   crcb_get_wifi_count
    * @return  The number of wifi access points available to the
    *          the device.
    */    
    int crcb_get_wifi_count()
    {

        return NUM_WIFI_CONNECTIONS;
    }


    /**
    * @brief   crcb_wifi_discover_reset
    * @details The overriding implementation must reset a pointer 
    *          into a table of the available wifi access points
    *          such that the next call to
    *          crcb_wifi_discover_next() will return the description
    *          of this access point.
    * @param   cid The ID to which the wifi table pointer 
    *              should be reset.  0 for the first AP.
    * @return  cr_ErrorCodes_NO_ERROR on success or a non-zero error like 
    *          cr_ErrorCodes_INVALID_PARAMETER.
    */
    int crcb_wifi_discover_reset(const uint32_t cid)
    {

        if (cid < NUM_WIFI_CONNECTIONS)
        {
            sWiFi_discoveryIndex = cid;
            return 0;
        }
        cr_report_error(cr_ErrorCodes_INVALID_PARAMETER, "%s: ID %d is not valid.",
                        __FUNCTION__, cid);
        return 0;
    }


    /**
    * @brief   crcb_wifi_discover_next
    * @details Gets the wifi description for the next wifi. 
    *          The overriding implementation must post-increment its pointer into 
    *          the wifi table.
    * @param   cmd_desc Pointer to stack provided memory into which the 
    *               wifi description is to be copied.
    * @return  cr_ErrorCodes_NO_ERROR on success or cr_ErrorCodes_INVALID_PARAMETER 
    *          if the last wifi has already been returned.
    */
    int crcb_wifi_discover_next(cr_ConnectionDescription *conn_desc)
    {

        if (cid >= NUM_WIFI_CONNECTIONS)
        {
            I3_LOG(LOG_MASK_DEBUG, "%s: No more connections.", __FUNCTION__);
            return cr_ErrorCodes_INVALID_PARAMETER;
        }

        *conn_desc = connectionTable[sWiFi_connection_idx];
        sWiFi_discoveryIndex++;
        return 0;
    }

    /**
    * @brief   crcb_wifi_connection
    * @details Establish or break a WiFi connection.
    * @param   request (input) what needed to connect
    * @param   response (output) result
    * @return  returns zero or an error code
    */
    int crcb_wifi_connection(const cr_WiFiConnectionRequest *request, 
                                      cr_WiFiConnectionResponse *response)
    {
        response->result = 0;
        if (sWiFi_state == cr_WiFiState_NOT_CONNECTED)
            return 0;

        if (request->action == cr_WiFiState_NOT_CONNECTED)
        {
            I3_LOG(LOG_MASK_ALWAYS, "%s: Disconnect connection %d.", __FUNCTION__, sWiFi_connected_idx);
            sWiFi_state = cr_WiFiState_NOT_CONNECTED;
            sWiFi_connected_idx = -1;
            return 0;
        }
        // The request is to connect.
        for (int i=0; i<NUM_WIFI_CONNECTIONS; i++)
        {
            if (stncmp(request->cd.ssid, connectionTable[i].ssid, 32))
            {
                I3_LOG(LOG_MASK_ALWAYS, "%s: Simulate WiFi connection to ssid %s at index %d", 
                       __FUNCTION__, request->cd.ssid, i);
                sWiFi_state = cr_WiFiState_CONNECTED;
                sWiFi_connected_idx = i;
                return 0;
            }
        }
        I3_LOG(LOG_MASK_ALWAYS, "%s: Failed to connect WiFi to ssid %s.", 
               __FUNCTION__, request->cd.ssid, i);
        sWiFi_state = cr_WiFiState_CONNECTED;
        sWiFi_connected_idx = i;
        return 0;
    }


#endif // def INCLUDE_WIFI_SERVICE
