/*
 * Kernel.h
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_KERNEL_H_
#define PLUMAOS_KERNEL_H_


#include "PlumaOS_Types.h"


void Kernel_Init(void);
void Kernel_StartScheduler(void);
uint8_t Kernel_TaskAdd(PlumaOS_ptrTask_t task, PlumaOS_PriorityTask_t priority, PlumaOS_kernelTask_t state);
void Kernel_TaskDelete(uint8_t index);
void Kernel_TaskDelay(uint8_t index, uint32_t tick);
void Kernel_TaskBlocked(uint8_t index);
void Kernel_TaskUnlocked(uint8_t index);

#endif /* PLUMAOS_KERNEL_H_ */
