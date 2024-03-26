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
 * \brief reach_app.c is a place holder for application specific functionality that is
 *        not part of the Reach core.
 *
 * Original Author: Chuck.Peplinski
 *
 ********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cr_stack.h"
#include "i3_log.h"
#include "app_version.h"
#include "reach_version.h"
#include "reach_silabs.h"

char sAppVersion[CR_STACK_VERSION_LEN];
const char *get_app_version()
{
  #ifdef DEV_BUILD
    snprintf(sAppVersion, CR_STACK_VERSION_LEN, "%u.%u.%u-676ah", 
             APP_MAJOR_VERSION, APP_MINOR_VERSION, APP_PATCH_VERSION);
  #else
    snprintf(sAppVersion, CR_STACK_VERSION_LEN, "%u.%u.%u", 
             APP_MAJOR_VERSION, APP_MINOR_VERSION, APP_PATCH_VERSION);
  #endif
    return sAppVersion;
}

// Change this to report appropriately about your applicaton.
void print_versions(sl_cli_command_arg_t *args)
{
    (void)args;
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!! Cygnus Reach Protobuf Server, built %s, %s", __DATE__, __TIME__);
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!!   App version %s", get_app_version() );
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!!   Reach C-stack version %s", cr_get_reach_version() );
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!!   Reach protobuf version %s", cr_get_proto_version());
    i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!! SiLabs Thunderboard hardware");

  #ifdef INCLUDE_CLI_SERVICE
    if (i3_log_get_remote_cli_enable())
        i3_log(LOG_MASK_ALWAYS, TEXT_GREEN "!!! Remote CLI support enabled.");
    else
        i3_log(LOG_MASK_ALWAYS, TEXT_YELLOW "!!! Remote CLI support built but not enabled.");
  #else
    i3_log(LOG_MASK_ALWAYS, TEXT_YELLOW "!!! Remote CLI NOT support built in.");
  #endif
}



