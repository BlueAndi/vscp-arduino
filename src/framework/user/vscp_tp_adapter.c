/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2024 Andreas Merkle
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
@brief  VSCP transport layer adapter
@file   vscp_tp_adapter.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_tp_adapter.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_tp_adapter.h"

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

/** Receive callback */
static vscp_tp_adapter_Read     vscp_tp_adapter_readFunc    = NULL;

/** Transmit callback */
static vscp_tp_adapter_Write    vscp_tp_adapter_writeFunc   = NULL;

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the transport layer.
 */
extern void vscp_tp_adapter_init(void)
{
    /* Nothing to do */
    
    return;
}

/**
 * This function set the transport layer callbacks.
 *
 * @param[in]   read    Receive callback
 * @param[in]   write   Transmit callback
 */
extern void vscp_tp_adapter_set(vscp_tp_adapter_Read read, vscp_tp_adapter_Write write)
{
    vscp_tp_adapter_readFunc    = read;
    vscp_tp_adapter_writeFunc   = write;

    return;
}

/**
 * This function reads a message from the transport layer.
 *
 * @param[out]  msg Message storage
 * @return  Message received or not
 * @retval  FALSE   No message received
 * @retval  TRUE    Message received
 */
extern BOOL vscp_tp_adapter_readMessage(vscp_RxMessage * const msg)
{
    BOOL    status  = FALSE;

    if (NULL != msg)
    {
        if (NULL != vscp_tp_adapter_readFunc)
        {
            status = vscp_tp_adapter_readFunc(msg);
        }
    }

    return status;
}

/**
 * This function writes a message to the transport layer.
 *
 * @param[in]   msg Message storage
 * @return  Message sent or not
 * @retval  FALSE   Couldn't send message
 * @retval  TRUE    Message successful sent
 */
extern BOOL vscp_tp_adapter_writeMessage(vscp_TxMessage const * const msg)
{
    BOOL    status  = FALSE;

    if ((NULL != msg) &&                        /* Message shall exists */
        (VSCP_L1_DATA_SIZE >= msg->dataSize))   /* Number of data bytes is limited */
    {
        if (NULL != vscp_tp_adapter_writeFunc)
        {
            status = vscp_tp_adapter_writeFunc(msg);
        }
    }

    return status;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

