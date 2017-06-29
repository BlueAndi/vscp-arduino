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
@brief  VSCP class 1 measurement with zone types
@file   vscp_type_measurezone.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 measurement with zone class defined types.

*******************************************************************************/
/** @defgroup vscp_type_measurezone Measurement with zone class types
 * Level 1 measurement with zone class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_MEASUREZONE_H__
#define __VSCP_TYPE_MEASUREZONE_H__

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

/** VSCP class 1 measurement with zone type: Undefined */
#define VSCP_TYPE_MEASUREZONE_UNDEFINED                             0

/** VSCP class 1 measurement with zone type: Count */
#define VSCP_TYPE_MEASUREZONE_COUNT                                 1

/** VSCP class 1 measurement with zone type: Length Distance */
#define VSCP_TYPE_MEASUREZONE_LENGTH_DISTANCE                       2

/** VSCP class 1 measurement with zone type: Mass */
#define VSCP_TYPE_MEASUREZONE_MASS                                  3

/** VSCP class 1 measurement with zone type: Time */
#define VSCP_TYPE_MEASUREZONE_TIME                                  4

/** VSCP class 1 measurement with zone type: Electric Current */
#define VSCP_TYPE_MEASUREZONE_ELECTRIC_CURRENT                      5

/** VSCP class 1 measurement with zone type: Temperature */
#define VSCP_TYPE_MEASUREZONE_TEMPERATURE                           6

/** VSCP class 1 measurement with zone type: Amount of substance */
#define VSCP_TYPE_MEASUREZONE_AMOUNT_OF_SUBSTANCE                   7

/** VSCP class 1 measurement with zone type: Luminous Intensity */
#define VSCP_TYPE_MEASUREZONE_LUMINOUS_INTENSITY                    8

/** VSCP class 1 measurement with zone type: Frequency */
#define VSCP_TYPE_MEASUREZONE_FREQUENCY                             9

/** VSCP class 1 measurement with zone type: Radioactivity and other random events */
#define VSCP_TYPE_MEASUREZONE_RADIOACTIVITY_AND_OTHER_RANDOM_EVENTS 10

/** VSCP class 1 measurement with zone type: Force */
#define VSCP_TYPE_MEASUREZONE_FORCE                                 11

/** VSCP class 1 measurement with zone type: Pressure */
#define VSCP_TYPE_MEASUREZONE_PRESSURE                              12

/** VSCP class 1 measurement with zone type: Energy */
#define VSCP_TYPE_MEASUREZONE_ENERGY                                13

/** VSCP class 1 measurement with zone type: Power */
#define VSCP_TYPE_MEASUREZONE_POWER                                 14

/** VSCP class 1 measurement with zone type: Electrical Charge */
#define VSCP_TYPE_MEASUREZONE_ELECTRICAL_CHARGE                     15

/** VSCP class 1 measurement with zone type: Electrical Potential (Voltage) */
#define VSCP_TYPE_MEASUREZONE_ELECTRICAL_POTENTIAL                  16

/** VSCP class 1 measurement with zone type: Electrical Capacitance */
#define VSCP_TYPE_MEASUREZONE_ELECTRICAL_CAPACITANCE                17

/** VSCP class 1 measurement with zone type: Electrical Resistance */
#define VSCP_TYPE_MEASUREZONE_ELECTRICAL_RESISTANCE                 18

/** VSCP class 1 measurement with zone type: Electrical Conductance */
#define VSCP_TYPE_MEASUREZONE_ELECTRICAL_CONDUCTANCE                19

/** VSCP class 1 measurement with zone type: Magnetic Field Strength */
#define VSCP_TYPE_MEASUREZONE_MAGNETIC_FIELD_STRENGTH               20

/** VSCP class 1 measurement with zone type: Magnetic Flux */
#define VSCP_TYPE_MEASUREZONE_MAGNETIC_FLUX                         21

/** VSCP class 1 measurement with zone type: Magnetic Flux Density */
#define VSCP_TYPE_MEASUREZONE_MAGNETIC_FLUX_DENSITY                 22

/** VSCP class 1 measurement with zone type: Inductance */
#define VSCP_TYPE_MEASUREZONE_INDUCTANCE                            23

/** VSCP class 1 measurement with zone type: Luminous Flux */
#define VSCP_TYPE_MEASUREZONE_LUMINOUS_FLUX                         24

/** VSCP class 1 measurement with zone type: Illuminance */
#define VSCP_TYPE_MEASUREZONE_ILLUMINANCE                           25

/** VSCP class 1 measurement with zone type: Radiation dose */
#define VSCP_TYPE_MEASUREZONE_RADIATION_DOSE                        26

/** VSCP class 1 measurement with zone type: Catalytic activity */
#define VSCP_TYPE_MEASUREZONE_CATALYTIC_ACTIVITY                    27

