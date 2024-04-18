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
 * @file      reach_silabs.h
 * @brief     Integration of Silicon Labs BLE features for Cygnus Reach
 * @copyright (c) Copyright 2023-2024 i3 Product Development. All Rights Reserved.
 *
 * Original Author: Chuck Peplinski
 * (Refactored by Joseph Peplinski)
 *
 ********************************************************************************************/

#ifndef _REACH_H_
#define _REACH_H_

#include <stddef.h>

#include "gatt_db.h"
#include "sl_bluetooth.h"
#include "reach-server.h"

// TODO: Make this work properly with our system, this is based on https://stackoverflow.com/a/35152306
#ifdef _DOXYGEN_
  /** @brief How often the device will check for new data when there is no BLE connection. */
  #define BLE_ADVERTISING_PROCESSING_INTERVAL_MS 100

  /** @brief How often the device will check for new data when BLE is connected. */
  #define BLE_CONNECTED_PROCESSING_INTERVAL_MS 0

  /** @brief The characteristic used by Reach, defined in gatt_db.h and configured through the GATT table editor.
   * @note Changing the UUID from the suggested value will prevent this device from working with the generic Reach app
   */
  #define REACH_CHARACTERISTIC gattdb_reach

  /** @brief The characteristic data used to store the advertised name.
   * @note This is not intended to be accessed outside of gatt_db.c, but modifying it seems to be the easiest way to change the advertisement.
   */
  #define DEVICE_NAME_CHARACTERISTIC_ATTRIBUTE gattdb_attribute_field_10

#endif

/**
* @brief Initializes the Silicon Labs Reach BLE implementation
* @note This should be called in app_init()
*/
void rsl_init(void);

/**
* @brief Handles Reach-related BLE processing as needed
* @note This should be called in app_process_action()
*/
void rsl_process_action(void);

/**
* @brief Handles Reach-specific BLE events
* @note This should be called in sl_bt_on_event(sl_bt_msg_t *evt) after the standard app event handler's switch statement
* @param evt The pointer to the event
*/
void rsl_bt_on_event(sl_bt_msg_t *evt);

/**
* @brief Sets the advertised name
* @param name The new advertised name.  This cannot be longer than APP_ADVERTISED_NAME_LENGTH
* @return 0 on success, -1 if the name is invalid, or -2 if the stack-level name change failed
*/
int rsl_set_advertised_name(char *name);

/**
* @brief Gets the system uptime in milliseconds.
* @return The uptime if successful, or a negative error code on failure.
*/
int64_t rsl_get_system_uptime(void);

/**
* @brief Busy-waits for the specified period of time
* @param ms How long to wait, in milliseconds
*/
void rsl_delay(uint32_t ms);

/**
* @brief Gets the handle for the current connection, for accessing BLE information outside of reach_silabs.c
* @return The current handle, or 0 if not connected
*/
uint8_t rsl_get_current_connection_handle(void);

/**
* @brief A callback for when a device connects via BLE, which can be used for app-specific actions
* @note This is implemented as a weak function which returns immediately in reach_silabs.c
*/
void rsl_app_handle_ble_connection(void);

/**
* @brief A callback for when a device disconnects via BLE, which can be used for app-specific actions
* @note This is implemented as a weak function which returns immediately in reach_silabs.c
*/
void rsl_app_handle_ble_disconnection(void);

#endif // _REACH_H_
