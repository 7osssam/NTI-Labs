/******************************************************************************
 *
 * Module: Sensor
 *
 * File Name: Sensor.c
 *
 * Description: Source file for the Sensor driver
 * 				- LM35 Sensor
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/

#include "Sensor.h"

/******************************************************************************
 *                          Functions Definitions                             *
 *****************************************************************************/

uint8 LM35_Read(void)
{
	uint8  temp_value = 0;
	uint16 ADC_value = 0;

	//0.54931640625

	/* Read ADC channel where the temperature sensor is connected */
	ADC_value = ADC_readChannelBlocking(LM35_CH);

	//
	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)ADC_value * LM35_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) /
						 (ADC_MAXIMUM_VALUE * LM35_MAX_VOLT));

	return temp_value;
}