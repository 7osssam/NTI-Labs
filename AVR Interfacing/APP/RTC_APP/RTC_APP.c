#include "STD_TYPES.h"
#include "TWI.h"
#include "RTC.h"

#include "LCD.h"
void RTC_APP()
{
	RTC_init();

	LCD_init();

	RTC_t RTC_data;
	RTC_t RTC_Time;

	while (1)
	{
		RTC_GetDate(&RTC_data);
		RTC_GetTime(&RTC_Time);

		LCD_Goto_XY(0, 0);
		LCD_displayString("Date is: ");

		LCD_Goto_XY(1, 0);
		LCD_displayInteger(RTC_BCD_2_DECIMAL(RTC_data.Days));
		LCD_displayCharacter('/');
		LCD_displayInteger(RTC_BCD_2_DECIMAL(RTC_data.Months));
		LCD_displayCharacter('/');
		LCD_displayInteger(RTC_BCD_2_DECIMAL(RTC_data.Years));

		LCD_Goto_XY(2, 0);
		LCD_displayString("Time is: ");

		LCD_Goto_XY(3, 0);
		LCD_displayInteger(RTC_BCD_2_DECIMAL(RTC_Time.Hours));
		LCD_displayCharacter(':');
		LCD_displayInteger(RTC_BCD_2_DECIMAL(RTC_Time.Minutes));
		LCD_displayCharacter(':');
		LCD_displayInteger(RTC_BCD_2_DECIMAL(RTC_Time.Seconds));
	}
}