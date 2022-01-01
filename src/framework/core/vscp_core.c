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
@brief  VSCP core functionality
@file   vscp_core.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_core.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_core.h"
#include "vscp_dev_data.h"
#include "../user/vscp_portable.h"
#include "vscp_transport.h"
#include "vscp_class_l1.h"
#include "vscp_type_protocol.h"
#include "vscp_type_information.h"
#include "../events/vscp_evt_information.h"
#include "vscp_ps.h"
#include "../user/vscp_timer.h"
#include "../user/vscp_app_reg.h"
#include "vscp_dm.h"
#include "vscp_dm_ng.h"
#include "vscp_util.h"
#include "../user/vscp_action.h"
#include "vscp_logger.h"

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HARD_CODED_NODE )

/** Node is hard coded. */
#define VSCP_CORE_HARD_CODED    TRUE

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_HARD_CODED_NODE ) */

/** Node is a dynamic node. */
#define VSCP_CORE_HARD_CODED    FALSE

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_HARD_CODED_NODE ) */

/** Timer threshold of 1s in ms */
#define VSCP_CORE_TIMER_THRESHOLD_1S    ((uint16_t)1000)

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/** VSCP core stack states */
typedef enum
{
    STATE_STARTUP = 0,  /**< Initial state after power-up */
    STATE_INIT,         /**< Node segment initialization */
    STATE_PREACTIVE,    /**< Node wait for nickname id assignment */
    STATE_ACTIVE,       /**< Node is in working order */
    STATE_IDLE,         /**< Idle state */
    STATE_RESET,        /**< Reset state */
    STATE_ERROR         /**< Error state */

} STATE;

/** VSCP node segment initialization sub state */
typedef enum
{
    INIT_STATE_PROBE_MASTER = 0,    /**< Notify segment master via probe event */
    INIT_STATE_PROBE_MASTER_WAIT,   /**< Wait for segment master acknowledge */
    INIT_STATE_PROBE,               /**< Probe nickname */
    INIT_STATE_PROBE_WAIT           /**< Wait for probe acknowledge */

} INIT_STATE;

/**
 * This type is used to store all necessary information, used by a extended
 * page read event.
 */
typedef struct
{
    uint16_t    page;   /**< Page */
    uint8_t     addr;   /**< Address (offset in page) */
    uint16_t    count;  /**< Number of registers to read */
    uint8_t     seq;    /**< Sequence id */

} ExtPageRead;

/*******************************************************************************
    PROTOTYPES
*******************************************************************************/

static void vscp_core_writeNicknameId(uint8_t nickname);
static BOOL vscp_core_checkPersistentMemory(void);
static void vscp_core_stateStartup(void);
static void vscp_core_changeToStateInit(BOOL probeSegmentMaster);
static void vscp_core_stateInit(void);
static void vscp_core_changeToStatePreActive(void);
static void vscp_core_statePreActive(void);
static void vscp_core_changeToStateActive(void);
static void vscp_core_stateActive(void);
static void vscp_core_changeToStateIdle(void);
static void vscp_core_stateIdle(void);
static void vscp_core_changeToStateReset(uint8_t timeout);
static void vscp_core_stateReset(void);
static void vscp_core_changeToStateError(void);
static void vscp_core_stateError(void);
static void vscp_core_handleProtocolClassType(void);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT )
static void vscp_core_handleProtocolHeartbeat(void);
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT ) */

static void vscp_core_handleProtocolNewNodeOnline(void);
static void vscp_core_handleProtocolProbeAck(void);
static void vscp_core_handleProtocolSetNicknameId(void);
static void vscp_core_handleProtocolDropNicknameId(void);
static void vscp_core_handleProtocolReadRegister(void);
static void vscp_core_sendRegisterReadWriteRsp(uint8_t addr, uint8_t value);
static uint8_t vscp_core_readRegister(uint16_t page, uint8_t addr);
static uint8_t vscp_core_writeRegister(uint16_t page, uint8_t addr, uint8_t value, /*@null@*/ BOOL* failed);
static void vscp_core_handleProtocolWriteRegister(void);
static void vscp_core_handleProtocolEnterBootLoaderMode(void);
static void vscp_core_handleProtocolGuidDropNickname(void);
static void vscp_core_handleProtocolPageRead(void);
static void vscp_core_handleProtocolPageWrite(void);
static void vscp_core_handleProtocolIncrementRegister(void);
static void vscp_core_handleProtocolDecrementRegister(void);
static void vscp_core_handleProtocolWhoIsThere(void);
static void vscp_core_handleProtocolGetDecisionMatrixInfo(void);
static void vscp_core_handleProtocolExtendedPageReadRegister(void);
static void vscp_core_extendedPageReadRegister(ExtPageRead * const data);
static void vscp_core_handleProtocolExtendedPageWriteRegister(void);
static uint8_t vscp_core_getStartUpControl(void);
static uint8_t vscp_core_getRegAppWriteProtect(void);

/*******************************************************************************
    LOCAL VARIABLES
*******************************************************************************/

/** Node nickname id */
static uint8_t          vscp_core_nickname          = VSCP_NICKNAME_NOT_INIT;

/** Current state of the VSCP core stack */
static STATE            vscp_core_state             = STATE_STARTUP;

/** Sub state of main state init */
static INIT_STATE       vscp_core_initState         = INIT_STATE_PROBE;

/** Receive message storage */
static vscp_RxMessage   vscp_core_rxMessage;

/** Receive message storage contains a valid message or not. */
static BOOL             vscp_core_rxMessageValid    = FALSE;

/** Timer id, which is used for timeout handling, regarding state transitions. */
static uint8_t          vscp_core_timerId                   = VSCP_TIMER_ID_INVALID;

/** Timer id, which is used for GUID drop nickname multi-frame timeout. */
static uint8_t          vscp_core_timerIdGuidDropNickname   = VSCP_TIMER_ID_INVALID;

/** Timer id, which is used for vscp register 162 multi-frame timeout. */
static uint8_t          vscp_core_timerIdReg162             = VSCP_TIMER_ID_INVALID;

/** Timer id, which is used to drive the time since epoch (unix timestamp). */
static uint8_t          vscp_core_timerIdTimeSinceEpoch     = VSCP_TIMER_ID_INVALID;

/** Seconds counter, used to wait for reset request. */
static uint8_t          vscp_core_secCnt            = 0;

/** Nickname id used during nickname discovery process */
static uint8_t          vscp_core_nickname_probe    = VSCP_NICKNAME_NOT_INIT;

/** Time since epoch 00:00:00 UTC, January 1, 1970 (unix timestamp) in s */
static uint32_t         vscp_core_timeSinceEpoch    = 0;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE )

/** Timer id, which is used for node heartbeat handling. */
static uint8_t          vscp_core_heartbeatTimerId      = VSCP_TIMER_ID_INVALID;

/** Enable/Disable node heartbeat */
static BOOL             vscp_core_isHeartbeatEnabled    = TRUE;

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

/** Register: alarm status */
static uint8_t          vscp_core_regAlarmStatus    = 0;

/** Register: page select */
static uint16_t         vscp_core_regPageSelect     = 0;

/** Reset requested or not */
static BOOL             vscp_core_resetRequested    = FALSE;

/**
 * Extended page read data, which is used to continue a extended page read in
 * the next process cycle.
 */
static ExtPageRead      vscp_core_extPageReadData   = { 0, 0, 0, 0 };

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes VSCP, including all layers.
 * Don't call any other VSCP function, until this function was called.
 *
 * @return Execution result
 */
extern VSCP_CORE_RET vscp_core_init(void)
{
    VSCP_CORE_RET   ret = VSCP_CORE_RET_OK;

    /* Initialize persistent memory access */
    vscp_ps_init();

    /* Initialize timer driver */
    vscp_timer_init();

    /* Initialize transport layer */
    vscp_transport_init();

    /* Initialize device data */
    vscp_dev_data_init();

    /* Initialize the application register access */
    vscp_app_reg_init();

    /* Initialize portable functions */
    vscp_portable_init();

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

    /* Initialize decision matrix functions */
    vscp_dm_init();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

    /* Initialize decision matrix next generation functions */
    vscp_dm_ng_init();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) || VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

    /* Initialize action module */
    vscp_action_init();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) || VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

    /* Initialize logger module */
    vscp_logger_init();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

    /* Initialize utilities module */
    vscp_util_init();

    vscp_core_nickname          = vscp_ps_readNicknameId();
    vscp_core_state             = STATE_STARTUP;
    vscp_core_initState         = INIT_STATE_PROBE;
    vscp_core_resetRequested    = FALSE;

    vscp_core_rxMessage.vscpClass   = VSCP_CLASS_L1_PROTOCOL;
    vscp_core_rxMessage.vscpType    = VSCP_TYPE_PROTOCOL_GENERAL;
    vscp_core_rxMessage.priority    = VSCP_PRIORITY_7_LOW;
    vscp_core_rxMessage.oAddr       = VSCP_NICKNAME_NOT_INIT;
    vscp_core_rxMessage.hardCoded   = FALSE;
    vscp_core_rxMessageValid        = FALSE;

    /* Show the user that the node starts up. */
    vscp_portable_setLampState(VSCP_LAMP_STATE_BLINK_SLOW);

    /* Create a timer for common timing issues */
    vscp_core_timerId = vscp_timer_create();
    if (VSCP_TIMER_ID_INVALID == vscp_core_timerId)
    {
        /* No timer available. */
        ret = VSCP_CORE_RET_ERROR;
    }

    /* Create a timer for GUID drop nickname multi-frame timeout. */
    vscp_core_timerIdGuidDropNickname = vscp_timer_create();
    if (VSCP_TIMER_ID_INVALID == vscp_core_timerIdGuidDropNickname)
    {
        /* No timer available. */
        ret = VSCP_CORE_RET_ERROR;
    }

    /* Create a timer for vscp register 162 multi-frame timeout. */
    vscp_core_timerIdReg162 = vscp_timer_create();
    if (VSCP_TIMER_ID_INVALID == vscp_core_timerIdReg162)
    {
        /* No timer available. */
        ret = VSCP_CORE_RET_ERROR;
    }

    /* Create a timer used to drive the internal time since epoch (unix timestamp). */
    vscp_core_timerIdTimeSinceEpoch = vscp_timer_create();
    if (VSCP_TIMER_ID_INVALID == vscp_core_timerIdTimeSinceEpoch)
    {
        /* No timer available. */
        ret = VSCP_CORE_RET_ERROR;
    }
    else
    {
        /* Start timer immediately. */
        vscp_timer_start(vscp_core_timerIdTimeSinceEpoch, VSCP_CORE_TIMER_THRESHOLD_1S);
    }

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE )

    /* Create a timer for own heartbeat */
    vscp_core_heartbeatTimerId = vscp_timer_create();
    if (VSCP_TIMER_ID_INVALID == vscp_core_heartbeatTimerId)
    {
        /* No timer available. */
        ret = VSCP_CORE_RET_ERROR;
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

    /* Verify persistent memory by checking the node control flags,
       especially the start up control. Because the start up control bits can
       be only 01b or 10b.
     */
    if (FALSE == vscp_core_checkPersistentMemory())
    {
        /* Reset to default values. */
        vscp_core_restoreFactoryDefaultSettings();
    }

    /* Any error happened? */
    if (VSCP_CORE_RET_OK != ret)
    {
        vscp_core_changeToStateError();
    }

    return ret;
}

