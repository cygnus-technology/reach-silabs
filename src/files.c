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
 * \brief A minimal implementation of file discovery and read/write handling
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

#include "files.h"
#include "i3_error.h"
#include "i3_log.h"

/* User code start [files.c: User Includes] */

#include "const_files.h"
#include "nvm3_generic.h"

/* User code end [files.c: User Includes] */

/********************************************************************************************
 *************************************     Defines     **************************************
 *******************************************************************************************/

/* User code start [files.c: User Defines] */

#define IO_TXT_KEY 0x1010
#define MAX_IO_TXT_LENGTH 2048

/* User code end [files.c: User Defines] */

/********************************************************************************************
 ***********************************     Data Types     ************************************
 *******************************************************************************************/

/* User code start [files.c: User Data Types] */
/* User code end [files.c: User Data Types] */

/********************************************************************************************
 ********************************     Global Variables     *********************************
 *******************************************************************************************/

cr_FileInfo file_descriptions[] = {
  {
    .file_id = FILE_IO_TXT,
    .file_name = "io.txt",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_NONVOLATILE,
    .require_checksum = false,
    .has_maximum_size_bytes = true,
    .maximum_size_bytes = 2048
  },
  {
    .file_id = FILE_CYGNUS_REACH_LOGO_PNG,
    .file_name = "cygnus-reach-logo.png",
    .access = cr_AccessLevel_READ,
    .storage_location = cr_StorageLocation_NONVOLATILE,
    .require_checksum = false,
    .has_maximum_size_bytes = true,
    .maximum_size_bytes = 17900
  },
  {
    .file_id = FILE_DEV_NULL,
    .file_name = "dev_null",
    .access = cr_AccessLevel_READ_WRITE,
    .storage_location = cr_StorageLocation_RAM,
    .require_checksum = false,
    .has_maximum_size_bytes = true,
    .maximum_size_bytes = 100000
  }
};

/* User code start [files.c: User Global Variables] */
/* User code end [files.c: User Global Variables] */

/********************************************************************************************
 *****************************     Local/Extern Variables     ******************************
 *******************************************************************************************/

static int sFid_index = 0;

/* User code start [files.c: User Local/Extern Variables] */

static char io_txt[MAX_IO_TXT_LENGTH];
static size_t io_txt_size = 0;

/* User code end [files.c: User Local/Extern Variables] */

/********************************************************************************************
 ***************************     Local Function Declarations     ****************************
 *******************************************************************************************/

static int sFindIndexFromFid(uint32_t fid, uint8_t *index);

/* User code start [files.c: User Local Function Declarations] */

void nvm_init(void);
void nvm_reset(void);

/* User code end [files.c: User Local Function Declarations] */

/********************************************************************************************
 ********************************     Global Functions     *********************************
 *******************************************************************************************/

void files_init(void)
{
  /* User code start [Files: Init] */

    size_t object_length;
    uint32_t type;
    int rval = (int) nvm3_getObjectInfo(nvm3_defaultHandle, IO_TXT_KEY, &type, &object_length);
    if (rval || type != NVM3_OBJECTTYPE_DATA)
    {
      I3_LOG(LOG_MASK_ERROR, "Failed to recover io.txt from flash, rewriting");
      memcpy(io_txt, default_io_txt, sizeof(default_io_txt));
      io_txt_size = sizeof(default_io_txt);
      rval = (int) nvm3_writeData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t *) io_txt, io_txt_size);
      if (rval)
        I3_LOG(LOG_MASK_ERROR, "Failed to rewrite default io.txt, error %d", rval);
    }
    else
    {
      // Data exists, try and get it
      rval = (int) nvm3_readData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t *) io_txt, object_length);
      if (rval)
      {
        I3_LOG(LOG_MASK_ERROR, "Failed to read io.txt from flash, error %d.  Attempting to rewrite.", rval);
        memcpy(io_txt, default_io_txt, sizeof(default_io_txt));
        io_txt_size = sizeof(default_io_txt);
        rval = (int) nvm3_writeData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t *) io_txt, io_txt_size);
        if (rval)
          I3_LOG(LOG_MASK_ERROR, "Failed to rewrite default io.txt, error %d", rval);
      }
      else
      {
        // Read io.txt contents successfully
        io_txt_size = object_length;
      }
    }
    file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;

  /* User code end [Files: Init] */
}

