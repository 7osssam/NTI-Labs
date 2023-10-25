
#include "Playground.h"

#include "SETTINGS.h"
#include <util/delay.h>

/******************************************************
 * 		Constants and global variables
 ******************************************************/
#define BALL_RTL_FLAG	  1
#define BALL_LTR_FLAG	  0

#define _7amok4a_ADDRESS  0
#define _7azal2om_ADDRESS 1
#define Ball_ADDRESS	  2
#define Heart_ADDRESS	  3

sint8 _7amok4a_row = 0;
sint8 _7azal2om_row = 0;
sint8 Ball_col = 0;
sint8 Ball_row = 0;

/* when the ball is moving from right to left , the flag is set to 1 (BALL_RTL_FLAG)
 * when the ball is moving from left to right, the flag is set to 0 (BALL_LTR_FLAG) */
uint8 Wall_flag = BALL_LTR_FLAG;

/*******************************************************
 * 				Private Functions 
 *******************************************************/

/**
 * @brief Initializes the custom LCD characters for the game.
 */
static void CustomCharacter_init()
{
	uint8 _7amok4a[8] = {0x0E, 0x0A, 0x0E, 0x05, 0x1F, 0x14, 0x04, 0x0A};

	uint8 _7azal2om[8] = {0x0E, 0x0A, 0x0E, 0x14, 0x1F, 0x05, 0x04, 0x0A};

	uint8 Ball[8] = {0x00, 0x04, 0x0E, 0x1F, 0x1F, 0x0E, 0x04, 0x00};

	uint8 Heart[8] = {0x00, 0x00, 0x1B, 0x1F, 0x1F, 0x0E, 0x04, 0x00};

	LCD_displaySpecialCharacter(_7amok4a, _7amok4a_ADDRESS);
	LCD_displaySpecialCharacter(_7azal2om, _7azal2om_ADDRESS);
	LCD_displaySpecialCharacter(Ball, Ball_ADDRESS);
	LCD_displaySpecialCharacter(Heart, Heart_ADDRESS);
}

/**
 * @brief Updates the position and movement of the ball in the game.
 */
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
		Wall_flag = BALL_RTL_FLAG;
	}
	else if (Ball_col == 0)
	{
		Wall_flag = BALL_LTR_FLAG;
	}

	LCD_Goto_XY(Ball_row, Ball_col);
	LCD_displayCharacter(Ball_ADDRESS);

	_delay_ms(BALL_DELAY_TIME);

	LCD_Goto_XY(Ball_row, Ball_col);
	LCD_displayCharacter(' ');

	if (Wall_flag == BALL_LTR_FLAG)
	{
		Ball_col++;
	}
	else if (Wall_flag == BALL_RTL_FLAG)
	{
		Ball_col--;
	}
}

/**
 * @brief Updates the position of players based on user input.
 *
 * @param key The user input key.
 */
static void PlayersKey_Update(uint8 key)
{
	// when the ball is moving from left to right, player can only move 7azal2om (right player) and the ball
	if (Wall_flag == BALL_LTR_FLAG)
	{
		if (key == _7azal2om_UP_KEY)
		{
			LCD_Goto_XY(_7azal2om_row, _7azal2om_COL);
			LCD_displayCharacter(' ');
			_7azal2om_row--;

			if (_7azal2om_row < 0)
			{
				_7azal2om_row = 0;
			}
		}
		else if (key == _7azal2om_DOWN_KEY)
		{
			LCD_Goto_XY(_7azal2om_row, _7azal2om_COL);
			LCD_displayCharacter(' ');
			_7azal2om_row++;

			if (_7azal2om_row > PLAYERS_POSSIBLE_POSITIONS)
			{
				_7azal2om_row = PLAYERS_POSSIBLE_POSITIONS;
			}
		}
	}
	// when the ball is moving from right to left, player can only move 7amok4a (left player) and the ball
	else if (Wall_flag == BALL_RTL_FLAG)
	{
		if (key == _7amok4a_UP_KEY)
		{
			LCD_Goto_XY(_7amok4a_row, 0);
			LCD_displayCharacter(' ');
			_7amok4a_row--;

			if (_7amok4a_row < 0)
			{
				_7amok4a_row = 0;
			}
		}
		else if (key == _7amok4a_DOWN_KEY)
		{
			LCD_Goto_XY(_7amok4a_row, _7amok4a_COL);
			LCD_displayCharacter(' ');
			_7amok4a_row++;

			if (_7amok4a_row > PLAYERS_POSSIBLE_POSITIONS)
			{
				_7amok4a_row = PLAYERS_POSSIBLE_POSITIONS;
			}
		}
	}
}

/**
 * @brief Updates the graphical user interface for player positions.
 */
