/* The MIT License (MIT)
 * 
 * Copyright (c) 2014 - 2021, Andreas Merkle
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
@brief  Digital input debounce class
@file   DigInDebounce.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module provides a class for debouncing ditial in.

*******************************************************************************/
/** @defgroup DigInDebounce Digital input debounce class
 * This module provides a class for debouncing ditial in.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __DIGINDEBOUNCE_H__
#define __DIGINDEBOUNCE_H__

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
 * Digital in debouncing
 */
class DigInDebounce
{
public:

    /** Initialize and instantiate a digital in debouncer.
     *
     * @param[in] pin   Digital input pin
     */
    DigInDebounce(int pin = 0) :
        mPin(pin),
        mState(HIGH),
        mLastReadState(HIGH),
        mLastDebounceTime(0),
        mcDebounceDelay(50)
    {
    }
        
    /** Destroy a digital in debouncer instance. */
    ~DigInDebounce()
    {
    }
    
    /**
     * Setup digital input pin.
     */
    void setup(int pin)
    {
        mPin = pin;
        
        mState = digitalRead(mPin);
        mLastReadState = mState;
        
        return;
    }
    
    /**
     * Returns the digital input state.
     */
    int read(void)
    {
        int readState = digitalRead(mPin);
        
        if (readState != mLastReadState)
        {
            mLastDebounceTime = millis();
        }
        else if ((millis() - mLastDebounceTime) > mcDebounceDelay)
        {
            if (readState != mState)
            {
                mState = readState;
            }
        }
        
        mLastReadState = readState;
        
        return mState;
    }
    
private:

    int             mPin;               /**< Pin number */
    int             mState;             /**< Current digital in state */
    int             mLastReadState;     /**< Last read digital in state */
    unsigned long   mLastDebounceTime;  /**< Last time the digital in state changed */
    
    const unsigned long mcDebounceDelay;    /**< Debounce delay */
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

#endif  /* __DIGINDEBOUNCE_H__ */

/** @} */
