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
@brief  VSCP level 1 classes
@file   vscp_class_l1.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all VSCP level 1 classes.

$Author: amerkle $
$Date: 2015-01-05 20:23:52 +0100 (Mo, 05 Jan 2015) $
*******************************************************************************/
/** @defgroup vscp_class_l1 VSCP Level 1 classes
 * VSCP Level 1 classes
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_CLASS_L1_H__
#define __VSCP_TYPE_CLASS_L1_H__

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

/** VSCP level 1 class: VSCP protocol functionality */
#define VSCP_CLASS_L1_PROTOCOL              0

/** VSCP level 1 class: Alarm */
#define VSCP_CLASS_L1_ALARM                 1

/** VSCP level 1 class: Security */
#define VSCP_CLASS_L1_SECURITY              2

/** VSCP level 1 class: Measurement */
#define VSCP_CLASS_L1_MEASUREMENT           10

/** VSCP level 1 class: Data */
#define VSCP_CLASS_L1_DATA                  15

/** VSCP level 1 class: Information */
#define VSCP_CLASS_L1_INFORMATION           20

/** VSCP level 1 class: Control */
#define VSCP_CLASS_L1_CONTROL               30

/** VSCP level 1 class: Multimedia */
#define VSCP_CLASS_L1_MULTIMEDIA            40

/** VSCP level 1 class: Alert on LAN */
#define VSCP_CLASS_L1_ALERT_ON_LAN          50

/** VSCP level 1 class: Double precision floating point measurement */
#define VSCP_CLASS_L1_MEASUREMENT_DOUBLE    60

/** VSCP level 1 class: Measurement with zone */
#define VSCP_CLASS_L1_MEASUREZONE           65

/** VSCP level 1 class: Single precision floating piont measurement */
#define VSCP_CLASS_L1_MEASUREMENT_SINGLE    70

/** VSCP level 1 class: Set value with zone */
#define VSCP_CLASS_L1_SET_VALUE_WITH_ZONE   85

/** VSCP level 1 class: Weather */
#define VSCP_CLASS_L1_WEATHER               90

/** VSCP level 1 class: Weather forecast */
#define VSCP_CLASS_L1_WEATHER_FORECAST      95

/** VSCP level 1 class: Phone */
#define VSCP_CLASS_L1_PHONE                 100

/** VSCP level 1 class: Display */
#define VSCP_CLASS_L1_DISPLAY               102

/** VSCP level 1 class: IR Remote i/f */
#define VSCP_CLASS_L1_REMOTE                110

/** VSCP level 1 class: Positon (GPS) */
#define VSCP_CLASS_L1_GPS                   206

/** VSCP level 1 class: Wireless */
#define VSCP_CLASS_L1_WIRELESS              212

/** VSCP level 1 class: Diagnostic */
#define VSCP_CLASS_L1_DIAGNOSTIC            506

/** VSCP level 1 class: Error */
#define VSCP_CLASS_L1_ERROR                 508

/** VSCP level 1 class: Logging i/f */
#define VSCP_CLASS_L1_LOG                   509

/** VSCP level 1 class: Laboratory use */
#define VSCP_CLASS_L1_LABORATORY            510

/** VSCP level 1 class: Local use */
#define VSCP_CLASS_L1_LOCAL                 511

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

#endif  /* __VSCP_TYPE_CLASS_L1_H__ */

/** @} */