/** VSCP class 1 measurement with zone type: Volume */
#define VSCP_TYPE_MEASUREZONE_VOLUME                                28

/** VSCP class 1 measurement with zone type: Sound intensity */
#define VSCP_TYPE_MEASUREZONE_SOUND_INTENSITY                       29

/** VSCP class 1 measurement with zone type: Angle */
#define VSCP_TYPE_MEASUREZONE_ANGLE                                 30

/** VSCP class 1 measurement with zone type: Position */
#define VSCP_TYPE_MEASUREZONE_POSITION                              31

/** VSCP class 1 measurement with zone type: Speed */
#define VSCP_TYPE_MEASUREZONE_SPEED                                 32

/** VSCP class 1 measurement with zone type: Acceleration */
#define VSCP_TYPE_MEASUREZONE_ACCELERATION                          33

/** VSCP class 1 measurement with zone type: Tension */
#define VSCP_TYPE_MEASUREZONE_TENSION                               34

/** VSCP class 1 measurement with zone type: Damp moist (Hygrometer reading) */
#define VSCP_TYPE_MEASUREZONE_DAMP_MOIST                            35

/** VSCP class 1 measurement with zone type: Flow */
#define VSCP_TYPE_MEASUREZONE_FLOW                                  36

/** VSCP class 1 measurement with zone type: Thermal resistance */
#define VSCP_TYPE_MEASUREZONE_THERMAL_RESISTANCE                    37

/** VSCP class 1 measurement with zone type: Refractive power */
#define VSCP_TYPE_MEASUREZONE_REFRACTIVE_POWER                      38

/** VSCP class 1 measurement with zone type: Dynamic viscosity */
#define VSCP_TYPE_MEASUREZONE_DYNAMIC_VISCOSITY                     39

/** VSCP class 1 measurement with zone type: Sound impedance */
#define VSCP_TYPE_MEASUREZONE_SOUND_IMPEDANCE                       40

/** VSCP class 1 measurement with zone type: Sound resistance */
#define VSCP_TYPE_MEASUREZONE_SOUND_RESISTANCE                      41

/** VSCP class 1 measurement with zone type: Electric elastance */
#define VSCP_TYPE_MEASUREZONE_ELECTRIC_ELASTANCE                    42

/** VSCP class 1 measurement with zone type: Luminous energy */
#define VSCP_TYPE_MEASUREZONE_LUMINOUS_ENERGY                       43

/** VSCP class 1 measurement with zone type: Luminance */
#define VSCP_TYPE_MEASUREZONE_LUMINANCE                             44

/** VSCP class 1 measurement with zone type: Chemical concentration */
#define VSCP_TYPE_MEASUREZONE_CHEMICAL_CONCENTRATION                45

/** VSCP class 1 measurement with zone type: Reserved */
#define VSCP_TYPE_MEASUREZONE_RESERVED_46                           46

/** VSCP class 1 measurement with zone type: Dose equivalent */
#define VSCP_TYPE_MEASUREZONE_DOSE_EQUIVALENT                       47

/** VSCP class 1 measurement with zone type: Reserved */
#define VSCP_TYPE_MEASUREZONE_RESERVED_48                           48

/** VSCP class 1 measurement with zone type: Dew Point */
#define VSCP_TYPE_MEASUREZONE_DEW_POINT                             49

/** VSCP class 1 measurement with zone type: Relative Level */
#define VSCP_TYPE_MEASUREZONE_RELATIVE_LEVEL                        50

/** VSCP class 1 measurement with zone type: Altitude  */
#define VSCP_TYPE_MEASUREZONE_ALTITUDE                              51

/** VSCP class 1 measurement with zone type: Area */
#define VSCP_TYPE_MEASUREZONE_AREA                                  52

/** VSCP class 1 measurement with zone type: Radiant intensity */
#define VSCP_TYPE_MEASUREZONE_RADIANT_INTENSITY                     53

/** VSCP class 1 measurement with zone type: Radiance */
#define VSCP_TYPE_MEASUREZONE_RADIANCE                              54

/** VSCP class 1 measurement with zone type: Irradiance Exitance Radiosity */
#define VSCP_TYPE_MEASUREZONE_IRRADIANCE_EXITANCE_RADIOSITY         55

/** VSCP class 1 measurement with zone type: Spectral radiance */
#define VSCP_TYPE_MEASUREZONE_SPECTRAL_RADIANCE                     56

/** VSCP class 1 measurement with zone type: Spectral irradiance */
#define VSCP_TYPE_MEASUREZONE_SPECTRAL_IRRADIANCE                   57

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

#endif  /* __VSCP_TYPE_MEASUREZONE_H__ */

/** @} */
