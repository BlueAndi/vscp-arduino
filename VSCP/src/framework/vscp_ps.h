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
@brief  VSCP persistent memory driver
@file   vscp_ps.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module handles VSCP related information in persistent memory.

*******************************************************************************/
/** @defgroup vscp_ps Persistent memory driver
 * The core uses the persistent memory driver to store important data in
 * non-volatile RAM, e.g. an EEPROM.
 *
 * This layer has to be adapted only in vscp_ps_read() and vscp_ps_write(),
 * because they abstract read/write to persistent memory itself.
 *
 * The address in persistent memory is given via VSCP_PS_ADDR_... defines.
 * Changing the VSCP_PS_ADDR_BASE moves the address base.
 * If you want right after VSCP your application specific data in the persistent
 * memory, use ::VSCP_PS_ADDR_NEXT as base address them.
 *
 * Supported compile switches:
 * - VSCP_CONFIG_BOOT_LOADER_SUPPORTED
 * - VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT
 * - VSCP_CONFIG_ENABLE_DM
 * - VSCP_CONFIG_ENABLE_DM_EXTENSION
 * - VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION
 * - VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS
 * - VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS
 * - VSCP_CONFIG_ENABLE_LOGGER
 *
 *
 * Attention, the persistent memory contains all data in LSB first!
 *
 * | Order | Size in byte                           | Enable flag                                                    | Description |
 * | ----: | -------------------------------------: | :------------------------------------------------------------- | :---------- |
 * |     1 |                                      1 | VSCP_CONFIG_BOOT_LOADER_SUPPORTED                              | Boot flag (jump to application or stay in bootloader) |
 * |     2 |                                      1 | -                                                              | VSCP nickname id |
 * |     3 |                                      1 | -                                                              | Segment controller CRC |
 * |     4 |                                      1 | -                                                              | Node control flags |
 * |     5 |                                      5 | -                                                              | User id |
 * |     6 |                                     16 | VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS                    | GUID |
 * |     7 |                                      1 | VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS               | Node zone |
 * |     8 |                                      1 | VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS           | Node sub zone |
 * |     9 |                                      4 | VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS     | Manufacturer device id |
 * |    10 |                                      4 | VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS | Manufacturer sub device id |
 * |    11 |                                     32 | VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS                 | MDF URL |
 * |    12 |                                      4 | VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS     | Family code |
 * |    13 |                                      4 | VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS            | Device type |
 * |    14 |                                      1 | VSCP_CONFIG_ENABLE_LOGGER                                      | Log id (stream) |
 * |    15 | VSCP_CONFIG_DM_ROWS * VSCP_DM_ROW_SIZE | VSCP_CONFIG_ENABLE_DM                                          | Standard decision matrix |
 * |    16 | VSCP_CONFIG_DM_ROWS * VSCP_DM_ROW_SIZE | VSCP_CONFIG_ENABLE_DM_EXTENSION                                | Extended decision matrix |
 * |    17 | VSCP_CONFIG_DM_NG_RULE_SET_SIZE        | VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION                          | Decision matrix next generation |
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_PS_H__
#define __VSCP_PS_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <inttypes.h>
#include "vscp_types.h"
#include "vscp_config.h"
#include "vscp_dev_data_config.h"
#include "vscp_dm.h"

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

/** Base address of all VSCP related data in the persistent memory. */
#define VSCP_PS_ADDR_BASE                   0

/* ---------------------------------------------------------------------------- */
/* -------- VSCP bootloader data, which can be modifiable (optional) ---------- */
/* ---------------------------------------------------------------------------- */

/** Address of the boot flag in the persistent memory.
 * The VSCP specification specified it to position 0 in the persistent memory.
 */
#define VSCP_PS_ADDR_BOOT_FLAG              (VSCP_PS_ADDR_BASE + 0)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED )

/** Size of the boot flag in byte */
#define VSCP_PS_SIZE_BOOT_FLAG               1

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */

/** Boot flag is not located in the persistent memory */
#define VSCP_PS_SIZE_BOOT_FLAG               0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */

