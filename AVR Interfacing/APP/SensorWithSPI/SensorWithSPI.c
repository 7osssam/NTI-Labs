
#include "SensorWithSPI.h"

#include "TIMER_services.h"
#include "LCD.h"

#if (SPI == MASTER)

	#include "SPI.h"
	#include "LCD.h"
	#include "EXTI.h"

	#include "SETTINGS.h"
	#include <util/delay.h>

	#include <avr/interrupt.h>

	#define DUMMY_DATA 0x01

uint8		   g_received_data = 0;
volatile uint8 EXTI_flag = 0;

void EXTI_ISR()
{
	EXTI_flag = 1;
}

void master_app()
{
	EXTI_ConfigType EXTI_config = {.interrupt = EXTI_INT0, .sense_control = EXTI_rising_edge};
	EXTI_setCallBack(&EXTI_config, EXTI_ISR);

	EXTI_init(&EXTI_config);
	EXTI_enable(&EXTI_config);

	LCD_init();
	SPI_init(SPI_Master, SPI_FOSC_128);

	sei();

	while (1)
	{
		LCD_Goto_XY(0, 0);
		LCD_displayString("LM34 : ");
		LCD_displayInteger(g_received_data);

		// 5 seconds delay
		for (int i = 0; i < 150; i++)
		{
			if (EXTI_flag == 1)
			{
				EXTI_flag = 0;
				LCD_displayString("interrupted");
				LCD_clearScreen();
				break;
			}

			_delay_ms(1);
			LCD_Goto_XY(1, 0);
			LCD_displayString("delay : ");
			LCD_displayInteger(i);
			LCD_displayCharacter(' ');
		}

		g_received_data = SPI_sendReceiveByte(DUMMY_DATA);
	}
}
#elif (SPI == SLAVE)

	#include "DIO.h"
	#include "SPI.h"
	#include "Sensor.h"
	#include "SETTINGS.h"
	#include <util/delay.h>

	#include "LCD.h"

	#include <avr/interrupt.h>

	/* Maximum temperature that can be measured by the sensor */
	#define LM35_MAX_TEMPERATURE 150
	/* the voltage of the sensor at the maximum temperature */
	#define LM35_MAX_VOLT		 1.5

	#define EXTI_PORT			 PORTD_ID
	#define EXTI_PIN			 PIN2_ID

uint8 temp_value = 0;

void SPI_ISR()
{
	SPI_sendReceiveByte(temp_value);
}

void slave_app()
{
	DIO_SetPinDirection(EXTI_PORT, EXTI_PIN, PIN_OUTPUT);

	SPI_SetCallBack(SPI_ISR);
	SPI_init(SPI_Slave, SPI_FOSC_128);

	ADC_ConfigType ADC_config = {.ref_volt = ADC_AVCC,
								 .prescaler = ADC_PRESCALER_128,
								 .auto_trigger_source = ADC_SINGLE_CONVERSION_MODE};
	ADC_init(&ADC_config);

	SPI_InterruptEnable();
	sei();

	while (1)
	{
		temp_value = LM35_Read();

		if (temp_value > 50)
		{
			DIO_SetPinValue(EXTI_PORT, EXTI_PIN, LOGIC_HIGH); // trigger the interrupt
		}
		else
		{
			DIO_SetPinValue(EXTI_PORT, EXTI_PIN, LOGIC_LOW);
		}
	}
}
#endif

void SPI_App(void)
{
#if (SPI == MASTER)
	master_app();
#elif (SPI == SLAVE)
	slave_app();
#endif
}