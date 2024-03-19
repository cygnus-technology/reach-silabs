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
 *                        (c) Copyright 2023, i3 Product Development
 *
 * reach_silabs.h/.c provides a SiLabs specific implementation of the required
 *      Reach functionality. It is rather on the border between the C stack and the app.
 *
 * Original Author: Chuck.Peplinski
 *
 ********************************************************************************************/

/**
 * @file      reach_silabs.c
 * @brief     Integration of SiLabs BLE features for Cygnus Reach demo
 * 
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 */


#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "nvm3_default.h"

#include "reach_silabs.h"
#include "reach-server.h"
#include "cr_stack.h"
#include "I3_LOG.h"
#include "app_version.h"
#include "reach_version.h"

#include "sl_bluetooth.h"
#include "em_common.h"
#include "app_assert.h"
#include "em_cmu.h"
#include "gatt_db.h"
#include "nvm3_default.h"
#include "app.h"

#ifdef REACH_USE_ENCRYPTION
#define AUTHENTICATION_IO_DISPLAY_ONLY 0
#define AUTHENTICATION_IO_DISPLAY_YES_NO 1
#define AUTHENTICATION_IO_KEYBOARD_ONLY 2
#define AUTHENTICATION_IO_NO_INPUT_NO_OUTPUT 3
#define AUTHENTICATION_IO_KEYBOARD_DISPLAY 4

#define AUTHENTICATION_LEVEL_JUST_WORKS 0
#define AUTHENTICATION_LEVEL_PASSKEY_ENTRY_NUMERIC_COMPARISON 0b1
#define AUTHENTICATION_LEVEL_SECURE_CONNECTIONS_ONLY 0b10

#endif // REACH_USE_ENCRYPTION

static uint8_t  sRsl_ble_connection = 0;
static uint16_t sRsl_ble_characteristic = 0;
static bool     sRsl_ble_subscribed = false;
static int8_t   sRsl_rssi = 0;

static uint32_t sNotifyCount = 0;
static uint32_t sNotifyDelay = 0;
static uint32_t sNotifyMaxDelay = 0;

#ifdef REACH_USE_BONDING
static bool allow_bonding = false;
#endif // REACH_USE_BONDING

#ifdef REACH_USE_ENCRYPTION
#ifdef REACH_USE_AUTHENTICATION
static uint8_t auth_settings[2];  // First index is MITM protection, second is I/O
#else
static uint8_t auth_settings[] = {AUTHENTICATION_LEVEL_JUST_WORKS, AUTHENTICATION_IO_NO_INPUT_NO_OUTPUT};  // First index is MITM protection, second is I/O
#endif // REACH_USE_AUTHENTICATION
#endif // REACH_USE_ENCRYPTION

void rsl_inform_connection(uint8_t connection, uint16_t characteristic)
{
  sRsl_ble_connection = connection;
  sRsl_ble_characteristic = characteristic;
  if (connection == 0)
      sRsl_ble_subscribed = false;
}

uint8_t rsl_get_connection(void)
{
    return sRsl_ble_connection; 
}

int rsl_get_rssi(void)
{
    return (int)sRsl_rssi;
}

void rsl_inform_subscribed(bool subscribed)
{
    sRsl_ble_subscribed = subscribed;
}

int rsl_stats()
{
#if 0
    extern uint32_t gBytesWritten, gLastOffset, gWfPacketCount;
    extern char gRfLoop;

    int avg = sNotifyDelay/sNotifyCount;
    I3_LOG(LOG_MASK_BLE, "  wf: %d bytes, %d packets.", gBytesWritten, gWfPacketCount);
    I3_LOG(LOG_MASK_BLE, "  rf: %d notifications, in groups of %d, retries avg %d, max %d\n",
                 sNotifyCount, gRfLoop, avg, sNotifyMaxDelay);

    sNotifyCount = 0;
    sNotifyDelay = 0;
    sNotifyMaxDelay = 0;

    gBytesWritten = 0;
    gLastOffset = 0;
    gWfPacketCount = 0;
#endif
    return 0;
}

