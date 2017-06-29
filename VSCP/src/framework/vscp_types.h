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
@brief  VSCP types and structures
@file   vscp_types.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module contains VSCP specific type, structure and constant definitions.

*******************************************************************************/
/** @addtogroup vscp_core
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPES_H__
#define __VSCP_TYPES_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <inttypes.h>
#include <stdlib.h>
#include "vscp_platform.h"

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

/** Maximum number of data bytes per message. */
#define VSCP_L1_DATA_SIZE                   (8)

/** Reserved nickname id for the segment master. */
#define VSCP_NICKNAME_SEGMENT_MASTER        (0x00)

/** Reserved nickname id for not initialized nodes. */
#define VSCP_NICKNAME_NOT_INIT              (0xFF)

/** Segment controller CRC value for not initialized nodes. */
#define VSCP_SEGMENT_CRC_NOT_INIT           (0xFF)

/** Node control flags default value. */
#define VSCP_NODE_CONTROL_FLAGS_DEFAULT     (0xA0)

/** Boot flag: no application present */
#define VSCP_BOOT_FLAG_NO_APPLICATION       (0xFF)

/** Boot flag: destination bootloader */
#define VSCP_BOOT_FLAG_BOOTLOADER           (0xBB)

/** Boot flag: destination application */
#define VSCP_BOOT_FLAG_APPLICATION          (0xAA)

/** GUID size */
#define VSCP_GUID_SIZE                      (16)

/** Application register start address (page 0) */
#define VSCP_REGISTER_APP_START_ADDR        (0x00)

/** Application register end address (page 0) */
#define VSCP_REGISTER_APP_END_ADDR          (0x7F)

/** VSCP specific register start address (page 0) */
#define VSCP_REGISTER_VSCP_START_ADDR       (0x80)

/** VSCP specific register end address (page 0) */
#define VSCP_REGISTER_VSCP_END_ADDR         (0xFF)

/** VSCP register: alarm status */
#define VSCP_REG_ALARM_STATUS               (VSCP_REGISTER_VSCP_START_ADDR + 0)

/** VSCP register: major version number */
#define VSCP_REG_VSCP_VERSION_MAJOR         (VSCP_REGISTER_VSCP_START_ADDR + 1)

/** VSCP register: minor version number */
#define VSCP_REG_VSCP_VERSION_MINOR         (VSCP_REGISTER_VSCP_START_ADDR + 2)

/** VSCP register: node control flags */
#define VSCP_REG_NODE_CONTROL_FLAGS         (VSCP_REGISTER_VSCP_START_ADDR + 3)

/** VSCP register: user id byte 0 */
#define VSCP_REG_USER_ID_0                  (VSCP_REGISTER_VSCP_START_ADDR + 4)

/** VSCP register: user id byte 1 */
#define VSCP_REG_USER_ID_1                  (VSCP_REGISTER_VSCP_START_ADDR + 5)

/** VSCP register: user id byte 2 */
#define VSCP_REG_USER_ID_2                  (VSCP_REGISTER_VSCP_START_ADDR + 6)

/** VSCP register: user id byte 3 */
#define VSCP_REG_USER_ID_3                  (VSCP_REGISTER_VSCP_START_ADDR + 7)

/** VSCP register: user id byte 4 */
#define VSCP_REG_USER_ID_4                  (VSCP_REGISTER_VSCP_START_ADDR + 8)

/** VSCP register: manufacturer device id byte 0 */
#define VSCP_REG_MANUFACTURER_DEV_ID_0      (VSCP_REGISTER_VSCP_START_ADDR + 9)

/** VSCP register: manufacturer device id byte 1 */
#define VSCP_REG_MANUFACTURER_DEV_ID_1      (VSCP_REGISTER_VSCP_START_ADDR + 10)

/** VSCP register: manufacturer device id byte 2 */
#define VSCP_REG_MANUFACTURER_DEV_ID_2      (VSCP_REGISTER_VSCP_START_ADDR + 11)

/** VSCP register: manufacturer device id byte 3 */
#define VSCP_REG_MANUFACTURER_DEV_ID_3      (VSCP_REGISTER_VSCP_START_ADDR + 12)

/** VSCP register: manufacturer sub device id byte 0 */
#define VSCP_REG_MANUFACTURER_SUB_DEV_ID_0  (VSCP_REGISTER_VSCP_START_ADDR + 13)

