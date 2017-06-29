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
@brief  VSCP device data default configuration
@file   vscp_dev_data_config.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the device specific default data configuration.

*******************************************************************************/
/** @defgroup vscp_dev_data_config Device default data configuration
 * The device default data configuration moves all device specific data to
 * the persistent memory and set some default values.
 *
 * Please don't change anything in this file and use the overwrite mechanism
 * by setting your prefered configuration in vscp_dev_data_config_overwrite.h
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_DEV_DATA_CONFIG_H__
#define __VSCP_DEV_DATA_CONFIG_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_config_base.h"
#include "vscp_dev_data_config_overwrite.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE

/** Enable the support of the family code */
#define VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE                             VSCP_CONFIG_BASE_ENABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE */

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS

/** Enable this define to load the GUID from persistent storage. */
#define VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS                         VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS */

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS

/** Enable this define to load the GUID from persistent storage. */
#define VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS                    VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS */

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS

/** Enable this define to load the GUID from persistent storage. */
#define VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS                VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS */

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS

/** Enable this define to load the manufacturer device id from persistent storage. */
#define VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS          VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS */

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS

/** Enable this define to load the manufacturer sub device id from persistent storage. */
#define VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS      VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS */

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS

/** Enable this define to load the MDF URL from persistent storage. */
#define VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS                      VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE )

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS

/** Enable this define to load the standard device family code from persistent storage.
 * Note, that the feature family code has to be enabled, otherwise this define won't be
 * considered.
 */
#define VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS          VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS */

#ifndef VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS

/** Enable this define to load the standard device type from persistent storage.
 * Note, that the feature family code has to be enabled, otherwise this define won't be
 * considered.
 */
#define VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS                 VSCP_CONFIG_BASE_DISABLED

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE ) */

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

#ifndef VSCP_DEV_DATA_CONFIG_NODE_GUID

/** Node GUID as hex string.
 * If you need your own GUID and its used only for in-house local use, see
 * VSCP v1.10.15, chapter Globally Unique Identifiers for pre-defined GUIDs.
 *
 * For development purposes you can use:
 * 00 00 00 00 00 00 00 00 00 00 00 00 xx xx xx xx
 */
#define VSCP_DEV_DATA_CONFIG_NODE_GUID                      { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_NODE_GUID */

#ifndef VSCP_DEV_DATA_CONFIG_NODE_ZONE

/** Node zone. Note, 0xff means all zones. */
#define VSCP_DEV_DATA_CONFIG_NODE_ZONE                      (0xff)

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_NODE_ZONE */

#ifndef VSCP_DEV_DATA_CONFIG_NODE_SUB_ZONE

/** Node zone. Note, 0xff means all sub zones. */
#define VSCP_DEV_DATA_CONFIG_NODE_SUB_ZONE                  (0xff)

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_NODE_SUB_ZONE */

#ifndef VSCP_DEV_DATA_CONFIG_MANUFACTURER_ID

/** Manufacturer:
 * 0x0000 - Unknown
 */
#define VSCP_DEV_DATA_CONFIG_MANUFACTURER_ID                ((uint16_t)0x0000)

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_MANUFACTURER_ID */

#ifndef VSCP_DEV_DATA_CONFIG_MANUFACTURER_DEVICE_ID

/** Manufacturer device id */
#define VSCP_DEV_DATA_CONFIG_MANUFACTURER_DEVICE_ID         ((uint32_t)0x00000000)

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_MANUFACTURER_DEVICE_ID */

#ifndef VSCP_DEV_DATA_CONFIG_MANUFACTURER_SUB_DEVICE_ID

/** Manufacturer sub device id */
#define VSCP_DEV_DATA_CONFIG_MANUFACTURER_SUB_DEVICE_ID     ((uint32_t)0x00000000)

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_MANUFACTURER_SUB_DEVICE_ID */

#ifndef VSCP_DEV_DATA_CONFIG_MDF_URL

/** MDF URL (only 32 characters are allowed!), without "http://" which is implied
 * Note, the encoding is UTF-8!
 */
#define VSCP_DEV_DATA_CONFIG_MDF_URL                        ""
/*                                                        -->12345678901234567890123456789012<-- */

#endif  /* VSCP_DEV_DATA_CONFIG_MDF_URL */

#ifndef VSCP_DEV_DATA_CONFIG_VERSION_MAJOR

/** Major firmware version (format: major.minor.sub-minor) */
#define VSCP_DEV_DATA_CONFIG_VERSION_MAJOR                  0

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_VERSION_MAJOR */

#ifndef VSCP_DEV_DATA_CONFIG_VERSION_MINOR

/** Minor firmware version (format: major.minor.sub-minor) */
#define VSCP_DEV_DATA_CONFIG_VERSION_MINOR                  1

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_VERSION_MINOR */

#ifndef VSCP_DEV_DATA_CONFIG_VERSION_SUB_MINOR

/** Sub-minor firmware version (format: major.minor.sub-minor) */
#define VSCP_DEV_DATA_CONFIG_VERSION_SUB_MINOR              0

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_VERSION_SUB_MINOR */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE )

#ifndef VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_FAMILY_CODE

/** Standard device family code. */
#define VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_FAMILY_CODE    ((uint32_t)0x00000000)

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_FAMILY_CODE */

#ifndef VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_TYPE

/** Standard device type. */
#define VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_TYPE           ((uint32_t)0x00000000)

#endif  /* Undefined VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_TYPE */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE ) */

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

#endif  /* __VSCP_DEV_DATA_CONFIG_H__ */

/** @} */
