/*
 * PlumaOs.h
 *
 *  Created on: 26/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_PLUMAOS_H_
#define PLUMAOS_PLUMAOS_H_


#include "Timer.h"
#include "Semaphore.h"
#include "MsgQueue.h"
#include "Event.h"
#include "Mutex.h"
#include "PlumaOS_Types.h"
#include "Kernel.h"


//#define PlumaOS_TimerInit()                       Timer_Init()
#define PlumaOS_TimerDiff(time_start, time_end)     Timer_Diff(time_start, time_end)
#define PlumaOS_TimerDelay(ticks)                   Timer_Delay(ticks)
#define PlumaOS_TimerGetTicks()                     Timer_GetTicks()


#define PlumaOS_SemaphoreCreate(semaphoreHandle, initValue)     Semaphore_Create(semaphoreHandle, initValue)
#define PlumaOS_SemaphoreDestroy(semaphoreHandle)               Semaphore_Destroy(semaphoreHandle)
#define PlumaOS_SemaphoreWait(semaphoreHandle)                  Semaphore_Wait(semaphoreHandle)
#define PlumaOS_SemaphorePost(semaphoreHandle)                  Semaphore_Post(semaphoreHandle)


#define PlumaOS_MsgQueueCreate(msgHandle, msgNo, msgSize)   MsgQueue_Create(msgHandle, msgNo, msgSize)
#define PlumaOS_MsgQueuePut(msgHandle, pMessage)            MsgQueue_Put(msgHandle, pMessage)
#define PlumaOS_MsgQueueGet(msgHandle, pMessage)            MsgQueue_Get(msgHandle, pMessage)
#define PlumaOS_MsgQueueAvailableMsgs(msgHandle)            MsgQueue_AvailableMsgs(msgHandle)
#define PlumaOS_MsgQueueDestroy(msgHandle)                  MsgQueue_Destroy(msgHandle)


#define PlumaOS_EventCreate(eventHandle, autoClear)                                 Event_Create(eventHandle, autoClear)
#define PlumaOS_EventSet(eventHandle, flagsToSet)                                   Event_Set(eventHandle, flagsToSet)
#define PlumaOS_EventClear(eventHandle, flagsToClear)                               Event_Clear(eventHandle, flagsToClear)
#define PlumaOS_EventGet(eventHandle, flagsMask, pFlagsOfEvent)                     Event_Get(eventHandle, flagsMask, pFlagsOfEvent)
#define PlumaOS_EventWait(eventHandle, flagsToWait, waitAll, millisec, pSetFlags)   Event_Wait(eventHandle, flagsToWait, waitAll, millisec, pSetFlags)
#define PlumaOS_EventDestroy(eventHandle)                                           Event_Destroy(eventHandle)


#define PlumaOS_MutexCreate(mutexHandle)    Mutex_Create(mutexHandle)
#define PlumaOS_MutexLock(mutexHandle)      Mutex_Lock(mutexHandle)
#define PlumaOS_MutexUnlock(mutexHandle)    Mutex_Unlock(mutexHandle)
#define PlumaOS_MutexDestroy(mutexHandle)   Mutex_Destroy(mutexHandle)


#define PlumaOS_StartScheduler()                Kernel_StartScheduler()


#define PlumaOS_TaskAdd(task, priority, state)  Kernel_TaskAdd(task , priority, state)
#define PlumaOS_TaskDelete(idTask)              Kernel_TaskDelete(idTask)
#define PlumaOS_TaskDelay(idTask,tick)          Kernel_TaskDelay(idTask,tick)
#define PlumaOS_TaskBlocked(idTask)             Kernel_TaskBlocked(idTask)
#define PlumaOS_TaskUnlocked(idTask)            Kernel_TaskUnlocked(idTask)


void PlumaOS_Init(void);

void PlumaOS_EnterCritical(uint32_t *sr);
void PlumaOS_ExitCritical(uint32_t sr);

#endif /* PLUMAOS_PLUMAOS_H_ */
