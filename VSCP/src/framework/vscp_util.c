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
@brief  VSCP utilities
@file   vscp_util.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_util.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_util.h"

#include "vscp_class_l1.h"
#include "vscp_type_protocol.h"
#include "vscp_type_information.h"
#include "vscp_type_control.h"
#include "vscp_type_phone.h"
#include "vscp_type_display.h"
#include "vscp_type_remote.h"

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

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the utility module.
 */
extern void vscp_util_init(void)
{
    /* Nothing to do */

    return;
}

/**
 * Get the index in the message data of the zone.
 * Note, sub zone index = zone index + 1
 *
 * This function is only necessary, because some VSCP events has the zone/sub-zone
 * at a different location in their data payload.
 *
 * @param[in]   vscpClass   VSCP class
 * @param[in]   vscpType    VSCP type
 *
 * @return Zone index in the message data
 */
extern uint8_t  vscp_util_getZoneIndex(uint16_t vscpClass, uint8_t vscpType)
{
    uint8_t zoneIndex   = 0xFF;

    /* In general every type 0, independent from class, has no zone information. */
    if (0 < vscpType)
    {
        switch(vscpClass)
        {
        case VSCP_CLASS_L1_ALARM:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_SECURITY:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_ALERT_ON_LAN:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_MEASUREZONE:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_SET_VALUE_WITH_ZONE:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_WEATHER:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_WEATHER_FORECAST:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_DIAGNOSTIC:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_ERROR:
            zoneIndex = 1;
            break;

        case VSCP_CLASS_L1_INFORMATION:
            if ((VSCP_TYPE_INFORMATION_STREAM_DATA_WITH_ZONE == vscpType) ||
                (VSCP_TYPE_INFORMATION_CONFIRM == vscpType))
            {
                zoneIndex = 0;
            }
            else if (VSCP_TYPE_INFORMATION_STREAM_DATA != vscpType)
            {
                zoneIndex = 1;
            }
            break;

        case VSCP_CLASS_L1_CONTROL:
            if ((VSCP_TYPE_CONTROL_DEACTIVATE >= vscpType) ||
                (
                    (VSCP_TYPE_CONTROL_DIM_LAMP <= vscpType) &&
                    (VSCP_TYPE_CONTROL_STREAM_DATA != vscpType)
                ))
            {
                zoneIndex = 1;
            }
            break;

        case VSCP_CLASS_L1_PHONE:
            if (VSCP_TYPE_PHONE_ANSWER == vscpType)
            {
                zoneIndex = 1;
            }
            break;

        case VSCP_CLASS_L1_DISPLAY:
            if (VSCP_TYPE_DISPLAY_SET_DISPLAY_BUFFER_PARAMETER != vscpType)
            {
                zoneIndex = 1;
            }
            break;

        case VSCP_CLASS_L1_REMOTE:
            if ((VSCP_TYPE_REMOTE_VSCP_ABSTRACT == vscpType) ||
                (VSCP_TYPE_REMOTE_MAPITO == vscpType))
            {
                zoneIndex = 1;
            }
            break;

        /* The following ones doesn't have any type with zone/sub-zone. */
        case VSCP_CLASS_L1_MEASUREMENT:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_DATA:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_MEASUREMENT_DOUBLE:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_MEASUREMENT_SINGLE:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_GPS:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_WIRELESS:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_LOG:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_LABORATORY:
            /*@fallthrough@*/
        case VSCP_CLASS_L1_LOCAL:
            /*@fallthrough@*/
        default:
            break;
        }
    }

    return zoneIndex;
}

/**
 * This function initializes a cyclic buffer.
 *
 * @param[in,out]   cbuffer     Cyclic buffer context
 * @param[in]       storage     Storage of all elements in the cyclic buffer
 * @param[in]       size        Storage size in byte
 * @param[in]       elemSize    Size of a single element in byte
 */
extern void vscp_util_cyclicBufferInit(vscp_util_CyclicBuffer * const cbuffer, void * const storage, uint8_t size, uint8_t elemSize)
{
    if (NULL != cbuffer)
    {
        cbuffer->storage    = storage;
        cbuffer->elemSize   = elemSize;
        cbuffer->num        = size / elemSize;
        cbuffer->readIndex  = 0;
        cbuffer->writeIndex = 0;
    }

    return;
}

/**
 * This function reads one or more elements from a cyclic buffer.
 *
 * @param[in,out]   cbuffer     Cyclic buffer context
 * @param[in]       elem        Element buffer (one ore more elements)
 * @param[in]       maxNum      Max. number of elements to read
 * @return Number of read elements
 */
extern uint8_t vscp_util_cyclicBufferRead(vscp_util_CyclicBuffer * const cbuffer, void * const elem, uint8_t maxNum)
{
    uint8_t read    = 0;

    if ((NULL != cbuffer) &&
        (NULL != elem) &&
        (0 < maxNum))
    {
        uint8_t *src    = &((uint8_t*)cbuffer->storage)[cbuffer->readIndex * cbuffer->elemSize];
        uint8_t *dst    = &((uint8_t*)elem)[0];

        /* Any element in the cyclic buffer empty?
         * And given buffer not full?
         */
        while((cbuffer->readIndex != cbuffer->writeIndex) && (maxNum > read))
        {
            uint8_t index           = 0;
            uint8_t nextReadIndex   = (cbuffer->readIndex + 1) % cbuffer->num;

            /* Copy a single element */
            for(index = 0; index < cbuffer->elemSize; ++index)
            {
                dst[index] = src[index];
            }

            cbuffer->readIndex  = nextReadIndex;
            src                 = &src[cbuffer->elemSize];
            dst                 = &dst[cbuffer->elemSize];
            ++read;
        }
    }

    return read;
}

/**
 * This function writes one or more elements to a cyclic buffer.
 *
 * @param[in,out]   cbuffer     Cyclic buffer context
 * @param[in]       elem        Element buffer (one ore more elements)
 * @param[in]       maxNum      Max. number of elements to write
 * @return Number of written elements
 */
extern uint8_t vscp_util_cyclicBufferWrite(vscp_util_CyclicBuffer * const cbuffer, void const * const elem, uint8_t maxNum)
{
    uint8_t written         = 0;

    if ((NULL != cbuffer) &&
        (NULL != elem) &&
        (0 < maxNum))
    {
        uint8_t nextWriteIndex   = (cbuffer->writeIndex + 1) % cbuffer->num;
        uint8_t *src            = &((uint8_t*)elem)[0];
        uint8_t *dst            = &((uint8_t*)cbuffer->storage)[cbuffer->writeIndex * cbuffer->elemSize];

        /* Cyclic buffer not full?
         * Any element in the given buffer?
         */
        while((cbuffer->readIndex != nextWriteIndex) && (maxNum > written))
        {
            uint8_t index   = 0;

            /* Copy a single element */
            for(index = 0; index < cbuffer->elemSize; ++index)
            {
                dst[index] = src[index];
            }

            cbuffer->writeIndex = nextWriteIndex;
            nextWriteIndex      = (nextWriteIndex + 1) % cbuffer->num;
            src                 = &src[cbuffer->elemSize];
            dst                 = &dst[cbuffer->elemSize];
            ++written;
        }
    }

    return written;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/
