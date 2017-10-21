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
@brief  VSCP class 1 measurement types
@file   vscp_type_measurement.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 measurement class defined types.

*******************************************************************************/
/** @defgroup vscp_type_measurement Measurement class types
 * Level 1 measurement class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_MEASUREMENT_H__
#define __VSCP_TYPE_MEASUREMENT_H__

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

/** VSCP class 1 measurement type: Undefined */
#define VSCP_TYPE_MEASUREMENT_UNDEFINED                             0

/** VSCP class 1 measurement type: Count */
#define VSCP_TYPE_MEASUREMENT_COUNT                                 1

/** VSCP class 1 measurement type: Length Distance */
#define VSCP_TYPE_MEASUREMENT_LENGTH_DISTANCE                       2

/** VSCP class 1 measurement type: Mass */
#define VSCP_TYPE_MEASUREMENT_MASS                                  3

/** VSCP class 1 measurement type: Time */
#define VSCP_TYPE_MEASUREMENT_TIME                                  4

/** VSCP class 1 measurement type: Electric Current */
#define VSCP_TYPE_MEASUREMENT_ELECTRIC_CURRENT                      5

/** VSCP class 1 measurement type: Temperature */
#define VSCP_TYPE_MEASUREMENT_TEMPERATURE                           6

/** VSCP class 1 measurement type: Amount of substance */
#define VSCP_TYPE_MEASUREMENT_AMOUNT_OF_SUBSTANCE                   7

/** VSCP class 1 measurement type: Luminous Intensity */
#define VSCP_TYPE_MEASUREMENT_LUMINOUS_INTENSITY                    8

/** VSCP class 1 measurement type: Frequency */
#define VSCP_TYPE_MEASUREMENT_FREQUENCY                             9

/** VSCP class 1 measurement type: Radioactivity and other random events */
#define VSCP_TYPE_MEASUREMENT_RADIOACTIVITY_AND_OTHER_RANDOM_EVENTS 10

/** VSCP class 1 measurement type: Force */
#define VSCP_TYPE_MEASUREMENT_FORCE                                 11

/** VSCP class 1 measurement type: Pressure */
#define VSCP_TYPE_MEASUREMENT_PRESSURE                              12

/** VSCP class 1 measurement type: Energy */
#define VSCP_TYPE_MEASUREMENT_ENERGY                                13

/** VSCP class 1 measurement type: Power */
#define VSCP_TYPE_MEASUREMENT_POWER                                 14

/** VSCP class 1 measurement type: Electrical Charge */
#define VSCP_TYPE_MEASUREMENT_ELECTRICAL_CHARGE                     15

/** VSCP class 1 measurement type: Electrical Potential (Voltage) */
#define VSCP_TYPE_MEASUREMENT_ELECTRICAL_POTENTIAL                  16

/** VSCP class 1 measurement type: Electrical Capacitance */
#define VSCP_TYPE_MEASUREMENT_ELECTRICAL_CAPACITANCE                17

/** VSCP class 1 measurement type: Electrical Resistance */
#define VSCP_TYPE_MEASUREMENT_ELECTRICAL_RESISTANCE                 18

/** VSCP class 1 measurement type: Electrical Conductance */
#define VSCP_TYPE_MEASUREMENT_ELECTRICAL_CONDUCTANCE                19

/** VSCP class 1 measurement type: Magnetic Field Strength */
#define VSCP_TYPE_MEASUREMENT_MAGNETIC_FIELD_STRENGTH               20

/** VSCP class 1 measurement type: Magnetic Flux */
#define VSCP_TYPE_MEASUREMENT_MAGNETIC_FLUX                         21

/** VSCP class 1 measurement type: Magnetic Flux Density */
#define VSCP_TYPE_MEASUREMENT_MAGNETIC_FLUX_DENSITY                 22

/** VSCP class 1 measurement type: Inductance */
#define VSCP_TYPE_MEASUREMENT_INDUCTANCE                            23

/** VSCP class 1 measurement type: Luminous Flux */
#define VSCP_TYPE_MEASUREMENT_LUMINOUS_FLUX                         24

/** VSCP class 1 measurement type: Illuminance */
#define VSCP_TYPE_MEASUREMENT_ILLUMINANCE                           25

/** VSCP class 1 measurement type: Radiation dose */
#define VSCP_TYPE_MEASUREMENT_RADIATION_DOSE                        26

/** VSCP class 1 measurement type: Catalytic activity */
#define VSCP_TYPE_MEASUREMENT_CATALYTIC_ACTIVITY                    27

/** VSCP class 1 measurement type: Volume */
#define VSCP_TYPE_MEASUREMENT_VOLUME                                28