void rsl_init()
{
    I3_LOG(LOG_MASK_ALWAYS, TEXT_GREEN "!!!");
    print_versions(NULL);
    I3_LOG(LOG_MASK_ALWAYS, TEXT_GREEN "!!!");

    cr_test_sizes();

    // Local init to emulate a parameter respository
    extern void init_param_repo();
    init_param_repo();

    I3_LOG(LOG_MASK_ALWAYS, "Enter 'help' to see available commands.");

#ifdef REACH_USE_AUTHENTICATION
    Ecode_t rval = nvm3_readData(nvm3_defaultHandle, REACH_AUTHENTICATION_SETTINGS_KEY, auth_settings, sizeof(auth_settings));
    if (rval)
    {
      I3_LOG(LOG_MASK_ERROR, "Failed to get stored authentication settings, error %u.  Using default of both devices pairing", rval);
      auth_settings[0] = AUTHENTICATION_LEVEL_PASSKEY_ENTRY_NUMERIC_COMPARISON;
      auth_settings[1] = AUTHENTICATION_IO_KEYBOARD_DISPLAY;
      rval = nvm3_writeData(nvm3_defaultHandle, REACH_AUTHENTICATION_SETTINGS_KEY, auth_settings, sizeof(auth_settings));
      if (rval)
        I3_LOG(LOG_MASK_ERROR, "Failed to write new authentication settings, error %u", rval);
    }
#endif // REACH_USE_AUTHENTICATION
}

#ifdef REACH_USE_AUTHENTICATION
int rsl_set_auth(bool app, bool device, bool secure)
{
  auth_settings[0] = AUTHENTICATION_LEVEL_PASSKEY_ENTRY_NUMERIC_COMPARISON;
  if (secure)
    auth_settings[0] |= AUTHENTICATION_LEVEL_SECURE_CONNECTIONS_ONLY;
  if (app && device)
    auth_settings[1] = AUTHENTICATION_IO_KEYBOARD_DISPLAY;
  else if (app)
    auth_settings[1] = AUTHENTICATION_IO_DISPLAY_ONLY;
  else if (device)
    auth_settings[1] = AUTHENTICATION_IO_KEYBOARD_ONLY;
  uint32_t rval = (uint32_t) nvm3_writeData(nvm3_defaultHandle, REACH_AUTHENTICATION_SETTINGS_KEY, auth_settings, sizeof(auth_settings));
  if (rval)
    I3_LOG(LOG_MASK_ERROR, "Failed to write new authentication settings, error %u", rval);
  rval = (uint32_t) sl_bt_sm_configure(auth_settings[0], auth_settings[1]);
  if (rval)
    I3_LOG(LOG_MASK_ERROR, "Failed to apply new authentication settings, error %u", rval);
#ifdef REACH_USE_BONDING
  rval = (uint32_t) sl_bt_sm_set_bondable_mode(1);
  if (rval)
    I3_LOG(LOG_MASK_ERROR, "Failed to set bondable mode, error %u", rval);
  rval = (uint32_t) sl_bt_sm_delete_bondings();
  if (rval)
    I3_LOG(LOG_MASK_ERROR, "Failed to delete bondings, error %u", rval);
#endif // REACH_USE_BONDING
  return 0;
}

void rsl_confirm_passkey(bool good)
{
  if (good)
    sl_bt_sm_passkey_confirm(sRsl_ble_connection, 1);
  else
    sl_bt_sm_passkey_confirm(sRsl_ble_connection, 0);
}
void rsl_set_passkey(uint32_t pk)
{
  int rval = (int) sl_bt_sm_enter_passkey(sRsl_ble_connection, pk);
  if (rval)
    I3_LOG(LOG_MASK_ERROR, "Failed to enter passkey, error %d", rval);
}
#endif // REACH_USE_AUTHENTICATION

#ifdef INCLUDE_CLI_SERVICE
// This CLI handler for remote access mirrors that found in silabs_cli.c for local access.
// It calls the same functions but uses a different parser.

// As a demo of challenge key based security, the CLI is disabled unless you have full access.
bool device_get_full_access_OK();

