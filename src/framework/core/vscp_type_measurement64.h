/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2024 Andreas Merkle
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
@brief  Double precision floating point measurement
@file   vscp_type_measurement64.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
Floating point double precision measurements. This class mirrors the standard measurement events is
CLASS1.MEASUREMENT=10. The measurement unit is always expressed in the standard unit.

This file is automatically generated. Don't change it manually.

*******************************************************************************/

#ifndef __VSCP_TYPE_MEASUREMENT64_H__
#define __VSCP_TYPE_MEASUREMENT64_H__

/** @defgroup vscp_type_measurement64 Double precision floating point measurement
 * Level 1 protocol class types
 * @{
 * @ingroup vscp_l1
 */

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

/**
 * General Event.
 */
#define VSCP_TYPE_MEASUREMENT64_GENERAL                      0

/**
 * This is a discrete value typical for a count. There is no unit for this measurement just a discrete
 * value.
 */
#define VSCP_TYPE_MEASUREMENT64_COUNT                        1

/**
 * Default unit: Meter.
 * This is a measurement of a length or a distance.
 */
#define VSCP_TYPE_MEASUREMENT64_LENGTH                       2

/**
 * Default unit: Kilogram.
 * This is a measurement of a mass.
 */
#define VSCP_TYPE_MEASUREMENT64_MASS                         3

/**
 * A time measurement.
 * Default unit: Seconds.
 * Opt. unit: (1) Milliseconds. Absolute: (2) y-y-m-d-h-m-s (binary). String: (3) "HHMMSS".
 */
#define VSCP_TYPE_MEASUREMENT64_TIME                         4

/**
 * Default unit: Ampere.
 * This is a measurement of an electric current.
 */
#define VSCP_TYPE_MEASUREMENT64_ELECTRIC_CURRENT             5

/**
 * Default unit: Kelvin.
 * Opt. unit: Degree Celsius (1), Fahrenheit (2)
 * This is a measurement of a temperature.
 */
#define VSCP_TYPE_MEASUREMENT64_TEMPERATURE                  6

/**
 * Default unit: Mole.
 * This is a measurement of an amount of a substance.
 */
#define VSCP_TYPE_MEASUREMENT64_AMOUNT_OF_SUBSTANCE          7

/**
 * Default unit: Candela.
 * This is a measurement of luminous intensity.
 */
#define VSCP_TYPE_MEASUREMENT64_INTENSITY_OF_LIGHT           8

/**
 * Default unit: Hertz.
 * This is a measurement of regular events during a second.
 */
#define VSCP_TYPE_MEASUREMENT64_FREQUENCY                    9

/**
 * Default unit: becquerel.
 * Optional unit: curie (1)
 * This is a measurement of rates of things, which happen randomly, or are unpredictable.
 */
#define VSCP_TYPE_MEASUREMENT64_RADIOACTIVITY                10

/**
 * Default unit: newton.
 * This is a measurement of force.
 */
#define VSCP_TYPE_MEASUREMENT64_FORCE                        11

/**
 * Default unit: pascal.
 * Opt. unit: bar (1), psi (2)
 * This is a measurement of pressure.
 */
#define VSCP_TYPE_MEASUREMENT64_PRESSURE                     12

/**
 * Default unit: Joule.
 * Optional unit: KWh (1)
 * This is a measurement of energy.
 */
#define VSCP_TYPE_MEASUREMENT64_ENERGY                       13

/**
 * Default unit: watt.
 * Optional unit: Horse power (1).
 * This is a measurement of power.
 */
#define VSCP_TYPE_MEASUREMENT64_POWER                        14

/**
 * Default unit: coulomb.
 * This is a measurement electrical charge.
 */
#define VSCP_TYPE_MEASUREMENT64_ELECTRICAL_CHARGE            15

/**
 * Default unit: volt.
 * This is a measurement of electrical potential.
 */
