/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_config.h
 *
 * Description: Configuration file for the LCD driver
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "SETTINGS.h"
#include "STD_TYPES.h"

/*******************************************************************************
 *                        LCD Commands Options                                 *
 *******************************************************************************/
#define LCD_2_LINES_MODE		   1
#define LCD_1_LINE_MODE			   0

#define LCD_LINES_MODE			   LCD_2_LINES_MODE

#define LCD_DATA_LENGTH_8BITS_MODE 1
#define LCD_DATA_LENGTH_4BITS_MODE 0

/* LCD Modes */
#define LCD_NUM_LINES			   4
#define LCD_NUM_POSITIONS		   20

#define LCD_FIRST_LINE			   0x00 // 0x00 - 0x80
#define LCD_SECOND_LINE			   0x40 // 0x40 - 0xC0
#define LCD_THIRD_LINE			   0x14 // 0x14 - 0x94
#define LCD_FOURTH_LINE			   0x54 // 0x54 - 0xD4

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE		   _4_BIT_MODE

#if ((LCD_DATA_BITS_MODE != _4_BIT_MODE) && (LCD_DATA_BITS_MODE != _8_BIT_MODE))

	#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD RS pin configuration */ /* Eta32 mega - PA3 */
#define LCD_RS_PORT_ID	 PORTA_ID
#define LCD_RS_PIN_ID	 PIN3_ID

/* LCD E pin configuration */ /* Eta32 mega - PA2 */
#define LCD_E_PORT_ID	 PORTA_ID
#define LCD_E_PIN_ID	 PIN2_ID

#define LCD_DATA_PORT_ID PORTB_ID

#if (LCD_DATA_BITS_MODE == _4_BIT_MODE)

	// for FUNCTION_SET command
	#define LCD_DATA_LENGTH_MODE LCD_DATA_LENGTH_4BITS_MODE

	#define LCD_DB4_PIN_ID		 PIN0_ID
	#define LCD_DB5_PIN_ID		 PIN1_ID
	#define LCD_DB6_PIN_ID		 PIN2_ID
	#define LCD_DB7_PIN_ID		 PIN4_ID
#elif (LCD_DATA_BITS_MODE == _8_BIT_MODE)
	// for FUNCTION_SET command
	#define LCD_DATA_LENGTH_MODE LCD_DATA_LENGTH_8BITS_MODE
#endif

#endif /* LCD_CONFIG_H_ */