int crcb_cli_enter(const char *ins)
{
    // block access to the CLI unless you have full acceess
    if (!device_get_full_access_OK())
        return 0;
    
    if (*ins == 0xA)
    {
        I3_LOG(LOG_MASK_ALWAYS | LOG_MASK_BARE, TEXT_CLI ">");
        return 0;
    }

    if ((*ins == '?') || (!strncmp("help", ins, 4)) )
    {
        I3_LOG(LOG_MASK_ALWAYS, TEXT_GREEN "!!! Cygnus Reach Server, built %s, %s", __DATE__, __TIME__);
        I3_LOG(LOG_MASK_ALWAYS, TEXT_GREEN "!!! App Version %d.%d.%d", APP_MAJOR_VERSION, APP_MINOR_VERSION, APP_PATCH_VERSION);
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "Commands:");
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "  ver : Print versions");
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "  /   : Display status");
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "  lm  : Log Mask: lm 0xXXX");
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "  rcli: Remote CLI <on|off>");
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "  phy : phy <1|2> BLE PHY 1M or 2M");
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "  nvm : nvm <?|clear|init>");
        I3_LOG(LOG_MASK_ALWAYS, TEXT_CLI "  sn  : read or set serial number in NVM. sn <?|clear|N>");
        I3_LOG(LOG_MASK_ALWAYS | LOG_MASK_BARE, TEXT_CLI ">");
        return 0;
    }

    crcb_set_command_line(ins);
    // step through remote_command_table and execute if matching
    if (!strncmp("ver", ins, 3))
        print_versions(NULL);
    else if (!strncmp("/", ins, 1))
        slash(NULL);
    else if (!strncmp("lm", ins, 2))
        cli_lm(NULL);
  #ifdef INCLUDE_CLI_SERVICE
    else if (!strncmp("rcli", ins, 4))
        cli_rcli(NULL);
  #endif  // def INCLUDE_CLI_SERVICE
    else if (!strncmp("phy", ins, 3))
        cli_phy(NULL);
    else if (!strncmp("nvm", ins, 3))
        cli_nvm(NULL);
    else if (!strncmp("sn", ins, 2))
        cli_sn(NULL);
    else
        I3_LOG(LOG_MASK_ALWAYS | LOG_MASK_BARE, TEXT_CLI 
               "CLI command '%s' not recognized (0x%x).", ins, *ins);

    I3_LOG(LOG_MASK_ALWAYS | LOG_MASK_BARE, TEXT_CLI ">");
    return 0;
}
#endif // def INCLUDE_CLI_SERVICE

int rsl_notify_client(uint8_t *data, size_t len)
{
    sl_status_t rval;

    I3_LOG(LOG_MASK_BLE, "%s(%d)", __FUNCTION__, len);
    sNotifyCount++;
    uint32_t loopCount = 0;
    do
    {
        rval = sl_bt_gatt_server_send_notification(sRsl_ble_connection,
                                                   sRsl_ble_characteristic,
                                                   len,
                                                   (uint8_t*)data);
        loopCount++;
        if (loopCount > 3000)
            break;
    }
    while (rval != SL_STATUS_OK);

    sNotifyDelay += loopCount;
    if (loopCount > sNotifyMaxDelay)
        sNotifyMaxDelay = loopCount;

    return (int)rval;
}

// The cr_process function calls crcb_send_coded_response() to send responses to the client.
// Returns zero on success.
int crcb_send_coded_response(const uint8_t *respBuf, size_t respSize)
{
    if (respSize == 0)
    {
        I3_LOG(LOG_MASK_REACH, "%s: No bytes to send.  ", __FUNCTION__);
        return cr_ErrorCodes_NO_ERROR;
    }
    int rval = 0;
    I3_LOG(LOG_MASK_REACH, TEXT_GREEN "%s: send %d bytes.", __FUNCTION__, respSize);

    if (sRsl_ble_subscribed)
    {   int s1;
        I3_LOG(LOG_MASK_BLE, "%s: call rsl_notify_client() with %d bytes", __FUNCTION__, respSize);
        s1 = rsl_notify_client((uint8_t*)respBuf, respSize);
        switch (s1)
        {
        case SL_STATUS_OK:  // 0
            I3_LOG(LOG_MASK_BLE, "Sent notification %d bytes, OK.", respSize);
            rval = 0;
            break;
        case SL_STATUS_COMMAND_TOO_LONG:
            LOG_ERROR("Response of %d bytes is too long. Return %d", 
                      respSize, cr_ErrorCodes_BUFFER_TOO_SMALL);
            rval = cr_ErrorCodes_BUFFER_TOO_SMALL;
            break;
        case SL_STATUS_INVALID_HANDLE:
            LOG_ERROR("Invalid Handle. Return %d", cr_ErrorCodes_INVALID_PARAMETER);
            rval = cr_ErrorCodes_INVALID_PARAMETER;
            break;
        default:
            LOG_ERROR("Response of %d bytes failed with status 0x%x.\n", 
                             respSize, s1);
            rval = cr_ErrorCodes_INVALID_PARAMETER;
        }
        return rval;
    }
    return cr_ErrorCodes_NO_ERROR;
}

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

