/*
 * Timer.c
 *
 *  Created on: 26/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_TIMER_C_
#define PLUMAOS_TIMER_C_

#include "Timer.h"

#define TIME_RANGE 0xFFFFFFFFU

uint32_t Ticks;

/**
 * @brief
 *
 */
void SysTick_Handler(void)
{
    Ticks++;
}

/**
 * @brief
 *
 */
void Timer_Init(void)
{
	SystemCoreClockUpdate();
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
    SysTick->LOAD = (uint32_t)(SystemCoreClock / 1000U - 1U);
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    Ticks = 0;
}

/**
 * @brief
 *
 * @param time_start
 * @param time_end
 * @return uint32_t
 */
uint32_t Timer_Diff(uint32_t time_start, uint32_t time_end)
{
    if (time_end >= time_start)
    {
        return time_end - time_start;
    }
    else
    {
        return TIME_RANGE - time_start + time_end + 1UL;
    }
}

/**
 * @brief
 *
 * @param ticks
 */
void Timer_Delay(uint32_t ticks)
{
    uint32_t currTime, timeStart;
    timeStart = Timer_GetTicks();

    do
    {
        currTime = Timer_GetTicks(); /* Get current time stamp */
    } while (ticks >= Timer_Diff(timeStart, currTime));
}

/**
 * @brief
 *
 * @return uint32_t
 */
uint32_t Timer_GetTicks(void)
{
    return Ticks;
}



#endif /* PLUMAOS_TIMER_C_ */