/**
 * This function restores VSCP default values for
 * - all registers,
 * - the persistent memory,
 * - internal variables.
 *
 * In other words, it restore factory defaults settings.
 */
extern void vscp_core_restoreFactoryDefaultSettings(void)
{
    uint8_t index   = 0;

    vscp_core_regAlarmStatus    = 0;
    vscp_core_regPageSelect     = 0;

    vscp_core_extPageReadData.page  = 0;
    vscp_core_extPageReadData.addr  = 0;
    vscp_core_extPageReadData.count = 0;
    vscp_core_extPageReadData.seq   = 0;

    /* Clear nickname id */
    vscp_core_writeNicknameId(VSCP_NICKNAME_NOT_INIT);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT )

    /* Clear segment controller CRC */
    vscp_ps_writeSegmentControllerCRC(VSCP_SEGMENT_CRC_NOT_INIT);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT ) */

    /* Wait for explicit initialization and remove application registers
     * write protection.
     */
    vscp_ps_writeNodeControlFlags(VSCP_NODE_CONTROL_FLAGS_DEFAULT);

    /* Reset user id */
    for(index = 0; index < VSCP_PS_SIZE_USER_ID; ++index)
    {
        vscp_ps_writeUserId(index, 0);
    }

    /* Restore VSCP device data factory default settings */
    vscp_dev_data_restoreFactoryDefaultSettings();

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

    /* Restore VSCP decision matrix factory default settings */
    vscp_dm_restoreFactoryDefaultSettings();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

    vscp_dm_ng_restoreFactoryDefaultSettings();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

    /* Restore application register factory default settings */
    vscp_app_reg_restoreFactoryDefaultSettings();

    /* Restore application factory default settings */
    vscp_portable_restoreFactoryDefaultSettings();

    return;
}

/**
 * This function process the whole VSCP core stack. Call it in a user defined
 * cyclic period.
 *
 * Note, for a fast handling of received events, this function returns TRUE in
 * case a event was handled, otherwise FALSE. Call it e.g. in a loop until no
 * event is handled anymore. If its not necessary in your application, just
 * skip the return value.
 *
 * @return If a received event was handled, it will return TRUE otherwise FALSE.
 */
extern BOOL vscp_core_process(void)
{
    BOOL isEventHandled = FALSE;

    /* Get any received message.
     * Note, only in the active state all received messages are processed.
     * In the other ones it depends on their sub state.
     */
    vscp_core_rxMessageValid = vscp_transport_readMessage(&vscp_core_rxMessage);
    isEventHandled = vscp_core_rxMessageValid;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER )

    /* Handle early as possible any kind of log control messages. */
    vscp_logger_handleEvent(&vscp_core_rxMessage);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_LOGGER ) */

    /* Handle internal time since epoch (unix timestamp), which increase per second. */
    if ((VSCP_TIMER_ID_INVALID != vscp_core_timerIdTimeSinceEpoch) &&
        (FALSE == vscp_timer_getStatus(vscp_core_timerIdTimeSinceEpoch)))
    {
        /* Increase unix timestamp */
        ++vscp_core_timeSinceEpoch;

        /* Restart timer */
        vscp_timer_start(vscp_core_timerIdTimeSinceEpoch, VSCP_CORE_TIMER_THRESHOLD_1S);
    }

    /* State machine */
    switch(vscp_core_state)
    {
    /* VSCP is initialized, what about the nickname id? */
    case STATE_STARTUP:
        vscp_core_stateStartup();
        break;

    /* No nickname id is assigned, starting discovery. */
    case STATE_INIT:
        vscp_core_stateInit();
        break;

    /* Node nickname id assignment by segment master. */
    case STATE_PREACTIVE:
        vscp_core_statePreActive();
        break;

    /* Node is active and awaits something to do. */
    case STATE_ACTIVE:
        vscp_core_stateActive();
        break;

    /* Node goes offline */
    case STATE_IDLE:
        vscp_core_stateIdle();
        break;

    /* Node waits for reset */
    case STATE_RESET:
        vscp_core_stateReset();
        break;

    /* A error happened. */
    case STATE_ERROR:
        vscp_core_stateError();
        break;

    /* Unknown state */
    default:
        /* This should never happen. */
        vscp_core_changeToStateError();
        break;
    }

    /* Invalidate received message */
    vscp_core_rxMessageValid = FALSE;

    return isEventHandled;
}

/**
 * This function reads the nickname id of the node.
 *
 * @return  Nickname id
 */
extern uint8_t  vscp_core_readNicknameId(void)
{
    return vscp_core_nickname;
}

/**
 * This function starts the node segment initialization.
 */
extern void vscp_core_startNodeSegmentInit(void)
{
    /* If the node is already in init state, nothing to do.
     * Otherwise prepare for nickname discovery,
     * see VSCP specification, chapter VSCP Level I Specifics,
     * Node segment initialization. Dynamic nodes, Step 1
     */
    if (STATE_INIT != vscp_core_state)
    {
        /* Change to init state */
        vscp_core_changeToStateInit(TRUE);
    }

    return;
}

/**
 * This function set one or more alarm status.
 * How the bits are read, is application specific.
 * Note that a active alarm (bit is set) can only be cleared by reading the
 * alarm register. Calling this function with 0, does nothing.
 *
 * @param[in]   value   New alarm status
 */
extern void vscp_core_setAlarm(uint8_t value)
{
    vscp_core_regAlarmStatus |= value;

    return;
}

/**
 * This function determines the state of VSCP and if it is in active state,
 * it will return TRUE, otherwise FALSE.
 *
 * @return  Is VSCP active or not?
 * @retval  FALSE   Not in active state
 * @retval  TRUE    In active state
 */
extern BOOL vscp_core_isActive(void)
{
    return (STATE_ACTIVE == vscp_core_state) ? TRUE : FALSE;
}

/**
 * Get the time since epoch 00:00:00 UTC, January 1, 1970.
 * The time itself is received by the segment master.
 *
 * @return Unix timestamp
 */
extern uint32_t vscp_core_getTimeSinceEpoch(void)
{
    return vscp_core_timeSinceEpoch;
}

/**
 * Set the time since epoch 00:00:00 UTC, January 1, 1970.
 * Note, if a segment master is present, it will overwrite the time with its
 * heartbeat message.
 *
 * @param[in] timestamp Unix timestamp
 */
extern void vscp_core_setTimeSinceEpoch(uint32_t timestamp)
{
    vscp_core_timeSinceEpoch = timestamp;
    return;
}

/**
 * Prepares a transmit message, before it is used.
 *
 * Default values:
 * - Nodes nickname
 * - Hard coded node flag
 * - No data
 *
 * After preparation, only the data and the number of data bytes has to be
 * modified additionally.
 *
 * @param[in,out]   txMessage   Transmit message which will be prepared.
 * @param[in]       vscpClass   Transmit message VSCP class
 * @param[in]       vscpType    Transmit message VSCP type
 * @param[in]       priority    Transmit message priority
 */
extern void vscp_core_prepareTxMessage(vscp_TxMessage * const txMessage, uint16_t vscpClass, uint8_t vscpType, VSCP_PRIORITY priority)
{
    if (NULL != txMessage)
    {
        txMessage->vscpClass    = vscpClass;
        txMessage->vscpType     = vscpType;
        txMessage->priority     = priority;
        txMessage->oAddr        = vscp_core_nickname;
        txMessage->hardCoded    = VSCP_CORE_HARD_CODED;
        txMessage->dataNum      = 0;
    }

    return;
}

/**
 * Send a event to the communication bus. Don't forget to prepare your transmit
 * message (@see vscp_core_prepareTxMessage) first and then modify for your needs,
 * before sending it!
 *
 * @param[in]   txMessage   The event which will be sent.
 * @return Status
 * @retval FALSE    Failed to send the event.
 * @retval TRUE     Event successful sent.
 */
extern BOOL vscp_core_sendEvent(vscp_TxMessage const * const txMessage)
{
    return vscp_transport_writeMessage(txMessage);
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE )

/**
 * Enable or disable the node heartbeat.
 *
 * @param[in] enableIt  Enable/Disable node hearbeat
 */
extern void vscp_core_enableHeartbeat(BOOL enableIt)
{
    if (FALSE == vscp_core_isHeartbeatEnabled)
    {
        vscp_core_isHeartbeatEnabled = TRUE;
    }
    else
    {
        vscp_core_isHeartbeatEnabled = FALSE;
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

/**
 * This function writes the nickname id of the node.
 *
 * @param[in]   nickname    Nickname id
 */
static void vscp_core_writeNicknameId(uint8_t nickname)
{
    /* Write it to persistent memory */
    vscp_ps_writeNicknameId(nickname);

    /* Read it back from persistent memory. This is done to be sure to provide
     * really the one, which is stored.
     */
    vscp_core_nickname = vscp_ps_readNicknameId();

    return;
}

/**
 * This function checks the persistent memory.
 * If the persistent memory is not initialized, it will return FALSE.
 * The check is done by checking the node control flags,
 * especially the start up control. Because the start up control bits can
 * be only 01b or 10b.
 *
 * @return  Status of persistent memory
 * @retval  FALSE   Persistent memory is not initialized
 * @retval  TRUE    Persistent memory is initialized
 */
static BOOL vscp_core_checkPersistentMemory(void)
{
    BOOL    status          = TRUE;
    uint8_t startUpControl  = vscp_core_getStartUpControl();

    if ((0x01 != startUpControl) &&
        (0x02 != startUpControl))
    {
        status = FALSE;
    }

    return status;
}

/**
 * Handles the startup state:
 * - Nickname shall be checked.
 */
static inline void  vscp_core_stateStartup(void)
{
    /* Is nickname assigned?
     * If no nickname is assigned, the node will be set to initialization
     * state. Otherwise to active state.
     */
    if (VSCP_NICKNAME_NOT_INIT == vscp_core_nickname)
    {
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_SILENT_NODE )

        /* Valid message? */
        if (TRUE == vscp_core_rxMessageValid)
        {
            /* Be silent as long as someone request the initialization with a
               CLASS1.PROTOCOL GUID drop nickname-ID / reset event.
             */
            if ((VSCP_CLASS_L1_PROTOCOL == vscp_core_rxMessage.vscpClass) &&
                (VSCP_TYPE_PROTOCOL_RESET_DEVICE == vscp_core_rxMessage.vscpType))
            {
                vscp_core_handleProtocolGuidDropNickname();
            }
        }

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_SILENT_NODE ) */

        /* Check the start-up control.
         * 01b   : Start initialization immediately
         * others: Wait for initialization, until it is explicit triggered.
         */
        if (0x01 == vscp_core_getStartUpControl())
        {
            vscp_core_changeToStateInit(TRUE);
        }
        else
        {
            /* Wait until the user press the segment initialization button */
            ;
        }

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_SILENT_NODE ) */
    }
    else
    {
        vscp_core_changeToStateActive();
    }

    return;
}

