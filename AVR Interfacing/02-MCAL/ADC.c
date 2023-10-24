/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.c
 *
 * Description: source file for the ADC driver
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/
#include "ADC.h"
#include "BIT_MACROS.h"
#include <avr/io.h>		   /* To use the IO Ports Registers */
#include <avr/interrupt.h> /* For ADC ISR */

static volatile void (*ADC_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                          Callback Functions                                *
 *******************************************************************************/
/*******************************************************************************
 * @fn              - ADC_setCallBack
 * @brief           - This function is used to set the callback function address
 * @param[in]       - void (*a_ptr)(void)
 * @return          - void
 *******************************************************************************/
void ADC_setCallback(void (*func_ptr)(void))
{
	if (func_ptr != NULL_PTR)
	{
		ADC_callBackPtr = func_ptr;
	}
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*******************************************************************************
 * @fn              - ADC_init
 * @brief           - This function is used to initialize the ADC driver
 * 						- Set the voltage reference
 * 						- Set the pre-scaler
 * 						- Enable/Disable Auto Trigger
 * 						- Set the Auto Trigger Source
 * 						- Disable ADC Interrupt
 * 						- Enable ADC
 * @param[in]       - ADC_ConfigType *config_ptr (Struct members are ref_volt, prescaler and auto_trigger_source)		
 * @return          - void
 *******************************************************************************/
void ADC_init(ADC_ConfigType* config_ptr)
{
	// ADMUX | Voltage Reference Selections for ADC
	switch (config_ptr->ref_volt)
	{
		case ADC_AREF: /* AREF, Internal Vref turned off */
			CLEAR_BIT(ADMUX, REFS0);
			CLEAR_BIT(ADMUX, REFS1);
			break;

		case ADC_AVCC: /* AVCC with external capacitor at AREF pin */
			SET_BIT(ADMUX, REFS0);
			CLEAR_BIT(ADMUX, REFS1);
			break;

		case ADC_INTERNAL: /* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
			SET_BIT(ADMUX, REFS0);
			SET_BIT(ADMUX, REFS1);
			break;
	}

	// ADMUX | Assume channel 0  11100000
	ADMUX = ADMUX & 0xE0;

	// ADCSRA | ADC Prescaler Selections 11111000
	ADCSRA = (ADCSRA & 0xF8) | (config_ptr->prescaler & 0x07);

	// ADCSRA | ADC enable
	SET_BIT(ADCSRA, ADEN);

	// ADCSRA | disable ADC Interrupt
	CLEAR_BIT(ADCSRA, ADIE);

	if (config_ptr->auto_trigger_source != ADC_SINGLE_CONVERSION_MODE)
	{
		// ADCSRA | ADC Auto Trigger Enable
		SET_BIT(ADCSRA, ADATE);

		// ADCSRB | ADC Auto Trigger Source Selections
		// ADTS2 ADTS1 ADTS0 –  ACME  PUD PSR2 PSR10
		// 1 	  1 	 1   0 	 0    0   0     0
		SFIOR = (SFIOR & 0x1F) | (config_ptr->auto_trigger_source << 5);
	}
	else
	{
		// ADCSRA | ADC Auto Trigger Disable
		CLEAR_BIT(ADCSRA, ADATE);
	}
}

/*******************************************************************************
 * @fn              - ADC_Deinit
 * @brief           - This function is used to deinitialize the ADC driver
 * @param[in]       - void
 * @return          - void
 *******************************************************************************/
void ADC_Deinit(void)
{
	// ADCSRA | ADC disable
	CLEAR_BIT(ADCSRA, ADEN);
}

/*******************************************************************************
 * @fn              - ADC_InterruptEnable
 * @brief           - This function is used to enable the ADC interrupt
 * @param[in]       - void
 * @return          - void
 *******************************************************************************/
void ADC_InterruptEnable(void)
{
	// ADCSRA | enable ADC Interrupt
	SET_BIT(ADCSRA, ADIE);
}

/*******************************************************************************
 * @fn              - ADC_InterruptDisable
 * @brief           - This function is used to disable the ADC interrupt
 * @param[in]       - void
 * @return          - void
 *******************************************************************************/
void ADC_InterruptDisable(void)
{
	// ADCSRA | disable ADC Interrupt
	CLEAR_BIT(ADCSRA, ADIE);
}

/*******************************************************************************
 * @fn              - ADC_setAutoTriggerSource
 * @brief           - This function is used to set the auto trigger source
 * @param[in]       - ADC_AutoTriggerSource_t auto_trigger_source
 * @return          - void
 *******************************************************************************/
void ADC_setAutoTriggerSource(ADC_AutoTriggerSource_t auto_trigger_source)
{
	if (auto_trigger_source != ADC_SINGLE_CONVERSION_MODE)
	{
		// ADCSRA | ADC Auto Trigger Enable
		SET_BIT(ADCSRA, ADATE);

		// ADCSRB | ADC Auto Trigger Source Selections
		// ADTS2 ADTS1 ADTS0 –  ACME  PUD PSR2 PSR10
		// 1 	  1 	 1   0 	 0    0   0     0
		SFIOR = (SFIOR & 0x1F) | (auto_trigger_source << 5);
	}
	else
	{
		// ADCSRA | ADC Auto Trigger Disable
		CLEAR_BIT(ADCSRA, ADATE);
	}
}

/*******************************************************************************
 * @fn              - ADC_readChannelBlocking
 * @brief           - This function starts the conversion and waits for it to finish and return the digital value
 * @param[in]       - ADC_Channel_t channel_num (0-7)
 * @return          - uint16
 * @note			- This function is used in case of polling
 *******************************************************************************/
uint16 ADC_readChannelBlocking(ADC_Channel_t channel_num)
{
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = (ADMUX & 0xE0) | (0x07 & channel_num); /* Input channel number must be from 0 --> 7 */

	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA, ADSC);

	/* Wait for conversion to complete, ADIF becomes '1' */
	while (IS_BIT_CLEAR(ADCSRA, ADIF))
		;

	/* Clear ADIF by write '1' to it :) */
	SET_BIT(ADCSRA, ADIF);

	/* Read the digital value from the data register */

	return ADC;
}

/*******************************************************************************
 * @fn              - ADC_readChannelNonBlocking
 * @brief           - This function is used to read the ADC channel non-blocking
 * @param[in]       - ADC_Channel_t channel_num (0-7)
 * @return          - void
 * @note			- This function is used in case of interrupt
 *******************************************************************************/
void ADC_startConversionNonBlocking(ADC_Channel_t channel_num)
{
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = (ADMUX & 0xE0) | (0x07 & channel_num); /* Input channel number must be from 0 --> 7 */

	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA, ADSC);
}

/*******************************************************************************
 * @fn              - ADC_getValue
 * @brief           - This function is used to get the ADC value
 * @param[in]       - void
 * @return          - uint16
 *******************************************************************************/
uint16 ADC_getValue(void)
{
	return ADC;
}

void ADC_Chain(ADC_Channel_t channel_num)
{
	ADC_startConversionNonBlocking(channel_num);
}

/******************** Interrupt Service Routines ********************/
ISR(ADC_vect)
{
	if (ADC_callBackPtr != NULL_PTR)
	{
		ADC_callBackPtr();
	}
}