/* -------------------------------------------------------------------- */
/* -------- VSCP data, which shall be modifiable (mandatory) ---------- */
/* -------------------------------------------------------------------- */

/** Address of the nickname id in the persistent memory. */
#define VSCP_PS_ADDR_NICKNAME               (VSCP_PS_ADDR_BOOT_FLAG + VSCP_PS_SIZE_BOOT_FLAG)

/** Size of nickname id in byte */
#define VSCP_PS_SIZE_NICKNAME               1

/** Address of the segment controller CRC in the persistent memory. */
#define VSCP_PS_ADDR_SEGMENT_CONTROLLER_CRC (VSCP_PS_ADDR_NICKNAME + VSCP_PS_SIZE_NICKNAME)

/** Size of segment controller CRC in byte */
#define VSCP_PS_SIZE_SEGMENT_CONTROLLER_CRC 1

/** Address of the node control flags in the persistent memory. */
#define VSCP_PS_ADDR_NODE_CONTROL_FLAGS     (VSCP_PS_ADDR_SEGMENT_CONTROLLER_CRC + VSCP_PS_SIZE_SEGMENT_CONTROLLER_CRC)

/** Size of node control flags in byte */
#define VSCP_PS_SIZE_NODE_CONTROL_FLAGS     1

/** Address of the user id in the persistent memory. */
#define VSCP_PS_ADDR_USER_ID                (VSCP_PS_ADDR_NODE_CONTROL_FLAGS + VSCP_PS_SIZE_NODE_CONTROL_FLAGS)

/** Size of user id in byte */
#define VSCP_PS_SIZE_USER_ID                5

/* ----------------------------------------------------------------- */
/* -------- VSCP data, which can be modifiable (optional) ---------- */
/* ----------------------------------------------------------------- */

/** Address of the GUID in the persistent memory. */
#define VSCP_PS_ADDR_GUID                   (VSCP_PS_ADDR_USER_ID + VSCP_PS_SIZE_USER_ID)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS )

/** Size of the GUID in byte */
#define VSCP_PS_SIZE_GUID                   VSCP_GUID_SIZE

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS ) */

/** GUID is not located in the persistent memory */
#define VSCP_PS_SIZE_GUID                   0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS ) */

/** Address of the node zone in the persistent memory. */
#define VSCP_PS_ADDR_NODE_ZONE              (VSCP_PS_ADDR_GUID + VSCP_PS_SIZE_GUID)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS )

/** Size of the node zone in byte */
#define VSCP_PS_SIZE_NODE_ZONE              1

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS ) */

/** Node zone is not located in the persistent memory */
#define VSCP_PS_SIZE_NODE_ZONE              0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS ) */

/** Address of the node sub zone in the persistent memory. */
#define VSCP_PS_ADDR_NODE_SUB_ZONE          (VSCP_PS_ADDR_NODE_ZONE + VSCP_PS_SIZE_NODE_ZONE)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS )

/** Size of the node zone in byte */
#define VSCP_PS_SIZE_NODE_SUB_ZONE          1

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS ) */

/** Node zone is not located in the persistent memory */
#define VSCP_PS_SIZE_NODE_SUB_ZONE          0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS ) */

/** Address of the manufacturer device id in the persistent memory. */
#define VSCP_PS_ADDR_MANUFACTURER_DEV_ID    (VSCP_PS_ADDR_NODE_SUB_ZONE + VSCP_PS_SIZE_NODE_SUB_ZONE)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS )

/** Size of the manufacturer device id in byte */
#define VSCP_PS_SIZE_MANUFACTURER_DEV_ID    4

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS ) */

/** Manufacturer device id is not located in the persistent memory */
#define VSCP_PS_SIZE_MANUFACTURER_DEV_ID    0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS ) */

/** Address of the manufacturer sub device id in the persistent memory. */
#define VSCP_PS_ADDR_MANUFACTURER_SUB_DEV_ID    (VSCP_PS_ADDR_MANUFACTURER_DEV_ID + VSCP_PS_SIZE_MANUFACTURER_DEV_ID)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS )

