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
@brief  VSCP class 1 weather types
@file   vscp_type_weather.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 weather class defined types.

*******************************************************************************/
/** @defgroup vscp_type_weather Weather class types
 * Level 1 weather class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_WEATHER_H__
#define __VSCP_TYPE_WEATHER_H__

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

/** VSCP class 1 weather type: Undefined */
#define VSCP_TYPE_WEATHER_UNDEFINED                 0

/** VSCP class 1 weather type: Season Winter */
#define VSCP_TYPE_WEATHER_SEASON_WINTER             1

/** VSCP class 1 weather type: Season spring */
#define VSCP_TYPE_WEATHER_SEASON_SPRING             2

/** VSCP class 1 weather type: Season summer */
#define VSCP_TYPE_WEATHER_SEASON_SUMMER             3

/** VSCP class 1 weather type: Autumn summer */
#define VSCP_TYPE_WEATHER_AUTUMN_SUMMER             4

/** VSCP class 1 weather type: Win none */
#define VSCP_TYPE_WEATHER_WIN_NONE                  5

/** VSCP class 1 weather type: Low wind */
#define VSCP_TYPE_WEATHER_LOW_WIND                  6

/** VSCP class 1 weather type: Medium wind */
#define VSCP_TYPE_WEATHER_MEDIUM_WIND               7

/** VSCP class 1 weather type: High wind */
#define VSCP_TYPE_WEATHER_HIGH_WIND                 8

/** VSCP class 1 weather type: Very high wind */
#define VSCP_TYPE_WEATHER_VERY_HIGH_WIND            9

/** VSCP class 1 weather type: Air foggy */
#define VSCP_TYPE_WEATHER_AIR_FOGGY                 10

/** VSCP class 1 weather type: Air freezing */
#define VSCP_TYPE_WEATHER_AIR_FREEZING              11

/** VSCP class 1 weather type: Cold */
#define VSCP_TYPE_WEATHER_COLD                      12

/** VSCP class 1 weather type: Very cold */
#define VSCP_TYPE_WEATHER_VERY_COLD                 13

/** VSCP class 1 weather type: Air normal */
#define VSCP_TYPE_WEATHER_AIR_NORMAL                14

/** VSCP class 1 weather type: Air hot */
#define VSCP_TYPE_WEATHER_AIR_HOT                   15

/** VSCP class 1 weather type: Air very hot */
#define VSCP_TYPE_WEATHER_AIR_VERY_HOT              16

/** VSCP class 1 weather type: Pollution low */
#define VSCP_TYPE_WEATHER_POLLUTION_LOW             17

/** VSCP class 1 weather type: Pollution medium */
#define VSCP_TYPE_WEATHER_POLLUTION_MEDIUM          18

/** VSCP class 1 weather type: Pollution high */
#define VSCP_TYPE_WEATHER_POLLUTION_HIGH            19

/** VSCP class 1 weather type: Air humid */
#define VSCP_TYPE_WEATHER_AIR_HUMID                 20

/** VSCP class 1 weather type: Air dry */
#define VSCP_TYPE_WEATHER_AIR_DRY                   21

/** VSCP class 1 weather type: Soil humid */
#define VSCP_TYPE_WEATHER_SOIL_HUMID                22

/** VSCP class 1 weather type: Soil dry */
#define VSCP_TYPE_WEATHER_SOIL_DRY                  23

/** VSCP class 1 weather type: Rain none */
#define VSCP_TYPE_WEATHER_RAIN_NONE                 24

/** VSCP class 1 weather type: Rain light */
#define VSCP_TYPE_WEATHER_RAIN_LIGHT                25

/** VSCP class 1 weather type: Rain heavy */
#define VSCP_TYPE_WEATHER_RAIN_HEAVY                26

/** VSCP class 1 weather type: Rain very heavy */
#define VSCP_TYPE_WEATHER_RAIN_VERY_HEAVY           27

/** VSCP class 1 weather type: Sun none */
#define VSCP_TYPE_WEATHER_SUN_NONE                  28

/** VSCP class 1 weather type: Sun light */
#define VSCP_TYPE_WEATHER_SUN_LIGHT                 29

/** VSCP class 1 weather type: Sun heavy */
#define VSCP_TYPE_WEATHER_SUN_HEAVY                 30

/** VSCP class 1 weather type: Snow none */
#define VSCP_TYPE_WEATHER_SNOW_NONE                 31

/** VSCP class 1 weather type: Snow light */
#define VSCP_TYPE_WEATHER_SNOW_LIGHT                32

/** VSCP class 1 weather type: Snow heavy */
#define VSCP_TYPE_WEATHER_SNOW_HEAVY                33

/** VSCP class 1 weather type: Dew point */
#define VSCP_TYPE_WEATHER_DEW_POINT                 34

/** VSCP class 1 weather type: Storm */
#define VSCP_TYPE_WEATHER_STORM                     35

/** VSCP class 1 weather type: Flood */
#define VSCP_TYPE_WEATHER_FLOOD                     36

/** VSCP class 1 weather type: Earthquake */
#define VSCP_TYPE_WEATHER_EARTHQUAKE                37

/** VSCP class 1 weather type: Nuclear disaster */
#define VSCP_TYPE_WEATHER_NUCLEAR_DISASTER          38

/** VSCP class 1 weather type: Fire */
#define VSCP_TYPE_WEATHER_FIRE                      39

/** VSCP class 1 weather type: Lightning */
#define VSCP_TYPE_WEATHER_LIGHTNING                 40

/** VSCP class 1 weather type: UV Radiation low */
#define VSCP_TYPE_WEATHER_UV_RADIATION_LOW          41

/** VSCP class 1 weather type: UV Radiation medium */
#define VSCP_TYPE_WEATHER_UV_RADIATION_MEDIUM       42

/** VSCP class 1 weather type: UV Radiation normal */
#define VSCP_TYPE_WEATHER_UV_RADIATION_NORMAL       43

/** VSCP class 1 weather type: UV Radiation high */
#define VSCP_TYPE_WEATHER_UV_RADIATION_HIGH         44

/** VSCP class 1 weather type: UV Radiation very high */
#define VSCP_TYPE_WEATHER_UV_RADIATION_VERY_HIGH    45

/** VSCP class 1 weather type: Warning level 1 */
#define VSCP_TYPE_WEATHER_WARNING_LEVEL_1           46

/** VSCP class 1 weather type: Warning level 2 */
#define VSCP_TYPE_WEATHER_WARNING_LEVEL_2           47

/** VSCP class 1 weather type: Warning level 3 */
#define VSCP_TYPE_WEATHER_WARNING_LEVEL_3           48

/** VSCP class 1 weather type: Warning level 4 */
#define VSCP_TYPE_WEATHER_WARNING_LEVEL_4           49

/** VSCP class 1 weather type: Warning level 5 */
#define VSCP_TYPE_WEATHER_WARNING_LEVEL_5           50

/** VSCP class 1 weather type: Armageddon */
#define VSCP_TYPE_WEATHER_ARMAGEDDON                51

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

#endif  /* __VSCP_TYPE_WEATHER_H__ */

/** @} */
