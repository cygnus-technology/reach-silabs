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
 * \brief A minimal implementation of Wi-Fi discovery and access
 *
 * Original Author: Chuck Peplinski
 * Script Authors: Joseph Peplinski and Andrew Carlson
 *
 * Generated with version 1.0.0 of the C code generator
 *
 ********************************************************************************************/

/********************************************************************************************
 *************************************     Includes     *************************************
 *******************************************************************************************/

#include "cr_stack.h"

/* User code start [wifi.c: User Includes] */
/* User code end [wifi.c: User Includes] */

/********************************************************************************************
 *************************************     Defines     **************************************
 *******************************************************************************************/

#define MAX_NUM_WIFI_ACCESS_POINTS 4

/* User code start [wifi.c: User Defines] */
/* User code end [wifi.c: User Defines] */

/********************************************************************************************
 ************************************     Data Types     ************************************
 *******************************************************************************************/

/* User code start [wifi.c: User Data Types] */
/* User code end [wifi.c: User Data Types] */

/********************************************************************************************
 *********************************     Global Variables     *********************************
 *******************************************************************************************/

/* User code start [wifi.c: User Global Variables] */
/* User code end [wifi.c: User Global Variables] */

/********************************************************************************************
 ***************************     Local Function Declarations     ****************************
 *******************************************************************************************/

/* User code start [wifi.c: User Local Function Declarations] */
/* User code end [wifi.c: User Local Function Declarations] */

/********************************************************************************************
 ******************************     Local/Extern Variables     ******************************
 *******************************************************************************************/

static uint32_t sWiFi_index = 0;
static uint32_t sWiFi_count = 0;
static cr_ConnectionDescription wifi_desc[MAX_NUM_WIFI_ACCESS_POINTS];

/* User code start [wifi.c: User Local/Extern Variables] */
static bool sFirstDiscover = true;
/* User code end [wifi.c: User Local/Extern Variables] */

/********************************************************************************************
 *********************************     Global Functions     *********************************
 *******************************************************************************************/

/* User code start [wifi.c: User Global Functions] */
/* User code end [wifi.c: User Global Functions] */

/********************************************************************************************
 *************************     Cygnus Reach Callback Functions     **************************
 *******************************************************************************************/

/**
* @brief   crcb_discover_wifi
* @details Retrieve the requested information about the WiFi
 *         system. The discovery process may take some time the
 *         implementation can choose to return
 *         cr_ErrorCodes_INCOMPLETE to indicate that the
 *         discover command needs to be issued again until it
 *         succeeds. Other errors are reported via the result
 *         field.
* @param   request (input) Unused.
* @param   response (output) The requested info
* @return  returns cr_ErrorCodes_NO_ERROR or
*          cr_ErrorCodes_INCOMPLETE.
*/
int crcb_discover_wifi(const cr_DiscoverWiFi *request, cr_DiscoverWiFiResponse *response)
{
  (void)request;
  response->result = cr_ErrorCodes_NOT_IMPLEMENTED;
  int rval = cr_ErrorCodes_INCOMPLETE;

  /* User code start [WiFi: Discover]
   * If you have not just launched a scan, launch one.
   * If you don't yet have data, return cr_ErrorCodes_INCOMPLETE.
   * The wifi_desc variable should be filled with available access points,
   * and sWiFi_count should be updated appropriately */

  response->result = 0;
  rval = 0;
  if (sFirstDiscover)
  {
    cr_ConnectionDescription temp = {
        .ssid = "Test Network",
        .has_signal_strength = true,
        .signal_strength = -20,
        .is_connected = false
    };
    cr_ConnectionDescription temp2 = {
        .ssid = "Network with Password",
        .has_signal_strength = true,
        .signal_strength = -15,
        .has_sec = true,
        .sec = cr_WiFiSecurity_WEP,
        .has_band = true,
        .band = cr_WiFiBand_BAND_5,
        .is_connected = false
    };
    wifi_desc[0] = temp;
    wifi_desc[1] = temp2;
    sWiFi_count = 2;
    sFirstDiscover = false;
  }

  /* User code end [WiFi: Discover] */
  return rval;
}

/**
* @brief   crcb_get_wifi_count
* @return  The number of wifi access points available to the
*          the device.
*/
int crcb_get_wifi_count()
{
  /* User code start [WiFi: Get Count] */
  /* User code end [WiFi: Get Count] */

  return sWiFi_count;
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
  if (cid >= sWiFi_count)
  {
    sWiFi_index = MAX_NUM_WIFI_ACCESS_POINTS;
    return cr_ErrorCodes_INVALID_ID;
  }
  sWiFi_index = cid;
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
  if (sWiFi_index >= MAX_NUM_WIFI_ACCESS_POINTS)
    return cr_ErrorCodes_INVALID_ID;

  if (sWiFi_index >= sWiFi_count)
    return cr_ErrorCodes_INVALID_PARAMETER;

  *conn_desc = wifi_desc[sWiFi_index];
  sWiFi_index++;
  return 0;
}

/**
* @brief   crcb_wifi_connection
* @details Establish or break a WiFi connection.
* @param   request (input) what needed to connect
* @param   response (output) result
* @return  returns zero or an error code
*/
int crcb_wifi_connection(const cr_WiFiConnectionRequest *request, cr_WiFiConnectionResponse *response)
{
  affirm(request);
  affirm(response);
  int rval = 0;
  
  /* User code start [WiFi: Connect/Disconnect] */

  for (uint32_t i = 0; i < sWiFi_count; i++)
  {
    if (!memcmp(request->ssid, wifi_desc[i].ssid, sizeof(wifi_desc[i].ssid)))
    {
      // Found a match
      if (request->connect)
      {
        if (i == 1)
        {
          if (!request->has_password || strncmp(request->password, "password", sizeof(request->password)))
          {
            response->result = cr_ErrorCodes_PERMISSION_DENIED;
            response->has_result_message = true;
            strncpy(response->result_message, "Incorrect password!", sizeof(response->result_message));
            return 0;
          }
        }
        wifi_desc[i].is_connected = response->connected = true;
        if (wifi_desc[i].has_signal_strength)
        {
          response->has_signal_strength = true;
          response->signal_strength = wifi_desc[i].signal_strength;
        }
      }
      else if (request->disconnect)
      {
        wifi_desc[i].is_connected = response->connected = false;
        if (wifi_desc[i].has_signal_strength)
        {
          response->has_signal_strength = true;
          response->signal_strength = wifi_desc[i].signal_strength;
        }
      }
      else
      {
        response->connected = wifi_desc[i].is_connected;
        if (wifi_desc[i].has_signal_strength)
        {
          response->has_signal_strength = true;
          response->signal_strength = wifi_desc[i].signal_strength;
        }
      }
      response->result = 0;
      return 0;
    }
  }
  return cr_ErrorCodes_INVALID_ID;

  /* User code end [WiFi: Connect/Disconnect] */

  return rval;
}

/* User code start [wifi.c: User Cygnus Reach Callback Functions] */
/* User code end [wifi.c: User Cygnus Reach Callback Functions] */

/********************************************************************************************
 *********************************     Local Functions     **********************************
 *******************************************************************************************/

/* User code start [wifi.c: User Local Functions] */
/* User code end [wifi.c: User Local Functions] */

