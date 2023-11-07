/******************************************************************
 * @Module   	: NVIC
 * @Title    	: Nested Vector Interrupt Controller (NVIC) Driver Header
 * @Filename 	: NVIC.h
 * @target  	: STM32F103C8T7 (Bluepill) ARM Microcontroller
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	:
 * @Notes    	:
 ********************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

#include "STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*TODO: Set Configured IRQ IN NVIC_Cfg File*/
#define NVIC_CONFIGURED_IRQS		 3
#define NVIC_PRIORITY_FIELDS_PER_REG 4

#define NVIC_XXXX_GROUP_PRIORITY	 0b011 /* 16 Groups & 0 SubGroups */
#define NVIC_XXXY_GROUP_PRIORITY	 0b100 /* 8 Groups & 2 SubGroups  */
#define NVIC_XXYY_GROUP_PRIORITY	 0b101 /* 4 Groups & 4 SubGroups  */
#define NVIC_XYYY_GROUP_PRIORITY	 0b110 /* 2 Groups & 8 SubGroups  */
#define NVIC_YYYY_GROUP_PRIORITY	 0b111 /* 0 Groups & 16 SubGroups */

#define NVIC_PRIORITY_GROUPING		 NVIC_XXXY_GROUP_PRIORITY

#if NVIC_PRIORITY_GROUPING == NVIC_XXXX_GROUP_PRIORITY
	#define NVIC_GROUP_PRIORITY_MASK	 0b1111
	#define NVIC_GROUP_PRIORITY_SHIFT	 0
	#define NVIC_SUBGROUP_PRIORITY_MASK	 0b0000
	#define NVIC_SUBGROUP_PRIORITY_SHIFT 0
#elif NVIC_PRIORITY_GROUPING == NVIC_XXXY_GROUP_PRIORITY
	#define NVIC_GROUP_PRIORITY_MASK	 0b0111
	#define NVIC_GROUP_PRIORITY_SHIFT	 1
	#define NVIC_SUBGROUP_PRIORITY_MASK	 0b0001
	#define NVIC_SUBGROUP_PRIORITY_SHIFT 0
#elif NVIC_PRIORITY_GROUPING == NVIC_XXYY_GROUP_PRIORITY
	#define NVIC_GROUP_PRIORITY_MASK	 0b0011
	#define NVIC_GROUP_PRIORITY_SHIFT	 2
	#define NVIC_SUBGROUP_PRIORITY_MASK	 0b0011
	#define NVIC_SUBGROUP_PRIORITY_SHIFT 0
#elif NVIC_PRIORITY_GROUPING == NVIC_XYYY_GROUP_PRIORITY
	#define NVIC_GROUP_PRIORITY_MASK	 0b0001
	#define NVIC_GROUP_PRIORITY_SHIFT	 3
	#define NVIC_SUBGROUP_PRIORITY_MASK	 0b0111
	#define NVIC_SUBGROUP_PRIORITY_SHIFT 0
#elif NVIC_PRIORITY_GROUPING == NVIC_YYYY_GROUP_PRIORITY
	#define NVIC_GROUP_PRIORITY_MASK	 0b0000
	#define NVIC_GROUP_PRIORITY_SHIFT	 4
	#define NVIC_SUBGROUP_PRIORITY_MASK	 0b1111
	#define NVIC_SUBGROUP_PRIORITY_SHIFT 0
