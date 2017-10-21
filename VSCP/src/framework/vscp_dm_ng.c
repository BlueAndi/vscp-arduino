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
@brief  VSCP decision matrix next generation
@file   vscp_dm_ng.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_dm_ng.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_dm_ng.h"
#include "vscp_util.h"
#include "vscp_action.h"
#include "vscp_ps.h"
#include <stdint.h>

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION )

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

/** Mask to retrieve the basic operater from the condition operator. */
#define VSCP_DM_NG_MASK_BASIC_OP    (0x0f)

/** Mask to retrieve the logic operater from the condition operator. */
#define VSCP_DM_NG_MASK_LOGIC_OP    (0xf0)

/** Minimum rule size, including the size byte.
 * size, action id, action parameter, condition operator, event parameter id, value
 */
#define VSCP_DM_NG_SIZE_MIN         6

/** Maximum size of a single rule in bytes */
#define VSCP_DM_NG_RULE_MAX_SIZE    40

/** Decision matrix NG location: Page */
#define VSCP_DM_NG_START_PAGE       VSCP_CONFIG_DM_NG_PAGE

/** Number of pages which are overspaned by the decision matrix NG, without considering the offset. */
#define VSCP_DM_NG_PAGES            (VSCP_CONFIG_DM_NG_RULE_SET_SIZE / 256)

/** Last page of the decision matrix NG */
#define VSCP_DM_NG_LAST_PAGE        (VSCP_DM_NG_START_PAGE + VSCP_DM_NG_PAGES)

/** Last offset in the last page of the decision matrix NG. */
#define VSCP_DM_NG_LAST_PAGE_OFFSET ((0 < (VSCP_CONFIG_DM_NG_RULE_SET_SIZE % 256)) ? (VSCP_CONFIG_DM_NG_RULE_SET_SIZE % 256 - 1) : 255)

/*******************************************************************************
    MACROS
*******************************************************************************/

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DM_NG_DEBUG )

/** Set error. */
#define VSCP_DM_NG_DEBUG_SET_ERROR()    \
    do{                                 \
        vscp_dm_ng_error = TRUE;        \
    }while(0)

/** Clear error */
#define VSCP_DM_NG_DEBUG_CLR_ERROR()    \
    do{                                 \
        vscp_dm_ng_error = FALSE;       \
        vscp_dm_ng_errorRule = 0;       \
        vscp_dm_ng_errorPos = 0;        \
    }while(0)

/** Increase rule number. If a error is set, the rule won't be increased. */
#define VSCP_DM_NG_DEBUG_INC_RULE()     \
    do{                                 \
        if (FALSE == vscp_dm_ng_error)  \
        {                               \
            ++vscp_dm_ng_errorRule;     \
        }                               \
    }while(0);

/** Increase the position in the current rule. If a error is set, the position won't be increased. */
#define VSCP_DM_NG_DEBUG_INC_POS(__pos)     \
    do{                                     \
        if (FALSE == vscp_dm_ng_error)      \
        {                                   \
            vscp_dm_ng_errorPos += (__pos); \
        }                                   \
    }while(0);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DM_NG_DEBUG ) */

#define VSCP_DM_NG_DEBUG_SET_ERROR()

#define VSCP_DM_NG_DEBUG_CLR_ERROR()

#define VSCP_DM_NG_DEBUG_INC_RULE()

#define VSCP_DM_NG_DEBUG_INC_POS(__pos)

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_DM_NG_DEBUG ) */

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/*******************************************************************************
    PROTOTYPES
*******************************************************************************/

static BOOL vscp_dm_ng_getDecisionResult(uint8_t const * const rulePart, uint8_t size, vscp_RxMessage const * const rxMsg);
static uint16_t vscp_dm_ng_getEventParValue(vscp_RxMessage const * const rxMsg, VSCP_DM_NG_EVENT_PAR_ID eventParId, uint8_t dataIndex);
static uint8_t  vscp_dm_ng_getZone(vscp_RxMessage const * const rxMsg);
static uint8_t  vscp_dm_ng_getSubZone(vscp_RxMessage const * const rxMsg);
static BOOL vscp_dm_ng_compare(VSCP_DM_NG_BASIC_OP basicOp, uint16_t eventParValue, uint16_t value);
static VSCP_DM_NG_RET   vscp_dm_ng_getFirstRule(uint8_t * const rule, uint8_t maxSize);
extern VSCP_DM_NG_RET   vscp_dm_ng_getNextRule(uint8_t * const rule, uint8_t maxSize);

