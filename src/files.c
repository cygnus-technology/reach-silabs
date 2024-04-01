/********************************************************************************************
 *
 * \date   2024
 *
 * \author i3 Product Development (JNP)
 *
 * \brief  Functions to handle reading and writing files with Reach
 *
 ********************************************************************************************/

#include "cr_stack.h"
#include "definitions.h"
#include "i3_log.h"

#include "const_files.h"

// If defined, NVM files will be stored in the NVM3 system
#define FILES_USE_NVM_STORAGE

#ifdef FILES_USE_NVM_STORAGE
#include "nvm3_generic.h"
#define IO_TXT_KEY 0x1010
#endif

#define MAX_IO_TXT_LENGTH 2048

static char io_txt[MAX_IO_TXT_LENGTH];
static size_t io_txt_size = 0;

void files_init(void)
{
#ifdef FILES_USE_NVM_STORAGE
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
#else
  file_descriptions[FILE_IO_TXT].storage_location = cr_StorageLocation_RAM;
  memset(io_txt, 0, sizeof(io_txt));
  memcpy(io_txt, default_io_txt, sizeof(default_io_txt));
  io_txt_size = sizeof(default_io_txt);
#endif
  file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;
}

void files_reset(void)
{
  memset(io_txt, 0, sizeof(io_txt));
  memcpy(io_txt, default_io_txt, sizeof(default_io_txt));
  io_txt_size = sizeof(default_io_txt);
  file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;
#ifdef FILES_USE_NVM_STORAGE
  int rval = (int) nvm3_writeData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t*) default_io_txt, sizeof(default_io_txt));
  if (rval != 0)
    I3_LOG(LOG_MASK_ERROR, "io.txt write failed, error %d", rval);
#endif
}

int crcb_read_file(const uint32_t fid,          // which file
                 const int offset,              // offset, negative value specifies current location.
                 const size_t bytes_requested,  // how many bytes to read
                 uint8_t *pData,                // where the data goes
                 int *bytes_read)               // bytes actually read, negative for errors.
{
  if (bytes_requested > REACH_BYTES_IN_A_FILE_PACKET)
  {
    I3_LOG(LOG_MASK_ERROR, "%s: %d is more than the buffer for a file read (%d).", __FUNCTION__, fid, REACH_BYTES_IN_A_FILE_PACKET);
    return cr_ErrorCodes_BUFFER_TOO_SMALL;
  }
  switch (fid)
  {
    case FILE_IO_TXT:
      if (offset < 0 || offset >= (int) io_txt_size)
        return cr_ErrorCodes_NO_DATA;
#ifdef FILES_USE_NVM_STORAGE
      if (offset == 0)
      {
        // Update the local buffer of the file in case a write failed before this read
        int rval = (int) nvm3_readData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t*) io_txt, io_txt_size);
        if (rval != 0)
          I3_LOG(LOG_MASK_ERROR, "io.txt read failed, error %d", rval);
      }
#endif
      *bytes_read = ((offset + bytes_requested) > io_txt_size) ? (io_txt_size - offset) : bytes_requested;
      memcpy(pData, &io_txt[offset], (size_t) *bytes_read);
      break;
    case FILE_CYGNUS_REACH_LOGO_PNG:
      if (offset < 0 || offset >= (int) sizeof(cygnus_reach_logo))
        return cr_ErrorCodes_NO_DATA;
      *bytes_read = ((offset + bytes_requested) > sizeof(cygnus_reach_logo)) ? (sizeof(cygnus_reach_logo) - offset) : bytes_requested;
      memcpy(pData, &cygnus_reach_logo[offset], (size_t) *bytes_read);
      break;
    default:
      i3_log(LOG_MASK_ERROR, "Invalid file read (ID %u)", fid);
      return cr_ErrorCodes_BAD_FILE;
  }
  return 0;
}

int crcb_file_prepare_to_write(const uint32_t fid, const size_t offset, const size_t bytes)
{
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
    default:
      return cr_ErrorCodes_BAD_FILE;
  }
  return 0;
}

int crcb_write_file(const uint32_t fid, // which file
                 const int offset,      // offset, negative value specifies current location.
                 const size_t bytes,    // how many bytes to write
                 const uint8_t *pData)  // where to get the data from
{
  switch (fid)
  {
    case FILE_IO_TXT:
      if (offset < 0 || offset + bytes > io_txt_size)
        return cr_ErrorCodes_INVALID_PARAMETER;
      memcpy(&io_txt[offset], pData, bytes);
      break;
    default:
      return cr_ErrorCodes_BAD_FILE;
  }
  return 0;
}

int crcb_file_transfer_complete(const uint32_t fid)
{
  switch (fid)
  {
    case FILE_IO_TXT:
#ifdef FILES_USE_NVM_STORAGE
      int rval = (int) nvm3_writeData(nvm3_defaultHandle, IO_TXT_KEY, (uint8_t*) io_txt, io_txt_size);
      if (rval != 0)
        I3_LOG(LOG_MASK_ERROR, "io.txt write failed, error %d", rval);
#endif
      file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;
      break;
    default:
      return cr_ErrorCodes_BAD_FILE;
  }
  return 0;
}

// returns zero or an error code
int crcb_erase_file(const uint32_t fid)
{
  switch (fid)
  {
    case FILE_IO_TXT:
#ifdef FILES_USE_NVM_STORAGE
      int rval = nvm3_deleteObject(nvm3_defaultHandle, IO_TXT_KEY);
      if (rval != 0)
        I3_LOG(LOG_MASK_ERROR, "Failed to erase io.txt, error %d", rval);
#endif
      io_txt_size = 0;
      memset(io_txt, 0, sizeof(io_txt));
      file_descriptions[FILE_IO_TXT].current_size_bytes = (int32_t) io_txt_size;
      break;
    default:
      return cr_ErrorCodes_BAD_FILE;
  }
  return 0;
}
