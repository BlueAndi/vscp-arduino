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
@brief  VSCP logger
@file   vscp_logger.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_logger.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_logger.h"
#include "vscp_core.h"
#include "vscp_class_l1.h"
#include "vscp_type_log.h"
#include "vscp_ps.h"

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

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

/** Logging enabled or not */
static BOOL     vscp_logger_isEnabled   = FALSE;

/** Current log level bitfield */
static uint8_t  vscp_logger_logLevel    = 0;

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the logger module.
 */
extern void vscp_logger_init(void)
{
    /* Nothing to do */

    return;
}

/**
 * This function enables/disables the logging, independent of CLASS1.Log.LogStart.
 */
extern void vscp_logger_enable(BOOL enableIt)
{
    vscp_logger_isEnabled = enableIt;
    return;
}

/**
 * This function gets the current log level(s).
 *
 * @return Current log level(s) (bitfield)
 */
extern uint8_t vscp_logger_getLogLevel(void)
{
    return vscp_logger_logLevel;
}

/**
 * This function sets the current log level(s).
 *
 * @param[in] level Log level(s) (bitfield)
 */
extern void vscp_logger_setLogLevel(uint8_t level)
{
    vscp_logger_logLevel = level;

    return;
}

/**
 * This function sends a log message, depended on the active log level.
 *
 * @param[in] id    Message id
 * @param[in] level Log level
 * @param[in] msg   Message
 * @param[in] size  Message size in bytes
 */
extern void vscp_logger_log(uint8_t id, VSCP_LOGGER_LVL level, uint8_t const * const msg, uint8_t size)
{
    if (TRUE == vscp_logger_isEnabled)
    {
        if (0 != (vscp_logger_logLevel & (1 << level)))
        {
            (void)vscp_logger_sendLogEvent(id, level, msg, size);
        }
    }

    return;
}

/**
 * This function sends a log message, depended on the active log level.
 *
 * @param[in] id    Message id
 * @param[in] level Log level
 * @param[in] value Value
 */
extern void vscp_logger_logUInt32(uint8_t id, VSCP_LOGGER_LVL level, uint32_t value)
{
    /* Value will be logged MSB first. */
    uint8_t buffer[4] = { ((uint8_t*)&value)[3], ((uint8_t*)&value)[2], ((uint8_t*)&value)[1], ((uint8_t*)&value)[0] };

    vscp_logger_log(id, level, buffer, sizeof(buffer));

    return;
}

/**
 * This function handles all CLASS1.Log events, which controls the logging functionality.
 * It will be called by the VSCP core.
 *
 * @param[in] msg   Received event message
 */
extern void vscp_logger_handleEvent(vscp_RxMessage const * const msg)
{
    if (NULL == msg)
    {
        return;
    }

    /* Handle only CLASS1.Log events */
    if (VSCP_CLASS_L1_LOG == msg->vscpClass)
    {
        /* Start logging? */
        if (VSCP_TYPE_LOG_LOG_START == msg->vscpType)
        {
            if (1 == msg->dataNum)
            {
                if (vscp_ps_readLogId() == msg->data[0])
                {
                    vscp_logger_isEnabled = TRUE;
                }
            }
        }
        /* Stop logging? */
        else if (VSCP_TYPE_LOG_LOG_STOP == msg->vscpType)
        {
            if (1 == msg->dataNum)
            {
                if (vscp_ps_readLogId() == msg->data[0])
                {
                    vscp_logger_isEnabled = FALSE;
                }
            }
        }
        /* Set log level? */
        else if (VSCP_TYPE_LOG_LOG_LEVEL == msg->vscpType)
        {
            if (1 == msg->dataNum)
            {
                vscp_logger_logLevel = msg->data[0];
            }
        }
        else
        {
            ;
        }
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

/**
 * Message for Log. Several frames have to be sent for a event that take up more the
 * five bytes which is the maximum for each frame. In this case the zero based index
 * (byte 2) should be increased for each frame.
 *
 * @param[in] id ID for event.
 * @param[in] level Log level for message.
 * @param[in] msg Message.
 * @param[in] size Message size in bytes.
 * @return Status
 * @retval FALSE Failed to send the event
 * @retval TRUE  Event successful sent
 *
 */
extern BOOL vscp_logger_sendLogEvent(uint8_t id, uint8_t level, uint8_t const * const msg, uint8_t size)
{
    vscp_TxMessage  txMsg;
    uint8_t         index       = 0;
    uint8_t         eventIndex  = 0;
    uint8_t         msgIndex    = 0;
    BOOL            status      = FALSE;

    vscp_core_prepareTxMessage(&txMsg, VSCP_CLASS_L1_LOG, VSCP_TYPE_LOG_LOG_EVENT, VSCP_PRIORITY_3_NORMAL);

    txMsg.dataNum = 8;
    txMsg.data[0] = id;
    txMsg.data[1] = level;

    /* If necessary, send several log events for a single log message. */
    do
    {
        /* Log event index, later needed to reassemble the log message */
        txMsg.data[2] = eventIndex;

        /* Defragment the log message */
        for(index = 3; index < VSCP_L1_DATA_SIZE; ++index)
        {
            if ((NULL != msg) &&
                (0 < size))
            {
                txMsg.data[index] = msg[msgIndex];
                ++msgIndex;
                --size;
            }
            /* Fill the rest of the log event with zeros. */
            else
            {
                txMsg.data[index] = 0;
            }
        }

        status = vscp_core_sendEvent(&txMsg);

        ++eventIndex;
    }
    while((NULL != msg) && (0 < size) && (TRUE == status));

    return status;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/
