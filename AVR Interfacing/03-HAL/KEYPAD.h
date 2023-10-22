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

#define STANDARD_KEYPAD

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

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
