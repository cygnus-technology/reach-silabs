/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * This file was modified by Joseph Peplinski for use with the
 * Cygnus Reach Thunderboard demo
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "sl_button.h"
#include "sl_simple_button_instances.h"
#include "sl_led.h"
#include "sl_simple_led_instances.h"
#include "sl_sensor_hall.h"
#include "sl_sensor_light.h"
#include "sl_sensor_rht.h"
#include "sl_sensor_imu.h"
#include "app.h"

#include "reach_silabs.h"
#include "parameters.h"
#include "files.h"
#include "cli.h"

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

static bool identify_enabled = false;
static uint16_t identify_interval_ms = 1000;
static bool identify_led_on = false;
static bool button_pressed = false;

static int64_t last_blink_time = 0;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////

  sl_sensor_hall_init();
  sl_sensor_light_init();
  sl_sensor_rht_init();
  sl_sensor_imu_init();
  sl_sensor_imu_enable(true);
  sl_sensor_imu_calibrate();

  parameters_init();
  files_init();
  cli_init();

  rsl_init();
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
  rsl_process_action();

  cli_poll();

  if (identify_enabled && (rsl_get_system_uptime() - last_blink_time) > identify_interval_ms)
  {
    last_blink_time = rsl_get_system_uptime();
    if (identify_led_on)
      sl_led_turn_off(&sl_led_led0);
    else
      sl_led_turn_on(&sl_led_led0);
    identify_led_on = !identify_led_on;
  }
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Set advertising interval to 100ms.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        160, // min. adv. interval (milliseconds * 1.6)
        160, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      app_assert_status(sc);
      // Start advertising and enable connections.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_legacy_advertiser_connectable);
      app_assert_status(sc);
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Restart advertising after client has disconnected.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_legacy_advertiser_connectable);
      app_assert_status(sc);
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }

  // Handle Reach-related events
  rsl_bt_on_event(evt);
}

void app_enable_identify(bool en)
{
  identify_enabled = en;
  if (!en && identify_led_on)
  {
    identify_led_on = false;
    sl_led_turn_off(&sl_led_led0);
  }
}

bool app_identify_enabled(void)
{
  return identify_enabled;
}

void app_set_identify_interval(float seconds)
{
  if (seconds < 0)
    return;
  identify_interval_ms = (uint16_t) ((seconds * 1000) / 2);
}

bool app_get_identify_led_on(void)
{
  return identify_led_on;
}

bool app_get_button_pressed(void)
{
  return button_pressed;
}

void sl_button_on_change (const sl_button_t *handle)
{
  (void) handle;
  if (sl_button_btn0.get_state(&sl_button_btn0))
  {
    app_enable_identify(!identify_enabled);
    button_pressed = true;
  }
  else
    button_pressed = false;
}

void rsl_app_handle_ble_connection(void)
{
  cr_set_comm_link_connected(true);
 #ifndef SKIP_NOTIFICATIONS_AT_CONNECT
  cr_init_param_notifications();
 #endif
  I3_LOG(LOG_MASK_ALWAYS, "BLE connected");
  return;
}

void rsl_app_handle_ble_disconnection(void)
{
  cr_clear_param_notifications();
  I3_LOG(LOG_MASK_ALWAYS, "BLE disconnected");
  return;
}