#define VSCP_TYPE_MEASUREMENT64_ELECTRICAL_POTENTIAL         16

/**
 * Default unit: farad (F).
 * This is a measurement of electric capacitance.
 */
#define VSCP_TYPE_MEASUREMENT64_ELECTRICAL_CAPACITANCE       17

/**
 * Default unit: ohm (Ω).
 * This is a measurement of resistance.
 */
#define VSCP_TYPE_MEASUREMENT64_ELECTRICAL_RESISTANCE        18

/**
 * Default unit: siemens.
 * This is a measurement of electrical conductance.
 */
#define VSCP_TYPE_MEASUREMENT64_ELECTRICAL_CONDUCTANCE       19

/**
 * Default unit: amperes per meter (H).
 * Optional units: teslas (B) (1)
 * This is a measurement of magnetic field strength.
 */
#define VSCP_TYPE_MEASUREMENT64_MAGNETIC_FIELD_STRENGTH      20

/**
 * Default unit: weber (Wb).
 * This is a measurement of magnetic flux.
 */
#define VSCP_TYPE_MEASUREMENT64_MAGNETIC_FLUX                21

/**
 * Default unit: tesla (B).
 * Optional units: Gauss (1)
 * This is a measurement of flux density or field strength for magnetic fields (also called the
 * magnetic induction).
 */
#define VSCP_TYPE_MEASUREMENT64_MAGNETIC_FLUX_DENSITY        22

/**
 * Default unit: henry (H).
 * This is a measurement of inductance.
 */
#define VSCP_TYPE_MEASUREMENT64_INDUCTANCE                   23

/**
 * Default unit: Lumen (lm= cd * sr)
 * This is a measurement of luminous Flux.
 */
#define VSCP_TYPE_MEASUREMENT64_FLUX_OF_LIGHT                24

/**
 * Default unit: lux (lx) ( lx = lm / m² )
 * This is used to express both Illuminance (incidence of light) and Luminous Emittance (emission of
 * light).
 */
#define VSCP_TYPE_MEASUREMENT64_ILLUMINANCE                  25

/**
 * Default unit: gray (Gy).
 * This is a measurement of a radiation dose (Absorbed dose of ionizing radiation).
 */
#define VSCP_TYPE_MEASUREMENT64_RADIATION_DOSE_ABSORBED      26

/**
 * Default unit: katal (kat).
 * This is a measurement of catalytic activity used in biochemistry.
 */
#define VSCP_TYPE_MEASUREMENT64_CATALYTIC_ACITIVITY          27

/**
 * Default unit: cubic meter (m³)
 * Opt. unit: Liter (dm³) (1), decilitre (100 cm³) (2), centilitre (10 cm³) (3), millilitre (cm³) (4)
 * where unit 4 is only available for Level II measurement events where units can hold this value.
 * This is a measurement of volume.
 */
#define VSCP_TYPE_MEASUREMENT64_VOLUME                       28

/**
 * Default unit: W/m2, watt per square meter.
 * This is a measurement of sound intensity (acoustic intensity).
 */
#define VSCP_TYPE_MEASUREMENT64_SOUND_INTENSITY              29

/**
 * Default unit: radian (rad) (Plane angles).
 * Opt Unit: degree (1).
 * Opt Unit: arcminute (2).
 * Opt Unit: arcseconds (3).
 * This is a measurement of an angle.
 */
#define VSCP_TYPE_MEASUREMENT64_ANGLE                        30

/**
 * Default unit: Longitude.
 * Opt. unit: Latitude.
 * This is a (decimal) measurement of a position as of WGS 84. Normally given as a floating point
 * value. See ./class1.gps.md for a better candidate to use for position data.
 */
#define VSCP_TYPE_MEASUREMENT64_POSITION                     31

/**
 * Default unit: Meters per second.
 * Optional unit: Kilometers per hour (1) Miles per hour (2)
 * This is a measurement of a speed.
 */
