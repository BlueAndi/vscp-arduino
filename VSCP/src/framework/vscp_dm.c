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
@brief  VSCP decision matrix
@file   vscp_dm.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see vscp_dm.h

*******************************************************************************/

/*******************************************************************************
    INCLUDES
*******************************************************************************/
#include "vscp_dm.h"
#include "vscp_action.h"
#include "vscp_util.h"
#include "vscp_dev_data.h"
#include "vscp_ps.h"

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM )

/*******************************************************************************
    COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
    CONSTANTS
*******************************************************************************/

#if VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/** Number of decision matrix rows */
#define VSCP_DM_ROWS                    VSCP_CONFIG_DM_ROWS

#else   /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

/** Number of decision matrix rows (standard + extension) */
#define VSCP_DM_ROWS                    (2 * VSCP_CONFIG_DM_ROWS)

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

/** Address of the decision matrix byte index, if paged feature is enabled. */
#define VSCP_DM_PAGED_INDEX             (0x7E)

/** Address of the decision matrix value, if paged feature is enabled. */
#define VSCP_DM_PAGED_VALUE             (0x7F)

/** Decision matrix location: Page */
#define VSCP_DM_START_PAGE              0

/** Decision matrix location: Offset in the page */
#define VSCP_DM_START_OFFSET            VSCP_DM_PAGED_INDEX

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/* If the decision matrix extension and the special paged feature are enabled, the
 * number of rows is limited to (128 / 8). Because the special paged feature is used
 * for both and the register read/write has a 8-bit index.
 */
VSCP_UTIL_COMPILE_TIME_ASSERT(VSCP_CONFIG_DM_ROWS > (128 / sizeof(vscp_dm_MatrixRow)))

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

/** Decision matrix location: Page */
#define VSCP_DM_START_PAGE              VSCP_CONFIG_DM_PAGE

/** Decision matrix location: Offset in the page */
#define VSCP_DM_START_OFFSET            VSCP_CONFIG_DM_OFFSET

/** Maximum number of rows per page. */
#define VSCP_DM_MAX_ROWS_PER_PAGE       ((uint8_t)(((uint16_t)256) / sizeof(vscp_dm_MatrixRow)))

/** Number of pages which are overspaned by the decision matrix, without considering the offset. */
#define VSCP_DM_PAGES                   (VSCP_DM_ROWS / VSCP_DM_MAX_ROWS_PER_PAGE)

/** Additional page, which depends on the decision matrix offset in the first page. */
#define VSCP_DM_ADDITIONAL_PAGE         ((255 - VSCP_DM_START_OFFSET) < ((VSCP_DM_START_PAGE + VSCP_DM_PAGES) + 1) ? 1 : 0)

/** Last page of the decision matrix. */
#define VSCP_DM_LAST_PAGE               (VSCP_DM_START_PAGE + VSCP_DM_PAGES + VSCP_DM_ADDITIONAL_PAGE)

/** Last offset in the last page of the decision matrix. */
#define VSCP_DM_LAST_OFFSET             ((VSCP_DM_ROWS % VSCP_DM_MAX_ROWS_PER_PAGE) * sizeof(vscp_dm_MatrixRow) - 1 + (0 < VSCP_DM_ADDITIONAL_PAGE ? 255 - VSCP_DM_START_OFFSET : 0))

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/* It is important, that a decision matrix extension row has the same size, as the
 * standard decision matrix row. Otherwise the whole register read/write handling
 * doesn't work anymore.
 */
VSCP_UTIL_COMPILE_TIME_ASSERT(sizeof(vscp_dm_MatrixRow) == sizeof(vscp_dm_ExtRow));

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

/*******************************************************************************
    MACROS
*******************************************************************************/

/*******************************************************************************
    TYPES AND STRUCTURES
*******************************************************************************/

/*******************************************************************************
    PROTOTYPES
*******************************************************************************/

static void vscp_dm_readDecisionMatrix(vscp_dm_MatrixRow * const row, uint8_t rowIndex);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

static void vscp_dm_readDecisionMatrixExt(vscp_dm_ExtRow * const row, uint8_t rowIndex);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

static BOOL vscp_dm_isDecisionMatrixPagedFeature(uint16_t page, uint8_t addr);
static uint8_t  vscp_dm_readRegisterPagedFeature(uint16_t page, uint8_t addr);
static uint8_t  vscp_dm_writeRegisterPagedFeature(uint16_t page, uint8_t addr, uint8_t value);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

