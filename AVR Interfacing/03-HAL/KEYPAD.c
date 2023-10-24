/******************************************************************
 * @Module   	: Keypad Module
 * @Title 	 	: Source file for Keypad Module
 * @Filename 	: KEYPAD.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#include "KEYPAD.h"
#include "DIO.h"

#include "SETTINGS.h"
#include <util/delay.h>

// clang-format off
#if (KEYPAD_NUM_COLS == 3)
	static uint8 KEYPAD_4x3[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
		{ 1 , 2,  3 },
		{ 4 , 5,  6 },
		{ 7 , 8,  9 },
		{'*', 0, '#'}};
#elif (KEYPAD_NUM_COLS == 4)
	static uint8 KEYPAD_4x4[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
		{ 7 , 8,  9 , '/'},
		{ 4 , 5,  6 , '*'},
		{ 1 , 2,  3 , '-'},
		{'C', 0, '=', '+'}};
#endif /* KEYPAD_NUM_COLS */
// clang-format on 

static uint8 KEYPAD_ROW_pins[KEYPAD_NUM_ROWS] = {KEYPAD_ROW1_PIN_ID, KEYPAD_ROW2_PIN_ID, KEYPAD_ROW3_PIN_ID, KEYPAD_ROW4_PIN_ID};
static uint8 KEYPAD_COL_pins[KEYPAD_NUM_COLS] = {KEYPAD_COL1_PIN_ID, KEYPAD_COL2_PIN_ID, KEYPAD_COL3_PIN_ID, KEYPAD_COL4_PIN_ID};

uint8 KEYPAD_getPressedKey()
{
	uint8 PressedKey = KEYPAD_NO_PRESSED_KEY;

	for (int row = 0; row < KEYPAD_NUM_ROWS; row++)
	{
		/*
		 * Each time setup the direction for all keypad port as input pins,
		 * except this row will be output pin
		 */
		DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_pins[row], PIN_OUTPUT);

		/* Set/Clear the row output pin */
		DIO_SetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_pins[row], KEYPAD_BUTTON_PRESSED);

		for (int col = 0; col < KEYPAD_NUM_COLS; col++)
		{
			if (DIO_ReadPin(KEYPAD_COL_PORT_ID, KEYPAD_COL_pins[col]) == KEYPAD_BUTTON_PRESSED)
			{
#if (KEYPAD_NUM_COLS == 3)
				//return KEYPAD_4x3[row][col];
				PressedKey = KEYPAD_4x3[row][col];
#elif (KEYPAD_NUM_COLS == 4)
				//return KEYPAD_4x4[row][col];
				PressedKey = KEYPAD_4x4[row][col];

#endif /* KEYPAD_NUM_COLS */
			}
		}

		DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_pins[row], PIN_INPUT);
		_delay_ms(5);
	}

	return PressedKey;
}