#endif /* NVIC_PRIORITY_GROUPING */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*Typedef For IRQ signals From STM32F103C8T7 peripherals To Cortex-M3F Core*/
typedef enum
{
	NVIC_WWDG_IRQ,			  /* Window Watchdog interrupt                        */
	NVIC_PVD_IRQ,			  /* PVD through EXTI line detection interrupt        */
	NVIC_TAMPER_IRQ,		  /* Tamper interrupt                                 */
	NVIC_RTC_IRQ,			  /* RTC global interrupt                             */
	NVIC_FLASH_IRQ,			  /* Flash global interrupt                           */
	NVIC_RCC_IRQ,			  /* RCC global interrupt                             */
	NVIC_EXTI0_IRQ,			  /* EXTI Line0 interrupt                             */
	NVIC_EXTI1_IRQ,			  /* EXTI Line1 interrupt                             */
	NVIC_EXTI2_IRQ,			  /* EXTI Line2 interrupt                             */
	NVIC_EXTI3_IRQ,			  /* EXTI Line3 interrupt                             */
	NVIC_EXTI4_IRQ,			  /* EXTI Line4 interrupt                             */
	NVIC_DMA1_Channel1_IRQ,	  /* DMA1 Channel1 global interrupt                   */
	NVIC_DMA1_Channel2_IRQ,	  /* DMA1 Channel2 global interrupt                   */
	NVIC_DMA1_Channel3_IRQ,	  /* DMA1 Channel3 global interrupt                   */
	NVIC_DMA1_Channel4_IRQ,	  /* DMA1 Channel4 global interrupt                   */
	NVIC_DMA1_Channel5_IRQ,	  /* DMA1 Channel5 global interrupt                   */
	NVIC_DMA1_Channel6_IRQ,	  /* DMA1 Channel6 global interrupt                   */
	NVIC_DMA1_Channel7_IRQ,	  /* DMA1 Channel7 global interrupt                   */
	NVIC_ADC1_2_IRQ,		  /* ADC1 and ADC2 global interrupt                   */
	NVIC_USB_HP_CAN_TX_IRQ,	  /* USB High Priority or CAN TX interrupts           */
	NVIC_USB_LP_CAN_RX0_IRQ,  /* USB Low Priority or CAN RX0 interrupts           */
	NVIC_CAN_RX1_IRQ,		  /* CAN RX1 interrupt                                */
	NVIC_CAN_SCE_IRQ,		  /* CAN SCE interrupt                                */
	NVIC_EXTI9_5_IRQ,		  /* EXTI Line[9:5] interrupts                        */
	NVIC_TIM1_BRK_IRQ,		  /* TIM1 Break interrupt                             */
	NVIC_TIM1_UP_IRQ,		  /* TIM1 Update interrupt                            */
	NVIC_TIM1_TRG_COM_IRQ,	  /* TIM1 Trigger and Commutation interrupts          */
	NVIC_TIM1_CC_IRQ,		  /* TIM1 Capture Compare interrupt                   */
	NVIC_TIM2_IRQ,			  /* TIM2 global interrupt                            */
	NVIC_TIM3_IRQ,			  /* TIM3 global interrupt                            */
	NVIC_TIM4_IRQ,			  /* TIM4 global interrupt                            */
	NVIC_I2C1_EV_IRQ,		  /* I2C1 event interrupt                             */
	NVIC_I2C1_ER_IRQ,		  /* I2C1 error interrupt                             */
	NVIC_I2C2_EV_IRQ,		  /* I2C2 event interrupt                             */
	NVIC_I2C2_ER_IRQ,		  /* I2C2 error interrupt                             */
	NVIC_SPI1_IRQ,			  /* SPI1 global interrupt                            */
	NVIC_SPI2_IRQ,			  /* SPI2 global interrupt                            */
	NVIC_USART1_IRQ,		  /* USART1 global interrupt                          */
	NVIC_USART2_IRQ,		  /* USART2 global interrupt                          */
	NVIC_USART3_IRQ,		  /* USART3 global interrupt                          */
	NVIC_EXTI15_10_IRQ,		  /* EXTI Line[15:10] interrupts                      */
	NVIC_RTCAlarm_IRQ,		  /* RTC Alarms through EXTI line interrupt           */
							  /* Reserved                                         */
	NVIC_TIM8_BRK_IRQ = 43,	  /* TIM8 Break interrupt                             */
	NVIC_TIM8_UP_IRQ,		  /* TIM8 Update interrupt                            */
	NVIC_TIM8_TRG_COM_IRQ,	  /* TIM8 Trigger and Commutation interrupts          */
	NVIC_TIM8_CC_IRQ,		  /* TIM8 Capture Compare interrupt                   */
	NVIC_ADC3_IRQ,			  /* ADC3 global interrupt                            */
	NVIC_FSMC_IRQ,			  /* FSMC global interrupt                            */
	NVIC_SDIO_IRQ,			  /* SDIO global interrupt                            */
	NVIC_TIM5_IRQ,			  /* TIM5 global interrupt                            */
	NVIC_SPI3_IRQ,			  /* SPI3 global interrupt                            */
	NVIC_UART4_IRQ,			  /* UART4 global interrupt                           */
	NVIC_UART5_IRQ,			  /* UART5 global interrupt                           */
	NVIC_TIM6_IRQ,			  /* TIM6 global interrupt                            */
	NVIC_TIM7_IRQ,			  /* TIM7 global interrupt                            */
	NVIC_DMA2_Channel1_IRQ,	  /* DMA2 Channel1 global interrupt                   */
	NVIC_DMA2_Channel2_IRQ,	  /* DMA2 Channel2 global interrupt                   */
	NVIC_DMA2_Channel3_IRQ,	  /* DMA2 Channel3 global interrupt                   */
	NVIC_DMA2_Channel4_5_IRQ, /* DMA2 Channel4 and DMA2 Channel5 global interrupt */
} NVIC_IrqNumberType;

/*Typdef For IRQ Group Priority According To Sys_Grouping_select in APIN Reg */
typedef uint8 NVIC_GroupPriorityType;