static BOOL vscp_dm_isDecisionMatrixStd(uint16_t page, uint8_t addr);
static uint8_t  vscp_dm_readRegisterStd(uint16_t page, uint8_t addr);
static uint8_t  vscp_dm_writeRegisterStd(uint16_t page, uint8_t addr, uint8_t value);

static BOOL vscp_dm_calculateMatrixIndex(uint8_t* index, uint8_t* offset, uint16_t page, uint8_t addr);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

/*******************************************************************************
    LOCAL VARIABLES
*******************************************************************************/

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

/** Decision matrix byte index, if paged feature is enabled. */
static uint8_t  vscp_dm_index       = 0;

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
    GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function initializes the decision matrix module.
 */
extern void vscp_dm_init(void)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

    vscp_dm_index   = 0;

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

    return;
}

/**
 * This function restores factory default settings.
 */
extern void vscp_dm_restoreFactoryDefaultSettings(void)
{
    uint16_t    index   = 0;

    /* Clear decision matrix */
    for(index = 0; index < VSCP_PS_SIZE_DM; ++index)
    {
        vscp_ps_writeDM(index, 0);
    }

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

    /* Clear decision matrix extension */
    for(index = 0; index < VSCP_PS_SIZE_DM_EXTENSION; ++index)
    {
        vscp_ps_writeDMExtension(index, 0);
    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

    return;
}

/**
 * This function get the number of rows in the decision matrix.
 *
 * @return  Number of rows
 */
extern uint8_t  vscp_dm_getMatrixRows(void)
{
    return VSCP_CONFIG_DM_ROWS;
}

/**
 * This function returns the page of the decision matrix.
 *
 * @return  Page
 */
extern uint16_t vscp_dm_getPage(void)
{
    return VSCP_DM_START_PAGE;
}

/**
 * This function get the offset of the decision matrix.
 *
 * @return  Decision matrix offset
 */
extern uint8_t  vscp_dm_getMatrixOffset(void)
{
    return VSCP_DM_START_OFFSET;
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
extern BOOL vscp_dm_isDecisionMatrix(uint16_t page, uint8_t addr)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

    return vscp_dm_isDecisionMatrixPagedFeature(page, addr);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

    return vscp_dm_isDecisionMatrixStd(page, addr);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */
}

/**
 * Read register and return its value.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @return  Register value
 */
extern uint8_t  vscp_dm_readRegister(uint16_t page, uint8_t addr)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

    return vscp_dm_readRegisterPagedFeature(page, addr);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

    return vscp_dm_readRegisterStd(page, addr);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */
}

/**
 * Write to register.
 *
 * @param[in]   page    Page
 * @param[in]   addr    Register address
 * @param[in]   value   Value to write
 * @return  Register value
 */
extern uint8_t  vscp_dm_writeRegister(uint16_t page, uint8_t addr, uint8_t value)
{
#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

    return vscp_dm_writeRegisterPagedFeature(page, addr, value);

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

    return vscp_dm_writeRegisterStd(page, addr, value);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */
}

/**
 * This function check the decision matrix and executes their actions if
 * applicable.
 *
 * @param[in]   msg Received message via VSCP
 */