/* User code start [files.c: User Global Functions] */

void files_nvm_reset(void)
{
  memset(io_txt, 0, sizeof(io_txt));
  memcpy(io_txt, default_io_txt, sizeof(default_io_txt));
  io_txt_size = sizeof(default_io_txt);
  file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;
  int rval = (int) nvm3_writeData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t*) default_io_txt, sizeof(default_io_txt));
  if (rval != 0)
    I3_LOG(LOG_MASK_ERROR, "io.txt write failed, error %d", rval);
}

/* User code end [files.c: User Global Functions] */

/********************************************************************************************
 *************************     Cygnus Reach Callback Functions     **************************
 *******************************************************************************************/

int crcb_file_get_description(uint32_t fid, cr_FileInfo *file_desc)
{
  int rval = 0;
  affirm(file_desc != NULL);
  uint8_t idx;
  rval = sFindIndexFromFid(fid, &idx);
  if (rval != 0)
    return rval;

  /* User code start [Files: Get Description]
   * If the file description needs to be updated (for example, changing the current size), now's the time */
  /* User code end [Files: Get Description] */

  *file_desc = file_descriptions[idx];

  return 0;
}

int crcb_file_get_file_count()
{
  int i;
  int numAvailable = 0;
  for (i = 0; i < NUM_FILES; i++)
  {
    if (crcb_access_granted(cr_ServiceIds_FILES, file_descriptions[i].file_id)) numAvailable++;
  }
  return numAvailable;
}

int crcb_file_discover_reset(const uint8_t fid)
{
  int rval = 0;
  uint8_t idx;
  rval = sFindIndexFromFid(fid, &idx);
  if (0 != rval)
  {
    I3_LOG(LOG_MASK_ERROR, "%s(%d): invalid FID, using NUM_FILES.", __FUNCTION__, fid);
    sFid_index = NUM_FILES;
    return cr_ErrorCodes_INVALID_ID;
  }
  if (!crcb_access_granted(cr_ServiceIds_FILES, file_descriptions[sFid_index].file_id))
  {
    I3_LOG(LOG_MASK_ERROR, "%s(%d): Access not granted, using NUM_FILES.", __FUNCTION__, fid);
    sFid_index = NUM_FILES;
    return cr_ErrorCodes_BAD_FILE;
  }
  sFid_index = idx;
  return 0;
}

int crcb_file_discover_next(cr_FileInfo *file_desc)
{
  if (sFid_index >= NUM_FILES) // end of search
    return cr_ErrorCodes_NO_DATA;

  while (!crcb_access_granted(cr_ServiceIds_FILES, file_desc[sFid_index].file_id))
  {
    I3_LOG(LOG_MASK_FILES, "%s: sFid_index (%d) skip, access not granted",
         __FUNCTION__, sFid_index);
    sFid_index++;
    if (sFid_index >= NUM_FILES)
    {
      I3_LOG(LOG_MASK_PARAMS, "%s: skipped to sFid_index (%d) >= NUM_FILES (%d)", __FUNCTION__, sFid_index, NUM_FILES);
      return cr_ErrorCodes_NO_DATA;
    }
  }
  *file_desc = file_descriptions[sFid_index++];
  return 0;
}

