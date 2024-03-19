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
 *                       Copyright i3 Product Development 2023-2024
 *
 * \brief Provides the time service to a Reach-enabled application.
 *
 ********************************************************************************************/


#include "reach-server.h"  // determines configuration
#ifdef INCLUDE_TIME_SERVICE

    #include <stdio.h>
    #include <string.h>
    #include <assert.h>
    #include "cr_stack.h"
    #include "i3_log.h"

    static int64_t sTime_refSeconds = 0;
    static int64_t sTime_matchingTicks = 0;
    static bool sHasTimezone = false;
    static int32_t sTimezone = 0;

    // Time is specified in UTC Epoch format, seconds since 1970.
    // More than 32 bits are required to remain valid past 2030.
    // Matching Linux, negative times are allowed for old dates.
    // This interface is intended to set the current time as UTC 
    // plus timezone offset.  Typically the client will consult 
    // a known accurate clock to fill in the time and zone.

    int crcb_time_get(cr_TimeGetResponse *response)
    {
        int64_t curSecs = cr_get_current_ticks()/SYS_TICK_RATE;

        response->seconds_utc = sTime_refSeconds + curSecs 
                - (sTime_matchingTicks/SYS_TICK_RATE);
        response->has_timezone = sHasTimezone;
        response->timezone = sTimezone;
        response->result_message[0] = 0;

        if (sHasTimezone) {
            I3_LOG(LOG_MASK_ALWAYS, "%s: Return %lu seconds, with zone %d.", 
                   __FUNCTION__, response->seconds_utc, response->timezone);
            return 0;
        }
        I3_LOG(LOG_MASK_ALWAYS, "%s: Return %lu seconds, no timezone.", 
               __FUNCTION__, response->seconds_utc);
        return 0;
    }

    int crcb_time_set(const cr_TimeSetRequest *request)
    {
        sTime_refSeconds = request->seconds_utc;
        sTime_matchingTicks = cr_get_current_ticks();
        sHasTimezone        = request->has_timezone;
        sTimezone = request->timezone;
        if (sHasTimezone) {
            I3_LOG(LOG_MASK_ALWAYS, "%s: Set %lu seconds = %u ticks, with zone %d.", 
                   __FUNCTION__, sTime_refSeconds, sTime_matchingTicks, sTimezone);
            return 0;
        }
        I3_LOG(LOG_MASK_ALWAYS, "%s: Set %lu seconds = %u ticks, no timezone", 
               __FUNCTION__, request->seconds_utc, sTime_matchingTicks);

        // An app might not want to zero this local copy of the timezone.
        // An app might wish to implement a more complicated understanding
        // of reading and writing time and timezones.
        sTimezone = 0;
        return 0;
    }


#endif // def INCLUDE_TIME_SERVICE
