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
@brief  VSCP device data
@file   vscp_dev_data.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_dev_data.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_dev_data.h"
#include "vscp_dev_data_config.h"
#include "vscp_ps.h"
#include "vscp_util.h"
#include "../user/vscp_portable.h"

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
    PROTOTYPES
*******************************************************************************/

/*******************************************************************************
    LOCAL VARIABLES
*******************************************************************************/

/** Device parameter container */
static vscp_dev_data_Container  vscp_dev_data_container;

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the module.
 */
extern void vscp_dev_data_init(void)
{
    uint8_t index   = 0;

    /* Initialize data container */
    for(index = 0; index < VSCP_GUID_SIZE; ++index)
    {
        vscp_dev_data_container.guid[index] = 0;
    }
    
    vscp_dev_data_container.zone    = 0xff;
    vscp_dev_data_container.subZone = 0xff;

    return;
}

/**
 * This function set the device specific parameter.
 *
 * @param[in]   container   Data container
 */
extern void vscp_dev_data_set(vscp_dev_data_Container const * const container)
{
    if (NULL != container)
    {
        vscp_dev_data_container = *container;
    }

    return;
}

/**
 * This function restores factory default settings.
 */
extern void vscp_dev_data_restoreFactoryDefaultSettings(void)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS )

    /* Restore GUID */
    {
        uint8_t         index   = 0;
        const uint8_t   guid[]  = VSCP_DEV_DATA_CONFIG_NODE_GUID;

        for(index = 0; index < VSCP_PS_SIZE_GUID; ++index)
        {
            /* GUID is given in MSB first, but the persistency stores it LSB first. */
            vscp_ps_writeGUID(VSCP_PS_SIZE_GUID - index - 1, guid[index]);
        }
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS )

    /* Restore node zone */
    vscp_ps_writeNodeZone(VSCP_DEV_DATA_CONFIG_NODE_ZONE);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS )

    /* Restore node sub zone */
    vscp_ps_writeNodeSubZone(VSCP_DEV_DATA_CONFIG_NODE_SUB_ZONE);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS )

    /* Restore manufacturer device id */
    {
        uint8_t         index               = 0;
        const uint32_t  manufacturerDevId   = VSCP_DEV_DATA_CONFIG_MANUFACTURER_DEVICE_ID;

        for(index = 0; index < VSCP_PS_SIZE_MANUFACTURER_DEV_ID; ++index)
        {
            vscp_ps_writeManufacturerDevId(index, ((const uint8_t*)&manufacturerDevId)[index]);
        }
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS )

    /* Restore manufacturer sub device id */
    {
        uint8_t         index               = 0;
        const uint32_t  manufacturerSubDevId   = VSCP_DEV_DATA_CONFIG_MANUFACTURER_SUB_DEVICE_ID;

        for(index = 0; index < VSCP_PS_SIZE_MANUFACTURER_SUB_DEV_ID; ++index)
        {
            vscp_ps_writeManufacturerSubDevId(index, ((const uint8_t*)&manufacturerSubDevId)[index]);
        }
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS )

    /* Restore MDF URL */
    {
        uint8_t     index       = 0;
        uint8_t     mdfIndex    = 0;
        const char  mdfUrl[]    = VSCP_DEV_DATA_CONFIG_MDF_URL;

        for(index = 0; index < VSCP_PS_SIZE_MDF_URL; ++index)
        {
            uint8_t value   = 0;

            if ('\0' != mdfUrl[mdfIndex])
            {
                value = (uint8_t)mdfUrl[mdfIndex];
                ++mdfIndex;
            }
            else
            /* Fill rest of mdf with zero's */
            {
                value = 0;
            }

            vscp_ps_writeMdfUrl(index, value);
        }
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE )

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS )

    /* Restore standard device family code */
    {
        uint8_t     index               = 0;
        uint32_t    stdDevFamilyCode    = VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_FAMILY_CODE;
        uint8_t     value               = 0;

        for(index = 0; index < VSCP_PS_SIZE_STD_DEV_FAMILY_CODE; ++index)
        {
            value   = (uint8_t)((stdDevFamilyCode >> index) & 0xff);

            vscp_ps_writeStdDevFamilyCode(index, value);
        }
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS )

    /* Restore standard device type */
    {
        uint8_t     index       = 0;
        uint32_t    stdDevType  = VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_TYPE;
        uint8_t     value       = 0;

        for(index = 0; index < VSCP_PS_SIZE_STD_DEV_TYPE; ++index)
        {
            value   = (uint8_t)((stdDevType >> index) & 0xff);

            vscp_ps_writeStdDevType(index, value);
        }
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS ) */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE ) */

    return;
}

/**
 * This function returns one byte of the GUID, which is selected by the index.
 * Index 0 corresponds with the GUID LSB byte, index 15 with the GUID MSB byte.
 *
 * @param[in]   index   Index in the GUID [0-15]
 * @return  GUID byte
 */
extern uint8_t  vscp_dev_data_getGUID(uint8_t index)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS )

    return vscp_ps_readGUID(index);

#elif VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT )

    return vscp_portable_readGUID(index);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS )
           VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT ) */

    uint8_t         value   = 0;

    if (VSCP_UTIL_ARRAY_NUM(vscp_dev_data_container.guid) > index)
    {
        value = vscp_dev_data_container.guid[VSCP_UTIL_ARRAY_NUM(vscp_dev_data_container.guid) - index - 1];
    }

    return value;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS )
           VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT ) */
}

/**
 * This function returns the node zone.
 *
 * @return Node zone
 */