/**
 * Change to init state.
 * - Drop nickname id.
 *
 * @param[in] probeSegmentMaster    Probe for segment master (true) or start own nickname discovery (false).
 */
static inline void  vscp_core_changeToStateInit(BOOL probeSegmentMaster)
{
    if (STATE_INIT != vscp_core_state)
    {
        /* Show the user that the node enters initialization state by blinking lamp. */
        vscp_portable_setLampState(VSCP_LAMP_STATE_BLINK_FAST);

        vscp_core_state = STATE_INIT;

        if (FALSE == probeSegmentMaster)
        {
            vscp_core_initState = INIT_STATE_PROBE;
            vscp_core_nickname_probe = VSCP_CONFIG_START_NODE_PROBE_NICKNAME;
        }
        else
        {
            vscp_core_initState = INIT_STATE_PROBE_MASTER;
            vscp_core_nickname_probe = VSCP_NICKNAME_SEGMENT_MASTER;
        }

        /* Clear nickname id */
        vscp_core_writeNicknameId(VSCP_NICKNAME_NOT_INIT);
    }

    return;
}

/**
 * Handles the init state:
 * - Node segment initialization of dynamic nodes, see VSCP specification,
 *   chapter VSCP Level I Specifics, Node segment initialization. Dynamic nodes
 * - Nickname id discovery process
 */
static inline void  vscp_core_stateInit(void)
{
    vscp_TxMessage  txMessage;

    /* Process sub state machine */
    switch(vscp_core_initState)
    {
    case INIT_STATE_PROBE_MASTER:

        /* The node sends a probe event (CLASS1.PROTOCOL, TYPE=2) to address 0
         * (the address reserved for the master of a segment) using 0xFF as its own
         * address. The priority of this event is set to 0x07.
         */
        txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
        txMessage.vscpType  = VSCP_TYPE_PROTOCOL_NEW_NODE_ONLINE;
        txMessage.priority  = VSCP_PRIORITY_7_LOW;
        txMessage.oAddr     = vscp_core_nickname;
        txMessage.hardCoded = VSCP_CORE_HARD_CODED;
        txMessage.dataNum   = 1;
        txMessage.data[0]   = VSCP_NICKNAME_SEGMENT_MASTER;

        if (FALSE == vscp_transport_writeMessage(&txMessage))
        {
            /* Error, try again next time. */
            ;
        }
        else
        {
            vscp_core_initState = INIT_STATE_PROBE_MASTER_WAIT;

            /* Start timer to observe the node segment initialization */
            vscp_timer_start(vscp_core_timerId, VSCP_CONFIG_NODE_SEGMENT_INIT_TIMEOUT);
        }

        break;

    case INIT_STATE_PROBE_MASTER_WAIT:

        /* Timeout, because no segment master available? */
        if (FALSE == vscp_timer_getStatus(vscp_core_timerId))
        {
            /* Start nickname id discovery process */
            vscp_core_initState = INIT_STATE_PROBE;

            /* Probe shall start with nickname id 1. */
            vscp_core_nickname_probe = VSCP_CONFIG_START_NODE_PROBE_NICKNAME;
        }
        /* Valid message received */
        else if (TRUE == vscp_core_rxMessageValid)
        {
            if (VSCP_CLASS_L1_PROTOCOL == vscp_core_rxMessage.vscpClass)
            {
                /* Probe event acknowledge? */
                if (VSCP_TYPE_PROTOCOL_PROBE_ACK == vscp_core_rxMessage.vscpType)
                {
                    /* Acknowledge from the segment master? */
                    if (VSCP_NICKNAME_SEGMENT_MASTER == vscp_core_rxMessage.oAddr)
                    {
                        /* Wait for nickname id assignment and don't stop the timer,
                         * because the next state is still part of it.
                         */
                        vscp_core_changeToStatePreActive();
                    }
                    else
                    {
                        /* Don't care about. */
                        ;
                    }
                }
            }
        }

        break;

    case INIT_STATE_PROBE:

        /* If no nickname assignment occurs the node checks the other possible
         * nicknames (1-254) in turn.
         */
        txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
        txMessage.vscpType  = VSCP_TYPE_PROTOCOL_NEW_NODE_ONLINE;
        txMessage.priority  = VSCP_PRIORITY_7_LOW;
        txMessage.oAddr     = vscp_core_nickname;
        txMessage.hardCoded = VSCP_CORE_HARD_CODED;
        txMessage.dataNum   = 1;
        txMessage.data[0]   = vscp_core_nickname_probe;

        if (FALSE == vscp_transport_writeMessage(&txMessage))
        {
            /* Error, try again next time. */
            ;
        }
        /* Abort now, because the segment is full (of nodes)? */
        else if (VSCP_NICKNAME_NOT_INIT == vscp_core_nickname_probe)
        {
            /* Stop timer */
            vscp_timer_stop(vscp_core_timerId);

            /* Go offline, because segment is full. */
            vscp_core_changeToStateIdle();
        }
        else
        {
            vscp_core_initState = INIT_STATE_PROBE_WAIT;

            /* Start timer to avoid that we wait infinite for the probe acknowledge. */
            vscp_timer_start(vscp_core_timerId, VSCP_CONFIG_PROBE_ACK_TIMEOUT);
        }

        break;

    case INIT_STATE_PROBE_WAIT:

        /* Timeout, because no other node uses the nickname id? */
        if (FALSE == vscp_timer_getStatus(vscp_core_timerId))
        {
            /* Available nickname id found. */
            vscp_core_writeNicknameId(vscp_core_nickname_probe);

            vscp_core_changeToStateActive();
        }
        /* Valid message received */
        else if (TRUE == vscp_core_rxMessageValid)
        {
            if (VSCP_CLASS_L1_PROTOCOL == vscp_core_rxMessage.vscpClass)
            {
                /* Probe event acknowledge? */
                if (VSCP_TYPE_PROTOCOL_PROBE_ACK == vscp_core_rxMessage.vscpType)
                {
                    /* Acknowledge from a node, which has the probed nickname id? */
                    if (vscp_core_nickname_probe == vscp_core_rxMessage.oAddr)
                    {
                        /* Stop timer */
                        vscp_timer_stop(vscp_core_timerId);

                        /* Try next nickname id.
                         * Note that sending a nickname of VSCP_NICKNAME_NOT_INIT,
                         * notifies the segment nodes that this node gave up.
                         * See VSCP specification, chapter Level I Events,
                         * CLASS1.PROTOCOL, Type=2 (0x02) New node on line / Probe
                         */
                        ++vscp_core_nickname_probe;

                        vscp_core_initState = INIT_STATE_PROBE;
                    }
                    else
                    {
                        /* Don't care about. */
                        ;
                    }
                }
            }
        }

        break;

    /* Unknown state */
    default:
        /* This should never happen. */
        vscp_core_changeToStateError();
        break;
    }

    return;
}

/**
 * Change to pre-active state.
 */
static inline void  vscp_core_changeToStatePreActive(void)
{
    vscp_core_state = STATE_PREACTIVE;

    return;
}

/**
 * Handles the pre-active state.
 * Waiting for the nickname assignment by the segment master.
 */
static inline void  vscp_core_statePreActive(void)
{
    /* Timeout? Note, the timer was started in init state. */
    if (FALSE == vscp_timer_getStatus(vscp_core_timerId))
    {
        /* No nickname id received, start own nickname discovery. */
        vscp_core_changeToStateInit(FALSE);
    }
    /* Valid message received */
    else if (TRUE == vscp_core_rxMessageValid)
    {
        if (VSCP_CLASS_L1_PROTOCOL == vscp_core_rxMessage.vscpClass)
        {
            /* Nickname id from the segment master? */
            if ((VSCP_TYPE_PROTOCOL_SET_NICKNAME == vscp_core_rxMessage.vscpType) &&
                (VSCP_NICKNAME_SEGMENT_MASTER == vscp_core_rxMessage.oAddr) &&
                (VSCP_NICKNAME_NOT_INIT == vscp_core_rxMessage.data[0]))
            {
                vscp_TxMessage  txMessage;

                /* Stop timer */
                vscp_timer_stop(vscp_core_timerId);

                /* Set nickname, respond to segment master and go active */
                vscp_core_writeNicknameId(vscp_core_rxMessage.data[1]);

                txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
                txMessage.vscpType  = VSCP_TYPE_PROTOCOL_NICKNAME_ACCEPTED;
                txMessage.priority  = VSCP_PRIORITY_7_LOW;
                txMessage.oAddr     = vscp_core_nickname;
                txMessage.hardCoded = VSCP_CORE_HARD_CODED;
                txMessage.dataNum   = 0;

                (void)vscp_transport_writeMessage(&txMessage);

                vscp_core_changeToStateActive();
            }
            /* Any other message */
            else
            {
                /* Don't care about it. */
                ;
            }
        }
    }

    return;
}

/**
 * Change to active state.
 * - If configured, show the user via lamp that the node changes to active state.
 * - Notify every node on the communication bus that a new node is online.
 * - If configured, start sending a heartbeat.
 */
static inline void  vscp_core_changeToStateActive(void)
{
    if (STATE_ACTIVE != vscp_core_state)
    {
        vscp_TxMessage  txMessage;

        /* Show the user that the node enters active state by enable the lamp. */
        vscp_portable_setLampState(VSCP_LAMP_STATE_ON);

        vscp_core_state = STATE_ACTIVE;

        txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
        txMessage.vscpType  = VSCP_TYPE_PROTOCOL_NEW_NODE_ONLINE;
        txMessage.priority  = VSCP_PRIORITY_0_HIGH;
        txMessage.oAddr     = vscp_core_nickname;
        txMessage.hardCoded = VSCP_CORE_HARD_CODED;
        txMessage.dataNum   = 1;
        txMessage.data[0]   = vscp_core_nickname;

        (void)vscp_transport_writeMessage(&txMessage);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE )

        if (FALSE != vscp_core_isHeartbeatEnabled)
        {
            /* Start timer for node heartbeat */
            vscp_timer_start(vscp_core_heartbeatTimerId, VSCP_CONFIG_HEARTBEAT_NODE_PERIOD);
        }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

    }

    return;
}

/**
 * Handles the active state.
 */
