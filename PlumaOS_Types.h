/*
 * Pluma_Types.h
 *
 *  Created on: 26/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_PLUMAOS_TYPES_H_
#define PLUMAOS_PLUMAOS_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/* Please include target microcontroller here */
#include "MKL25Z4.h"

typedef enum
{
	PlumaOS_Success = 0,
	PlumaOS_Error,
	PlumaOS_Timeout,
	PlumaOS_Idle
}PlumaOS_Sts_t;

typedef enum
{
	PlumaOS_TaskReady = 0,
	PlumaOS_TaskBlocked,
	PlumaOS_TaskPaused,
}PlumaOS_StateTask_t;

typedef enum
{
	PlumaOS_TaskRunning = true,
	PlumaOS_TaskWaiting = false
}PlumaOS_kernelTask_t;

typedef enum
{
	PlumaOS_PriorityIdle = 0,
	PlumaOS_PriorityLow,
	PlumaOS_PriorityNormal,
	PlumaOS_PriorityHigh
}PlumaOS_PriorityTask_t;


#ifndef PlumaOS_Null
#define PlumaOS_Null ((void *)0)
#endif

#ifndef PlumaOS_Handle_t
typedef void *PlumaOS_Handle_t;
#endif

#ifndef PlumaOS_ptrTask_t
typedef void(*PlumaOS_ptrTask_t)(void);
#endif


#define XOR_2(x,y)						((!x && y)||(x && !y))
#define XOR_3(x,y,z)					XOR_2(XOR_2(x,y),z)

#define KERNEL_PRIORITY_ACTIVE			0
#define KERNEL_PRIORITY_NOT_ACTIVE		1

#if XOR_2(KERNEL_PRIORITY_ACTIVE,KERNEL_PRIORITY_NOT_ACTIVE)

	#if KERNEL_PRIORITY_ACTIVE
		#define KERNEL_TYPE_PRIORITY 			KERNEL_PRIORITY_ACTIVE
	#endif
	#if KERNEL_PRIORITY_NOT_ACTIVE
		#define KERNEL_TYPE_PRIORITY 			KERNEL_PRIORITY_NOT_ACTIVE
	#endif

#else
	#define KERNEL_TYPE_PRIORITY 			KERNEL_PRIORITY_NOT_ACTIVE
#endif /*  XOR_2(KERNEL_PRIORITY_ACTIVE,KERNEL_PRIORITY_NOT_ACTIVE) */


#define KERNEL_DISABLE_TASK_CONTROL     0 // Disabling Paused Task Control
#define KERNEL_ENABLE_TASK_CONTROL      1 // Enabling Paused Task Control

#if XOR_2(KERNEL_DISABLE_TASK_CONTROL,KERNEL_ENABLE_TASK_CONTROL)

	#if KERNEL_DISABLE_TASK_CONTROL
		#define KERNEL_TASK_CONTROL     KERNEL_DISABLE_TASK_CONTROL 
	#endif 
	#if KERNEL_ENABLE_TASK_CONTROL
		#define KERNEL_TASK_CONTROL     KERNEL_ENABLE_TASK_CONTROL 
	#endif 
#else
	#define KERNEL_TASK_CONTROL        KERNEL_DISABLE_TASK_CONTROL
#endif /* XOR_2(KERNEL_DISABLE_TASK_CONTROL,KERNEL_ENABLE_TASK_CONTROL) */


#endif /* PLUMAOS_PLUMAOS_TYPES_H_ */
