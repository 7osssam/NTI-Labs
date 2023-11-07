
#ifndef RCC_H_
#define RCC_H_

#include "std_types.h"

typedef struct
{
	uint32 RCC_CR;
	uint32 RCC_CFGR;
	uint32 RCC_CIR;
	uint32 RCC_APB2RSTR;
	uint32 RCC_APB1RSTR;
	uint32 RCC_AHBENR;
	uint32 RCC_APB2ENR;
	uint32 RCC_APB1ENR;
	uint32 RCC_BDCR;
	uint32 RCC_CSR;
} RCC_Registers;

typedef enum
{
	/* These are the values that are used to choose the MCO
	   clock source.
	 * You can choose one value to pass it to:
	   void RCC_MCO_CLK(uint8 MCO_CLKSource)
	   as function argument.
	 * These Values can't be edited by the user.
	 * */
	MCO_No_clock,
	MCO_System_clock_selected = 4,
	MCO_HSI_clock_selected,
	MCO_HSE_clock_selected,
	MCO_PLL_clock_divided_by_2_selected
} MCO_CLKSource_t;

typedef enum
{
	/* These are the values that are used to choose Input
	   Clock source of PLL.
	 * You can choose one value to pass it to:
	   void RCC_EnablePLL(uint8 PLL_CLKSource, uint8 PLL_Value)
	   as the first argument.
	 * These Values can be edited by the user.
	 * */
	Half_HSI,
	Half_HSE,
	HSE
} PLL_CLKSource_t;

typedef enum
{
	/* These are the values that are used to choose the PLL
	   Multiplication factor.
	 * You can choose one value to pass it to:
	   void RCC_EnablePLL(uint8 PLL_CLKSource, uint8 PLL_Value)
	   as the second argument.
	 * These Values can't be edited by the user.
	 * */
	PLL_input_clock_x2,
	PLL_input_clock_x3,
	PLL_input_clock_x4,
	PLL_input_clock_x5,
	PLL_input_clock_x6,
	PLL_input_clock_x7,
	PLL_input_clock_x8,
	PLL_input_clock_x9,
	PLL_input_clock_x10,
	PLL_input_clock_x11,
	PLL_input_clock_x12,
	PLL_input_clock_x13,
	PLL_input_clock_x14,
	PLL_input_clock_x15,
	PLL_input_clock_x16,
} PLL_Value_t;

typedef enum
{
	/* RCC APB2RSTR Registers */
	AFIORST,
	IOPARST = 2,
	IOPBRST,
	IOPCRST,
	IOPDRST,
	IOPERST,
	IOPFRST,
	IOPGRST,
	ADC1RST,
	ADC2RST,
	TIM1RST,
	SPI1RST,
	TIM8RST,
	USART1RST,
	ADC3RST,
	TIM9RST = 19,
	TIM10RST,
	TIM11RST,
	/* RCC APB1RSTR Registers */
	TIM2RST = 32,
	TIM3RST,
	TIM4RST,
	TIM5RST,
	TIM6RST,
	TIM7RST,
	TIM12RST,
	TIM13RST,
	TIM14RST,
	WWDGRST = 43,
	SPI2RST = 46,
	SPI3RST,
	USART2RST = 49,
	USART3RST,
	UART4RST,
	UART5RST,
	I2C1RST,
	I2C2RST,
	USBRST,
	CANRST = 57,
	BKPRST = 59,
	PWRRST,
	DACRST
} RCC_APBRSTR_t;

/* * * * * * * * * * * * * * *
 *   RCC_AHBENR Registers    *
 * * * * * * * * * * * * * * */
enum
{
	/* These are the values that are used to enable clock for a
	 * specific module.
	 * You can choose one value to pass it to:
	   void RCC_DisableCLK(uint8 peripheralIdx)
	   void RCC_EnableCLK(uint8 peripheralIdx)
	   as function argument.
	 * These Values can't be edited by the user.
	 * */
	DMA1EN,
	DMA2EN,
	SRAMEN,
	FLIFTEN = 4,
	CRCEN = 6,
	FSMCEN = 8,
	SDIOEN = 10
};

/* * * * * * * * * * * * * * *
 *   RCC_APB2ENR Registers   *
 * * * * * * * * * * * * * * */
enum
{
	/* These are the values that are used to enable clock for a
	 * specific module.
	 * You can choose one value to pass it to:
	   void RCC_DisableCLK(uint8 peripheralIdx)
	   void RCC_EnableCLK(uint8 peripheralIdx)
	   as function argument.
	 * These Values can't be edited by the user.
	 * */
	AFIOEN = 32,
	IOPAEN = 34,
	IOPBEN,
	IOPCEN,
	IOPDEN,
	IOPEEN,
	IOPFEN,
	IOPGEN,
	ADC1EN,
	ADC2EN,
	TIM1REN,
	SPI1EN,
	TIM8EN,
	USART1EN,
	ADC3EN,
	TIM9EN = 51,
	TIM10EN,
	TIM11EN
};

/* * * * * * * * * * * * * * *
 *   RCC_APB1ENR Registers   *
 * * * * * * * * * * * * * * */
enum
{
	/* These are the values that are used to enable clock for a
	 * specific module.
	 * You can choose one value to pass it to:
	   void RCC_DisableCLK(uint8 peripheralIdx)
	   void RCC_EnableCLK(uint8 peripheralIdx)
	   as function argument.
	 * These Values can't be edited by the user.
	 * */
	TIM2EN = 64,
	TIM3EN,
	TIM4EN,
	TIM5EN,
	TIM6EN,
	TIM7EN,
	TIM12EN,
	TIM13EN,
	TIM14EN,
	WWDGEN = 75,
	SPI2EN = 78,
	SPI3EN,
	USART2EN = 81,
	USART3EN,
	UART4EN,
	UART5EN,
	I2C1EN,
	I2C2EN,
	USBEN,
	CANEN = 89,
	BKPEN = 91,
	PWREN,
	DACEN
};

void RCC_EnableHSI(void);

void RCC_EnableHSE(void);

void RCC_EnablePLL(PLL_CLKSource_t PLL_CLKSource, PLL_Value_t PLL_Value);

void Reset_Module(RCC_APBRSTR_t peripheralIdx);

void Remove_ResetFlag(void);

void RCC_EnableCLK(uint8 peripheralIdx);

void RCC_DisableCLK(uint8 peripheralIdx);

void RCC_Config(void);

#endif /* RCC_H_ */
