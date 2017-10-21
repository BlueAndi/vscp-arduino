/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2017, Andreas Merkle
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
@brief  VSCP default configuration
@file   vscp_config.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the configuration switches and timing related constants
for VSCP core and decision matrix.

*******************************************************************************/
/** @defgroup vscp_config VSCP default configuration
 * The default configuration of VSCP handles the default features of the
 * framework and its default constant parameters.
 *
 * Please don't change anything in this file and use the overwrite mechanism
 * by setting your prefered configuration in vscp_config_overwrite.h
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_CONFIG_H__
#define __VSCP_CONFIG_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_config_base.h"
#include "vscp_config_overwrite.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

#ifndef VSCP_CONFIG_ENABLE_LOGGER

/** Enable log functionality (CLASS1.Log). Use the macros in vscp_logger.h to
 * send log messages.
 */
#define VSCP_CONFIG_ENABLE_LOGGER               VSCP_CONFIG_BASE_DISABLED

#endif  /* VSCP_CONFIG_ENABLE_LOGGER */

#ifndef VSCP_CONFIG_SILENT_NODE

/** Silent node configuration, which is used for e. g. RS-485 connections.
 * This type of nodes only listen to traffic before they get initialized
 * by a host. In this case the nickname discovery process is not started
 * for a node when it is powered up for the first time.
 * This type on node instead starts to listen for the
 * CLASS1.PROTOCOL, Type=23 (GUID drop nickname-ID / reset device.) event.
 * When this series of events is received and the GUID is the same as for
 * the module the module starts the nickname discovery procedure as of above.
 */
#define VSCP_CONFIG_SILENT_NODE                 VSCP_CONFIG_BASE_DISABLED

#endif  /* VSCP_CONFIG_SILENT_NODE */

#ifndef VSCP_CONFIG_HARD_CODED_NODE

/** Hard-coded node (fixed nickname id)
 * @todo Support of hard-coded node configuration.
 */
#define VSCP_CONFIG_HARD_CODED_NODE             VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_HARD_CODED_NODE */

#ifndef VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT

/** Enable segment controller heartbeat support for nodes. */
#define VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT   VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT */

#ifndef VSCP_CONFIG_HEARTBEAT_NODE

/** Enable sending node heartbeat (mandatory since 2015-09-10). */
#define VSCP_CONFIG_HEARTBEAT_NODE              VSCP_CONFIG_BASE_ENABLED

#endif  /* Undefined VSCP_CONFIG_HEARTBEAT_NODE */

#ifndef VSCP_CONFIG_IDLE_CALLOUT

/** Enable idle callout.
 * If VSCP stops working and enters idle state, the application will be
 * notified.
 */
#define VSCP_CONFIG_IDLE_CALLOUT                VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_IDLE_CALLOUT */

#ifndef VSCP_CONFIG_ERROR_CALLOUT

/** Enable error callout.
 * If VSCP stops working and enters error state, the application will be
 * notified.
 */
#define VSCP_CONFIG_ERROR_CALLOUT               VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_ERROR_CALLOUT */

#ifndef VSCP_CONFIG_BOOT_LOADER_SUPPORTED

/** Enable boot loader support. */
#define VSCP_CONFIG_BOOT_LOADER_SUPPORTED       VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_BOOT_LOADER_SUPPORTED */

#ifndef VSCP_CONFIG_ENABLE_DM

/** Enable decision matrix (standard). */
#define VSCP_CONFIG_ENABLE_DM                   VSCP_CONFIG_BASE_ENABLED

#endif  /* Undefined VSCP_CONFIG_ENABLE_DM */

#ifndef VSCP_CONFIG_DM_PAGED_FEATURE

/** Enable decision matrix special paged feature. */
#define VSCP_CONFIG_DM_PAGED_FEATURE            VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_DM_PAGED_FEATURE */

#ifndef VSCP_CONFIG_ENABLE_DM_EXTENSION

/** Enable the decision matrix extension to be able to compare to
 * a configureable zone/sub-zone and event parameters.
 */
#define VSCP_CONFIG_ENABLE_DM_EXTENSION         VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_ENABLE_DM_EXTENSION */

#if VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM )

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )
#error If you use the special paged feature, enable the decision matrix first.
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )
#error If you use the decision matrix extension, enable the decision matrix first.
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM ) */