/** VSCP register: manufacturer sub device id byte 1 */
#define VSCP_REG_MANUFACTURER_SUB_DEV_ID_1  (VSCP_REGISTER_VSCP_START_ADDR + 14)

/** VSCP register: manufacturer sub device id byte 2 */
#define VSCP_REG_MANUFACTURER_SUB_DEV_ID_2  (VSCP_REGISTER_VSCP_START_ADDR + 15)

/** VSCP register: manufacturer sub device id byte 3 */
#define VSCP_REG_MANUFACTURER_SUB_DEV_ID_3  (VSCP_REGISTER_VSCP_START_ADDR + 16)

/** VSCP register: nickname id */
#define VSCP_REG_NICKNAME_ID                (VSCP_REGISTER_VSCP_START_ADDR + 17)

/** VSCP register: page select MSB */
#define VSCP_REG_PAGE_SELECT_MSB            (VSCP_REGISTER_VSCP_START_ADDR + 18)

/** VSCP register: page select LSB */
#define VSCP_REG_PAGE_SELECT_LSB            (VSCP_REGISTER_VSCP_START_ADDR + 19)

/** VSCP register: firmware major version */
#define VSCP_REG_FIRMWARE_VERSION_MAJOR     (VSCP_REGISTER_VSCP_START_ADDR + 20)

/** VSCP register: firmware minor version */
#define VSCP_REG_FIRMWARE_VERSION_MINOR     (VSCP_REGISTER_VSCP_START_ADDR + 21)

/** VSCP register: firmware sub minor version */
#define VSCP_REG_FIRMWARE_VERSION_SUB_MINOR (VSCP_REGISTER_VSCP_START_ADDR + 22)

/** VSCP register: boot loader algorithm */
#define VSCP_REG_BOOT_LOADER_ALGORITHM      (VSCP_REGISTER_VSCP_START_ADDR + 23)

/** VSCP register: buffer size */
#define VSCP_REG_BUFFER_SIZE                (VSCP_REGISTER_VSCP_START_ADDR + 24)

/** VSCP register: number of register pages used */
#define VSCP_REG_PAGES_USED                 (VSCP_REGISTER_VSCP_START_ADDR + 25)

/** VSCP register: standard device family code byte 3 (MSB) */
#define VSCP_REG_STD_DEV_FAMILY_CODE_3      (VSCP_REGISTER_VSCP_START_ADDR + 26)

/** VSCP register: standard device family code byte 2 */
#define VSCP_REG_STD_DEV_FAMILY_CODE_2      (VSCP_REGISTER_VSCP_START_ADDR + 27)

/** VSCP register: standard device family code byte 1 */
#define VSCP_REG_STD_DEV_FAMILY_CODE_1      (VSCP_REGISTER_VSCP_START_ADDR + 28)

/** VSCP register: standard device family code byte 0 (LSB) */
#define VSCP_REG_STD_DEV_FAMILY_CODE_0      (VSCP_REGISTER_VSCP_START_ADDR + 29)

/** VSCP register: standard device type byte 3 (MSB) */
#define VSCP_REG_STD_DEV_TYPE_3             (VSCP_REGISTER_VSCP_START_ADDR + 30)

/** VSCP register: standard device type byte 2 */
#define VSCP_REG_STD_DEV_TYPE_2             (VSCP_REGISTER_VSCP_START_ADDR + 31)

/** VSCP register: standard device type byte 1 */
#define VSCP_REG_STD_DEV_TYPE_1             (VSCP_REGISTER_VSCP_START_ADDR + 32)

/** VSCP register: standard device type byte 0 (LSB) */
#define VSCP_REG_STD_DEV_TYPE_0             (VSCP_REGISTER_VSCP_START_ADDR + 33)

/** VSCP register: restore default configuration */
#define VSCP_REG_RESTORE_STD_CFG            (VSCP_REGISTER_VSCP_START_ADDR + 34)

/** VSCP register: GUID byte 15 (MSB) */
#define VSCP_REG_GUID_15                    (VSCP_REGISTER_VSCP_START_ADDR + 80)

/** VSCP register: GUID byte 14 */
#define VSCP_REG_GUID_14                    (VSCP_REGISTER_VSCP_START_ADDR + 81)

/** VSCP register: GUID byte 13 */
#define VSCP_REG_GUID_13                    (VSCP_REGISTER_VSCP_START_ADDR + 82)

