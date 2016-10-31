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
@brief  VSCP class 1 security types
@file   vscp_type_security.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 security class defined types.

*******************************************************************************/
/** @defgroup vscp_type_security Security class types
 * Level 1 security class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_SECURITY_H__
#define __VSCP_TYPE_SECURITY_H__

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

/** VSCP class 1 security type: Undefined */
#define VSCP_TYPE_SECURITY_UNDEFINED                        0

/** VSCP class 1 security type: Motion Detect */
#define VSCP_TYPE_SECURITY_MOTION_DETECT                    1

/** VSCP class 1 security type: Glass break */
#define VSCP_TYPE_SECURITY_GLASS_BREAK                      2

/** VSCP class 1 security type: Beam break */
#define VSCP_TYPE_SECURITY_BEAM_BREAK                       3

/** VSCP class 1 security type: Sensor tamper */
#define VSCP_TYPE_SECURITY_SENSOR_TAMPER                    4

/** VSCP class 1 security type: Shock sensor */
#define VSCP_TYPE_SECURITY_SHOCK_SENSOR                     5

/** VSCP class 1 security type: Smoke sensor */
#define VSCP_TYPE_SECURITY_SMOKE_SENSOR                     6

/** VSCP class 1 security type: Heat sensor */
#define VSCP_TYPE_SECURITY_HEAT_SENSOR                      7

/** VSCP class 1 security type: Panic switch */
#define VSCP_TYPE_SECURITY_PANIC_SWITCH                     8

/** VSCP class 1 security type: Door contact */
#define VSCP_TYPE_SECURITY_DOOR_CONTACT                     9

/** VSCP class 1 security type: Window contact */
#define VSCP_TYPE_SECURITY_WINDOW_CONTACT                   10

/** VSCP class 1 security type: CO sensor */
#define VSCP_TYPE_SECURITY_CO_SENSOR                        11

/** VSCP class 1 security type: Frost detected */
#define VSCP_TYPE_SECURITY_FROST_DETECTED                   12

/** VSCP class 1 security type: Flame detected */
#define VSCP_TYPE_SECURITY_FLAME_DETECTED                   13

/** VSCP class 1 security type: Oxygen low */
#define VSCP_TYPE_SECURITY_OXYGEN_LOW                       14

/** VSCP class 1 security type: Weight detected */
#define VSCP_TYPE_SECURITY_WEIGHT_DETECTED                  15

/** VSCP class 1 security type: Water detected */
#define VSCP_TYPE_SECURITY_WATER_DETECTED                   16

/** VSCP class 1 security type: Condensation detected */
#define VSCP_TYPE_SECURITY_CONDENSATION_DETECTED            17

/** VSCP class 1 security type: Noise (sound) detected */
#define VSCP_TYPE_SECURITY_NOISE_DETECTED                   18

/** VSCP class 1 security type: Harmful sound levels detected */
#define VSCP_TYPE_SECURITY_HARMFUL_SOUND_LEVELS_DETECTED    19

/** VSCP class 1 security type: Tamper detected */
#define VSCP_TYPE_SECURITY_TAMPER_DETECTED                  20

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

#endif  /* __VSCP_TYPE_SECURITY_H__ */

/** @} */
