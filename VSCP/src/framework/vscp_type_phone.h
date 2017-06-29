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
@brief  VSCP class 1 phone types
@file   vscp_type_phone.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 phone class defined types.

*******************************************************************************/
/** @defgroup vscp_type_phone Phone class types
 * Level 1 phone class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_PHONE_H__
#define __VSCP_TYPE_PHONE_H__

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

/** VSCP class 1 phone type: Undefined */
#define VSCP_TYPE_PHONE_UNDEFINED       0

/** VSCP class 1 phone type: Incoming call */
#define VSCP_TYPE_PHONE_INCOMING_CALL   1

/** VSCP class 1 phone type: Outgoing call */
#define VSCP_TYPE_PHONE_OUTGOING_CALL   2

/** VSCP class 1 phone type: Ring */
#define VSCP_TYPE_PHONE_RING            3

/** VSCP class 1 phone type: Answer */
#define VSCP_TYPE_PHONE_ANSWER          4

/** VSCP class 1 phone type: Hangup */
#define VSCP_TYPE_PHONE_HANGUP          5

/** VSCP class 1 phone type: Giveup */
#define VSCP_TYPE_PHONE_GIVEUP          6

/** VSCP class 1 phone type: Transfer */
#define VSCP_TYPE_PHONE_TRANSFER        7

/** VSCP class 1 phone type: Database info */
#define VSCP_TYPE_PHONE_DATABASE_INFO   8

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

#endif  /* __VSCP_TYPE_PHONE_H__ */

/** @} */
