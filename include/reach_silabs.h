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
 * \brief reach_silabs.h/.c provides a SiLabs specific implementation of the required
 *      Reach functionality.
 *
 * Original Author: Chuck.Peplinski
 *
 ********************************************************************************************/

/**
 * @file      reach_silabs.h
 * @brief     Integration of SiLabs BLE features for Cygnus Reach demo
 * 
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 */


#ifndef _REACH_H_
#define _REACH_H_

#include <stddef.h>

#include "gatt_db.h"
#include "sl_bluetooth.h"
#include "sl_cli_command.h"
#include "reach-server.h"

#define REACH_MAX_PROMPT_SIZE 256
#define REACH_SN_KEY    0x10000

// should come from GATT DB.
#define REACH_BLE_CHARICTERISTIC_ID   gattdb_REACH

// Cyan is OK on both white and black backgrounds
#define TEXT_CLI   TEXT_CYAN

void rsl_init();
int rsl_stats();
int rsl_set_auth(bool app, bool device, bool secure);
void rsl_confirm_passkey(bool good);
void rsl_set_passkey(uint32_t pk);

// stores the connection info so others can use it.
void rsl_inform_connection(uint8_t connection, uint16_t characteristic);
uint8_t rsl_get_connection(void);
void rsl_inform_subscribed(bool subscribed);
int rsl_get_rssi(void);

int rsl_notify_client(uint8_t *data, size_t len);

/**************************************************************************//**
 * Reach version of the SiLabs Application Init.
 *****************************************************************************/
void rsl_app_init(void);

/**************************************************************************//**
 * Reach version of the SiLabs Application Process Action. 
 *****************************************************************************/
void rsl_app_process_action(void);

/**************************************************************************//**
 * Reach version of the SiLabs event handler.
 *****************************************************************************/
void rsl_bt_on_event(sl_bt_msg_t *evt);


/**
 * The Reach handler for each SiLabs sl_bt_evt is made into a function. This 
 * should simplify integration with new SiLabs projects.  Returns 0 if the Reach 
 * thing is handled.  Non-zero return implies there should be another handler. 
 * 
 */
void rsl_on_evt_system_boot_id();
void rsl_on_evt_connection_opened_id(sl_bt_msg_t *evt);
void rsl_on_evt_connection_closed_id();
int  rsl_on_evt_gatt_server_user_read_request_id(
    sl_bt_evt_gatt_server_user_read_request_t *data);
int rsl_on_evt_gatt_server_characteristic_status_id(
    sl_bt_evt_gatt_server_characteristic_status_t *data);
// int rsl_on_evt_gatt_server_user_write_request_id(
//    sl_bt_evt_gatt_server_user_write_request_t *data);
void rsl_on_evt_connection_parameters_id(sl_bt_evt_connection_parameters_t *data);
void rsl_on_evt_connection_phy_status_id(sl_bt_evt_connection_phy_status_t *data);
int rsl_on_evt_gatt_server_attribute_value_id(sl_bt_evt_gatt_server_attribute_value_t *data);


const char *rsl_get_advertised_name();

int rsl_read_serial_number(unsigned int *sn);
int rsl_write_serial_number(unsigned int sn);

/**************************************************************************//**
 * Command line handlers:
 *****************************************************************************/
extern void print_versions(sl_cli_command_arg_t *args);
extern void slash(sl_cli_command_arg_t *args);
extern void cli_lm(sl_cli_command_arg_t *args);
#ifdef INCLUDE_CLI_SERVICE
  extern void cli_rcli(sl_cli_command_arg_t *args);
#endif  // def INCLUDE_CLI_SERVICE
extern void cli_phy(sl_cli_command_arg_t *args);
extern void cli_nvm(sl_cli_command_arg_t *args);
extern void cli_sn(sl_cli_command_arg_t *args);


#endif // _REACH_H_
