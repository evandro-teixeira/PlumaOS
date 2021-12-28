/*
 * Kernel.c
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#include "Kernel.h"
#include "List.h"
#include "Timer.h"


static PlumaOS_ptrTask_t idleTask;
static uint8_t idTask = 0;
static uint8_t idTaskIdle = 0xFF;
noList_t *kernel_list;


static void Kernel_TaskIdle(void);
static void Kernel_AddTaskIlde(PlumaOS_ptrTask_t task);
/**
 *
 */
static void Kernel_TaskIdle(void)
{
	if(idleTask != PlumaOS_Null)
	{
		idleTask();
	}
}

/**
 *
 */
static void Kernel_AddTaskIlde(PlumaOS_ptrTask_t task)
{
	if(task != PlumaOS_Null)
	{
		idleTask = task;
	}
}

/**
 * @brief
 *
 */
void Kernel_Init(void)
{
	strTask_t param;
	idTask = 0;
	kernel_list = List_Init();
	//idTaskIdle = Kernel_AddTask(Kernel_TaskIdle,PlumaOS_PriorityIdle,PlumaOS_TaskReady);
	idleTask = PlumaOS_Null;
	param.pausedtime = 0;
	param.Priority = PlumaOS_PriorityIdle;
	param.state = PlumaOS_TaskReady;
	param.task = Kernel_TaskIdle;
	param.task_status = PlumaOS_TaskWaiting;
	kernel_list = List_Insert(kernel_list,++idTask,param);
	idTaskIdle = idTask;
}

/**
 * @brief
 *
 */
void Kernel_StartScheduler(void)
{
	PlumaOS_ptrTask_t taskRun = {PlumaOS_Null};
	uint8_t index = 0;

	while (1)
	{
#if (KERNEL_TASK_CONTROL == KERNEL_ENABLE_TASK_CONTROL) /* Disabling Paused Task Control */
		// Check if there are any paused tasks
		for (index = 0; index < idTask; index++)
		{
			if (kernel_list->param.state == PlumaOS_TaskPaused)
			{
				if (kernel_list->param.pausedtime <= Timer_GetTicks())
				{
					kernel_list->param.state = PlumaOS_TaskReady;
				}
			}
			kernel_list = kernel_list->next;
		}
#endif /* endif ~ Disabling Paused Task Control */

		// high priority task search
		for (index = 1; index < (idTask + 1); index++)
		{
			if ((kernel_list->param.state == PlumaOS_TaskReady) &&
				(kernel_list->param.Priority == PlumaOS_PriorityHigh) &&
				(kernel_list->param.task_status == PlumaOS_TaskWaiting))
			{
				taskRun = kernel_list->param.task;
				kernel_list->param.task_status = PlumaOS_TaskRunning;
				break;
			}
			kernel_list = kernel_list->next;
		}

#if (KERNEL_TYPE_PRIORITY == KERNEL_PRIORITY_ACTIVE)

		if (index > idTask)
		{
			// Busca tarefa de media prioridade
			for (index = 1; index < (idTask + 1); index++)
			{
				if ((kernel_list->param.state == Task_Ready) &&
					(kernel_list->param.priority == Priority_Medium) &&
					(kernel_list->param.kernel_task_state == PlumaOS_TaskWaiting))
				{
					taskRun = kernel_list->param.task;
					kernel_list->param.kernel_task_state = PlumaOS_TaskRunning;
					break;
				}

				kernel_list = kernel_list->next;
			}
			if (index > idTask)
			{
				// Busca tarefa de baixa prioridade
				for (index = 1; index < (idTask + 1); index++)
				{
					if ((kernel_list->param.state == Task_Ready) &&
						(kernel_list->param.priority == Priority_Low) &&
						(kernel_list->param.kernel_task_state == PlumaOS_TaskWaiting))
					{
						taskRun = kernel_list->param.task;
						kernel_list->param.kernel_task_state = PlumaOS_TaskRunning;
						break;
					}

					kernel_list = kernel_list->next;
				}
				if (index > idTask)
				{
					// Busca tarefa de Idle
					for (index = 1; index < (idTask + 1); index++)
					{
						if ((kernel_list->param.state == Task_Ready) &&
							(kernel_list->param.priority == Priority_Idle) &&
							(kernel_list->param.kernel_task_state == PlumaOS_TaskWaiting))
						{
							taskRun = kernel_list->param.task;
							kernel_list->param.kernel_task_state = PlumaOS_TaskRunning;
							break;
						}

						kernel_list = kernel_list->next;
					}
					if (!(index > idTask))
					{
						kernel_list->param.kernel_task_state = PlumaOS_TaskWaiting;
					}
				}
				else
				{
					kernel_list->param.kernel_task_state = PlumaOS_TaskWaiting;
				}
			}
			else
			{
				kernel_list->param.kernel_task_state = PlumaOS_TaskWaiting;
			}
		}
		else
		{
			kernel_list->param.kernel_task_state = PlumaOS_TaskWaiting;
		}

#else /** else (KERNEL_TYPE_PRIORITY == KERNEL_PRIORITY_ACTIVE) */
		/** (KERNEL_TYPE_PRIORITY == KERNEL_PRIORITY_NOT_ACTIVE) */

		if (index > idTask)
		{
			// Idle Task Search
			for (index = 1; index < (idTask + 1); index++)
			{
				if ((kernel_list->param.state == PlumaOS_TaskReady) &&
					(kernel_list->param.Priority == PlumaOS_PriorityIdle) &&
					(kernel_list->param.task_status == PlumaOS_TaskWaiting))
				{
					taskRun = kernel_list->param.task;
					kernel_list->param.task_status = PlumaOS_TaskRunning;
					break;
				}
				kernel_list = kernel_list->next;
			}
			if (!(index > idTask))
			{
				kernel_list->param.task_status = PlumaOS_TaskWaiting;
			}
		}
		else
		{
			kernel_list->param.task_status = PlumaOS_TaskWaiting;
			kernel_list = kernel_list->next;
		}

#endif /* endif (KERNEL_TYPE_PRIORITY == KERNEL_PRIORITY_ACTIVE) */

		/** Run Task */
		if (taskRun != PlumaOS_Null)
		{
			taskRun();
		}
	}
}

