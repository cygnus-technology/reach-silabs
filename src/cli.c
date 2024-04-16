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
 * @file      cli.c
 * @brief     An example implementation of functions to handle the Reach CLI service
 * @copyright (c) Copyright 2023-2024 i3 Product Development. All Rights Reserved.
 *
 * Original Author: Joseph Peplinski
 *
 ********************************************************************************************/

#include "nvm3_generic.h"
#include "sl_bluetooth.h"
#include "sl_iostream.h"
#include "sl_iostream_handles.h"
#include "sl_gsdk_version.h"

#include "reach-server.h"
#include "cr_stack.h"
#include "i3_log.h"
#include "app_version.h"
#include "reach_silabs.h"

#define CLI_USE_PARAM_REPO_COLOR

#define TEXT_CLI "%s"

static void slash(void);
static void lm(const char *input);

extern char * param_repo_get_cli_text_color(void);

static sl_iostream_t *handle;
static char input[64];
static uint8_t input_length = 0;

void cli_init(void)
{
  handle = sl_iostream_get_handle("vcom");

  // Clear the screen and print some information on startup
  char clear_screen[] = "\033[2J\033]H";
  sl_iostream_write(handle, clear_screen, sizeof(clear_screen));
  print_versions();
  sl_iostream_putchar(handle, '>');
}

void cli_poll(void)
{
  if (input_length == sizeof(input))
  {
    i3_log(LOG_MASK_WARN, "CLI input too long, clearing");
    memset(input, 0, sizeof(input));
    input_length = 0;
  }
  if (!sl_iostream_getchar(handle, &input[input_length]))
  {
    switch (input[input_length])
    {
      case '\r':
        sl_iostream_putchar(handle, '\r');
        sl_iostream_putchar(handle, '\n');
        if (input_length == 0)
        {
          sl_iostream_putchar(handle, '>');
          break; // No data, no need to call anything
        }
        input[input_length] = 0; // Null-terminate the string
        crcb_cli_enter((const char*) input);
        input_length = 0;
        memset(input, 0, sizeof(input));
        sl_iostream_putchar(handle, '>');
        break;
      case '\n':
        break; // Ignore, only expect '\r' for command execution
      case '\b':
        // Received a backspace
        if (input_length > 0)
        {
          input[--input_length] = 0;
          sl_iostream_putchar(handle, '\b');
          sl_iostream_putchar(handle, ' ');
          sl_iostream_putchar(handle, '\b');
        }
        break;
      default:
        // Still waiting for an input
        sl_iostream_putchar(handle, input[input_length]);
        if (input_length < sizeof(input))
          input_length++;
        break;
    }
  }
}

char sAppVersion[CR_STACK_VERSION_LEN];
const char *get_app_version()
{
  #ifdef DEV_BUILD
    snprintf(sAppVersion, CR_STACK_VERSION_LEN, "%u.%u.%u-dev", 
             APP_MAJOR_VERSION, APP_MINOR_VERSION, APP_PATCH_VERSION);
  #else
    snprintf(sAppVersion, CR_STACK_VERSION_LEN, "%u.%u.%u", 
             APP_MAJOR_VERSION, APP_MINOR_VERSION, APP_PATCH_VERSION);
  #endif
    return sAppVersion;
}


void print_versions(void)
{
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "!!! Reach Thunderboard demo, built %s, %s", 
         param_repo_get_cli_text_color(), __DATE__, __TIME__);
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "!!!   Silicon Labs Gecko SDK version %s", 
         param_repo_get_cli_text_color(), SL_GSDK_VERSION_STR);
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "!!!   Reach stack version %s", 
         param_repo_get_cli_text_color(), cr_get_reach_version());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "!!!   Reach protobuf version %s", 
         param_repo_get_cli_text_color(), cr_get_proto_version());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "!!!   App version %s", 
         param_repo_get_cli_text_color(), get_app_version());

  #ifdef INCLUDE_CLI_SERVICE
    if (i3_log_get_remote_cli_enable())
        i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!! Remote CLI support enabled.");
    else
        i3_log(LOG_MASK_ALWAYS, TEXT_YELLOW "!!! Remote CLI support built but not enabled.");
  #else
    i3_log(LOG_MASK_ALWAYS, TEXT_YELLOW "!!! Remote CLI NOT support built in.");
  #endif
}