int crcb_read_file(const uint32_t fid, const int offset, const size_t bytes_requested, uint8_t *pData, int *bytes_read)
{
  int rval = 0;
  uint8_t idx;
  rval = sFindIndexFromFid(fid, &idx);
  if (0 != rval)
  {
    I3_LOG(LOG_MASK_ERROR, "%s(%d): invalid FID.", __FUNCTION__, fid);
    return cr_ErrorCodes_INVALID_ID;
  }
  if (bytes_requested > REACH_BYTES_IN_A_FILE_PACKET)
  {
    I3_LOG(LOG_MASK_ERROR, "%s: %d is more than the buffer for a file read (%d).", __FUNCTION__, fid, REACH_BYTES_IN_A_FILE_PACKET);
    return cr_ErrorCodes_BUFFER_TOO_SMALL;
  }

  /* User code start [Files: Read]
   * The code generator does nothing to handle storing files, so this is where pData and bytes_read should be updated */

  switch (fid)
  {
    case FILE_IO_TXT:
      if (offset < 0 || offset >= (int) io_txt_size)
      {
        I3_LOG(LOG_MASK_ERROR, "io.txt read: Offset of %d is outside of the file size %d", offset, io_txt_size);
        return cr_ErrorCodes_READ_FAILED;
      }
      if (offset == 0)
      {
        // Update the local buffer of the file in case a write failed before this read
        int rval = (int) nvm3_readData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t*) io_txt, io_txt_size);
        if (rval != 0)
          I3_LOG(LOG_MASK_ERROR, "io.txt read failed, error %d", rval);
      }
      I3_LOG(LOG_MASK_FILES, "Read fid %u, offset %d, requested %d, size %d", fid, offset, bytes_requested, io_txt_size);
      if (offset > (int) io_txt_size)
      {
        I3_LOG(LOG_MASK_ERROR, "io.txt read: Offset of %d is greater than size of %d", offset, io_txt_size);
        return cr_ErrorCodes_READ_FAILED;
      }
      *bytes_read = ((offset + bytes_requested) > io_txt_size) ? (io_txt_size - offset) : bytes_requested;
      memcpy(pData, &io_txt[offset], (size_t) *bytes_read);
      break;

    case FILE_CYGNUS_REACH_LOGO_PNG:
      I3_LOG(LOG_MASK_FILES, "Read fid %u, offset %d, requested %d", fid, offset, bytes_requested);
      if (offset < 0 || offset >= (int) sizeof(cygnus_reach_logo))
      {
        I3_LOG(LOG_MASK_ERROR, "cygnus logo read: Offset of %d is outside of the file size %d", offset, sizeof(cygnus_reach_logo));
        return cr_ErrorCodes_READ_FAILED;
      }
      *bytes_read = ((offset + bytes_requested) > sizeof(cygnus_reach_logo)) ? (sizeof(cygnus_reach_logo) - offset) : bytes_requested;
      memcpy(pData, &cygnus_reach_logo[offset], (size_t) *bytes_read);
      break;
    case FILE_DEV_NULL:
      I3_LOG(LOG_MASK_FILES, "Read fid %u (dev/null), offset %d, requested %d", fid, offset, bytes_requested);
      *bytes_read = bytes_requested;
      break;
    default:
      i3_log(LOG_MASK_ERROR, "Invalid file read (ID %u)", fid);
      return cr_ErrorCodes_BAD_FILE;
  }

  /* User code end [Files: Read] */

  return rval;
}

int crcb_file_prepare_to_write(const uint32_t fid, const size_t offset, const size_t bytes)
{
  int rval = 0;
  uint8_t idx;
  rval = sFindIndexFromFid(fid, &idx);
  if (0 != rval)
  {
    I3_LOG(LOG_MASK_ERROR, "%s(%d): invalid FID.", __FUNCTION__, fid);
    return cr_ErrorCodes_INVALID_ID;
  }
  /* User code start [Files: Pre-Write]
   * This is the opportunity to prepare for a file write, or to reject it. */

  switch (fid)
  {
    case FILE_IO_TXT:
      // Partial writes are currently not supported by this demo
      if (offset != 0)
        return cr_ErrorCodes_INVALID_PARAMETER;
      if (offset + bytes > sizeof(io_txt))
        return cr_ErrorCodes_BUFFER_TOO_SMALL;
      memset(&io_txt[offset], 0, bytes);
      io_txt_size = bytes + offset;
      break;

    case FILE_DEV_NULL:
      break;

    default:
      return cr_ErrorCodes_BAD_FILE;
  }

  /* User code end [Files: Pre-Write] */
  return 0;
}

