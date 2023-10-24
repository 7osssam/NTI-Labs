#ifndef PLAYGROUND_H_
#define PLAYGROUND_H_

#include "DIO.h"
#include "LCD.h"
#include "Buzzer.h"

#include "STD_TYPES.h"
#include "KEYPAD.h"

#define LCD_NUM_LINES			   4
#define LCD_NUM_POSITIONS		   20

#define PLAYERS_POSSIBLE_POSITIONS 2

#define _7amok4a_ADDRESS		   0
#define _7azal2om_ADDRESS		   1
#define Ball_ADDRESS			   2

#define DELAY_TIME				   300
#define BALL_DELAY_TIME			   100

#define _7amok4a_UP_KEY			   7
#define _7amok4a_DOWN_KEY		   1
#define _7amok4a_COL			   0

#define _7azal2om_UP_KEY		   9
#define _7azal2om_DOWN_KEY		   3
#define _7azal2om_COL			   (LCD_NUM_POSITIONS - 1)

#define Ball_UP_KEY				   8
#define Ball_DOWN_KEY			   2
#define Ball_RIGHT_KEY			   6
#define Ball_LEFT_KEY			   4

#define BALL_RTL_FLAG			   0
#define BALL_LTR_FLAG			   1

#define RESET_KEY				   5

void Playground_init();
void Playground_MainLoop();

#endif /* PLAYGROUND_H_ */