static inline void  vscp_core_stateActive(void)
{
    /* Valid message? */
    if (TRUE == vscp_core_rxMessageValid)
    {
        /* Handle all protocol class specific events. This is mandatory for L1 and L2 nodes. */
        if (VSCP_CLASS_L1_PROTOCOL == vscp_core_rxMessage.vscpClass)
        {
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION )

            /* Notify application about event.
             * If application handles event, the core will not handle it.
             */
            if (FALSE == vscp_portable_provideProtocolEvent(&vscp_core_rxMessage))
            {
                vscp_core_handleProtocolClassType();
            }

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION ) */

            vscp_core_handleProtocolClassType();

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_PROTOCOL_EVENT_NOTIFICATION ) */
        }
        else
        /* Notify application */
        {
            vscp_portable_provideEvent(&vscp_core_rxMessage);
        }

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

        /* Execute actions of the decision matrix (standard + extension) */
        vscp_dm_executeActions(&vscp_core_rxMessage);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

        /* Execute actions of the decision matrix next generation */
        vscp_dm_ng_executeActions(&vscp_core_rxMessage);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */
    }

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE )

    /* Send periodically the node heartbeat.
     * Note that sending the node heartbeat shall not be synchronized to the segment heartbeat!
     */
    if ((FALSE != vscp_core_isHeartbeatEnabled) &&
        (FALSE == vscp_timer_getStatus(vscp_core_heartbeatTimerId)))
    {
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_CUSTOM_HEARTBEAT )
        (void)vscp_portable_sendNodeHeartbeatEvent();
#else
        (void)vscp_evt_information_sendNodeHeartbeat(0, vscp_dev_data_getNodeZone(), vscp_dev_data_getNodeSubZone(), NULL, 0);
#endif

        /* Restart timer */
        vscp_timer_start(vscp_core_heartbeatTimerId, VSCP_CONFIG_HEARTBEAT_NODE_PERIOD);
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_NODE ) */

    /* Continue a extended page read? */
    if (0 < vscp_core_extPageReadData.count)
    {
        vscp_core_extendedPageReadRegister(&vscp_core_extPageReadData);
    }

    return;
}

/**
 * Change to idle state.
 */
static inline void  vscp_core_changeToStateIdle(void)
{
    if (STATE_IDLE != vscp_core_state)
    {
        /* Disable lamp and show the user that the node is offline. */
        vscp_portable_setLampState(VSCP_LAMP_STATE_OFF);

        vscp_core_state = STATE_IDLE;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_IDLE_CALLOUT )

        /* Notify the application. */
        vscp_portable_idleStateEntered();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_IDLE_CALLOUT ) */

    }

    return;
}

/**
 * Handles the idle state.
 */
static inline void  vscp_core_stateIdle(void)
{
    /* Do nothing! */
    return;
}

/**
 * Change to reset state.
 *
 * @param[in]   timeout Time in seconds to wait until reset is requested.
 */
static inline void  vscp_core_changeToStateReset(uint8_t timeout)
{
    if (STATE_RESET != vscp_core_state)
    {
        /* Disable lamp and show the user that the node is offline. */
        vscp_portable_setLampState(VSCP_LAMP_STATE_OFF);

        vscp_core_state = STATE_RESET;

        vscp_core_secCnt = timeout;

        /* Is a timer needed? */
        if (0 < vscp_core_secCnt)
        {
            /* Start timer for a second */
            vscp_timer_start(vscp_core_timerId, (uint16_t)1000);
        }
        else
        {
            /* No timer needed */
            vscp_timer_stop(vscp_core_timerId);
        }
    }

    return;
}

/**
 * Handles the reset state.
 */
static inline void  vscp_core_stateReset(void)
{
    if (FALSE == vscp_core_resetRequested)
    {
        /* Timeout? */
        if (FALSE == vscp_timer_getStatus(vscp_core_timerId))
        {
            /* Decrease number of seconds, before reset */
            if (0 < vscp_core_secCnt)
            {
                --vscp_core_secCnt;
            }

            /* Reset now? */
            if (0 == vscp_core_secCnt)
            {
                /* Request reset */
                vscp_portable_resetRequest();

                vscp_core_resetRequested = TRUE;
            }
            else
            {
                /* Restart timer for a second */
                vscp_timer_start(vscp_core_timerId, (uint16_t)1000);
            }
        }
    }

    return;
}

/**
 * Change to error state.
 */
static inline void  vscp_core_changeToStateError(void)
{
    if (STATE_ERROR != vscp_core_state)
    {
        /* Disable lamp and show the user that the node is offline. */
        vscp_portable_setLampState(VSCP_LAMP_STATE_OFF);

        vscp_core_state = STATE_ERROR;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ERROR_CALLOUT )

        /* Notify the application. */
        vscp_portable_errorStateEntered();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ERROR_CALLOUT ) */

    }

    return;
}

/**
 * Handles the error state.
 */
static inline void  vscp_core_stateError(void)
{
    /* Do nothing! */
    return;
}

/**
 * Handles the protocol class and its types.
 *
 * Precondition:  A valid message shall be in the receive buffer.
 */
static inline void  vscp_core_handleProtocolClassType(void)
{
    switch(vscp_core_rxMessage.vscpType)
    {
    /* VSCP specification, chapter Segment Controller Heartbeat. */
    case VSCP_TYPE_PROTOCOL_SEGCTRL_HEARTBEAT:
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT )
        vscp_core_handleProtocolHeartbeat();
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT ) */
        break;

    /* VSCP specification, chapter New node on line / Probe. */
    case VSCP_TYPE_PROTOCOL_NEW_NODE_ONLINE:
        vscp_core_handleProtocolNewNodeOnline();
        break;

    /* VSCP specification, chapter Probe ACK. */
    case VSCP_TYPE_PROTOCOL_PROBE_ACK:
        vscp_core_handleProtocolProbeAck();
        break;

    /* VSCP specification, chapter Set nickname-ID for node. */
    case VSCP_TYPE_PROTOCOL_SET_NICKNAME:
        vscp_core_handleProtocolSetNicknameId();
        break;

    /* VSCP specification, chapter nickname-ID accepted. */
    case VSCP_TYPE_PROTOCOL_NICKNAME_ACCEPTED:
        /* This event is interesting for node management, but not for a node itself. */
        break;

    /* VSCP specification, chapter Drop nickname-ID / Reset Device. */
    case VSCP_TYPE_PROTOCOL_DROP_NICKNAME:
        vscp_core_handleProtocolDropNicknameId();
        break;

    /* VSCP specification, chapter Read register. */
    case VSCP_TYPE_PROTOCOL_READ_REGISTER:
        vscp_core_handleProtocolReadRegister();
        break;

    /* VSCP specification, chapter Read/Write response. */
    case VSCP_TYPE_PROTOCOL_RW_RESPONSE:
        /* This event is interesting for node configuration, but not for a node itself. */
        break;

    /* VSCP specification, chapter Write register. */
    case VSCP_TYPE_PROTOCOL_WRITE_REGISTER:
        vscp_core_handleProtocolWriteRegister();
        break;

    /* VSCP specification, chapter Enter boot loader mode. */
    case VSCP_TYPE_PROTOCOL_ENTER_BOOT_LOADER:
        vscp_core_handleProtocolEnterBootLoaderMode();
        break;

    /* VSCP specification, chapter ACK boot loader mode. */
    case VSCP_TYPE_PROTOCOL_ACK_BOOT_LOADER:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter NACK boot loader mode. */
    case VSCP_TYPE_PROTOCOL_NACK_BOOT_LOADER:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter Start block data transfer. */
    case VSCP_TYPE_PROTOCOL_START_BLOCK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter Block data. */
    case VSCP_TYPE_PROTOCOL_BLOCK_DATA:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter ACK data block. */
    case VSCP_TYPE_PROTOCOL_BLOCK_DATA_ACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter NACK data block. */
    case VSCP_TYPE_PROTOCOL_BLOCK_DATA_NACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter Program data block */
    case VSCP_TYPE_PROTOCOL_PROGRAM_BLOCK_DATA:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter ACK program data block */
    case VSCP_TYPE_PROTOCOL_PROGRAM_BLOCK_DATA_ACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter NACK program data block */
    case VSCP_TYPE_PROTOCOL_PROGRAM_BLOCK_DATA_NACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter Activate new image */
    case VSCP_TYPE_PROTOCOL_ACTIVATE_NEW_IMAGE:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter GUID drop nickname-ID / reset device. */
    case VSCP_TYPE_PROTOCOL_RESET_DEVICE:
        vscp_core_handleProtocolGuidDropNickname();
        break;

    /* VSCP specification, chapter Page read. */
    case VSCP_TYPE_PROTOCOL_PAGE_READ:
        vscp_core_handleProtocolPageRead();
        break;

    /* VSCP specification, chapter Page write. */
    case VSCP_TYPE_PROTOCOL_PAGE_WRITE:
        vscp_core_handleProtocolPageWrite();
        break;

    /* VSCP specification, chapter Read/Write page response. */
    case VSCP_TYPE_PROTOCOL_RW_PAGE_RESPONSE:
        /* This event is interesting for node configuration, but not for a node itself. */
        break;

    /* VSCP specification, chapter High end server probe. */
    case VSCP_TYPE_PROTOCOL_HIGH_END_SERVER_PROBE:
        /* Not mandatory, not supported */
        break;

    /* VSCP specification, chapter High end server response. */
    case VSCP_TYPE_PROTOCOL_HIGH_END_SERVER_RESPONSE:
        /* Not mandatory, not supported */
        break;

    /* VSCP specification, chapter Increment register. */
    case VSCP_TYPE_PROTOCOL_INCREMENT_REGISTER:
        vscp_core_handleProtocolIncrementRegister();
        break;

    /* VSCP specification, chapter Decrement register. */
    case VSCP_TYPE_PROTOCOL_DECREMENT_REGISTER:
        vscp_core_handleProtocolDecrementRegister();
        break;

    /* VSCP specification, chapter Who is there? */
    case VSCP_TYPE_PROTOCOL_WHO_IS_THERE:
        vscp_core_handleProtocolWhoIsThere();
        break;

    /* VSCP specification, chapter Who is there response. */
    case VSCP_TYPE_PROTOCOL_WHO_IS_THERE_RESPONSE:
        /* This event is interesting for node management, but not for a node itself. */
        break;

    /* VSCP specification, chapter Get decision matrix info. */
    case VSCP_TYPE_PROTOCOL_GET_MATRIX_INFO:
        vscp_core_handleProtocolGetDecisionMatrixInfo();
        break;

    /* VSCP specification, chapter Get decision matrix info. */
    case VSCP_TYPE_PROTOCOL_GET_MATRIX_INFO_RESPONSE:
        /* This event is interesting for node management, but not for a node itself. */
        break;

    /* VSCP specification, chapter Get embedded MDF. */
    case VSCP_TYPE_PROTOCOL_GET_EMBEDDED_MDF:
        /* Optional and not supported yet. */
        break;

    /* VSCP specification, chapter Get embedded MDF response. */
    case VSCP_TYPE_PROTOCOL_GET_EMBEDDED_MDF_RESPONSE:
        /* Optional and not supported yet. */
        break;

    /* VSCP specification, chapter Extended page read register. */
    case VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_READ:
        vscp_core_handleProtocolExtendedPageReadRegister();
        break;

    /* VSCP specification, chapter Extended page write register. */
    case VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_WRITE:
        vscp_core_handleProtocolExtendedPageWriteRegister();
        break;

    /* VSCP specification, chapter Extended page read write response. */
    case VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_RESPONSE:
        /* This event is interesting for node management, but not for a node itself. */
        break;

    /* VSCP specification, chapter Get event interest. */
    case VSCP_TYPE_PROTOCOL_GET_EVENT_INTEREST:
        /* Optional and not supported yet. */
        break;

    /* VSCP specification, chapter Get event interest response. */
    case VSCP_TYPE_PROTOCOL_GET_EVENT_INTEREST_RESPONSE:
        /* Optional and not supported yet. */
        break;

    /* VSCP specification, chapter Activate new image ACK. */
    case VSCP_TYPE_PROTOCOL_ACTIVATE_NEW_IMAGE_ACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter Activate new image NACK. */
    case VSCP_TYPE_PROTOCOL_ACTIVATE_NEW_IMAGE_NACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter Start block data transfer ACK. */
    case VSCP_TYPE_PROTOCOL_START_BLOCK_ACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* VSCP specification, chapter Start block data transfer NACK. */
    case VSCP_TYPE_PROTOCOL_START_BLOCK_NACK:
        /* Boot loader specific event. Not supported. */
        break;

    /* Not handled type */
    default:
        break;
    }

    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT )

