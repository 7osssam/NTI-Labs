/******************************************************************
 * @Project	 	: 7amok4a Playground
 * @Description : A simple game for two players using the LCD and the keypad.
 * @target  	: ATMEGA32 (eta32)
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc  
 * @Notes    	: 
 ********************************************************************/

#ifndef PLAYGROUND_H_
#define PLAYGROUND_H_

#include "DIO.h"
#include "LCD.h"
#include "Buzzer.h"

#include "STD_TYPES.h"
#include "KEYPAD.h"

#define PLAYERS_POSSIBLE_POSITIONS 2
#define MAX_SCORE				   5

/************ Delay Times ************/
#define DELAY_TIME				   500
#define BALL_DELAY_TIME			   100

/************ 7amok4a Keys (Left Player) ************/
#define _7amok4a_UP_KEY			   7
#define _7amok4a_DOWN_KEY		   1
#define _7amok4a_COL			   0

/************ 7azal2om Keys (Right Player) ************/
#define _7azal2om_UP_KEY		   9
#define _7azal2om_DOWN_KEY		   3
#define _7azal2om_COL			   (LCD_NUM_POSITIONS - 1)

/************ Ball Keys ************/
#define Ball_UP_KEY				   8
#define Ball_DOWN_KEY			   2

/************ Reset Key ************/
#define RESET_KEY				   5

/**
 * @brief Initializes the game playground including the LCD and custom characters.
 */
void Playground_init();

/**
 * @brief Main loop for the game playground that handles the game logic and user input.
 */
void Playground_MainLoop();

#endif /* PLAYGROUND_H_ */