/*******************************************************************************
    LOCAL VARIABLES
*******************************************************************************/

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DM_NG_DEBUG )

/** Error flag */
static BOOL     vscp_dm_ng_error        = FALSE;

/** If a error happened, it contains the corresponding rule. */
static uint8_t  vscp_dm_ng_errorRule    = 0;

/** If a error happened, it contains the corresponding position in the rule. */
static uint8_t  vscp_dm_ng_errorPos     = 0;

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DM_NG_DEBUG ) */

/** Counts the number of rules down, until all rules are read with the
 * ::vscp_dm_ng_getFirstRule and
 * ::vscp_dm_ng_getNextRule functions.
 */
static uint8_t  vscp_dm_ng_ruleCnt      = 0;

/** Byte index in the rule set, used by
 * ::vscp_dm_ng_getFirstRule and
 * ::vscp_dm_ng_getNextRule functions.
 */
static uint16_t vscp_dm_ng_ruleSetIndex = 0;

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the module.
 */
extern void vscp_dm_ng_init(void)
{
    /* Nothing to do */

    return;
}

/**
 * This function restores factory default settings.
 */
extern void vscp_dm_ng_restoreFactoryDefaultSettings(void)
{
    uint16_t    index   = 0;

    /* Clear decision matrix next generation */
    for(index = 0; index < VSCP_CONFIG_DM_NG_RULE_SET_SIZE; ++index)
    {
        vscp_ps_writeDMNextGeneration(index, 0);
    }

    return;
}

/**
 * This function check if the given page and address are part of the
 * decision matrix.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Is part of the decision matrix or not.
 * @retval  FALSE   Is not part of the decision matrix.
 * @retval  TRUE    Is part of the decision matrix.
 */
extern BOOL vscp_dm_ng_isDecisionMatrix(uint16_t page, uint8_t addr)
{
    BOOL        status      = FALSE;

    /* Decision matrix NG is not empty? */
    if (0 < VSCP_CONFIG_DM_NG_RULE_SET_SIZE)
    {
        /* Page is inside? */
        if ((VSCP_DM_NG_START_PAGE <= page) &&
            (VSCP_DM_NG_LAST_PAGE >= page))
        {
            /* Page is equal to the last decision matrix NG page? */
            if (VSCP_DM_NG_LAST_PAGE == page)
            {
                /* Address is lower or equal than the last decision matrix NG offset? */
                if (VSCP_DM_NG_LAST_PAGE_OFFSET >= addr)
                {
                    status = TRUE;
                }
            }
            /* Address is inside */
            else
            {
                status = TRUE;
            }
        }
    }
    
    return status;
}

/**
 * Read register and return its value.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Register value
 */
extern uint8_t  vscp_dm_ng_readRegister(uint16_t page, uint8_t addr)
{
    uint8_t value   = 0;
    uint8_t index   = 0;
    
    if (VSCP_DM_NG_START_PAGE <= page)
    {
        index = (page - VSCP_DM_NG_START_PAGE) * 256 + addr;
        
        value = vscp_ps_readDMNextGeneration(index);
    }
    
    return value;
}

/**
 * Write to register.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @param[in]   value   Value to write
 * @return  Register value
 */
extern uint8_t  vscp_dm_ng_writeRegister(uint16_t page, uint8_t addr, uint8_t value)
{
    uint8_t index   = 0;
    
    if (VSCP_DM_NG_START_PAGE <= page)
    {
        index = (page - VSCP_DM_NG_START_PAGE) * 256 + addr;
        
        vscp_ps_writeDMNextGeneration(index, value);
        
        /* Read value back */
        value = vscp_ps_readDMNextGeneration(index);
    }
    
    return value;
}

/**
 * This function process all configured rules and if any action regarding the
 * received message takes place, it will call the corresponding action.
 *
 * @param[in]   rxMsg   Received message
 */
