/*
 * reach-server.h
 *
 *  This file specifies aspects of the Reach server that are controlled by the app.
 *
 */

/**
 * @file      reach-server.c
 * @brief     This file specifies aspects of the Reach server that are 
 *            controlled by the app.
 * @copyright (c) Copyright 2023 i3 Product Development. All Rights Reserved.
 */


#ifndef _REACH_SERVER_H_
#define _REACH_SERVER_H_


/// If this is defined, the Reach characteristic must be set up to use 
/// encryption in the GATT table as well
// #define REACH_USE_ENCRYPTION

#ifdef REACH_USE_ENCRYPTION

/// These 4 defines can be used to configure different levels of 
/// encryption/authentication being used for BLE communications

/// Defining this will allow for pairing/authentication information 
/// to be stored. Bonding must also be set up for 
/// reading/writing/notifying the Reach characteristic in the 
/// GATT table NOTE: Not enabling bonding seems to result in 
/// weird behavior with re-connecting to devices 
#define REACH_USE_BONDING

/// If using authentication, the Reach characteristic must be set 
/// up in the GATT table to require authentication for 
/// reading/writing/notifying as well 
#define REACH_USE_AUTHENTICATION

#ifdef REACH_USE_AUTHENTICATION
/// Defining only the app or device-side authentication will require 
/// entering a passcode on the side selected.
#define REACH_USE_APP_SIDE_AUTHENTICATION
#define REACH_USE_DEVICE_SIDE_AUTHENTICATION

/// Defining this will only allow secure connections (security level 4), 
/// not legacy pairing
#define REACH_REQUIRE_AUTHENTICATED_SECURE_CONNECTIONS

#if (!defined(REACH_USE_APP_SIDE_AUTHENTICATION) && !defined(REACH_USE_DEVICE_SIDE_AUTHENTICATION))
#error "If using BLE authentication, at least one means of authentication must be supported!"
#endif

#endif // REACH_USE_AUTHENTICATION
#endif // REACH_USE_ENCRYPTION

/// A range of parameters are driven by the 244 byte packet size 
/// imposed by BLE.  See reach_ble_proto_sizes.h 

/// As the app is using BLE, the largest encoded buffer cannot be larger than 
/// 244 bytes.  The Reach stack will statically allocate two buffers of this size, 
/// for encoding and decoding
#define CR_CODED_BUFFER_SIZE    244

/// The raw data that encodes to BLE might be slightly larger.
/// The Reach stack will allocate one buffer of this size, for decoding the prompt.
/// The app is to provide the raw memory to be encoded.
#define CR_DECODED_BUFFER_SIZE   256 

/// Number of ticks per second passed to cr_process()
#define SYS_TICK_RATE   1000

/// #define NO_REACH_LOGGING to completely exclude logging to save space.
/// #define NO_REACH_LOGGING 

/// What logging should be enabled by default.  See i3_log.h
#define DEFAULT_LOG_MASK    0xCF7

/// Determines the storage space for the advertised name.  See 
/// cr_set_advertised_name().  Allows an app to adjust this depending on its 
/// needs. 
#define APP_ADVERTISED_NAME_LENGTH  16


#define INCLUDE_PARAMETER_SERVICE
/// Define this to be a 32 bit number that must be provided to access the device.
/// #define APP_REQUIRED_CHALLENGE_KEY  0x1020304

/// Setting this to zero removes support for unpolled parameter change notification
/// Defines the size of the array holding param notification specifications.
#define NUM_SUPPORTED_PARAM_NOTIFY  8

/// Define this to include support for the file service.
#define INCLUDE_FILE_SERVICE

/// Define this to support the remote CLI service.
#define INCLUDE_CLI_SERVICE
#ifdef INCLUDE_CLI_SERVICE
  /// If false use a command to enable it.
  #define REMOTE_CLI_ECHO_ON_DEFAULT    false
#endif

#define INCLUDE_COMMAND_SERVICE

#define INCLUDE_TIME_SERVICE

// #define INCLUDE_WIFI_SERVICE

// #define INCLUDE_STREAM_SERVICE

// Configuration of error reporting by cr_report_error()
#define ERROR_FORMAT_LOG_ONLY   0  // only log to console
#define ERROR_FORMAT_SHORT      1  // send error code only to client
#define ERROR_FORMAT_FULL       2  // send error message to client.
#define ERROR_REPORT_FORMAT     ERROR_FORMAT_FULL

#include "reach.pb.h"

/// Ideally all of the buffer sizes flow from here.
#include "reach_ble_proto_sizes.h"

/// This is the number of buffers allocated.
/// It's coded here to be the same as the number allowed in a transfer.
/// With code changes it could be less.
#define REACH_PARAM_BUFFER_COUNT REACH_COUNT_PARAM_IDS

// To test the case in which there are no extended parameter descriptions:
// #define SKIP_ENUMS  // test

/// Define this to test compatibility with the Ahsoka header.
/// You must also change reach.proto.
#define AHSOKA_HEADER
#define TEST_HEADER

// prints out buffer sizes for tuning.
#define VERBOSE_SIZES

#endif  // ndef _REACH_SERVER_H_

