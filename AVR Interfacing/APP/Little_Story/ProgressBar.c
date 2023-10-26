#include "ProgressBar.h"

#include "LCD.h"

/* the remaining characters of the bar are filled with empty characters */
#define EMPTY_BAR_CHARS ' '

void ProgressBar_init()
{
	uint8 _1_BIT_BAR[8] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};

	uint8 _2_BIT_BAR[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};

	uint8 _3_BIT_BAR[8] = {0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};

	uint8 _4_BIT_BAR[8] = {0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};

	uint8 _5_BIT_BAR[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

	LCD_displaySpecialCharacter(_1_BIT_BAR, _1_BIT_BAR_ADDRESS);
	LCD_displaySpecialCharacter(_2_BIT_BAR, _2_BIT_BAR_ADDRESS);
	LCD_displaySpecialCharacter(_3_BIT_BAR, _3_BIT_BAR_ADDRESS);
	LCD_displaySpecialCharacter(_4_BIT_BAR, _4_BIT_BAR_ADDRESS);
	LCD_displaySpecialCharacter(_5_BIT_BAR, _5_BIT_BAR_ADDRESS);
}

void ProgressBar(uint32 MaximumValue, uint32 CurrentValue, uint8 LineNumber)
{
	/* to make sure that the current value doesn't exceed the maximum value */
	if (CurrentValue > MaximumValue || LineNumber > LCD_NUM_LINES - 1)
	{
		return;
	}

	uint8		 i;
	static uint8 LastPattern = 0; // to keep track of the last pattern displayed

	float32 bar_width = ((float32)LCD_NUM_POSITIONS / MaximumValue) * CurrentValue;

	uint8 bar_width_int = (uint8)bar_width;

	LCD_Goto_XY(LineNumber, 0);

	if (bar_width >= 1)
	{
		for (i = 1; i <= bar_width; i++)
		{
			LCD_displayCharacter(_5_BIT_BAR_ADDRESS); // the location of the full 5-bits bar
		}

		bar_width = bar_width - (i - 1); // to get the remaining width of the bar
	}

	LastPattern = bar_width * 5; // multiplying by 5 to get the location of the last pattern

	switch (LastPattern)
	{
		case 0:
			break;
		case 1: // the location of the 1-bit bar
			LCD_displayCharacter(_1_BIT_BAR_ADDRESS);
			break;
		case 2: // the location of the 2-bits bar
			LCD_displayCharacter(_2_BIT_BAR_ADDRESS);
			break;
		case 3: // the location of the 3-bits bar
			LCD_displayCharacter(_3_BIT_BAR_ADDRESS);
			break;
		case 4: // the location of the 4-bits bar
			LCD_displayCharacter(_4_BIT_BAR_ADDRESS);
			break;
	}

	// Clearing the remaining line of the bar until the end of the screen
	for (uint8 j = 0; j < (LCD_NUM_POSITIONS - bar_width_int - 1); j++)
	{
		LCD_displayCharacter(EMPTY_BAR_CHARS);
	}

	// to reset the last pattern when reaching 100% or more
	if (bar_width_int >= LCD_NUM_POSITIONS)
	{
		LastPattern = 0;
	}
}
