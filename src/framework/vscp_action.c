/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2018, Andreas Merkle
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
@brief  VSCP actions
@file   vscp_action.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_action.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_action.h"

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) || VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

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
    PROTOTYPES
*******************************************************************************/

/*******************************************************************************
    LOCAL VARIABLES
*******************************************************************************/

/** Action execution function */
static vscp_action_Execute  vscp_action_executeFunc = NULL;

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the module.
 */
extern void vscp_action_init(void)
{
    /* Implement your code here ... */

    return;
}

/**
 * This function executes a action with the given parameter.
 *
 * @param[in]   action  Action id
 * @param[in]   par     Action parameter
 * @param[in]   msg     Received VSCP message which triggered the action
 */
extern void vscp_action_execute(uint8_t action, uint8_t par, vscp_RxMessage const * const msg)
{
    if (NULL != vscp_action_executeFunc)
    {
        vscp_action_executeFunc(action, par, msg);
    }

    return;
}

/**
 * This function set the action execution callback.
 *
 * @param[in] func  Action execution function
 */
extern void vscp_action_set(vscp_action_Execute func)
{
    vscp_action_executeFunc = func;
    return;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) || VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */
