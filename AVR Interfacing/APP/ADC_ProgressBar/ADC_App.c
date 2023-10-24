
#include "ADC_App.h"

#include "LCD.h"
#include "ADC.h"
#include "ProgressBar.h"
#include <avr/interrupt.h>

#include "SETTINGS.h"
#include <util/delay.h>

uint16 g_ADC_value = 0;

// buffer for ADC values to multiple channels
uint16 g_ADC_arr_value[2] = {0, 0};

void ADC_ISR(void)
{
	static uint8 i = 0;

	g_ADC_arr_value[i] = ADC_getValue();
	ADC_startConversionNonBlocking(i);

	i++;

	if (i == 2)
	{
		i = 0;
	}

	//g_ADC_value = ADC_getValue();
	//ADC_startConversionNonBlocking(ADC1);
}

void ADC_APP(void)
{
	uint16 ADC_value = 0;

	ADC_ConfigType ADC_config = {
		.ref_volt = ADC_AVCC, .prescaler = ADC_PRESCALER_128, .auto_trigger_source = ADC_FREE_RUNNING_MODE};
	ADC_init(&ADC_config);

	LCD_init();
	ProgressBar_init();

	ADC_startConversionNonBlocking(ADC0);
	ADC_startConversionNonBlocking(ADC1);

	ADC_InterruptEnable();
	ADC_setCallback(ADC_ISR);

	sei(); // Enable Global Interrupts

	while (1)
	{
		LCD_Goto_XY(0, 0);
		LCD_displayString("ADC Read1 = ");
		LCD_displayInteger(g_ADC_arr_value[0]);
		LCD_displayString("     ");

		LCD_Goto_XY(1, 0);
		LCD_displayString("ADC Read2 = ");
		LCD_displayInteger(g_ADC_arr_value[1]);
		LCD_displayString("     ");

		ProgressBar(ADC_MAXIMUM_VALUE, g_ADC_arr_value[0], 2);
		ProgressBar(ADC_MAXIMUM_VALUE, g_ADC_arr_value[1], 3);
	}
}