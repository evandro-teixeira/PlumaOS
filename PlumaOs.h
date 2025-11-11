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

/**
 * @defgroup Timer_Macros Timer Management Macros
 * @{
 */

/**
 * @brief Calculates the time difference between two timestamps.
 * 
 * Computes the elapsed time in system ticks between @p time_start and @p time_end.
 * 
 * @param[in] time_start The starting timestamp in ticks.
 * @param[in] time_end   The ending timestamp in ticks.
 * 
 * @return uint32_t The time difference in system ticks.
 * 
 * @see Timer_Diff()
 */
#define PlumaOS_TimerDiff(time_start, time_end)     Timer_Diff(time_start, time_end)

/**
 * @brief Delays task execution for a specified number of system ticks.
 * 
 * Suspends the calling task for the specified number of system ticks,
 * allowing the scheduler to execute other ready tasks.
 * 
 * @param[in] ticks The number of system ticks to delay.
 * 
 * @return void
 * 
 * @see Timer_Delay()
 */
#define PlumaOS_TimerDelay(ticks)                   Timer_Delay(ticks)

/**
 * @brief Retrieves the current system tick counter.
 * 
 * Returns the current value of the system tick counter, which increments
 * with each system timer interrupt.
 * 
 * @return uint32_t The current system tick count.
 * 
 * @see Timer_GetTicks()
 */
#define PlumaOS_TimerGetTicks()                     Timer_GetTicks()

/** @} */

/**
 * @defgroup Semaphore_Macros Semaphore Management Macros
 * @{
 */

/**
 * @brief Creates a semaphore with an initial count value.
 * 
 * Initializes a new semaphore with the specified initial value.
 * The semaphore can be used to control access to shared resources.
 * 
 * @param[out] semaphoreHandle Pointer to the semaphore handle to initialize.
 * @param[in]  initValue       Initial counter value for the semaphore.
 * 
 * @return void
 * 
 * @see Semaphore_Create()
 */
#define PlumaOS_SemaphoreCreate(semaphoreHandle, initValue)     Semaphore_Create(semaphoreHandle, initValue)

/**
 * @brief Destroys a semaphore and releases its resources.
 * 
 * Terminates the semaphore and frees all associated memory.
 * 
 * @param[in] semaphoreHandle Pointer to the semaphore handle to destroy.
 * 
 * @return void
 * 
 * @see Semaphore_Destroy()
 */
#define PlumaOS_SemaphoreDestroy(semaphoreHandle)               Semaphore_Destroy(semaphoreHandle)

/**
 * @brief Waits for a semaphore to be signaled (blocking call).
 * 
 * Attempts to acquire the semaphore. If the semaphore count is greater than zero,
 * it decrements the count and returns immediately. Otherwise, the task blocks
 * until the semaphore is signaled by another task.
 * 
 * @param[in] semaphoreHandle Pointer to the semaphore handle.
 * 
 * @return void
 * 
 * @see Semaphore_Wait()
 */
#define PlumaOS_SemaphoreWait(semaphoreHandle)                  Semaphore_Wait(semaphoreHandle)

/**
 * @brief Signals a semaphore and wakes up waiting tasks.
 * 
 * Increments the semaphore counter and wakes up one waiting task if any are blocked.
 * 
 * @param[in] semaphoreHandle Pointer to the semaphore handle.
 * 
 * @return void
 * 
 * @see Semaphore_Post()
 */
#define PlumaOS_SemaphorePost(semaphoreHandle)                  Semaphore_Post(semaphoreHandle)

/** @} */

/**
 * @defgroup MsgQueue_Macros Message Queue Management Macros
 * @{
 */

/**
 * @brief Creates a message queue with specified capacity and message size.
 * 
 * Initializes a new FIFO message queue that can hold up to @p msgNo messages,
 * each of size @p msgSize bytes.
 * 
 * @param[out] msgHandle Pointer to the message queue handle to initialize.
 * @param[in]  msgNo     Maximum number of messages the queue can hold.
 * @param[in]  msgSize   Size of each message in bytes.
 * 
 * @return void
 * 
 * @see MsgQueue_Create()
 */
#define PlumaOS_MsgQueueCreate(msgHandle, msgNo, msgSize)   MsgQueue_Create(msgHandle, msgNo, msgSize)

