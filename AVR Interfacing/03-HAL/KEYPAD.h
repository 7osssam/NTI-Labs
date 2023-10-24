/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: KEYPAD.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "STD_TYPES.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS		   4
#define KEYPAD_NUM_ROWS		   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID	   PORTC_ID
#define KEYPAD_ROW1_PIN_ID	   PIN5_ID
#define KEYPAD_ROW2_PIN_ID	   PIN4_ID
#define KEYPAD_ROW3_PIN_ID	   PIN3_ID
#define KEYPAD_ROW4_PIN_ID	   PIN2_ID

#define KEYPAD_COL_PORT_ID	   PORTD_ID
#define KEYPAD_COL1_PIN_ID	   PIN7_ID
#define KEYPAD_COL2_PIN_ID	   PIN6_ID
#define KEYPAD_COL3_PIN_ID	   PIN5_ID
#define KEYPAD_COL4_PIN_ID	   PIN3_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED  LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED LOGIC_HIGH

#define KEYPAD_NO_PRESSED_KEY  0xFF

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * @brief Get the pressed key from the keypad.
 *
 * This function scans the rows and columns of the keypad to detect a keypress.
 * When a key is pressed, it returns the corresponding key value, or KEYPAD_NO_PRESSED_KEY
 * if no key is currently pressed. It also sets up the keypad row and column pins
 * for scanning and resets their directions to input after scanning.
 *
 * @return The value of the pressed key (0-9, '*', '#', '+', '-', '/', 'C'), or KEYPAD_NO_PRESSED_KEY if no key is pressed.
 * 
 * @note This function can be used as a blocking function, or it can be called periodically to check for a keypress.
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
