/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Hossam Mohamed 
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "STD_TYPES.h"
#include "BIT_MACROS.h"

/*******************************************************************************
 *                        Shared Configuration Parameters                      *
 *******************************************************************************/
#define LCD_NUM_LINES					   4
#define LCD_NUM_POSITIONS				   20

/*******************************************************************************
 *                                LCD Commands                                 *
 *******************************************************************************/
#define LCD_CLEAR_COMMAND				   0x01 /* replace all characters with ASCII 'space' */
#define LCD_GO_TO_HOME					   0x02 /* return cursor to first position on first line */
#define LCD_DECREMENT_CURSOR			   0x04 /* shift cursor to left */
#define LCD_INCREMENT_CURSOR			   0x06 /* shift cursor to right */
#define LCD_SHIFT_DISPLAY_RIGHT			   0x05 /* shift display to right */
#define LCD_SHIFT_DISPLAY_LEFT			   0x07 /* shift display to left */
#define LCD_CURSOR_BLINK				   0x0F /* (cursor on, blink char */
#define LCD_SHIFT_CURSOR_POSITION_TO_LEFT  0x10 /* (shift cursor to left) */

//! TODO: remove LCD_FUNCTION_SET is enough
#define LCD_TWO_LINES_EIGHT_BITS_MODE	   0x38 /* 0x38 for 8-bit mode */
#define LCD_TWO_LINES_FOUR_BITS_MODE	   0x28 /* 0x28 for 4-bit mode */
												//////!

#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1 0x33 /* 0x33 for 4-bit mode */
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2 0x32 /* 0x32 for 4-bit mode */

#define LCD_CURSOR_OFF					   0x0C /* when cursor is off, no need to blink */
#define LCD_CURSOR_ON					   0x0E /* when cursor is on, no need to blink */
#define LCD_SET_CURSOR_LOCATION			   0x80 /* Set cursor position in DDRAM */

#define LCD_FUNCTION_SET				   CONCAT_8BIT(0, 0, 1, LCD_DATA_LENGTH_MODE, LCD_LINES_MODE, 0, 0, 0)
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief Initialize the LCD module.
 *
 * This function initializes the LCD module, configuring the necessary control pins
 * (RS and E) and setting the appropriate data bits mode (4-bit or 8-bit). It also
 * configures the LCD display mode, cursor settings, and clears the LCD at the beginning.
 *
 * @note Ensure that the appropriate pins and data bus configuration are set before
 * calling this function. The initialization process may vary depending on the selected
 * data bits mode (4-bit or 8-bit).
 *
 * @warning This function should be called before using the LCD for displaying any data.
 *
 * @see LCD_sendCommand
 */
void LCD_init(void);

/**
 * @brief Send a command to the LCD module.
 *
 * This function sends a command to the LCD module using the specified data bits mode
 * (4-bit or 8-bit) and the appropriate control signals.
 *
 * @param command The command to send to the LCD.
 *
 * @note This function provides control over the RS (Register Select) and E (Enable) pins
 * and allows sending commands to the LCD, such as clearing the display, setting the cursor
 * position, and controlling various display settings.
 *
 * @warning When using 4-bit mode, this function sends the command in two 4-bit nibbles,
 * with appropriate delays and control signals. Ensure that the data bus pins and control
 * pins are properly configured before calling this function.
 */
void LCD_sendCommand(uint8 command);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_Goto_XY(uint8 row, uint8 col);

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char* Str);

/*
 * Description :
 * Display the required string in the center of the screen of specified row
 */
void LCD_displayStringCenter(uint8 row, const char* Str);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char* Str);

/*
 * Description :
 * Display special character at a specified location on the screen (GDDRAM)
 */
void LCD_displaySpecialCharacter(uint8* Pattern, uint8 Location);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_displayInteger(sint32 num);

/*
 * Description :
 * Display the required float value on the screen
 */
void LCD_displayFloat(float32 num, uint8 numAfterDecimal);

/*
 * Description :
 * Display Binary number on the screen (8-bits)
 */
void LCD_displayBinary(uint8 num);

/*
 * Description :
 * Display Hexadecimal number on the screen (8-bits)
 */
void LCD_displayHex(uint8 num);

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
