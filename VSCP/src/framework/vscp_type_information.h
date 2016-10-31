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
@brief  VSCP class 1 information types
@file   vscp_type_information.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 information class defined types.

*******************************************************************************/
/** @defgroup vscp_type_information Information class types
 * Level 1 information class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_INFORMATION_H__
#define __VSCP_TYPE_INFORMATION_H__

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

/** VSCP class 1 information type: Undefined */
#define VSCP_TYPE_INFORMATION_UNDEFINED             0

/** VSCP class 1 information type: Button */
#define VSCP_TYPE_INFORMATION_BUTTON                1

/** VSCP class 1 information type: Mouse */
#define VSCP_TYPE_INFORMATION_MOUSE                 2

/** VSCP class 1 information type: On */
#define VSCP_TYPE_INFORMATION_ON                    3

/** VSCP class 1 information type: Off */
#define VSCP_TYPE_INFORMATION_OFF                   4

/** VSCP class 1 information type: Alive */
#define VSCP_TYPE_INFORMATION_ALIVE                 5

/** VSCP class 1 information type: Terminating */
#define VSCP_TYPE_INFORMATION_TERMINATING           6

/** VSCP class 1 information type: Opened */
#define VSCP_TYPE_INFORMATION_OPENED                7

/** VSCP class 1 information type: Closed */
#define VSCP_TYPE_INFORMATION_CLOSED                8

/** VSCP class 1 information type: Node heartbeat */
#define VSCP_TYPE_INFORMATION_NODE_HEARTBEAT        9

/** VSCP class 1 information type: Below limit */
#define VSCP_TYPE_INFORMATION_BELOW_LIMIT           10

/** VSCP class 1 information type: Above limit */
#define VSCP_TYPE_INFORMATION_ABOVE_LIMIT           11

/** VSCP class 1 information type: Pulse */
#define VSCP_TYPE_INFORMATION_PULSE                 12

/** VSCP class 1 information type: Error */
#define VSCP_TYPE_INFORMATION_ERROR                 13

/** VSCP class 1 information type: Resumed */
#define VSCP_TYPE_INFORMATION_RESUMED               14

/** VSCP class 1 information type: Paused */
#define VSCP_TYPE_INFORMATION_PAUSED                15

/** VSCP class 1 information type: Sleeping */
#define VSCP_TYPE_INFORMATION_SLEEPING              16

/** VSCP class 1 information type: Good morning */
#define VSCP_TYPE_INFORMATION_GOOD_MORNING          17

/** VSCP class 1 information type: Good day */
#define VSCP_TYPE_INFORMATION_GOOD_DAY              18

/** VSCP class 1 information type: Good afternoon */
#define VSCP_TYPE_INFORMATION_GOOD_AFTERNOON        19

/** VSCP class 1 information type: Good evening */
#define VSCP_TYPE_INFORMATION_GOOD_EVENING          20

/** VSCP class 1 information type: Good night */
#define VSCP_TYPE_INFORMATION_GOOD_NIGHT            21

/** VSCP class 1 information type: See you soon */
#define VSCP_TYPE_INFORMATION_SEE_YOU_SOON          22

/** VSCP class 1 information type: Goodbye */
#define VSCP_TYPE_INFORMATION_GOODBYE               23

/** VSCP class 1 information type: Stop */
#define VSCP_TYPE_INFORMATION_STOP                  24

/** VSCP class 1 information type: Start */
#define VSCP_TYPE_INFORMATION_START                 25

/** VSCP class 1 information type: Reset completed */
#define VSCP_TYPE_INFORMATION_RESET_COMPLETED       26

/** VSCP class 1 information type: Interrupted */
#define VSCP_TYPE_INFORMATION_INTERRUPTED           27

/** VSCP class 1 information type: Preparing to sleep */
#define VSCP_TYPE_INFORMATION_PREPARING_TO_SLEEP    28

/** VSCP class 1 information type: Woken up */
#define VSCP_TYPE_INFORMATION_WOKEN_UP              29

/** VSCP class 1 information type: Dusk */
#define VSCP_TYPE_INFORMATION_DUSK                  30

/** VSCP class 1 information type: Dawn */
#define VSCP_TYPE_INFORMATION_DAWN                  31

/** VSCP class 1 information type: Active */
#define VSCP_TYPE_INFORMATION_ACTIVE                32

/** VSCP class 1 information type: Inactive */
#define VSCP_TYPE_INFORMATION_INACTIVE              33

/** VSCP class 1 information type: Busy */
#define VSCP_TYPE_INFORMATION_BUSY                  34

/** VSCP class 1 information type: Idle */
#define VSCP_TYPE_INFORMATION_IDLE                  35

/** VSCP class 1 information type: Stream data */
#define VSCP_TYPE_INFORMATION_STREAM_DATA           36