/** Size of the manufacturer sub device id in byte */
#define VSCP_PS_SIZE_MANUFACTURER_SUB_DEV_ID    4

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS ) */

/** Manufacturer sub device id is not located in the persistent memory */
#define VSCP_PS_SIZE_MANUFACTURER_SUB_DEV_ID    0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS ) */

/** Address of the MDF URL in the persistent memory. */
#define VSCP_PS_ADDR_MDF_URL                    (VSCP_PS_ADDR_MANUFACTURER_SUB_DEV_ID + VSCP_PS_SIZE_MANUFACTURER_SUB_DEV_ID)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS )

/** Size of the MDF URL in byte */
#define VSCP_PS_SIZE_MDF_URL                    32

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS ) */

/** MDF URL is not located in the persistent memory. */
#define VSCP_PS_SIZE_MDF_URL                    0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS ) */

/** Address of the standard device family code in the persistent memory. */
#define VSCP_PS_ADDR_STD_DEV_FAMILY_CODE    (VSCP_PS_ADDR_MDF_URL + VSCP_PS_SIZE_MDF_URL)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS )

/** Size of the standard device family code in byte */
#define VSCP_PS_SIZE_STD_DEV_FAMILY_CODE    4

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS ) */

/** Standard device family code is not located in the persistent memory */
#define VSCP_PS_SIZE_STD_DEV_FAMILY_CODE    0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS ) */

/** Address of the standard device type in the persistent memory. */
#define VSCP_PS_ADDR_STD_DEV_TYPE           (VSCP_PS_ADDR_STD_DEV_FAMILY_CODE + VSCP_PS_SIZE_STD_DEV_FAMILY_CODE)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS )

/** Size of the standard device type in byte */
#define VSCP_PS_SIZE_STD_DEV_TYPE           4

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS ) */

/** Standard device type is not located in the persistent memory */
#define VSCP_PS_SIZE_STD_DEV_TYPE           0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS ) */

/** Address of the log id (stream id), used by the VSCP logger */
#define VSCP_PS_ADDR_LOG_ID                 (VSCP_PS_ADDR_STD_DEV_TYPE + VSCP_PS_SIZE_STD_DEV_TYPE)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

/** Size of the log id (stream id) in byte */
#define VSCP_PS_SIZE_LOG_ID                 1

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

/** Log id (stream id) is not available */
#define VSCP_PS_SIZE_LOG_ID                 0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

/* --------------------------------------------------------------- */
/* -------- VSCP decision matrix (standard + extension) ---------- */
/* --------------------------------------------------------------- */

/** Address of the decision matrix (standard) */
#define VSCP_PS_ADDR_DM                     (VSCP_PS_ADDR_LOG_ID + VSCP_PS_SIZE_LOG_ID)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

/** Size of the decision matrix (standard) in byte */
#define VSCP_PS_SIZE_DM                     (VSCP_CONFIG_DM_ROWS * VSCP_DM_ROW_SIZE)

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM ) */

/** Decision matrix is not available */
#define VSCP_PS_SIZE_DM                     0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM ) */

/** Address of the decision matrix extension */
#define VSCP_PS_ADDR_DM_EXTENSION          (VSCP_PS_ADDR_DM + VSCP_PS_SIZE_DM)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/** Size of the decision matrix extension in byte */
#define VSCP_PS_SIZE_DM_EXTENSION          (VSCP_CONFIG_DM_ROWS * VSCP_DM_ROW_SIZE)

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

/** Decision matrix extension is not available */
#define VSCP_PS_SIZE_DM_EXTENSION           0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

/* -------------------------------------------------------- */
/* -------- VSCP decision matrix next generation ---------- */
/* -------------------------------------------------------- */

/** Address of the decision matrix next generation */
#define VSCP_PS_ADDR_DM_NEXT_GENERATION     (VSCP_PS_ADDR_DM_EXTENSION + VSCP_PS_SIZE_DM_EXTENSION)

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

/** Size of the decision matrix next generation in byte */
#define VSCP_PS_SIZE_DM_NEXT_GENERATION     VSCP_CONFIG_DM_NG_RULE_SET_SIZE

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

