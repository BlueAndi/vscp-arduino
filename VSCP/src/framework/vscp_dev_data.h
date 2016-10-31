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
@brief  VSCP device data
@file   vscp_dev_data.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module provides device (node) specific data.

*******************************************************************************/
/** @defgroup vscp_dev_data VSCP device data
 * This module contains device specific data access. The data itself can be set
 * during compile time via a C-define. Or they can be configured to be loaded
 * from the persistent memory. Decide this by adapting the @see vscp_dev_data_config.h
 *
 * Supported compile switches:
 * - VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE
 * - VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS
 *
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_DEV_DATA_H__
#define __VSCP_DEV_DATA_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <inttypes.h>
#include "vscp_types.h"

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

/** This type defines the device specific parameters, which can be modified
 * by the arduino top level class.
 */
typedef struct
{
    uint8_t guid[VSCP_GUID_SIZE];   /**< Node GUID */
    uint8_t zone;                   /**< Node zone */
    uint8_t subZone;                /**< Node sub zone */

} vscp_dev_data_Container;

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the module.
 */
extern void vscp_dev_data_init(void);

/**
 * This function set the device specific parameter.
 *
 * @param[in]   container   Data container
 */
extern void vscp_dev_data_set(vscp_dev_data_Container const * const container);

/**
 * This function restores factory default settings.
 */
extern void vscp_dev_data_restoreFactoryDefaultSettings(void);

/**
 * This function returns one byte of the GUID, which is selected by the index.
 * Index 0 corresponds with the GUID LSB byte, index 15 with the GUID MSB byte.
 *
 * @param[in]   index   Index in the GUID [0-15]
 * @return  GUID byte
 */
extern uint8_t  vscp_dev_data_getGUID(uint8_t index);

/**
 * This function returns the node zone.
 *
 * @return Node zone
 */
extern uint8_t  vscp_dev_data_getNodeZone(void);

/**
 * This function returns the node sub zone.
 *
 * @return Node sub zone
 */
extern uint8_t  vscp_dev_data_getNodeSubZone(void);

/**
 * This function returns one byte of the manufacturer device id at the given
 * @see index. If the index is out of bounce, a 0 will be returned.
 *
 * @param[in]   index   Index of the manufacturer device id [0..3]
 * @return  Manufacturer device id byte @see index
 */
extern uint8_t  vscp_dev_data_getManufacturerDevId(uint8_t index);

/**
 * This function returns one byte of the manufacturer sub device id at the given
 * @see index. If the index is out of bounce, a 0 will be returned.
 *
 * @param[in]   index   Index of the manufacturer sub device id [0..3]
 * @return  Manufacturer sub device id byte @see index
 */
extern uint8_t  vscp_dev_data_getManufacturerSubDevId(uint8_t index);

/**
 * This function returns one byte of the MDF URL, which is selected by the index.
 *
 * @param[in]   index   Index in the MDF URL
 * @return  MDF URL byte
 */
extern uint8_t  vscp_dev_data_getMdfUrl(uint8_t index);

/**
 * This function returns the firmware version major number.
 *
 * @return  Firmware version major number
 */
extern uint8_t  vscp_dev_data_getFirmwareVersionMajor(void);

/**
 * This function returns the firmware version minor number.
 *
 * @return  Firmware version minor number
 */
extern uint8_t  vscp_dev_data_getFirmwareVersionMinor(void);

/**
 * This function returns the firmware version sub minor number.
 *
 * @return  Firmware version sub minor number
 */
extern uint8_t  vscp_dev_data_getFirmwareVersionSubMinor(void);

/**
 * This function returns one byte of the standard device family code at the
 * given @see index.
 * If the family code is not supported, the family code will be 0.
 *
 * @param[in]   index   Index
 * @return  Standard device family code byte @see index
 */
extern uint8_t  vscp_dev_data_getStdDevFamilyCode(uint8_t index);

/**
 * This function returns one byte of the standard device type at the
 * given @see index.
 * If the family code is not supported, the family code will be 0.
 *
 * @param[in]   index   Index
 * @return  Standard device family code byte @see index
 */
extern uint8_t  vscp_dev_data_getStdDevType(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_DEV_DATA_H__ */

/** @} */