extern void vscp_dm_ng_executeActions(vscp_RxMessage const * const rxMsg)
{
    uint8_t rule[VSCP_DM_NG_RULE_MAX_SIZE];

    if (NULL == rxMsg)
    {
        return;
    }

    /* Get the first rule */
    if (VSCP_DM_NG_RET_OK != vscp_dm_ng_getFirstRule(rule, VSCP_DM_NG_RULE_MAX_SIZE))
    {
        return;
    }

    VSCP_DM_NG_DEBUG_CLR_ERROR();

    /* Walk through every rule */
    do
    {
        uint8_t index           = 0;
        uint8_t actionId        = 0;
        uint8_t actionPar       = 0;
        BOOL    decisionResult  = FALSE;
        uint8_t ruleSize        = 0;

        VSCP_DM_NG_DEBUG_INC_RULE();

        /* rule: <rule size> ... */
        ruleSize = rule[index];
        ++index;

        if (VSCP_DM_NG_SIZE_MIN <= ruleSize)
        {
            /* ... <action id> <action parameter> ... */
            actionId = rule[index];
            ++index;

            actionPar = rule[index];
            ++index;

            /* Parse the condition(s) only in case there is a action to execute.
             * Otherwise save time and get the next rule.
             */
            if (VSCP_DM_NG_ACTION_NO_OPERATION != actionId)
            {
                /* Get the decision result. Note, the decision result is the
                 * same as the condition result or the combination of several
                 * condition results.
                 */
                decisionResult = vscp_dm_ng_getDecisionResult(&rule[index], ruleSize - index, rxMsg);

                if (TRUE == decisionResult)
                {
                    vscp_action_execute(actionId, actionPar, rxMsg);
                }
            }
        }
        else
        {
            VSCP_DM_NG_DEBUG_INC_POS(index);
            VSCP_DM_NG_DEBUG_SET_ERROR();
        }
    }
    while(VSCP_DM_NG_RET_OK == vscp_dm_ng_getNextRule(rule, VSCP_DM_NG_RULE_MAX_SIZE));

    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DM_NG_DEBUG )

/**
 * Get error information, if available.
 *
 * @param[out]  rule    Rule number [1; x]
 * @param[out]  pos     Position index in the rule (not rule set)
 * @return Error available
 * @retval FALSE    No error
 * @retval TRUE     Error happened
 */
extern BOOL vscp_dm_ng_getError(uint8_t * const rule, uint8_t * const pos)
{
    if (NULL != rule)
    {
        *rule = vscp_dm_ng_errorRule;
    }

    if (NULL != pos)
    {
        *pos = vscp_dm_ng_errorPos;
    }

    return vscp_dm_ng_error;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_DM_NG_DEBUG ) */

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

/**
 * This function calculate the decision result of all conditions in the rule.
 *
 * @param[in]   rulePart    Part of the rule, starting with the first condition.
 * @param[in]   size        Size of the rule part
 * @param[in]   rxMsg       Received message
 * @return Result
 */
