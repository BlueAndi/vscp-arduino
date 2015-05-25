/* The MIT License (MIT)
 * 
 * Copyright (c) 2014 - 2015, Andreas Merkle
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
@brief  VSCP framework class
@file   VSCP.cpp
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see VSCP.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "VSCP.h"
#include "framework/vscp_core.h"
#include "framework/vscp_portable.h"
#include "framework/vscp_timer.h"
#include "framework/vscp_dev_data.h"
#include "framework/vscp_tp_adapter.h"
#include "framework/vscp_action.h"

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

/*******************************************************************************
    PROTOTYPES
*******************************************************************************/

/*******************************************************************************
    LOCAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

VSCP::VSCP() :
    mIsInitialized(false),                  /* Call setup() later */
    mStatusLampPin(0),                      /* Status Lamp pin */
    mInitButtonPin(0),                      /* Segment initialization button pin */
    mInitButton(),                          /* Default constructor init button debouncer */
    mLastInitButtonState(HIGH),             /* Last init button state */
    mStatusLampState(VSCP_LAMP_STATE_OFF),  /* Status lamp startup state is off */
    mStatusLampFastPeriod(250),             /* 250 ms fast status lamp blinking period */
    mStatusLampSlowPeriod(1000),            /* 1 s slow status lamp blinking period */
    mStatusLampTimer(),                     /* Status lamp timer for blinking */
    mVSCPTimerPeriod(250),                  /* 250 ms VSCP timer period */
    mVSCPTimer()                            /* Timer instance used to handle the VSCP framework timers */
{
    return;
}

VSCP::~VSCP()
{
    return;
}

void VSCP::setup(
    int             statusLampPin,
    int             initButtonPin,
    const VSCPGuid& guid, 
    unsigned char   zone,
    unsigned char   subZone,
    TpRead          tpReadFunc,
    TpWrite         tpWriteFunc,
    ExecuteAction   actionExecFunc)
{
    unsigned char           index   = 0;
    vscp_dev_data_Container devData;

    /* Configure the hardware */
    pinMode(statusLampPin, OUTPUT);
    pinMode(initButtonPin, INPUT_PULLUP);
    
    mStatusLampPin = statusLampPin;
    mInitButtonPin = initButtonPin;
    mInitButton.setup(mInitButtonPin);
       
    /* Initialize the VSCP core and the user specific stuff. */
    (void)vscp_core_init();
    
    /* Store device data */
    for(index = 0; index < VSCP_GUID_SIZE; ++index)
    {
        devData.guid[index] = guid[index];
    }
    devData.zone    = zone;
    devData.subZone = subZone;
    vscp_dev_data_set(&devData);
    
    /* Setup transport layer */
    vscp_tp_adapter_set(tpReadFunc, tpWriteFunc);
    
    /* Setup action */
    vscp_action_set(actionExecFunc);
    
    /* Start VSCP timer */
    mVSCPTimer.start(mVSCPTimerPeriod, false);
    
    /* Framework is now ready */
    mIsInitialized = true;
    
    return;
}

void VSCP::restoreFactoryDefaultSettings(void)
{
    if (true == mIsInitialized)
    {
        vscp_core_restoreFactoryDefaultSettings();
    }
    
    return;
}

void VSCP::process(void)
{
    if (true == mIsInitialized)
    {
        /* Process the whole framework */
        vscp_core_process();
        
        /* Process all member timers */
        mStatusLampTimer.process();
        mVSCPTimer.process();
        
        /* Process all VSCP framework timers */
        if (true == mVSCPTimer.isTimeout())
        {
            vscp_timer_process(mVSCPTimerPeriod);
        }
            
        /* Process the status lamp */
        processStatusLamp();
        
        /* Handle segment initialization button */
        if (LOW == mInitButton.read())
        {
            if (HIGH == mLastInitButtonState)
            {
                vscp_core_startNodeSegmentInit();
            }
            
            mLastInitButtonState = LOW;
        }
        else
        {
            mLastInitButtonState = HIGH;
        }
    }
    
    return;
}

uint8_t VSCP::readNicknameId(void)
{
    unsigned char   nicknameId  = VSCP_NICKNAME_NOT_INIT;
    
    if (true == mIsInitialized)
    {
        nicknameId = vscp_core_readNicknameId();
    }
    
    return nicknameId;
}

void VSCP::startNodeSegmentInit(void)
{
    if (true == mIsInitialized)
    {
        vscp_core_startNodeSegmentInit();
    }
    
    return;
}

void VSCP::setAlarm(unsigned char value)
{
    if (true == mIsInitialized)
    {
        vscp_core_setAlarm(value);
    }
    
    return;
}

bool VSCP::isActive(void)
{
    bool    status  = false;

    if (TRUE == mIsInitialized)
    {
        if (FALSE != vscp_core_isActive())
        {
            status = true;
        }
    }
    
    return status;
}

void VSCP::prepareTxMessage(vscp_TxMessage& txMessage, unsigned int vscpClass, unsigned char vscpType, VSCP_PRIORITY priority)
{
    vscp_core_prepareTxMessage(&txMessage, vscpClass, vscpType, priority);
    return;
}

bool VSCP::write(const vscp_TxMessage& txMessage)
{
    bool    status = false;

    if (TRUE == mIsInitialized)
    {
        status = vscp_core_sendEvent(&txMessage);
    }
    
    return status;
}

bool VSCP::read(vscp_RxMessage& msg)
{
    bool    status = false;

    if (TRUE == mIsInitialized)
    {
        status = vscp_portable_read(&msg);
    }
    
    return status;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

void VSCP::processStatusLamp(void)
{
    VSCP_LAMP_STATE     statusLampState     = vscp_portable_getLampState();
    
    /* Lamp state changed? */
    if (mStatusLampState != statusLampState)
    {
        mStatusLampState = statusLampState;
        
        
        
        switch(mStatusLampState)
        {
        case VSCP_LAMP_STATE_OFF:
            digitalWrite(mStatusLampPin, LOW);
            Serial.println("Off");
            break;

        case VSCP_LAMP_STATE_ON:
            digitalWrite(mStatusLampPin, HIGH);
            Serial.println("On");
            break;

        case VSCP_LAMP_STATE_BLINK_SLOW:
            mStatusLampTimer.start(mStatusLampSlowPeriod, false);
            Serial.println("Slow");
            break;

        case VSCP_LAMP_STATE_BLINK_FAST:
            mStatusLampTimer.start(mStatusLampFastPeriod, false);
            Serial.println("Fast");
            break;

        default:
            break;
        }
    }
    /* Shall the lamp blink? */
    else if ((VSCP_LAMP_STATE_BLINK_SLOW == mStatusLampState) ||
             (VSCP_LAMP_STATE_BLINK_FAST == mStatusLampState))
    {
        /* Toggle status lamp? */
        if (true == mStatusLampTimer.isTimeout())
        {
            int statusLampPinState = digitalRead(mStatusLampPin);
            
            if (LOW == statusLampPinState)
            {
                statusLampPinState = HIGH;
            }
            else
            {
                statusLampPinState = LOW;
            }
        
            digitalWrite(mStatusLampPin, statusLampPinState);
        }
    }
    
    return;
}
