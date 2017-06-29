/*
 * The MIT License (MIT)
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
@file   vscp_util.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module provides utility functions, which are used in different VSCP
framework modules.

*******************************************************************************/
/** @defgroup vscp_util VSCP utilities
 * Utility functions, which are used in different VSCP framework modules.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_UTIL_H__
#define __VSCP_UTIL_H__

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

/** Mark unused variables with this macro. */
#define VSCP_UTIL_UNUSED(__var)                 do{ (void)(__var); }while(0)

/** Get number of elements in a array. */
#define VSCP_UTIL_ARRAY_NUM(__array)            (sizeof(__array) / sizeof((__array)[0]))

/** Use this macro for a compile time assertion. */
#define VSCP_UTIL_COMPILE_TIME_ASSERT(__expr)   typedef char COMP_TIME_ASSERT[(__expr) ? 1 : -1]

/** MSB of a word */
#define VSCP_UTIL_WORD_MSB(__word)              ((uint8_t)(((__word) >> 8) & 0xff))

/** LSB of a word */
#define VSCP_UTIL_WORD_LSB(__word)              ((uint8_t)(((__word) >> 0) & 0xff))

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** This type defines a cyclic buffer context. */
typedef struct
{
    void    *storage;   /**< Storage of elements */
    uint8_t elemSize;   /**< Element size */
    uint8_t num;        /**< Number of elements in the storage */
    uint8_t readIndex;  /**< Read index */
    uint8_t writeIndex; /**< Write index */

} vscp_util_CyclicBuffer;

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the utility module.
 */
extern void vscp_util_init(void);

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
extern uint8_t  vscp_util_getZoneIndex(uint16_t vscpClass, uint8_t vscpType);

/**
 * This function initializes a cyclic buffer.
 *
 * @param[in,out]   cbuffer     Cyclic buffer context
 * @param[in]       storage     Storage of all elements in the cyclic buffer
 * @param[in]       size        Storage size in byte
 * @param[in]       elemSize    Size of a single element in byte
 */
extern void vscp_util_cyclicBufferInit(vscp_util_CyclicBuffer * const cbuffer, void * const storage, uint8_t size, uint8_t elemSize);

/**
 * This function reads one or more elements from a cyclic buffer.
 *
 * @param[in,out]   cbuffer     Cyclic buffer context
 * @param[in]       elem        Element buffer (one ore more elements)
 * @param[in]       maxNum      Max. number of elements to read
 * @return Number of read elements
 */
extern uint8_t vscp_util_cyclicBufferRead(vscp_util_CyclicBuffer * const cbuffer, void * const elem, uint8_t maxNum);

/**
 * This function writes one or more elements to a cyclic buffer.
 *
 * @param[in,out]   cbuffer     Cyclic buffer context
 * @param[in]       elem        Element buffer (one ore more elements)
 * @param[in]       maxNum      Max. number of elements to write
 * @return Number of written elements
 */
extern uint8_t vscp_util_cyclicBufferWrite(vscp_util_CyclicBuffer * const cbuffer, void const * const elem, uint8_t maxNum);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_UTIL_H__ */

/** @} */