static BOOL vscp_dm_ng_getDecisionResult(uint8_t const * const rulePart, uint8_t size, vscp_RxMessage const * const rxMsg)
{
    uint8_t             index           = 0;
    BOOL                result          = FALSE;
    BOOL                firstCondition  = TRUE;
    VSCP_DM_NG_LOGIC_OP logicOpPrev     = VSCP_DM_NG_LOGIC_OP_LAST;
    BOOL                error           = FALSE;

    if ((NULL == rulePart) ||
        (NULL == rxMsg) ||
        (0 == size))
    {
        return FALSE;
    }

    /* ... <condition operator> <event parameter id> <value> ... */
    do
    {
        VSCP_DM_NG_BASIC_OP     basicOp         = VSCP_DM_NG_BASIC_OP_UNDEFINED;
        VSCP_DM_NG_LOGIC_OP     logicOp         = VSCP_DM_NG_LOGIC_OP_LAST;
        VSCP_DM_NG_EVENT_PAR_ID eventParId      = VSCP_DM_NG_EVENT_PAR_ID_UNDEFINED;
        uint8_t                 eventParIndex   = 0;
        uint16_t                eventParValue   = 0;
        uint16_t                value           = 0;
        BOOL                    condResult      = FALSE;

        /* Overspan condition operator and event parameter id for rule end check. */
        if (size <= (index + 2))
        {
            error = TRUE;
            break;
        }

        /* ... <condition operator> ... */
        basicOp = rulePart[index] & VSCP_DM_NG_MASK_BASIC_OP;
        logicOp = rulePart[index] & VSCP_DM_NG_MASK_LOGIC_OP;
        ++index;

        /* Out of bounce check */
        if (VSCP_DM_NG_BASIC_OP_MAX_NUM <= basicOp)
        {
            error = TRUE;
            break;
        }

        if ((VSCP_DM_NG_LOGIC_OP_LAST != logicOp) &&
            (VSCP_DM_NG_LOGIC_OP_AND != logicOp) &&
            (VSCP_DM_NG_LOGIC_OP_OR != logicOp))
        {
            error = TRUE;
            break;
        }

        /* ... <event parameter id> ... */
        eventParId = rulePart[index];
        ++index;

        /* Out of bounce check */
        if (VSCP_DM_NG_EVENT_PAR_ID_MAX_NUM <= eventParId)
        {
            error = TRUE;
            break;
        }

        /* If the event parameter index is in the rule, it will be
         * get now.
         */
        if (VSCP_DM_NG_EVENT_PAR_ID_DATA == eventParId)
        {
            eventParIndex = rulePart[index];
            ++index;

            /* End of rule reached? */
            if (size <= index)
            {
                error = TRUE;
                break;
            }
        }

        /* Get the event parameter value */
        eventParValue = vscp_dm_ng_getEventParValue(rxMsg, eventParId, eventParIndex);

        /* ... <value ... */
        value = rulePart[index];
        ++index;

        /* To compare against the vscp class, a 16-value is needed. */
        if (VSCP_DM_NG_EVENT_PAR_ID_CLASS == eventParId)
        {
            /* End of rule reached? */
            if (size <= index)
            {
                error = TRUE;
                break;
            }

            value <<= 8;
            value |= rulePart[index];
            ++index;
        }

        /* Compare */
        condResult = vscp_dm_ng_compare(basicOp, eventParValue, value);

        /* The first condition result? */
        if (TRUE == firstCondition)
        {
            result          = condResult;
            firstCondition  = FALSE;
        }
        /* Combine previous result with current result via logic AND? */
        else if (VSCP_DM_NG_LOGIC_OP_AND == logicOpPrev)
        {
            if ((TRUE == result) && (TRUE == condResult))
            {
                result = TRUE;
            }
            else
            {
                result = FALSE;
            }
        }
        /* Combine previous result with current result via logic OR? */
        else if (VSCP_DM_NG_LOGIC_OP_OR == logicOpPrev)
        {
            if ((TRUE == result) || (TRUE == condResult))
            {
                result = TRUE;
            }
            else
            {
                result = FALSE;
            }
        }
        else
        /* Error */
        {
            error = TRUE;
            break;
        }

        /* Is the decision result already known? */
        if ((VSCP_DM_NG_LOGIC_OP_AND == logicOp) &&
            (FALSE == result))
        {
            /* Makes no sense to continue with this rule, because the result
             * won't change anymore.
             */
            break;
        }

        /* Is the decision result already known? */
        if ((VSCP_DM_NG_LOGIC_OP_OR == logicOp) &&
            (TRUE == result))
        {
            /* Makes no sense to continue with this rule, because the result
             * won't change anymore.
             */
            break;
        }

        logicOpPrev = logicOp;
    }
    while(VSCP_DM_NG_LOGIC_OP_LAST != logicOpPrev);

    /* Any error happened? */
    if (FALSE != error)
    {
        VSCP_DM_NG_DEBUG_INC_POS(index);
        VSCP_DM_NG_DEBUG_SET_ERROR();

        result = FALSE;
    }

    return result;
}