/**
 * Handle segment controller heartbeat.
 */
static inline void  vscp_core_handleProtocolHeartbeat(void)
{
    /* Check number of parameters. */
    if (0 < vscp_core_rxMessage.dataNum)
    {
        /* If the received segment controller CRC is different than the stored one,
         * it seems the node was moved to a new segment.
         */
        if (vscp_ps_readSegmentControllerCRC() != vscp_core_rxMessage.data[0])
        {
            /* Store CRC of the this segment */
            vscp_ps_writeSegmentControllerCRC(vscp_core_rxMessage.data[0]);

            /* If a nickname discovery was processed just before, there is no
             * need to do it again.
             */
            if (VSCP_NICKNAME_SEGMENT_MASTER != vscp_core_nickname_probe)
            {
                vscp_core_changeToStateInit(TRUE);
            }
        }

        /* If available, store time since epoch 00:00:00 UTC, January 1, 1970 */
        if (5 <= vscp_core_rxMessage.dataNum)
        {
            vscp_core_timeSinceEpoch  = ((uint32_t)vscp_core_rxMessage.data[1]) << 24;
            vscp_core_timeSinceEpoch |= ((uint32_t)vscp_core_rxMessage.data[2]) << 16;
            vscp_core_timeSinceEpoch |= ((uint32_t)vscp_core_rxMessage.data[3]) <<  8;
            vscp_core_timeSinceEpoch |= ((uint32_t)vscp_core_rxMessage.data[4]) <<  0;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT )

            /* Notify application about a new received timestamp. */
            vscp_portable_updateTimeSinceEpoch(vscp_core_timeSinceEpoch);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_SEGMENT_TIME_CALLOUT ) */
        }
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_HEARTBEAT_SUPPORT_SEGMENT ) */

/**
 * Handles a protocol class new node online / probe event.
 */
static inline void  vscp_core_handleProtocolNewNodeOnline(void)
{
    /* Check number of parameters. */
    if (1 == vscp_core_rxMessage.dataNum)
    {
        /* Does this belongs to a node with the same nickname id? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            vscp_TxMessage  txMessage;

            /* Answer that the nickname id is already in use. */
            txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
            txMessage.vscpType  = VSCP_TYPE_PROTOCOL_PROBE_ACK;
            txMessage.priority  = VSCP_PRIORITY_0_HIGH;
            txMessage.oAddr     = vscp_core_nickname;
            txMessage.hardCoded = VSCP_CORE_HARD_CODED;
            txMessage.dataNum   = 0;

            (void)vscp_transport_writeMessage(&txMessage);
        }
    }

    return;
}

/**
 * Handles a protocol class probe acknowledge.
 */
static inline void  vscp_core_handleProtocolProbeAck(void)
{
    /* Check number of parameters. */
    if (0 == vscp_core_rxMessage.dataNum)
    {
        /* Response from a node with the same nickname id? */
        if (vscp_core_nickname == vscp_core_rxMessage.oAddr)
        {
            /* Oups ... */
            vscp_core_changeToStateInit(TRUE);
        }
    }

    return;
}

/**
 * Handles a protocol class set nickname id event.
 */
static inline void  vscp_core_handleProtocolSetNicknameId(void)
{
    /* Check number of parameters. */
    if (2 == vscp_core_rxMessage.dataNum)
    {
        /* Change the node nickname id? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            /* But not all nickname ids are allowed. */
            if (VSCP_NICKNAME_SEGMENT_MASTER != vscp_core_rxMessage.data[1])
            {
                vscp_TxMessage  txMessage;

                vscp_core_writeNicknameId(vscp_core_rxMessage.data[1]);

                /* Answer that the nickname id is already in use. */
                txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
                txMessage.vscpType  = VSCP_TYPE_PROTOCOL_NICKNAME_ACCEPTED;
                txMessage.priority  = VSCP_PRIORITY_7_LOW;
                txMessage.oAddr     = vscp_core_nickname;
                txMessage.hardCoded = VSCP_CORE_HARD_CODED;
                txMessage.dataNum   = 0;

                (void)vscp_transport_writeMessage(&txMessage);
            }
        }
    }

    return;
}

/**
 * Handles a protocol class drop nickname id event.
 */
static inline void  vscp_core_handleProtocolDropNicknameId(void)
{
    /* Check number of parameters. */
    if (0 < vscp_core_rxMessage.dataNum)
    {
        /* Drop the node nickname id? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            /* Drop nickname and restart? */
            if (1 == vscp_core_rxMessage.dataNum)
            {
                vscp_core_writeNicknameId(VSCP_NICKNAME_NOT_INIT);
                vscp_core_changeToStateReset(0);
            }
            /* Additional flags received? */
            else if ((2 == vscp_core_rxMessage.dataNum) ||
                     (3 == vscp_core_rxMessage.dataNum))
            {
                uint8_t waitTime    = 0;

                /* Wait time received? */
                if (3 == vscp_core_rxMessage.dataNum)
                {
                    waitTime = vscp_core_rxMessage.data[2];
                }

                /* Byte 1:
                 * Bit 5 - Reset device. Keep nickname.
                 * Bit 6 - Set persistent storage to default.
                 * Bit 7 - Go idle. Do not start up again.
                 */

                /* Set persistent memory to default (bit 6)? */
                if (0 != (vscp_core_rxMessage.data[1] & (1 << 6)))
                {
                    /* Backup nickname, because restore factory settings will clear it. */
                    uint8_t nicknameBackup  = vscp_core_nickname;

                    /* Set defaults to persistent memory. */
                    vscp_core_restoreFactoryDefaultSettings();

                    /* Restore nickname? */
                    if (0 != (vscp_core_rxMessage.data[1] & (1 << 5)))
                    {
                        /* Restore nickname */
                        vscp_core_writeNicknameId(nicknameBackup);
                    }
                }

                /* Reset device (bit 5)?
                 * Note that "reset device" has a higher priority than "go idle".
                 * There is no exact description in the specification yet.
                 */
                if (0 != (vscp_core_rxMessage.data[1] & (1 << 5)))
                {
                    vscp_core_changeToStateReset(waitTime);
                }
                /* Change to idle state (bit 7)? */
                else if (0 != (vscp_core_rxMessage.data[1] & (1 << 7)))
                {
                    vscp_core_writeNicknameId(VSCP_NICKNAME_NOT_INIT);
                    vscp_core_changeToStateIdle();
                }
                else
                {
                    vscp_core_writeNicknameId(VSCP_NICKNAME_NOT_INIT);
                    vscp_core_changeToStateReset(waitTime);
                }
            }
        }
    }

    return;
}

/**
 * Handles a protocol class read register event.
 */
static inline void  vscp_core_handleProtocolReadRegister(void)
{
    /* Check number of parameters. */
    if (2 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            uint8_t addr    = vscp_core_rxMessage.data[1];
            uint8_t value   = vscp_core_readRegister(0, addr);

            /* Response to read register event */
            vscp_core_sendRegisterReadWriteRsp(addr, value);
        }
    }

    return;
}

/**
 * Send a register read/write response.
 *
 * @param[in]   addr    Register address
 * @param[in]   value   Register value
 */
static void vscp_core_sendRegisterReadWriteRsp(uint8_t addr, uint8_t value)
{
    vscp_TxMessage  txMessage;

    txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
    txMessage.vscpType  = VSCP_TYPE_PROTOCOL_RW_RESPONSE;
    txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
    txMessage.oAddr     = vscp_core_nickname;
    txMessage.hardCoded = VSCP_CORE_HARD_CODED;
    txMessage.dataNum   = 2;
    txMessage.data[0]   = addr;
    txMessage.data[1]   = value;

    (void)vscp_transport_writeMessage(&txMessage);

    return;
}

/**
 * Read register and return its value.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Register value
 */
