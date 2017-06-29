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
@brief  VSCP timer driver
@file   vscp_timer.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module implements the VSCP timers.

*******************************************************************************/
/** @defgroup vscp_timer Timer
 * The timer interface is used only by the core, except the processing function
 * vscp_timer_process(). Call the processing function to handle all created
 * timers. If the timers are handled in an interrupt service routine or a
 * different task, than the one which calls vscp_core_process(), don't forget
 * to make the timer functions reentrant.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TIMER_H__
#define __VSCP_TIMER_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <inttypes.h>
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
 * This function initializes the timer driver.
 */
extern void vscp_timer_init(void);

/**
 * This function creates a timer and returns its id.
 *
 * @return  Timer id
 * @retval  255     No timer resource available
 * @retval  0-254   Valid timer id
 */
extern uint8_t  vscp_timer_create(void);

/**
 * This function starts the timer of the given id.
 * If the timer is already running, it will be restart with the new value.
 *
 * @param[in]   id      Timer id
 * @param[in]   value   Time in ms
 */
extern void vscp_timer_start(uint8_t id, uint16_t value);

/**
 * This function stops a timer with the given id.
 *
 * @param[in]   id  Timer id
 */
extern void vscp_timer_stop(uint8_t id);

/**
 * This function get the status of a timer.
 *
 * @param[in]   id  Timer id
 * @return  Timer status
 * @retval  FALSE   Timer is stopped or timeout
 * @retval  TRUE    Timer is running
 */
extern BOOL vscp_timer_getStatus(uint8_t id);

/**
 * This function process all timers and has to be called cyclic.
 *
 * @param[in]   period  Period in ticks of calling this function.
 */
extern void vscp_timer_process(uint16_t period);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_TIMER_H__ */

/** @} */
