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
@brief  VSCP transport layer
@file   vscp_transport.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module handles the transport of the VSCP.

*******************************************************************************/
/** @defgroup vscp_transport Transport layer
 * The transport layer adapts VSCP to the underlying physical transport medium,
 * e.g. CAN.
 *
 * In case of receiving a message, the core reads only one message from the
 * transport layer per process call and handle it complete. If more than one
 * message are received, the transport layer has to implement some kind of
 * buffer mechanism.
 *
 * In case of transmitting a message, the core can write several messages to
 * the transport layer, in one processing cycle. If the transport layer can't
 * send a message, in some cases the core will get into trouble, because right
 * now now fall-back mechanism exists.
 *
 * Supported compile switches:
 * - VSCP_CONFIG_ENABLE_LOOPBACK
 *
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TRANSPORT_H__
#define __VSCP_TRANSPORT_H__

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
 * This function initializes the transport layer.
 */
extern void vscp_transport_init(void);

/**
 * This function reads a message from the transport layer.
 *
 * @param[out]  msg Message storage
 * @return  Message received or not
 * @retval  FALSE   No message received
 * @retval  TRUE    Message received
 */
extern BOOL vscp_transport_readMessage(vscp_RxMessage * const msg);

/**
 * This function writes a message to the transport layer.
 *
 * @param[in]   msg Message storage
 * @return  Message sent or not
 * @retval  FALSE   Couldn't send message
 * @retval  TRUE    Message successful sent
 */
extern BOOL vscp_transport_writeMessage(vscp_TxMessage const * const msg);

/**
 * This function returns the number of transmit errors.
 * Note, that calling this function clears the transmit error counter.
 *
 * @return Number of transmit errors
 */
extern uint8_t  vscp_transport_getTransmitErrors(void);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_TRANSPORT_H__ */

/** @} */
