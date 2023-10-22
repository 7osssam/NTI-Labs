/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: KEYPAD.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/
#include "KEYPAD.h"
#include "DIO.h"

#include "SETTINGS.h"
#include <util/delay.h>

/*******************************************************************************
 *                       Private Variables                                     *
 *******************************************************************************/
// disable formatting for this section
// clang-format off
#ifdef STANDARD_KEYPAD /* for eta32mini kit */
	#if (KEYPAD_NUM_COLS == 3)
static unit8 KEYPAD_4x3[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9},
	{'*', 0, '#'}};

	#elif (KEYPAD_NUM_COLS == 4)
static uint8 KEYPAD_4x4[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
	{ 7 , 8,  9 , '/'},
	{ 4 , 5,  6 , '*'},
	{ 1 , 2,  3 , '-'},
	{'C', 0, '=', '+'}};
	#endif /* KEYPAD_NUM_COLS */
#endif	   /* STANDARD_KEYPAD */
// clang-format on

static uint8 KEYPAD_ROW_pins[KEYPAD_NUM_ROWS] = {KEYPAD_ROW1_PIN_ID, KEYPAD_ROW2_PIN_ID, KEYPAD_ROW3_PIN_ID,
												 KEYPAD_ROW4_PIN_ID};
static uint8 KEYPAD_COL_pins[KEYPAD_NUM_COLS] = {KEYPAD_COL1_PIN_ID, KEYPAD_COL2_PIN_ID, KEYPAD_COL3_PIN_ID,
												 KEYPAD_COL4_PIN_ID};

/*******************************************************************************
 *                      Functions Definitions                                  **
 *******************************************************************************/

uint8 KEYPAD_getPressedKey(void)
{
	uint8 col, row;
	DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW1_PIN_ID, PIN_INPUT);
	DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW2_PIN_ID, PIN_INPUT);
	DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW3_PIN_ID, PIN_INPUT);
	DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW4_PIN_ID, PIN_INPUT);

	DIO_SetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL1_PIN_ID, PIN_INPUT);
	DIO_SetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL2_PIN_ID, PIN_INPUT);
	DIO_SetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL3_PIN_ID, PIN_INPUT);
#if (KEYPAD_NUM_COLS == 4)
	DIO_SetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL4_PIN_ID + 3, PIN_INPUT);
#endif

	for (row = 0; row < KEYPAD_NUM_ROWS; row++) /* loop for rows */
	{
		/*
		 * Each time setup the direction for all keypad port as input pins,
		 * except this row will be output pin
		 */
		DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_pins[row], PIN_OUTPUT);

		/* Set/Clear the row output pin */
		DIO_SetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_pins[row], KEYPAD_BUTTON_PRESSED);

		for (col = 0; col < KEYPAD_NUM_COLS; col++) /* loop for columns */
		{
			/* Check if the switch is pressed in this column */
			if (DIO_ReadPin(KEYPAD_COL_PORT_ID, KEYPAD_COL_pins[col]) == KEYPAD_BUTTON_PRESSED)
			{
#if (KEYPAD_NUM_COLS == 3)
	#ifdef STANDARD_KEYPAD
				// return KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
				return KEYPAD_4x3[row][col];
	#else
				return ((row * KEYPAD_NUM_COLS) + col + 1);
	#endif
#elif (KEYPAD_NUM_COLS == 4)
	#ifdef STANDARD_KEYPAD
				// return KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
				return KEYPAD_4x4[row][col];
	#else
				return ((row * KEYPAD_NUM_COLS) + col + 1);
	#endif

#endif /* KEYPAD_NUM_COLS */
			}
		}
		DIO_SetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_pins[row], PIN_INPUT);
		_delay_ms(5); /* Add small delay to fix CPU load issue in proteus */
	}
}