static uint8_t  vscp_core_readRegister(uint16_t page, uint8_t addr)
{
    uint8_t ret = 0;

    /* Page 0 includes the VSCP specific registers. */
    if ((0 == page) &&
        (VSCP_REGISTER_VSCP_START_ADDR <= addr) &&
        (VSCP_REGISTER_VSCP_END_ADDR >= addr))
    {
        switch(addr)
        {
            case VSCP_REG_ALARM_STATUS:
                ret = vscp_core_regAlarmStatus;

                /* Reset alarm */
                vscp_core_regAlarmStatus = 0;
                break;

            case VSCP_REG_VSCP_VERSION_MAJOR:
                ret = VSCP_CORE_VERSION_MAJOR;
                break;

            case VSCP_REG_VSCP_VERSION_MINOR:
                ret = VSCP_CORE_VERSION_MINOR;
                break;

            case VSCP_REG_NODE_CONTROL_FLAGS:
                ret = vscp_ps_readNodeControlFlags();
                break;

            case VSCP_REG_USER_ID_0:
                /*@fallthrough@*/
            case VSCP_REG_USER_ID_1:
                /*@fallthrough@*/
            case VSCP_REG_USER_ID_2:
                /*@fallthrough@*/
            case VSCP_REG_USER_ID_3:
                /*@fallthrough@*/
            case VSCP_REG_USER_ID_4:
                ret = vscp_ps_readUserId(addr - VSCP_REG_USER_ID_0);
                break;

            case VSCP_REG_MANUFACTURER_DEV_ID_0:
                /*@fallthrough@*/
            case VSCP_REG_MANUFACTURER_DEV_ID_1:
                /*@fallthrough@*/
            case VSCP_REG_MANUFACTURER_DEV_ID_2:
                /*@fallthrough@*/
            case VSCP_REG_MANUFACTURER_DEV_ID_3:
                ret = vscp_dev_data_getManufacturerDevId(addr - VSCP_REG_MANUFACTURER_DEV_ID_0);
                break;

            case VSCP_REG_MANUFACTURER_SUB_DEV_ID_0:
                /*@fallthrough@*/
            case VSCP_REG_MANUFACTURER_SUB_DEV_ID_1:
                /*@fallthrough@*/
            case VSCP_REG_MANUFACTURER_SUB_DEV_ID_2:
                /*@fallthrough@*/
            case VSCP_REG_MANUFACTURER_SUB_DEV_ID_3:
                ret = vscp_dev_data_getManufacturerSubDevId(addr - VSCP_REG_MANUFACTURER_SUB_DEV_ID_0);
                break;

            case VSCP_REG_NICKNAME_ID:
                ret = vscp_core_nickname;
                break;

            case VSCP_REG_PAGE_SELECT_MSB:
                ret = VSCP_UTIL_WORD_MSB(vscp_core_regPageSelect);
                break;

            case VSCP_REG_PAGE_SELECT_LSB:
                ret = VSCP_UTIL_WORD_LSB(vscp_core_regPageSelect);
                break;

            case VSCP_REG_FIRMWARE_VERSION_MAJOR:
                ret = vscp_dev_data_getFirmwareVersionMajor();
                break;

            case VSCP_REG_FIRMWARE_VERSION_MINOR:
                ret = vscp_dev_data_getFirmwareVersionMinor();
                break;

            case VSCP_REG_FIRMWARE_VERSION_SUB_MINOR:
                ret = vscp_dev_data_getFirmwareVersionSubMinor();
                break;

            case VSCP_REG_BOOT_LOADER_ALGORITHM:
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED )
                ret = vscp_portable_getBootLoaderAlgorithm();
#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */
                ret = 0xFF;
#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */
                break;

            case VSCP_REG_BUFFER_SIZE:
                ret = VSCP_L1_DATA_SIZE;
                break;

            case VSCP_REG_PAGES_USED:
                ret = vscp_app_reg_getPagesUsed();
                break;

            case VSCP_REG_STD_DEV_FAMILY_CODE_3:
                /*@fallthrough@*/
            case VSCP_REG_STD_DEV_FAMILY_CODE_2:
                /*@fallthrough@*/
            case VSCP_REG_STD_DEV_FAMILY_CODE_1:
                /*@fallthrough@*/
            case VSCP_REG_STD_DEV_FAMILY_CODE_0:
                ret = vscp_dev_data_getStdDevFamilyCode(3 - (addr - VSCP_REG_STD_DEV_FAMILY_CODE_3));
                break;

            case VSCP_REG_STD_DEV_TYPE_3:
                /*@fallthrough@*/
            case VSCP_REG_STD_DEV_TYPE_2:
                /*@fallthrough@*/
            case VSCP_REG_STD_DEV_TYPE_1:
                /*@fallthrough@*/
            case VSCP_REG_STD_DEV_TYPE_0:
                ret = vscp_dev_data_getStdDevType(3 - (addr - VSCP_REG_STD_DEV_TYPE_3));
                break;

            case VSCP_REG_RESTORE_STD_CFG:
                /* Write only */
                break;

            case VSCP_REG_GUID_15:
                /*@fallthrough@*/
            case VSCP_REG_GUID_14:
                /*@fallthrough@*/
            case VSCP_REG_GUID_13:
                /*@fallthrough@*/
            case VSCP_REG_GUID_12:
                /*@fallthrough@*/
            case VSCP_REG_GUID_11:
                /*@fallthrough@*/
            case VSCP_REG_GUID_10:
                /*@fallthrough@*/
            case VSCP_REG_GUID_9:
                /*@fallthrough@*/
            case VSCP_REG_GUID_8:
                /*@fallthrough@*/
            case VSCP_REG_GUID_7:
                /*@fallthrough@*/
            case VSCP_REG_GUID_6:
                /*@fallthrough@*/
            case VSCP_REG_GUID_5:
                /*@fallthrough@*/
            case VSCP_REG_GUID_4:
                /*@fallthrough@*/
            case VSCP_REG_GUID_3:
                /*@fallthrough@*/
            case VSCP_REG_GUID_2:
                /*@fallthrough@*/
            case VSCP_REG_GUID_1:
                /*@fallthrough@*/
            case VSCP_REG_GUID_0:
                ret = vscp_dev_data_getGUID(15 - (addr - VSCP_REG_GUID_15));
                break;

            default:

                if ((VSCP_REG_MDF_URL_BEGIN <= addr) &&
                    (VSCP_REG_MDF_URL_END >= addr))
                {
                    ret = vscp_dev_data_getMdfUrl(addr - VSCP_REG_MDF_URL_BEGIN);
                }

                break;
        }
    }

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )
    /* Is the addressed register part of the decision matrix? */
    else if (FALSE != vscp_dm_isDecisionMatrix(page, addr))
    {
        ret = vscp_dm_readRegister(page, addr);
    }
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )
    /* Is the addressed register part of the decision matrix NG? */
    else if (FALSE != vscp_dm_ng_isDecisionMatrix(page, addr))
    {
        ret = vscp_dm_ng_readRegister(page, addr);
    }
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

    else
    /* Application specific register */
    {
        ret = vscp_app_reg_readRegister(page, addr);
    }

    return ret;
}

/**
 * Write to register.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @param[in]   value   Value to write
 * @param[out]  failed  Write error is set to TRUE
 * @return  Register value
 */
static uint8_t  vscp_core_writeRegister(uint16_t page, uint8_t addr, uint8_t value, /*@null@*/ BOOL* failed)
{
    uint8_t ret     = 0;
    BOOL    error   = TRUE;

    /* Page 0 includes the VSCP specific registers. */
    if ((0 == page) &&
        (VSCP_REGISTER_VSCP_START_ADDR <= addr) &&
        (VSCP_REGISTER_VSCP_END_ADDR >= addr))
    {
        switch(addr)
        {
        case VSCP_REG_ALARM_STATUS:
            /* Read only */
            break;

        case VSCP_REG_VSCP_VERSION_MAJOR:
            /* Read only */
            break;

        case VSCP_REG_VSCP_VERSION_MINOR:
            /* Read only */
            break;

        case VSCP_REG_NODE_CONTROL_FLAGS:
            vscp_ps_writeNodeControlFlags(value);
            ret = vscp_ps_readNodeControlFlags();
            error = FALSE;
            break;

        case VSCP_REG_USER_ID_0:
            /*@fallthrough@*/
        case VSCP_REG_USER_ID_1:
            /*@fallthrough@*/
        case VSCP_REG_USER_ID_2:
            /*@fallthrough@*/
        case VSCP_REG_USER_ID_3:
            /*@fallthrough@*/
        case VSCP_REG_USER_ID_4:
            vscp_ps_writeUserId(addr - VSCP_REG_USER_ID_0, value);
            ret = vscp_ps_readUserId(addr - VSCP_REG_USER_ID_0);
            error = FALSE;
            break;

        case VSCP_REG_MANUFACTURER_DEV_ID_0:
            /*@fallthrough@*/
        case VSCP_REG_MANUFACTURER_DEV_ID_1:
            /*@fallthrough@*/
        case VSCP_REG_MANUFACTURER_DEV_ID_2:
            /*@fallthrough@*/
        case VSCP_REG_MANUFACTURER_DEV_ID_3:
            /* Read only */
            break;

        case VSCP_REG_MANUFACTURER_SUB_DEV_ID_0:
            /*@fallthrough@*/
        case VSCP_REG_MANUFACTURER_SUB_DEV_ID_1:
            /*@fallthrough@*/
        case VSCP_REG_MANUFACTURER_SUB_DEV_ID_2:
            /*@fallthrough@*/
        case VSCP_REG_MANUFACTURER_SUB_DEV_ID_3:
            /* Read only */
            break;

        case VSCP_REG_NICKNAME_ID:
            /* Read only */
            break;

        case VSCP_REG_PAGE_SELECT_MSB:
            vscp_core_regPageSelect &= 0x00FF;
            vscp_core_regPageSelect |= ((uint16_t)value) << 8;
            ret = VSCP_UTIL_WORD_MSB(vscp_core_regPageSelect);
            error = FALSE;
            break;

        case VSCP_REG_PAGE_SELECT_LSB:
            vscp_core_regPageSelect &= 0xFF00;
            vscp_core_regPageSelect |= ((uint16_t)value) << 0;
            ret = VSCP_UTIL_WORD_LSB(vscp_core_regPageSelect);
            error = FALSE;
            break;

        case VSCP_REG_FIRMWARE_VERSION_MAJOR:
            /* Read only */
            break;

        case VSCP_REG_FIRMWARE_VERSION_MINOR:
            /* Read only */
            break;

        case VSCP_REG_FIRMWARE_VERSION_SUB_MINOR:
            /* Read only */
            break;

        case VSCP_REG_BOOT_LOADER_ALGORITHM:
            /* Read only */
            break;

        case VSCP_REG_BUFFER_SIZE:
            /* Read only */
            break;

        case VSCP_REG_PAGES_USED:
            /* Read only */
            break;

        case VSCP_REG_STD_DEV_FAMILY_CODE_3:
            /*@fallthrough@*/
        case VSCP_REG_STD_DEV_FAMILY_CODE_2:
            /*@fallthrough@*/
        case VSCP_REG_STD_DEV_FAMILY_CODE_1:
            /*@fallthrough@*/
        case VSCP_REG_STD_DEV_FAMILY_CODE_0:
            /* Read only */
            break;

        case VSCP_REG_STD_DEV_TYPE_3:
            /*@fallthrough@*/
        case VSCP_REG_STD_DEV_TYPE_2:
            /*@fallthrough@*/
        case VSCP_REG_STD_DEV_TYPE_1:
            /*@fallthrough@*/
        case VSCP_REG_STD_DEV_TYPE_0:
            /* Read only */
            break;

        case VSCP_REG_RESTORE_STD_CFG:

            /* 0x55 has to be written first, multi-frame timer is disabled. */
            if ((0x55 == value) &&
                (FALSE == vscp_timer_getStatus(vscp_core_timerIdReg162)))
            {
                vscp_timer_start(vscp_core_timerIdReg162, VSCP_CONFIG_MULTI_MSG_TIMEOUT);
            }
            /* 0xAA has to be written after 0x55 and within a specific time. */
            else if ((0xAA == value) &&
                     (TRUE == vscp_timer_getStatus(vscp_core_timerIdReg162)))
            {
                vscp_timer_stop(vscp_core_timerIdReg162);

                /* Restore default settings */
                vscp_core_restoreFactoryDefaultSettings();
            }

            error = FALSE;
            break;

        case VSCP_REG_GUID_15:
            /*@fallthrough@*/
        case VSCP_REG_GUID_14:
            /*@fallthrough@*/
        case VSCP_REG_GUID_13:
            /*@fallthrough@*/
        case VSCP_REG_GUID_12:
            /*@fallthrough@*/
        case VSCP_REG_GUID_11:
            /*@fallthrough@*/
        case VSCP_REG_GUID_10:
            /*@fallthrough@*/
        case VSCP_REG_GUID_9:
            /*@fallthrough@*/
        case VSCP_REG_GUID_8:
            /*@fallthrough@*/
        case VSCP_REG_GUID_7:
            /*@fallthrough@*/
        case VSCP_REG_GUID_6:
            /*@fallthrough@*/
        case VSCP_REG_GUID_5:
            /*@fallthrough@*/
        case VSCP_REG_GUID_4:
            /*@fallthrough@*/
        case VSCP_REG_GUID_3:
            /*@fallthrough@*/
        case VSCP_REG_GUID_2:
            /*@fallthrough@*/
        case VSCP_REG_GUID_1:
            /*@fallthrough@*/
        case VSCP_REG_GUID_0:
            /* Read only */
            break;

        default:

            if ((VSCP_REG_MDF_URL_BEGIN <= addr) &&
                (VSCP_REG_MDF_URL_END >= addr))
            {
                /* Read only */
                ;
            }

            break;
        }
    }
    /* Write protection disabled? */
    else if (0 != vscp_core_getRegAppWriteProtect())
    {

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )
        /* Is the addressed register part of the decision matrix? */
        if (FALSE != vscp_dm_isDecisionMatrix(page, addr))
        {
            ret = vscp_dm_writeRegister(page, addr, value);
        }
        else
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )
        /* Is the addressed register part of the decision matrix NG? */
        if (FALSE != vscp_dm_ng_isDecisionMatrix(page, addr))
        {
            ret = vscp_dm_ng_writeRegister(page, addr, value);
        }
        else
