/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2025 Andreas Merkle
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
@brief  Measurement
@file   vscp_evt_measurement.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
Measurements are fetched from the SI units and from SI derived units. The SI unit (or the SI
derived unit) is also used as the default unit. As in the SI unit standard, names for a unit is in
lower case ("newton") and the unit ("N") is in upper case.

This file is automatically generated. Don't change it manually.

*******************************************************************************/

#ifndef __VSCP_EVT_MEASUREMENT_H__
#define __VSCP_EVT_MEASUREMENT_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "../user/vscp_platform.h"

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
extern BOOL vscp_evt_measurement_sendGeneralEvent(void);

/**
 * Count
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendCount(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Length/Distance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendLengthDistance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Mass
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendMass(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Time
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendTime(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Electric Current
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendElectricCurrent(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Temperature
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendTemperature(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Amount of substance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendAmountOfSubstance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Luminous Intensity (Intensity of light)
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendLuminousIntensityIntensityOfLight(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Frequency
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendFrequency(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Radioactivity and other random events
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRadioactivityAndOtherRandomEvents(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Force
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendForce(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Pressure
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendPressure(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Energy
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendEnergy(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Power
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendPower(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Electrical Charge
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendElectricalCharge(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Electrical Potential (Voltage)
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendElectricalPotentialVoltage(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Electrical Capacitance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendElectricalCapacitance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Electrical Resistance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendElectricalResistance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Electrical Conductance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendElectricalConductance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Magnetic Field Strength
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendMagneticFieldStrength(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Magnetic Flux
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendMagneticFlux(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Magnetic Flux Density
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendMagneticFluxDensity(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Inductance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendInductance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Luminous Flux
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendLuminousFlux(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Illuminance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendIlluminance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Radiation dose (absorbed)
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRadiationDoseAbsorbed(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Catalytic activity
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendCatalyticActivity(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Volume
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendVolume(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Sound intensity
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSoundIntensity(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Angle, direction or similar
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendAngleDirectionOrSimilar(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Position WGS 84
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendPositionWgs84(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Speed
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSpeed(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Acceleration
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendAcceleration(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Tension
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendTension(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Damp/moist (Hygrometer reading)
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendDampMoistHygrometerReading(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Flow
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendFlow(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Thermal resistance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendThermalResistance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Refractive (optical) power
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRefractiveOpticalPower(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Dynamic viscosity
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendDynamicViscosity(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Sound impedance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSoundImpedance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Sound resistance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSoundResistance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Electric elastance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendElectricElastance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Luminous energy
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendLuminousEnergy(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Luminance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendLuminance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Chemical (molar) concentration
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendChemicalMolarConcentration(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/* "Chemical (mass) concentration" not supported. No frame defined. */

/**
 * Reserved
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendReserved(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/* "Reserved" not supported. No frame defined. */

/**
 * Dew Point
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendDewPoint(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Relative Level
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRelativeLevel(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Altitude
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendAltitude(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Area
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendArea(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Radiant intensity
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRadiantIntensity(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Radiance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRadiance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Irradiance, Exitance, Radiosity
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendIrradianceExitanceRadiosity(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Spectral radiance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSpectralRadiance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Spectral irradiance
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSpectralIrradiance(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Sound pressure (acoustic pressure)
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSoundPressureAcousticPressure(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Sound energy density
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSoundEnergyDensity(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Sound level
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendSoundLevel(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Radiation dose (equivalent)
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRadiationDoseEquivalent(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Radiation dose (exposure)
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendRadiationDoseExposure(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Power factor
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendPowerFactor(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Reactive Power
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendReactivePower(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

/**
 * Reactive Energy
 * 
 * @param[in] index Index for sensor.
 * @param[in] unit The unit of the data.
 * @param[in] data The data as signed integer.
 * @param[in] exp The exponent of the data (10^exponent).
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement_sendReactiveEnergy(uint8_t index, uint8_t unit, int32_t data, int8_t exp);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_EVT_MEASUREMENT_H__ */
