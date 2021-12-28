/*
 * Mutex.h
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_MUTEX_H_
#define PLUMAOS_MUTEX_H_


#include "PlumaOS_Types.h"



PlumaOS_Sts_t Mutex_Create(PlumaOS_Handle_t mutexHandle);
PlumaOS_Sts_t Mutex_Lock(PlumaOS_Handle_t mutexHandle);
PlumaOS_Sts_t Mutex_Unlock(PlumaOS_Handle_t mutexHandle);
PlumaOS_Sts_t Mutex_Destroy(PlumaOS_Handle_t mutexHandle);


#endif /* PLUMAOS_MUTEX_H_ */