/** VSCP class 1 information type: token activity */
#define VSCP_TYPE_INFORMATION_TOKEN_ACTIVITY        37

/** VSCP class 1 information type: Stream data with zone */
#define VSCP_TYPE_INFORMATION_STREAM_DATA_WITH_ZONE 38

/** VSCP class 1 information type: confirm */
#define VSCP_TYPE_INFORMATION_CONFIRM               39

/** VSCP class 1 information type: Level changed */
#define VSCP_TYPE_INFORMATION_LEVEL_CHANGED         40

/** VSCP class 1 information type: Warning */
#define VSCP_TYPE_INFORMATION_WARNING               41

/** VSCP class 1 information type: State */
#define VSCP_TYPE_INFORMATION_STATE                 42

/** VSCP class 1 information type: Action trigger */
#define VSCP_TYPE_INFORMATION_ACTION_TRIGGER        43

/** VSCP class 1 information type: Sunrise */
#define VSCP_TYPE_INFORMATION_SUNRISE               44

/** VSCP class 1 information type: Sunset */
#define VSCP_TYPE_INFORMATION_SUNSET                45

/** VSCP class 1 information type: Start of record */
#define VSCP_TYPE_INFORMATION_START_OF_RECORD       46

/** VSCP class 1 information type: End of record */
#define VSCP_TYPE_INFORMATION_END_OF_RECORD         47

/** VSCP class 1 information type: Pre-set active */
#define VSCP_TYPE_INFORMATION_PRESET_ACTIVE         48

/** VSCP class 1 information type: Detect */
#define VSCP_TYPE_INFORMATION_DETECT                49

/** VSCP class 1 information type: Overflow */
#define VSCP_TYPE_INFORMATION_OVERFLOW              50

/** VSCP class 1 information type: Big level changed */
#define VSCP_TYPE_INFORMATION_BIG_LEVEL_CHANGED     51

/** VSCP class 1 information type: Civil sunrise twilight time */
#define VSCP_TYPE_INFORMATION_CIVIL_SUNRISE_TWILIGHT_TIME           52

/** VSCP class 1 information type: Civil sunset twilight time */
#define VSCP_TYPE_INFORMATION_CIVIL_SUNSET_TWILIGHT_TIME            53

/** VSCP class 1 information type: Nautical sunrise twilight time */
#define VSCP_TYPE_INFORMATION_NAUTICAL_SUNRISE_TWILIGHT_TIME        54

/** VSCP class 1 information type: Nautical sunset twilight time */
#define VSCP_TYPE_INFORMATION_NAUTICAL_SUNSET_TWILIGHT_TIME         55

/** VSCP class 1 information type: Astronomical sunrise twilight time */
#define VSCP_TYPE_INFORMATION_ASTRONOMICAL_SUNRISE_TWILIGHT_TIME    56

/** VSCP class 1 information type: Astronomical sunset twilight time */
#define VSCP_TYPE_INFORMATION_ASTRONOMICAL_SUNSET_TWILIGHT_TIME     57

/** VSCP class 1 information type: Calculated noon */
#define VSCP_TYPE_INFORMATION_CALCULATED_NOON                       58

/** VSCP class 1 information type: Shutter up */
#define VSCP_TYPE_INFORMATION_SHUTTER_UP                            59

/** VSCP class 1 information type: Shutter down */
#define VSCP_TYPE_INFORMATION_SHUTTER_DOWN                          60

/** VSCP class 1 information type: Shutter left */
#define VSCP_TYPE_INFORMATION_SHUTTER_LEFT                          61

/** VSCP class 1 information type: Shutter right */
#define VSCP_TYPE_INFORMATION_SHUTTER_RIGHT                         62

/** VSCP class 1 information type: Shutter reached top end */
#define VSCP_TYPE_INFORMATION_SHUTTER_REACHED_TOP_END               63

/** VSCP class 1 information type: Shutter reached bottom end */
#define VSCP_TYPE_INFORMATION_SHUTTER_REACHED_BOTTOM_END            64

/** VSCP class 1 information type: Shutter reached middle end */
#define VSCP_TYPE_INFORMATION_SHUTTER_REACHED_MIDDLE_END            65

/** VSCP class 1 information type: Shutter reached preset end */
#define VSCP_TYPE_INFORMATION_SHUTTER_REACHED_PRESET_END            66

/** VSCP class 1 information type: Shutter reached preset left */
#define VSCP_TYPE_INFORMATION_SHUTTER_REACHED_PRESET_LEFT           67

/** VSCP class 1 information type: Shutter reached preset right */
#define VSCP_TYPE_INFORMATION_SHUTTER_REACHED_PRESET_RIGHT          68

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

#endif  /* __VSCP_TYPE_INFORMATION_H__ */

/** @} */
