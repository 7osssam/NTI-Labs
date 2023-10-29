#include "Little_Story.h"

#include "BIT_MACROS.h"
#include "STD_TYPES.h"

#include "LCD.h"
#include "KEYPAD.h"
#include "ProgressBar.h"

#include "SETTINGS.h"
#include <util/delay.h>

#define _7amok4a_1_ADDRESS	5
#define _7amok4a_2_ADDRESS	6
#define HeartFulled_ADDRESS 7
#define HeartEmpty_ADDRESS	3

#define RUNNING_DELAY		75
#define JUMPING_DELAY		50
#define HEART_BEAT_DELAY	100

void CustomCharacter_init()
{
	uint8 _7amok4a_1[8] = {0x0E, 0x0A, 0x0E, 0x05, 0x1F, 0x14, 0x04, 0x0A};
	uint8 _7amok4a_2[8] = {0x0E, 0x0A, 0x0E, 0x14, 0x1F, 0x05, 0x04, 0x0A};

	uint8 HeartFulled[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
	uint8 HeartEmpty[8] = {0x0, 0xa, 0x15, 0x11, 0xa, 0x4, 0x0};

	LCD_displaySpecialCharacter(_7amok4a_1, _7amok4a_1_ADDRESS);
	LCD_displaySpecialCharacter(_7amok4a_2, _7amok4a_2_ADDRESS);

	LCD_displaySpecialCharacter(HeartFulled, HeartFulled_ADDRESS);
	LCD_displaySpecialCharacter(HeartEmpty, HeartEmpty_ADDRESS);
}

void _7amok4a_running(uint8 x, uint8 y)
{
	while (1)
	{
		static uint8 i = 0;
		ProgressBar(15, i, 3);

		LCD_Goto_XY(x, i);
		LCD_displayCharacter(_7amok4a_1_ADDRESS);
		_delay_ms(RUNNING_DELAY);
		LCD_Goto_XY(x, i);
		LCD_displayCharacter(_7amok4a_2_ADDRESS);

		LCD_Goto_XY(x, i + 1);
		LCD_displayCharacter(' ');
		_delay_ms(RUNNING_DELAY);
		LCD_Goto_XY(x, i);
		LCD_displayCharacter(' ');

		LCD_Goto_XY(x, i + 1);
		LCD_displayCharacter(_7amok4a_1_ADDRESS);
		_delay_ms(RUNNING_DELAY);
		LCD_Goto_XY(x, i + 1);
		LCD_displayCharacter(_7amok4a_2_ADDRESS);

		i++;

		if (i == y)
		{
			break;
		}
	}
}

void _7amok4a_jumping(uint8 x, uint8 y)
{
	uint8 key = KEYPAD_NO_PRESSED_KEY;

	while (key != 0)
	{
		LCD_Goto_XY(x, y);
		LCD_displayCharacter(_7amok4a_1_ADDRESS);
		do
		{
			key = KEYPAD_getPressedKey();
		} while (key == KEYPAD_NO_PRESSED_KEY);

		_delay_ms(JUMPING_DELAY);
		LCD_Goto_XY(x, y);
		LCD_displayCharacter(_7amok4a_2_ADDRESS);

		LCD_Goto_XY(x - 1, y);
		LCD_displayCharacter(' ');
		_delay_ms(JUMPING_DELAY);
		LCD_Goto_XY(x, y);
		LCD_displayCharacter(' ');

		LCD_Goto_XY(x - 1, y);
		LCD_displayCharacter(_7amok4a_1_ADDRESS);
		_delay_ms(JUMPING_DELAY);
		LCD_Goto_XY(x - 1, y);
		LCD_displayCharacter(_7amok4a_2_ADDRESS);
		_delay_ms(JUMPING_DELAY);
		LCD_Goto_XY(x - 1, y);
		LCD_displayCharacter(' ');

		LCD_displayStringCenter(3, "Press 0 to exit");
	}
}

void HeartBeat(uint8 x, uint8 y, uint8 count)
{
	for (uint8 i = 0; i < count; i++)
	{
		LCD_Goto_XY(x, y);
		LCD_displayCharacter(HeartFulled_ADDRESS);
		_delay_ms(HEART_BEAT_DELAY);
		LCD_Goto_XY(x, y);
		LCD_displayCharacter(HeartEmpty_ADDRESS);
		_delay_ms(HEART_BEAT_DELAY);
	}
}

void Directed(void)
{
	LCD_Goto_XY(2, 0);
	LCD_displayCharacter('D');
	LCD_Goto_XY(2, 1);
	LCD_displayCharacter('i');
	LCD_Goto_XY(2, 2);
	LCD_displayCharacter('r');
	LCD_Goto_XY(2, 3);
	LCD_displayCharacter('e');
	LCD_Goto_XY(2, 4);
	LCD_displayCharacter('c');
	LCD_Goto_XY(2, 5);
	LCD_displayCharacter('t');
	LCD_Goto_XY(2, 6);
	LCD_displayCharacter('e');
	LCD_Goto_XY(2, 7);
	LCD_displayCharacter('d');
	LCD_Goto_XY(2, 8);
	LCD_displayCharacter(' ');
	LCD_Goto_XY(2, 9);
	LCD_displayCharacter('b');
	LCD_Goto_XY(2, 10);
	LCD_displayCharacter('y');
	LCD_Goto_XY(2, 11);
	LCD_displayCharacter(':');
	LCD_Goto_XY(3, 0);
	LCD_displayCharacter('H');
	LCD_Goto_XY(3, 1);
	LCD_displayCharacter('O');
	LCD_Goto_XY(3, 2);
	LCD_displayCharacter('S');
	LCD_Goto_XY(3, 3);
	LCD_displayCharacter('S');
	LCD_Goto_XY(3, 4);
	LCD_displayCharacter('A');
	LCD_Goto_XY(3, 5);
	LCD_displayCharacter('M');
	LCD_Goto_XY(3, 6);
	LCD_displayCharacter(' ');
	LCD_Goto_XY(3, 7);
	LCD_displayCharacter('M');
	LCD_Goto_XY(3, 8);
	LCD_displayCharacter('O');
	LCD_Goto_XY(3, 9);
	LCD_displayCharacter('H');
	LCD_Goto_XY(3, 10);
	LCD_displayCharacter('A');
	LCD_Goto_XY(3, 11);
	LCD_displayCharacter('M');
	LCD_Goto_XY(3, 12);
	LCD_displayCharacter('E');
	LCD_Goto_XY(3, 13);
	LCD_displayCharacter('D');
	LCD_sendCommand(0x1C);
	//_delay_ms(100);
}

void Little_Story_App()
{
	LCD_init();

	ProgressBar_init();
	CustomCharacter_init();

	LCD_displayStringCenter(0, "Little Story");
	_delay_ms(1000);
	LCD_clearScreen();

	LCD_displayStringCenter(1, "Hello, I'm 7amok4a");
	LCD_displayCharacter(_7amok4a_1_ADDRESS);
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayStringCenter(0, "I can run");
	_7amok4a_running(2, 19);

	LCD_clearScreen();

	LCD_displayStringCenter(0, "I can jump");
	LCD_Goto_XY(2, 0);
	LCD_displayCharacter(_7amok4a_1_ADDRESS);
	LCD_displayStringCenter(1, "Press any key");
	_7amok4a_jumping(2, 0);

	LCD_clearScreen();

	LCD_displayStringCenter(0, "AND I SUPPORT");
	LCD_displayStringCenter(1, "PALESTINE");
	_delay_ms(1000);

	LCD_clearScreen();
	LCD_displayStringCenter(1, "FREE PALESTINE");
	HeartBeat(1, 17, 20);

	LCD_clearScreen();
	while (1)
	{
		Directed();
	}
}