/**
 * @brief Puts a message into the message queue (non-blocking).
 * 
 * Adds a message to the rear of the FIFO queue. If the queue is full,
 * the behavior depends on the queue implementation.
 * 
 * @param[in] msgHandle Pointer to the message queue handle.
 * @param[in] pMessage  Pointer to the message data to be sent.
 * 
 * @return void
 * 
 * @see MsgQueue_Put()
 */
#define PlumaOS_MsgQueuePut(msgHandle, pMessage)            MsgQueue_Put(msgHandle, pMessage)

/**
 * @brief Retrieves a message from the message queue (blocking).
 * 
 * Removes and returns the first message from the FIFO queue.
 * If the queue is empty, the calling task blocks until a message becomes available.
 * 
 * @param[in]  msgHandle Pointer to the message queue handle.
 * @param[out] pMessage  Pointer to buffer where the received message will be stored.
 * 
 * @return void
 * 
 * @see MsgQueue_Get()
 */
#define PlumaOS_MsgQueueGet(msgHandle, pMessage)            MsgQueue_Get(msgHandle, pMessage)

/**
 * @brief Returns the number of available messages in the queue.
 * 
 * Queries the current number of messages waiting in the message queue.
 * 
 * @param[in] msgHandle Pointer to the message queue handle.
 * 
 * @return uint32_t The number of messages currently in the queue.
 * 
 * @see MsgQueue_AvailableMsgs()
 */
#define PlumaOS_MsgQueueAvailableMsgs(msgHandle)            MsgQueue_AvailableMsgs(msgHandle)

/**
 * @brief Destroys a message queue and releases its resources.
 * 
 * Terminates the message queue and frees all associated memory.
 * Any tasks blocked on this queue will be awakened.
 * 
 * @param[in] msgHandle Pointer to the message queue handle to destroy.
 * 
 * @return void
 * 
 * @see MsgQueue_Destroy()
 */
#define PlumaOS_MsgQueueDestroy(msgHandle)                  MsgQueue_Destroy(msgHandle)

/** @} */

/**
 * @defgroup Event_Macros Event Management Macros
 * @{
 */

/**
 * @brief Creates an event with automatic or manual flag clearing.
 * 
 * Initializes a new event object for inter-task synchronization.
 * 
 * @param[out] eventHandle Pointer to the event handle to initialize.
 * @param[in]  autoClear   TRUE for auto-clear mode (flags clear automatically after tasks wake),
 *                         FALSE for manual-clear mode (flags persist until explicitly cleared).
 * 
 * @return void
 * 
 * @see Event_Create()
 */
#define PlumaOS_EventCreate(eventHandle, autoClear)                                 Event_Create(eventHandle, autoClear)

/**
 * @brief Sets (signals) event flags and wakes waiting tasks.
 * 
 * Sets the specified event flags, awakening any tasks waiting for those flags.
 * 
 * @param[in] eventHandle Pointer to the event handle.
 * @param[in] flagsToSet  Bitmask of flags to set (OR combination of flag bits).
 * 
 * @return void
 * 
 * @see Event_Set()
 */
#define PlumaOS_EventSet(eventHandle, flagsToSet)                                   Event_Set(eventHandle, flagsToSet)

/**
 * @brief Clears (resets) event flags.
 * 
 * Clears the specified event flags. This is typically used in manual-clear mode.
 * 
 * @param[in] eventHandle   Pointer to the event handle.
 * @param[in] flagsToClear  Bitmask of flags to clear (OR combination of flag bits).
 * 
 * @return void
 * 
 * @see Event_Clear()
 */
#define PlumaOS_EventClear(eventHandle, flagsToClear)                               Event_Clear(eventHandle, flagsToClear)

/**
 * @brief Retrieves the current state of event flags without blocking.
 * 
 * Queries the current state of event flags without causing the task to block.
 * 
 * @param[in]  eventHandle     Pointer to the event handle.
 * @param[in]  flagsMask       Bitmask of flags to query.
 * @param[out] pFlagsOfEvent   Pointer to variable where current flag state is stored.
 * 
 * @return void
 * 
 * @see Event_Get()
 */
#define PlumaOS_EventGet(eventHandle, flagsMask, pFlagsOfEvent)                     Event_Get(eventHandle, flagsMask, pFlagsOfEvent)

