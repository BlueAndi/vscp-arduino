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
@brief  VSCP application registers
@file   vscp_app_reg.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_app_reg.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_app_reg.h"
#include "vscp_types.h"

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
 * This function initializes this module.
 */
extern void vscp_app_reg_init(void)
{
    /* Implement your code here ... */

    return;
}

/**
 * Restore the application specific factory default settings.
 */
extern void vscp_app_reg_restoreFactoryDefaultSettings(void)
{
    /* Implement your code here ... */

    return;
}

/**
 * This function returns the number of used pages.
 * Its used in the register abstraction model.
 * Deprecated since VSCP spec. v1.10.2
 *
 * @return  Pages used
 * @retval  0   More than 255 pages are used.
 */
extern uint8_t  vscp_app_reg_getPagesUsed(void)
{
    uint8_t pagesUsed   = 1;    /* At least one page, which is mandatory. */

    /* Implement your code here ... */

    return pagesUsed;
}

/**
 * This function reads a application specific register and returns the value.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Register value
 */
extern uint8_t  vscp_app_reg_readRegister(uint16_t page, uint8_t addr)
{
    uint8_t value   = 0;

    if (0 == page)
    {
        if ((VSCP_REGISTER_APP_START_ADDR <= addr) &&
            (VSCP_REGISTER_APP_END_ADDR >= addr))
        {
            /* Implement your code here ... */

        }
    }
    else
    {
        /* Implement your code here ... */

    }

    return value;
}

/**
 * This function writes a value to an application specific register.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @param[in]   value   Value to write
 * @return  Register value
 */
extern uint8_t  vscp_app_reg_writeRegister(uint16_t page, uint8_t addr, uint8_t value)
{
    uint8_t readBackValue   = 0;

    if (0 == page)
    {
        if ((VSCP_REGISTER_APP_START_ADDR <= addr) &&
            (VSCP_REGISTER_APP_END_ADDR >= addr))
        {
            /* Implement your code here ... */

        }
    }
    else
    {
        /* Implement your code here ... */

    }

    return readBackValue;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

