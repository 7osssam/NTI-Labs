
#include "TIMER.h"
#include "LCD.h"
#include "STD_TYPES.h"
#include "KEYPAD.h"
#include "DIO.h"

#include "SETTINGS.h"
#include <util/delay.h>
#include <avr/interrupt.h>

uint32 overflow = 0;

void Counter_ISR(void)
{
	overflow += 256;
}

void counter_app(void)
{
	DIO_init(&DIO_Configuration);
	LCD_init();

	Timer0_ConfigType Counter_Config = {.initial_value = 0,
										.Timer0_Mode = TIMER0_NORMAL_MODE,
										.Clock_source = TIMER_EXTERNAL_FALLING,
										.OC0_Mode = OC0_DISCONNECTED};

	Timer0_init(&Counter_Config);
	Timer0_OVF_SetCallBack(Counter_ISR);

	sei();

	while (1)
	{
		uint8  TCNT0_value = Timer0_ReadTCNT0();
		uint32 counter = TCNT0_value + overflow;

		if (DIO_ReadPin(PORTD_ID, PIN0_ID) == LOGIC_LOW)
		{
			//reset counter
			Timer0_WriteToTCNT0(0);

			//TCNT0_value = 0; // this line is not needed as the TCNT0_value is already 0
			overflow = 0;
			counter = 0;
		}

		LCD_Goto_XY(0, 0);
		LCD_displayString("Counter: ");
		LCD_displayInteger(counter);

		_delay_ms(20); // debounce delay
	}
}