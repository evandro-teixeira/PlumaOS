/*
 * Semaphore.h
 *
 *  Created on: 26/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_SEMAPHORE_H_
#define PLUMAOS_SEMAPHORE_H_

#include "PlumaOS_Types.h"

PlumaOS_Sts_t Semaphore_Create(PlumaOS_Handle_t semaphoreHandle, uint32_t initValue);
PlumaOS_Sts_t Semaphore_Destroy(PlumaOS_Handle_t semaphoreHandle);
PlumaOS_Sts_t Semaphore_Wait(PlumaOS_Handle_t semaphoreHandle);
PlumaOS_Sts_t Semaphore_Post(PlumaOS_Handle_t semaphoreHandle);

#endif /* PLUMAOS_SEMAPHORE_H_ */
