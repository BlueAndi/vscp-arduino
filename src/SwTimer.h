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
@brief  Software timer class
@file   SwTimer.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module provides a software timer class, which handles the timer tick
overflow.

@section svn Subversion
$Author: amerkle $
$Rev: 449 $
$Date: 2015-01-05 20:23:52 +0100 (Mo, 05 Jan 2015) $
*******************************************************************************/
/** @defgroup SwTimer Software timer class
 * This module provides a software timer class, which handles the timer tick
 * overflow.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __SWTIMER_H__
#define __SWTIMER_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#if (100 <= ARDUINO)
#include "Arduino.h"
#else   /* (100 > ARDUINO) */
#include "WProgram.h"
#endif  /* (100 > ARDUINO) */

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
    CLASSES, TYPES AND STRUCTURES
*******************************************************************************/

/**
 * Software timer which handles the timer tick overflow.
 */
class SwTimer
{
public:

    /** Initialize and instantiate a software timer. */
    SwTimer() :
        mIsManualRestart(false),
        mTimeout(0),
        mValue(0),
        mTimerTicksPrev(0)
    {
    }
    
    /** Destroy a software timer instance. */
    ~SwTimer()
    {
    }
    
    /**
     * Starts a software timer.
     *
     * @param[in] timeout       Timeout in ms
     * @param[in] manualRestart Restart timer manually or automatically
     */
    void start(unsigned int timeout, bool manualRestart = false)
    {
        mIsManualRestart    = manualRestart;
        mTimeout            = timeout;
        mValue              = mTimeout;
        mTimerTicksPrev     = millis();
        return;
    }
    
    /**
     * Returns the timer timeout state.
     *
     * @return Timer timeout state
     * @retval false    No timeout
     * @retval true     Timeout
     */
    bool isTimeout(void)
    {
        bool    state   = false;
    
        if (0 == mValue)
        {
            state = true;
            
            /* Restart timer now? */
            if (false == mIsManualRestart)
            {
                restart();
            }
        }
        
        return state;
    }
    
    /**
     * Restarts the timer.
     */
    void restart(void)
    {
        mValue          = mTimeout;
        mTimerTicksPrev = millis();
    }

    /**
     * Process the timer.
     */
    void process(void)
    {
        if (0 < mValue)
        {
            unsigned long   timerTicks  = millis();
            unsigned long   diff        = 0;
            
            /* Timer overflow detected? */
            if (timerTicks < mTimerTicksPrev)
            {
                diff = ((unsigned long)(-1) - mTimerTicksPrev) + timerTicks;
            }
            /* No overflow */
            else
            {
                diff = timerTicks - mTimerTicksPrev;
            }
            
            if (diff < mValue)
            {
                mValue -= diff;
            }
            else
            {
                mValue = 0;
            }
                        
            mTimerTicksPrev = timerTicks;
        }
    
        return;
    }
    
private:

    bool            mIsManualRestart;   /**< Restart manual flag */
    unsigned int    mTimeout;           /**< Timeout value in ms */
    unsigned int    mValue;             /**< Current value in ms */
    unsigned long   mTimerTicksPrev;    /**< Previous timer ticks for overflow detection. */
    
};

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* __SWTIMER_H__ */

/** @} */
