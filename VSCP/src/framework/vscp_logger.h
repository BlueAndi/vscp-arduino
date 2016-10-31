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
@brief  VSCP logger
@file   vscp_logger.h
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
This module handles VSCP logging messages, dependend from the activated log
level.

*******************************************************************************/
/** @defgroup vscp_logger VSCP logger
 * The logger handles all kind of log messages, which are sent directly to the
 * VSCP transport layer. There is no buffering of log messages, so it can
 * happend that a complete message or parts of a message will be lost.
 *
 * Parts of a message means, if the message is defragmented in several VSCP
 * events, it can happen that a event will be lost.
 *
 * Supported compile switches:
 * - VSCP_CONFIG_ENABLE_LOGGER
 *
 * @{
 */

/*
 * Don't forget to set JAVADOC_AUTOBRIEF to YES in the doxygen file to generate
 * a correct module description.
 */

#ifndef __VSCP_LOGGER_H__
#define __VSCP_LOGGER_H__

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include <inttypes.h>
#include "vscp_config.h"
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

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

/** Log INFO message with id. */
#define LOG_INFO(__id)      vscp_logger_log((__id), VSCP_LOGGER_LVL_INFO, NULL, 0)

/** Log DEBUG message with id. */
#define LOG_DEBUG(__id)     vscp_logger_log((__id), VSCP_LOGGER_LVL_DEBUG, NULL, 0)

/** Log WARNING message with id. */
#define LOG_WARNING(__id)   vscp_logger_log((__id), VSCP_LOGGER_LVL_WARNING, NULL, 0)

/** Log ERROR message with id. */
#define LOG_ERROR(__id)     vscp_logger_log((__id), VSCP_LOGGER_LVL_ERROR, NULL, 0)

/** Log FATAL message with id. */
#define LOG_FATAL(__id)     vscp_logger_log((__id), VSCP_LOGGER_LVL_FATAL, NULL, 0)

/** Log INFO message with id and 32-bit unsigned integer value. */
#define LOG_INFO_UINT32(__id, __value)      do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_INFO, (__value)); }while(0)

/** Log DEBUG message with id and 32-bit unsigned integer value. */
#define LOG_DEBUG_UINT32(__id, __value)     do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_DEBUG, (__value)); }while(0)

/** Log WARNING message with id and 32-bit unsigned integer value. */
#define LOG_WARNING_UINT32(__id, __value)   do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_WARNING, (__value)); }while(0)

/** Log ERROR message with id and 32-bit unsigned integer value. */
#define LOG_ERROR_UINT32(__id, __value)     do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_ERROR, (__value)); }while(0)

/** Log FATAL message with id and 32-bit unsigned integer value. */
#define LOG_FATAL_UINT32(__id, __value)     do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_FATAL, (__value)); }while(0)

/** Log INFO message with id and 32-bit signed integer value. */
#define LOG_INFO_INT32(__id, __value)       do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_INFO, (uint32_t)(__value)); }while(0)

/** Log DEBUG message with id and 32-bit signed integer value. */
#define LOG_DEBUG_INT32(__id, __value)      do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_DEBUG, (uint32_t)(__value)); }while(0)

/** Log WARNING message with id and 32-bit signed integer value. */
#define LOG_WARNING_INT32(__id, __value)    do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_WARNING, (uint32_t)(__value)); }while(0)

/** Log ERROR message with id and 32-bit signed integer value. */
#define LOG_ERROR_INT32(__id, __value)      do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_ERROR, (uint32_t)(__value)); }while(0)

/** Log FATAL message with id and 32-bit signed integer value. */
#define LOG_FATAL_INT32(__id, __value)      do{ vscp_logger_logUInt32((__id), VSCP_LOGGER_LVL_FATAL, (uint32_t)(__value)); }while(0)

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

/** Log INFO message with id. */
#define LOG_INFO(__id)

/** Log DEBUG message with id. */
#define LOG_DEBUG(__id)

/** Log WARNING message with id. */
#define LOG_WARNING(__id)

/** Log ERROR message with id. */
#define LOG_ERROR(__id)

/** Log FATAL message with id. */
#define LOG_FATAL(__id)

/** Log INFO message with id and 32-bit unsigned integer value. */
#define LOG_INFO_UINT32(__id, __value)

