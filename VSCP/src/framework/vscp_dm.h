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
@brief  VSCP decision matrix
@file   vscp_dm.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module handles the decision matrix of the node.

*******************************************************************************/
/** @defgroup vscp_dm Decision matrix
 * The decision matrix.
 *
 * The page of the decision matrix can be configured by VSCP_CONFIG_DM_PAGE.
 * And the offset in the page by VSCP_CONFIG_DM_OFFSET.
 *
 * The number of rows can be configured by changing the VSCP_CONFIG_DM_ROWS.
 *
 * Supported compile switches:
 * - VSCP_CONFIG_ENABLE_DM
 * - VSCP_CONFIG_DM_PAGED_FEATURE
 * - VSCP_CONFIG_ENABLE_DM_EXTENSION
 *
 * If the decision matrix extension is enabled, it will be just behind the
 * standard decision matrix in the persistent memory. Important is, that
 * the decision matrix extension has the same number of rows and the same
 * size in bytes as the standard decision matrix.
 *
 * Note that if the number rows in the decision matrix is requested with
 * ::vscp_dm_getMatrixRows, always the number of rows of the standard
 * decision matrix is returned. In case of the extension is enabled, too.
 * This is, because VSCP specification v1.10.16 doesn't know anything about
 * the decision matrix extension.
 *
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_DM_H__
#define __VSCP_DM_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <inttypes.h>
#include "vscp_config.h"
#include "vscp_types.h"
#include "vscp_util.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

/** Decision matrix (standard or extension) row size in bytes */
#define VSCP_DM_ROW_SIZE            8

/** Action: No operation */
#define VSCP_DM_ACTION_NO_OPERATION (0x00)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/** This action is the trigger to use the decision matrix extension.
 * Set it in the action of the standard decision matrix and the extension is
 * enabled (only) for this row.
 */
#define VSCP_DM_ACTION_EXTENDED_DM  (0xff)

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** This type defines the decision matrix row flags. */
typedef enum
{
    VSCP_DM_FLAG_CLASS_FILTER_BIT8  = 0x01, /**< Class filter bit 8 (MSB) */
    VSCP_DM_FLAG_CLASS_MASK_BIT8    = 0x02, /**< Class mask bit 8 (MSB) */
    VSCP_DM_FLAG_RESERVED           = 0x04, /**< Reserved for future use */
    VSCP_DM_FLAG_MATCH_SUB_ZONE     = 0x08, /**< Match sub zone flag */
    VSCP_DM_FLAG_MATCH_ZONE         = 0x10, /**< Match zone flag */
    VSCP_DM_FLAG_HARDCODED          = 0x20, /**< Hardcoded node address */
    VSCP_DM_FLAG_CHECK_OADDR        = 0x40, /**< Check originating address */
    VSCP_DM_FLAG_ENABLE             = 0x80  /**< Enable decision matrix row */

} VSCP_DM_FLAG;

/** This type defines a decision matrix row. */
typedef struct
{
    uint8_t oaddr;          /**< Originating address (event source) */
    uint8_t flags;          /**< Flags */
    uint8_t classMask;      /**< Class mask */
    uint8_t classFilter;    /**< Class filter */
    uint8_t typeMask;       /**< Type mask */
    uint8_t typeFilter;     /**< Type filter */
    uint8_t action;         /**< Action */
    uint8_t actionPar;      /**< Action parameter */

} vscp_dm_MatrixRow;

VSCP_UTIL_COMPILE_TIME_ASSERT(sizeof(vscp_dm_MatrixRow) == VSCP_DM_ROW_SIZE);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/** This type defines the extension flags. */
typedef enum
{
    VSCP_DM_EXTFLAG_MATCH_PAR_0 = 0x01, /**< Compare to event parameter byte 0 */
    VSCP_DM_EXTFLAG_MATCH_PAR_3 = 0x02, /**< Compare to event parameter byte 3 */
    VSCP_DM_EXTFLAG_MATCH_PAR_4 = 0x04, /**< Compare to event parameter byte 4 */
    VSCP_DM_EXTFLAG_MATCH_PAR_5 = 0x08, /**< Compare to event parameter byte 5 */
    VSCP_DM_EXTFLAG_RESERVED_0  = 0x10, /**< Reserved for future use */
    VSCP_DM_EXTFLAG_RESERVED_1  = 0x20, /**< Reserved for future use */
    VSCP_DM_EXTFLAG_RESERVED_2  = 0x40, /**< Reserved for future use */
    VSCP_DM_EXTFLAG_RESERVED_3  = 0x80  /**< Reserved for future use */

} VSCP_DM_EXTFLAG;

/** This type defines a decision matrix extension row. */
typedef struct
{
    uint8_t zone;       /**< Zone */
    uint8_t subZone;    /**< Sub-zone */
    uint8_t par0;       /**< Event parameter byte 0 */
    uint8_t par3;       /**< Event parameter byte 3 */
    uint8_t par4;       /**< Event parameter byte 4 */
    uint8_t par5;       /**< Event parameter byte 5 */
    uint8_t action;     /**< Action */
    uint8_t actionPar;  /**< Action parameter */

} vscp_dm_ExtRow;

VSCP_UTIL_COMPILE_TIME_ASSERT(sizeof(vscp_dm_ExtRow) == VSCP_DM_ROW_SIZE);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the decision matrix module.
 */
extern void vscp_dm_init(void);

/**
 * This function restores factory default settings.
 */
extern void vscp_dm_restoreFactoryDefaultSettings(void);

/**
 * This function get the number of rows in the decision matrix.
 *
 * @return  Number of rows
 */
extern uint8_t  vscp_dm_getMatrixRows(void);

/**
 * This function returns the page of the decision matrix.
 *
 * @return  Page
 */
extern uint16_t vscp_dm_getPage(void);

/**
 * This function get the offset of the decision matrix.
 *
 * @return  Decision matrix offset
 */
extern uint8_t  vscp_dm_getMatrixOffset(void);

/**
 * This function check if the given page and address are part of the
 * decision matrix.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Is part of the decision matrix or not.
 * @retval  FALSE   Is not part of the decision matrix.
 * @retval  TRUE    Is part of the decision matrix.
 */
extern BOOL vscp_dm_isDecisionMatrix(uint16_t page, uint8_t addr);

/**
 * Read register and return its value.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Register value
 */
extern uint8_t  vscp_dm_readRegister(uint16_t page, uint8_t addr);

/**
 * Write to register.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @param[in]   value   Value to write
 * @return  Register value
 */
extern uint8_t  vscp_dm_writeRegister(uint16_t page, uint8_t addr, uint8_t value);

/**
 * This function check the decision matrix and executes their actions if
 * applicable.
 *
 * @param[in]   msg Received message via VSCP
 */
extern void vscp_dm_executeActions(vscp_RxMessage const * const msg);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_DM_H__ */

/** @} */
