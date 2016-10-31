/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2016, Andreas Merkle
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
@file   vscp_transport.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_transport.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_transport.h"
#include "vscp_tp_adapter.h"
#include "vscp_config.h"
#include "vscp_util.h"
#include "vscp_class_l1.h"

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

/** Transmit error counter, counts every message, which couldn't be sent. */
static uint8_t                  vscp_txErrorCnt = 0;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK )

/** Cyclic buffer instance for VSCP event loopback. */
static vscp_util_CyclicBuffer   vscp_transport_loopBackCyclicBuffer;

/** Message storage of the cyclic buffer, used for loopback VSCP events. */
static vscp_Message             vscp_transport_loopBackStorage[VSCP_CONFIG_LOOPBACK_STORAGE_NUM];

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK ) */

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the transport layer.
 */
extern void vscp_transport_init(void)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK )

    /* Initialize the cyclic buffer for the VSCP event loopback */
    vscp_util_cyclicBufferInit( &vscp_transport_loopBackCyclicBuffer,
                                &vscp_transport_loopBackStorage,
                                sizeof(vscp_transport_loopBackStorage),
                                sizeof(vscp_transport_loopBackStorage[0]));

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK ) */

    /* Initialize transport layer adapter */
    vscp_tp_adapter_init();

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
extern BOOL vscp_transport_readMessage(vscp_RxMessage * const msg)
{
    BOOL    status  = FALSE;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK )

    if (NULL != msg)
    {
        /* The loopback works as FIFO (first in, first out).
         * A easy way would be to write now a received message to the loopback.
         * Read from the loopback and provide it to the upper layer.
         * This would cause three copy operations:
         * 1. Copy from lower layer to msg.
         * 2. Copy from msg to loopback.
         * 3. Copy from loopback to msg.
         *
         * In the case that the loopback is empty, this can be reduced to only
         * one copy operation, which is implemented below.
         */

        /* Read message from loopback */
        uint8_t read = vscp_util_cyclicBufferRead(&vscp_transport_loopBackCyclicBuffer, msg, 1);

        /* Read a message? */
        if (0 < read)
        {
            /* Write any received message from the lower layer to the loopback. */
            vscp_RxMessage  rxMsg;
            BOOL            received = vscp_tp_adapter_readMessage(&rxMsg);

            if (TRUE == received)
            {
                (void)vscp_util_cyclicBufferWrite(&vscp_transport_loopBackCyclicBuffer, &rxMsg, 1);
            }

            status = TRUE;
        }
        else
        /* No message in the loopback, maybe one is received from lower layer. */
        {
            status = vscp_tp_adapter_readMessage(msg);
        }

    }

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOOPBACK ) */

    status = vscp_tp_adapter_readMessage(msg);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOOPBACK ) */

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
extern BOOL vscp_transport_writeMessage(vscp_TxMessage const * const msg)
{
    BOOL    status  = FALSE;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOOPBACK )

    if ((NULL != msg) &&                        /* Message shall exists */
        (VSCP_L1_DATA_SIZE >= msg->dataNum))    /* Number of data bytes is limited */
    {
        /* Write all messages to loopback, except:
         * - CLASS1.PROTOCOL: The core would interpret them.
         * - CLASS1.LOG     : Make no sense.
         */
        if ((VSCP_CLASS_L1_PROTOCOL != msg->vscpClass) &&
            (VSCP_CLASS_L1_LOG != msg->vscpClass))
        {
            (void)vscp_util_cyclicBufferWrite(&vscp_transport_loopBackCyclicBuffer, msg, 1);
        }

        status = vscp_tp_adapter_writeMessage(msg);
    }

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOOPBACK ) */

    status = vscp_tp_adapter_writeMessage(msg);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOOPBACK ) */

    /* Count every transmit error */
    if (FALSE == status)
    {
        if (255 > vscp_txErrorCnt)
        {
            ++vscp_txErrorCnt;
        }
    }

    return status;
}

/**
 * This function returns the number of transmit errors.
 * Note, that calling this function clears the transmit error counter.
 *
 * @return Number of transmit errors
 */
extern uint8_t  vscp_transport_getTransmitErrors(void)
{
    uint8_t num = vscp_txErrorCnt;

    vscp_txErrorCnt = 0;

    return num;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/