/** Log DEBUG message with id and 32-bit unsigned integer value. */
#define LOG_DEBUG_UINT32(__id, __value)

/** Log WARNING message with id and 32-bit unsigned integer value. */
#define LOG_WARNING_UINT32(__id, __value)

/** Log ERROR message with id and 32-bit unsigned integer value. */
#define LOG_ERROR_UINT32(__id, __value)

/** Log FATAL message with id and 32-bit unsigned integer value. */
#define LOG_FATAL_UINT32(__id, __value)

/** Log INFO message with id and 32-bit signed integer value. */
#define LOG_INFO_INT32(__id, __value)

/** Log DEBUG message with id and 32-bit signed integer value. */
#define LOG_DEBUG_INT32(__id, __value)

/** Log WARNING message with id and 32-bit signed integer value. */
#define LOG_WARNING_INT32(__id, __value)

/** Log ERROR message with id and 32-bit signed integer value. */
#define LOG_ERROR_INT32(__id, __value)

/** Log FATAL message with id and 32-bit signed integer value. */
#define LOG_FATAL_INT32(__id, __value)

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** This type defines the different log levels. */
typedef enum
{
    VSCP_LOGGER_LVL_INFO = 0,   /**< The INFO level designates informational messages that highlight the progress of the application at coarse-grained level. */
    VSCP_LOGGER_LVL_DEBUG,      /**< The DEBUG level designates fine-grained informational events that are most useful to debug an application. */
    VSCP_LOGGER_LVL_WARNING,    /**< The WARN level designates potentially harmful situations. */
    VSCP_LOGGER_LVL_ERROR,      /**< The ERROR level designates error events that might still allow the application to continue running. */
    VSCP_LOGGER_LVL_FATAL,      /**< The FATAL level designates very severe error events that will presumably lead the application to abort. */
    VSCP_LOGGER_LVL_USER1,      /**< User defined level 1 */
    VSCP_LOGGER_LVL_USER2,      /**< User defined level 2 */
    VSCP_LOGGER_LVL_USER3       /**< User defined level 3 */

} VSCP_LOGGER_LVL;

/*******************************************************************************
    VARIABLES
*******************************************************************************/

/*******************************************************************************
    FUNCTIONS
*******************************************************************************/

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

/**
 * This function initializes the logger module.
 */
extern void vscp_logger_init(void);

/**
 * This function enables/disables the logging, independent of CLASS1.Log.LogStart.
 */
extern void vscp_logger_enable(BOOL enableIt);

/**
 * This function gets the current log level(s).
 *
 * @return Current log level(s) (bitfield)
 */
extern uint8_t vscp_logger_getLogLevel(void);

/**
 * This function sets the current log level(s).
 *
 * @param[in] level Log level(s) (bitfield)
 */
extern void vscp_logger_setLogLevel(uint8_t level);

/**
 * This function sends a log message, depended on the active log level.
 *
 * @param[in] id    Message id
 * @param[in] level Log level
 * @param[in] msg   Message
 * @param[in] size  Message size in bytes
 */
extern void vscp_logger_log(uint8_t id, VSCP_LOGGER_LVL level, uint8_t const * const msg, uint8_t size);

/**
 * This function sends a log message, depended on the active log level.
 *
 * @param[in] id    Message id
 * @param[in] level Log level
 * @param[in] value Value
 */
extern void vscp_logger_logUInt32(uint8_t id, VSCP_LOGGER_LVL level, uint32_t value);

/**
 * This function handles all CLASS1.Log events, which controls the logging functionality.
 * It will be called by the VSCP core.
 *
 * @param[in] msg   Received event message
 */
extern void vscp_logger_handleEvent(vscp_RxMessage const * const msg);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

/**
 * Message for Log. Several frames have to be sent for a event that take up more the
 * five bytes which is the maximum for each frame. In this case the zero based index
 * (byte 2) should be increased for each frame.
 *
 * @param[in] id ID for event.
 * @param[in] level Log level for message.
 * @param[in] msg Message.
 * @param[in] size Message size in bytes.
 * @return Status
 * @retval FALSE Failed to send the event
 * @retval TRUE  Event successful sent
 *
 */
extern BOOL vscp_logger_sendLogEvent(uint8_t id, uint8_t level, uint8_t const * const msg, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif  /* __VSCP_LOGGER_H__ */

/** @} */
