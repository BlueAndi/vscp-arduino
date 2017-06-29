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
@brief  VSCP data coding
@file   vscp_data_coding.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module provides data coding functionality as specified by VSCP specification.

*******************************************************************************/
/** @defgroup vscp_data_coding VSCP data coding
 * Data coding functionality as specified by VSCP specification.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_DATA_CODING_H__
#define __VSCP_DATA_CODING_H__

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

/** This type defines the different representations, used in the format byte. */
typedef enum
{
    VSCP_DATA_CODING_REPRESENTATION_BIT = 0,            /**< The data should be represented as a set of bits. */
    VSCP_DATA_CODING_REPRESENTATION_BYTE,               /**< The data should be represented as a set of bytes. */
    VSCP_DATA_CODING_REPRESENTATION_STRING,             /**< The data should be represented as an ASCII numerical string */
    VSCP_DATA_CODING_REPRESENTATION_INTEGER,            /**< The data should be represented as a signed integer. */
    VSCP_DATA_CODING_REPRESENTATION_NORMALIZED_INTEGER, /**< Data is coded as a normalized integer. */
    VSCP_DATA_CODING_REPRESENTATION_FLOATING_POINT,     /**< Data is coded as a IEEE-754 1985 floating point value. */
    VSCP_DATA_CODING_REPRESENTATION_RESERVED_1,         /**< Reserved */
    VSCP_DATA_CODING_REPRESENTATION_RESERVED_2          /**< Reserved */

} VSCP_DATA_CODING_REPRESENTATION;

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the module.
 */
extern void vscp_data_coding_init(void);

/**
 * This function returns the format byte.
 *
 * @param[in]   representation  The data representation.
 * @param[in]   unit            The unit of the data.
 * @param[in]   index           Sensor index (optional)
 * @return Format byte
 */
extern uint8_t vscp_data_coding_getFormatByte(VSCP_DATA_CODING_REPRESENTATION representation, uint8_t unit, uint8_t index);

/**
 * This function returns the data in the normalized integer format.
 * Note, there is not format byte at the head of the coded data. This is
 * necessary to be able to use it e.g. for mesasurment with zone class.
 *
 * Examples:
 * -   11   => data =  11, exp = 0
 * -  -11   => data = -11, exp = 0
 * -    2.2 => data =  22, exp = -1
 * -   -2.2 => data = -22, exp = -1
 * -  330   => data =  33, exp = 1
 * - -330   => data = -33, exp = 1
 *
 * @param[in]       data            The data value
 * @param[in]       exp             The data exponent
 * @param[in,out]   codedData       The coded data array
 * @param[in]       codedDataSize   The size of the coded data array
 * @return Used coded data size
 */
extern uint8_t vscp_data_coding_int32ToNormalizedInteger(int32_t data, int8_t exp, uint8_t * const codedData, uint8_t codedDataSize);

/**
 * This function returns the normalized integer format in integer form.
 * Note, there is shall not be a format byte at the head of the coded data.
 *
 * @param[in,out]   codedData       The coded data array
 * @param[in]       codedDataSize   The size of the coded data array
 * @param[in]       data            The data value
 * @param[in]       exp             The data exponent
 */
extern void vscp_data_coding_normalizedIntegerToInt32(uint8_t const * const codedData, uint8_t codedDataSize, int32_t* const data, int8_t* const exp);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_DATA_CODING_H__ */

/** @} */
