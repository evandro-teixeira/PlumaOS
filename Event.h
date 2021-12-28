/*
 * Event.h
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_EVENT_H_
#define PLUMAOS_EVENT_H_


#include "PlumaOS_Types.h"

typedef uint32_t event_flags_t;

PlumaOS_Sts_t Event_Create(PlumaOS_Handle_t eventHandle, uint8_t autoClear);
PlumaOS_Sts_t Event_Set(PlumaOS_Handle_t eventHandle, event_flags_t flagsToSet);
PlumaOS_Sts_t Event_Clear(PlumaOS_Handle_t eventHandle, event_flags_t flagsToClear);
PlumaOS_Sts_t Event_Get(PlumaOS_Handle_t eventHandle, event_flags_t flagsMask, event_flags_t *pFlagsOfEvent);
PlumaOS_Sts_t Event_Wait(PlumaOS_Handle_t eventHandle, event_flags_t flagsToWait, uint8_t waitAll, uint32_t millisec, event_flags_t *pSetFlags);
PlumaOS_Sts_t Event_Destroy(PlumaOS_Handle_t eventHandle);

#endif /* PLUMAOS_EVENT_H_ */