#define UPDATE_APP_TIMER_MS 50
uint32_t time_since_startup = 0;

sl_sleeptimer_timer_handle_t sleepTimerHandle;
void app_timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data)
{
    (void)handle;
    (void)data;
    //Code executed when the timer expires.
    time_since_startup++;
}

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void rsl_app_init(void)
{
    sl_status_t status;

    // this clears a line between runs.
    // init_cygnus_cli() prints a banner.
    I3_LOG(LOG_MASK_ALWAYS, "\n\n**\n");

    // Add the CLI commands implemented in cli_functions.c
    extern void init_cygnus_cli();
    init_cygnus_cli();
    
    // Add a timer for Reach
    sl_sleeptimer_init();
    uint32_t timer_timeout = UPDATE_APP_TIMER_MS;
    status = sl_sleeptimer_start_periodic_timer_ms(&sleepTimerHandle,
                                                   timer_timeout,
                                                   app_timer_callback,
                                                   (void *)NULL, 0, 0);
    app_assert_status(status);
    CMU_ClockEnable(cmuClock_RTCC, true);
    
    rsl_init();

    cr_init();
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void rsl_app_process_action(void)
{
    extern void generate_data_for_notify(uint32_t timestamp);

    uint32_t timestamp = time_since_startup * UPDATE_APP_TIMER_MS;
    generate_data_for_notify(timestamp);
    // process reach stack
    cr_process(timestamp);
}


/**************************************************************************//**
 * Advertise Name
 *****************************************************************************/
extern sli_bt_gattdb_attribute_chrvalue_t gattdb_attribute_field_10;

const char *rsl_get_advertised_name() 
{
    return (char*)(gattdb_attribute_field_10.data);
}

int rsl_set_advertised_name(unsigned int sn)
{
    // Give the device a unique name:
    // gattdb_attribute_field_10 holds the device name.
    // Check advertise in the generic access service to enable the long name.
    memset(gattdb_attribute_field_10.data, 0, gattdb_attribute_field_10.max_len);
    const char *aName = cr_get_advertised_name();
    if (aName[0] != 0) {
        gattdb_attribute_field_10.len =
                snprintf((char*)(gattdb_attribute_field_10.data),
                         gattdb_attribute_field_10.max_len,
                         "%s", aName);
    }
    else {
        I3_LOG(LOG_MASK_ALWAYS, TEXT_YELLOW "Serial number not set.  Using %u (%x:%x)", 
               sn, sn >> 8, sn & 0xFF);
        gattdb_attribute_field_10.len =
                snprintf((char*)(gattdb_attribute_field_10.data),
                         gattdb_attribute_field_10.max_len,
                         "Reacher %u", sn);
    }
    I3_LOG(LOG_MASK_ALWAYS, TEXT_YELLOW "Advertise non-extended name %s, len %d of max %d", 
           gattdb_attribute_field_10.data, 
           gattdb_attribute_field_10.len, 
           gattdb_attribute_field_10.max_len);
    return 0;
}


/**************************************************************************//**
 * Bluetooth stack event handler.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 * 
 * Reach expects a Reach service advertising UUID
 * edd59269-79b3-4ec2-a6a2-89bfb640f930 and a REACH
 * characteristic with UUID
 * d42d1039-1d11-4f10-bae6-5f3b44cf6439.
 * Support Read, Write, Write without response and notify.
 * Do not support Reliable write or indicate.
 * Maximum length is 255.
 *****************************************************************************/
void rsl_bt_on_event(sl_bt_msg_t *evt)
{
    switch (SL_BT_MSG_ID(evt->header))
    {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
        rsl_on_evt_system_boot_id();
        break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
        rsl_on_evt_connection_opened_id(evt);
        break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
        rsl_on_evt_connection_closed_id();
        break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // request to read characteristic
    case sl_bt_evt_gatt_server_user_read_request_id:
    {
        sl_bt_evt_gatt_server_user_read_request_t *data = 
            &evt->data.evt_gatt_server_user_read_request;
        int rval = rsl_on_evt_gatt_server_user_read_request_id(data);
        if (rval != 0) {
            // handle other things here.
            LOG_ERROR( 
                   "%s: Failed to handle non-REACH BLE read request (%d)", 
                   __FUNCTION__, rval);
        }
        break;
    }

    // subscribe to notification
    case sl_bt_evt_gatt_server_characteristic_status_id:
    {
        sl_bt_evt_gatt_server_characteristic_status_t *data = 
            &evt->data.evt_gatt_server_characteristic_status;
        int rval = rsl_on_evt_gatt_server_characteristic_status_id(data);
        if (rval != 0) {
            // handle other things here.
            LOG_ERROR( 
                   "%s: Failed to handle non-REACH BLE configuration change. characteristic 0x%x. rval %d", 
                __FUNCTION__, data->characteristic, rval);
        }
        break;
    }
    /* This is obsolete, not called now, has a warning about unmatched types.
    // accept a write request
    case sl_bt_evt_gatt_server_user_write_request_id:
    {
        // sl_bt_evt_gatt_server_attribute_value_t *data =
        sl_bt_evt_gatt_server_user_write_request_t *data =
            &evt->data.evt_gatt_server_attribute_value;

        int rval = rsl_on_evt_gatt_server_user_write_request_id(data);
        if (rval != 0) {
            // handle other things here.
            LOG_ERROR(
                   "%s: Failed to handle non-REACH BLE write request (%d)", 
                   __FUNCTION__, rval);
        }
        break;
    }
    */

    // display connection parameteter
    case sl_bt_evt_connection_parameters_id:
    {
        sl_bt_evt_connection_parameters_t *data = &evt->data.evt_connection_parameters;
        rsl_on_evt_connection_parameters_id(data);
        break;
    }

    case sl_bt_evt_connection_phy_status_id:
    {
        sl_bt_evt_connection_phy_status_t *data = &evt->data.evt_connection_phy_status;
        rsl_on_evt_connection_phy_status_id(data);
        break;
    }
    case sl_bt_evt_connection_remote_used_features_id:
        // I3_LOG(LOG_MASK_BLE, "sl_bt_evt_connection_remote_used_features_id 0x%x", SL_BT_MSG_ID(evt->header));
        break;
    case sl_bt_evt_gatt_mtu_exchanged_id:
        // I3_LOG(LOG_MASK_BLE, "sl_bt_evt_gatt_mtu_exchanged_id 0x%x", SL_BT_MSG_ID(evt->header));
        break;

    case sl_bt_evt_gatt_server_attribute_value_id:
    {
        sl_bt_evt_gatt_server_attribute_value_t *data = &evt->data.evt_gatt_server_attribute_value;
        int rval = rsl_on_evt_gatt_server_attribute_value_id(data);
        if (rval != 0) {
            // handle other things here.
            LOG_ERROR(
                   "%s: Failed to handle non-REACH BLE attribute value. attribute 0x%x. len %d. rval %d", 
                   __FUNCTION__, data->value.data, data->value.len, rval);
        }
        break;
    }
    case sl_bt_evt_gatt_server_execute_write_completed_id:
    {
        sl_bt_evt_gatt_server_execute_write_completed_t *data = &evt->data.evt_gatt_server_execute_write_completed;
        I3_LOG(LOG_MASK_WARN, "write completed result 0x%x.", data->result);
        break;
    }
  #if 1
    case sl_bt_evt_gatt_procedure_completed_id:
        I3_LOG(LOG_MASK_BLE, "sl_bt_evt_gatt_procedure_completed_id 0x%x", SL_BT_MSG_ID(evt->header));
        break;
    case sl_bt_evt_user_message_to_host_id:
        I3_LOG(LOG_MASK_BLE, "sl_bt_evt_user_message_to_host_id 0x%x", SL_BT_MSG_ID(evt->header));
        break;
    case sl_bt_cmd_gatt_server_send_notification_id:
        I3_LOG(LOG_MASK_BLE, "sl_bt_cmd_gatt_server_send_notification_id 0x%x", SL_BT_MSG_ID(evt->header));
        break;
  #endif

    case sl_bt_evt_system_resource_exhausted_id:
    {
        // I hit this when doing a read very quickly.
        // We have buffer errors.  I believe they are benign, just causing some delay.
        // The comment suggests changing SL_BT_CONFIG_BUFFER_SIZE, but that didn't help.
        sl_bt_evt_system_resource_exhausted_t *data = &evt->data.evt_system_resource_exhausted;
        I3_LOG(LOG_MASK_WARN, "evt_system_resource_exhausted: disc %d, buf %d, heap %d.",
               data ->num_buffers_discarded, 
               data->num_buffer_allocation_failures, 
               data->num_heap_allocation_failures);
        break;
    }
    case sl_bt_evt_connection_data_length_id:
        // normal when phy changes to 2M.
        break;

    case sl_bt_evt_connection_rssi_id: 
    {
        // RSSI was requested, this is the response
        sl_bt_evt_connection_rssi_t *data =  &evt->data.evt_connection_rssi;
        // I3_LOG(LOG_MASK_WARN, "RSSI reports %d.",  data->rssi);
        sRsl_rssi = data->rssi;   // overwrite the previous value
        break;
    }
#ifdef REACH_USE_ENCRYPTION
    case sl_bt_evt_sm_bonded_id:
      printf("Bond success\r\n");
      break;

    case sl_bt_evt_sm_bonding_failed_id:
      printf("Bonding failed, reason 0x%2X\r\n",
                 evt->data.evt_sm_bonding_failed.reason);
      sl_bt_connection_close(evt->data.evt_sm_bonding_failed.connection);
      break;
#ifdef REACH_USE_BONDING
    case sl_bt_evt_sm_confirm_bonding_id:
      printf("Bonding confirm\r\n");
      sl_bt_sm_bonding_confirm(evt->data.evt_sm_confirm_bonding.connection, allow_bonding);
      break;
#endif // REACH_USE_BONDING

#ifdef REACH_USE_AUTHENTICATION
    case sl_bt_evt_sm_confirm_passkey_id:
      i3_log(LOG_MASK_ALWAYS, "Passkey is %06lu, type 'pkc <y|n>' into the CLI to confirm or deny that this matches the key seen on the phone", evt->data.evt_sm_confirm_passkey.passkey);
      break;
    case sl_bt_evt_sm_passkey_display_id:
      i3_log(LOG_MASK_ALWAYS, "Enter the following passkey into the phone: %06lu", evt->data.evt_sm_passkey_display.passkey);
      break;
    case sl_bt_evt_sm_passkey_request_id:
      i3_log(LOG_MASK_ALWAYS, "Passkey request received, type 'pk <code>' into the CLI");
      break;
#endif // REACH_USE_AUTHENTICATION
#endif // REACH_USE_ENCRYPTION

    // -------------------------------
    // Default event handler.
    default:
        LOG_ERROR( "Event 0x%x", SL_BT_MSG_ID(evt->header));
        break;
    }
}

int rsl_read_serial_number(unsigned int *sn)
{
    size_t dataLen;
    uint32_t objectType;
    Ecode_t eCode;

    nvm3_getObjectInfo(nvm3_defaultHandle, REACH_SN_KEY, &objectType, &dataLen);
    if (objectType != NVM3_OBJECTTYPE_DATA) {
        I3_LOG(LOG_MASK_WARN, "Serial number key 0x%x not found in NVM.", REACH_SN_KEY);
        return -1;
    }
    if (dataLen != sizeof(unsigned int)) {
        I3_LOG(LOG_MASK_WARN, "Serial number key has wrong size, %d, not %d.", dataLen, sizeof(unsigned int));
    }
    eCode = nvm3_readData(nvm3_defaultHandle, REACH_SN_KEY, (uint8_t *)sn, sizeof(unsigned int));
    if (ECODE_NVM3_OK != eCode) {
        LOG_ERROR( "NVM Read of SN key 0x%x failed with 0x%x.", 
           REACH_SN_KEY, eCode);
        return -2;
    }
    return 0;
}

int rsl_write_serial_number(unsigned int sn)
{
    nvm3_writeData(nvm3_defaultHandle, REACH_SN_KEY, (uint8_t *)&sn, sizeof(unsigned int));
    return 0;
}


///////////////////////////////////////////////////////////////////////////
// Functions to handle events
///////////////////////////////////////////////////////////////////////////

void rsl_on_evt_system_boot_id()
{
    bd_addr address;
    uint8_t address_type;
    uint8_t sysId[8];
    sl_status_t sc;

    // I3_LOG(LOG_MASK_BLE, "sl_bt_evt_system_boot_id 0x%x", SL_BT_MSG_ID(evt->header));
    // Extract unique ID from BT Address.
    sc = sl_bt_system_get_identity_address(&address, &address_type);
    app_assert_status(sc);

    // Pad and reverse unique ID to get System ID.
    sysId[0] = address.addr[5];
    sysId[1] = address.addr[4];
    sysId[2] = address.addr[3];
    sysId[3] = 0xFF;
    sysId[4] = 0xFE;
    sysId[5] = address.addr[2];
    sysId[6] = address.addr[1];
    sysId[7] = address.addr[0];

    sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id, 0,
                                                 sizeof(sysId),
                                                 sysId);
    app_assert_status(sc);
    I3_LOG(LOG_MASK_BLE, "BLE system ID %02X:%02X:%02X:%02X:%02X:%02X",
           sysId[0], sysId[1], sysId[2], sysId[5], sysId[6], sysId[7]);
#ifdef REACH_USE_ENCRYPTION
    // Set up authentication
    sc = sl_bt_sm_configure(auth_settings[0], auth_settings[1]);
    app_assert_status(sc);

#ifdef REACH_USE_BONDING
    sc = sl_bt_sm_set_bondable_mode(1);
    app_assert_status(sc);

    // Clear stored bondings on startup (for testing purposes)
    sc = sl_bt_sm_delete_bondings();
    app_assert_status(sc);
#endif // REACH_USE_BONDING

#ifdef REACH_USE_AUTHENTICATION
//    sc = sl_bt_sm_set_passkey(0);
//    app_assert_status(sc);
#endif // REACH_USE_AUTHENTICATION
#endif // REACH_USE_ENCRYPTION

    // the sysId becomes the default serial number if not otherwise set.
    rsl_set_advertised_name((sysId[6]<<8) + sysId[7]);

    sc = sl_bt_advertiser_create_set(&advertising_set_handle);
    app_assert_status(sc);

    // Generate data for advertising
    sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                               sl_bt_advertiser_general_discoverable);
    app_assert_status(sc);

    // Set advertising interval to 100ms.
    sc = sl_bt_advertiser_set_timing(advertising_set_handle, 
                                     160, // min. adv. interval (milliseconds * 1.6)
                                     160, // max. adv. interval (milliseconds * 1.6)
                                     0,   // adv. duration
                                     0);  // max. num. adv. events
    app_assert_status(sc);
    // Start advertising and enable connections.
    sc = sl_bt_legacy_advertiser_start(advertising_set_handle, 
                                       sl_bt_advertiser_connectable_scannable);
    app_assert_status(sc);
}
 
///////////////////////////////////////////////////////////////////////////
void rsl_on_evt_connection_opened_id(sl_bt_msg_t *evt)
{
    extern char gPhy;

    sl_bt_connection_set_preferred_phy(evt->data.evt_connection_opened.connection, gPhy, gPhy);
    I3_LOG(LOG_MASK_ALWAYS, "Device connected to BLE with connection ID %u. %dM Phy requested",
           evt->data.evt_connection_opened.connection, gPhy);

    rsl_inform_connection(evt->data.evt_connection_opened.connection, REACH_BLE_CHARICTERISTIC_ID);
    sl_bt_connection_get_median_rssi(evt->data.evt_connection_opened.connection, &sRsl_rssi);

    // inform Reach and reinit.
    cr_set_comm_link_connected(true);

#ifdef REACH_USE_ENCRYPTION
    sl_bt_sm_increase_security(sRsl_ble_connection);
#endif // REACH_USE_ENCRYPTION
}

///////////////////////////////////////////////////////////////////////////
void rsl_on_evt_connection_closed_id()
{
    sl_status_t sc;
    I3_LOG(LOG_MASK_ALWAYS, "Device disconnected from BLE, restart advertising");

    // Generate data for advertising
    sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                               sl_bt_advertiser_general_discoverable);
    app_assert_status(sc);

    // Restart advertising after client has disconnected.
    sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                       sl_bt_advertiser_connectable_scannable);
    app_assert_status(sc);

    rsl_inform_connection(0, REACH_BLE_CHARICTERISTIC_ID);
    cr_set_comm_link_connected(false);
}

