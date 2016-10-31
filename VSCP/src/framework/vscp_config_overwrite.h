/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2016, Andreas Merkle
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
@brief  VSCP configuration overwrite
@file   vscp_config_overwrite.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the configuration preferred by the user. It overwrites the
default configuration in vscp_config.h

*******************************************************************************/
/** @defgroup vscp_config_overwrite VSCP configuration overwrite
 * This module contains the configuration preferred by the user. It overwrites the
 * default configuration in vscp_config.h
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_CONFIG_OVERWRITE_H__
#define __VSCP_CONFIG_OVERWRITE_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/* ---------- Define here your preferred configuration setup. ---------- */

/*
#define VSCP_CONFIG_ENABLE_LOGGER               VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_SILENT_NODE                 VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_HARD_CODED_NODE             VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT   VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_HEARTBEAT_NODE              VSCP_CONFIG_BASE_ENABLED

#define VSCP_CONFIG_IDLE_CALLOUT                VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_ERROR_CALLOUT               VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_BOOT_LOADER_SUPPORTED       VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_ENABLE_DM                   VSCP_CONFIG_BASE_ENABLED

#define VSCP_CONFIG_DM_PAGED_FEATURE            VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_ENABLE_DM_EXTENSION         VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION   VSCP_CONFIG_BASE_DISABLED

#define VSCP_CONFIG_ENABLE_LOOPBACK             VSCP_CONFIG_BASE_DISABLED

*/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

/* ---------- Define here your preferred configuration setup. ---------- */

/*

#define VSCP_CONFIG_NODE_SEGMENT_INIT_TIMEOUT   ((uint16_t)5000)

#define VSCP_CONFIG_PROBE_ACK_TIMEOUT           ((uint16_t)2000)

#define VSCP_CONFIG_MULTI_MSG_TIMEOUT           ((uint16_t)1000)

#define VSCP_CONFIG_HEARTBEAT_NODE_PERIOD       ((uint16_t)30000)

#define VSCP_CONFIG_DM_PAGE                     1

#define VSCP_CONFIG_DM_OFFSET                   0

#define VSCP_CONFIG_DM_ROWS                     10

#define VSCP_CONFIG_DM_NG_RULE_SET_SIZE         80

#define VSCP_CONFIG_LOOPBACK_STORAGE_NUM        4

*/

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

#endif  /* __VSCP_CONFIG_OVERWRITE_H__ */

/** @} */
