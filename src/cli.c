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
 * \brief A minimal command-line interface implementation
 *
 * Original Author: Chuck Peplinski
 * Script Authors: Joseph Peplinski and Andrew Carlson
 *
 * Generated with version 1.0.0 of the C code generator
 *
 ********************************************************************************************/

/********************************************************************************************
 ************************************     Includes     *************************************
 *******************************************************************************************/

#include "cli.h"
#include "cr_stack.h"
#include "i3_log.h"

/* User code start [cli.c: User Includes] */

#include "sl_gsdk_version.h"
#include "sl_iostream.h"
#include "sl_iostream_handles.h"
#include "nvm3_generic.h"
#include "reach_silabs.h"
#include "app_version.h"

/* User code end [cli.c: User Includes] */

/********************************************************************************************
 *************************************     Defines     **************************************
 *******************************************************************************************/

/* User code start [cli.c: User Defines] */
/* User code end [cli.c: User Defines] */

/********************************************************************************************
 ***********************************     Data Types     ************************************
 *******************************************************************************************/

/* User code start [cli.c: User Data Types] */
/* User code end [cli.c: User Data Types] */

/********************************************************************************************
 ********************************     Global Variables     *********************************
 *******************************************************************************************/

/* User code start [cli.c: User Global Variables] */
/* User code end [cli.c: User Global Variables] */

/********************************************************************************************
 *****************************     Local/Extern Variables     ******************************
 *******************************************************************************************/

static char input[64];
static uint8_t input_length = 0;

/* User code start [cli.c: User Local/Extern Variables] */

static sl_iostream_t *handle;

/* User code end [cli.c: User Local/Extern Variables] */

/********************************************************************************************
 ***************************     Local Function Declarations     ****************************
 *******************************************************************************************/

static void cli_write_prompt(void);
static void cli_write(char *text);
static void cli_write_char(char c);
static bool cli_read_char(char *received);

/* User code start [cli.c: User Local Function Declarations] */

extern void app_get_num_reads(uint32_t *numReads);
static void print_versions(void);
static void slash(void);
static void lm(const char *input);

/* User code end [cli.c: User Local Function Declarations] */

/********************************************************************************************
 ********************************     Global Functions     *********************************
 *******************************************************************************************/

void cli_init(void)
{
  /* User code start [CLI: Init] */

  handle = sl_iostream_get_handle("vcom");
  // Clear the screen
  cli_write("\033[2J\033]H");
  print_versions();

  /* User code end [CLI: Init] */
  cli_write_prompt();
}

bool cli_poll(void)
{
  if (input_length == sizeof(input))
  {
    i3_log(LOG_MASK_WARN, "CLI input too long, clearing");
    memset(input, 0, sizeof(input));
    input_length = 0;
    cli_write_prompt();
  }
  if (cli_read_char(&input[input_length]))
  {
    switch (input[input_length])
    {
      case '\r':
        cli_write("\r\n");
        if (input_length == 0)
        {
          cli_write_prompt();
          break; // No data, no need to call anything
        }
        input[input_length] = 0; // Null-terminate the string
        crcb_cli_enter((const char*) input);
        input_length = 0;
        memset(input, 0, sizeof(input));
        cli_write_prompt();
        break;
      case '\n':
        break; // Ignore, only expect '\r' for command execution
      case '\b':
        // Received a backspace
        if (input_length > 0)
        {
          input[--input_length] = 0;
          cli_write("\b \b");
        }
        break;
      default:
        // Still waiting for an input
        cli_write_char(input[input_length]);
        if (input_length < sizeof(input))
          input_length++;
        break;
    }
  return true;
  }
  return false;
}

/* User code start [cli.c: User Global Functions] */
/* User code end [cli.c: User Global Functions] */

/********************************************************************************************
 *************************     Cygnus Reach Callback Functions     **************************
 *******************************************************************************************/