/** Decision matrix next generation is not available */
#define VSCP_PS_SIZE_DM_NEXT_GENERATION     0

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

/* -------- */

/** Next available address after all VSCP related data.
 * Use this define if you want right after VSCP your application specific data
 * in the persistent memory.
 */
#define VSCP_PS_ADDR_NEXT                   (VSCP_PS_ADDR_DM_NEXT_GENERATION + VSCP_PS_SIZE_DM_NEXT_GENERATION)

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
 * This function initializes the persistent memory access module.
 * It doesn't write anything in the persistent memory! It only initializes
 * the module that read/write access is possible.
 */
extern void vscp_ps_init(void);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED )

/**
 * This function reads the boot flag from persistent memory.
 *
 * @return  Boot flag
 */
extern uint8_t  vscp_ps_readBootFlag(void);

/**
 * This function writes the boot flag to persistent memory.
 *
 * @param[in]   bootFlag    Boot flag
 */
extern void vscp_ps_writeBootFlag(uint8_t bootFlag);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */

/**
 * This function reads the nickname id of the node form the persistent memory.
 *
 * @return  Nickname id
 */
extern uint8_t  vscp_ps_readNicknameId(void);

/**
 * This function writes the nickname id of the node to the persistent memory.
 *
 * @param[in]   nickname    Nickname id
 */
extern void vscp_ps_writeNicknameId(uint8_t nickname);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT )

/**
 * This function reads the stored segment controller GUID CRC from the persistent memory.
 *
 * @return  Segment controller GUID CRC
 */
extern uint8_t  vscp_ps_readSegmentControllerCRC(void);

/**
 * This function writes the segment controller GUID CRC to the persistent memory.
 *
 * @param[in]   crc Segment controller GUID CRC
 */
extern void vscp_ps_writeSegmentControllerCRC(uint8_t crc);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT ) */

/**
 * Read the node control flags from persistent memory.
 *
 * @return  Node control flags
 */
extern uint8_t  vscp_ps_readNodeControlFlags(void);

/**
 * Write the node control flags to persistent memory.
 *
 * @param[in]   value   Value to write
 */
extern void vscp_ps_writeNodeControlFlags(uint8_t value);

/**
 * Read byte @see index of the user id from persistent memory.
 * Note that index 0 is the LSB and index 4 the MSB.
 *
 * @param[in]   index   Index of the user id [0-4]
 * @return  User id byte @see index
 */
extern uint8_t  vscp_ps_readUserId(uint8_t index);

/**
 * Write byte @see index of the user id to persistent memory.
 * Note that index 0 is the LSB and index 4 the MSB.
 *
 * @param[in]   index   Index of the user id [0-4]
 * @param[in]   value   User id byte @see index
 */
extern void vscp_ps_writeUserId(uint8_t index, uint8_t value);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS )

/**
 * Read byte @see index of the GUID from persistent memory.
 * Note that index 0 is the LSB and index 15 the MSB.
 *
 * @param[in]   index   Index of the GUID [0-15]
 * @return  GUID byte @see index
 */
extern uint8_t  vscp_ps_readGUID(uint8_t index);

/**
 * Write byte @see index of the GUID to persistent memory.
 * Note that index 0 is the LSB and index 15 the MSB.
 *
 * @param[in]   index   Index of the GUID [0-15]
 * @param[in]   value   GUID byte @see index
 */
extern void vscp_ps_writeGUID(uint8_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS )

/**
 * Read node zone from persistent memory.
 *
 * @return  Node zone
 */
extern uint8_t  vscp_ps_readNodeZone(void);

/**
 * Write node zone to persistent memory.
 *
 * @param[in]   value   Node zone
 */
extern void vscp_ps_writeNodeZone(uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_ZONE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS )

/**
 * Read node sub zone from persistent memory.
 *
 * @return  Node sub zone
 */
extern uint8_t  vscp_ps_readNodeSubZone(void);

/**
 * Write node sub zone to persistent memory.
 *
 * @param[in]   value   Node sub zone
 */
