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
 ******************************************************************************/

/**
 * @file      app.c
 * @brief     A version of this file is generated by the SiLabs tools. To 
 *            facilitate code reuse in projects derived from Reach, this file is
 *            practically empty, instead calling the Reach SiLabs versions of
 *            these functions. Feel free to add your own application specific
 *            things here, or consider whether changes to the "standard"
 *            reach_silabs.c are appropriate.
 * 
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 */

#include "reach_silabs.h"
#include "cr_stack.h"
#include "sl_bluetooth.h"
#include "app.h"


/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void)
{
    unsigned int sn;
    int rval = rsl_read_serial_number(&sn);
    if (rval == 0) {
        char name[REACH_SHORT_STRING_LEN];
        snprintf(name, REACH_SHORT_STRING_LEN, "Reacher SN-%u", sn);
        cr_set_advertised_name(name, REACH_SHORT_STRING_LEN);
    }
    rsl_app_init();
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
    rsl_app_process_action();
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
    rsl_bt_on_event(evt);
}
