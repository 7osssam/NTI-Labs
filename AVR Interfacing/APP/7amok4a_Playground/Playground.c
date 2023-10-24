
#include "Playground.h"

#include "SETTINGS.h"
#include <util/delay.h>

sint8 _7amok4a_Position = 0;
sint8 _7azal2om_Position = 0;
sint8 Ball_col = 0;
sint8 Ball_row = 0;

uint8 Ball_speed_delay = BALL_DELAY_TIME;

/* when the ball is moving from left to right, the flag is set to 1 (BALL_RTL_FLAG)
 * when the ball is moving from right to left, the flag is set to 0 (BALL_LTR_FLAG) */
uint8 Wall_flag = BALL_RTL_FLAG;

static void CustomCharacter_init()
{
	uint8 _7amok4a[8] = {0x0E, 0x0A, 0x0E, 0x05, 0x1F, 0x14, 0x04, 0x0A};

	uint8 _7azal2om[8] = {0x0E, 0x0A, 0x0E, 0x14, 0x1F, 0x05, 0x04, 0x0A};

	uint8 Ball[8] = {0x00, 0x04, 0x0E, 0x1F, 0x1F, 0x0E, 0x04, 0x00};

	LCD_displaySpecialCharacter(_7amok4a, _7amok4a_ADDRESS);
	LCD_displaySpecialCharacter(_7azal2om, _7azal2om_ADDRESS);
	LCD_displaySpecialCharacter(Ball, Ball_ADDRESS);
}

static void Ball_Loop()
{
	if (Ball_row > LCD_NUM_LINES)
	{
		Ball_row = LCD_NUM_LINES;
	}
	else if (Ball_row < 0)
	{
		Ball_row = 0;
	}

	if (Ball_col == LCD_NUM_POSITIONS - 1)
	{
		Wall_flag = 1;
	}
	else if (Ball_col == 0)
	{
		Wall_flag = 0;
	}

	LCD_Goto_XY(Ball_row, Ball_col);
	LCD_displayCharacter(Ball_ADDRESS);
	_delay_ms(BALL_DELAY_TIME);

	LCD_Goto_XY(Ball_row, Ball_col);
	LCD_displayCharacter(' ');

	if (Wall_flag == BALL_RTL_FLAG)
	{
		Ball_col++;
	}
	else if (Wall_flag == BALL_LTR_FLAG)
	{
		Ball_col--;
	}
}

static void PlayersKey_Update(uint8 key)
{
	if (key == _7amok4a_UP_KEY)
	{
		LCD_Goto_XY(_7amok4a_Position, 0);
		LCD_displayCharacter(' ');
		_7amok4a_Position--;

		if (_7amok4a_Position < 0)
		{
			_7amok4a_Position = 0;
		}
	}
	else if (key == _7amok4a_DOWN_KEY)
	{
		LCD_Goto_XY(_7amok4a_Position, _7amok4a_COL);
		LCD_displayCharacter(' ');
		_7amok4a_Position++;

		if (_7amok4a_Position > PLAYERS_POSSIBLE_POSITIONS)
		{
			_7amok4a_Position = PLAYERS_POSSIBLE_POSITIONS;
		}
	}

	if (key == _7azal2om_UP_KEY)
	{
		LCD_Goto_XY(_7azal2om_Position, _7azal2om_COL);
		LCD_displayCharacter(' ');
		_7azal2om_Position--;

		if (_7azal2om_Position < 0)
		{
			_7azal2om_Position = 0;
		}
	}
	else if (key == _7azal2om_DOWN_KEY)
	{
		LCD_Goto_XY(_7azal2om_Position, _7azal2om_COL);
		LCD_displayCharacter(' ');
		_7azal2om_Position++;

		if (_7azal2om_Position > PLAYERS_POSSIBLE_POSITIONS)
		{
			_7azal2om_Position = PLAYERS_POSSIBLE_POSITIONS;
		}
	}
}

static void PlayersGUI_Update()
{
	LCD_Goto_XY(_7amok4a_Position, _7amok4a_COL);
	LCD_displayCharacter(_7amok4a_ADDRESS);

	LCD_Goto_XY(_7azal2om_Position, _7azal2om_COL);
	LCD_displayCharacter(_7azal2om_ADDRESS);
}

static void Ball_Update(uint8 key)
{
	switch (key)
	{
		case Ball_UP_KEY:
			LCD_Goto_XY(Ball_row, Ball_col);
			LCD_displayCharacter(' ');
			Ball_row--;
			if (Ball_row < 0)
			{
				Ball_row = 0;
			}
			break;

		case Ball_DOWN_KEY:
			LCD_Goto_XY(Ball_row, Ball_col);
			LCD_displayCharacter(' ');
			Ball_row++;
			if (Ball_row > PLAYERS_POSSIBLE_POSITIONS)
			{
				Ball_row = PLAYERS_POSSIBLE_POSITIONS;
			}
			break;
		case Ball_RIGHT_KEY:
			if (Wall_flag == BALL_RTL_FLAG)
			{
				//increase the speed of the ball
				if (Ball_speed_delay > 1)
				{
					Ball_speed_delay--;
				}
			}
			else
			{
				//decrease the speed of the ball
				if (Ball_speed_delay < BALL_DELAY_TIME)
				{
					Ball_speed_delay++;
				}
			}

			break;

		case Ball_LEFT_KEY:
			break;
	}

	LCD_Goto_XY(Ball_row, Ball_col);
	LCD_displayCharacter(Ball_ADDRESS);
}

void Playground_init()
{
	LCD_init();
	Buzzer_init();
	CustomCharacter_init();
}

void Playground_MainLoop()
{
	uint8 _7amok4a_score = 0;
	uint8 _7azal2om_score = 0;

	uint8 key = 0;

	while (1)
	{
		key = KEYPAD_getPressedKey();

		PlayersKey_Update(key);

		if (key == Ball_UP_KEY || key == Ball_DOWN_KEY || key == Ball_RIGHT_KEY || key == Ball_LEFT_KEY)
		{
			Ball_Update(key);
		}

		PlayersGUI_Update();

		Ball_Loop();

		if (Ball_col <= _7amok4a_COL && Ball_row != _7amok4a_Position)
		{
			_7azal2om_score++; // increase the opponent score
			Buzzer_Alarm();
		}
		if (Ball_col >= _7azal2om_COL && Ball_row != _7azal2om_Position)
		{
			_7amok4a_score++; // increase the player score
			Buzzer_Alarm();
		}

		LCD_Goto_XY(3, 0);
		LCD_displayString("L: ");
		LCD_displayInteger(_7amok4a_score);
		LCD_Goto_XY(3, 15);
		LCD_displayString("R: ");
		LCD_displayInteger(_7azal2om_score);

		if (key == RESET_KEY)
		{
			LCD_clearScreen();
			LCD_displayStringCenter(1, "RESET GAME");
			_delay_ms(DELAY_TIME);
			LCD_clearScreen();
			_7amok4a_Position = 0;
			_7azal2om_Position = 0;
			_7amok4a_score = 0;
			_7azal2om_score = 0;

			Ball_col = 0;
			Ball_row = 0;
			Wall_flag = BALL_RTL_FLAG;
		}
	}
}