#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */

        /* Application specific registers */
        {
            ret = vscp_app_reg_writeRegister(page, addr, value);
        }

        error = FALSE;
    }

    if (NULL != failed)
    {
        *failed = error;
    }

    return ret;
}

/**
 * Handles a protocol class write register event.
 */
static inline void  vscp_core_handleProtocolWriteRegister(void)
{
    /* Check number of parameters. */
    if (3 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            uint8_t addr    = vscp_core_rxMessage.data[1];
            uint8_t value   = vscp_core_rxMessage.data[2];
            BOOL    error   = FALSE;

            /* Write to register */
            value = vscp_core_writeRegister(0, addr, value, &error);

            /* Successful written? */
            if (FALSE == error)
            {
                /* Response to write register event */
                vscp_core_sendRegisterReadWriteRsp(addr, value);
            }
        }
    }

    return;
}

/**
 * Handles a protocol class enter boot loader event.
 */
static inline void  vscp_core_handleProtocolEnterBootLoaderMode(void)
{
    /* Check number of parameters. */
    if (8 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            vscp_TxMessage  txMessage;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED )

            uint16_t    pageSelect = (((uint16_t)vscp_core_rxMessage.data[6]) << 8) | vscp_core_rxMessage.data[7];

            /* Boot loader not supported?
             * Boot loader algorithm not supported?
             * Wrong GUID bytes?
             * Wrong page select register values?
             */
            if ((0xFF == vscp_portable_getBootLoaderAlgorithm()) ||
                (vscp_portable_getBootLoaderAlgorithm() != vscp_core_rxMessage.data[1]) ||
                (vscp_dev_data_getGUID(15 - 0) != vscp_core_rxMessage.data[2]) ||
                (vscp_dev_data_getGUID(15 - 3) != vscp_core_rxMessage.data[3]) ||
                (vscp_dev_data_getGUID(15 - 5) != vscp_core_rxMessage.data[4]) ||
                (vscp_dev_data_getGUID(15 - 7) != vscp_core_rxMessage.data[5]) ||
                (vscp_core_regPageSelect != pageSelect))
            {
                txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
                txMessage.vscpType  = VSCP_TYPE_PROTOCOL_NACK_BOOT_LOADER;
                txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
                txMessage.oAddr     = vscp_core_nickname;
                txMessage.hardCoded = VSCP_CORE_HARD_CODED;
                txMessage.dataNum   = 1;
                txMessage.data[0]   = 0;   /* User defined error code - not used */

                (void)vscp_transport_writeMessage(&txMessage);
            }
            else
            {
                /* Go idle and wait */
                vscp_core_changeToStateIdle();

                /* Set boot flag to bootloader */
                vscp_ps_writeBootFlag(VSCP_BOOT_FLAG_BOOTLOADER);

                /* Request jump to boot loader */
                vscp_portable_bootLoaderRequest();

                /* Boot loader shall send the acknowledge! */
            }

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */

            txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
            txMessage.vscpType  = VSCP_TYPE_PROTOCOL_NACK_BOOT_LOADER;
            txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
            txMessage.oAddr     = vscp_core_nickname;
            txMessage.hardCoded = VSCP_CORE_HARD_CODED;
            txMessage.dataNum   = 1;
            txMessage.data[0]   = 0;   /* User defined error code - not used */

            (void)vscp_transport_writeMessage(&txMessage);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_BOOT_LOADER_SUPPORTED ) */
        }
    }

    return;
}

/**
 * Handles a protocol class GUID drop nickname id event.
 */
static inline void  vscp_core_handleProtocolGuidDropNickname(void)
{
    /* Check number of parameters. */
    if ((5 == vscp_core_rxMessage.dataNum) &&
        (4 > vscp_core_rxMessage.data[0]))
    {
        static uint8_t  status = 0;

        /* First event of this multi-event? */
        if (0 == vscp_core_rxMessage.data[0])
        {
            /* Reset flag, which is used during all events. */
            status = 0;

            /* Start timer to observe multi-message handling. */
            vscp_timer_start(vscp_core_timerIdGuidDropNickname, VSCP_CONFIG_MULTI_MSG_TIMEOUT);
        }

        /* Timeout? */
        if (FALSE == vscp_timer_getStatus(vscp_core_timerIdGuidDropNickname))
        {
            /* Prevent dropping the nickname. */
            status = 0;
        }
        else
        {
            uint8_t index   = 0;
            BOOL    isEqual = TRUE;

            for(index = 0; index < 4; ++index)
            {
                if (vscp_core_rxMessage.data[1 + index] != vscp_dev_data_getGUID(15 - 4 * vscp_core_rxMessage.data[0] - index))
                {
                    isEqual = FALSE;
                    break;
                }
            }

            if (TRUE == isEqual)
            {
                /* Remember the compare result of each event. */
                status |= 1 << vscp_core_rxMessage.data[0];
            }

            /* Drop the node nickname id? */
            if ((3 == vscp_core_rxMessage.data[0]) &&
                (0x0F== status))
            {
                /* Stop timer */
                vscp_timer_stop(vscp_core_timerIdGuidDropNickname);

                /* Reset status */
                status = 0;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_SILENT_NODE )

                /* Start nickname discovery? */
                if (STATE_STARTUP == vscp_core_state)
                {
                    vscp_core_startNodeSegmentInit();
                }
                else
                /* Nickname already assigned */
                {
                    /* Drop nickname and reset */
                    vscp_core_writeNicknameId(VSCP_NICKNAME_NOT_INIT);
                    vscp_core_changeToStateReset(0);
                }

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_SILENT_NODE ) */

                /* Drop nickname and reset */
                vscp_core_writeNicknameId(VSCP_NICKNAME_NOT_INIT);
                vscp_core_changeToStateReset(0);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_SILENT_NODE ) */
            }
        }
    }

    return;
}

/**
 * Handles a protocol class read page event.
 */
static inline void  vscp_core_handleProtocolPageRead(void)
{
    /* Check number of parameters. */
    if (3 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            vscp_TxMessage  txMessage;
            uint8_t         addr        = vscp_core_rxMessage.data[1];
            uint8_t         index       = 0;
            uint8_t         num         = vscp_core_rxMessage.data[2];
            uint8_t         dataIndex   = 0;

            /* If the number of bytes to read overflows the page, it will be
             * limited to the page end.
             */
            if ((0xFF - num) < addr)
            {
                num = 0xFF - addr;
            }

            /* Prepare tx message */
            txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
            txMessage.vscpType  = VSCP_TYPE_PROTOCOL_RW_PAGE_RESPONSE;
            txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
            txMessage.oAddr     = vscp_core_nickname;
            txMessage.hardCoded = VSCP_CORE_HARD_CODED;
            txMessage.dataNum   = VSCP_L1_DATA_SIZE;

            /* Sequence number */
            txMessage.data[dataIndex] = 0;
            ++dataIndex;

            for(index = 0; index < num; ++index)
            {
                txMessage.data[dataIndex] = vscp_core_readRegister(vscp_core_regPageSelect, addr + index);
                ++dataIndex;

                if (VSCP_L1_DATA_SIZE <= dataIndex)
                {
                    (void)vscp_transport_writeMessage(&txMessage);

                    /* Increase sequence number and reset data index */
                    dataIndex = 0;
                    ++(txMessage.data[dataIndex]);
                    ++dataIndex;
                }
            }

            if (1 < dataIndex)
            {
                txMessage.dataNum = dataIndex;

                (void)vscp_transport_writeMessage(&txMessage);
            }
        }
    }

    return;
}

/**
 * Handles a protocol class write page event.
 */
static inline void  vscp_core_handleProtocolPageWrite(void)
{
    /* Check number of parameters. */
    if (3 <= vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            vscp_TxMessage  txMessage;
            uint8_t         addr        = vscp_core_rxMessage.data[1];
            uint8_t         index       = 0;
            uint8_t         num         = vscp_core_rxMessage.dataNum - 2;
            uint8_t         dataIndex   = 0;

            /* If the number of bytes to read overflows the page, it will be
             * limited to the page end.
             */
            if ((0xFF - num) < addr)
            {
                num = 0xFF - addr;
            }

            /* Prepare tx message */
            txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
            txMessage.vscpType  = VSCP_TYPE_PROTOCOL_RW_PAGE_RESPONSE;
            txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
            txMessage.oAddr     = vscp_core_nickname;
            txMessage.hardCoded = VSCP_CORE_HARD_CODED;

            /* Sequence number */
            txMessage.data[dataIndex] = 0;
            ++dataIndex;

            for(index = 0; index < num; ++index)
            {
                txMessage.data[dataIndex] = vscp_core_writeRegister(vscp_core_regPageSelect,
                                                                    addr + index,
                                                                    vscp_core_rxMessage.data[2 + index],
                                                                    NULL);
                ++dataIndex;
            }

            txMessage.dataNum = dataIndex;

            (void)vscp_transport_writeMessage(&txMessage);
        }
    }

    return;
}