int crcb_cli_enter(const char *ins)
{
  if (*ins == '\r' || *ins == '\n')
  {
    return 0;
  }

  if ((*ins == '?') || (!strncmp("help", ins, 4)))
    {
    i3_log(LOG_MASK_ALWAYS, "  ver: Print versions");
    i3_log(LOG_MASK_ALWAYS, "  /: Display status");
    i3_log(LOG_MASK_ALWAYS, "  lm (<new log mask>): Print current log mask, or set a new log mask");
    return 0;
  }

  crcb_set_command_line(ins);
  // step through remote_command_table and execute if matching
  if (!strncmp("ver", ins, 3))
  {
    /* User code start [CLI: 'ver' handler] */

	print_versions();

    /* User code end [CLI: 'ver' handler] */
  }
  else if (!strncmp("/", ins, 1))
  {
    /* User code start [CLI: '/' handler] */

	slash();

    /* User code end [CLI: '/' handler] */
  }
  else if (!strncmp("lm", ins, 2))
  {
    /* User code start [CLI: 'lm' handler] */

	lm(ins);

    /* User code end [CLI: 'lm' handler] */
  }
  /* User code start [CLI: Custom command handling] */
  /* User code end [CLI: Custom command handling] */
  else
    i3_log(LOG_MASK_WARN, "CLI command '%s' not recognized.", ins, *ins);
  return 0;
}

/* User code start [cli.c: User Cygnus Reach Callback Functions] */
/* User code end [cli.c: User Cygnus Reach Callback Functions] */

/********************************************************************************************
 *********************************     Local Functions     **********************************
 *******************************************************************************************/

static void cli_write_prompt(void)
{
  /* User code start [CLI: Write Prompt]
   * This is called after a command is sent and processed, indicating that the CLI is ready for a new prompt.
   * A typical implementation of this is to send a single '>' character. */

  cli_write_char('>');

  /* User code end [CLI: Write Prompt] */
}

static void cli_write(char *text)
{
  /* User code start [CLI: Write]
   * This is where other output sources should be handled (for example, writing to a UART port)
   * This is called for outputs which are not necessary via BLE, such as clearing lines or handling backspaces */

  sl_iostream_write(handle, text, strlen(text));

  /* User code end [CLI: Write] */
}

static void cli_write_char(char c)
{
  /* User code start [CLI: Write Char]
   * This is used to write single characters, which may be handled differently from longer strings. */

  sl_iostream_putchar(handle, c);

  /* User code end [CLI: Write Char] */
}

static bool cli_read_char(char *received)
{
  /* User code start [CLI: Read]
   * This is where other input sources (such as a UART) should be handled.
   * This should be non-blocking, and return true if a character was received, or false if not. */

  return !sl_iostream_getchar(handle, received);

  /* User code end [CLI: Read] */
}

/* User code start [cli.c: User Local Functions] */

static void print_versions(void)
{
  i3_log(LOG_MASK_ALWAYS, "!!! Reach Thunderboard demo, built %s, %s", __DATE__, __TIME__);
  i3_log(LOG_MASK_ALWAYS, "!!!   Silicon Labs Gecko SDK version %s", SL_GSDK_VERSION_STR);
  i3_log(LOG_MASK_ALWAYS, "!!!   Reach stack version %s", cr_get_reach_version());
  i3_log(LOG_MASK_ALWAYS, "!!!   Reach protobuf version %s", cr_get_proto_version());
  i3_log(LOG_MASK_ALWAYS, "!!!   App version %s", get_app_version());

#ifdef INCLUDE_CLI_SERVICE
  if (i3_log_get_remote_cli_enable())
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!! Remote CLI support enabled.");
  else
    i3_log(LOG_MASK_ALWAYS, TEXT_YELLOW "!!! Remote CLI support built but not enabled.");
#else
  i3_log(LOG_MASK_ALWAYS, TEXT_YELLOW "!!! Remote CLI NOT support built in.");
#endif
}

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
    i3_log(LOG_MASK_ALWAYS, "  No notifications are active. %u read%s since last check.", numReads,
        numReads == 1 ? "" : "s");
  }
  else
  {
    i3_log(LOG_MASK_ALWAYS, "  %u %s active.", numActive, numActive > 1 ? "notifications are" : "notification is");
    i3_log(LOG_MASK_ALWAYS, "  %u %s sent with %u read%s since last check.", numSent,
        numSent != 1 ? "notifications were" : "notification was", numReads, numReads == 1 ? "" : "s");
  }
  i3_log(LOG_MASK_ALWAYS, "  Current log mask: 0x%x", i3_log_get_mask());
#ifdef ENABLE_REMOTE_CLI
  if (i3_log_get_remote_cli_enable())
    i3_log(LOG_MASK_ALWAYS, "  Remote CLI support enabled.");
  else
    i3_log(LOG_MASK_ALWAYS, "  Remote CLI support built but not enabled.");