extern uint8_t  vscp_dev_data_getNodeZone(void)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS )

    return vscp_ps_readNodeZone();

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS ) */

    return vscp_dev_data_container.zone;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS ) */
}

/**
 * This function returns the node sub zone.
 *
 * @return Node sub zone
 */
extern uint8_t  vscp_dev_data_getNodeSubZone(void)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS )

    return vscp_ps_readNodeSubZone();

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS ) */

    return vscp_dev_data_container.subZone;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS ) */
}

/**
 * This function returns one byte of the manufacturer device id at the given
 * @see index. If the index is out of bounce, a 0 will be returned.
 *
 * @param[in]   index   Index of the manufacturer device id [0..3]
 * @return  Manufacturer device id byte @see index
 */
extern uint8_t  vscp_dev_data_getManufacturerDevId(uint8_t index)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS )

    return vscp_ps_readManufacturerDevId(index);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS ) */

    uint8_t         value               = 0;
    const uint32_t  manufacturerDevId   = VSCP_DEV_DATA_CONFIG_MANUFACTURER_DEVICE_ID;

    if (sizeof(manufacturerDevId) > index)
    {
        value = ((const uint8_t*)&manufacturerDevId)[index];
    }

    return value;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS ) */
}

/**
 * This function returns one byte of the manufacturer sub device id at the given
 * @see index. If the index is out of bounce, a 0 will be returned.
 *
 * @param[in]   index   Index of the manufacturer sub device id [0..3]
 * @return  Manufacturer sub device id byte @see index
 */
extern uint8_t  vscp_dev_data_getManufacturerSubDevId(uint8_t index)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS )

    return vscp_ps_readManufacturerSubDevId(index);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS ) */

    uint8_t         value               = 0;
    const uint32_t  manufacturerSubDevId   = VSCP_DEV_DATA_CONFIG_MANUFACTURER_SUB_DEVICE_ID;

    if (sizeof(manufacturerSubDevId) > index)
    {
        value = ((const uint8_t*)&manufacturerSubDevId)[index];
    }

    return value;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS ) */
}

/**
 * This function returns one byte of the MDF URL, which is selected by the index.
 *
 * @param[in]   index   Index in the MDF URL
 * @return  MDF URL byte
 */
extern uint8_t  vscp_dev_data_getMdfUrl(uint8_t index)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS )

    return vscp_ps_readMdfUrl(index);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS ) */

    uint8_t     value       = 0;
    const char  mdfUrl[]    = VSCP_DEV_DATA_CONFIG_MDF_URL;
    uint8_t     run         = 0;

    while('\0' != mdfUrl[run])
    {
        if (index == run)
        {
            value = (uint8_t)mdfUrl[run];
            break;
        }

        ++run;
    }

    return value;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS ) */
}

/**
 * This function returns the firmware version major number.
 *
 * @return  Firmware version major number
 */
extern uint8_t  vscp_dev_data_getFirmwareVersionMajor(void)
{
    return VSCP_DEV_DATA_CONFIG_VERSION_MAJOR;
}

/**
 * This function returns the firmware version minor number.
 *
 * @return  Firmware version minor number
 */
extern uint8_t  vscp_dev_data_getFirmwareVersionMinor(void)
{
    return VSCP_DEV_DATA_CONFIG_VERSION_MINOR;
}

/**
 * This function returns the firmware version sub minor number.
 *
 * @return  Firmware version sub minor number
 */
extern uint8_t  vscp_dev_data_getFirmwareVersionSubMinor(void)
{
    return VSCP_DEV_DATA_CONFIG_VERSION_SUB_MINOR;
}

/**
 * This function returns one byte of the standard device family code at the
 * given @see index.
 * If the family code is not supported, the family code will be 0.
 *
 * @param[in]   index   Index
 * @return  Standard device family code byte @see index
 */
extern uint8_t  vscp_dev_data_getStdDevFamilyCode(uint8_t index)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE )

    uint32_t    stdDevFamilyCode    = VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_FAMILY_CODE;
    uint8_t     value               = (uint8_t)((stdDevFamilyCode >> ((uint32_t)index)) & 0xff);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS )

    value = vscp_ps_readStdDevFamilyCode(index);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS ) */

    /* 0xFF shall be mapped to 0x00 according to specification. */
    if (0xFF == value)
    {
        value = 0x00;
    }

    return value;

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE ) */

    return 0;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE ) */
}

/**
 * This function returns one byte of the standard device type at the
 * given @see index.
 * If the family code is not supported, the family code will be 0.
 *
 * @param[in]   index   Index
 * @return  Standard device family code byte @see index
 */
extern uint8_t  vscp_dev_data_getStdDevType(uint8_t index)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE )

    uint32_t    stdDevType  = VSCP_DEV_DATA_CONFIG_STANDARD_DEVICE_TYPE;
    uint8_t     value       = (uint8_t)((stdDevType >> ((uint32_t)index)) & 0xff);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS )

    value = vscp_ps_readStdDevType(index);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS ) */

    /* 0xFF shall be mapped to 0x00 according to specification. */
    if (0xFF == value)
    {
        value = 0x00;
    }

    return value;

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE ) */

    return 0;

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_FAMILY_CODE ) */
}

/**
 * Get the firmware device code.
 * The firmware code is used to distinguish a device type of a module from one
 * another so that the correct firmware can be loaded to a module. Typically a
 * board have different firmware codes here for different microprocessors used
 * as reversions of the board is shipped over time.
 * 
 * Return 0 if not used.
 * 
 * @return Firmware device code
 */
extern uint32_t vscp_dev_data_getFirmwareDeviceCode(void)
{
    return VSCP_DEV_DATA_CONFIG_FIRMWARE_DEVICE_CODE;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/
