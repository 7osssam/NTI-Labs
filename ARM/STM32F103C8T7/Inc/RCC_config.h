

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_

#define RCC_CLOCK  Enable_HSI

#define Enable_HSI 0

#define Enable_HSE 1

#define Enable_PLL 2

#if (RCC_CLOCK == Enable_PLL)

	/* * * * * * * * * * * *
 *   PLL CLK Source    *
 * * * * * * * * * * * */
	/*
 	Half_HSI,
	Half_HSE,
	HSE
  */
	#define PLL_CLK_Source			  HSE

	/* * * * * * * * * * * * * * *
 * PLL Multiplication Factor *
 * * * * * * * * * * * * * * */
	/*
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
	*/
	#define PLL_Multiplication_Factor PLL_input_clock_x16
#endif

#endif /* CONFIG_H_ */
