/*
 * PlumaOS.c
 *
 *  Created on: 28/12/2021
 *      Author: Evandro Teixeira
 */

#include "PlumaOs.h"

/**
 * @brief
 *
 */
void PlumaOS_Init(void)
{
	Timer_Init();
	Kernel_Init();
}


/**
 * @brief
 *
 * @return uint32_t
 */
static inline uint32_t PlumaOS_DisableGlobalIRQ(void)
{
    uint32_t regPrimask = __get_PRIMASK();
    __disable_irq();
    return regPrimask;
}

/**
 * @brief
 *
 * @param primask
 */
static inline void PlumaOS_EnableGlobalIRQ(uint32_t primask)
{
    __enable_irq();
    __set_PRIMASK(primask);
}

/**
 * @brief
 *
 * @param sr
 */
void PlumaOS_EnterCritical(uint32_t *sr)
{
    *sr = PlumaOS_DisableGlobalIRQ();
}

/**
 * @brief
 *
 * @param sr
 */
void PlumaOS_ExitCritical(uint32_t sr)
{
    PlumaOS_EnableGlobalIRQ(sr);
}