/**
 *
 */
uint8_t Kernel_TaskAdd(PlumaOS_ptrTask_t task, PlumaOS_PriorityTask_t priority, PlumaOS_kernelTask_t state)
{
#if (!(KERNEL_TYPE_PRIORITY == KERNEL_PRIORITY_ACTIVE))
	if(priority != PlumaOS_PriorityIdle)
	{
		priority = PlumaOS_PriorityHigh;
	}
	else
	{
		if(idleTask != PlumaOS_Null)
		{
			/* The OS allows only one task with Idle priority */
			/* The Idle Task is the first task added in the OS. */
			priority = PlumaOS_PriorityHigh;
		}

	}
#else
	if((idleTask != PlumaOS_Null) && (priority == PlumaOS_PriorityIdle))
	{
		/* The OS allows only one task with Idle priority */
		/* The Idle Task is the first task added in the OS. */
		priority = PlumaOS_PriorityLow;
	}
#endif /** endif (KERNEL_TYPE_PRIORITY == KERNEL_PRIORITY_NOT_ACTIVE) */

	if((idleTask == PlumaOS_Null) && (priority == PlumaOS_PriorityIdle))
	{
		Kernel_AddTaskIlde(task);
		return idTaskIdle;
	}
	else
	{
		strTask_t param;
		param.pausedtime = 0;
		param.Priority = priority;
		param.state = state;
		param.task = task;
		param.task_status = PlumaOS_TaskWaiting;
		kernel_list = List_Insert(kernel_list,++idTask,param);
		return idTask;
	}
}

/**
 * @brief
 */
void Kernel_TaskDelete(uint8_t index)
{
	kernel_list = List_Remove(kernel_list,index,idTask);
}

/**
 *
 */
void Kernel_TaskDelay(uint8_t index, uint32_t tick)
{
	uint8_t i = 0;

	for(i=0;i<idTask;i++)
	{
		if(kernel_list->index == index)
		{
			kernel_list->param.pausedtime = tick + Timer_GetTicks();
			kernel_list->param.state = PlumaOS_TaskPaused;
			break;
		}
		kernel_list = kernel_list->next;
	}
}

/**
 *
 */
void Kernel_TaskBlocked(uint8_t index)
{
	uint8_t i = 0;

	for(i=0;i<idTask;i++)
	{
		if(kernel_list->index == index)
		{
			kernel_list->param.state = PlumaOS_TaskBlocked;
			break;
		}
		kernel_list = kernel_list->next;
	}
}

/**
 *
 */
void Kernel_TaskUnlocked(uint8_t index)
{
	uint8_t i = 0;

	for(i=0;i<idTask;i++)
	{
		if(kernel_list->index == index)
		{
			kernel_list->param.state = PlumaOS_TaskReady;
			break;
		}
		kernel_list = kernel_list->next;
	}
}