/**
 * @brief Waits for one or more event flags to be set (blocking).
 * 
 * Blocks the calling task until the specified event flags are set.
 * 
 * @param[in]  eventHandle   Pointer to the event handle.
 * @param[in]  flagsToWait   Bitmask of flags to wait for (OR combination of flag bits).
 * @param[in]  waitAll       TRUE to wait for ALL specified flags, FALSE to wait for ANY flag.
 * @param[in]  millisec      Timeout in milliseconds (0 means wait indefinitely).
 * @param[out] pSetFlags     Pointer to variable where the flags that woke the task are stored.
 * 
 * @return void
 * 
 * @see Event_Wait()
 */
#define PlumaOS_EventWait(eventHandle, flagsToWait, waitAll, millisec, pSetFlags)   Event_Wait(eventHandle, flagsToWait, waitAll, millisec, pSetFlags)

/**
 * @brief Destroys an event object and releases its resources.
 * 
 * Terminates the event and frees all associated memory.
 * Any tasks blocked on this event will be awakened.
 * 
 * @param[in] eventHandle Pointer to the event handle to destroy.
 * 
 * @return void
 * 
 * @see Event_Destroy()
 */
#define PlumaOS_EventDestroy(eventHandle)                                           Event_Destroy(eventHandle)

/** @} */

/**
 * @defgroup Mutex_Macros Mutex Management Macros
 * @{
 */

/**
 * @brief Creates a mutex for mutual exclusion.
 * 
 * Initializes a new mutex object for protecting shared resources from concurrent access.
 * 
 * @param[out] mutexHandle Pointer to the mutex handle to initialize.
 * 
 * @return void
 * 
 * @see Mutex_Create()
 */
#define PlumaOS_MutexCreate(mutexHandle)    Mutex_Create(mutexHandle)

/**
 * @brief Locks a mutex (blocking call).
 * 
 * Acquires exclusive ownership of the mutex. If the mutex is already owned by another task,
 * the calling task blocks until the mutex is released.
 * 
 * @param[in] mutexHandle Pointer to the mutex handle.
 * 
 * @return void
 * 
 * @see Mutex_Lock()
 */
#define PlumaOS_MutexLock(mutexHandle)      Mutex_Lock(mutexHandle)

/**
 * @brief Unlocks a mutex and allows other tasks to acquire it.
 * 
 * Releases exclusive ownership of the mutex. If tasks are waiting for this mutex,
 * the highest priority waiting task will acquire it.
 * 
 * @param[in] mutexHandle Pointer to the mutex handle.
 * 
 * @return void
 * 
 * @see Mutex_Unlock()
 */
#define PlumaOS_MutexUnlock(mutexHandle)    Mutex_Unlock(mutexHandle)

/**
 * @brief Destroys a mutex and releases its resources.
 * 
 * Terminates the mutex and frees all associated memory.
 * Any tasks blocked on this mutex will be awakened.
 * 
 * @param[in] mutexHandle Pointer to the mutex handle to destroy.
 * 
 * @return void
 * 
 * @see Mutex_Destroy()
 */
#define PlumaOS_MutexDestroy(mutexHandle)   Mutex_Destroy(mutexHandle)

/** @} */

/**
 * @defgroup Kernel_Macros Kernel and Task Management Macros
 * @{
 */

/**
 * @brief Starts the kernel scheduler and begins task execution.
 * 
 * Initializes the scheduler and starts executing tasks based on priority.
 * This function typically does not return unless the system is halted.
 * 
 * @return void
 * 
 * @note This function should be called after all tasks have been added via PlumaOS_TaskAdd().
 * 
 * @see Kernel_StartScheduler()
 */
#define PlumaOS_StartScheduler()                Kernel_StartScheduler()

/**
 * @brief Adds a new task to the kernel scheduler.
 * 
 * Creates and adds a task with the specified priority and initial state.
 * The task will be managed by the scheduler.
 * 
 * @param[in] task     Pointer to the task function to execute.
 * @param[in] priority Priority level of the task (e.g., PRIORITY_LOW, PRIORITY_NORMAL, PRIORITY_HIGH).
 * @param[in] state    Initial state of the task (e.g., TASK_READY, TASK_BLOCKED).
 * 
 * @return void
 * 
 * @see Kernel_TaskAdd()
 */
#define PlumaOS_TaskAdd(task, priority, state)  Kernel_TaskAdd(task , priority, state)

