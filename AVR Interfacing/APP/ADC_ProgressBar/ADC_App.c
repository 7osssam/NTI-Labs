
#include "ADC_App.h"

#include "LCD.h"
#include "ADC.h"
#include "ProgressBar.h"
#include <avr/interrupt.h>

#include "SETTINGS.h"
#include <util/delay.h>

/* Maximum temperature that can be measured by the sensor */
#define LM35_MAX_TEMPERATURE 150
/* the voltage of the sensor at the maximum temperature */
#define LM35_MAX_VOLT		 1.5

// buffer for ADC values to multiple channels
uint16 g_ADC_arr_value[2] = {0, 0};

uint8 temp_value = 0;
uint8 LDR_value = 0;

void ADC_ISR(void)
{
	static uint8 i = 0;

	g_ADC_arr_value[i] = ADC_getValue();

	// g_ADC_arr_value[0] --> LDR
	// g_ADC_arr_value[1] --> LM35

	LDR_value = g_ADC_arr_value[0];

	temp_value = (uint8)(((uint32)g_ADC_arr_value[1] * LM35_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) /
						 (ADC_MAXIMUM_VALUE * LM35_MAX_VOLT));

	// start conversion for the next channel
	ADC_startConversionNonBlocking(i);

	i++;

	// reset i to 0 if it reaches 2
	if (i == 2)
	{
		i = 0;
	}
}

void ADC_APP(void)
{
	uint16 ADC_value = 0;

	ADC_ConfigType ADC_config = {
		.ref_volt = ADC_AVCC, .prescaler = ADC_PRESCALER_128, .auto_trigger_source = ADC_FREE_RUNNING_MODE};

	ADC_init(&ADC_config);

	LCD_init();
	ProgressBar_init();

	ADC_startConversionNonBlocking(ADC0); // LDR
	ADC_startConversionNonBlocking(ADC1); // LM35

	ADC_InterruptEnable();
	ADC_setCallback(ADC_ISR);

	sei(); // Enable Global Interrupts

	while (1)
	{
		LCD_Goto_XY(0, 0);
		LCD_displayString("LDR = ");
		LCD_displayInteger(LDR_value);
		LCD_displayString("     ");

		LCD_Goto_XY(1, 0);
		LCD_displayString("Temp = ");
		LCD_displayInteger(temp_value);
		LCD_displayString("     ");

		ProgressBar(ADC_MAXIMUM_VALUE, g_ADC_arr_value[0], 2);
		ProgressBar(ADC_MAXIMUM_VALUE, g_ADC_arr_value[1], 3);
	}
}