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
@file   vscp_data_coding.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_data_coding.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_data_coding.h"

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

static inline uint8_t vscp_data_coding_getNormalizerByte(uint8_t sign, uint8_t magnitude);

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
 * This function initializes the module.
 */
extern void vscp_data_coding_init(void)
{
    /* Nothing to do */

    return;
}

/**
 * This function returns the format byte.
 *
 * @param[in]   representation  The data representation.
 * @param[in]   unit            The unit of the data.
 * @param[in]   index           Sensor index (optional)
 * @return Format byte
 */
extern uint8_t vscp_data_coding_getFormatByte(VSCP_DATA_CODING_REPRESENTATION representation, uint8_t unit, uint8_t index)
{
    uint8_t formatByte  = 0;

    formatByte  = (representation & 0x07) << 5; /* Numerical representation */
    formatByte |= (unit           & 0x03) << 3; /* Unit */
    formatByte |= (index          & 0x07) << 0; /* Zero based sensor index */

    return formatByte;
}

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
extern uint8_t vscp_data_coding_int32ToNormalizedInteger(int32_t data, int8_t exp, uint8_t * const codedData, uint8_t codedDataSize)
{
    uint8_t     codedDataIndex  = 0;
    uint8_t     expSign         = (0 > exp) ? 1 : 0;
    uint8_t     expMagnitude    = (0 > exp) ? (-1 * exp) : exp;
    uint32_t    dataMagnitude   = (0 > data) ? (-1 * data) : data;
    uint8_t     neededSize      = 1;

    /* Calculate needed coded data size */
    if (0x80 > dataMagnitude)
    {
        /* 8 bit value */
        neededSize += 1;
    }
    else if (0x8000 > dataMagnitude)
    {
        /* 16 bit value */
        neededSize += 2;
    }
    else if (0x800000 > dataMagnitude)
    {
        /* 24 bit value */
        neededSize += 3;
    }
    else
    {
        /* 32 bit value */
        neededSize += 4;
    }

    /* Check given coded data size */
    if (codedDataSize < neededSize)
    {
        /* Abort */
        return 0;
    }

    /* Build normalizer byte */
    codedData[codedDataIndex] = vscp_data_coding_getNormalizerByte(expSign, expMagnitude);
    ++codedDataIndex;

    /* 8 bit signed integer? */
    if (0x80 > dataMagnitude)
    {
        codedData[codedDataIndex] = (data >> 0) & 0xff;
        ++codedDataIndex;
    }
    /* 16 bit signed integer? */
    else if (0x8000 > dataMagnitude)
    {
        codedData[codedDataIndex] = (uint8_t)((data >> 8) & 0xff);
        ++codedDataIndex;

        codedData[codedDataIndex] = (uint8_t)((data >> 0) & 0xff);
        ++codedDataIndex;
    }
    /* 24 bit signed integer? */
    else if (0x800000 > dataMagnitude)
    {
        codedData[codedDataIndex] = (uint8_t)((data >> 16) & 0xff);
        ++codedDataIndex;

        codedData[codedDataIndex] = (uint8_t)((data >>  8) & 0xff);
        ++codedDataIndex;

        codedData[codedDataIndex] = (uint8_t)((data >>  0) & 0xff);
        ++codedDataIndex;
    }
    /* 32 bit signed integer */
    else
    {
        codedData[codedDataIndex] = (uint8_t)((data >> 24) & 0xff);
        ++codedDataIndex;

        codedData[codedDataIndex] = (uint8_t)((data >> 16) & 0xff);
        ++codedDataIndex;

        codedData[codedDataIndex] = (uint8_t)((data >> 8) & 0xff);
        ++codedDataIndex;

        codedData[codedDataIndex] = (uint8_t)((data >> 0) & 0xff);
        ++codedDataIndex;
    }

    return codedDataIndex;
}

/**
 * This function returns the normalized integer format in integer form.
 * Note, there is shall not be a format byte at the head of the coded data.
 *
 * @param[in,out]   codedData       The coded data array
 * @param[in]       codedDataSize   The size of the coded data array
 * @param[in]       data            The data value
 * @param[in]       exp             The data exponent
 */
extern void vscp_data_coding_normalizedIntegerToInt32(uint8_t const * const codedData, uint8_t codedDataSize, int32_t* const data, int8_t* const exp)
{
    uint8_t codedDataIndex  = 0;

    if ((NULL == data) ||
        (NULL == exp))
    {
        return;
    }

    *data = 0;
    *exp  = 0;

    if ((1 > codedDataSize) ||  /* Invalid */
        (5 < codedDataSize))    /* More than 32 bit values are not supported */
    {
        return;
    }

    /* Build exponent */
    *exp = (int8_t)(codedData[codedDataIndex] & 0x7f);
    if (0 != (codedData[codedDataIndex] & 0x80))
    {
        *exp *= -1;
    }
    ++codedDataIndex;

    /* 8 bit signed value? */
    if (2 == codedDataSize)
    {
        *data = ((int32_t)codedData[codedDataIndex]) << 0;
        ++codedDataIndex;
    }
    /* 16 bit signed value? */
    else if (3 == codedDataSize)
    {
        *data = ((int32_t)codedData[codedDataIndex]) << 8;
        ++codedDataIndex;

        *data |= ((int32_t)codedData[codedDataIndex]) << 0;
        ++codedDataIndex;
    }
    /* 24 bit signed value? */
    else if (4 == codedDataSize)
    {
        /* Handle sign bit */
        if (0 != (codedData[codedDataIndex] & 0x80))
        {
            *data = (int32_t)0xff000000;
        }
        else
        {
            *data = 0;
        }

        *data |= ((int32_t)codedData[codedDataIndex]) << 16;
        ++codedDataIndex;

        *data |= ((int32_t)codedData[codedDataIndex]) <<  8;
        ++codedDataIndex;

        *data |= ((int32_t)codedData[codedDataIndex]) <<  0;
        ++codedDataIndex;
    }
    /* 32 bit signed value? */
    else if (5 == codedDataSize)
    {
        *data  = ((int32_t)codedData[codedDataIndex]) << 24;
        ++codedDataIndex;

        *data |= ((int32_t)codedData[codedDataIndex]) << 16;
        ++codedDataIndex;

        *data |= ((int32_t)codedData[codedDataIndex]) <<  8;
        ++codedDataIndex;

        *data |= ((int32_t)codedData[codedDataIndex]) <<  0;
        ++codedDataIndex;
    }
    /* Error or not supported */
    else
    {
        ;
    }

    return;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

/**
 * This function returns the normalizer byte.
 *
 * @param[in]   sign        The sign of the exponent.
 * @param[in]   magnitude   The magnitude of the exponent.
 * @return Normalizer byte
 */
static inline uint8_t vscp_data_coding_getNormalizerByte(uint8_t sign, uint8_t magnitude)
{
    uint8_t normalizerByte  = 0;

    normalizerByte  = (sign      & 0x01) << 7;  /* Sign */
    normalizerByte |= (magnitude & 0x7f) << 0;  /* Magnitude */

    return normalizerByte;
}