/**
 * This function returns the value from the event parameters.
 *
 * @param[in]   rxMsg       Received message
 * @param[in]   eventParId  Event parameter id
 * @param[in]   dataIndex   Data index (only used in case of VSCP_DM_NG_EVENT_PAR_ID_DATA)
 * @return Event parameter value
 */
static uint16_t vscp_dm_ng_getEventParValue(vscp_RxMessage const * const rxMsg, VSCP_DM_NG_EVENT_PAR_ID eventParId, uint8_t dataIndex)
{
    uint16_t    value   = 0;

    if (NULL == rxMsg)
    {
        return 0;
    }

    switch(eventParId)
    {
    case VSCP_DM_NG_EVENT_PAR_ID_UNDEFINED:
        /* Use default value */
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_CLASS:
        value = rxMsg->vscpClass;
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_TYPE:
        value = rxMsg->vscpType;
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_OADDR:
        value = rxMsg->oAddr;
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_HARD_CODED:
        value = (uint16_t)rxMsg->hardCoded;
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_PRIORITY:
        value = rxMsg->priority;
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_ZONE:
        value = vscp_dm_ng_getZone(rxMsg);
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_SUB_ZONE:
        value = vscp_dm_ng_getSubZone(rxMsg);
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_DATA_NUM:
        value = rxMsg->dataNum;
        break;

    case VSCP_DM_NG_EVENT_PAR_ID_DATA0:
        /*@fallthrough@*/
    case VSCP_DM_NG_EVENT_PAR_ID_DATA1:
        /*@fallthrough@*/
    case VSCP_DM_NG_EVENT_PAR_ID_DATA2:
        /*@fallthrough@*/
    case VSCP_DM_NG_EVENT_PAR_ID_DATA3:
        /*@fallthrough@*/
    case VSCP_DM_NG_EVENT_PAR_ID_DATA4:
        /*@fallthrough@*/
    case VSCP_DM_NG_EVENT_PAR_ID_DATA5:
        /*@fallthrough@*/
    case VSCP_DM_NG_EVENT_PAR_ID_DATA6:
        dataIndex = eventParId - VSCP_DM_NG_EVENT_PAR_ID_DATA0;
        /*@fallthrough@*/
    case VSCP_DM_NG_EVENT_PAR_ID_DATA:
        if (rxMsg->dataNum > dataIndex)
        {
            value = rxMsg->data[dataIndex];
        }
        break;

    default:
        /* Use default value */
        break;
    }

    return value;
}

/**
 * This function returns the zone of the received message.
 *
 * @param[in]   rxMsg   Received message
 * @return Zone
 */
static uint8_t  vscp_dm_ng_getZone(vscp_RxMessage const * const rxMsg)
{
    uint8_t zone    = 0xff;

    if (NULL != rxMsg)
    {
        uint8_t index   = vscp_util_getZoneIndex(rxMsg->vscpClass, rxMsg->vscpType);

        if (VSCP_L1_DATA_SIZE > index)
        {
            zone = rxMsg->data[index];
        }
    }

    return zone;
}

/**
 * This function returns the sub-zone of the received message.
 *
 * @param[in]   rxMsg   Received message
 * @return Sub-zone
 */
static uint8_t  vscp_dm_ng_getSubZone(vscp_RxMessage const * const rxMsg)
{
    uint8_t subZone    = 0xff;

    if (NULL != rxMsg)
    {
        uint8_t index   = vscp_util_getZoneIndex(rxMsg->vscpClass, rxMsg->vscpType);

        if (VSCP_L1_DATA_SIZE > index)
        {
            subZone = rxMsg->data[index + 1];
        }
    }

    return subZone;
}

/**
 * This function compares the two given values according to the operator.
 *
 * @param[in]   basicOp         Operator which is used to compare
 * @param[in]   eventParValue   Event parameter value
 * @param[in]   value           Value
 * @return Result
 */