/**
 * Handles a protocol class increment register event.
 */
static inline void  vscp_core_handleProtocolIncrementRegister(void)
{
    /* Check number of parameters. */
    if (2 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            uint8_t addr    = vscp_core_rxMessage.data[1];
            uint8_t value   = vscp_core_readRegister(0, addr);
            BOOL    error   = FALSE;

            /* Increment by one */
            ++value;

            /* Write to register */
            value = vscp_core_writeRegister(0, addr, value, &error);

            if (FALSE == error)
            {
                /* Response to increment register event */
                vscp_core_sendRegisterReadWriteRsp(addr, value);
            }
        }
    }

    return;
}

/**
 * Handles a protocol class decrement register event.
 */
static inline void  vscp_core_handleProtocolDecrementRegister(void)
{
    /* Check number of parameters. */
    if (2 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            uint8_t addr    = vscp_core_rxMessage.data[1];
            uint8_t value   = vscp_core_readRegister(0, addr);
            BOOL    error   = FALSE;

            /* Decrement by one */
            --value;

            /* Write to register */
            value = vscp_core_writeRegister(0, addr, value, &error);

            if (FALSE == error)
            {
                /* Response to increment register event */
                vscp_core_sendRegisterReadWriteRsp(addr, value);
            }
        }
    }

    return;
}

/**
 * Handles a protocol class who is there event.
 */
static inline void  vscp_core_handleProtocolWhoIsThere(void)
{
    /* Check number of parameters. */
    if (1 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if ((vscp_core_nickname == vscp_core_rxMessage.data[0]) ||
            (VSCP_NICKNAME_NOT_INIT == vscp_core_rxMessage.data[0]))
        {
            vscp_TxMessage  txMessage;
            int8_t          sIndex      = 0;
            uint8_t         uIndex      = 0;
            uint8_t         dataIndex   = 0;
            uint8_t         rowIndex    = 0;

            txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
            txMessage.vscpType  = VSCP_TYPE_PROTOCOL_WHO_IS_THERE_RESPONSE;
            txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
            txMessage.oAddr     = vscp_core_nickname;
            txMessage.hardCoded = VSCP_CORE_HARD_CODED;
            txMessage.dataNum   = 8;

            /* Row index */
            txMessage.data[dataIndex] = rowIndex;
            ++dataIndex;
            ++rowIndex;

            /* GUID */
            for(sIndex = 15; sIndex >= 0; --sIndex)
            {
                txMessage.data[dataIndex] = vscp_dev_data_getGUID((uint8_t)sIndex);
                ++dataIndex;

                if (VSCP_L1_DATA_SIZE <= dataIndex)
                {
                    (void)vscp_transport_writeMessage(&txMessage);

                    dataIndex = 0;

                    /* Row index */
                    txMessage.data[dataIndex] = rowIndex;
                    ++dataIndex;
                    ++rowIndex;
                }
            }

            /* MDF */
            for(uIndex = 0; uIndex < 32; ++uIndex)
            {
                txMessage.data[dataIndex] = vscp_dev_data_getMdfUrl(uIndex);
                ++dataIndex;

                if (VSCP_L1_DATA_SIZE <= dataIndex)
                {
                    (void)vscp_transport_writeMessage(&txMessage);

                    dataIndex = 0;

                    /* Row index */
                    txMessage.data[dataIndex] = rowIndex;
                    ++dataIndex;
                    ++rowIndex;
                }
            }

            /* Fill up */
            while(VSCP_L1_DATA_SIZE > dataIndex)
            {
                txMessage.data[dataIndex] = 0;
                ++dataIndex;
            }

            (void)vscp_transport_writeMessage(&txMessage);
        }
    }

    return;
}

/**
 * Handles a protocol class get decision matrix info event.
 */
static inline void  vscp_core_handleProtocolGetDecisionMatrixInfo(void)
{
    /* Check number of parameters. */
    if (1 == vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            vscp_TxMessage  txMessage;
            uint8_t         matrixSize      = 0;
            uint8_t         matrixOffset    = 0;
            uint16_t        pageStart       = 0;

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

            matrixSize      = vscp_dm_getMatrixRows();
            matrixOffset    = vscp_dm_getMatrixOffset();
            pageStart       = vscp_dm_getPage();

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */

            txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
            txMessage.vscpType  = VSCP_TYPE_PROTOCOL_GET_MATRIX_INFO_RESPONSE;
            txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
            txMessage.oAddr     = vscp_core_nickname;
            txMessage.hardCoded = VSCP_CORE_HARD_CODED;
            txMessage.dataNum   = 4;
            txMessage.data[0]   = matrixSize;
            txMessage.data[1]   = matrixOffset;
            txMessage.data[2]   = VSCP_UTIL_WORD_MSB(pageStart);
            txMessage.data[3]   = VSCP_UTIL_WORD_LSB(pageStart);
            /* Note page end is depreciated (byte 4 and 5) and byte 6 is only for L2 nodes. */

            (void)vscp_transport_writeMessage(&txMessage);
        }
    }

    return;
}

/**
 * Handles a protocol class extended page read register event.
 */
static inline void  vscp_core_handleProtocolExtendedPageReadRegister(void)
{
    /* Check number of parameters. */
    if (4 <= vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            vscp_core_extPageReadData.page  = (((uint16_t)vscp_core_rxMessage.data[1]) << 8) | (vscp_core_rxMessage.data[2]);
            vscp_core_extPageReadData.addr  = vscp_core_rxMessage.data[3];
            vscp_core_extPageReadData.seq   = 0;

            /* Read more than one register? */
            if (5 == vscp_core_rxMessage.dataNum)
            {
                vscp_core_extPageReadData.count = vscp_core_rxMessage.data[4];

                /* Shall 256 registers be read? */
                if (0 == vscp_core_extPageReadData.count)
                {
                    vscp_core_extPageReadData.count = 256;
                }
            }
            else
            {
                vscp_core_extPageReadData.count = 1;
            }

            /* Only one response will be sent now.
             * If more responses are necessary, they will be sent in the following
             * process cycles. This avoids that the framework blocks the application
             * too long. And makes the node more responsive.
             */
            vscp_core_extendedPageReadRegister(&vscp_core_extPageReadData);
        }
    }

    return;
}

/**
 * This function handles a extended page read register.
 *
 * @param[in] data  Extended page read register data
 */
static void vscp_core_extendedPageReadRegister(ExtPageRead * const data)
{
    if ((NULL != data) &&
        (0 < data->count))
    {
        vscp_TxMessage  txMessage;
        uint8_t         index       = 0;
        uint8_t         addr        = data->addr;
        uint16_t        count       = data->count;
        BOOL            nextPage    = FALSE;

        /* Prepare tx message */
        txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
        txMessage.vscpType  = VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_RESPONSE;
        txMessage.priority  = VSCP_PRIORITY_7_LOW;
        txMessage.oAddr     = vscp_core_nickname;
        txMessage.hardCoded = VSCP_CORE_HARD_CODED;

        /* Sequence number */
        txMessage.data[0] = data->seq;

        /* Page and offset */
        txMessage.data[1] = (data->page >> 8) & 0xff;
        txMessage.data[2] = (data->page >> 0) & 0xff;
        txMessage.data[3] = addr;

        /* Read registers */
        index = 4;
        do
        {
            txMessage.data[index] = vscp_core_readRegister(data->page, addr);
            ++index;
            --count;

            /* If the read takes place on the next page, a new event shall be used,
             * because the event parameter contains the page, where all read
             * registers are located.
             */
            if (0xff > addr)
            {
                ++addr;
            }
            else
            {
                nextPage = TRUE;
            }
        }
        while((VSCP_L1_DATA_SIZE > index) && (0 < count) && (FALSE == nextPage));

        /* Set event data size */
        txMessage.dataNum = index;

        if (TRUE == vscp_transport_writeMessage(&txMessage))
        {
            /* Continue on the next page? */
            if (TRUE == nextPage)
            {
                ++data->page;
                data->addr = 0;
            }
            /* Continue on the same page */
            else
            {
                data->addr = addr;
            }

            data->count = count;
            ++data->seq;
        }
    }

    return;
}

/**
 * Handles a protocol class extended page write register event.
 */
static inline void  vscp_core_handleProtocolExtendedPageWriteRegister(void)
{
    /* Check number of parameters. */
    if (5 <= vscp_core_rxMessage.dataNum)
    {
        /* This node? */
        if (vscp_core_nickname == vscp_core_rxMessage.data[0])
        {
            vscp_TxMessage  txMessage;
            uint16_t        page        = (((uint16_t)vscp_core_rxMessage.data[1]) << 8) | (vscp_core_rxMessage.data[2]);
            uint8_t         addr        = vscp_core_rxMessage.data[3];
            uint8_t         num         = vscp_core_rxMessage.dataNum - 4;
            uint8_t         index       = 0;
            uint8_t         dataIndex   = 0;

            /* If the number of bytes to write overflows the page, it will be
             * limited to the page end.
             */
            if (((0xFF - num) + 1) < addr)
            {
                num = (0xFF - addr) + 1;
            }

            /* Prepare tx message */
            txMessage.vscpClass = VSCP_CLASS_L1_PROTOCOL;
            txMessage.vscpType  = VSCP_TYPE_PROTOCOL_EXTENDED_PAGE_RESPONSE;
            txMessage.priority  = VSCP_PRIORITY_3_NORMAL;
            txMessage.oAddr     = vscp_core_nickname;
            txMessage.hardCoded = VSCP_CORE_HARD_CODED;

            /* Sequence number */
            txMessage.data[0] = 0;

            /* Page and register */
            txMessage.data[1] = vscp_core_rxMessage.data[1];
            txMessage.data[2] = vscp_core_rxMessage.data[2];
            txMessage.data[3] = vscp_core_rxMessage.data[3];

            dataIndex = 4;

            /* Write registers */
            for(index = 0; index < num; ++index)
            {
                txMessage.data[dataIndex] = vscp_core_writeRegister(page, addr + index, vscp_core_rxMessage.data[4 + index], NULL);
                ++dataIndex;
            }

            txMessage.dataNum = dataIndex;

            (void)vscp_transport_writeMessage(&txMessage);
        }
    }

    return;
}

/**
 * Get start up control information.
 *
 * @return  Start-up control information.
 * @retval  01b Start initialization immediately
 * @retval  others Wait until initialization is explicit started
 */
static inline uint8_t   vscp_core_getStartUpControl(void)
{
    return (vscp_ps_readNodeControlFlags() >> 6) & 0x03;
}

/**
 * Get application register write protection information.
 *
 * @return  Write protection information
 * @retval  0 Write protected
 * @retval  1 Write enabled
 */
static inline uint8_t   vscp_core_getRegAppWriteProtect(void)
{
    return (vscp_ps_readNodeControlFlags() >> 5) & 0x01;
}
