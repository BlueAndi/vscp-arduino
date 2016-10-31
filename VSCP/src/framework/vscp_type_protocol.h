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
@brief  VSCP class 1 protocol types
@file   vscp_type_protocol.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This header contains all level 1 protocol class defined types.

*******************************************************************************/
/** @defgroup vscp_type_protocol Protocol class types
 * Level 1 protocol class types
 * @{
 * @ingroup vscp_l1
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_TYPE_PROTOCOL_H__
#define __VSCP_TYPE_PROTOCOL_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/

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

/** VSCP class 1 protocol type: Undefined */
#define VSCP_TYPE_PROTOCOL_UNDEFINED                            0

/** VSCP class 1 protocol type: Segment Controller Hearbeat */
#define VSCP_TYPE_PROTOCOL_SEGMENT_CONTROLLER_HEARTBEAT         1

/** VSCP class 1 protocol type: New node on line / Probe */
#define VSCP_TYPE_PROTOCOL_NEW_NODE_ONLINE                      2

/** VSCP class 1 protocol type: Probe acknowledge */
#define VSCP_TYPE_PROTOCOL_PROBE_ACK                            3

/** VSCP class 1 protocol type: Reserved for future use */
#define VSCP_TYPE_PROTOCOL_RESERVED_1                           4

/** VSCP class 1 protocol type: Reserved for future use */
#define VSCP_TYPE_PROTOCOL_RESERVED_2                           5

/** VSCP class 1 protocol type: Set nickname-ID for node */
#define VSCP_TYPE_PROTOCOL_SET_NICKNAME_ID                      6

/** VSCP class 1 protocol type: Nickname-ID accepted */
#define VSCP_TYPE_PROTOCOL_NICKNAME_ID_ACCEPTED                 7

/** VSCP class 1 protocol type: Drop nickname-ID / Reset device */
#define VSCP_TYPE_PROTOCOL_DROP_NICKNAME_ID                     8

/** VSCP class 1 protocol type: Read register */
#define VSCP_TYPE_PROTOCOL_READ_REGISTER                        9

/** VSCP class 1 protocol type: Read / Write resposne */
#define VSCP_TYPE_PROTOCOL_READ_WRITE_RESPONSE                  10

/** VSCP class 1 protocol type: Write register */
#define VSCP_TYPE_PROTOCOL_WRITE_REGISTER                       11

/** VSCP class 1 protocol type: Enter boot loader mode */
#define VSCP_TYPE_PROTOCOL_ENTER_BOOT_LOADER_MODE               12

/** VSCP class 1 protocol type: Acknowledge boot loader mode */
#define VSCP_TYPE_PROTOCOL_ENTER_BOOT_LOADER_MODE_ACK           13

/** VSCP class 1 protocol type: Negative acknowledge boot loader mode */
#define VSCP_TYPE_PROTOCOL_ENTER_BOOT_LOADER_MODE_NACK          14

/** VSCP class 1 protocol type: Start block data transfer */
#define VSCP_TYPE_PROTOCOL_START_BLOCK_DATA_TRANSFER            15

/** VSCP class 1 protocol type: Block data */
#define VSCP_TYPE_PROTOCOL_BLOCK_DATA                           16

/** VSCP class 1 protocol type: Data block acknowledge */
#define VSCP_TYPE_PROTOCOL_BLOCK_DATA_ACK                       17

/** VSCP class 1 protocol type: Data block negative acknowledge */
#define VSCP_TYPE_PROTOCOL_BLOCK_DATA_NACK                      18

/** VSCP class 1 protocol type: Program data block */
#define VSCP_TYPE_PROTOCOL_PROGRAM_DATA_BLOCK                   19

/** VSCP class 1 protocol type: Program data block acknowledge */
#define VSCP_TYPE_PROTOCOL_PROGRAM_DATA_BLOCK_ACK               20