/** VSCP class 1 measurement type: Sound intensity */
#define VSCP_TYPE_MEASUREMENT_SOUND_INTENSITY                       29

/** VSCP class 1 measurement type: Angle */
#define VSCP_TYPE_MEASUREMENT_ANGLE                                 30

/** VSCP class 1 measurement type: Position */
#define VSCP_TYPE_MEASUREMENT_POSITION                              31

/** VSCP class 1 measurement type: Speed */
#define VSCP_TYPE_MEASUREMENT_SPEED                                 32

/** VSCP class 1 measurement type: Acceleration */
#define VSCP_TYPE_MEASUREMENT_ACCELERATION                          33

/** VSCP class 1 measurement type: Tension */
#define VSCP_TYPE_MEASUREMENT_TENSION                               34

/** VSCP class 1 measurement type: Damp moist (Hygrometer reading) */
#define VSCP_TYPE_MEASUREMENT_DAMP_MOIST                            35

/** VSCP class 1 measurement type: Flow */
#define VSCP_TYPE_MEASUREMENT_FLOW                                  36

/** VSCP class 1 measurement type: Thermal resistance */
#define VSCP_TYPE_MEASUREMENT_THERMAL_RESISTANCE                    37

/** VSCP class 1 measurement type: Refractive power */
#define VSCP_TYPE_MEASUREMENT_REFRACTIVE_POWER                      38

/** VSCP class 1 measurement type: Dynamic viscosity */
#define VSCP_TYPE_MEASUREMENT_DYNAMIC_VISCOSITY                     39

/** VSCP class 1 measurement type: Sound impedance */
#define VSCP_TYPE_MEASUREMENT_SOUND_IMPEDANCE                       40

/** VSCP class 1 measurement type: Sound resistance */
#define VSCP_TYPE_MEASUREMENT_SOUND_RESISTANCE                      41

/** VSCP class 1 measurement type: Electric elastance */
#define VSCP_TYPE_MEASUREMENT_ELECTRIC_ELASTANCE                    42

/** VSCP class 1 measurement type: Luminous energy */
#define VSCP_TYPE_MEASUREMENT_LUMINOUS_ENERGY                       43

/** VSCP class 1 measurement type: Luminance */
#define VSCP_TYPE_MEASUREMENT_LUMINANCE                             44

/** VSCP class 1 measurement type: Chemical concentration */
#define VSCP_TYPE_MEASUREMENT_CHEMICAL_CONCENTRATION                45

/** VSCP class 1 measurement type: Reserved */
#define VSCP_TYPE_MEASUREMENT_RESERVED_46                           46

/** VSCP class 1 measurement type: Dose equivalent */
#define VSCP_TYPE_MEASUREMENT_DOSE_EQUIVALENT                       47

/** VSCP class 1 measurement type: Reserved */
#define VSCP_TYPE_MEASUREMENT_RESERVED_48                           48

/** VSCP class 1 measurement type: Dew Point */
#define VSCP_TYPE_MEASUREMENT_DEW_POINT                             49

/** VSCP class 1 measurement type: Relative Level */
#define VSCP_TYPE_MEASUREMENT_RELATIVE_LEVEL                        50

/** VSCP class 1 measurement type: Altitude  */
#define VSCP_TYPE_MEASUREMENT_ALTITUDE                              51

/** VSCP class 1 measurement type: Area */
#define VSCP_TYPE_MEASUREMENT_AREA                                  52

/** VSCP class 1 measurement type: Radiant intensity */
#define VSCP_TYPE_MEASUREMENT_RADIANT_INTENSITY                     53

/** VSCP class 1 measurement type: Radiance */
#define VSCP_TYPE_MEASUREMENT_RADIANCE                              54

/** VSCP class 1 measurement type: Irradiance Exitance Radiosity */
#define VSCP_TYPE_MEASUREMENT_IRRADIANCE_EXITANCE_RADIOSITY         55

/** VSCP class 1 measurement type: Spectral radiance */
#define VSCP_TYPE_MEASUREMENT_SPECTRAL_RADIANCE                     56

/** VSCP class 1 measurement type: Spectral irradiance */
#define VSCP_TYPE_MEASUREMENT_SPECTRAL_IRRADIANCE                   57

/** VSCP class 1 measurement type: Sound pressure */
#define VSCP_TYPE_MEASUREMENT_SOUND_PRESSURE                        58

/** VSCP class 1 measurement type: Sound density */
#define VSCP_TYPE_MEASUREMENT_SOUND_DENSITY                         59

/** VSCP class 1 measurement type: Sound level */
#define VSCP_TYPE_MEASUREMENT_SOUND_LEVEL                           60

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

#endif  /* __VSCP_TYPE_MEASUREMENT_H__ */

/** @} */
