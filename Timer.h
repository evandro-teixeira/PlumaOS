/*
 * Timer.h
 *
 *  Created on: 26/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_TIMER_H_
#define PLUMAOS_TIMER_H_

#include "PlumaOS_Types.h"

void Timer_Init(void);
uint32_t Timer_Diff(uint32_t time_start, uint32_t time_end);
void Timer_Delay(uint32_t ticks);
uint32_t Timer_GetTicks(void);


#endif /* PLUMAOS_TIMER_H_ */
