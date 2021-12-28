/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "../PlumaOS/PlumaOs.h"
#include "../Drivers/gpio.h"

#define LED_RED     GPIOB,18
#define LED_GREEN   GPIOB,19
#define SETUP		0
#define LOOP  		1


void task_led_red(void);
void task_led_green(void);

uint8_t IdTaskRed = 0;
uint8_t IdTaskGreen = 0;

int main(void)
{
    /* Write your code here */
    /* This for loop should be replaced. By default this loop allows a single stepping. */
    PlumaOS_Init();

    IdTaskRed = PlumaOS_TaskAdd(task_led_red,PlumaOS_PriorityNormal,PlumaOS_TaskReady);
    IdTaskGreen = PlumaOS_TaskAdd(task_led_green,PlumaOS_PriorityNormal,PlumaOS_TaskReady);

    PlumaOS_StartScheduler();

    for (;;)
    {

    }
    /* Never leave main */
    return 0;
}

void task_led_red(void)
{
    static uint8_t state = 0;
    static uint32_t ticks = 0;

    switch(state)
    {
        case 0:
            gpio_Init(LED_RED,OUTPUT,NO_PULL_RESISTOR);
            gpio_Set(LED_RED,HIGH);
            state = 1;
        break;
        case 2:
        default:
            if(PlumaOS_TimerDiff(PlumaOS_TimerGetTicks(),ticks) < 1)
            {
                state = 1;
            }
        break;
        case 1:
            gpio_Toggle(LED_RED);
            ticks = PlumaOS_TimerGetTicks() + 1000;
            state = 2;
        break;
    }
}

void task_led_green(void)
{
    static uint8_t state = 0;

    switch(state)
    {
        case SETUP:
        {
            gpio_Init(LED_GREEN,OUTPUT,NO_PULL_RESISTOR);
            gpio_Set(LED_GREEN,LOW);
            state = 1;
        }
        break;
        case LOOP:
        default:
        {
            gpio_Toggle(LED_GREEN);
            PlumaOS_TaskDelay(IdTaskGreen,1000);
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