/** VSCP register: GUID byte 12 */
#define VSCP_REG_GUID_12                    (VSCP_REGISTER_VSCP_START_ADDR + 83)

/** VSCP register: GUID byte 11 */
#define VSCP_REG_GUID_11                    (VSCP_REGISTER_VSCP_START_ADDR + 84)

/** VSCP register: GUID byte 10 */
#define VSCP_REG_GUID_10                    (VSCP_REGISTER_VSCP_START_ADDR + 85)

/** VSCP register: GUID byte 9 */
#define VSCP_REG_GUID_9                     (VSCP_REGISTER_VSCP_START_ADDR + 86)

/** VSCP register: GUID byte 8 */
#define VSCP_REG_GUID_8                     (VSCP_REGISTER_VSCP_START_ADDR + 87)

/** VSCP register: GUID byte 7 */
#define VSCP_REG_GUID_7                     (VSCP_REGISTER_VSCP_START_ADDR + 88)

/** VSCP register: GUID byte 6 */
#define VSCP_REG_GUID_6                     (VSCP_REGISTER_VSCP_START_ADDR + 89)

/** VSCP register: GUID byte 5 */
#define VSCP_REG_GUID_5                     (VSCP_REGISTER_VSCP_START_ADDR + 90)

/** VSCP register: GUID byte 4 */
#define VSCP_REG_GUID_4                     (VSCP_REGISTER_VSCP_START_ADDR + 91)

/** VSCP register: GUID byte 3 */
#define VSCP_REG_GUID_3                     (VSCP_REGISTER_VSCP_START_ADDR + 92)

/** VSCP register: GUID byte 2 */
#define VSCP_REG_GUID_2                     (VSCP_REGISTER_VSCP_START_ADDR + 93)

/** VSCP register: GUID byte 1 */
#define VSCP_REG_GUID_1                     (VSCP_REGISTER_VSCP_START_ADDR + 94)

/** VSCP register: GUID byte 0 (LSB) */
#define VSCP_REG_GUID_0                     (VSCP_REGISTER_VSCP_START_ADDR + 95)

/** VSCP register: module description file URL begin */
#define VSCP_REG_MDF_URL_BEGIN              (VSCP_REGISTER_VSCP_START_ADDR + 96)

/** VSCP register: module description file URL end */
#define VSCP_REG_MDF_URL_END                (VSCP_REGISTER_VSCP_START_ADDR + 127)

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** This type defines the message priorities. */
typedef enum
{
    VSCP_PRIORITY_0_HIGH = 0,   /**< High priority */
    VSCP_PRIORITY_1,            /**< Priority 1 */
    VSCP_PRIORITY_2,            /**< Priority 2 */
    VSCP_PRIORITY_3_NORMAL,     /**< Priority 3 */
    VSCP_PRIORITY_4,            /**< Priority 4 */
    VSCP_PRIORITY_5,            /**< Priority 5 */
    VSCP_PRIORITY_6,            /**< Priority 6 */
    VSCP_PRIORITY_7_LOW         /**< Low priority */

} VSCP_PRIORITY;

/** This type defines a VSCP message. */
typedef struct
{
    VSCP_PRIORITY   priority;                   /**< Message priority */
    uint16_t        vscpClass;                  /**< VSCP class */
    uint8_t         vscpType;                   /**< VSCP type */
    uint8_t         oAddr;                      /**< Message originating address */
    BOOL            hardCoded;                  /**< Is hard coded node (TRUE) or dynamic node (FALSE) */
    uint8_t         dataNum;                    /**< Number of data bytes */
    /*@reldef@*/
    uint8_t         data[VSCP_L1_DATA_SIZE];    /**< Data */

} vscp_Message;

/** This type defines a VSCP receive message. */
typedef vscp_Message vscp_RxMessage;

/** This type defines a VSCP transmit message. */
typedef vscp_Message vscp_TxMessage;

/** This type defines the different information lamp states. */
typedef enum
{
    VSCP_LAMP_STATE_OFF = 0,    /**< Lamp is off */
    VSCP_LAMP_STATE_ON,         /**< Lamp is on */
    VSCP_LAMP_STATE_BLINK_SLOW, /**< Lamp is slow blinking */
    VSCP_LAMP_STATE_BLINK_FAST  /**< Lamp is fast blinking */

} VSCP_LAMP_STATE;

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_TYPES_H__ */

/** @} */