extern void vscp_dm_executeActions(vscp_RxMessage const * const msg)
{
    uint8_t index   = 0;

    if (NULL == msg)
    {
        return;
    }

    /* Walk through all decision matrix rows and execute the triggered ones. */
    for(index = 0; index < VSCP_CONFIG_DM_ROWS; ++index)
    {
        uint16_t            classMask   = 0;
        uint16_t            classFilter = 0;
        vscp_dm_MatrixRow   row         = { 0, 0, 0, 0, 0, 0, 0, 0 };

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

        vscp_dm_ExtRow      extRow      = { 0, 0, 0, 0, 0, 0, 0, 0 };

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

        vscp_dm_readDecisionMatrix(&row, index);

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

        vscp_dm_readDecisionMatrixExt(&extRow, index);

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

        /* Decision matrix row disabled? */
        if (0 == (row.flags & VSCP_DM_FLAG_ENABLE))
        {
            /* Next row */
            continue;
        }

        /* No action? */
        if (VSCP_DM_ACTION_NO_OPERATION == row.action)
        {
            /* Next row */
            continue;
        }

        /* Check originating address? */
        if (0 != (row.flags & VSCP_DM_FLAG_CHECK_OADDR))
        {
            /* Address doesn't match? */
            if (row.oaddr != msg->oAddr)
            {
                /* Next row */
                continue;
            }
        }

        /* Check hard-coded bit? */
        if (0 != (row.flags & VSCP_DM_FLAG_HARDCODED))
        {
            /* No hard coded node? */
            if (FALSE == msg->hardCoded)
            {
                /* Next row */
                continue;
            }
        }

        /* Zone or sub zone match necessary? */
        if ((0 != (row.flags & VSCP_DM_FLAG_MATCH_ZONE)) ||
            (0 != (row.flags & VSCP_DM_FLAG_MATCH_SUB_ZONE)))
        {
            uint8_t zoneIndex   = vscp_util_getZoneIndex(msg->vscpClass, msg->vscpType);

            if ((0 <= zoneIndex) &&
                (VSCP_L1_DATA_SIZE > zoneIndex))
            {
                uint8_t subZoneIndex    = zoneIndex + 1;

                /* Zone match? */
                if (0 != (row.flags & VSCP_DM_FLAG_MATCH_ZONE))
                {
                    uint8_t zone    = msg->data[zoneIndex];
                    uint8_t dmZone  = vscp_dev_data_getNodeZone();

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

                    /* Is the extension enabled for this row? */
                    if (VSCP_DM_ACTION_EXTENDED_DM == row.action)
                    {
                        /* Overwrite node zone */
                        dmZone = extRow.zone;
                    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

                    /* Zone's doesn't match? */
                    if (zone != dmZone)
                    {
                        /* Next row */
                        continue;
                    }
                }

                /* Sub zone match? */
                if (0 != (row.flags & VSCP_DM_FLAG_MATCH_SUB_ZONE))
                {
                    uint8_t subZone     = msg->data[subZoneIndex];
                    uint8_t dmSubZone   = vscp_dev_data_getNodeSubZone();

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

                    /* Is the extension enabled for this row? */
                    if (VSCP_DM_ACTION_EXTENDED_DM == row.action)
                    {
                        /* Overwrite node sub-zone */
                        dmSubZone = extRow.subZone;
                    }

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

                    /* Sub-zone's doesn't match? */
                    if (subZone != dmSubZone)
                    {
                        /* Next row */
                        continue;
                    }
                }
            }
            else
            {
                /* Next row */
                continue;
            }
        }

        /* Build class mask and filter */
        classMask   = row.classMask;

        if (0 != (row.flags & VSCP_DM_FLAG_CLASS_MASK_BIT8))
        {
            classMask |= (uint16_t)0x0100;
        }

        classFilter = row.classFilter;

        if (0 != (row.flags & VSCP_DM_FLAG_CLASS_FILTER_BIT8))
        {
            classFilter |= (uint16_t)0x0100;
        }

        /* Class doesn't match? */
        if ((0 != classMask) &&
            (classFilter != (classMask & msg->vscpClass)))
        {
            /* Next row */
            continue;
        }

        /* Type doesn't match? */
        if ((0 != row.typeMask) &&
            (row.typeFilter != (row.typeMask & msg->vscpType)))
        {
            /* Next row */
            continue;
        }

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

        /* Is the extension enabled for this row? */
        if (VSCP_DM_ACTION_EXTENDED_DM == row.action)
        {
            /* The action parameters transform to the extension flags. */
            uint8_t extFlags    = row.actionPar;

            /* Compare to event parameter byte 0? */
            if (0 != (extFlags & VSCP_DM_EXTFLAG_MATCH_PAR_0))
            {
                if (0 == msg->dataNum)
                {
                    /* Next row */
                    continue;
                }
                else if (extRow.par0 != msg->data[0])
                {
                    /* Next row */
                    continue;
                }
            }

            /* Compare to event parameter byte 3? */
            if (0 != (extFlags & VSCP_DM_EXTFLAG_MATCH_PAR_3))
            {
                if (3 >= msg->dataNum)
                {
                    /* Next row */
                    continue;
                }
                else if (extRow.par3 != msg->data[3])
                {
                    /* Next row */
                    continue;
                }
            }

            /* Compare to event parameter byte 4? */
            if (0 != (extFlags & VSCP_DM_EXTFLAG_MATCH_PAR_4))
            {
                if (4 >= msg->dataNum)
                {
                    /* Next row */
                    continue;
                }
                else if (extRow.par4 != msg->data[4])
                {
                    /* Next row */
                    continue;
                }
            }

            /* Compare to event parameter byte 5? */
            if (0 != (extFlags & VSCP_DM_EXTFLAG_MATCH_PAR_5))
            {
                if (5 >= msg->dataNum)
                {
                    /* Next row */
                    continue;
                }
                else if (extRow.par5 != msg->data[5])
                {
                    /* Next row */
                    continue;
                }
            }

            /* Execute action */
            vscp_action_execute(extRow.action, extRow.actionPar, msg);
        }
        else
        {
            /* Execute action */
            vscp_action_execute(row.action, row.actionPar, msg);
        }

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

        /* Execute action */
        vscp_action_execute(row.action, row.actionPar, msg);

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */
    }

    return;
}

/*******************************************************************************
    LOCAL FUNCTIONS
*******************************************************************************/

/**
 * This function reads a single line from the decision matrix.
 *
 * @param[out]  row         Pointer to the row storage
 * @param[in]   rowIndex    Row index
 */
static void vscp_dm_readDecisionMatrix(vscp_dm_MatrixRow * const row, uint8_t rowIndex)
{
    if (NULL != row)
    {
        uint16_t    start       = ((uint16_t)rowIndex) * sizeof(vscp_dm_MatrixRow);
        uint8_t     index       = 0;
        uint8_t*    rowBytePtr  = (uint8_t*)row;

        for(index = 0; index < sizeof(vscp_dm_MatrixRow); ++index)
        {
            *rowBytePtr = vscp_ps_readDM(start + index);
            ++rowBytePtr;
        }
    }

    return;
}

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION )

