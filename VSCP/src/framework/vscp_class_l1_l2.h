/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2016, Andreas Merkle
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
@brief  VSCP level 1 classes over level 2
@file   vscp_class_l1_l2.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all VSCP level 1 classes over level 2.

*******************************************************************************/
/** @defgroup vscp_class_l1_l2 VSCP Level 1 classes over level 2.
 * VSCP Level 1 classes over level 2
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_CLASS_L1_L2_H__
#define __VSCP_TYPE_CLASS_L1_L2_H__

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

/** The base id for all level 1 events, sent over level 2.
 * An event with a class >= 512 but < 1024 will be sent to all Level II clients
 * and to the correct i/f (the one that have the addressed GUID). A response from
 * the device will go out as as a Level II event using the GUID of the interface
 * but class will always have a value < 512 for a response event just as all
 * events originating from a device.
 */
#define VSCP_CLASS_L1_L2_BASE               512

/** VSCP level 1 class over level 2: VSCP protocol functionality */
#define VSCP_CLASS_L1_L2_PROTOCOL           (VSCP_CLASS_L1_L2_BASE + 0)

/** VSCP level 1 class over level 2: Alarm */
#define VSCP_CLASS_L1_L2_ALARM              (VSCP_CLASS_L1_L2_BASE + 1)

/** VSCP level 1 class over level 2: Security */
#define VSCP_CLASS_L1_L2_SECURITY           (VSCP_CLASS_L1_L2_BASE + 2)

/** VSCP level 1 class over level 2: Measurement */
#define VSCP_CLASS_L1_L2_MEASUREMENT        (VSCP_CLASS_L1_L2_BASE + 10)

/** VSCP level 1 class over level 2: Data */
#define VSCP_CLASS_L1_L2_DATA               (VSCP_CLASS_L1_L2_BASE + 15)

/** VSCP level 1 class over level 2: Information */
#define VSCP_CLASS_L1_L2_INFORMATION        (VSCP_CLASS_L1_L2_BASE + 20)

/** VSCP level 1 class over level 2: Control */
#define VSCP_CLASS_L1_L2_CONTROL            (VSCP_CLASS_L1_L2_BASE + 30)

/** VSCP level 1 class over level 2: Multimedia */
#define VSCP_CLASS_L1_L2_MULTIMEDIA         (VSCP_CLASS_L1_L2_BASE + 40)

/** VSCP level 1 class over level 2: Alert on LAN */
#define VSCP_CLASS_L1_L2_ALERT_ON_LAN       (VSCP_CLASS_L1_L2_BASE + 50)

/** VSCP level 1 class over level 2: Double precision floating point measurement */
#define VSCP_CLASS_L1_L2_MEASUREMENT_DOUBLE (VSCP_CLASS_L1_L2_BASE + 60)

/** VSCP level 1 class over level 2: Measurement with zone */
#define VSCP_CLASS_L1_L2_MEASUREZONE        (VSCP_CLASS_L1_L2_BASE + 65)

/** VSCP level 1 class over level 2: Single precision floating piont measurement */
#define VSCP_CLASS_L1_L2_MEASUREMENT_SINGLE (VSCP_CLASS_L1_L2_BASE + 70)

/** VSCP level 1 class over level 2: Set value with zone */
#define VSCP_CLASS_L1_L2_SET_VALUE_WITH_ZONE (VSCP_CLASS_L1_L2_BASE + 85)

/** VSCP level 1 class over level 2: Weather */
#define VSCP_CLASS_L1_L2_WEATHER             (VSCP_CLASS_L1_L2_BASE + 90)

/** VSCP level 1 class over level 2: Weather forecast */
#define VSCP_CLASS_L1_L2_WEATHER_FORECAST    (VSCP_CLASS_L1_L2_BASE + 95)

/** VSCP level 1 class over level 2: Phone */
#define VSCP_CLASS_L1_L2_PHONE               (VSCP_CLASS_L1_L2_BASE + 100)

/** VSCP level 1 class over level 2: Display */
#define VSCP_CLASS_L1_L2_DISPLAY             (VSCP_CLASS_L1_L2_BASE + 102)

/** VSCP level 1 class over level 2: IR Remote i/f */
#define VSCP_CLASS_L1_L2_REMOTE              (VSCP_CLASS_L1_L2_BASE + 110)

/** VSCP level 1 class over level 2: Positon (GPS) */
#define VSCP_CLASS_L1_L2_GPS                 (VSCP_CLASS_L1_L2_BASE + 206)

/** VSCP level 1 class over level 2: Wireless */
#define VSCP_CLASS_L1_L2_WIRELESS            (VSCP_CLASS_L1_L2_BASE + 212)

/** VSCP level 1 class over level 2: Diagnostic */
#define VSCP_CLASS_L1_L2_DIAGNOSTIC          (VSCP_CLASS_L1_L2_BASE + 506)

/** VSCP level 1 class over level 2: Error */
#define VSCP_CLASS_L1_L2_ERROR               (VSCP_CLASS_L1_L2_BASE + 508)

/** VSCP level 1 class over level 2: Logging i/f */
#define VSCP_CLASS_L1_L2_LOG                 (VSCP_CLASS_L1_L2_BASE + 509)

/** VSCP level 1 class over level 2: Laboratory use */
#define VSCP_CLASS_L1_L2_LABORATORY          (VSCP_CLASS_L1_L2_BASE + 510)

/** VSCP level 1 class over level 2: Local use */
#define VSCP_CLASS_L1_L2_LOCAL               (VSCP_CLASS_L1_L2_BASE + 511)

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

#endif  /* __VSCP_TYPE_CLASS_L1_L2_H__ */

/** @} */
