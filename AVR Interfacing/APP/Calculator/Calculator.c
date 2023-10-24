

#include "Calculator.h"
#include "Algo.h"

#include "KEYPAD.h"
#include "LCD.h"
#include "STD_TYPES.h"

#include "SETTINGS.h"
#include <util/delay.h>

#define MAX_NORMAL_CALC_LENGTH MAX_EXPRESSION_LENGTH

#define MAIN_MENU_KEY_FLAG	   0
#define CLEAR_KEY_FLAG		   1

#define NORMAL_MODE			   0xCC
#define PROGRAMMER_MODE		   0xAA

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/***********************************************************************************
 * 								 Private Functions								   *
 ***********************************************************************************/

/**
 * The function DecimaltoChar converts a decimal number to its corresponding character representation.
 * 
 * @param num The parameter "num" is of type uint8, which means it is an unsigned 8-bit integer.
 * 
 * @return The character representation of the input number.
 */
static char DecimaltoChar(uint8 num)
{
	return num + '0';
}

/**
 * @brief Helper function to reset Reset the InputExpression array.
 * @param[in] InputExpression The expression to reset.
 */
static void ResetExpression(uint8* InputExpression)
{
	for (uint8 i = 0; i < MAX_NORMAL_CALC_LENGTH; i++)
	{
		InputExpression[i] = 0;
	}
}

/**
 * @brief Display the reset menu on the LCD and handle user input.
 * @param[in] Mode The calculator mode (NORMAL_MODE or PROGRAMMER_MODE).
 * @return MAIN_MENU_KEY_FLAG (0) to return to the main menu or CLEAR_KEY_FLAG (1) to reset the calculator.
 */
static uint8 ResetMenu(uint8 Mode)
{
	uint8 ExitMenuKey = KEYPAD_NO_PRESSED_KEY;

	LCD_displayStringRowColumn(LCD_NUM_LINES - 1, 0, "C:CLR");
	LCD_displayStringRowColumn(LCD_NUM_LINES - 1, LCD_NUM_POSITIONS - 6, "0:EXIT");

	LCD_sendCommand(LCD_CURSOR_OFF); // turn off the cursor
	LCD_sendCommand(LCD_GO_TO_HOME); // reset the cursor to the home position

	while (1)
	{
		do
		{
			ExitMenuKey = KEYPAD_getPressedKey();
		} while (ExitMenuKey == KEYPAD_NO_PRESSED_KEY); /* wait until a key is pressed */

		if (ExitMenuKey == 'C') /* if the user pressed C, reset the calculator */
		{
			LCD_clearScreen();
			ExitMenuKey = CLEAR_KEY_FLAG;
			break;
		}
		else if (ExitMenuKey == 0) /* if the user pressed 0, return to the main menu */
		{
			LCD_clearScreen();
			ExitMenuKey = MAIN_MENU_KEY_FLAG;
			break;
		}
		// if user pressed another operator, return to the normal mode and add the operator to the expression
		else if (ExitMenuKey == '/' || ExitMenuKey == '*' || ExitMenuKey == '-' || ExitMenuKey == '+')
		{
			if (Mode == NORMAL_MODE)
			{
				LCD_clearScreen();
				return ExitMenuKey;
			}
			else
			{
				/* Do nothing */
			}
		}

		_delay_ms(DELAY_PRESS_TIME);
	}
	return ExitMenuKey;
}

/**
 * @brief Handle the normal calculator mode.
 * @return MAIN_MENU_KEY_FLAG (0) to return to the main menu or CLEAR_KEY_FLAG (1) to reset the calculator.
 */
