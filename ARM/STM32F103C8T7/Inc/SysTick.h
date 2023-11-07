/******************************************************************
 * @Title    : System Tick Driver Header
 * @Filename : SysTick.h
 * @Author   : Hossam Mohamed
 * @Compiler : 
 * @Target   : 
 ********************************************************************/
#ifndef SYS_TICK_H_
#define SYS_TICK_H_

#include "BIT_MACROS.h"
#include "STD_TYPES.h"

typedef enum
{
	AHB_8 = 0,
	PROCESSOR_CLOCK = 1 // (AHB)
} SysTick_CLKSOURCE;

typedef enum
{
	INT_DISABLE = 0,
	INT_ENABLE = 1
} SysTick_INT;

// configuration type
typedef struct
{
	SysTick_CLKSOURCE ClkSrc;
	SysTick_INT		  Int;
	uint32			  ReloadValue;
} SysTick_ConfigType;

/**
 * @brief Initialize the SysTick timer with the specified configuration.
 *
 * This function initializes the SysTick timer with the provided configuration settings.
 * It allows you to specify the clock source, reload value, and interrupt enable/disable
 * for the SysTick timer.
 *
 * @param Config_Ptr A pointer to a SysTick_ConfigType structure containing the
 *                   configuration settings for the SysTick timer.
 *
 * @note This function assumes that the SysTick timer is correctly set up in the hardware.
 *       Ensure that the clock source, reload value, and interrupt settings are compatible
 *       with the hardware and application requirements.
 *
 * @param[in] Config_Ptr Pointer to the configuration structure.
 *
 * @see SysTick_CLKSOURCE
 * @see SysTick_INT
 *
 * @return None
 */
void SysTick_init(SysTick_ConfigType* Config_Ptr);

/**
 * @brief Set the SysTick timer priority.
 *
 * This function sets the SysTick timer priority.
 *
 * @param ExceptionPriority The priority for the SysTick timer interrupt.
 *
 * @note This function assumes that the SysTick timer is correctly set up in the hardware.
 *       Ensure that the SysTick timer interrupt is enabled in the NVIC.
 *
 * @note This function should be called after SysTick_init() function.
 *
 * @return None
 */
void SysTick_SetPriority(uint8 ExceptionPriority);

/**
 * @brief Enable the SysTick timer exception.
 *
 * This function enables the SysTick timer exception.
 *
 * @return None
 */
void SysTick_enableException(void);

/**
 * @brief Disable the SysTick timer exception.
 *
 * This function disables the SysTick timer exception.
 *
 * @return None
 */
void SysTick_disableException(void);

#endif /* SYS_TICK_H_ */