int crcb_cli_enter(const char *ins)
{
  if (*ins == '\r' || *ins == '\n')
  {
    return 0;
  }

  if ((*ins == '?') || (!strncmp("help", ins, 4)))
  {
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!! Reach Thunderboard demo, built %s, %s", __DATE__, __TIME__);
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!! App Version %s", get_app_version());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "Commands:", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  ver : Print versions", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  /   : Display status", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  lm (<new log mask>): Print current log mask, or set a new log mask", param_repo_get_cli_text_color());

    return 0;
  }

  crcb_set_command_line(ins);
  // step through remote_command_table and execute if matching
  if (!strncmp("ver", ins, 3))
    print_versions();
  else if (!strncmp("/", ins, 1))
    slash();
  else if (!strncmp("lm", ins, 2))
    lm(ins);
  else
    i3_log(LOG_MASK_WARN, "CLI command '%s' not recognized.", ins, *ins);
  return 0;
}

extern void app_get_num_reads(uint32_t *numReads);

static void slash(void)
{
  i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "Thunderboard Status:");

  // Reach information
  uint32_t numActive, numSent;
  uint32_t numReads;
  app_get_num_reads(&numReads);
  cr_get_notification_statistics(&numActive, &numSent);
  if (numActive == 0)
  {
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  No notifications are active. %u read%s since last check.", param_repo_get_cli_text_color(), numReads,
        numReads == 1 ? "" : "s");
  }
  else
  {
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  %u %s active.", param_repo_get_cli_text_color(), numActive, numActive > 1 ? "notifications are" : "notification is");
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  %u %s sent with %u read%s since last check.", param_repo_get_cli_text_color(), numSent,
        numSent != 1 ? "notifications were" : "notification was", numReads, numReads == 1 ? "" : "s");
  }
  i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  Current log mask: 0x%x", param_repo_get_cli_text_color(), i3_log_get_mask());
#ifdef ENABLE_REMOTE_CLI
  if (i3_log_get_remote_cli_enable())
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  Remote CLI support enabled.", param_repo_get_cli_text_color());
  else
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  Remote CLI support built but not enabled.", param_repo_get_cli_text_color());
#else
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  !!! Remote CLI NOT support built in.", param_repo_get_cli_text_color());
  #endif

  // System information
  bd_addr address;
  uint8_t address_type;
  sl_bt_system_get_identity_address(&address, &address_type);
  i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  BLE Device Address: %02X:%02X:%02X:%02X:%02X:%02X", param_repo_get_cli_text_color(), address.addr[5], address.addr[4],
      address.addr[3], address.addr[2], address.addr[1], address.addr[0]);
  i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  Uptime: %.3f seconds", param_repo_get_cli_text_color(), ((float) rsl_get_system_uptime()) / 1000);

  // NVM statistics
  i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  NVM3 Storage: %u/%u bytes remaining", param_repo_get_cli_text_color(), nvm3_defaultHandle->unusedNvmSize,
      nvm3_defaultHandle->nvmSize);
  size_t object_count = nvm3_countObjects(nvm3_defaultHandle);
  size_t deleted_object_count = nvm3_countDeletedObjects(nvm3_defaultHandle);
  i3_log(LOG_MASK_ALWAYS, TEXT_CLI "                %u object%s present, %u deleted object%s remaining in flash", param_repo_get_cli_text_color(), object_count,
      object_count == 1 ? "" : "s", deleted_object_count, deleted_object_count == 1 ? "" : "s");
  uint32_t erase_count = 0;
  int rval = (int) nvm3_getEraseCount(nvm3_defaultHandle, &erase_count);
  if (!rval)
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "                The most-used page of flash has been erased %u time%s", param_repo_get_cli_text_color(), erase_count,
        erase_count == 1 ? "" : "s");
  else
    i3_log(LOG_MASK_ERROR, "                Failed to get flash erase count, error 0x%x", rval);
}

