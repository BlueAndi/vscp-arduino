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
@brief  VSCP device data configuration overwrite
@file   vscp_dev_data_config_overwrite.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains the device specific data configuration preferred by the
user. It overwrites the default configuration in vscp_dev_data_config.h

*******************************************************************************/
/** @defgroup vscp_dev_data_config_overwrite VSCP device data configuration overwrite
 * This module contains the device specific data configuration preferred by the
 * user. It overwrites the default configuration in vscp_dev_data_config.h
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_DEV_DATA_CONFIG_OVERWRITE_H__
#define __VSCP_DEV_DATA_CONFIG_OVERWRITE_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/* ---------- Define here your preferred configuration setup. ---------- */

/*

#define VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE                         VSCP_CONFIG_BASE_ENABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS                     VSCP_CONFIG_BASE_DISABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS                VSCP_CONFIG_BASE_DISABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS            VSCP_CONFIG_BASE_DISABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS      VSCP_CONFIG_BASE_DISABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS  VSCP_CONFIG_BASE_DISABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS                  VSCP_CONFIG_BASE_DISABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS      VSCP_CONFIG_BASE_DISABLED

#define VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS             VSCP_CONFIG_BASE_DISABLED

*/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

/* ---------- Define here your preferred configuration setup. ---------- */

/*

#define VSCP_DEV_DATA_CONFIG_NODE_GUID                      { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

#define VSCP_DEV_DATA_CONFIG_NODE_ZONE                      (0xff)

#define VSCP_DEV_DATA_CONFIG_NODE_SUB_ZONE                  (0xff)

#define VSCP_DEV_DATA_CONFIG_MANUFACTURER_ID                ((uint16_t)0x0000)

#define VSCP_DEV_DATA_CONFIG_MANUFACTURER_DEVICE_ID         ((uint32_t)0x00000000)

#define VSCP_DEV_DATA_CONFIG_MANUFACTURER_SUB_DEVICE_ID     ((uint32_t)0x00000000)

#define VSCP_DEV_DATA_CONFIG_MDF_URL                        "www.blue-andi.de/vscp/rb01.mdf"

#define VSCP_DEV_DATA_CONFIG_VERSION_MAJOR                  0

#define VSCP_DEV_DATA_CONFIG_VERSION_MINOR                  1

#define VSCP_DEV_DATA_CONFIG_VERSION_SUB_MINOR              0

#define VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_FAMILY_CODE    ((uint32_t)0x00000000)

#define VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_TYPE           ((uint32_t)0x00000000)

*/

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

#endif  /* __VSCP_DEV_DATA_CONFIG_OVERWRITE_H__ */

/** @} */
