/******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: EXTI.c
 *
 * Description: Source file for the External Interrupt driver
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/
#include "EXTI.h"
#include "BIT_MACROS.h"

#include "DIO_map.h"
#include <avr/interrupt.h>
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_INT0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT2_callBackPtr)(void) = NULL_PTR;

#define ISC_MASK 0x03

/*******************************************************************************
 *                                    ISR's                                    *
 *******************************************************************************/

ISR(INT0_vect)
{
	if (g_INT0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application  */
		(*g_INT0_callBackPtr)();
	}
}

ISR(INT1_vect)
{
	if (g_INT1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application  */
		(*g_INT1_callBackPtr)();
	}
}

ISR(INT2_vect)
{
	if (g_INT2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application  */
		(*g_INT2_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void EXTI_init(EXTI_ConfigType* Config_Ptr)
{
	if (Config_Ptr->interrupt == EXTI_INT0)
	{
		MCUCR = (MCUCR & ~ISC_MASK) | (Config_Ptr->sense_control & ISC_MASK);
	}
	else if (Config_Ptr->interrupt == EXTI_INT1)
	{
		MCUCR = (MCUCR & ~(ISC_MASK << 2)) | ((Config_Ptr->sense_control & ISC_MASK) << 2);
	}
	else if (Config_Ptr->interrupt == EXTI_INT2)
	{
		switch (Config_Ptr->sense_control)
		{
			case EXTI_falling_edge:
				CLEAR_BIT(MCUCSR, ISC2);
				break;
			case EXTI_rising_edge:
				SET_BIT(MCUCSR, ISC2);
				break;
		}
	}
}

void EXTI_enable(EXTI_ConfigType* Config_Ptr)
{
	if (Config_Ptr->interrupt == EXTI_INT0)
	{
		SET_BIT(GICR, INT0);
	}
	else if (Config_Ptr->interrupt == EXTI_INT1)
	{
		SET_BIT(GICR, INT1);
	}
	else if (Config_Ptr->interrupt == EXTI_INT2)
	{
		SET_BIT(GICR, INT2);
	}
}

void EXTI_disable(EXTI_ConfigType* Config_Ptr)
{
	if (Config_Ptr->interrupt == EXTI_INT0)
	{
		CLEAR_BIT(GICR, INT0);
	}
	else if (Config_Ptr->interrupt == EXTI_INT1)
	{
		CLEAR_BIT(GICR, INT1);
	}
	else if (Config_Ptr->interrupt == EXTI_INT2)
	{
		CLEAR_BIT(GICR, INT2);
	}
}

/*******************************************************************************
 *                      Callback functions implementations                      *
 * *****************************************************************************/
void EXTI_setCallBack(EXTI_ConfigType* Config_Ptr, void (*a_ptr)(void))
{
	switch (Config_Ptr->interrupt)
	{
		case EXTI_INT0:
			g_INT0_callBackPtr = a_ptr;
			break;
		case EXTI_INT1:
			g_INT1_callBackPtr = a_ptr;
			break;
		case EXTI_INT2:
			g_INT2_callBackPtr = a_ptr;
			break;
	}
}