static void lm(const char *input)
{
  uint32_t lm = 0;
  int args = sscanf(input, "lm %lx", &lm);
  if (args != 1)
  {
    lm = i3_log_get_mask();
    // Print current log mask
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "Current log mask: 0x%x", param_repo_get_cli_text_color(), lm);
#ifndef NO_REACH_LOGGING
    // print information about log mask
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  ALWAYS, ERROR and WARN are enabled", param_repo_get_cli_text_color());
    if (lm & LOG_MASK_WEAK)
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  mask 0x%x: WEAK is enabled", param_repo_get_cli_text_color(), LOG_MASK_WEAK);
    else
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    mask 0x%x: WEAK is disabled", param_repo_get_cli_text_color(), LOG_MASK_WEAK);
    if (lm & LOG_MASK_WIRE)
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  mask 0x%x: WIRE is enabled", param_repo_get_cli_text_color(), LOG_MASK_WIRE);
    else
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    mask 0x%x: WIRE is disabled", param_repo_get_cli_text_color(), LOG_MASK_WIRE);
    if (lm & LOG_MASK_REACH)
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  mask 0x%x: REACH is enabled", param_repo_get_cli_text_color(), LOG_MASK_REACH);
    else
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    mask 0x%x: REACH is disabled", param_repo_get_cli_text_color(), LOG_MASK_REACH);
    if (lm & LOG_MASK_PARAMS)
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  mask 0x%x: PARAMS is enabled", param_repo_get_cli_text_color(), LOG_MASK_PARAMS);
    else
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    mask 0x%x: PARAMS is disabled", param_repo_get_cli_text_color(), LOG_MASK_PARAMS);
    if (lm & LOG_MASK_FILES)
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  mask 0x%x: FILES is enabled", param_repo_get_cli_text_color(), LOG_MASK_FILES);
    else
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    mask 0x%x: FILES is disabled", param_repo_get_cli_text_color(), LOG_MASK_FILES);
    if (lm & LOG_MASK_BLE)
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  mask 0x%x: BLE is enabled", param_repo_get_cli_text_color(), LOG_MASK_BLE);
    else
      i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    mask 0x%x: BLE is disabled", param_repo_get_cli_text_color(), LOG_MASK_BLE);
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "  Other Valid log masks:", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    LOG_MASK_ACME               0x4000", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    LOG_MASK_DEBUG              0x8000", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    LOG_MASK_TIMEOUT           0x10000", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    LOG_MASK_DATASTREAM_DEBUG 0x100000", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    LOG_MASK_ZIGBEE_DEBUG     0x200000", param_repo_get_cli_text_color());
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "    LOG_MASK_ZIGBEE_OTA_DEBUG 0x400000", param_repo_get_cli_text_color());
#else
        // Logging is typically disabled to save space, so don't waste it with a bunch of printouts
        i3_log(LOG_MASK_WARN, TEXT_CLI "Log mask is of limited use, as logging is disabled", param_repo_get_cli_text_color());
#endif
  }
  else
  {
    i3_log_set_mask(lm);
    i3_log(LOG_MASK_ALWAYS, TEXT_CLI "The log mask is now 0x%x", param_repo_get_cli_text_color(), lm);
#ifdef NO_REACH_LOGGING
        i3_log(LOG_MASK_WARN, TEXT_CLI "Log mask is of limited use, as logging is disabled", param_repo_get_cli_text_color());
#endif
  }
}
