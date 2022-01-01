/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2022 Andreas Merkle
 * http://www.blue-andi.de
 * vscp@blue-andi.de
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
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
@brief  VSCP portable support package
@file   vscp_portable.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains VSCP support functionality, which is used by the core.

*******************************************************************************/
/** @defgroup vscp_portable Portable stuff
 * Here is all application depended stuff, which can be handled different in
 * any system.
 *
 * Supported compile switches:
 * - VSCP_CONFIG_BOOT_LOADER_SUPPORTED
 * - VSCP_CONFIG_IDLE_CALLOUT
 * - VSCP_CONFIG_ERROR_CALLOUT
 * - VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT
 * - VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT
 * - VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION
 *
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_PORTABLE_H__
#define __VSCP_PORTABLE_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "../core/vscp_types.h"
#include "../core/vscp_config.h"
#include "../core/vscp_dev_data_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

/**
 * This function initializes this module.
 */
extern void vscp_portable_init(void);

/**
 * Restore the application specific factory default settings.
 */
extern void vscp_portable_restoreFactoryDefaultSettings(void);

/**
 * This function set the current lamp state.
 *
 * @param[in]   state   Lamp state to set
 */
extern void vscp_portable_setLampState(VSCP_LAMP_STATE state);

/**
 * This function return the current lamp state.
 *
 * @return Lamp state
 */
extern VSCP_LAMP_STATE vscp_portable_getLampState(void);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_IDLE_CALLOUT )

/**
 * If VSCP stops its work and enters idle state, this function will be called.
 */
extern void vscp_portable_idleStateEntered(void);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_IDLE_CALLOUT ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ERROR_CALLOUT )

/**
 * If VSCP stops its work and enters error state, this function will be called.
 */
extern void vscp_portable_errorStateEntered(void);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ERROR_CALLOUT ) */

/**
 * This function requests a reset.
 * It requests it and doesn't expect that it will be immediately.
 * Because the application needs time to change to a safe state before.
 */
extern void vscp_portable_resetRequest(void);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED )

/**
 * This function returns the supported boot loader algorithm.
 *
 * @return  Boot loader algorithm
 * @retval  0xFF    No boot loader supported
 */
extern uint8_t  vscp_portable_getBootLoaderAlgorithm(void);

/**
 * This function requests a jump to the bootloader.
 * It requests it and doesn't expect that it will be immediately.
 * Because the application needs time to change to a safe state before.
 */
extern void vscp_portable_bootLoaderRequest(void);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */

/**
 * This function provides received VSCP events, except the PROTOCOL class.
 *
 * @param[in]   msg Message
 */
extern void vscp_portable_provideEvent(vscp_RxMessage const * const msg);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION )

/**
 * This function provides received VSCP PROTOCOL class events.
 *
 * Attention: Handling events which the core is waiting for can cause bad
 * behaviour.
 * 
 * @param[in]   msg Message
 * 
 * @return Event handled or not. If application handles event, the core won't handle it.
 * @retval FALSE    Event not handled
 * @retval TRUE     Event handled
 */
extern BOOL vscp_portable_provideProtocolEvent(vscp_RxMessage const * const msg);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT )

/**
 * This function is called for every received segment master heartbeat event,
 * in case it contains a new time since epoch.
 * 
 * @param timestamp Unix timestamp
 */
extern void vscp_portable_updateTimeSinceEpoch(uint32_t timestamp);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT )

/**
 * This function returns one byte of the GUID, which is selected by the index.
 * Index 0 corresponds with the GUID LSB byte, index 15 with the GUID MSB byte.
 * 
 * Note, this function can be used to get the MCU stored GUID.
 *
 * @param[in]   index   Index in the GUID [0-15]
 * @return  GUID byte
 */
extern uint8_t  vscp_portable_readGUID(uint8_t index);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_CUSTOM_HEARTBEAT )

/**
 * Custom node heartbeat event function implementation.
 *
 * @return Status
 * @retval FALSE Failed to send the event
 * @retval TRUE  Event successul sent
 */
extern BOOL vscp_portable_sendNodeHeartbeatEvent();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_CUSTOM_HEARTBEAT ) */

/**
 * This function read a received VSCP message.
 * If no message is received it returns FALSE otherwise TRUE.
 *
 * @param[out]  msg Message
 * @return Message received or not
 */
extern BOOL vscp_portable_read(vscp_RxMessage * const msg);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_PORTABLE_H__ */

/** @} */
