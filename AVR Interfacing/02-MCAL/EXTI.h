/******************************************************************************
 *
 * Module: External Interrupt
 *
 * File Name: EXTI.h
 *
 * Description: Header file for External Interrupt Module.
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/

#ifndef EXTI_H_
#define EXTI_H_

#include "STD_TYPES.h"

/*******************************************************************************
 * 					       Types Declaration                               	   *
 * *****************************************************************************/
typedef enum
{
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2
} EXTI_Interrupt;

typedef enum
{
	EXTI_low_level,
	EXTI_any_logical_change,
	EXTI_falling_edge,
	EXTI_rising_edge
} EXTI_sense_control_t;

/*******************************************************************************
 * 								Configuration structure                        *
 * *****************************************************************************/
typedef struct
{
	EXTI_Interrupt		 interrupt;		// EX_INT0, EX_INT1, EX_INT2
	EXTI_sense_control_t sense_control; // low_level, any_logical_change, falling_edge, rising_edge
} EXTI_ConfigType;

/*******************************************************************************
 * 								Functions Prototypes                           *
 * *****************************************************************************/
void EXTI_init(EXTI_ConfigType* Config_Ptr);
void EXTI_enable(EXTI_ConfigType* Config_Ptr);
void EXTI_disable(EXTI_ConfigType* Config_Ptr);

/****************************** Call Back function *****************************/
void EXTI_setCallBack(EXTI_ConfigType* Config_Ptr, void (*a_ptr)(void));

#endif /* EXTI_H_ */