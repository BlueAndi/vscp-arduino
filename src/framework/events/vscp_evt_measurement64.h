/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2022 Andreas Merkle
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
@file   vscp_evt_measurement64.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
Floating point double precision measurements. This class mirrors the standard measurement events is
CLASS1.MEASUREMENT=10. The measurement unit is always expressed in the standard unit.

This file is automatically generated. Don't change it manually.

*******************************************************************************/

#ifndef __VSCP_EVT_MEASUREMENT64_H__
#define __VSCP_EVT_MEASUREMENT64_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "..\user\vscp_platform.h"
#include <math.h>

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

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

/**
 * General event
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendGeneralEvent(void);

/**
 * Count
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendCount(double_t value);

/**
 * Length/Distance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendLengthDistance(double_t value);

/**
 * Mass
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendMass(double_t value);

/**
 * Time
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendTime(double_t value);

/**
 * Electric Current
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendElectricCurrent(double_t value);

/**
 * Temperature
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendTemperature(double_t value);

/**
 * Amount of substance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendAmountOfSubstance(double_t value);

/**
 * Luminous Intensity (Intensity of light)
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendLuminousIntensityIntensityOfLight(double_t value);

/**
 * Frequency
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendFrequency(double_t value);

/**
 * Radioactivity and other random events
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRadioactivityAndOtherRandomEvents(double_t value);

/**
 * Force
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendForce(double_t value);

/**
 * Pressure
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendPressure(double_t value);

/**
 * Energy
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendEnergy(double_t value);

/**
 * Power
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendPower(double_t value);

/**
 * Electrical Charge
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendElectricalCharge(double_t value);

/**
 * Electrical Potential (Voltage)
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendElectricalPotentialVoltage(double_t value);

/**
 * Electrical Capacitance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendElectricalCapacitance(double_t value);

/**
 * Electrical Resistance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendElectricalResistance(double_t value);

/**
 * Electrical Conductance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendElectricalConductance(double_t value);

/**
 * Magnetic Field Strength
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendMagneticFieldStrength(double_t value);

/**
 * Magnetic Flux
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendMagneticFlux(double_t value);

/**
 * Magnetic Flux Density
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendMagneticFluxDensity(double_t value);

/**
 * Inductance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendInductance(double_t value);

/**
 * Luminous Flux
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendLuminousFlux(double_t value);

/**
 * Illuminance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendIlluminance(double_t value);

/**
 * Radiation dose
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRadiationDose(double_t value);

/**
 * Catalytic activity
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendCatalyticActivity(double_t value);

/**
 * Volume
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendVolume(double_t value);

/**
 * Sound intensity
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSoundIntensity(double_t value);

/**
 * Angle
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendAngle(double_t value);

/**
 * Position WGS 84
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendPositionWgs84(double_t value);

/**
 * Speed
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSpeed(double_t value);

/**
 * Acceleration
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendAcceleration(double_t value);

/**
 * Tension
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendTension(double_t value);

/**
 * Damp/moist (Hygrometer reading)
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendDampMoistHygrometerReading(double_t value);

/**
 * Flow
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendFlow(double_t value);

/**
 * Thermal resistance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendThermalResistance(double_t value);

/**
 * Refractive (optical) power
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRefractiveOpticalPower(double_t value);

/**
 * Dynamic viscosity
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendDynamicViscosity(double_t value);

/**
 * Sound impedance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSoundImpedance(double_t value);

/**
 * Sound resistance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSoundResistance(double_t value);

/**
 * Electric elastance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendElectricElastance(double_t value);

/**
 * Luminous energy
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendLuminousEnergy(double_t value);

/**
 * Luminance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendLuminance(double_t value);

/**
 * Chemical concentration
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendChemicalConcentration(double_t value);

/* "Reserved" not supported. No frame defined. */

/**
 * Dose equivalent
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendDoseEquivalent(double_t value);

/* "Reserved" not supported. No frame defined. */

/**
 * Dew Point
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendDewPoint(double_t value);

/**
 * Relative Level
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRelativeLevel(double_t value);

/**
 * Altitude
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendAltitude(double_t value);

/**
 * Area
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendArea(double_t value);

/**
 * Radiant intensity
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRadiantIntensity(double_t value);

/**
 * Radiance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRadiance(double_t value);

/**
 * Irradiance, Exitance, Radiosity
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendIrradianceExitanceRadiosity(double_t value);

/**
 * Spectral radiance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSpectralRadiance(double_t value);

/**
 * Spectral irradiance
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSpectralIrradiance(double_t value);

/**
 * Sound pressure (acoustic pressure)
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSoundPressureAcousticPressure(double_t value);

/**
 * Sound energy density
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSoundEnergyDensity(double_t value);

/**
 * Sound level
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendSoundLevel(double_t value);

/**
 * Radiation dose (equivalent)
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRadiationDoseEquivalent(double_t value);

/**
 * Radiation dose (exposure)
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendRadiationDoseExposure(double_t value);

/**
 * Power factor
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendPowerFactor(double_t value);

/**
 * Reactive Power
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendReactivePower(double_t value);

/**
 * Reactive Energy
 * 
 * @param[in] value The value is a "double" - IEEE-754, 64 Bits, double precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement64_sendReactiveEnergy(double_t value);

#endif  /* __VSCP_EVT_MEASUREMENT64_H__ */
