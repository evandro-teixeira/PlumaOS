/*
 * MsgQueue.c
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#include "MsgQueue.h"


typedef struct
{
    volatile uint8_t isWaiting;
    uint32_t time_start;
    uint32_t timeout;
    uint32_t size;
    uint8_t *queueMem;
    uint16_t number;
    uint16_t max;
    uint16_t head;
    uint16_t tail;
} msg_queue_t;


/**
 * @brief
 *
 * @param msgqHandle
 * @param msgNo
 * @param msgSize
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t MsgQueue_Create(PlumaOS_Handle_t msgHandle, uint32_t msgNo, uint32_t msgSize)
{
    msg_queue_t *pMsgQStruct = msgHandle;

    pMsgQStruct->max = (uint16_t)msgNo;
    pMsgQStruct->number = 0;
    pMsgQStruct->head = 0;
    pMsgQStruct->tail = 0;
    pMsgQStruct->size = msgSize;
    pMsgQStruct->queueMem = (uint8_t *)((uint8_t *)msgHandle + sizeof(msg_queue_t));
    return PlumaOS_Success;
}

/**
 * @brief
 *
 * @param msgqHandle
 * @param pMessage
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t MsgQueue_Put(PlumaOS_Handle_t msgHandle, void *pMessage)
{
    msg_queue_t *pQueue;
    PlumaOS_Sts_t status = PlumaOS_Success;
    uint32_t regPrimask;
    uint8_t *pMsgArray;

    pQueue = (msg_queue_t *)msgHandle;

    if (NULL == pQueue->queueMem)
    {
        return PlumaOS_Error;
    }

    PlumaOS_EnterCritical(&regPrimask);
    if (pQueue->number >= pQueue->max)
    {
        status = PlumaOS_Error;
    }
    else
    {
        pMsgArray = &pQueue->queueMem[pQueue->tail];
        for (uint32_t i = 0; i < pQueue->size; i++)
        {
            pMsgArray[i] = *((uint8_t *)pMessage + i);
        }

        pQueue->number++;
        pQueue->tail += (uint16_t)pQueue->size;

        if (pQueue->tail >= (pQueue->max * pQueue->size))
        {
            pQueue->tail = 0;
        }
    }
    PlumaOS_ExitCritical(regPrimask);
    return status;
}

/**
 * @brief
 *
 * @param msgqHandle
 * @param pMessage
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t MsgQueue_Get(PlumaOS_Handle_t msgHandle, void *pMessage)
{
    msg_queue_t *pQueue;
    PlumaOS_Sts_t status = PlumaOS_Success;
    uint32_t regPrimask;
    uint8_t *pMsgArray;

    pQueue = (msg_queue_t *)msgHandle;

    if (NULL == pQueue->queueMem)
    {
        return PlumaOS_Error;
    }

    PlumaOS_EnterCritical(&regPrimask);
    if (0U != pQueue->number)
    {
        pMsgArray = (uint8_t *)pMessage;
        for (uint32_t i = 0; i < pQueue->size; i++)
        {
            pMsgArray[i] = pQueue->queueMem[pQueue->head + i];
        }

        pQueue->number--;
        pQueue->head += (uint16_t)pQueue->size;
        pQueue->isWaiting = 0U;

        if (pQueue->head >= (pQueue->max * pQueue->size))
        {
            pQueue->head = 0;
        }
        status = PlumaOS_Success;
    }
    PlumaOS_ExitCritical(regPrimask);

    return status;
}

/**
 * @brief
 *
 * @param msgqHandle
 * @return uint16_t
 */
uint16_t MsgQueue_AvailableMsgs(PlumaOS_Handle_t msgHandle)
{
    msg_queue_t *pQueue = (msg_queue_t *)msgHandle;

    return (int)pQueue->number;
}

/**
 * @brief
 *
 * @param msgqHandle
 * @return PlumaOS_Sts_t
 */
PlumaOS_Sts_t MsgQueue_Destroy(PlumaOS_Handle_t msgHandle)
{
    msg_queue_t *pQueue = (msg_queue_t *)msgHandle;
    (void)memset(pQueue, 0, sizeof(msg_queue_t));

    return PlumaOS_Success;
}



