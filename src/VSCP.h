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
@brief  VSCP framework class
@file   VSCP.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module provides a C++ wrapper for the VSCP framework.

*******************************************************************************/
/** @defgroup vscpFramework VSCP framework class
 * C++ wrapper for the VSCP framework.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_H__
#define __VSCP_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#if (100 <= ARDUINO)
#include "Arduino.h"
#else   /* (100 > ARDUINO) */
#include "WProgram.h"
#endif  /* (100 > ARDUINO) */

#include "DigInDebounce.h"
#include "SwTimer.h"
#include "framework/user/vscp_platform.h"
#include "framework/core/vscp_types.h"

#include "framework/core/vscp_class_l1.h"
#include "framework/core/vscp_class_l1_l2.h"
#include "framework/core/vscp_type_alarm.h"
#include "framework/core/vscp_type_control.h"
#include "framework/core/vscp_type_display.h"
#include "framework/core/vscp_type_information.h"
#include "framework/core/vscp_type_log.h"
#include "framework/core/vscp_type_measurement.h"
#include "framework/core/vscp_type_measurezone.h"
#include "framework/core/vscp_type_phone.h"
#include "framework/core/vscp_type_remote.h"
#include "framework/core/vscp_type_security.h"
#include "framework/core/vscp_type_weather.h"
#include "framework/core/vscp_type_weather_forecast.h"

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

/** VSCP node GUID - a unique identifier */
typedef unsigned char VSCPGuid[VSCP_GUID_SIZE];

/** VSCP framework class */
class VSCP
{
public:

    /** This type defines the transport receive function. */
    typedef bool (*TpRead)(vscp_RxMessage * const rxMsg);
    
    /** This type defines the transport transmit function. */
    typedef bool (*TpWrite)(vscp_TxMessage const * const txMsg);
    
    /** This type defines the action execution function. */
    typedef void (*ExecuteAction)(unsigned char action, unsigned char par, vscp_RxMessage const * const msg);

    /**
     * Create a VSCP framework instance.
     */
    VSCP();

    /**
     * Destroys a VSCP framework instance.
     */
    ~VSCP();
    
    /**
     * Initializes a VSCP framework instance.
     *
     * @param[in]   statusLampPin   Pin of the status lamp
     * @param[in]   initButtonPin   Pin of the init button
     * @param[in]   guid            Node GUID
     * @param[in]   zone            Node zone
     * @param[in]   subZone         Node sub-zone
     * @param[in]   tpReadFunc      Transport layer read function
     * @param[in]   tpWriteFunc     Transport layer write function
     * @param[in]   actionExecFunc  Action execution function
     */
    void setup(
        int             statusLampPin,
        int             initButtonPin,
        const VSCPGuid& guid,
        unsigned char   zone,
        unsigned char   subZone,
        TpRead          tpReadFunc,
        TpWrite         tpWriteFunc,
        ExecuteAction   actionExecFunc);
    
    /**
     * This method restores VSCP default values for
     * - all registers,
     * - the persistent memory,
     * - internal variables.
     *
     * In other words, it restore factory defaults settings.
     */
    void restoreFactoryDefaultSettings(void);

    /**
     * This method process the whole VSCP core stack. Call it in a user defined
     * cyclic period.
     */
    void process(void);

    /**
     * This method reads the nickname id of the node.
     *
     * @return  Nickname id
     */
    uint8_t readNicknameId(void);

    /**
     * This method starts the node segment initialization.
     */
    void startNodeSegmentInit(void);

    /**
     * This method set one or more alarm status.
     * How the bits are read, is application specific.
     * Note that a active alarm (bit is set) can only be cleared by reading the
     * alarm register. Calling this method with 0, do nothing.
     *
     * @param[in]   value   New alarm status
     */
    void setAlarm(unsigned char value);

    /**
     * This method determines the state of VSCP and if it is in active state,
     * it will return true, otherwise false.
     *
     * @return  Is VSCP active or not?
     * @retval  false   Not in active state
     * @retval  true    In active state
     */
    bool isActive(void);
    
    /**
     * Prepares a transmit message, before it is used.
     *
     * Default values:
     * - Nodes nickname
     * - Hard coded node flag
     * - No data
     *
     * After preparation, only the data and the number of data bytes has to be
     * modified additionally.
     *
     * @param[in,out]   txMessage   Transmit message which will be prepared.
     * @param[in]       vscpClass   Transmit message VSCP class
     * @param[in]       vscpType    Transmit message VSCP type
     * @param[in]       priority    Transmit message priority
     */
    void prepareTxMessage(vscp_TxMessage& txMessage, unsigned int vscpClass, unsigned char vscpType, VSCP_PRIORITY priority);

    /**
     * Send a event to the communication bus. Don't forget to prepare your transmit
     * message (@see vscp_core_prepareTxMessage) first and then modify for your needs,
     * before sending it!
     *
     * @param[in]   txMessage   The event which will be sent.
     * @return Status
     * @retval FALSE    Failed to send the event.
     * @retval TRUE     Event successful sent.
     */
    bool write(const vscp_TxMessage& txMessage);
    
    /**
     * This method reads a VSCP message.
     * If no message is available it returns false otherwise true.
     *
     * @param[out]  msg Received message
     * @return Anything read or not
     */
    bool read(vscp_RxMessage& msg);
    
private:

    /* Never copy the VSCP framework */
    VSCP(const VSCP& vscp);

    /* Never copy the VSCP framework */
    VSCP& operator=(const VSCP& vscp);
    
    bool                mIsInitialized;         /**< Is framework initialized or not */
    
    int                 mStatusLampPin;         /**< Status lamp pin */
    int                 mInitButtonPin;         /**< Segment initialization button pin */
    DigInDebounce       mInitButton;            /**< Debounced init button state */
    int                 mLastInitButtonState;   /**< Last init button state */
        
    VSCP_LAMP_STATE     mStatusLampState;       /**< Current state of the status lamp */
    const unsigned int  mStatusLampFastPeriod;  /**< Fast status lamp blinking periode in ms */
    const unsigned int  mStatusLampSlowPeriod;  /**< Slow status lamp blinking periode in ms */
    SwTimer             mStatusLampTimer;       /**< Status lamp timer used for blinking */
    
    const unsigned int  mVSCPTimerPeriod;       /**< VSCP timer period in ms */
    SwTimer             mVSCPTimer;             /**< VSCP timer */
        
    /**
     * Process the status lamp.
     */
    void processStatusLamp(void);
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

#endif  /* __VSCP_H__ */

/** @} */
