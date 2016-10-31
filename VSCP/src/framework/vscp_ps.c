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
@brief  VSCP persistent memory driver
@file   vscp_ps.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_ps.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_ps.h"
#include "vscp_ps_access.h"

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

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the persistent memory access module.
 * It doesn't write anything in the persistent memory! It only initializes
 * the module that read/write access is possible.
 */
extern void vscp_ps_init(void)
{
    /* Initialize persistent memory access driver */
    vscp_ps_access_init();

    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED )

/**
 * This function reads the boot flag from persistent memory.
 *
 * @return  Boot flag
 */
extern uint8_t  vscp_ps_readBootFlag(void)
{
    return vscp_ps_access_read8(VSCP_PS_ADDR_BOOT_FLAG);
}

/**
 * This function writes the boot flag to persistent memory.
 *
 * @param[in]   bootFlag    Boot flag
 */
extern void vscp_ps_writeBootFlag(uint8_t bootFlag)
{
    vscp_ps_access_write8(VSCP_PS_ADDR_BOOT_FLAG, bootFlag);
    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */

/**
 * This function reads the nickname id of the node form the persistent memory.
 *
 * @return  Nickname id
 */
extern uint8_t  vscp_ps_readNicknameId(void)
{
    return vscp_ps_access_read8(VSCP_PS_ADDR_NICKNAME);
}

/**
 * This function writes the nickname id of the node to the persistent memory.
 *
 * @param[in]   nickname    Nickname id
 */
extern void vscp_ps_writeNicknameId(uint8_t nickname)
{
    vscp_ps_access_write8(VSCP_PS_ADDR_NICKNAME, nickname);
    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT )

/**
 * This function reads the stored segment controller CRC from the persistent memory.
 *
 * @return  Segment controller CRC
 */
extern uint8_t  vscp_ps_readSegmentControllerCRC(void)
{
    return vscp_ps_access_read8(VSCP_PS_ADDR_SEGMENT_CONTROLLER_CRC);
}

/**
 * This function writes the segment controller CRC to the persistent memory.
 *
 * @param[in]   crc Segment controller CRC
 */
extern void vscp_ps_writeSegmentControllerCRC(uint8_t crc)
{
    vscp_ps_access_write8(VSCP_PS_ADDR_SEGMENT_CONTROLLER_CRC, crc);
    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT ) */

/**
 * Read the node control flags from persistent memory.
 *
 * @return  Node control flags
 */
extern uint8_t  vscp_ps_readNodeControlFlags(void)
{
    return vscp_ps_access_read8(VSCP_PS_ADDR_NODE_CONTROL_FLAGS);
}

/**
 * Write the node control flags to persistent memory.
 *
 * @param[in]   value   Value to write
 */
extern void vscp_ps_writeNodeControlFlags(uint8_t value)
{
    vscp_ps_access_write8(VSCP_PS_ADDR_NODE_CONTROL_FLAGS, value);
    return;
}

/**
 * Read byte @see index of the user id from persistent memory.
 * Note that index 0 is the LSB and index 4 the MSB.
 *
 * @param[in]   index   Index of the user id [0-4]
 * @return  User id byte @see index
 */
extern uint8_t  vscp_ps_readUserId(uint8_t index)
{
    uint8_t data    = 0;

    if (VSCP_PS_SIZE_USER_ID > index)
    {
        data = vscp_ps_access_read8(VSCP_PS_ADDR_USER_ID + index);
    }

    return data;
}

/**
 * Write byte @see index of the user id to persistent memory.
 * Note that index 0 is the LSB and index 4 the MSB.
 *
 * @param[in]   index   Index of the user id [0-4]
 * @param[in]   value   User id byte @see index
 */
extern void vscp_ps_writeUserId(uint8_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_USER_ID > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_USER_ID + index, value);
    }

    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS )

/**
 * Read byte @see index of the GUID from persistent memory.
 * Note that index 0 is the LSB and index 15 the MSB.
 *
 * @param[in]   index   Index of the GUID [0-15]
 * @return  GUID byte @see index
 */
extern uint8_t  vscp_ps_readGUID(uint8_t index)
{
    uint8_t data    = 0;

    if (VSCP_PS_SIZE_GUID > index)
    {
        data = vscp_ps_access_read8(VSCP_PS_ADDR_GUID + index);
    }

    return data;
}

/**
 * Write byte @see index of the GUID to persistent memory.
 * Note that index 0 is the LSB and index 15 the MSB.
 *
 * @param[in]   index   Index of the GUID [0-15]
 * @param[in]   value   GUID byte @see index
 */
extern void vscp_ps_writeGUID(uint8_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_GUID > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_GUID + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS )

/**
 * Read node zone from persistent memory.
 *
 * @return  Node zone
 */
extern uint8_t  vscp_ps_readNodeZone(void)
{
    return vscp_ps_access_read8(VSCP_PS_ADDR_NODE_ZONE);
}

/**
 * Write node zone to persistent memory.
 *
 * @param[in]   value   Node zone
 */
extern void vscp_ps_writeNodeZone(uint8_t value)
{
    vscp_ps_access_write8(VSCP_PS_ADDR_NODE_ZONE, value);
    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS )

/**
 * Read node sub zone from persistent memory.
 *
 * @return  Node sub zone
 */
extern uint8_t  vscp_ps_readNodeSubZone(void)
{
    return vscp_ps_access_read8(VSCP_PS_ADDR_NODE_SUB_ZONE);
}

/**
 * Write node sub zone to persistent memory.
 *
 * @param[in]   value   Node sub zone
 */
