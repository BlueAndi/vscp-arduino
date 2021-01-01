/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2021, Andreas Merkle
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
@brief  VSCP persistent memory access driver
@file   vscp_ps_access.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the persistent memory access driver.

*******************************************************************************/
/** @defgroup vscp_ps_access Persistent memory access driver
 * The persistent memory driver uses the access driver to really access the
 * persistent memory.
 *
 * Because this is usually device specific, the persistent memory access has to
 * be implemented by the user.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_PS_ACCESS_H__
#define __VSCP_PS_ACCESS_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>

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
 * This function initializes the persistent memory access driver.
 * It doesn't write anything in the persistent memory! It only initializes
 * the module that read/write access is possible.
 */
extern void vscp_ps_access_init(void);

/**
 * Read a single byte from the persistent memory.
 *
 * @param[in]   addr    Address in persistent memory
 * @return  Value
 */
extern uint8_t  vscp_ps_access_read8(uint16_t addr);

/**
 * Write a single byte to the persistent memory.
 *
 * @param[in]   addr    Address in persistent memory
 * @param[in]   value   Value to write
 */
extern void vscp_ps_access_write8(uint16_t addr, uint8_t value);

/**
 * Read several bytes from the persistent memory.
 *
 * @param[in]   addr    Address in persistent memory
 * @param[in]   buffer  Buffer which to read in
 * @param[in]   size    Buffer size in byte (Number of data to read)
 */
extern void vscp_ps_access_readMultiple(uint16_t addr, uint8_t* const buffer, uint8_t size);

/**
 * Write several bytes to the persistent memory.
 *
 * @param[in]   addr    Address in persistent memory
 * @param[in]   buffer  Buffer which to write
 * @param[in]   size    Bufer size in byte (Number of data to write)
 */
extern void vscp_ps_access_writeMultiple(uint16_t addr, const uint8_t* const buffer, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_PS_ACCESS_H__ */

/** @} */