#else
    i3_log(LOG_MASK_ALWAYS, "  !!! Remote CLI NOT support built in.");
  #endif

  // System information
  bd_addr address;
  uint8_t address_type;
  sl_bt_system_get_identity_address(&address, &address_type);
  i3_log(LOG_MASK_ALWAYS, "  BLE Device Address: %02X:%02X:%02X:%02X:%02X:%02X", address.addr[5], address.addr[4],
      address.addr[3], address.addr[2], address.addr[1], address.addr[0]);
  i3_log(LOG_MASK_ALWAYS, "  Uptime: %.3f seconds", ((float) rsl_get_system_uptime()) / 1000);

  // NVM statistics
  i3_log(LOG_MASK_ALWAYS, "  NVM3 Storage: %u/%u bytes remaining", nvm3_defaultHandle->unusedNvmSize,
      nvm3_defaultHandle->nvmSize);
  size_t object_count = nvm3_countObjects(nvm3_defaultHandle);
  size_t deleted_object_count = nvm3_countDeletedObjects(nvm3_defaultHandle);
  i3_log(LOG_MASK_ALWAYS, "                %u object%s present, %u deleted object%s remaining in flash", object_count,
      object_count == 1 ? "" : "s", deleted_object_count, deleted_object_count == 1 ? "" : "s");
  uint32_t erase_count = 0;
  int rval = (int) nvm3_getEraseCount(nvm3_defaultHandle, &erase_count);
  if (!rval)
    i3_log(LOG_MASK_ALWAYS, "                The most-used page of flash has been erased %u time%s", erase_count,
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
    i3_log(LOG_MASK_ALWAYS, "Current log mask: 0x%x", lm);
#ifndef NO_REACH_LOGGING
    // print information about log mask
    i3_log(LOG_MASK_ALWAYS, "  ALWAYS, ERROR and WARN are enabled");
    if (lm & LOG_MASK_WEAK)
      i3_log(LOG_MASK_ALWAYS, "  mask 0x%x: WEAK is enabled", LOG_MASK_WEAK);
    else
      i3_log(LOG_MASK_ALWAYS, "    mask 0x%x: WEAK is disabled", LOG_MASK_WEAK);
    if (lm & LOG_MASK_WIRE)
      i3_log(LOG_MASK_ALWAYS, "  mask 0x%x: WIRE is enabled", LOG_MASK_WIRE);
    else
      i3_log(LOG_MASK_ALWAYS, "    mask 0x%x: WIRE is disabled", LOG_MASK_WIRE);
    if (lm & LOG_MASK_REACH)
      i3_log(LOG_MASK_ALWAYS, "  mask 0x%x: REACH is enabled", LOG_MASK_REACH);
    else
      i3_log(LOG_MASK_ALWAYS, "    mask 0x%x: REACH is disabled", LOG_MASK_REACH);
    if (lm & LOG_MASK_PARAMS)
      i3_log(LOG_MASK_ALWAYS, "  mask 0x%x: PARAMS is enabled", LOG_MASK_PARAMS);
    else
      i3_log(LOG_MASK_ALWAYS, "    mask 0x%x: PARAMS is disabled", LOG_MASK_PARAMS);
    if (lm & LOG_MASK_FILES)
      i3_log(LOG_MASK_ALWAYS, "  mask 0x%x: FILES is enabled", LOG_MASK_FILES);
    else
      i3_log(LOG_MASK_ALWAYS, "    mask 0x%x: FILES is disabled", LOG_MASK_FILES);
    if (lm & LOG_MASK_BLE)
      i3_log(LOG_MASK_ALWAYS, "  mask 0x%x: BLE is enabled", LOG_MASK_BLE);
    else
      i3_log(LOG_MASK_ALWAYS, "    mask 0x%x: BLE is disabled", LOG_MASK_BLE);
    i3_log(LOG_MASK_ALWAYS, "  Other Valid log masks:");
    i3_log(LOG_MASK_ALWAYS, "    LOG_MASK_ACME               0x4000");
    i3_log(LOG_MASK_ALWAYS, "    LOG_MASK_DEBUG              0x8000");
    i3_log(LOG_MASK_ALWAYS, "    LOG_MASK_TIMEOUT           0x10000");
#else
        // Logging is typically disabled to save space, so don't waste it with a bunch of printouts
        i3_log(LOG_MASK_WARN, "Log mask is of limited use, as logging is disabled");
#endif
  }
  else
  {
    i3_log_set_mask(lm);
    i3_log(LOG_MASK_ALWAYS, "The log mask is now 0x%x", lm);
#ifdef NO_REACH_LOGGING
        i3_log(LOG_MASK_WARN, "Log mask is of limited use, as logging is disabled");
#endif
  }
}

/* User code end [cli.c: User Local Functions] */