#define VSCP_TYPE_MEASUREMENT64_SPEED                        32

/**
 * Default unit: Meters per second/second (m/s2).
 * This is a measurement of acceleration.
 */
#define VSCP_TYPE_MEASUREMENT64_ACCELERATION                 33

/**
 * Default unit: N/m.
 * This is a measurement of tension.
 */
#define VSCP_TYPE_MEASUREMENT64_TENSION                      34

/**
 * Default unit: Relative percentage 0-100%.
 * This is a measurement of relative moistness (Humidity).
 */
#define VSCP_TYPE_MEASUREMENT64_HUMIDITY                     35

/**
 * Default unit: Cubic meters/second.
 * Opt Unit: Liters/Second.
 * This is a measurement of flow.
 */
#define VSCP_TYPE_MEASUREMENT64_FLOW                         36

/**
 * Default unit: Thermal ohm K/W.
 * This is a measurement of thermal resistance.
 */
#define VSCP_TYPE_MEASUREMENT64_THERMAL_RESISTANCE           37

/**
 * Default unit: dioptre (dpt) m-1.
 * This is a measurement of refractive (optical) power.
 */
#define VSCP_TYPE_MEASUREMENT64_REFRACTIVE_POWER             38

/**
 * Default unit: pascal second
 * Optional units: poiseuille (Pl) = 1, poise (P) = 2
 * This is a measurement of dynamic viscosity.
 */
#define VSCP_TYPE_MEASUREMENT64_DYNAMIC_VISCOSITY            39

/**
 * Default unit: rayl (Pa·s/m)
 * This is a measurement of sound impedance.
 */
#define VSCP_TYPE_MEASUREMENT64_SOUND_IMPEDANCE              40

/**
 * Default unit: Acoustic ohm Pa · s/ m³.
 * This is a measurement of sound resistance.
 */
#define VSCP_TYPE_MEASUREMENT64_SOUND_RESISTANCE             41

/**
 * Default unit: daraf (f-1).
 * This is a measurement of electric elasticity.
 */
#define VSCP_TYPE_MEASUREMENT64_ELECTRIC_ELASTANCE           42

/**
 * Default unit: talbot ( tb = lm * s)
 * This is a measurement of luminous energy.
 */
#define VSCP_TYPE_MEASUREMENT64_LUMINOUS_ENERGY              43

/**
 * Default unit: cd / m²) (non SI unit = nit)
 * This is a measurement of luminance.
 */
#define VSCP_TYPE_MEASUREMENT64_LUMINANCE                    44

/**
 * Default unit: mol/m³.
 * This is a measurement of chemical mol/ppm/percent concentration.
 */
#define VSCP_TYPE_MEASUREMENT64_CHEMICAL_CONCENTRATION_MOLAR 45

/**
 * Default unit: mol/m³.
 * This is a measurement of chemical mass concentration.
 */
#define VSCP_TYPE_MEASUREMENT64_CHEMICAL_CONCENTRATION_MASS  46

/**
 * Reserved.
 */
#define VSCP_TYPE_MEASUREMENT64_RESERVED47                   47

/**
 * Reserved (was doublet of Type= 24, do not use any longer!)
 */
#define VSCP_TYPE_MEASUREMENT64_RESERVED48                   48

/**
 * Default unit: Kelvin.
 * Opt. unit: Degree Celsius (1), Fahrenheit (2)
 * This is a measurement of the Dew Point.
 */
#define VSCP_TYPE_MEASUREMENT64_DEWPOINT                     49

/**
 * Default unit: Relative value.
 * This is a relative value for a level measurement without a unit. It is just relative to the min/max
 * value for the selected data representation, typically percentage or per mille or similar.
 */
#define VSCP_TYPE_MEASUREMENT64_RELATIVE_LEVEL               50

/**
 * Default unit: Meter.
 * Opt. unit: Feet(1), inches (2)
 * Altitude in meters.
 */
