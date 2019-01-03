/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2019, Andreas Merkle
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
@brief  VSCP timer layer
@file   vscp_timer.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_timer.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_timer.h"
#include "vscp_util.h"
#include "vscp_config.h"
#include <string.h>

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE )

/** Number of provided timers */
#define VSCP_TIMER_NUM  5

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

/** Number of provided timers */
#define VSCP_TIMER_NUM  4

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** This type defines a timer context with all its internal parameters. */
typedef struct
{
    uint8_t     id;     /**< Timer id (0xFF means this timer is available) */
    uint16_t    value;  /**< Timer counter value */

} vscp_timer_Timer;

/*******************************************************************************
    PROTOTYPES
*******************************************************************************/

/*******************************************************************************
    LOCAL VARIABLES
*******************************************************************************/

/** Timers */
static vscp_timer_Timer vscp_timer_context[VSCP_TIMER_NUM];

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the timer driver.
 */
extern void vscp_timer_init(void)
{
    uint8_t index   = 0;
    
    /* Reset all timers */
    memset(vscp_timer_context, 0, sizeof(vscp_timer_context));
    
    for(index = 0; index < VSCP_TIMER_NUM; ++index)
    {
        vscp_timer_context[index].id = VSCP_TIMER_ID_INVALID;
    }
    
    return;
}

/**
 * This function creates a timer and returns its id.
 *
 * @return  Timer id
 * @retval  255     No timer resource available
 * @retval  0-254   Valid timer id
 */
extern uint8_t  vscp_timer_create(void)
{
    uint8_t timerId = VSCP_TIMER_ID_INVALID;
    uint8_t index   = 0;

    /* Search for an available timer */
    for(index = 0; index < VSCP_TIMER_NUM; ++index)
    {
        /* Is the timer available? */
        if (VSCP_TIMER_ID_INVALID == vscp_timer_context[index].id)
        {
            /* Mark the timer as used */
            vscp_timer_context[index].id    = index;
            timerId                         = vscp_timer_context[index].id;
            
            break;
        }
    }

    return timerId;
}

/**
 * This function starts the timer of the given id.
 * If the timer is already running, it will be restart with the new value.
 *
 * @param[in]   id      Timer id
 * @param[in]   value   Time in ms
 */
extern void vscp_timer_start(uint8_t id, uint16_t value)
{
    if (VSCP_UTIL_ARRAY_NUM(vscp_timer_context) > id)
    {
        vscp_timer_context[id].value = value;
    }

    return;
}

/**
 * This function stops a timer with the given id.
 *
 * @param[in]   id  Timer id
 */
extern void vscp_timer_stop(uint8_t id)
{
    if (VSCP_UTIL_ARRAY_NUM(vscp_timer_context) > id)
    {
        vscp_timer_context[id].value = 0;
    }

    return;
}

/**
 * This function get the status of a timer.
 *
 * @param[in]   id  Timer id
 * @return  Timer status
 * @retval  FALSE   Timer is stopped or timeout
 * @retval  TRUE    Timer is running
 */
extern BOOL vscp_timer_getStatus(uint8_t id)
{
    BOOL    status  = FALSE;
    
    if (VSCP_UTIL_ARRAY_NUM(vscp_timer_context) > id)
    {
        if (0 < vscp_timer_context[id].value)
        {
            status = TRUE;
        }
    }

    return status;
}

/**
 * This function process all timers and has to be called cyclic.
 *
 * @param[in]   period  Period in ticks of calling this function.
 */
extern void vscp_timer_process(uint16_t period)
{
    uint8_t index   = 0;

    /* Process all timers */
    for(index = 0; index < VSCP_TIMER_NUM; ++index)
    {
        /* Is the timer enabled? */
        if (VSCP_TIMER_ID_INVALID != vscp_timer_context[index].id)
        {
            if (period <= vscp_timer_context[index].value)
            {
                vscp_timer_context[index].value -= period;
            }
            else
            {
                vscp_timer_context[index].value = 0;
            }
        }
    }

    return;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