///////////////////////////////////////////////////////////////////////////
int  rsl_on_evt_gatt_server_user_read_request_id(
    sl_bt_evt_gatt_server_user_read_request_t *data)
{
    if (data->characteristic != REACH_BLE_CHARICTERISTIC_ID)
        return 1;

    I3_LOG(LOG_MASK_BLE, "sl_bt_evt_gatt_server_user_read_request_id %d", 
           data->characteristic);

    uint8_t *resp_buf;
    size_t resp_len;

    cr_get_coded_response_buffer(&resp_buf, &resp_len);
    I3_LOG(LOG_MASK_BLE, "Read request for reach. %d.", resp_len);

    int rval = sl_bt_gatt_server_send_user_read_response(data->connection,
                                                         data->characteristic,
                                                         0, // uint8_t att_errorcode,
                                                         resp_len, // size_t value_len,
                                                         resp_buf, // const uint8_t* value,
                                                         NULL);
    if (rval != 0)
    {
        LOG_ERROR( "%s: Reach user read responded. rval 0x%x.", 
               __FUNCTION__, rval);
    }
    return 0;
}


///////////////////////////////////////////////////////////////////////////
int rsl_on_evt_gatt_server_characteristic_status_id(
    sl_bt_evt_gatt_server_characteristic_status_t *data)
{
#ifdef REACH_USE_ENCRYPTION
    if (data->characteristic == gattdb_service_changed_char)
        return 0;
#endif // REACH_USE_ENCRYPTION
    if (data->characteristic != REACH_BLE_CHARICTERISTIC_ID)
    {
        // characteristic 3 can be related to secure connections.
        i3_log(LOG_MASK_WARN, "%s: Non reach characteristic %d", __FUNCTION__, data->characteristic);
        return 0;
    }

    if (data->status_flags != sl_bt_gatt_server_client_config)
        return 2;
    if (data->client_config_flags == sl_bt_gatt_notification)
    {
        I3_LOG(LOG_MASK_ALWAYS, "Subscribed to REACH notifications");
        rsl_inform_subscribed(true);
    }
    else
    {
        I3_LOG(LOG_MASK_BLE, "sl_bt_evt_gatt_server_characteristic_status_id: Unsubscribed from REACH notifications");
        rsl_inform_subscribed(false);
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////// 
/// This seems obsolete, not used now. 
/* 
  int rsl_on_evt_gatt_server_user_write_request_id(
    sl_bt_evt_gatt_server_user_write_request_t *data)
{
    if (data->characteristic != REACH_BLE_CHARICTERISTIC_ID)
        return 1;
    I3_LOG(LOG_MASK_ALWAYS, "Write to reach.  Len %d", data->value.len);
    cr_store_coded_prompt(data->value.data, data->value.len);
    return 0;
}
*/

///////////////////////////////////////////////////////////////////////////
void rsl_on_evt_connection_parameters_id(sl_bt_evt_connection_parameters_t *data)
{
    I3_LOG(LOG_MASK_BLE, "connection %d. interval %d. latency %d. timeout %d. secure %d, txsize %d",
           data->connection,    /**< Connection handle */
           data->interval,      /**< Connection interval. Time = Value x 1.25 ms */
           data->latency,       /**< Peripheral latency (how many connection intervals the peripheral can skip) */
           data->timeout,       /**< Supervision timeout. Time = Value x 10 ms */
           data->security_mode, /** Security mode. Values:
                                   (0x0): No security
                                   (0x1): Unauthenticated pairing with encryption
                                   (0x2): Authenticated pairing with encryption
                                   (0x3): Authenticated Secure Connections pairing with 128-bit encryption */
           data->txsize);       /**< Maximum Data Channel PDU Payload size that the controller can send in an air packet */
}

///////////////////////////////////////////////////////////////////////////
void rsl_on_evt_connection_phy_status_id(sl_bt_evt_connection_phy_status_t *data)
{
    switch (data->phy)
    {   /**< Current active PHY. See values from @ref sl_bt_connection_set_preferred_phy command. */
    case 1:
        I3_LOG(LOG_MASK_ALWAYS, TEXT_YELLOW "Slow 1M PHY" TEXT_RESET);
        break;
    case 2:
        I3_LOG(LOG_MASK_ALWAYS, TEXT_GREEN "Fast 2M PHY" TEXT_RESET);
        break;
    case 4:
        I3_LOG(LOG_MASK_ALWAYS, TEXT_YELLOW "Slow 125k coded PHY" TEXT_RESET);
        break;
    case 8:
        I3_LOG(LOG_MASK_ALWAYS, TEXT_YELLOW "Slow 500k coded PHY" TEXT_RESET);
        break;
    default:
        LOG_ERROR( "Undefined BLE PHY 0x%x", data->phy);
        break;
    }
}

///////////////////////////////////////////////////////////////////////////
int rsl_on_evt_gatt_server_attribute_value_id(sl_bt_evt_gatt_server_attribute_value_t *data)
{
    if (data->attribute != REACH_BLE_CHARICTERISTIC_ID)
        return 1;
    I3_LOG(LOG_MASK_BLE, "Attribute Write to reach.  Len %d", data->value.len);
    cr_store_coded_prompt(data->value.data, data->value.len);
    return 0;
}


