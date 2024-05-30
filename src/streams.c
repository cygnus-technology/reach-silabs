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
 * \brief A minimal implementation of stream discovery and access
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

#include "streams.h"
#include <stdint.h>
#include "cr_stack.h"
#include "i3_error.h"
#include "i3_log.h"

/* User code start [streams.c: User Includes] */
/* User code end [streams.c: User Includes] */

/********************************************************************************************
 *************************************     Defines     **************************************
 *******************************************************************************************/

/* User code start [streams.c: User Defines] */
/* User code end [streams.c: User Defines] */

/********************************************************************************************
 ***********************************     Data Types     ************************************
 *******************************************************************************************/

/* User code start [streams.c: User Data Types] */
/* User code end [streams.c: User Data Types] */

/********************************************************************************************
 ********************************     Global Variables     *********************************
 *******************************************************************************************/

/* User code start [streams.c: User Global Variables] */

static int sReadFrequencyCounter = 0;
#define STREAM_READ_FREQUENCY   100
static uint32_t sRollCount[NUM_STREAMS];

/* User code end [streams.c: User Global Variables] */

/********************************************************************************************
 *****************************     Local/Extern Variables     ******************************
 *******************************************************************************************/

static int sSid_index = 0;
static cr_StreamInfo stream_descriptions[] = {
    {
        .stream_id = STREAM_THING1_R,
        .name = "thing1-R",
        .description = "Read this stream",
        .access = cr_AccessLevel_READ
    },
    {
        .stream_id = STREAM_THING2_W,
        .name = "thing2-W",
        .description = "Write this stream",
        .access = cr_AccessLevel_WRITE
    }
};

/* User code start [streams.c: User Local/Extern Variables] */
/* User code end [streams.c: User Local/Extern Variables] */

/********************************************************************************************
 ***************************     Local Function Declarations     ****************************
 *******************************************************************************************/

static int sFindIndexFromSid(uint32_t sid, uint8_t *index);

/* User code start [streams.c: User Local Function Declarations] */
/* User code end [streams.c: User Local Function Declarations] */

/********************************************************************************************
 ********************************     Global Functions     *********************************
 *******************************************************************************************/

/* User code start [streams.c: User Global Functions] */
/* User code end [streams.c: User Global Functions] */

/********************************************************************************************
 *************************     Cygnus Reach Callback Functions     **************************
 *******************************************************************************************/

int crcb_stream_get_count()
{
    int i;
    int numAvailable = 0;
    for (i = 0; i < NUM_STREAMS; i++)
    {
        if (crcb_access_granted(cr_ServiceIds_STREAMS, stream_descriptions[i].stream_id)) numAvailable++;
    }
    return numAvailable;
}

int crcb_stream_discover_reset(const uint8_t sid)
{
    int rval = 0;
    uint8_t idx;
    rval = sFindIndexFromSid(sid, &idx);
    if (0 != rval)
    {
        I3_LOG(LOG_MASK_ERROR, "%s(%d): invalid SID, using NUM_STREAMS.", __FUNCTION__, sid);
        sSid_index = NUM_STREAMS;
        return cr_ErrorCodes_INVALID_ID;
    }
    if (!crcb_access_granted(cr_ServiceIds_FILES, stream_descriptions[sSid_index].stream_id))
    {
        I3_LOG(LOG_MASK_ERROR, "%s(%d): Access not granted, using NUM_STREAMS.", __FUNCTION__, sid);
        sSid_index = NUM_STREAMS;
        return cr_ErrorCodes_INVALID_ID;
    }
    sSid_index = idx;

    return 0;
}

int crcb_stream_discover_next(cr_StreamInfo *stream_desc)
{
    if (sSid_index >= NUM_STREAMS) // end of search
        return cr_ErrorCodes_NO_DATA;

    while (!crcb_access_granted(cr_ServiceIds_STREAMS, stream_descriptions[sSid_index].stream_id))
    {
        I3_LOG(LOG_MASK_WARN, "%s: sSid_index (%d) skip, access not granted",
               __FUNCTION__, sSid_index);
        sSid_index++;
        if (sSid_index >= NUM_STREAMS)
        {
            I3_LOG(LOG_MASK_WARN, "%s: skipped to sSid_index (%d) >= NUM_STREAMS (%d)",
                   __FUNCTION__, sSid_index, NUM_STREAMS);
            return cr_ErrorCodes_NO_DATA;
        }
    }
    *stream_desc = stream_descriptions[sSid_index++];
    return 0;
}