/**
 * @brief Deletes a task and removes it from the scheduler.
 * 
 * Terminates a task and removes it from the ready queue. The task ID becomes invalid
 * after this call.
 * 
 * @param[in] idTask The ID of the task to delete.
 * 
 * @return void
 * 
 * @see Kernel_TaskDelete()
 */
#define PlumaOS_TaskDelete(idTask)              Kernel_TaskDelete(idTask)

/**
 * @brief Delays a specific task execution for a specified time.
 * 
 * Suspends the specified task for the given number of system ticks.
 * The task will be automatically moved to the ready state when the delay expires.
 * 
 * @param[in] idTask Task ID of the task to delay.
 * @param[in] tick   Number of system ticks to delay.
 * 
 * @return void
 * 
 * @see Kernel_TaskDelay()
 */
#define PlumaOS_TaskDelay(idTask,tick)          Kernel_TaskDelay(idTask,tick)

/**
 * @brief Blocks a task, removing it from the ready queue.
 * 
 * Transitions a task to the blocked state. The task will not be scheduled
 * until it is explicitly unblocked.
 * 
 * @param[in] idTask The ID of the task to block.
 * 
 * @return void
 * 
 * @see Kernel_TaskBlocked()
 */
#define PlumaOS_TaskBlocked(idTask)             Kernel_TaskBlocked(idTask)

/**
 * @brief Unblocks a task, moving it to the ready queue.
 * 
 * Transitions a task from the blocked state back to the ready state,
 * allowing it to be scheduled again.
 * 
 * @param[in] idTask The ID of the task to unblock.
 * 
 * @return void
 * 
 * @see Kernel_TaskUnlocked()
 */
#define PlumaOS_TaskUnlocked(idTask)            Kernel_TaskUnlocked(idTask)

/**
 * @brief Initializes the PlumaOS kernel and timer subsystems.
 * 
 * This function must be called before any other PlumaOS function.
 * It initializes the system timer and the kernel scheduler, preparing
 * the operating system for task management and scheduling.
 * 
 * @return void
 * 
 * @note Call this function once during system startup, before PlumaOS_StartScheduler().
 * 
 * @see Timer_Init()
 * @see Kernel_Init()
 */
void PlumaOS_Init(void);

/**
 * @brief Enters a critical section by disabling interrupts.
 * 
 * This function disables all maskable interrupts and saves the previous
 * interrupt state. The saved state must be restored by calling PlumaOS_ExitCritical()
 * with the same @p sr parameter to properly exit the critical section.
 * 
 * @param[out] sr Pointer to a variable where the current interrupt state will be saved.
 *                This value is used to restore the interrupt state later.
 * 
 * @return void
 * 
 * @note Critical sections should be kept as short as possible to minimize
 *       interrupt latency and ensure real-time responsiveness.
 * 
 * @warning Must be paired with a matching PlumaOS_ExitCritical() call.
 * 
 * @see PlumaOS_ExitCritical()
 * 
 * @par Example:
 * @code
 * uint32_t sr;
 * PlumaOS_EnterCritical(&sr);
 * // Protected code section
 * PlumaOS_ExitCritical(sr);
 * @endcode
 */
void PlumaOS_EnterCritical(uint32_t *sr);

/**
 * @brief Exits a critical section by restoring the previous interrupt state.
 * 
 * This function restores the interrupt enable/disable state that was saved
 * by a previous call to PlumaOS_EnterCritical(). It should be called with
 * the exact @p sr value obtained from the matching PlumaOS_EnterCritical() call.
 * 
 * @param[in] sr The saved interrupt state to restore. This value should have been
 *               obtained from a previous call to PlumaOS_EnterCritical().
 * 
 * @return void
 * 
 * @note This function must always be paired with a corresponding PlumaOS_EnterCritical() call.
 * 
 * @warning Failure to properly match EnterCritical/ExitCritical pairs may result
 *          in unexpected interrupt behavior or system hang.
 * 
 * @see PlumaOS_EnterCritical()
 * 
 * @par Example:
 * @code
 * uint32_t sr;
 * PlumaOS_EnterCritical(&sr);
 * // Protected code section
 * PlumaOS_ExitCritical(sr);
 * @endcode
 */
void PlumaOS_ExitCritical(uint32_t sr);

#endif /* PLUMAOS_PLUMAOS_H_ */
