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
 * @file      reach_silabs.c
 * @brief     Integration of Silicon Labs BLE features for Cygnus Reach
 * @copyright (c) Copyright 2023-2024 i3 Product Development. All Rights Reserved.
 *
 * Original Author: Chuck Peplinski
 * (Refactored by Joseph Peplinski)
 *
 ********************************************************************************************/

#include "reach_silabs.h"

#include <string.h>

#include "sl_bluetooth.h"
#include "sl_sleeptimer.h"
#include "em_common.h"
#include "app_assert.h"

#include "reach-server.h"
#include "cr_stack.h"
#include "i3_log.h"
#include "app_version.h"
#include "reach_version.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#ifndef BLE_ADVERTISING_PROCESSING_INTERVAL_MS
#define BLE_ADVERTISING_PROCESSING_INTERVAL_MS 100
#endif // BLE_ADVERTISING_PROCESSING_INTERVAL_MS

#ifndef BLE_CONNECTED_PROCESSING_INTERVAL_MS
#define BLE_CONNECTED_PROCESSING_INTERVAL_MS 0
#endif // BLE_CONNECTED_PROCESSING_INTERVAL_MS

#ifndef REACH_CHARACTERISTIC
#define REACH_CHARACTERISTIC gattdb_reach
#endif // REACH_CHARACTERISTIC

#ifndef DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE
#define DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE gattdb_attribute_field_10
#endif // DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE

/*******************************************************************************
 ****************************   LOCAL  TYPES   *********************************
 ******************************************************************************/

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// State information
static uint8_t device_connection = 0;
static bool ble_subscribed = false;
static uint64_t last_process_time = 0;

// Extern variables required
extern sli_bt_gattdb_attribute_chrvalue_t DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE;

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

void rsl_init(void)
{
#ifdef VERBOSE_SIZES
  // Useful for testing changes to reach-protobuf, but otherwise not needed
  cr_test_sizes();
#endif

  cr_init();

  // Set the default name in Reach to the default advertised BLE name
  cr_set_advertised_name((char *) DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.data, 
                         DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.len);
}

void rsl_process_action(void)
{
  int64_t uptime = rsl_get_system_uptime();
  if (uptime < 0)
  {
    I3_LOG(LOG_MASK_ERROR, "Failed to get system uptime");
    return;
  }
  int64_t next_process_time = last_process_time + (cr_get_comm_link_connected() ? BLE_CONNECTED_PROCESSING_INTERVAL_MS:BLE_ADVERTISING_PROCESSING_INTERVAL_MS);
  if (uptime >= next_process_time)
  {
    cr_process((uint32_t) uptime);
    last_process_time = uptime;
  }
}

void rsl_bt_on_event(sl_bt_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header))
  {
    // Startup
    case sl_bt_evt_system_boot_id:
      // Nothing needed
      break;

    // Connection/disconnection
    case sl_bt_evt_connection_opened_id:
      device_connection = evt->data.evt_connection_opened.connection;
      rsl_app_handle_ble_connection();
      cr_set_comm_link_connected(true);
      break;
    case sl_bt_evt_connection_closed_id:
      cr_set_comm_link_connected(false);
      ble_subscribed = false;
      device_connection = 0;
      rsl_app_handle_ble_disconnection();
      break;

    // Read/write/subscribe
    case sl_bt_evt_gatt_server_user_read_request_id:
    {
      sl_bt_evt_gatt_server_user_read_request_t *data = &evt->data.evt_gatt_server_user_read_request;
      if (data->characteristic != REACH_CHARACTERISTIC)
        break;
      uint8_t *resp_buf;
      size_t resp_len;

      cr_get_coded_response_buffer(&resp_buf, &resp_len);
      I3_LOG(LOG_MASK_BLE, "Reach read request, length %u", resp_len);

      int rval = sl_bt_gatt_server_send_user_read_response(data->connection, data->characteristic, 0, resp_len, resp_buf, NULL);
      if (rval != 0)
      {
        LOG_ERROR("Failed to send read response, error %d", rval);
      }
      break;
    }
    case sl_bt_evt_gatt_server_user_write_request_id:
      // Deprecated in favor of sl_bt_evt_gatt_server_attribute_value_id
      break;
    case sl_bt_evt_gatt_server_attribute_value_id:
    {
      sl_bt_evt_gatt_server_attribute_value_t *data = &evt->data.evt_gatt_server_attribute_value;
      if (data->attribute != REACH_CHARACTERISTIC)
        break;
      I3_LOG(LOG_MASK_BLE, "Reach write, length %d", data->value.len);
      cr_store_coded_prompt(data->value.data, data->value.len);
      break;
    }
    case sl_bt_evt_gatt_server_characteristic_status_id:
    {
      sl_bt_evt_gatt_server_characteristic_status_t *data = &evt->data.evt_gatt_server_characteristic_status;
      if (data->characteristic != REACH_CHARACTERISTIC || data->status_flags != sl_bt_gatt_server_client_config)
        break;
      ble_subscribed = (data->client_config_flags == sl_bt_gatt_notification);
      I3_LOG(LOG_MASK_BLE, "%s Reach characteristic", (data->client_config_flags == sl_bt_gatt_notification) ? "Subscribed to" : "Unsubscribed from");
      break;
    }

    // Events mostly useful for debugging
    case sl_bt_evt_connection_parameters_id:
    {
      sl_bt_evt_connection_parameters_t *data = &evt->data.evt_connection_parameters;
      I3_LOG(LOG_MASK_BLE, "connection %d. interval %d. latency %d. timeout %d. secure %d, txsize %d",
          data->connection, /**< Connection handle */
          data->interval, /**< Connection interval. Time = Value x 1.25 ms */
          data->latency, /**< Peripheral latency (how many connection intervals the peripheral can skip) */
          data->timeout, /**< Supervision timeout. Time = Value x 10 ms */
          data->security_mode, /** Security mode. Values:
                                                         (0x0): No security
                                                         (0x1): Unauthenticated pairing with encryption
                                                         (0x2): Authenticated pairing with encryption
                                                         (0x3): Authenticated Secure Connections pairing with 128-bit encryption */
          data->txsize); /**< Maximum Data Channel PDU Payload size that the controller can send in an air packet */
      break;
    }
    case sl_bt_evt_system_resource_exhausted_id:
    {
      sl_bt_evt_system_resource_exhausted_t *data = &evt->data.evt_system_resource_exhausted;
      I3_LOG(LOG_MASK_WARN, "evt_system_resource_exhausted: disc %d, buf %d, heap %d.", data->num_buffers_discarded, data->num_buffer_allocation_failures,
          data->num_heap_allocation_failures);
      break;
    }
    case sl_bt_evt_connection_phy_status_id:
    case sl_bt_evt_connection_remote_used_features_id:
    case sl_bt_evt_gatt_mtu_exchanged_id:
    case sl_bt_evt_gatt_server_execute_write_completed_id:
    case sl_bt_evt_gatt_procedure_completed_id:
    case sl_bt_evt_user_message_to_host_id:
    case sl_bt_evt_connection_data_length_id:
    case sl_bt_evt_connection_rssi_id:
      // Useful debugging information is available in these cases, but this isn't necessary for general use
      break;

    default:
      // Unhandled event, ignore
      break;
  }
}