#ifndef VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION

/** Enable the decision matrix next generation. */
#define VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION   VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION */

#ifndef VSCP_CONFIG_ENABLE_LOOPBACK

/** Enable a loopback for all sent VSCP events. This feature is interesting to invoke
 * decision matrix actions by own sent VSCP events.
 */
#define VSCP_CONFIG_ENABLE_LOOPBACK             VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_CONFIG_ENABLE_LOOPBACK */

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

#ifndef VSCP_CONFIG_NODE_SEGMENT_INIT_TIMEOUT

/** Timeout in ms for the node segment initialization.
 * See VSCP specification, chapter VSCP Level I Specifics, Node segment initialization. Dynamic nodes, Step 2
 */
#define VSCP_CONFIG_NODE_SEGMENT_INIT_TIMEOUT   ((uint16_t)5000)

#endif  /* Undefined VSCP_CONFIG_NODE_SEGMENT_INIT_TIMEOUT */

#ifndef VSCP_CONFIG_PROBE_ACK_TIMEOUT

/** Timeout in ms for the probe acknowledge. */
#define VSCP_CONFIG_PROBE_ACK_TIMEOUT           ((uint16_t)2000)

#endif  /* Undefined VSCP_CONFIG_PROBE_ACK_TIMEOUT */

#ifndef VSCP_CONFIG_MULTI_MSG_TIMEOUT

/** Timeout in ms to observe multi-message handling. */
#define VSCP_CONFIG_MULTI_MSG_TIMEOUT           ((uint16_t)1000)

#endif  /* Undefined VSCP_CONFIG_MULTI_MSG_TIMEOUT */

#ifndef VSCP_CONFIG_HEARTBEAT_NODE_PERIOD

/** Node heartbeat period in ms (recommended 30s - 60s). */
#define VSCP_CONFIG_HEARTBEAT_NODE_PERIOD       ((uint16_t)30000)

#endif  /* Undefined VSCP_CONFIG_HEARTBEAT_NODE_PERIOD */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

#if VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

#ifndef VSCP_CONFIG_DM_PAGE

/** Decision matrix location: First page of the decision matrix. */
#define VSCP_CONFIG_DM_PAGE                     1

#endif  /* Undefined VSCP_CONFIG_DM_PAGE */

#if (0 == VSCP_CONFIG_DM_PAGE)
#error If you want the special paged feature, please enable VSCP_CONFIG_DM_PAGED_FEATURE instead of using VSCP_CONFIG_DM_PAGE.
#endif  /* (0 == VSCP_CONFIG_DM_PAGE) */

#ifndef VSCP_CONFIG_DM_OFFSET

/** Decision matrix location: Offset in the first page of the decision matrix. */
#define VSCP_CONFIG_DM_OFFSET                   0

#endif  /* Undefined VSCP_CONFIG_DM_OFFSET */

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

#ifndef VSCP_CONFIG_DM_ROWS

/** Number of decision matrix rows. */
#define VSCP_CONFIG_DM_ROWS                     10

#endif  /* Undefined VSCP_CONFIG_DM_ROWS */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

#ifndef VSCP_CONFIG_DM_NG_PAGE

/** Decision matrix next generation: Location in the application register space.
 * Note that the dm ng always starts at the begin of the page! This design
 * decision was just for simplification, nothing else.
 */
#define VSCP_CONFIG_DM_NG_PAGE                  2

#endif  /* Undefined VSCP_CONFIG_DM_NG_PAGE */

#ifndef VSCP_CONFIG_DM_NG_RULE_SET_SIZE

/** Decision matrix next generation: Maximum size in bytes of a rule set. */
#define VSCP_CONFIG_DM_NG_RULE_SET_SIZE         80

#endif  /* VSCP_CONFIG_DM_NG_RULE_SET_SIZE */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK )

#ifndef VSCP_CONFIG_LOOPBACK_STORAGE_NUM

/** Number of messages in the loopback cyclic buffer. Note, that if you want to
 * store up to 3 events, you have to configure 4, because of the technical
 * implementation of the cyclic buffer.
 */
#define VSCP_CONFIG_LOOPBACK_STORAGE_NUM        4

#endif  /* VSCP_CONFIG_LOOPBACK_STORAGE_NUM */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK ) */

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

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_CONFIG_H__ */

/** @} */
