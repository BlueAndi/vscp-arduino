/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2020, Andreas Merkle
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
@brief  Phone
@file   vscp_evt_phone.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This class is for phone related functionality.

This file is automatically generated. Don't change it manually.

*******************************************************************************/

#ifndef __VSCP_EVT_PHONE_H__
#define __VSCP_EVT_PHONE_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "..\user\vscp_platform.h"

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
 * General event
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendGeneralEvent(void);

/**
 * Incoming call
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * @param[in] index Index of phone event (base = 0). Each call can be broken up into fragments. This
 * is the fragment number.
 * @param[in] total Total number of events (fragments) for this call information.
 * @param[in] info Caller information. Number or real text information. (array[5])
 * @param[in] infosize Size in byte.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendIncomingCall(uint8_t id, uint8_t index, uint8_t total, uint8_t const * const info, uint8_t infoSize);

/**
 * Incoming call
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * @param[in] index Index of phone event (base = 0). Each call can be broken up into fragments. This
 * is the fragment number.
 * @param[in] total Total number of events (fragments) for this call information.
 * @param[in] info Caller information. Number or real text information. (array[5])
 * @param[in] infosize Size in byte.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendOutgoingCall(uint8_t id, uint8_t index, uint8_t total, uint8_t const * const info, uint8_t infoSize);

/**
 * Ring
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendRing(uint8_t id);

/**
 * Incoming call
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * @param[in] index Index of phone event (base = 0). Each call can be broken up into fragments. This
 * is the fragment number.
 * @param[in] total Total number of events (fragments) for this call information.
 * @param[in] info Caller information. Number or real text information. (array[5])
 * @param[in] infosize Size in byte.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendAnswer(uint8_t id, uint8_t index, uint8_t total, uint8_t const * const info, uint8_t infoSize);

/**
 * Ring
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendHangup(uint8_t id);

/**
 * Ring
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendGiveup(uint8_t id);

/**
 * Ring
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendTransfer(uint8_t id);

/**
 * Incoming call
 * 
 * @param[in] id Id for the call. This is an incremental identity number for each call.
 * @param[in] index Index of phone event (base = 0). Each call can be broken up into fragments. This
 * is the fragment number.
 * @param[in] total Total number of events (fragments) for this call information.
 * @param[in] info Caller information. Number or real text information. (array[5])
 * @param[in] infosize Size in byte.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_phone_sendDatabaseInfo(uint8_t id, uint8_t index, uint8_t total, uint8_t const * const info, uint8_t infoSize);

#endif  /* __VSCP_EVT_PHONE_H__ */