// strnlen is technically a Linux function and is often not found by the compiler.
size_t strnlen( const char * s,size_t maxlen );

int rsl_set_advertised_name(char *name)
{
  // Check "Advertise" in the generic access service and increase the "Device Name" parameter's maximum length to enable the long name.
  size_t name_length = strnlen(name, DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.max_len);
  if (name_length > DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.max_len || name_length == 0)
    return -1;

  memset(DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.data, 0, DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.max_len);
  strncpy((char*) (DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.data), name, DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.max_len);
  DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE.len = name_length;
  cr_set_advertised_name(name, strlen(name));
  return 0;
}

int64_t rsl_get_system_uptime(void)
{
  uint64_t uptime = sl_sleeptimer_get_tick_count64();
  uint64_t uptime_ms = 0;
  sl_status_t rval = sl_sleeptimer_tick64_to_ms(uptime, &uptime_ms);
  if (rval != 0)
    return -1;
  return (int64_t) uptime_ms;
}

int crcb_send_coded_response(const uint8_t *respBuf, size_t respSize)
{
  if (respSize == 0)
  {
    I3_LOG(LOG_MASK_REACH, "%s: No bytes to send.  ", __FUNCTION__);
    return cr_ErrorCodes_NO_ERROR;
  }
  if (!ble_subscribed)
    return cr_ErrorCodes_NO_ERROR;
  I3_LOG(LOG_MASK_REACH, TEXT_GREEN "%s: send %d bytes.", __FUNCTION__, respSize);
  I3_LOG(LOG_MASK_BLE, "%s: call rsl_notify_client() with %d bytes", __FUNCTION__, respSize);
  int rval = sl_bt_gatt_server_send_notification(device_connection, REACH_CHARACTERISTIC, respSize, respBuf);
  switch (rval)
  {
    case SL_STATUS_OK:  // 0
      I3_LOG(LOG_MASK_BLE, "Sent notification %d bytes, OK.", respSize);
      rval = cr_ErrorCodes_NO_ERROR;
      break;
    case SL_STATUS_COMMAND_TOO_LONG:
      LOG_ERROR("Response of %d bytes is too long. Return %d", respSize, cr_ErrorCodes_BUFFER_TOO_SMALL);
      rval = cr_ErrorCodes_BUFFER_TOO_SMALL;
      break;
    case SL_STATUS_INVALID_HANDLE:
      LOG_ERROR("Invalid Handle. Return %d", cr_ErrorCodes_INVALID_PARAMETER);
      rval = cr_ErrorCodes_INVALID_PARAMETER;
      break;
    default:
      LOG_ERROR("Response of %d bytes failed, error 0x%x.", respSize, rval);
      rval = cr_ErrorCodes_INVALID_PARAMETER;
      break;
  }
  return rval;
}

void __attribute__((weak)) rsl_app_handle_ble_connection(void)
{
  pvtCrParam_init_notifications();
  I3_LOG(LOG_MASK_ALWAYS, "BLE connected");
  return;
}

void __attribute__((weak)) rsl_app_handle_ble_disconnection(void)
{
  pvtCrParam_clear_notifications();
  I3_LOG(LOG_MASK_ALWAYS, "BLE disconnected");
  return;
}

uint8_t rsl_get_current_connection_handle(void)
{
  return device_connection;
}

/*******************************************************************************
 ***************************   LOCAL FUNCTIONS    ******************************
 ******************************************************************************/


