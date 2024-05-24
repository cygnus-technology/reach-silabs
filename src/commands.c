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
 * \brief A minimal implementation of command discovery and handling
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

#include "commands.h"
#include <stdint.h>
#include "cr_stack.h"
#include "i3_log.h"

/* User code start [commands.c: User Includes] */

#include "files.h"
#include "parameters.h"
#include "reach_silabs.h"

/* User code end [commands.c: User Includes] */

/********************************************************************************************
 *************************************     Defines     **************************************
 *******************************************************************************************/

/* User code start [commands.c: User Defines] */
/* User code end [commands.c: User Defines] */

/********************************************************************************************
 ***********************************     Data Types     ************************************
 *******************************************************************************************/

/* User code start [commands.c: User Data Types] */

typedef enum
{
  SEQUENCE_AUTOBIOGRAPHY,
  SEQUENCE_REDESIGN_YOUR_LOGO,
  SEQUENCE_SAY_HELLO,
  SEQUENCE_INACTIVE = 0xFF
} sequence_t;

/* User code end [commands.c: User Data Types] */

/********************************************************************************************
 ********************************     Global Variables     *********************************
 *******************************************************************************************/

/* User code start [commands.c: User Global Variables] */
/* User code end [commands.c: User Global Variables] */

/********************************************************************************************
 *****************************     Local/Extern Variables     ******************************
 *******************************************************************************************/

static int sCommandIndex = 0;
static const cr_CommandInfo command_desc[] = {
    {
        .id = COMMAND_RESET_DEFAULTS,
        .name = "Reset Defaults",
        .has_description = true,
        .description = "Restore factory values."
    },
    {
        .id = COMMAND_CLICK_FOR_WISDOM,
        .name = "Click for Wisdom",
        .has_description = true,
        .description = "Press it and find out"
    },
    {
        .id = COMMAND_NO_LOGGING,
        .name = "No logging",
        .has_description = true,
        .description = "lm 0"
    },
    {
        .id = COMMAND_MUCH_LOGGING,
        .name = "Much logging",
        .has_description = true,
        .description = "lm 1c7"
    },
    {
        .id = COMMAND_NOTIFICATIONS_ON,
        .name = "Notifications On",
        .has_description = true,
        .description = "Enable notifications on changes"
    },
    {
        .id = COMMAND_NOTIFICATIONS_OFF,
        .name = "Notifications Off",
        .has_description = true,
        .description = "disable all notifications"
    },
    {
        .id = COMMAND_REMOTE_CLI_ON,
        .name = "Remote CLI On",
        .has_description = true,
        .description = "To interact remotely"
    },
    {
        .id = COMMAND_REMOTE_CLI_OFF,
        .name = "Remote CLI Off",
        .has_description = true,
        .description = "Avoids heavy communication load"
    }
};

/* User code start [commands.c: User Local/Extern Variables] */

static uint32_t times_clicked = 0;
static uint8_t sequence_position = 0;
static sequence_t active_sequence = SEQUENCE_INACTIVE;

/* User code end [commands.c: User Local/Extern Variables] */

/********************************************************************************************
 ***************************     Local Function Declarations     ****************************
 *******************************************************************************************/

/* User code start [commands.c: User Local Function Declarations] */

int app_command_execute(const uint8_t cid);

/* User code end [commands.c: User Local Function Declarations] */

/********************************************************************************************
 ********************************     Global Functions     *********************************
 *******************************************************************************************/

/* User code start [commands.c: User Global Functions] */
/* User code end [commands.c: User Global Functions] */

/********************************************************************************************
 *************************     Cygnus Reach Callback Functions     **************************
 *******************************************************************************************/

int crcb_get_command_count()
{
    int i;
    int numAvailable = 0;
    for (i=0; i<NUM_COMMANDS; i++)
    {
        if (crcb_access_granted(cr_ServiceIds_COMMANDS, command_desc[i].id))
            numAvailable++;
    }
    return numAvailable;
}

