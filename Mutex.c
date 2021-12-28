/*
 * Mutex.c
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#include "Mutex.h"


typedef struct
{
    uint32_t time_start;
    uint32_t timeout;
    volatile uint8_t isWaiting;
    volatile uint8_t isLocked;
} mutex_t;


/**
 * @brief
 *
 * @param mutexHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Mutex_Create(PlumaOS_Handle_t mutexHandle)
{
    mutex_t *pMutexStruct = (mutex_t *)mutexHandle;

    pMutexStruct->isLocked = 0U;
    pMutexStruct->isWaiting = 0U;
    pMutexStruct->time_start = 0u;
    pMutexStruct->timeout = 0u;
    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param mutexHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Mutex_Lock(PlumaOS_Handle_t mutexHandle)
{
    mutex_t *pMutexStruct = (mutex_t *)mutexHandle;
    uint32_t regPrimask;

    if (0U == pMutexStruct->isLocked)
    {
        //PlumaOS_EnterCritical(&regPrimask);
        pMutexStruct->isLocked = 1U;
        pMutexStruct->isWaiting = 0U;
        //PlumaOS_ExitCritical(regPrimask);
        return PlumaOS_Success;
    }
    else return PlumaOS_Idle;
}

/**
 * @brief
 *
 * @param mutexHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Mutex_Unlock(PlumaOS_Handle_t mutexHandle)
{
    mutex_t *pMutexStruct = (mutex_t *)mutexHandle;
    uint32_t regPrimask;

    //PlumaOS_EnterCritical(&regPrimask);
    pMutexStruct->isLocked = 0U;
    //PlumaOS_ExitCritical(regPrimask);
    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param mutexHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t Mutex_Destroy(PlumaOS_Handle_t mutexHandle)
{
    mutex_t *pMutexStruct = (mutex_t *)mutexHandle;
    /* Destory mutexHandle's data */
    (void)memset(pMutexStruct, 0, sizeof(mutex_t));

    return PlumaOS_Success;
}