/**
 * This function reads a single line from the decision matrix extension.
 *
 * @param[out]  row         Pointer to the row storage
 * @param[in]   rowIndex    Row index
 */
static void vscp_dm_readDecisionMatrixExt(vscp_dm_ExtRow * const row, uint8_t rowIndex)
{
    if (NULL != row)
    {
        uint16_t    start       = ((uint16_t)rowIndex) * sizeof(vscp_dm_ExtRow);
        uint16_t    index       = 0;
        uint8_t*    rowBytePtr  = (uint8_t*)row;

        for(index = 0; index < sizeof(vscp_dm_ExtRow); ++index)
        {
            *rowBytePtr = vscp_ps_readDMExtension(start + index);
            ++rowBytePtr;
        }
    }

    return;
}

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM_EXTENSION ) */

#if VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_DM_PAGED_FEATURE )

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
static inline BOOL vscp_dm_isDecisionMatrixPagedFeature(uint16_t page, uint8_t addr)
{
    BOOL    status  = FALSE;

    if (0 == page)
    {
        if ((VSCP_DM_PAGED_INDEX == addr) ||
            (VSCP_DM_PAGED_VALUE == addr))
        {
            status = TRUE;
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
static inline uint8_t  vscp_dm_readRegisterPagedFeature(uint16_t page, uint8_t addr)
{
    uint8_t value   = 0;

    if (0 == page)
    {
        if (VSCP_DM_PAGED_INDEX == addr)
        {
            value = vscp_dm_index;
        }
        else if (VSCP_DM_PAGED_VALUE == addr)
        {
            uint8_t rowIndex    = vscp_dm_index / sizeof(vscp_dm_MatrixRow);
            uint8_t rowOffset   = vscp_dm_index % sizeof(vscp_dm_MatrixRow);

            /* Row out of bounds? */
            if (VSCP_DM_ROWS <= rowIndex)
            {
                value = 0;
            }
            else
            {
                uint16_t    index   = ((uint16_t)rowIndex) * sizeof(vscp_dm_MatrixRow) + (uint16_t)rowOffset;

                value = vscp_ps_readDM(index);
            }
        }
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
static inline uint8_t   vscp_dm_writeRegisterPagedFeature(uint16_t page, uint8_t addr, uint8_t value)
{
    if (0 == page)
    {
        if (VSCP_DM_PAGED_INDEX == addr)
        {
            uint16_t    lastIndex   = ((uint16_t)VSCP_DM_ROWS * (uint16_t)sizeof(vscp_dm_MatrixRow)) - (uint16_t)1;

            /* Index in range? */
            if (lastIndex >= value)
            {
                vscp_dm_index = value;
            }
        }
        else if (VSCP_DM_PAGED_VALUE == addr)
        {
            uint8_t rowIndex    = vscp_dm_index / sizeof(vscp_dm_MatrixRow);
            uint8_t rowOffset   = vscp_dm_index % sizeof(vscp_dm_MatrixRow);

            /* Row out of bounds? */
            if (VSCP_DM_ROWS <= rowIndex)
            {
                value = 0;
            }
            else
            {
                uint16_t    index   = ((uint16_t)rowIndex) * sizeof(vscp_dm_MatrixRow) + (uint16_t)rowOffset;

                vscp_ps_writeDM(index, value);
            }
        }
    }

    return value;
}

#else   /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

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
static inline BOOL vscp_dm_isDecisionMatrixStd(uint16_t page, uint8_t addr)
{
    BOOL    status  = FALSE;

    /* Decision matrix is not empty? */
    if (0 < VSCP_DM_ROWS)
    {
        /* Page is equal to the first decision matrix page? */
        if (VSCP_DM_START_PAGE == page)
        {
            /* Address is greater or equal than the decision matrix offset? */
            if (VSCP_DM_START_OFFSET <= addr)
            {
                /* Decision matrix spans more than one page? */
                if (VSCP_DM_START_PAGE < VSCP_DM_LAST_PAGE)
                {
                    status = TRUE;
                }
                /* Decision matrix has only one page.
                 * Is the address lower or equal than the last decision matrix offset?
                 */
                else if (VSCP_DM_LAST_OFFSET >= addr)
                {
                    status = TRUE;
                }
            }
        }
        /* Page is equal to the last decision matrix page? */
        else if (VSCP_DM_LAST_PAGE == page)
        {
            /* Address is lower or equal than the last decision matrix offset? */
            if (VSCP_DM_START_OFFSET >= addr)
            {
                status = TRUE;
            }
        }
        /* Page is between first and last decision matrix page? */
        else if ((VSCP_DM_START_PAGE < page) &&
                 (VSCP_DM_LAST_PAGE > page))
        {
            status = TRUE;
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
static inline uint8_t  vscp_dm_readRegisterStd(uint16_t page, uint8_t addr)
{
    uint8_t value       = 0;
    uint8_t rowIndex    = 0;
    uint8_t rowOffset   = 0;

    /* Is the given page and address part of the decision matrix? */
    if (TRUE == vscp_dm_calculateMatrixIndex(&rowIndex, &rowOffset, page, addr))
    {
        uint16_t    index   = ((uint16_t)rowIndex) * sizeof(vscp_dm_MatrixRow) + (uint16_t)rowOffset;

        value = vscp_ps_readDM(index);
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
static inline uint8_t   vscp_dm_writeRegisterStd(uint16_t page, uint8_t addr, uint8_t value)
{
    uint8_t rowIndex    = 0;
    uint8_t rowOffset   = 0;

    /* Is the given page and address part of the decision matrix? */
    if (TRUE == vscp_dm_calculateMatrixIndex(&rowIndex, &rowOffset, page, addr))
    {
        uint16_t    index   = ((uint16_t)rowIndex) * sizeof(vscp_dm_MatrixRow) + (uint16_t)rowOffset;

        vscp_ps_writeDM(index, value);
        
        /* Read value back */
        value = vscp_ps_readDM(index);
    }

    return value;
}

/**
 * This function calculates the row index and offset in the decision matrix,
 * according to the given page and address.
 *
 * @param[out]  index   Row index
 * @param[out]  offset  Offset in the row
 * @param[in]   page    Page
 * @param[in]   addr    Address
 * @return  Successful calculated or out of bounds
 * @retval  FALSE   Out of bounds
 * @retval  TRUE    Successful calculated
 */
static BOOL vscp_dm_calculateMatrixIndex(uint8_t* index, uint8_t* offset, uint16_t page, uint8_t addr)
{
    BOOL    status  = FALSE;

    if ((NULL != index) &&
        (NULL != offset))
    {
        *index  = 0;
        *offset = 0;

        if (TRUE == vscp_dm_isDecisionMatrix(page, addr))
        {
            uint16_t    byteIndex   = 0;

            byteIndex  = page - VSCP_DM_START_PAGE;
            byteIndex *= sizeof(vscp_dm_MatrixRow);

            if (VSCP_DM_START_PAGE == page)
            {
                byteIndex += addr - VSCP_DM_START_OFFSET;
            }
            else
            {
                byteIndex += (0xFF - VSCP_DM_START_OFFSET) + 1;
                byteIndex += addr;
            }

            *index  = (uint8_t)(byteIndex / sizeof(vscp_dm_MatrixRow));
            *offset = (uint8_t)(byteIndex % sizeof(vscp_dm_MatrixRow));

            status = TRUE;
        }
    }

    return status;
}

#endif  /* VSCP_CONFIG_BASE_IS_DISABLED( VSCP_CONFIG_DM_PAGED_FEATURE ) */

#endif  /* VSCP_CONFIG_BASE_IS_ENABLED( VSCP_CONFIG_ENABLE_DM ) */