int crcb_command_discover_next(cr_CommandInfo *cmd_desc)
{
    if (sCommandIndex >= NUM_COMMANDS)
    {
        I3_LOG(LOG_MASK_REACH, "%s: Command index %d indicates discovery complete.",
               __FUNCTION__, sCommandIndex);
        return cr_ErrorCodes_NO_DATA;
    }

    while (!crcb_access_granted(cr_ServiceIds_COMMANDS, command_desc[sCommandIndex].id))
    {
        I3_LOG(LOG_MASK_FILES, "%s: sCommandIndex (%d) skip, access not granted",
                   __FUNCTION__, sCommandIndex);
        sCommandIndex++;
        if (sCommandIndex >= NUM_COMMANDS)
        {
            I3_LOG(LOG_MASK_PARAMS, "%s: skipped to sCommandIndex (%d) >= NUM_COMMANDS (%d)",
                   __FUNCTION__, sCommandIndex, NUM_COMMANDS);
            return cr_ErrorCodes_NO_DATA;
        }
    }
    *cmd_desc = command_desc[sCommandIndex++];
    return 0;
}

int crcb_command_discover_reset(const uint32_t cid)
{
    if (cid >= NUM_COMMANDS)
    {
        i3_log(LOG_MASK_ERROR, "%s: Command ID %d does not exist.",
               __FUNCTION__, cid);
        return cr_ErrorCodes_INVALID_ID;
    }

    for (sCommandIndex = 0; sCommandIndex < NUM_COMMANDS; sCommandIndex++)
    {
        if (command_desc[sCommandIndex].id == cid) {
            if (!crcb_access_granted(cr_ServiceIds_COMMANDS, command_desc[sCommandIndex].id))
            {
                sCommandIndex = 0;
                break;
            }
            I3_LOG(LOG_MASK_PARAMS, "discover command reset (%d) reset to %d", cid, sCommandIndex);
            return 0;
        }
    }
    sCommandIndex = crcb_get_command_count();
    I3_LOG(LOG_MASK_PARAMS, "discover command reset (%d) reset defaults to %d", cid, sCommandIndex);
    return cr_ErrorCodes_INVALID_ID;
}

int crcb_command_execute(const uint8_t cid)
{
    int rval = 0;
    switch (cid)
    {
        /* User code start [Commands: Command Handler] */
        /* User code end [Commands: Command Handler] */
        default:
            rval = cr_ErrorCodes_INVALID_ID;
            break;
    }
    /* User code start [Commands: Command Handler Post-Switch] */

    rval = app_command_execute(cid);

    /* User code end [Commands: Command Handler Post-Switch] */
    return rval;
}

/* User code start [commands.c: User Cygnus Reach Callback Functions] */
/* User code end [commands.c: User Cygnus Reach Callback Functions] */

/********************************************************************************************
 *********************************     Local Functions     **********************************
 *******************************************************************************************/

/* User code start [commands.c: User Local Functions] */