/** VSCP class 1 protocol type: Program data block negative acknowledge */
#define VSCP_TYPE_PROTOCOL_PROGRAM_DATA_BLOCK_NACK              21

/** VSCP class 1 protocol type: Activate new image */
#define VSCP_TYPE_PROTOCOL_ACTIVATE_NEW_IMAGE                   22

/** VSCP class 1 protocol type: GUID drop nickname-ID / reset device */
#define VSCP_TYPE_PROTOCOL_GUID_DROP_NICKNAME_ID                23

/** VSCP class 1 protocol type: Page read */
#define VSCP_TYPE_PROTOCOL_PAGE_READ                            24

/** VSCP class 1 protocol type: Page write */
#define VSCP_TYPE_PROTOCOL_PAGE_WRITE                           25

/** VSCP class 1 protocol type: Read/Write page response */
#define VSCP_TYPE_PROTOCOL_PAGE_READ_WRITE_RESPONSE             26

/** VSCP class 1 protocol type: High end server probe */
#define VSCP_TYPE_PROTOCOL_HIGH_END_SERVER_PROBE                27

/** VSCP class 1 protocol type: High end server response */
#define VSCP_TYPE_PROTOCOL_HIGH_END_SERVER_RESPONSE             28

/** VSCP class 1 protocol type: Increment register */
#define VSCP_TYPE_PROTOCOL_INCREMENT_REGISTER                   29

/** VSCP class 1 protocol type: Decrement register */
#define VSCP_TYPE_PROTOCOL_DECREMENT_REGISTER                   30

/** VSCP class 1 protocol type: Who is there? */
#define VSCP_TYPE_PROTOCOL_WHO_IS_THERE                         31

/** VSCP class 1 protocol type: */
#define VSCP_TYPE_PROTOCOL_WHO_IS_THERE_RESPONSE                32

/** VSCP class 1 protocol type: Get decision matrix info */
#define VSCP_TYPE_PROTOCOL_GET_DECISION_MATRIX_INFO             33

/** VSCP class 1 protocol type: Decision matrix info response */
#define VSCP_TYPE_PROTOCOL_GET_DECISION_MATRIX_INFO_RESPONSE    34

/** VSCP class 1 protocol type: Get embedded module description file (MDF) */
#define VSCP_TYPE_PROTOCOL_GET_EMBEDDED_MDF                     35

/** VSCP class 1 protocol type: Get embedded module description file response */
#define VSCP_TYPE_PROTOCOL_GET_EMBEDDED_MDF_RESPONSE            36

/** VSCP class 1 protocol type: Extended page read register */
#define VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_READ_REGISTER          37

/** VSCP class 1 protocol type: Extended page write register */
#define VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_WRITE_REGISTER         38

/** VSCP class 1 protocol type: Extended page read/write response */
#define VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_READ_WRITE_RESPONSE    39

/** VSCP class 1 protocol type: Get event interest */
#define VSCP_TYPE_PROTOCOL_GET_EVENT_INTEREST                   40

/** VSCP class 1 protocol type: Get event interest response */
#define VSCP_TYPE_PROTOCOL_GET_EVENT_INTEREST_RESPONSE          41

/** VSCP class 1 protocol type: Activate new image acknowledge */
#define VSCP_TYPE_PROTOCOL_ACTIVATE_NEW_IMAGE_ACK               48

/** VSCP class 1 protocol type: Activate new image negative acknowledge */
#define VSCP_TYPE_PROTOCOL_ACTIVATE_NEW_IMAGE_NACK              49

/** VSCP class 1 protocol type: Start block data transfer acknowledge */
#define VSCP_TYPE_PROTOCOL_START_BLOCK_DATA_TRANSFER_ACK        50

/** VSCP class 1 protocol type: Start block data transfer negative acknowledge */
#define VSCP_TYPE_PROTOCOL_START_BLOCK_DATA_TRANSFER_NACK       51

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

#endif  /* __VSCP_TYPE_PROTOCOL_H__ */

/** @} */
