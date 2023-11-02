
#include "LCD.h"
#include "DIO.h"
#include "ADC.h"
#include "TIMER.h"
#include "Servo.h"
#include "ICU.h"

#include <avr/interrupt.h>

#include "SETTINGS.h"
#include <avr/delay.h>

volatile uint8 edgeFlag = 0;
volatile uint8 period = 0;
volatile uint8 TimeON = 0;

void ICU_ISR(void)
{
	if (edgeFlag == 0)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(ICU_RISING);

		edgeFlag = 1;
	}
	else if (edgeFlag == 1)
	{
		period = ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(ICU_FALLING);
		edgeFlag = 2;
	}
	else if (edgeFlag == 2)
	{
		TimeON = ICU_getInputCaptureValue();
		edgeFlag = 3;
		ICU_deInit();
	}
}

void ICU_APP()
{
	ICU_setCallBack(ICU_ISR);
	DIO_init(&DIO_Configuration);
	LCD_init();

	ICU_ConfigType ICU_Config = {.clock = TIMER_F_CPU_1024, .edge = ICU_RISING};
	ICU_init(&ICU_Config);

	sei();

	while (1)
	{
		if (edgeFlag == 3)
		{
			LCD_Goto_XY(0, 0);
			LCD_displayString("Period: ");
			LCD_displayInteger(period);

			LCD_Goto_XY(1, 0);
			LCD_displayString("TimeON: ");
			LCD_displayInteger(TimeON);

			LCD_Goto_XY(2, 0);
			LCD_displayString("Duty: ");
			LCD_displayInteger((TimeON * 100) / period);
		}
		else
		{
			LCD_Goto_XY(0, 0);
			LCD_displayString("Measuring...");
		}
	}
}
