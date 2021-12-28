/*
 * Event.c
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_EVENT_C_
#define PLUMAOS_EVENT_C_

#include "Event.h"

typedef struct Event
{
    uint32_t time_start;
    uint32_t timeout;
    volatile event_flags_t flags;
    uint8_t autoClear;
    volatile uint8_t isWaiting;
} event_t;

/**
 * @brief
 *
 * @param eventHandle
 * @param autoClear
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Event_Create(PlumaOS_Handle_t eventHandle, uint8_t autoClear)
{
    event_t *pEventStruct = eventHandle;

    pEventStruct->isWaiting = 0U;
    pEventStruct->flags = 0;
    pEventStruct->autoClear = autoClear;
    pEventStruct->time_start = 0u;
    pEventStruct->timeout = 0u;

    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param eventHandle
 * @param flagsToSet
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Event_Set(PlumaOS_Handle_t eventHandle, event_flags_t flagsToSet)
{
    event_t *pEventStruct;
    uint32_t regPrimask;
    pEventStruct = (event_t *)eventHandle;
    /* Set flags ensuring atomic operation */
    //PlumaOS_EnterCritical(&regPrimask);
    pEventStruct->flags |= flagsToSet;
    //PlumaOS_ExitCritical(regPrimask);

    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param eventHandle
 * @param flagsToClear
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Event_Clear(PlumaOS_Handle_t eventHandle, event_flags_t flagsToClear)
{
    event_t *pEventStruct;
    uint32_t regPrimask;
    pEventStruct = (event_t *)eventHandle;
    /* Clear flags ensuring atomic operation */
    //PlumaOS_EnterCritical(&regPrimask);
    pEventStruct->flags &= ~flagsToClear;
    //PlumaOS_ExitCritical(regPrimask);

    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param eventHandle
 * @param flagsMask
 * @param pFlagsOfEvent
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Event_Get(PlumaOS_Handle_t eventHandle, event_flags_t flagsMask, event_flags_t *pFlagsOfEvent)
{
    event_t *pEventStruct;
    pEventStruct = (event_t *)eventHandle;
    uint32_t regPrimask;

    if (NULL == pFlagsOfEvent)
    {
        return PlumaOS_Error;
    }

    //PlumaOS_EnterCritical(&regPrimask);
    *pFlagsOfEvent = pEventStruct->flags & flagsMask;
    //PlumaOS_ExitCritical(regPrimask);

    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param eventHandle
 * @param flagsToWait
 * @param waitAll
 * @param millisec
 * @param pSetFlags
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Event_Wait(PlumaOS_Handle_t eventHandle, event_flags_t flagsToWait, uint8_t waitAll, uint32_t millisec, event_flags_t *pSetFlags)
{
    event_t *pEventStruct;
    uint32_t regPrimask;
    PlumaOS_Sts_t retVal = PlumaOS_Idle;

    if (NULL == pSetFlags)
    {
        return PlumaOS_Error;
    }

    pEventStruct = (event_t *)eventHandle;

    //PlumaOS_EnterCritical(&regPrimask);
    *pSetFlags = pEventStruct->flags & flagsToWait;

    /* Check the event flag first, if does not meet wait condition, deal with timeout. */
    if (((0U == waitAll) && (0U != *pSetFlags)) || (*pSetFlags == flagsToWait))
    {
        pEventStruct->isWaiting = 0U;
        if (1U == pEventStruct->autoClear)
        {
            pEventStruct->flags &= ~flagsToWait;
        }
        retVal = PlumaOS_Success;
    }
    //PlumaOS_ExitCritical(regPrimask);

    return retVal;
}

/**
 * @brief
 *
 * @param eventHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Event_Destroy(PlumaOS_Handle_t eventHandle)
{
    event_t *pEventStruct = (event_t *)eventHandle;

    /* Destroy eventHandle's data */
    (void)memset(pEventStruct, 0, sizeof(event_t));

    return PlumaOS_Success;
}



#endif /* PLUMAOS_EVENT_C_ */
