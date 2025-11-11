/*
 * PlumaOS.c
 *
 *  Created on: 28/12/2021
 *      Author: Evandro Teixeira
 */

#include "PlumaOs.h"

/**
 * @brief Initializes the PlumaOS kernel and timer subsystems.
 * 
 * This function must be called before any other PlumaOS function.
 * It initializes the system timer and the kernel scheduler, preparing
 * the operating system for task management and scheduling.
 * 
 * @return void
 * 
 * @note Call this function once during system startup, before PlumaOS_StartScheduler().
 * 
 * @see Timer_Init()
 * @see Kernel_Init()
 */
void PlumaOS_Init(void)
{
	Timer_Init();
	Kernel_Init();
}


/**
 * @brief Disables global interrupts and saves the current interrupt state.
 * 
 * This static inline function disables all maskable interrupts by setting
 * the PRIMASK register on Cortex-M processors. It returns the previous
 * state of the PRIMASK register, allowing restoration later.
 * 
 * @return uint32_t The previous value of the PRIMASK register before disabling interrupts.
 * 
 * @note Used internally for critical section protection.
 * @warning Direct use of this function is not recommended. Use PlumaOS_EnterCritical() instead.
 * 
 * @see PlumaOS_EnableGlobalIRQ()
 * @see PlumaOS_EnterCritical()
 */
static inline uint32_t PlumaOS_DisableGlobalIRQ(void)
{
    uint32_t regPrimask = __get_PRIMASK();
    __disable_irq();
    return regPrimask;
}

/**
 * @brief Restores global interrupt state to a previously saved state.
 * 
 * This static inline function restores the interrupt enable/disable state
 * by writing back the PRIMASK register value. It should be used with a value
 * previously obtained from PlumaOS_DisableGlobalIRQ().
 * 
 * @param[in] primask The PRIMASK register value to restore. This value should
 *                    have been obtained from a previous call to PlumaOS_DisableGlobalIRQ().
 * 
 * @return void
 * 
 * @note Used internally for critical section protection.
 * @warning Direct use of this function is not recommended. Use PlumaOS_ExitCritical() instead.
 * 
 * @see PlumaOS_DisableGlobalIRQ()
 * @see PlumaOS_ExitCritical()
 */
static inline void PlumaOS_EnableGlobalIRQ(uint32_t primask)
{
    __enable_irq();
    __set_PRIMASK(primask);
}

/**
 * @brief Enters a critical section by disabling interrupts.
 * 
 * This function disables all maskable interrupts and saves the previous
 * interrupt state. The saved state must be restored by calling PlumaOS_ExitCritical()
 * with the same @p sr parameter to properly exit the critical section.
 * 
 * @param[out] sr Pointer to a variable where the current interrupt state will be saved.
 *                This value is used to restore the interrupt state later.
 * 
 * @return void
 * 
 * @note Critical sections should be kept as short as possible to minimize
 *       interrupt latency and ensure real-time responsiveness.
 * 
 * @warning Must be paired with a matching PlumaOS_ExitCritical() call.
 * 
 * @see PlumaOS_ExitCritical()
 * 
 * @par Example:
 * @code
 * uint32_t sr;
 * PlumaOS_EnterCritical(&sr);
 * // Protected code section
 * PlumaOS_ExitCritical(sr);
 * @endcode
 */
void PlumaOS_EnterCritical(uint32_t *sr)
{
    *sr = PlumaOS_DisableGlobalIRQ();
}

/**
 * @brief Exits a critical section by restoring the previous interrupt state.
 * 
 * This function restores the interrupt enable/disable state that was saved
 * by a previous call to PlumaOS_EnterCritical(). It should be called with
 * the exact @p sr value obtained from the matching PlumaOS_EnterCritical() call.
 * 
 * @param[in] sr The saved interrupt state to restore. This value should have been
 *               obtained from a previous call to PlumaOS_EnterCritical().
 * 
 * @return void
 * 
 * @note This function must always be paired with a corresponding PlumaOS_EnterCritical() call.
 * 
 * @warning Failure to properly match EnterCritical/ExitCritical pairs may result
 *          in unexpected interrupt behavior or system hang.
 * 
 * @see PlumaOS_EnterCritical()
 * 
 * @par Example:
 * @code
 * uint32_t sr;
 * PlumaOS_EnterCritical(&sr);
 * // Protected code section
 * PlumaOS_ExitCritical(sr);
 * @endcode
 */
void PlumaOS_ExitCritical(uint32_t sr)
{
    PlumaOS_EnableGlobalIRQ(sr);
}