extern void vscp_ps_writeNodeSubZone(uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_NODE_SUB_ZONE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS )

/**
 * Read the manufacturer device id from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer device id [0-3]
 * @return  Manufacturer device id
 */
extern uint8_t  vscp_ps_readManufacturerDevId(uint8_t index);

/**
 * Write the manufacturer device id to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer device id [0-3]
 * @param[in]   value   Manufacturer device id
 */
extern void vscp_ps_writeManufacturerDevId(uint8_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_DEV_ID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS )

/**
 * Read the manufacturer sub device id from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer sub device id [0-3]
 * @return  Manufacturer sub device id
 */
extern uint8_t  vscp_ps_readManufacturerSubDevId(uint8_t index);

/**
 * Write the manufacturer sub device id to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the manufacturer sub device id [0-3]
 * @param[in]   value   Manufacturer sub device id
 */
extern void vscp_ps_writeManufacturerSubDevId(uint8_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MANUFACTURER_SUB_DEV_ID_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS )

/**
 * Read the MDF URL from persistent memory.
 *
 * @param[in]   index   Index
 * @return  MDF URL value
 */
extern uint8_t  vscp_ps_readMdfUrl(uint8_t index);

/**
 * Write the manufacturer sub device id to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index
 * @param[in]   value   MDF URL value
 */
extern void vscp_ps_writeMdfUrl(uint8_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_MDF_URL_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS )

/**
 * Read the standard device family code from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device family code [0-3]
 * @return  Standard device family code
 */
extern uint8_t  vscp_ps_readStdDevFamilyCode(uint8_t index);

/**
 * Write the standard device family code to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device family code [0-3]
 * @param[in]   value   Standard device family code
 */
extern void vscp_ps_writeStdDevFamilyCode(uint8_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_FAMILY_CODE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS )

/**
 * Read the standard device type from persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device type [0-3]
 * @return  Standard device type
 */
extern uint8_t  vscp_ps_readStdDevType(uint8_t index);

/**
 * Write the standard device type to persistent memory.
 * Note that index 0 is the LSB and index 3 the MSB.
 *
 * @param[in]   index   Index of the standard device type [0-3]
 * @param[in]   value   Standard device type
 */
extern void vscp_ps_writeStdDevType(uint8_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_STD_DEV_TYPE_STORAGE_PS ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

/**
 * Read the log id (stream id) from persistent memory.
 *
 * @return  Log id
 */
extern uint8_t  vscp_ps_readLogId(void);

/**
 * Write the log id (stream id) to persistent memory.
 *
 * @param[in]   value   Log id
 */
extern void vscp_ps_writeLogId(uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

/**
 * Read the decision matrix from persistent memory.
 *
 * @param[in]   index   Decision matrix index
 * @return  Value
 */
extern uint8_t  vscp_ps_readDM(uint16_t index);

/**
 * Write the decision matrix to persistent memory.
 *
 * @param[in]   index   Decision matrix index
 * @param[in]   value   Decision matrix value
 */
extern void vscp_ps_writeDM(uint16_t index, uint8_t value);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/**
 * Read the decision matrix extension from persistent memory.
 *
 * @param[in]   index   Decision matrix extension index
 * @return  Value
 */
extern uint8_t  vscp_ps_readDMExtension(uint16_t index);

/**
 * Write the decision matrix extension to persistent memory.
 *
 * @param[in]   index   Decision matrix extension index
 * @param[in]   value   Decision matrix extension value
 */
extern void vscp_ps_writeDMExtension(uint16_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

/**
 * Read the decision matrix next generation from persistent memory.
 *
 * @param[in]   index   Decision matrix next generation index
 * @return  Value
 */
extern uint8_t  vscp_ps_readDMNextGeneration(uint16_t index);

/**
 * Write the decision matrix next generation to persistent memory.
 *
 * @param[in]   index   Decision matrix next generation index
 * @param[in]   value   Value
 */
extern void vscp_ps_writeDMNextGeneration(uint16_t index, uint8_t value);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_PS_H__ */

/** @} */