int crcb_stream_get_description(uint32_t sid, cr_StreamInfo *stream_desc)
{
    int rval = 0;
    affirm(stream_desc != NULL);
    uint8_t idx;
    rval = sFindIndexFromSid(sid, &idx);
    if (rval != 0) return rval;
    *stream_desc = stream_descriptions[idx];
    /* User code start [Streams: Get Description] */
    /* User code end [Streams: Get Description] */
    return 0;
}

int crcb_stream_read(uint32_t sid, cr_StreamData *data)
{
    int rval = cr_ErrorCodes_NO_DATA;
    affirm(data != NULL);
    uint8_t idx;
    rval = sFindIndexFromSid(sid, &idx);
    if (rval != 0) return cr_ErrorCodes_NO_DATA;

    /* User code start [Streams: Read] */

    if (sReadFrequencyCounter++ < STREAM_READ_FREQUENCY)
        return cr_ErrorCodes_NO_DATA;

    sReadFrequencyCounter = 0;
    // generate some fake data
    data->stream_id = sid;
    data->roll_count = sRollCount[idx]++;
    data->has_checksum = false;
    data->message_data.size = 10 + 10*(sRollCount[idx]%18);
    for (int i=0; i<data->message_data.size; i++ )
    {
        data->message_data.bytes[i] = 0xFF & (sRollCount[idx] + i);
    }

    int pvtCr_notify_stream(cr_StreamData *data);
    rval = pvtCr_notify_stream(data);
    if (rval)
        return cr_ErrorCodes_NO_DATA;

    I3_LOG(LOG_MASK_PARAMS, "%s: Generated %d bytes of stream data for stream %d.",
           __FUNCTION__, data->message_data.size, sid);

    return cr_ErrorCodes_NO_ERROR;

    /* User code end [Streams: Read] */
    // return cr_ErrorCodes_NO_ERROR;
}

int crcb_stream_write(uint32_t sid, cr_StreamData *data)
{
    int rval = 0;
    affirm(data != NULL);
    uint8_t idx;
    rval = sFindIndexFromSid(sid, &idx);
    if (rval != 0) return rval;

    /* User code start [Streams: Write] */

    // data flows to the device
    i3_log_dump_buffer(LOG_MASK_PARAMS, "Stream write data",
                       data->message_data.bytes, data->message_data.size);

    /* User code end [Streams: Write] */
    return 0;
}

int crcb_stream_open(uint32_t sid)
{
    int rval = 0;
    uint8_t idx;
    rval = sFindIndexFromSid(sid, &idx);
    if (rval != 0) return rval;

    /* User code start [Streams: Open] */

    sRollCount[idx] = 0;

    /* User code end [Streams: Open] */
    return 0;
}

int crcb_stream_close(uint32_t sid)
{
    int rval = 0;
    uint8_t idx;
    rval = sFindIndexFromSid(sid, &idx);
    if (rval != 0) return rval;

    /* User code start [Streams: Close] */
    /* User code end [Streams: Close] */
    return 0;
}

/* User code start [streams.c: User Cygnus Reach Callback Functions] */
/* User code end [streams.c: User Cygnus Reach Callback Functions] */

/********************************************************************************************
 *********************************     Local Functions     **********************************
 *******************************************************************************************/

static int sFindIndexFromSid(uint32_t sid, uint8_t *index)
{
    uint8_t idx;
    for (idx=0; idx<NUM_STREAMS; idx++) {
        if (stream_descriptions[idx].stream_id == sid) {
            *index = idx;
            return 0;
        }
    }
    return cr_ErrorCodes_INVALID_ID;
}

/* User code start [streams.c: User Local Functions] */
/* User code end [streams.c: User Local Functions] */