/*Typdef For IRQ subGroup Priority According To Sys_Grouping_select in APIN Reg */
typedef uint8 NVIC_SubGroupPriorityType;

/*Typdef For Configuring an IRQ*/
typedef struct
{
	NVIC_IrqNumberType		  IRQ_Num;
	NVIC_GroupPriorityType	  groupPriority;
	NVIC_SubGroupPriorityType subGroupPriority;
} NVIC_ConfigType;

/**********************************************************************************************************************
 *                                        GLOBAL FUNCTION PROTOTYPES                                                *
 *********************************************************************************************************************/

/**
 * @brief Initialize the Nested Vectored Interrupt Controller (NVIC) for a specific interrupt.
 *
 * This function configures the NVIC for a given interrupt by enabling it, setting its priority,
 * and configuring its priority grouping. It uses the NVIC_ConfigType structure to specify the
 * interrupt number, group priority, and subgroup priority.
 *
 * @param configPtr A pointer to a NVIC_ConfigType structure containing the configuration
 *                 parameters for the interrupt.
 *
 * @note The NVIC must be properly configured to handle the interrupt priorities and grouping
 *       before using this function.
 *
 * @note This function assumes that IRQ numbers are within valid ranges and that the NVIC
 *       registers are accessible and correctly set up.
 *
 * @see NVIC_ConfigType
 * @see NVIC_SetPriorityGrouping
 * @see NVIC_SetPriority
 * @see NVIC_EnableIRQ
 *
 * @param[in] configPtr Pointer to the NVIC_ConfigType structure with interrupt configuration.
 *
 * @return None
 */
void NVIC_Init(const NVIC_ConfigType* configPtr);

/**
 * @brief Set an interrupt as pending in the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function forces an interrupt to be pending in the NVIC, indicating that the interrupt
 * is ready to be serviced. It uses the IRQ number to determine the NVIC register and bit
 * position to set as pending.
 *
 * @param IRQ_Num The IRQ number of the interrupt to set as pending.
 *
 * @note This function assumes that IRQ numbers are within valid ranges and that the NVIC
 *       registers are correctly set up to handle pending interrupts.
 *
 * @see NVIC_ClearPendingIRQ
 * @see NVIC_SetPendingIRQ
 *
 * @param[in] IRQ_Num The IRQ number to set as pending.
 *
 * @return None
 */
void NVIC_SetPending(NVIC_IrqNumberType IRQ_Num);

/**
 * @brief Clear the pending status of an interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function removes the pending status of a specific interrupt in the NVIC, indicating
 * that the interrupt no longer needs servicing. It uses the IRQ number to determine the NVIC
 * register and bit position to clear as pending.
 *
 * @param IRQ_Num The IRQ number of the interrupt to clear its pending status.
 *
 * @note This function assumes that IRQ numbers are within valid ranges and that the NVIC
 *       registers are correctly set up to handle pending interrupts.
 *
 * @see NVIC_SetPendingIRQ
 * @see NVIC_IrqSetPending
 *
 * @param[in] IRQ_Num The IRQ number to clear its pending status.
 *
 * @return None
 */
void NVIC_ClearPending(NVIC_IrqNumberType IRQ_Num);

/**
 * @brief Enable an interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function enables a specific interrupt in the NVIC, allowing it to be serviced when
 * its conditions are met. It uses the IRQ number to determine the NVIC register and bit
 * position to enable.
 *
 * @param IRQ_Num The IRQ number of the interrupt to enable.
 *
 * @note This function assumes that IRQ numbers are within valid ranges and that the NVIC
 *       registers are correctly set up to handle interrupt enables.
 *
 * @see NVIC_IrqDisable
 * @see NVIC_IrqSetPending
 *
 * @param[in] IRQ_Num The IRQ number to enable.
 *
 * @return None
 */
void NVIC_SetEnable(NVIC_IrqNumberType IRQ_Num);

/**
 * @brief Disable an interrupt in the Nested Vectored Interrupt Controller (NVIC).
 *
 * This function disables a specific interrupt in the NVIC, preventing it from being serviced
 * when its conditions are met. It uses the IRQ number to determine the NVIC register and bit
 * position to disable.
 *
 * @param IRQ_Num The IRQ number of the interrupt to disable.
 *
 * @note This function assumes that IRQ numbers are within valid ranges and that the NVIC
 *       registers are correctly set up to handle interrupt disables.
 *
 * @see NVIC_IrqSetEnable
 * @see NVIC_IrqClearPending
 *
 * @param[in] IRQ_Num The IRQ number to disable.
 *
 * @return None
 */
void NVIC_SetDisable(NVIC_IrqNumberType IRQ_Num);

void NVIC_SetPriority(NVIC_IrqNumberType IRQ_Num, uint8 groupPriority, uint8 subGroupPriority);
#endif /* NVIC_H_ */