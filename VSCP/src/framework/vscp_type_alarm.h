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
@brief  VSCP class 1 alarm types
@file   vscp_type_alarm.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 alarm class defined types.

*******************************************************************************/
/** @defgroup vscp_type_alarm Alarm class types
 * Level 1 alarm class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_ALARM_H__
#define __VSCP_TYPE_ALARM_H__

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

/** VSCP class 1 alarm type: Undefined */
#define VSCP_TYPE_ALARM_UNDEFINED           0

/** VSCP class 1 alarm type: Warning */
#define VSCP_TYPE_ALARM_WARNING             1

/** VSCP class 1 alarm type: Alarm occurred */
#define VSCP_TYPE_ALARM_ALARM_OCCURRED      2

/** VSCP class 1 alarm type: Alarm sound on/off */
#define VSCP_TYPE_ALARM_ALARM_SOUND_ON_OFF  3

/** VSCP class 1 alarm type: Alarm light on/off */
#define VSCP_TYPE_ALARM_ALARM_LIGHT_ON_OFF  4

/** VSCP class 1 alarm type: Power on/off */
#define VSCP_TYPE_ALARM_POWER_ON_OFF        5

/** VSCP class 1 alarm type: Emergency Stop */
#define VSCP_TYPE_ALARM_EMERGENCY_STOP      6

/** VSCP class 1 alarm type: Emergency Pause */
#define VSCP_TYPE_ALARM_EMERGENCY_PAUSE     7

/** VSCP class 1 alarm type: Emergency Reset */
#define VSCP_TYPE_ALARM_EMERGENCY_RESET     8

/** VSCP class 1 alarm type: Emergency Resume */
#define VSCP_TYPE_ALARM_EMERGENCY_RESUME    9

/** VSCP class 1 alarm type: Issued after an alarm system has been armed.  */
#define VSCP_TYPE_ALARM_EMERGENCY_ARM       10

/** VSCP class 1 alarm type: Issued after an alarm system has been disarmed. */
#define VSCP_TYPE_ALARM_EMERGENCY_DISARM    11

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

#endif  /* __VSCP_TYPE_ALARM_H__ */

/** @} */