int crcb_write_file(const uint32_t fid, const int offset, const size_t bytes, const uint8_t *pData)
{
  int rval = 0;
  uint8_t idx;
  rval = sFindIndexFromFid(fid, &idx);
  if (0 != rval)
  {
    I3_LOG(LOG_MASK_ERROR, "%s(%d): invalid FID.", __FUNCTION__, fid);
    return cr_ErrorCodes_INVALID_ID;
  }
  /* User code start [Files: Write]
   * Here is where the received data should be copied to wherever the application is storing it */

  switch (fid)
  {
    case FILE_IO_TXT:
      if (offset < 0 || offset + bytes > io_txt_size)
      {
        I3_LOG(LOG_MASK_ERROR, "io.txt write failed outside of limited size, error %d", cr_ErrorCodes_WRITE_FAILED);
        return cr_ErrorCodes_WRITE_FAILED;
      }
      memcpy(&io_txt[offset], pData, bytes);
      break;
    case FILE_DEV_NULL:
      I3_LOG(LOG_MASK_FILES, "Write fid %u (dev/null), offset %d, bytes %d", fid, offset, bytes);
      break;

    default:
      return cr_ErrorCodes_BAD_FILE;
  }

  /* User code end [Files: Write] */
  return 0;
}

int crcb_file_transfer_complete(const uint32_t fid)
{
  int rval = 0;
  uint8_t idx;
  rval = sFindIndexFromFid(fid, &idx);
  if (0 != rval)
  {
    I3_LOG(LOG_MASK_ERROR, "%s(%d): invalid FID.", __FUNCTION__, fid);
    return cr_ErrorCodes_INVALID_ID;
  }
  /* User code start [Files: Write Complete]
   * This allows the application to handle any actions which need to occur after a file has successfully been written */

  switch (fid)
  {
    case FILE_IO_TXT:
      int rval = (int) nvm3_writeData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t*) io_txt, io_txt_size);
      if (rval != 0)
        I3_LOG(LOG_MASK_ERROR, "io.txt write failed, error %d", rval);
      file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;
      break;

    case FILE_DEV_NULL:
      break;

    default:
      return cr_ErrorCodes_BAD_FILE;
  }

  /* User code end [Files: Write Complete] */
  return 0;
}

int crcb_erase_file(const uint32_t fid)
{
  int rval = 0;
  uint8_t idx;
  rval = sFindIndexFromFid(fid, &idx);
  if (0 != rval)
  {
    I3_LOG(LOG_MASK_ERROR, "%s(%d): invalid FID.", __FUNCTION__, fid);
    return cr_ErrorCodes_INVALID_ID;
  }
  /* User code start [Files: Erase]
   * The exact meaning of "erasing" is user-defined, depending on how files are stored by the application */

  switch (fid)
  {
    case FILE_IO_TXT:
      int rval = nvm3_deleteObject(nvm3_defaultHandle, IO_TXT_KEY);
      if (rval != 0)
        I3_LOG(LOG_MASK_ERROR, "Failed to erase io.txt, error %d", rval);
      io_txt_size = 0;
      memset(io_txt, 0, sizeof(io_txt));
      file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;
      break;
    default:
      return cr_ErrorCodes_BAD_FILE;
  }

  /* User code end [Files: Erase] */
  return 0;
}

/* User code start [files.c: User Cygnus Reach Callback Functions] */
/* User code end [files.c: User Cygnus Reach Callback Functions] */

/********************************************************************************************
 *********************************     Local Functions     **********************************
 *******************************************************************************************/

static int sFindIndexFromFid(uint32_t fid, uint8_t *index)
{
  uint8_t idx;
  for (idx = 0; idx < NUM_FILES; idx++)
  {
    if (file_descriptions[idx].file_id == fid)
    {
      *index = idx;
      return 0;
    }
  }
  return cr_ErrorCodes_INVALID_ID;
}

/* User code start [files.c: User Local Functions] */
/* User code end [files.c: User Local Functions] */