int app_command_execute(const uint8_t cid)
{
  int rval = 0;
  switch (cid)
  {
    case COMMAND_RESET_DEFAULTS:
      rval = parameters_reset_nvm();
      if (rval != 0)
      {
        files_nvm_reset();
      }
      break;

    case COMMAND_NO_LOGGING:
      i3_log_set_mask(0);
      break;
    case COMMAND_MUCH_LOGGING:
      i3_log_set_mask(0x1C7);
      break;
    case COMMAND_NOTIFICATIONS_OFF:
      cr_clear_param_notifications();
      I3_LOG(LOG_MASK_ALWAYS, "Notifications are disabled.");
      break;
    case COMMAND_NOTIFICATIONS_ON:
      cr_init_param_notifications();
      I3_LOG(LOG_MASK_ALWAYS, "Notifications are installed.");
      break;

    case COMMAND_REMOTE_CLI_ON:
      i3_log_set_remote_cli_enable(true);
      break;
    case COMMAND_REMOTE_CLI_OFF:
      i3_log_set_remote_cli_enable(false);
      break;

    case COMMAND_CLICK_FOR_WISDOM:
    {
      I3_LOG(LOG_MASK_ALWAYS, TEXT_BOLDMAGENTA "Dispensing wisdom*...");
      I3_LOG(LOG_MASK_ALWAYS, TEXT_BOLDMAGENTA "* wisdom sometimes comes from unexpected places.  like maybe an error report?");
      if (times_clicked > 3)
      {
        int64_t time = rsl_get_system_uptime() / 100;
        if (active_sequence == SEQUENCE_INACTIVE)
        {
          // Activate an easter egg based on the uptime
          if (time % 10 == SEQUENCE_AUTOBIOGRAPHY)
            active_sequence = SEQUENCE_AUTOBIOGRAPHY;
          else if (time % 10 == SEQUENCE_REDESIGN_YOUR_LOGO)
            active_sequence = SEQUENCE_REDESIGN_YOUR_LOGO;
          else if (time % 10 == SEQUENCE_SAY_HELLO)
            active_sequence = SEQUENCE_SAY_HELLO;
        }
        if (active_sequence != SEQUENCE_INACTIVE)
        {
          // An easter egg has already been activated, continue that sequence until it is exhausted
          switch (active_sequence)
          {
            case SEQUENCE_AUTOBIOGRAPHY:
            {
              // A comment made during David Bowie's 50th birthday live chat on AOL (Source: https://www.bowiewonderworld.com/chats/dbchat0197.htm)
              switch (sequence_position)
              {
                case 0:
                  cr_report_error(1997, "I'm looking for backing for an unauthorized auto-biography that I am writing.");
                  break;
                default:
                  cr_report_error(1997, "Hopefully, this will sell in such huge numbers that I will be able to sue myself for an extraordinary amount of money "
                      "and finance the film version in which I will play everybody.");
                  sequence_position = 0;
                  active_sequence = SEQUENCE_INACTIVE;
                  break;
              }
              break;
            }
            case SEQUENCE_REDESIGN_YOUR_LOGO:
            {
              // Lyrics from "Redesign Your Logo" by Lemon Demon
              switch (sequence_position)
              {
                case 0:
                  cr_report_error(2016, "Redesign your logo, we know what we're doing.  We are here to help you; everything's connected");
                  break;
                case 1:
                  cr_report_error(2016, "Time is of the essence, we live in the future.  Color makes us hungry; everything's connected");
                  break;
                case 2:
                  cr_report_error(2016, "Redesign your logo, we know how to do it.  Make the calculations, put them into action");
                  break;
                default:
                  cr_report_error(2016, "We will find the angle, starting with convention.  On to innovation; everything's connected");
                  sequence_position = 0;
                  active_sequence = SEQUENCE_INACTIVE;
                  break;
              }
              break;
            }
            case SEQUENCE_SAY_HELLO:
            {
              // Lyrics from "Say Hello" by Laurie Anderson
              switch (sequence_position)
              {
                case 0:
                  cr_report_error(1984, "A certain American religious sect has been looking at conditions of the world during the Flood");
                  break;
                case 1:
                  cr_report_error(1984,
                      "According to their calculations, during the Flood the winds, tides and currents were in an overall southeasterly direction");
                  break;
                case 2:
                  cr_report_error(1984,
                      "This would mean that in order for Noah's Ark to have ended up on Mount Ararat, it would have to have started out several thousand miles to the west");
                  break;
                case 3:
                  cr_report_error(1984,
                      "This would then locate pre-Flood civilization in the area of Upstate New York, and the Garden of Eden roughly in New York City");
                  break;
                case 4:
                  cr_report_error(1984, "Now, in order to get from one place to another, something must move");
                  break;
                case 5:
                  cr_report_error(1984, "No one in New York remembers moving, and there are no traces of Biblical history in the Upstate New York area");
                  break;
                default:
                  cr_report_error(1984, "So we are led to the only available conclusion in this time warp, and that is that the Ark has simply not left yet");
                  sequence_position = 0;
                  active_sequence = SEQUENCE_INACTIVE;
                  break;
              }
              break;
            }
            default:
              break;
          }
          if (active_sequence != SEQUENCE_INACTIVE)
            sequence_position++;
          break;
        }
      }
      switch (times_clicked % 4)
      {
        case 0:
          cr_report_error(cr_ErrorCodes_NO_ERROR,
              "The message reported by cr_report_error() can be up to 180 characters long.  An error code of cr_ErrorCodes_NO_ERROR (%d) is displayed differently",
              cr_ErrorCodes_NO_ERROR);
          break;
        case 1:
          cr_report_error(cr_ErrorCodes_NO_DATA, "Informative error reporting code can often make it easy to locate the source of an error.  "
              "Large and layered systems often have no way to report errors up the chain.");
          break;
        case 2:
          cr_report_error(9999, "Reach offers a way to communicate errors from the device to the developer.  "
              "Calls to cr_report_errror() result in messages like this.  Error codes can be any integer value.");
          break;
        case 3:
          cr_report_error(3, "Is that all there is?");
          break;
      }
      times_clicked++;
      break;
    }
    default:
      // Unsupported command
      return cr_ErrorCodes_INVALID_ID;
  }
  if (rval)
  {
    i3_log(LOG_MASK_ERROR, "Failed to execute command %u, error %d", cid, rval);
    rval = cr_ErrorCodes_NO_DATA;
  }
  return rval;
}

/* User code end [commands.c: User Local Functions] */

