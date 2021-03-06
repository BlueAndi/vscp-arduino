/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2021, Andreas Merkle
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
@brief  Single precision floating point measurement
@file   vscp_evt_measurement32.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
Floating point single precision measurements. This class mirrors the standard measurement events is
CLASS1.MEASUREMENT=10. The measurement unit is always the standard unit.

This file is automatically generated. Don't change it manually.

*******************************************************************************/

#ifndef __VSCP_EVT_MEASUREMENT32_H__
#define __VSCP_EVT_MEASUREMENT32_H__

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
extern BOOL vscp_evt_measurement32_sendGeneralEvent(void);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendCount(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendLengthDistance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendMass(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendTime(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendElectricCurrent(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendTemperature(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendAmountOfSubstance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendLuminousIntensityIntensityOfLight(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendFrequency(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendRadioactivityAndOtherRandomEvents(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendForce(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendPressure(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendEnergy(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendPower(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendElectricalCharge(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendElectricalPotentialVoltage(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendElectricalCapacitance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendElectricalResistance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendElectricalConductance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendMagneticFieldStrength(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendMagneticFlux(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendMagneticFluxDensity(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendInductance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendLuminousFlux(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendIlluminance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendRadiationDose(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendCatalyticActivity(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendVolume(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSoundIntensity(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendAngle(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendPositionWgs84(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSpeed(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendAcceleration(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendTension(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendDampMoistHygrometerReading(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendFlow(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendThermalResistance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendRefractiveOpticalPower(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendDynamicViscosity(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSoundImpedance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSoundResistance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendElectricElastance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendLuminousEnergy(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendLuminance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendChemicalConcentration(float_t value);

/* "Reserved" not supported. No frame defined. */

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendDoseEquivalent(float_t value);

/* "Reserved" not supported. No frame defined. */

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendDewPoint(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendRelativeLevel(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendAltitude(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendArea(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendRadiantIntensity(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendRadiance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendIrradianceExitanceRadiosity(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSpectralRadiance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSpectralIrradiance(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSoundPressureAcousticPressure(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSoundEnergyDensity(float_t value);

/**
 * Count
 * 
 * @param[in] value The value is a "float" - IEEE-754, 32 Bits, single precision.
 * 
 * @return If event is sent, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_evt_measurement32_sendSoundLevel(float_t value);

#endif  /* __VSCP_EVT_MEASUREMENT32_H__ */
