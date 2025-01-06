/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2025 Andreas Merkle
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
@brief  VSCP core functionality
@file   vscp_core.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the core functionality of VSCP.

*******************************************************************************/
/** @defgroup vscp_core The VSCP core functionality.
 * The VSCP core functionality.
 *
 * Some remarks:
 * - If a message is not sent and the core has no retry mechanism in this case,
 * the message will be lost.
 * - If a transmit message is lost, the core won't change to error state.
 *
 * Supported compile switches:
 * - VSCP_CONFIG_ENABLE_LOGGER
 * - VSCP_CONFIG_SILENT_NODE
 * - VSCP_CONFIG_HARD_CODED_NODE
 * - VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT
 * - VSCP_CONFIG_HEARTBEAT_NODE
 * - VSCP_CONFIG_IDLE_CALLOUT
 * - VSCP_CONFIG_ERROR_CALLOUT
 * - VSCP_CONFIG_BOOT_LOADER_SUPPORTED
 * - VSCP_CONFIG_ENABLE_DM
 * - VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION
 * - VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT
 * - VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION
 *
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_CORE_H__
#define __VSCP_CORE_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "vscp_config.h"
#include "vscp_types.h"

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

/** VSCP specification major version number, the framework is compliant to. */
#define VSCP_CORE_VERSION_MAJOR     (1)

/** VSCP specification minor version number, the framework is compliant to. */
#define VSCP_CORE_VERSION_MINOR     (13)

/** VSCP specification sub-minor version number, the framework is compliant to. */
#define VSCP_CORE_VERSION_SUB_MINOR (1)

/** VSCP specification version string, the framework is compliant to. */
#define VSCP_CORE_VERSION_STR       "v1.15.4"

/** VSCP framework version string */
#define VSCP_CORE_FRAMEWORK_VERSION "v2.1.0"

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** VSCP function return values. */
typedef enum
{
    VSCP_CORE_RET_OK = 0,   /**< Successful */
    VSCP_CORE_RET_ERROR     /**< Failed */

} VSCP_CORE_RET;

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

/**
 * This function initializes VSCP, including all layers.
 * Don't call any other VSCP function, until this function was called.
 */
extern VSCP_CORE_RET vscp_core_init(void);

/**
 * This function restores VSCP default values for
 * - all registers,
 * - the persistent memory,
 * - internal variables.
 *
 * In other words, it restore factory defaults settings.
 */
extern void vscp_core_restoreFactoryDefaultSettings(void);

/**
 * This function process the whole VSCP core stack. Call it in a user defined
 * cyclic period.
 *
 * Note, for a fast handling of received events, this function returns TRUE in
 * case a event was handled partly or completely, otherwise FALSE.
 * Call it e.g. in a loop until no event is handled anymore. If its not
 * necessary in your application, just skip the return value.
 *
 * @return If a received event was handled, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_core_process(void);

/**
 * This function reads the nickname id of the node.
 *
 * @return  Nickname id
 */
extern uint8_t  vscp_core_readNicknameId(void);

/**
 * This function starts the node segment initialization.
 */
extern void vscp_core_startNodeSegmentInit(void);

/**
 * This function set one or more alarm status.
 * How the bits are read, is application specific.
 * Note that a active alarm (bit is set) can only be cleared by reading the
 * alarm register. Calling this function with 0, does nothing.
 *
 * @param[in]   value   New alarm status
 */
extern void vscp_core_setAlarm(uint8_t value);

/**
 * This function determines the state of VSCP and if it is in active state,
 * it will return TRUE, otherwise FALSE.
 *
 * @return  Is VSCP active or not?
 * @retval  FALSE   Not in active state
 * @retval  TRUE    In active state
 */
extern BOOL vscp_core_isActive(void);

/**
 * Get the time since epoch 00:00:00 UTC, January 1, 1970.
 * The time itself is received by the segment master.
 *
 * @return Unix timestamp
 */
extern uint32_t vscp_core_getTimeSinceEpoch(void);

/**
 * Set the time since epoch 00:00:00 UTC, January 1, 1970.
 * Note, if a segment master is present, it will overwrite the time with its
 * heartbeat message.
 *
 * @param[in] timestamp Unix timestamp
 */
extern void vscp_core_setTimeSinceEpoch(uint32_t timestamp);

/**
 * Prepares a transmit message, before it is used.
 *
 * Default values:
 * - Nodes nickname
 * - Hard coded node flag
 * - No data
 *
 * After preparation, only the data and the number of data bytes has to be
 * modified additionally.
 *
 * @param[in,out]   txMessage   Transmit message which will be prepared.
 * @param[in]       vscpClass   Transmit message VSCP class
 * @param[in]       vscpType    Transmit message VSCP type
 * @param[in]       priority    Transmit message priority
 */
extern void vscp_core_prepareTxMessage(vscp_TxMessage * const txMessage, uint16_t vscpClass, uint8_t vscpType, VSCP_PRIORITY priority);

/**
 * Send a event to the communication bus. Don't forget to prepare your transmit
 * message (@see vscp_core_prepareTxMessage) first and then modify for your needs,
 * before sending it!
 *
 * @param[in]   txMessage   The event which will be sent.
 * @return Status
 * @retval FALSE    Failed to send the event.
 * @retval TRUE     Event successful sent.
 */
extern BOOL vscp_core_sendEvent(vscp_TxMessage const * const txMessage);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE )

/**
 * Enable or disable the node heartbeat.
 *
 * @param[in] enableIt  Enable/Disable node hearbeat
 */
extern void vscp_core_enableHeartbeat(BOOL enableIt);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_CORE_H__ */

/** @} */
