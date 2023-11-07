/******************************************************************
 * @Module   	: RCC
 * @Title 	 	: Reset and clock control Register header file
 * @Filename 	: RCC_reg.h
 * @target  	: STM32F103C8T7 (Bluepill) ARM Microcontroller
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	:
 * @Notes    	:
 ********************************************************************/
#ifndef RCC_REG_H_
#define RCC_REG_H_

#include "std_types.h"
#include "RCC.h"

/* Define the size of register in STM32F103C8T6 */
#define SIZE_OF_REGISTER		   32

/* Check if the peripheral id is in the RCC_APB2RSTR register */
#define PERIPHERAL_IN_RCC_APB2RSTR (peripheralIdx < 32)

/* Check if the peripheral id is in the RCC_APB1RSTR register */
#define PERIPHERAL_IN_RCC_APB1RSTR (peripheralIdx < 64)

/* Check if the peripheral id is in the RCC_AHBENR register */
#define PERIPHERAL_IN_RCC_AHBENR   (peripheralIdx < 32)

/* Check if the peripheral id is in the RCC_APB2ENR register */
#define PERIPHERAL_IN_RCC_APB2ENR  (peripheralIdx < 64)

/* Check if the peripheral id is in the RCC_APB1ENR register */
#define PERIPHERAL_IN_RCC_APB1ENR  (peripheralIdx < 96)

/* RCC registers offsets addresses */
#define PERIPH_BASE				   (0x40000000)

/* RCC registers offsets addresses */
#define APB1PERIPH_OFFSET		   (0x00000)
#define APB2PERIPH_OFFSET		   (0x10000)
#define AHBPERIPH_OFFSET		   (0x20000)

/* RCC registers base addresses */
#define APB1PERIPH_BASE			   (PERIPH_BASE + APB1PERIPH_OFFSET)
#define APB2PERIPH_BASE			   (PERIPH_BASE + APB2PERIPH_OFFSET)
#define AHBPERIPH_BASE			   (PERIPH_BASE + AHBPERIPH_OFFSET)

/* RCC register map */

#define RCC_OFFSET				   (0x1000)
#define RCC_BASE				   (AHBPERIPH_BASE + RCC_OFFSET)

#define RCC						   ((volatile RCC_Registers*)RCC_BASE)

#define PLL_VALUE_MASK			   0xFFC3FFFF
#define MCO_VALUE_MASK			   0xF8FFFFFF
#define AHB_VALUE_MASK			   0xFFFFFF0F
#define APB1_VALUE_MASK			   0xFFFFF8FF
#define APB2_VALUE_MASK			   0xFFFFC7FF
#define ADC_VALUE_MASK			   0xFFFF3FFF
#define USB_VALUE_MASK			   0xFFBFFFFF

/* * * * * * * * * * * * * * * * * * * * * *
 *  Clock control register (RCC_CR) Pins   *
 * * * * * * * * * * * * * * * * * * * * * */
enum
{
	HSION,
	HSIRDY,
	HSITRIM0 = 3,
	HSITRIM1,
	HSITRIM2,
	HSITRIM3,
	HSITRIM4,
	HSICAL0,
	HSICAL1,
	HSICAL2,
	HSICAL3,
	HSICAL4,
	HSICAL5,
	HSICAL6,
	HSICAL7,
	HSEON,
	HSERDY,
	HSEBYP,
	CSSON,
	PLLON = 24,
	PLLRDY
};

/* * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Clock configuration register (RCC_CFGR) Pins   *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
enum
{
	SW0,
	SW1,
	SWS0,
	SWS1,
	HPRE0,
	HPRE1,
	HPRE2,
	HPRE3,
	PPRE10,
	PPRE11,
	PPRE12,
	PPRE20,
	PPRE21,
	PPRE22,
	ADCPRE0,
	ADCPRE1,
	PLLSRC,
	PLLXTPRE,
	PLLMUL0,
	PLLMUL1,
	PLLMUL2,
	PLLMUL3,
	USBPRE,
	MCO0 = 24,
	MCO1,
	MCO2
};

/* * * * * * * * * * * * * * * * * * * * * * * *
 *  Clock interrupt register (RCC_CIR) Pins    *
 * * * * * * * * * * * * * * * * * * * * * * * */
enum
{
	LSIRDYF,
	LSERDYF,
	HSIRDYF,
	HSERDYF,
	PLLRDYF,
	CSSF = 7,
	LSIRDYIE,
	LSERDYIE,
	HSIRDYIE,
	HSERDYIE,
	PLLRDYIE,
	LSIRDYC = 16,
	LSERDYC,
	HSIRDYC,
	HSERDYC,
	PLLRDYC,
	CSSC = 23
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Backup domain control register (RCC_BDCR) Pins   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum
{
	LSEON,
	LSERDY,
	LSEBYP,
	RTCSEL0 = 8,
	RTCSEL1,
	RTCEN = 15,
	BDRST
};

/* * * * * * * * * * * * * * * * * * * * * * *
 *  Control/status register (RCC_CSR) Pins   *
 * * * * * * * * * * * * * * * * * * * * * * */
enum
{
	LSION,
	LSIRDY,
	RMVF = 24,
	PINRSTF = 26,
	PORRSTF,
	SFTRSTF,
	IWDGRSTF,
	WWDGRSTF,
	LPWRRSTF
};

#endif /* RCC_REG_H_ */
