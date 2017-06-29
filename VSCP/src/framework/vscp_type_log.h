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
@brief  VSCP class 1 log types
@file   vscp_type_log.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 log class defined types.

*******************************************************************************/
/** @defgroup vscp_type_log Log class types
 * Level 1 log class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_LOG_H__
#define __VSCP_TYPE_LOG_H__

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

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

/** VSCP class 1 log type: Undefined */
#define VSCP_TYPE_LOG_UNDEFINED 0

/** VSCP class 1 log type: Log event */
#define VSCP_TYPE_LOG_LOG_EVENT 1

/** VSCP class 1 log type: Log start */
#define VSCP_TYPE_LOG_LOG_START 2

/** VSCP class 1 log type: Log stop */
#define VSCP_TYPE_LOG_LOG_STOP  3

/** VSCP class 1 log type: Log level */
#define VSCP_TYPE_LOG_LOG_LEVEL 4

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

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_TYPE_LOG_H__ */

/** @} */
