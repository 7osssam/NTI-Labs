
#include "ADC_App.h"

#include "DIO.h"
#include "LCD.h"
#include "ADC.h"
#include "EXTI.h"
#include "ProgressBar.h"

#include "Buzzer.h"

#include <avr/interrupt.h>

#include "SETTINGS.h"
#include <util/delay.h>

#define LDR_FLAG			 0
#define LM35_FLAG			 1

/* Maximum temperature that can be measured by the sensor */
#define LM35_MAX_TEMPERATURE 150
/* the voltage of the sensor at the maximum temperature */
#define LM35_MAX_VOLT		 1.5

// buffer for ADC values to multiple channels
volatile uint16 g_ADC_arr_value[2] = {0, 0};

volatile uint8 temp_value = 0;
volatile uint8 LDR_value = 0;

volatile uint8 g_ADC_flag = 2; // 2 means no interrupt has occurred yet

void ADC_ISR(void)
{
	static uint8 i = 0;

	g_ADC_arr_value[i] = ADC_getValue();

	// g_ADC_arr_value[0] --> LDR
	// g_ADC_arr_value[1] --> LM35
	LDR_value = g_ADC_arr_value[LDR_FLAG];

	temp_value = (uint8)(((uint32)g_ADC_arr_value[LM35_FLAG] * LM35_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) /
						 (ADC_MAXIMUM_VALUE * LM35_MAX_VOLT));

	if (LDR_value >= 100)
	{
		DIO_SetPinValue(PORTD_ID, PIN2_ID, LOGIC_HIGH); // Trigger External Interrupt 0
		g_ADC_flag = LDR_FLAG; // save the channel number that triggered the interrupt
	}
	else if (temp_value >= 30)
	{
		DIO_SetPinValue(PORTD_ID, PIN2_ID, LOGIC_HIGH); // Trigger External Interrupt 0
		g_ADC_flag = LM35_FLAG; // save the channel number that triggered the interrupt
	}
	else
	{
		DIO_SetPinValue(PORTD_ID, PIN2_ID, LOGIC_LOW);
		g_ADC_flag = 2;
	}

	// start conversion for the next channel
	ADC_startConversionNonBlocking(i);
	i++;
	// reset i to 0 if it reaches 2
	if (i == 2)
	{
		i = 0;
	}
}

void EXTI0_ISR(void)
{
	Buzzer_on();
	_delay_ms(1000);
	Buzzer_off();
}

void ADC_APP(void)
{
	ADC_ConfigType ADC_config = {
		.ref_volt = ADC_AVCC, .prescaler = ADC_PRESCALER_128, .auto_trigger_source = ADC_FREE_RUNNING_MODE};
	EXTI_ConfigType EXTI0_config = {.interrupt = EXTI_INT0, .sense_control = EXTI_rising_edge};

	EXTI_setCallBack(EXTI_INT0, ADC_ISR);
	ADC_setCallback(ADC_ISR);

	ADC_init(&ADC_config);

	EXTI_init(&EXTI0_config);

	LCD_init();

	ADC_startConversionNonBlocking(ADC0); // LDR
	ADC_startConversionNonBlocking(ADC1); // LM35

	ADC_InterruptEnable();
	EXTI_enable(&EXTI0_config);

	sei(); // Enable Global Interrupts

	while (1)
	{
		if (g_ADC_flag != 2)
		{
			LCD_Goto_XY(0, 0);
			if (g_ADC_flag == LDR_FLAG)
			{
				LCD_displayString("LDR is  ");
				LCD_displayInteger(LDR_value);
				ProgressBar(ADC_MAXIMUM_VALUE, LDR_value, 2);
			}
			else if (g_ADC_flag == LM35_FLAG)
			{
				LCD_displayString("LM35 is ");
				LCD_displayInteger(temp_value);
				ProgressBar(LM35_MAX_TEMPERATURE, temp_value, 2);
			}
		}
		else
		{
			LCD_Goto_XY(0, 0);
			LCD_displayString("No DATA        ");
		}
	}
}