extern void vscp_ps_writeNodeSubZone(uint8_t value)
{
    vscp_ps_access_write8(VSCP_PS_ADDR_NODE_SUB_ZONE, value);
    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS )

/**
 * Read the manufacturer device id from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer device id [0-3]
 * @return  Manufacturer device id
 */
extern uint8_t  vscp_ps_readManufacturerDevId(uint8_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_MANUFACTURER_DEV_ID > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_MANUFACTURER_DEV_ID + index);
    }

    return value;
}

/**
 * Write the manufacturer device id to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer device id [0-3]
 * @param[in]   value   Manufacturer device id
 */
extern void vscp_ps_writeManufacturerDevId(uint8_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_MANUFACTURER_DEV_ID > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_MANUFACTURER_DEV_ID + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS )

/**
 * Read the manufacturer sub device id from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer sub device id [0-3]
 * @return  Manufacturer sub device id
 */
extern uint8_t  vscp_ps_readManufacturerSubDevId(uint8_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_MANUFACTURER_SUB_DEV_ID > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_MANUFACTURER_SUB_DEV_ID + index);
    }

    return value;
}

/**
 * Write the manufacturer sub device id to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer sub device id [0-3]
 * @param[in]   value   Manufacturer sub device id
 */
extern void vscp_ps_writeManufacturerSubDevId(uint8_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_MANUFACTURER_SUB_DEV_ID > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_MANUFACTURER_SUB_DEV_ID + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS )

/**
 * Read the MDF URL from persistent memory.
 *
 * @param[in]   index   Index
 * @return  MDF URL value
 */
extern uint8_t  vscp_ps_readMdfUrl(uint8_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_MDF_URL > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_MDF_URL + index);
    }

    return value;
}

/**
 * Write the manufacturer sub device id to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index
 * @param[in]   value   MDF URL value
 */
extern void vscp_ps_writeMdfUrl(uint8_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_MDF_URL > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_MDF_URL + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS )

/**
 * Read the standard device family code from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device family code [0-3]
 * @return  Standard device family code
 */
extern uint8_t  vscp_ps_readStdDevFamilyCode(uint8_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_STD_DEV_FAMILY_CODE > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_STD_DEV_FAMILY_CODE + index);
    }

    return value;
}

/**
 * Write the standard device family code to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device family code [0-3]
 * @param[in]   value   Standard device family code
 */
extern void vscp_ps_writeStdDevFamilyCode(uint8_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_STD_DEV_FAMILY_CODE > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_STD_DEV_FAMILY_CODE + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS )

/**
 * Read the standard device type from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device type [0-3]
 * @return  Standard device type
 */
extern uint8_t  vscp_ps_readStdDevType(uint8_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_STD_DEV_TYPE > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_STD_DEV_TYPE + index);
    }

    return value;
}

/**
 * Write the standard device type to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device type [0-3]
 * @param[in]   value   Standard device type
 */
extern void vscp_ps_writeStdDevType(uint8_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_STD_DEV_TYPE > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_STD_DEV_TYPE + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

/**
 * Read the log id (stream id) from persistent memory.
 *
 * @return  Log id
 */
extern uint8_t  vscp_ps_readLogId(void)
{
    return vscp_ps_access_read8(VSCP_PS_ADDR_LOG_ID);
}

/**
 * Write the log id (stream id) to persistent memory.
 *
 * @param[in]   value   Log id
 */
extern void vscp_ps_writeLogId(uint8_t value)
{
    vscp_ps_access_write8(VSCP_PS_ADDR_LOG_ID, value);
    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

/**
 * Read the decision matrix from persistent memory.
 *
 * @param[in]   index   Decision matrix index
 * @return  Value
 */
extern uint8_t  vscp_ps_readDM(uint16_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_DM > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_DM + index);
    }

    return value;
}

/**
 * Write the decision matrix to persistent memory.
 *
 * @param[in]   index   Decision matrix index
 * @param[in]   value   Decision matrix value
 */
extern void vscp_ps_writeDM(uint16_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_DM > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_DM + index, value);
    }

    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/**
 * Read the decision matrix extension from persistent memory.
 *
 * @param[in]   index   Decision matrix extension index
 * @return  Value
 */
extern uint8_t  vscp_ps_readDMExtension(uint16_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_DM_EXTENSION > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_DM_EXTENSION + index);
    }

    return value;
}

/**
 * Write the decision matrix extension to persistent memory.
 *
 * @param[in]   index   Decision matrix extension index
 * @param[in]   value   Decision matrix extension value
 */
extern void vscp_ps_writeDMExtension(uint16_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_DM_EXTENSION > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_DM_EXTENSION + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

/**
 * Read the decision matrix next generation from persistent memory.
 *
 * @param[in]   index   Decision matrix next generation index
 * @return  Value
 */
extern uint8_t  vscp_ps_readDMNextGeneration(uint16_t index)
{
    uint8_t value   = 0;

    if (VSCP_PS_SIZE_DM_NEXT_GENERATION > index)
    {
        value = vscp_ps_access_read8(VSCP_PS_ADDR_DM_NEXT_GENERATION + index);
    }

    return value;
}

/**
 * Write the decision matrix next generation to persistent memory.
 *
 * @param[in]   index   Decision matrix next generation index
 * @param[in]   value   Value
 */
extern void vscp_ps_writeDMNextGeneration(uint16_t index, uint8_t value)
{
    if (VSCP_PS_SIZE_DM_NEXT_GENERATION > index)
    {
        vscp_ps_access_write8(VSCP_PS_ADDR_DM_NEXT_GENERATION + index, value);
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/
