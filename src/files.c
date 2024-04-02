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
 *                          Copyright i3 Product Development 2023
 * 
 * \brief Provides the files service to a Reach-enabled application.
 *
 ********************************************************************************************/


/**
 * @file      files.c
 * @brief     An example of support for the file service in a Cygnus Reach 
 *            enabled device.  This file is part of the application and NOT part
 *            of the core stack.  Different applications can expose different
 *            file sets using their own implementation of the reach callback
 *            functions illustrated here.  The crcb_ callback functions are
 *            documented in cr_weak.c.
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 * The Cygngus Reach firmware stack is shared under an MIT license.
 */

#include "reach-server.h"  // configures Reach

#ifdef INCLUDE_FILE_SERVICE
    #include <stdio.h>
    #include <string.h>
    #include <assert.h>

    #include "cr_stack.h"
    #include "i3_log.h"

    #define NUM_FILES   3
    static const cr_FileInfo sFiles[NUM_FILES] =
    {
        {
            0,                              // int32_t file_id
            "log_file.csv",                 // char file_name[24]
            cr_AccessLevel_READ,            // cr_AccessLevel access (Read / Write)
            4000,                           // size in bytes
            cr_StorageLocation_RAM,         // cr_StorageLocation storage_location
            false                           // requires checksum
        },
        {
            1,                              // int32_t file_id
            "ota.bin",                      // char file_name[24]
            cr_AccessLevel_READ_WRITE,      // cr_AccessLevel access (Read / Write)
            50000,                          // size in bytes
            cr_StorageLocation_NONVOLATILE, // cr_StorageLocation storage_location
            false                           // requires checksum
        },
        {
            2,                              // int32_t file_id
            "cs_test.bin",                  // char file_name[24]
            cr_AccessLevel_READ_WRITE,      // cr_AccessLevel access (Read / Write)
            2000,                           // size in bytes
            cr_StorageLocation_RAM,         // cr_StorageLocation storage_location
            true                            // requires checksum
        }
    };

    static int sCrFileLineNum = 0;

    int crcb_file_get_description(uint32_t fid, cr_FileInfo *file_desc)
    {
        // This construct assumes that fid's are contiguous with the fid 
        // matching the index.  More complicated constructions could allow 
        // for non-contiguous file ID's.

        if (fid >= NUM_FILES)
            return cr_ErrorCodes_BAD_FILE;

        *file_desc = sFiles[fid];
        return 0;
    }

    // The "ack_rate" determines how many packets are transmitted 
    // before an acknowledgement is required. 
    // The ack rate is determined by the communication method and 
    // it's not generally different from file to file.
    // The ack rate might be low if the application expects transmission errors.
    // A higher ack rate makes for faster transmission.
    // A lower ack rate allows for faster error recovery.
    // The client specifies its preferred ack rate as "requested_ack_rate" 
    // in the FileTransferRequest message.
    // A "real" application would probably return a high number here in order 
    // to guarantee a high transfer rate.  Here we return the requested rate 
    // so that you can use the client to experiment with ack rates.
    int crcb_file_get_preferred_ack_rate(uint32_t fid, uint32_t requested_rate, bool is_write)
    {
        if (0 != i3_log_get_mask()) {
            i3_log(LOG_MASK_WARN, "Logging can interfere with file write.");
        }
        (void)is_write;
        (void)fid;
        return requested_rate;
    }

    int crcb_file_get_file_count()
    {
        return NUM_FILES;
    }

    static uint8_t sFid_index = 0;
    int crcb_file_discover_reset(const uint8_t fid)
    {
        if (fid >= NUM_FILES)
        {
            i3_log(LOG_MASK_ERROR, "crcb_file_discover_reset(%d): invalid FID, using 0.", fid);
            sFid_index = 0;
            return 0;
        }
        sFid_index = fid;
        return 0;
    }

    int crcb_file_discover_next(cr_FileInfo *file_desc)
    {
        if (sFid_index >= NUM_FILES)
        {
            i3_log(LOG_MASK_FILES, "%s: sFid_index (%d) >= NUM_FILES (%d)",
                   __FUNCTION__, sFid_index, NUM_FILES);
            return cr_ErrorCodes_BAD_FILE;
        }
        *file_desc = sFiles[sFid_index];
        sFid_index++;
        return 0;
    }

    // Attempts to read the specified file.
    // returns zero or an error code.
    // In this example the "file" is a synthetic thing that just returns increasing numbers.
    // A real application would provide real data by whatever means is appropriate.
    int crcb_read_file(const uint32_t fid,          // which file
                     const int offset,              // offset, negative value specifies current location.
                     const size_t bytes_requested,  // how many bytes to read
                     uint8_t *pData,                // where the data goes
                     int *bytes_read)               // bytes actually read, negative for errors.
    {
        if (fid >= NUM_FILES)
        {
            i3_log(LOG_MASK_ERROR, "%s: File ID %d does not exist.", __FUNCTION__, fid);
            return cr_ErrorCodes_BAD_FILE;
        }
        if (bytes_requested > REACH_BYTES_IN_A_FILE_PACKET)
        {
            i3_log(LOG_MASK_ERROR, "%s: %d is more than the buffer for a file read (%d).",
                   __FUNCTION__, fid, REACH_BYTES_IN_A_FILE_PACKET);
            return cr_ErrorCodes_BUFFER_TOO_SMALL;
        }

        switch (fid) {
        case 0:  // "log_file.csv"
          {
            if (offset == 0 ) 
                sCrFileLineNum = 0;

            unsigned int totalPrinted = 0;
            unsigned int numPrinted = 0;
            while (totalPrinted < bytes_requested) {
                unsigned int limit = bytes_requested - totalPrinted;
                if (limit < 48)
                {   // fill with spaces
                    memset(pData, ' ', limit);
                    break;
                }
                snprintf((char*)pData, limit, "%4d, line, 0x%04X, %5u, %5u, %5u, %5u,\n",
                         ++sCrFileLineNum, 0xFFFF & rand(), 0xFFFF & rand(), 
                         0xFFFF & rand(),  0xFFFF & rand(), 0xFFFF & rand());
                numPrinted = strlen((char*)pData);
                totalPrinted += numPrinted;
                // i3_log(LOG_MASK_ALWAYS, "%d, %d, %d: '%s'", limit, numPrinted, totalPrinted, pData);
                pData += numPrinted;
            }
            *bytes_read = bytes_requested;
            return 0;
          }
        case 1:  // ota.bin
        case 2:
            // copy some code into the buffer
            memcpy(pData, (void*)&crcb_file_get_description, bytes_requested);
            *bytes_read = bytes_requested;
            return 0;

        default:
            affirm(false);  
            break;
        }
        *bytes_read = bytes_requested;
        return 0;
    }

    // returns zero or an error code
    // In this example the received data is not stored.
    // A real application can store the data as appropriate.
    int crcb_write_file(const uint32_t fid, // which file
                     const int offset,      // offset, negative value specifies current location.
                     const size_t bytes,    // how many bytes to write
                     const uint8_t *pData)  // where to get the data from
    {
        (void)offset;
        (void)bytes;
        (void)pData;

        if (fid >= NUM_FILES)
        {
            i3_log(LOG_MASK_ERROR, "%s: File ID %d does not exist.",
                   __FUNCTION__, fid);
            return cr_ErrorCodes_BAD_FILE;
        }

        if (fid == 0)
        {
            i3_log(LOG_MASK_ERROR, "%s: File ID %d has no write permission.",
                   __FUNCTION__, fid);
            return cr_ErrorCodes_PERMISSION_DENIED;
        }

        // the received data is not stored anywhere.
        // 
        // LOG_DUMP_MASK(LOG_MASK_FILES, "Received File Data", pData, bytes);
        return 0;
    }

    // returns zero or an error code
    int crcb_erase_file(const uint32_t fid)
    {
        if (fid >= NUM_FILES)
        {
            i3_log(LOG_MASK_ERROR, "%s: File ID %d does not exist.",
                   __FUNCTION__, fid);
            return cr_ErrorCodes_BAD_FILE;
        }

        if (fid == 0)
        {
            i3_log(LOG_MASK_ERROR, "%s: File ID %d has no write permission.",
                   __FUNCTION__, fid);
            return cr_ErrorCodes_PERMISSION_DENIED;
        }
        I3_LOG(LOG_MASK_FILES, "Fake file erase of file %d.", fid);
        return 0;
    }

#endif  // def INCLUDE_FILE_SERVICE
