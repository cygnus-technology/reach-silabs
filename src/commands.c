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
 *                        Copyright i3 Product Development 2023-2024
 * 
 * \brief Provides the device info service to a Reach-enabled application.
 *
 ********************************************************************************************/

/**
 * @file      commands.c
 * @brief     An example of support for the command service in a Cygnus Reach 
 *            enabled device.  This file is part of the application and NOT part
 *            of the core stack.  Different applications can expose different
 *            command sets using their own implementation of the reach callback
 *            functions illustrated here. The crcb_ callback functions are
 *            documented in cr_weak.c.
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 * The Cygngus Reach firmware stack is shared under an MIT license.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "reach-server.h"  // configures Reach
#include "cr_stack.h"
#include "i3_log.h"
#include "reach_silabs.h"

#include "nvm3_default.h"

#ifdef INCLUDE_COMMAND_SERVICE
//*************************************************************************
//  Command Service
//*************************************************************************

#define NUM_COMMANDS    10

#define COMMAND_ENABLE_RCLI     1
#define COMMAND_DISABLE_RCLI    2
#define COMMAND_MIN_LOG         3
#define COMMAND_MAX_LOG         4
#define COMMAND_FACTORY         20

uint8_t sCommandIndex = 0;
const cr_CommandInfo sCommands[NUM_COMMANDS] = 
{
  #ifdef INCLUDE_CLI_SERVICE
    {COMMAND_ENABLE_RCLI,   "Enable remote CLI", true, "Enable the remote CLI", false, 0},
    {COMMAND_DISABLE_RCLI,  "Disable remote CLI", true, "Disable the remote CLI", false, 0},
  #endif  // def INCLUDE_CLI_SERVICE
    {COMMAND_MIN_LOG,       "Minimize Logging (lm 0)", true, "Minimize the log level", false, 0},
    {COMMAND_MAX_LOG,       "Much Logging (lm 7C0)", true, "Maximize the log level", false, 0},
    {COMMAND_FACTORY,       "Factory Reset", true, "Perform a factory reset", false, 0},     // erases NVM, restores serial number

    {6,       "Error Demo", true, "I've seen things you people wouldn't believe", true, 0},
    {7,       "Alice", true, "Attack ships on fire off the shoulder of Orion", true, 1000},
    {8,       "David 1", true, "", true, 65538},
    {9,       "David 2", false, "", false, 0},
    {10,      "Fake 10", true, "I'm a potato", false, 0}

    //    {47, "Trigger OTA"},        // example not implemented here.
    //    {99, "Board Reset"},        // example not implemented here.

};

int crcb_get_command_count()
{
    return NUM_COMMANDS;
}

int crcb_command_discover_next(cr_CommandInfo *cmd_desc)
{
    if (sCommandIndex >= NUM_COMMANDS)
    {
        I3_LOG(LOG_MASK_REACH, "%s: Command index %d indicates discovery complete.",
               __FUNCTION__, sCommandIndex);
        return cr_ErrorCodes_NO_DATA;
    }
    *cmd_desc = sCommands[sCommandIndex++];
    return 0;
}

int crcb_command_discover_reset(const uint32_t cid)
{
    if (cid >= NUM_COMMANDS)
    {
        i3_log(LOG_MASK_ERROR, "%s: Command ID %d does not exist.",
               __FUNCTION__, cid);
        return cr_ErrorCodes_INVALID_PARAMETER;
    }
    sCommandIndex = cid;
    return 0;
}

// actually execute the command
int crcb_command_execute(const uint8_t cid)
{
    for (int i=0; i< NUM_COMMANDS; i++)
    {
        if (cid == sCommands[i].id)
        {
            i3_log(LOG_MASK_ALWAYS, "Execute command %d, '%s'", 
                   sCommands[i].id, sCommands[i].name);
            switch (cid) {
          #ifdef INCLUDE_CLI_SERVICE
            case COMMAND_ENABLE_RCLI:  // 1
                i3_log_set_remote_cli_enable(true);
                break;
            case COMMAND_DISABLE_RCLI:  // 2
                i3_log_set_remote_cli_enable(false);
                break;
          #endif  // def INCLUDE_CLI_SERVICE
            case COMMAND_MIN_LOG:  // 3
                i3_log_set_mask(0);
                break;
            case COMMAND_MAX_LOG:  // 4
                i3_log_set_mask(DEFAULT_LOG_MASK);
                break;
            case COMMAND_FACTORY:
            {
                unsigned int sn;
                int has_sn = !rsl_read_serial_number(&sn);
                Ecode_t eCode = nvm3_eraseAll(nvm3_defaultHandle);
                i3_log(LOG_MASK_ALWAYS, "nvm3_eraseAll() returned 0x%x", eCode);
                extern void init_param_repo();
                eCode = nvm3_eraseAll(nvm3_defaultHandle);
                i3_log(LOG_MASK_ALWAYS, "nvm3_eraseAll() returned 0x%x", eCode);
                init_param_repo();
                if (has_sn) {
                    nvm3_writeData(nvm3_defaultHandle, REACH_SN_KEY, (uint8_t *)&sn, sizeof(unsigned int));
                    i3_log(LOG_MASK_ALWAYS, "Serial number restored as %d.", sn);
                }
                break;
            }
            case 6:
                LOG_ERROR("Command 6 triggers an error for testing.");
                cr_report_error(6, "(demonstration) The message reported by cr_report_error() "
                                   "can be up to 180 characters long.\n");
                break;
            case 7:
                LOG_ERROR("Command 7 triggers an error for testing.");
                cr_report_error(7, "Why, sometimes I've believed as many as six "
                                   "impossible things before breakfast.\n");
                break;
            case 8:
                LOG_ERROR("Command 8 triggers an error for testing.");
                cr_report_error(8, "I'm looking for backing for an unauthorized "
                                   "auto-biography that I am writing.\n");
                break;
            case 9:
                LOG_ERROR("Command 9 triggers an error for testing.");
                cr_report_error(9, "Hopefully, this will sell in such huge numbers "
                                   "that I will be able to sue myself for an "
                                   "extraordinary amount of money and finance "
                                   "the film version in which I will play everybody.\n");
            case 10:
                LOG_ERROR("Command 10 triggers an error for testing.");
                cr_report_error(9, "Is that all there is?\n");
                break;
            default:
                i3_log(LOG_MASK_ALWAYS, "Command %d not implemented.", cid);
                break;
            }
            return 0;
        }
    }
    i3_log(LOG_MASK_ERROR, "%s: Command ID %d not found.",
           __FUNCTION__, cid);
    return cr_ErrorCodes_INVALID_PARAMETER;
}

#endif  // def INCLUDE_COMNMAND_SERVICE
