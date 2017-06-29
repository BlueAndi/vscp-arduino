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
@brief  VSCP base configuration switches
@file   vscp_config_base.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the base configuation switches, which are used in
configuration files to enable/disable features.

*******************************************************************************/
/** @defgroup vscp_config_base VSCP configuration base
 * This module contains the base configuation switches, which are used in
 * configuration files to enable/disable features.
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_CONFIG_BASE_H__
#define __VSCP_CONFIG_BASE_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/** Use this to enable a feature. */
#define VSCP_CONFIG_BASE_DISABLED   0

/** Use this to enable a feature. */
#define VSCP_CONFIG_BASE_ENABLED    1

/*******************************************************************************
    MACROS
*******************************************************************************/

/** Use this to determine if a configuration switch is disabled. */
#define VSCP_CONFIG_BASE_IS_DISABLED(__switch)  (VSCP_CONFIG_BASE_DISABLED == (__switch))

/** Use this to determine if a configuration switch is enabled. */
#define VSCP_CONFIG_BASE_IS_ENABLED(__switch)  (VSCP_CONFIG_BASE_ENABLED == (__switch))

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_CONFIG_BASE_H__ */

/** @} */
