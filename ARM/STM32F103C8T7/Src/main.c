/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"

#include "EXTI.h"
#include "EXTI_reg.h"

#include "NVIC.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
	#warning \
		"FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay(uint32 nCount)
{
	for (; nCount != 0; nCount--)
	{
		asm("nop");
	}
}

void EXTI0_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR0;
	GPIO_TogglePinValue(GPIOB, PIN1);
}

int main(void)
{
	RCC_Config();

	RCC_EnableCLK(IOPAEN);
	RCC_EnableCLK(IOPBEN);

	GPIO_SetPinDirection(GPIOA, PIN0, OUT_PUSH_PULL, OUTPUT_10MHZ);
	GPIO_SetPinDirection(GPIOA, PIN1, OUT_PUSH_PULL, OUTPUT_10MHZ);
	GPIO_SetPinDirection(GPIOB, PIN1, OUT_PUSH_PULL, OUTPUT_10MHZ);

	GPIO_SetPinValue(GPIOA, PIN1, LOGIC_HIGH);
	//GPIO_SetPinValue(GPIOB, PIN1, LOGIC_HIGH);

	NVIC_SetEnable(NVIC_EXTI0_IRQ);
	NVIC_SetPriority(NVIC_EXTI0_IRQ, 0x10, 0x01);

	EXTI_Init(); // PA0 to EXTI0

	while (1)
	{
		delay(100000);

		GPIO_TogglePinValue(GPIOA, PIN1);
		GPIO_TogglePinValue(GPIOA, PIN0);
	}
}
