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
@brief  VSCP decision matrix next generation
@file   vscp_dm_ng.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the VSCP decision matrix next generation.

*******************************************************************************/
/** @defgroup vscp_dm_ng VSCP decision matrix next generation
 * The decision matrix next generation (DM-NG) is from the idea similar to the
 * standard decision matrix and the decision matrix extension.
 * But it breaks out of their limitations.
 *
 * <pre>
 * EBNF:
 * rule set = number of rules, { rule } ;
 * rule = rule size, action, decision ;
 * action = action id, action parameter ;
 * decision = condition, { condition } ;
 * condition = condition operator, event parameter id, value ;
 * condition operator = logic operator, basic operator ;
 * logic operator = last | and | or ;
 * basic operator = undefined | equal | lower | greater | lower or equal | greater or equal | mask ;
 * </pre>
 *
 * Supported compile switches:
 * - VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION
 *
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_DM_NG_H__
#define __VSCP_DM_NG_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <inttypes.h>
#include "vscp_config.h"
#include "vscp_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/** Enable the debug mode for easier rule debugging. */
#define VSCP_DM_NG_DEBUG    VSCP_CONFIG_BASE_ENABLED

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

/** Action: No operation */
#define VSCP_DM_NG_ACTION_NO_OPERATION  (0x00)

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** This type defines the supported status return values. */
typedef enum
{
    VSCP_DM_NG_RET_OK = 0,  /**< Successful */
    VSCP_DM_NG_RET_NO_RULE, /**< No rule available */
    VSCP_DM_NG_RET_ERROR,   /**< Error */
    VSCP_DM_NG_RET_NULL     /**< Unexpected NULL pointer */

} VSCP_DM_NG_RET;

/** This type defines the supported basic operators. */
typedef enum
{
    VSCP_DM_NG_BASIC_OP_UNDEFINED = 0,  /**< Undefined condition */
    VSCP_DM_NG_BASIC_OP_EQUAL,          /**< Event parameter value is equal to defined value */
    VSCP_DM_NG_BASIC_OP_LOWER,          /**< Event parameter value is lower than defined value */
    VSCP_DM_NG_BASIC_OP_GREATER,        /**< Event parameter value is greater than defined value */
    VSCP_DM_NG_BASIC_OP_LOWER_EQUAL,    /**< Event parameter value is lower or equal than defined value */
    VSCP_DM_NG_BASIC_OP_GREATER_EQUAL,  /**< Event parameter value is greater or equal than defined value */
    VSCP_DM_NG_BASIC_OP_MASK,           /**< Event parameter value is masked with defined value */

    VSCP_DM_NG_BASIC_OP_MAX_NUM         /**< Only used to get the number of basic operators. */

} VSCP_DM_NG_BASIC_OP;

/** This type defines the supported logic operators. */
typedef enum
{
    VSCP_DM_NG_LOGIC_OP_LAST = 0x00,    /**< Last condition */
    VSCP_DM_NG_LOGIC_OP_AND  = 0x10,    /**< Combine the following condition with logic AND */
    VSCP_DM_NG_LOGIC_OP_OR   = 0x20     /**< Combine the following condition with logic OR */

} VSCP_DM_NG_LOGIC_OP;

/** This type defines the supported event parameters. */
typedef enum
{
    VSCP_DM_NG_EVENT_PAR_ID_UNDEFINED = 0,  /**< Undefined */
    VSCP_DM_NG_EVENT_PAR_ID_CLASS,          /**< Class */
    VSCP_DM_NG_EVENT_PAR_ID_TYPE,           /**< Type */
    VSCP_DM_NG_EVENT_PAR_ID_OADDR,          /**< Nickname id */
    VSCP_DM_NG_EVENT_PAR_ID_HARD_CODED,     /**< Hard coded flag */
    VSCP_DM_NG_EVENT_PAR_ID_PRIORITY,       /**< Priority */
    VSCP_DM_NG_EVENT_PAR_ID_ZONE,           /**< Zone */
    VSCP_DM_NG_EVENT_PAR_ID_SUB_ZONE,       /**< Sub-zone */
    VSCP_DM_NG_EVENT_PAR_ID_DATA_NUM,       /**< Number of data in the payload */
    VSCP_DM_NG_EVENT_PAR_ID_DATA0,          /**< Payload data byte 0 */
    VSCP_DM_NG_EVENT_PAR_ID_DATA1,          /**< Payload data byte 1 */
    VSCP_DM_NG_EVENT_PAR_ID_DATA2,          /**< Payload data byte 2 */
    VSCP_DM_NG_EVENT_PAR_ID_DATA3,          /**< Payload data byte 3 */
    VSCP_DM_NG_EVENT_PAR_ID_DATA4,          /**< Payload data byte 4 */
    VSCP_DM_NG_EVENT_PAR_ID_DATA5,          /**< Payload data byte 5 */
    VSCP_DM_NG_EVENT_PAR_ID_DATA6,          /**< Payload data byte 6 */
    VSCP_DM_NG_EVENT_PAR_ID_DATA,           /**< Payload data byte x (x is additional index value) */

    VSCP_DM_NG_EVENT_PAR_ID_MAX_NUM         /**< Only used to get the number of event parameter ids. */

} VSCP_DM_NG_EVENT_PAR_ID;

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the module.
 */
extern void vscp_dm_ng_init(void);

/**
 * This function restores factory default settings.
 */
extern void vscp_dm_ng_restoreFactoryDefaultSettings(void);

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
extern BOOL vscp_dm_ng_isDecisionMatrix(uint16_t page, uint8_t addr);

/**
 * Read register and return its value.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Register value
 */
extern uint8_t  vscp_dm_ng_readRegister(uint16_t page, uint8_t addr);

/**
 * Write to register.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @param[in]   value   Value to write
 * @return  Register value
 */
extern uint8_t  vscp_dm_ng_writeRegister(uint16_t page, uint8_t addr, uint8_t value);

/**
 * This function process all configured rules and if any action regarding the
 * received message takes place, it will call the corresponding action.
 *
 * @param[in]   rxMsg   Received message
 */
extern void vscp_dm_ng_executeActions(vscp_RxMessage const * const rxMsg);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DM_NG_DEBUG )

/**
 * Get error information, if available.
 *
 * @param[out]  rule    Rule number [1; x]
 * @param[out]  pos     Position index in the rule (not rule set)
 * @return Error available
 * @retval FALSE    No error
 * @retval TRUE     Error happened
 */
extern BOOL vscp_dm_ng_getError(uint8_t * const rule, uint8_t * const pos);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DM_NG_DEBUG ) */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_DM_NG_H__ */

/** @} */
