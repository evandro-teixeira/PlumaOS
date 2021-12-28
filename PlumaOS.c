/*
 * PlumaOS.c
 *
 *  Created on: 28/12/2021
 *      Author: Evandro Teixeira
 */

#include "PlumaOs.h"

/**
 *
 */
void PlumaOS_Init(void)
{
	Timer_Init();
	Kernel_Init();
}

