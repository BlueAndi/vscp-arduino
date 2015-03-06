/* The MIT License (MIT)
 * 
 * Copyright (c) 2014 - 2015, Andreas Merkle
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
@file   vscp_ps_access.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_ps_access.h

@section svn Subversion
$Rev: 449 $
$Date: 2015-01-05 20:23:52 +0100 (Mo, 05 Jan 2015) $
*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_ps_access.h"
#include "avr/eeprom.h"

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
 * This function initializes the persistent memory access driver.
 * It doesn't write anything in the persistent memory! It only initializes
 * the module that read/write access is possible.
 */
extern void vscp_ps_access_init(void)
{
    /* Implement your code here ... */

    return;
}

/**
 * Read a single byte from the persistent memory.
 *
 * @param[in]   addr    Address in persistent memory
 * @return  Value
 */
extern uint8_t  vscp_ps_access_read8(uint16_t addr)
{
    return eeprom_read_byte((const uint8_t*)addr);
}

/**
 * Write a single byte to the persistent memory.
 *
 * @param[in]   addr    Address in persistent memory
 * @param[in]   value   Value to write
 */
extern void vscp_ps_access_write8(uint16_t addr, uint8_t value)
{
    eeprom_write_byte((uint8_t*)addr, value);

    return;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/