static BOOL vscp_dm_ng_compare(VSCP_DM_NG_BASIC_OP basicOp, uint16_t eventParValue, uint16_t value)
{
    BOOL    result  = FALSE;

    switch(basicOp)
    {
    case VSCP_DM_NG_BASIC_OP_UNDEFINED:
        /* Use default result */
        break;

    case VSCP_DM_NG_BASIC_OP_EQUAL:
        if (eventParValue == value)
        {
            result = TRUE;
        }
        break;

    case VSCP_DM_NG_BASIC_OP_LOWER:
        if (eventParValue < value)
        {
            result = TRUE;
        }
        break;

    case VSCP_DM_NG_BASIC_OP_GREATER:
        if (eventParValue > value)
        {
            result = TRUE;
        }
        break;

    case VSCP_DM_NG_BASIC_OP_LOWER_EQUAL:
        if (eventParValue <= value)
        {
            result = TRUE;
        }
        break;

    case VSCP_DM_NG_BASIC_OP_GREATER_EQUAL:
        if (eventParValue >= value)
        {
            result = TRUE;
        }
        break;

    case VSCP_DM_NG_BASIC_OP_MASK:
        if (0 != (eventParValue & value))
        {
            result = TRUE;
        }
        break;

    default:
        /* Use default result */
        break;
    }

    return result;
}

/**
 * Get the first rule in the rule set.
 *
 * @param[in,out]   rule    Rule buffer
 * @param[in]       maxSize Rule buffer size
 * @return Status
 */
static VSCP_DM_NG_RET   vscp_dm_ng_getFirstRule(uint8_t * const rule, uint8_t maxSize)
{
    VSCP_DM_NG_RET  status  = VSCP_DM_NG_RET_OK;

    if (NULL == rule)
    {
        return VSCP_DM_NG_RET_NULL;
    }

    /* Get the number of rules */
    vscp_dm_ng_ruleSetIndex = 0;
    vscp_dm_ng_ruleCnt      = vscp_ps_readDMNextGeneration(vscp_dm_ng_ruleSetIndex);
    ++vscp_dm_ng_ruleSetIndex;

    /* Empty rule set? */
    if (0 == vscp_dm_ng_ruleCnt)
    {
        status = VSCP_DM_NG_RET_NO_RULE;
    }
    else
    {
        uint8_t ruleSize = vscp_ps_readDMNextGeneration(vscp_dm_ng_ruleSetIndex);

        /* Is the rule buffer big enough to hold the complete rule? */
        if (maxSize < ruleSize)
        {
            status = VSCP_DM_NG_RET_ERROR;
        }
        else
        {
            uint8_t index   = 0;

            /* Copy rule to buffer */
            for(index = 0; index < ruleSize; ++index)
            {
                rule[index] = vscp_ps_readDMNextGeneration(vscp_dm_ng_ruleSetIndex + index);
            }

            /* Increment rule set index to the next rule */
            vscp_dm_ng_ruleSetIndex += ruleSize;
            --vscp_dm_ng_ruleCnt;
        }
    }

    return status;
}

/**
 * Get the next rule in the rule set.
 *
 * @param[in,out]   rule    Rule buffer
 * @param[in]       maxSize Rule buffer size
 * @return Status
 */
extern VSCP_DM_NG_RET   vscp_dm_ng_getNextRule(uint8_t * const rule, uint8_t maxSize)
{
    VSCP_DM_NG_RET  status  = VSCP_DM_NG_RET_OK;

    if (NULL == rule)
    {
        return VSCP_DM_NG_RET_NULL;
    }

    /* No rule available anymore? */
    if (0 == vscp_dm_ng_ruleCnt)
    {
        status = VSCP_DM_NG_RET_NO_RULE;
    }
    else
    {
        uint8_t ruleSize = vscp_ps_readDMNextGeneration(vscp_dm_ng_ruleSetIndex);

        /* Is the rule buffer big enough to hold the complete rule? */
        if (maxSize < ruleSize)
        {
            status = VSCP_DM_NG_RET_ERROR;
        }
        else
        {
            uint8_t index   = 0;

            /* Copy rule to buffer */
            for(index = 0; index < ruleSize; ++index)
            {
                rule[index] = vscp_ps_readDMNextGeneration(vscp_dm_ng_ruleSetIndex + index);
            }

            /* Increment rule set index to the next rule */
            vscp_dm_ng_ruleSetIndex += ruleSize;
            --vscp_dm_ng_ruleCnt;
        }
    }

    return status;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_NEXT_GENERATION ) */
