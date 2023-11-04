#include "LCD.h"

#include "SETTINGS.h"
#include <util/delay.h>

#include "EEPROM_Services.h"
#include "EEPROM.h"
#include "EEPROM_APP.h"

#include <avr/io.h>

void EEPROM_APP()
{
	EEPROM_init();

	LCD_init();

	uint8 data = 150;

	if (EEPROM_writeByte(0x300, 200))
	{
		_delay_ms(60);

		LCD_displayStringCenter(0, "Error Writing");
		_delay_ms(500);
	}
	else
	{
		LCD_displayStringCenter(0, "Success Writing");
		_delay_ms(500);

		if (EEPROM_readByte(0x300, &data))
		{
			_delay_ms(60);

			LCD_displayStringCenter(1, "Error Reading");
			_delay_ms(500);
		}
		else
		{
			LCD_displayStringCenter(1, "Success Reading");
			LCD_displayStringCenter(2, "And data is ");
			LCD_displayInteger(data);

			_delay_ms(500);
		}
	}
}