static void PlayersGUI_Update()
{
	LCD_Goto_XY(_7amok4a_row, _7amok4a_COL);
	LCD_displayCharacter(_7amok4a_ADDRESS);

	LCD_Goto_XY(_7azal2om_row, _7azal2om_COL);
	LCD_displayCharacter(_7azal2om_ADDRESS);
}

/**
 * @brief Resets the game to its initial state.
 *
 * @param P1_score Pointer to player 1's score.
 * @param P2_score Pointer to player 2's score.
 */
static void ResetGame(uint8* P1_score, uint8* P2_score)
{
	LCD_clearScreen();
	_7amok4a_row = 0;
	_7azal2om_row = 0;
	*P1_score = MAX_SCORE;
	*P2_score = MAX_SCORE;

	Ball_col = 0;
	Ball_row = 0;
	Wall_flag = BALL_LTR_FLAG;
}

/**
 * @brief Updates the position of the ball based on user input.
 *
 * @param key The user input key.
 */
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
	}

	LCD_Goto_XY(Ball_row, Ball_col);
	LCD_displayCharacter(Ball_ADDRESS);
}

/**
 * @brief Calculates and updates the game score.
 *
 * @param P1_score Pointer to player 1's score.
 * @param P2_score Pointer to player 2's score.
 * @return TRUE if someone scores, FALSE if no one scores.
 */
static uint8 ScoreCalculator(uint8* P1_score, uint8* P2_score)
{
	uint8 score_flag = FALSE; // FALSE : no one scores , TRUE : someone scores

	// when _7azal2om scores
	if (Ball_col <= _7amok4a_COL && Ball_row != _7amok4a_row)
	{
		*P1_score = *P1_score - 1; // decrease the player 1 life score
		Buzzer_Alarm();
		score_flag = TRUE;
	}
	// when _7amok4a scores
	else if (Ball_col >= _7azal2om_COL && Ball_row != _7azal2om_row)
	{
		*P2_score = *P2_score - 1; // decrease the player 2 life score
		Buzzer_Alarm();
		score_flag = TRUE;
	}

	return score_flag;
}

/**
 * @brief Updates the graphical user interface for displaying the game score.
 *
 * @param P1_score Pointer to player 1's score.
 * @param P2_score Pointer to player 2's score.
 */
static void ScoreGUI(uint8* P1_score, uint8* P2_score)
{
	// P1 : _7amok4a  , P2 : _7azal2om
	LCD_Goto_XY(LCD_NUM_LINES - 1, 0);
	LCD_displayString("P1:");
	LCD_displayInteger(*P1_score);
	LCD_displayCharacter(Heart_ADDRESS);
	LCD_Goto_XY(LCD_NUM_LINES - 1, LCD_NUM_POSITIONS - 5);
	LCD_displayString("P2:");
	LCD_displayInteger(*P2_score);
	LCD_displayCharacter(Heart_ADDRESS);

	// if one player loses
	if (*P1_score == 0 || *P2_score == 0)
	{
		LCD_clearScreen();
		if (*P1_score == 0)
		{
			LCD_displayStringCenter(1, "7azal2om Wins!");
		}
		else if (*P2_score == 0)
		{
			LCD_displayStringCenter(1, "7amok4a Wins!");
		}
		_delay_ms(DELAY_TIME);
		ResetGame(P1_score, P2_score);
	}
}

/******************************************************
 * 			 Public Functions 
 ******************************************************/
/**
 * @brief Initializes the game playground including the LCD and custom characters.
 */
void Playground_init()
{
	LCD_init();
	Buzzer_init();
	CustomCharacter_init();
}

/**
 * @brief Main loop for the game playground that handles the game logic and user input.
 */
void Playground_MainLoop()
{
	uint8 _7amok4a_lifes = MAX_SCORE;
	uint8 _7azal2om_lifes = MAX_SCORE;

	uint8 key = KEYPAD_NO_PRESSED_KEY;

	while (1)
	{
		Ball_Loop();
		PlayersGUI_Update();

		if (ScoreCalculator(&_7amok4a_lifes, &_7azal2om_lifes))
		{
			// if someone scores , update the score GUI
			ScoreGUI(&_7amok4a_lifes, &_7azal2om_lifes);
		}

		key = KEYPAD_getPressedKey();

		switch (key)
		{
			case KEYPAD_NO_PRESSED_KEY:
				break;

			case Ball_UP_KEY:
			case Ball_DOWN_KEY:
				Ball_Update(key);

				break;
			case _7amok4a_UP_KEY:
			case _7amok4a_DOWN_KEY:
			case _7azal2om_UP_KEY:
			case _7azal2om_DOWN_KEY:
				PlayersKey_Update(key);
				break;
			case RESET_KEY:
				LCD_clearScreen();
				LCD_displayStringCenter(1, "RESET GAME");
				_delay_ms(DELAY_TIME);
				ResetGame(&_7amok4a_lifes, &_7azal2om_lifes);
				break;
			default:
				break;
		}
	}
}