#define VSCP_TYPE_MEASUREMENT64_ALTITUDE                     51

/**
 * Default unit: square meter (m²)
 * Area in square meter.
 */
#define VSCP_TYPE_MEASUREMENT64_AREA                         52

/**
 * Default unit: watt per steradian ( W / sr )
 * Radiated power per room angle.
 */
#define VSCP_TYPE_MEASUREMENT64_RADIANT_INTENSITY            53

/**
 * Default unit: watt per steradian per square metre ( W / (sr * m²) )
 * This is the radiant flux emitted, reflected, transmitted or received by a surface.
 */
#define VSCP_TYPE_MEASUREMENT64_RADIANCE                     54

/**
 * Default unit: watt per square metre ( W / m² )
 * Power emitted from or striking onto a surface or area.
 */
#define VSCP_TYPE_MEASUREMENT64_IRRADIANCE                   55

/**
 * Default unit: watt per steradian per square metre per nm (W·sr-1·m-2·nm-1)
 * Opt. unit: watt per steradian per meter3 (W·sr-1·m-3) (1), watt per steradian per square metre per
 * hertz (W·sr-1·m-3) (2)
 * Radiance of a surface per unit frequency or wavelength.
 */
#define VSCP_TYPE_MEASUREMENT64_SPECTRAL_RADIANCE            56

/**
 * Default unit: watt per square metre per nm (W·m-2·nm-1)
 * Opt. unit: watt per metre3 (W·m-3) (1), watt per square metre per hertz (W·m-2·Hz-1) (2)
 * Irradiance of a surface per unit frequency or wavelength.
 */
#define VSCP_TYPE_MEASUREMENT64_SPECTRAL_IRRADIANCE          57

/**
 * Default unit: pascal (Pa)
 * This is a measurement of sound pressure (acoustic pressure).
 */
#define VSCP_TYPE_MEASUREMENT64_SOUND_PRESSURE               58

/**
 * Default unit: pascal (Pa)
 * Sound energy density or sound density is the sound energy per unit volume.
 */
#define VSCP_TYPE_MEASUREMENT64_SOUND_DENSITY                59

/**
 * Default unit: decibel (dB)
 * Sound level expressed in decibel. This event is supplied for convenience.
 */
#define VSCP_TYPE_MEASUREMENT64_SOUND_LEVEL                  60

/**
 * Default unit: sievert (Sv).
 * Optional unit rem (1)
 * This is a measurement of a radiation dose (Equivalent dose of ionizing radiation).
 */
#define VSCP_TYPE_MEASUREMENT64_DOSE_EQUIVALENT              61

/**
 * Default unit: coulomb per kilogram (C/kg).
 * Optional unit: Röntgen/R (1)
 * This is a measurement of a radiation dose (Exposed dose of ionizing radiation).
 */
#define VSCP_TYPE_MEASUREMENT64_RADIATION_DOSE_EXPOSURE      62

/**
 * Default unit: cos of phase angle.
 * This is a measurment of a power factor. Power factor is an expression of energy efficiency. It is
 * usually expressed as a percentage - and the lower the percentage, the less efficient power usage
 * is.
 */
#define VSCP_TYPE_MEASUREMENT64_POWER_FACTOR                 63

/**
 * Default unit: VAr
 * In electric power transmission and distribution, volt-ampere reactive (VAr) is a unit of
 * measurement of reactive power. Reactive power exists in AC circuit when the current and voltage are
 * not in phase.
 */
#define VSCP_TYPE_MEASUREMENT64_REACTIVE_POWER               64

/**
 * Default unit: kVArh
 * Reactive energy is the electrical energy produced, flowing or supplied by an electric circuit
 * during a time interval, measured in units of kVArh or standard multiples thereof.
 */
#define VSCP_TYPE_MEASUREMENT64_REACTIVE_ENERGY              65

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

#endif  /* __VSCP_TYPE_MEASUREMENT64_H__ */

/** @} */
