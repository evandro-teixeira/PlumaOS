/*
 * Semaphore.c
 *
 *  Created on: 26/12/2021
 *      Author: Evandro Teixeira
 */

#include "Semaphore.h"

#define MAX_VALUE 0xFF // max value

typedef struct
{
    uint32_t time_start;
    uint32_t timeout;
    volatile uint8_t isWaiting;
    volatile uint8_t semCount;
} semaphore_t;

/**
 * @brief
 *
 * @param semaphoreHandle
 * @param initValue
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Semaphore_Create(PlumaOS_Handle_t semaphoreHandle, uint32_t initValue)
{
    semaphore_t *pSemStruct = (semaphore_t *)semaphoreHandle;

    pSemStruct->semCount = (uint8_t)initValue;
    pSemStruct->isWaiting = 0U;
    pSemStruct->time_start = 0U;
    pSemStruct->timeout = 0U;
    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param semaphoreHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Semaphore_Destroy(PlumaOS_Handle_t semaphoreHandle)
{
    semaphore_t *pSemStruct = (semaphore_t *)semaphoreHandle;
    (void)memset(pSemStruct, 0, sizeof(semaphore_t));

    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param semaphoreHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Semaphore_Wait(PlumaOS_Handle_t semaphoreHandle /*, uint32_t millisec*/)
{
    semaphore_t *pSemStruct = (semaphore_t *)semaphoreHandle;
    uint32_t regPrimask;

    if (0U != pSemStruct->semCount)
    {
        PlumaOS_EnterCritical(&regPrimask);
        pSemStruct->semCount--;
        pSemStruct->isWaiting = 0U;
        PlumaOS_ExitCritical(regPrimask);
        return PlumaOS_Success;
    }
    return PlumaOS_Idle;
}

/**
 * @brief
 *
 * @param semaphoreHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Semaphore_Post(PlumaOS_Handle_t semaphoreHandle)
{
    semaphore_t *pSemStruct = (semaphore_t *)semaphoreHandle;
    uint32_t regPrimask;

    if (MAX_VALUE == pSemStruct->semCount)
    {
        return PlumaOS_Error;
    }
    PlumaOS_EnterCritical(&regPrimask);
    ++pSemStruct->semCount;
    PlumaOS_ExitCritical(regPrimask);

    return PlumaOS_Success;
}
