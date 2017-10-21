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
@brief  VSCP class 1 control types
@file   vscp_type_control.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 control class defined types.

*******************************************************************************/
/** @defgroup vscp_type_control Control class types
 * Level 1 control class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_CONTROL_H__
#define __VSCP_TYPE_CONTROL_H__

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

/** VSCP class 1 control type: Undefined */
#define VSCP_TYPE_CONTROL_UNDEFINED                 0

/** VSCP class 1 control type: Mute on/off */
#define VSCP_TYPE_CONTROL_MUTE_ON_OFF               1

/** VSCP class 1 control type: (All) Lamp(s) on/off */
#define VSCP_TYPE_CONTROL_LAMP_ON_OFF               2

/** VSCP class 1 control type: Open */
#define VSCP_TYPE_CONTROL_OPEN                      3

/** VSCP class 1 control type: Close */
#define VSCP_TYPE_CONTROL_CLOSE                     4

/** VSCP class 1 control type: Turn on */
#define VSCP_TYPE_CONTROL_TURN_ON                   5

/** VSCP class 1 control type: Turn off */
#define VSCP_TYPE_CONTROL_TURN_OFF                  6

/** VSCP class 1 control type: Start */
#define VSCP_TYPE_CONTROL_START                     7

/** VSCP class 1 control type: Stop */
#define VSCP_TYPE_CONTROL_STOP                      8

/** VSCP class 1 control type: Reset */
#define VSCP_TYPE_CONTROL_RESET                     9

/** VSCP class 1 control type: Interrupt */
#define VSCP_TYPE_CONTROL_INTERRUPT                 10

/** VSCP class 1 control type: Sleep */
#define VSCP_TYPE_CONTROL_SLEEP                     11

/** VSCP class 1 control type: Wakeup */
#define VSCP_TYPE_CONTROL_WAKEUP                    12

/** VSCP class 1 control type: Resume */
#define VSCP_TYPE_CONTROL_RESUME                    13

/** VSCP class 1 control type: Pause */
#define VSCP_TYPE_CONTROL_PAUSE                     14

/** VSCP class 1 control type: Activate */
#define VSCP_TYPE_CONTROL_ACTIVATE                  15

/** VSCP class 1 control type: Deactivate */
#define VSCP_TYPE_CONTROL_DEACTIVATE                16

/** VSCP class 1 control type: Reserved for future use */
#define VSCP_TYPE_CONTROL_RESERVED_1                17

/** VSCP class 1 control type: Reserved for future use */
#define VSCP_TYPE_CONTROL_RESERVED_2                18

/** VSCP class 1 control type: Reserved for future use */
#define VSCP_TYPE_CONTROL_RESERVED_3                19

/** VSCP class 1 control type: Dim lamp(s) */
#define VSCP_TYPE_CONTROL_DIM_LAMP                  20

/** VSCP class 1 control type: Change channel */
#define VSCP_TYPE_CONTROL_CHANGE_CHANNEL            21

/** VSCP class 1 control type: Change level */
#define VSCP_TYPE_CONTROL_CHANGE_LEVEL              22

/** VSCP class 1 control type: Relative change level */
#define VSCP_TYPE_CONTROL_RELATIVE_CHANGE_LEVEL     23

/** VSCP class 1 control type: Measurement request */
#define VSCP_TYPE_CONTROL_MEASUREMENT_REQUEST       24

/** VSCP class 1 control type: Stream data */
#define VSCP_TYPE_CONTROL_STREAM_DATA               25

/** VSCP class 1 control type: Synchronize */
#define VSCP_TYPE_CONTROL_SYNCHRONIZE               26

/** VSCP class 1 control type: Stream data with zone */
#define VSCP_TYPE_CONTROL_STREAM_DATA_WITH_ZONE     27

/** VSCP class 1 control type: Set pre-set */
#define VSCP_TYPE_CONTROL_SET_PRESET                28

/** VSCP class 1 control type: Toggle state */
#define VSCP_TYPE_CONTROL_TOGGLE_STATE              29

/** VSCP class 1 control type: Timed pulse on */
#define VSCP_TYPE_CONTROL_TIMED_PULSE_ON            30

/** VSCP class 1 control type: Timed pulse off */
#define VSCP_TYPE_CONTROL_TIMED_PULSE_OFF           31

/** VSCP class 1 control type: Set country/language */
#define VSCP_TYPE_CONTROL_SET_COUNTRY_LANGUAGE      32

/** VSCP class 1 control type: Big Change level */
#define VSCP_TYPE_CONTROL_BIG_CHANGE_LEVEL          33

/** VSCP class 1 control type: Move shutter up */
#define VSCP_TYPE_CONTROL_MOVE_SHUTTER_UP           34

/** VSCP class 1 control type: Move shutter down */
#define VSCP_TYPE_CONTROL_MOVE_SHUTTER_DOWN         35

/** VSCP class 1 control type: Move shutter left */
#define VSCP_TYPE_CONTROL_MOVE_SHUTTER_LEFT         36

/** VSCP class 1 control type: Move shutter right */
#define VSCP_TYPE_CONTROL_MOVE_SHUTTER_RIGHT        37

/** VSCP class 1 control type: Move shutter to middle position */
#define VSCP_TYPE_CONTROL_MOVE_SHUTTER_MIDDLE_POS   38

/** VSCP class 1 control type: Move shutter to preset position */
#define VSCP_TYPE_CONTROL_MOVE_SHUTTER_PRESET_POS   39

/** VSCP class 1 control type: (All) Lamp(s) on */
#define VSCP_TYPE_CONTROL_LAMP_ON                   40

/** VSCP class 1 control type: (All) Lamp(s) off */
#define VSCP_TYPE_CONTROL_LAMP_OFF                  41

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

#endif  /* __VSCP_TYPE_CONTROL_H__ */

/** @} */
