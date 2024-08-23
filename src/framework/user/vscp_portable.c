/* The MIT License (MIT)
 *
 * Copyright (c) 2014 - 2024 Andreas Merkle
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
@brief  VSCP portable support package
@file   vscp_portable.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_portable.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_portable.h"
#include "../core/vscp_core.h"

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

/** State of the status lamp. */
static VSCP_LAMP_STATE  vscp_portable_statusLampState   = VSCP_LAMP_STATE_OFF;

/** Receive message storage */
static vscp_RxMessage   vscp_portable_rxMsg;

/** Flag which notify about a received message */
static BOOL             vscp_portable_isReceived        = FALSE;

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes this module.
 */
extern void vscp_portable_init(void)
{
    /* Implement your code here ... */

    return;
}

/**
 * Restore the application specific factory default settings.
 */
extern void vscp_portable_restoreFactoryDefaultSettings(void)
{
    /* Implement your code here ... */

    return;
}

/**
 * This function set the current lamp state.
 *
 * @param[in]   state   Lamp state to set
 */
extern void vscp_portable_setLampState(VSCP_LAMP_STATE state)
{
    vscp_portable_statusLampState = state;
    return;
}

/**
 * This function return the current lamp state.
 *
 * @return Lamp state
 */
extern VSCP_LAMP_STATE vscp_portable_getLampState(void)
{
    return vscp_portable_statusLampState;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_IDLE_CALLOUT )

/**
 * If VSCP stops its work and enters idle state, this function will be called.
 */
extern void vscp_portable_idleStateEntered(void)
{
    /* Implement your code here ... */

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_IDLE_CALLOUT ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ERROR_CALLOUT )

/**
 * If VSCP stops its work and enters error state, this function will be called.
 */
extern void vscp_portable_errorStateEntered(void)
{
    /* Implement your code here ... */

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ERROR_CALLOUT ) */

/**
 * This function requests a reset.
 * It requests it and doesn't expect that it will be immediately.
 * Because the application needs time to change to a safe state before.
 */
extern void vscp_portable_resetRequest(void)
{
    /* Implement your code here ... */

    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED )

/**
 * This function returns the supported boot loader algorithm.
 *
 * @return  Boot loader algorithm
 * @retval  0xFF    No boot loader supported
 */
extern uint8_t  vscp_portable_getBootLoaderAlgorithm(void)
{
    uint8_t algorithm   = 0xFF;

    /* Implement your code here ... */

    return algorithm;
}

/**
 * This function requests a jump to the bootloader.
 * It requests it and doesn't expect that it will be immediately.
 * Because the application needs time to change to a safe state before.
 */
extern void vscp_portable_bootLoaderRequest(void)
{
    /* Implement your code here ... */

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */

/**
 * This function provides received VSCP events, except the PROTOCOL class.
 *
 * @param[in]   msg Message
 */
extern void vscp_portable_provideEvent(vscp_RxMessage const * const msg)
{
    vscp_portable_rxMsg         = *msg;
    vscp_portable_isReceived    = TRUE;
    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION )

/**
 * This function provides received VSCP PROTOCOL class events.
 *
 * Attention: Handling events which the core is waiting for can cause bad
 * behaviour.
 * 
 * @param[in]   msg Message
 * 
 * @return Event handled or not. If application handles event, the core won't handle it.
 * @retval FALSE    Event not handled
 * @retval TRUE     Event handled
 */
extern BOOL vscp_portable_provideProtocolEvent(vscp_RxMessage const * const msg)
{
    BOOL isEventHandled = FALSE;

    /* Implement your code here ... */

    return isEventHandled;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT )

/**
 * This function is called for every received segment master heartbeat event,
 * in case it contains a new time since epoch.
 * 
 * @param timestamp Unix timestamp
 */
extern void vscp_portable_updateTimeSinceEpoch(uint32_t timestamp)
{
    /* Implement your code here ... */

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT )

/**
 * This function returns one byte of the GUID, which is selected by the index.
 * Index 0 corresponds with the GUID LSB byte, index 15 with the GUID MSB byte.
 * 
 * Note, this function can be used to get the MCU stored GUID.
 *
 * @param[in]   index   Index in the GUID [0-15]
 * @return  GUID byte
 */
extern uint8_t  vscp_portable_readGUID(uint8_t index)
{
    uint8_t value = 0;

    /* Implement your code here ... */

    return value;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DEV_DATA_CONFIG_ENABLE_GUID_STORAGE_EXT ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_CUSTOM_HEARTBEAT )

/**
 * Custom node heartbeat event function implementation.
 *
 * @return Status
 * @retval FALSE Failed to send the event
 * @retval TRUE  Event successul sent
 */
extern BOOL vscp_portable_sendNodeHeartbeatEvent() {
   
    /* Implement your version of vscp_information_sendNodeHeartbeatEvent() */

    return TRUE;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_CUSTOM_HEARTBEAT ) */

/**
 * This function read a received VSCP message.
 * If no message is received it returns FALSE otherwise TRUE.
 *
 * @param[out]  msg Message
 * @return Message received or not
 */
extern BOOL vscp_portable_read(vscp_RxMessage * const msg)
{
    BOOL    status  = FALSE;

    if (NULL != msg)
    {
        if (TRUE == vscp_portable_isReceived)
        {
            *msg                        = vscp_portable_rxMsg;
            status                      = TRUE;
            vscp_portable_isReceived    = FALSE;
        }
    }
    
    return status;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