static uint8 NormalMode(void)
{
	uint8 EqualKeyFlag = FALSE;
	uint8 ExitMenuFlag = 0;

	uint8 input_index = 0;
	uint8 input = KEYPAD_NO_PRESSED_KEY;

	uint8 InputExpression[MAX_NORMAL_CALC_LENGTH] = {0};

	sint16 result = 0;

	while (EqualKeyFlag == FALSE)
	{
		// trun on cursor
		LCD_sendCommand(LCD_CURSOR_ON);
		do
		{
			input = KEYPAD_getPressedKey();
		} while (input == KEYPAD_NO_PRESSED_KEY); /* wait until a key is pressed */

		if (input == '=') // if the user pressed =, calculate the result
		{
			result = CalculateExpression(InputExpression);

			// set zeros to InputExpression array to clear it
			ResetExpression(InputExpression);

			LCD_Goto_XY(1, 0);
			LCD_displayCharacter('=');
			LCD_displayInteger(result);

			ExitMenuFlag = ResetMenu(NORMAL_MODE); /* to return to the main menu or reset the calculator */

			// if the user pressed an operator again after the result
			if (ExitMenuFlag != CLEAR_KEY_FLAG && ExitMenuFlag != MAIN_MENU_KEY_FLAG)
			{
				input_index = 0;			// reset the input index to start from the beginning of the array
				uint8 NegativeFlag = FALSE; // to handle negative numbers

				if (result < 0)
				{
					NegativeFlag = TRUE; // set the flag
					result *= -1;		 // make the number positive
				}

				/* convert every digit of the result from decimal to char and save it in InputExpression array */
				while (result != 0)
				{
					//InputExpression[input_index++] = (result % 10) + '0';
					InputExpression[input_index++] = DecimaltoChar(result % 10);
					result /= 10;
				}
				if (NegativeFlag == TRUE)
				{
					InputExpression[input_index++] = '-'; // add the negative sign back to the expression
				}

				/* reverse the InputExpression array */
				for (uint8 i = 0; i < input_index / 2; i++)
				{
					uint8 temp = InputExpression[i];
					InputExpression[i] = InputExpression[input_index - i - 1];
					InputExpression[input_index - i - 1] = temp;
				}

				/* save the operator next to the expression */
				InputExpression[input_index++] = ExitMenuFlag;

				LCD_displayString(InputExpression);
			}
			else
			{
				EqualKeyFlag = TRUE; /* to exit the while loop */
			}
		}
		else if (input == 'C') // if the user pressed C, clear the last input from the LCD
		{
			if (input_index > 0)
			{
				input_index--;						// decrement i to remove the last input from the array
				InputExpression[input_index] = 0;	// set the last input to zero
				LCD_sendCommand(LCD_GO_TO_HOME);	// reset the cursor to the home position
				LCD_clearScreen();					// clear the LCD
				LCD_displayString(InputExpression); // display the new expression without the last input
			}
		}
		else
		{
			if (isCharDigit(DecimaltoChar(input))) // if the input is a number '0' - '9'
			{
				InputExpression[input_index] = DecimaltoChar(input); // save the input in the array
				LCD_displayInteger(input);
			}
			else // if the input is an operator
			{
				// if the user entered an operator as the first input or after another operator (except '-' to handle negative numbers)
				if (input_index == 0 || isOperator(InputExpression[input_index - 1]) == TRUE)
				{
					// handle negative numbers
					if (input == '-')
					{
						/* do nothing */
					}
					else
					{
						// display an error message
						LCD_clearScreen();
						LCD_displayString("Invalid Input");
						_delay_ms(1000);
						LCD_clearScreen();

						input_index = 0;
						ResetExpression(InputExpression);

						// skip the rest of the loop and wait for the user to enter a valid input
						continue;
					}
				}

				InputExpression[input_index] = input;
				LCD_displayCharacter(input);
			}

			input_index++; // increment i to save the next input in the next index

			if (input_index == MAX_NORMAL_CALC_LENGTH - 1) // if the user entered the maximum number of inputs
			{
				// display an error message
				LCD_clearScreen();
				LCD_displayString("Max Input Reached");
				_delay_ms(1000);
				LCD_clearScreen();

				// reset the calculator
				ExitMenuFlag = MAIN_MENU_KEY_FLAG;
				EqualKeyFlag = TRUE; /* to exit the while loop */
			}
		}
		_delay_ms(DELAY_PRESS_TIME);
	}

	return ExitMenuFlag;
}

/**
 * @brief Handle the programmer calculator mode.
 * @return MAIN_MENU_KEY_FLAG (0) to return to the main menu or CLEAR_KEY_FLAG (1) to reset the calculator.
 */
static uint8 ProgrammerMode(void)
{
	uint8 EqualKeyFlag = FALSE;
	uint8 ExitMenuFlag = 0;

	uint8 key = KEYPAD_NO_PRESSED_KEY;
	uint8 num = 0;
	LCD_sendCommand(LCD_GO_TO_HOME);

	while (EqualKeyFlag == FALSE)
	{
		LCD_sendCommand(LCD_CURSOR_ON);

		do
		{
			key = KEYPAD_getPressedKey();
		} while (key == KEYPAD_NO_PRESSED_KEY); /* wait until a key is pressed */

		if (key >= 0 && key <= 9)
		{
			num = num * 10 + key;
			LCD_displayInteger(key);
		}
		else if (key == '=')
		{
			LCD_clearScreen();

			LCD_Goto_XY(0, 0);
			LCD_displayString("0b");
			LCD_displayBinary(num);

			LCD_Goto_XY(1, 0);
			LCD_displayString("0x");
			LCD_displayHex(num);

			EqualKeyFlag = TRUE; /* to exit the while loop */

			ExitMenuFlag = ResetMenu(PROGRAMMER_MODE);
		}
		_delay_ms(DELAY_PRESS_TIME);
	}

	return ExitMenuFlag;
}

/***********************************************************************************
 * 								Public Functions								   *
 ***********************************************************************************/
/**
 * @brief Display the main menu on the LCD and handle user input to choose the calculator mode.
 */
void CalculatorMenu(void)
{
	uint8 option = KEYPAD_NO_PRESSED_KEY; /* to store the user's choice */
	uint8 returnValue = 0;				  /* to store the return value of each function */
	LCD_init();

	LCD_displayStringCenter(1, "CALCULATOR");
	_delay_ms(100);
	LCD_displayStringCenter(0, "2 Modes");

	_delay_ms(500);
	LCD_clearScreen(); /* clear LCD at the beginning */

	while (1) // Super Loop
	{
		LCD_displayStringCenter(0, "CALCULATOR MENU");
		LCD_displayStringRowColumn(1, 0, "1-Normal");
		LCD_displayStringRowColumn(2, 0, "2-Programmer");

		do
		{
			option = KEYPAD_getPressedKey();
		} while (option == KEYPAD_NO_PRESSED_KEY); /* wait until a key is pressed */

		_delay_ms(DELAY_PRESS_TIME); /* Press time */

		LCD_clearScreen(); /* clear LCD at the beginning */

		switch (option)
		{
			case 1:
				do
				{
					returnValue = NormalMode();
				} while (returnValue == CLEAR_KEY_FLAG);

				break;
			case 2:
				do
				{
					returnValue = ProgrammerMode();
				} while (returnValue == CLEAR_KEY_FLAG);

				break;
		}
	}
}
