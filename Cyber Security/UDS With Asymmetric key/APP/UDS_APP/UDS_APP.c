
#include "UDS_APP.h"

#include "UART.h"
#include "UART_Services.h"
#include "Buzzer.h"
#include "LCD.h"

#include "STD_TYPES.h"

#include <stdlib.h> // for rand() function
#include <string.h>

#include "SETTINGS.h"
#include <util/delay.h>

#define UDS_ROUTINE_CONTROL		 0x31
#define UDS_SUBROUTINE_CONTROL	 0x01
#define UDS_CHECK_KEY_ID		 0x02
#define UDS_NEGATIVE_RESPONSE_ID 0x7F

#define UDS_NEGATIVE_RESPONSE	 "0x7F3135"
#define UDS_TURN_ON_BUZZER		 0x3101AA00
#define UDS_SECURITY_ACCESS		 0x2701
#define UDS_CHECK_KEY			 0x2702

#define UDS_POSITIVE_RESPONSE	 0x71
#define UDS_REQUEST_UPLOAD		 0x35
#define UDS_SECURITY_ACCESS_ID	 0x27
#define UDS_ENTER_SECURITY_KEY	 "0x6701"
#define UDS_TURN_ON_BUZZER_ID	 0xAA00 // this routine need a security access to be executed
#define UDS_MESSAGE_SIZE		 8
#define ALPHABET_SIZE			 26

uint32 encrypted_key;
uint8  AccessKey_flag = FALSE;

void LCD_displayHex_u32(uint32 num)
{
	const char hexLookup[] = "0123456789ABCDEF";
	for (int shift = sizeof(uint32) * 8 - 4; shift >= 0; shift -= 4)
	{
		uint8 hex = (num >> shift) & 0x0F;
		LCD_displayCharacter(hexLookup[hex]);
	}
}

static void UDS_init()
{
	UART_ConfigType UART_Config = {.baud_rate = BAUD_9600,
								   .bit_data = UART_8_BIT_DATA,
								   .parity = UART_NO_PARITY,
								   .stop_bit = UART_1_STOP_BIT};

	UART_init(&UART_Config);
	LCD_init();

	Buzzer_init(); // TODO: Buzzer init
}

//3101AA00
uint32 stringToHex(const uint8* str)
{
	uint8* endptr;
	return strtoul(str, &endptr, 16);
}

uint32 stringtoInt(uint8* str)
{
	uint8* endptr;
	return strtoul(str, &endptr, 10);
}

void intToString(uint8 num, uint8* str)
{
	uint8 i = 0;
	uint8 temp;
	do
	{
		temp = num % 10;
		str[i] = temp + '0';
		num /= 10;
		i++;
	} while (num != 0);
	str[i] = '\0';
}

void UART_ReceiveMessage(uint8* Str, uint8 len)
{
	uint8 i = 0;
	uint8 temp;
	do
	{
		temp = UART_ReceiveByte();
		// if temp is not a valid hex character
		if (!((temp >= '0' && temp <= '9') || (temp >= 'A' && temp <= 'F')))
		{
			// ignore it
			continue;
		}

		Str[i] = temp;
		LCD_displayCharacter(Str[i]);
		i++;
	} while (i < len);
	Str[i] = '\0';
}

void UART_SendMessage(uint8* Str)
{
	uint8 i = 0;
	while (Str[i] != '\0')
	{
		UART_SendByte(Str[i]);
		i++;
	}
}

uint8 encryptMessage(uint8 message) // use any alogrithm
{
	message = message ^ 0xFF;

	return message;
}

void GetAccessKey()
{
	uint32 random_key = rand() % 10000;
	uint8  rand_str[4];
	uint8  security_access_key[4];
	uint8  security_access_flag = FALSE;

	while (security_access_flag != TRUE)
	{
		LCD_clearScreen();
		LCD_Goto_XY(0, 0);
		LCD_displayString("Get Key: ");
		UART_ReceiveMessage(security_access_key, 4);

		if (stringToHex(security_access_key) == UDS_SECURITY_ACCESS)
		{
			UART_SendMessage(UDS_ENTER_SECURITY_KEY);
			intToString(random_key, rand_str);
			UART_SendString(rand_str);

			encrypted_key = encryptMessage(random_key);
			security_access_flag = TRUE;

			LCD_clearScreen();
			LCD_Goto_XY(3, 0);
			LCD_displayString(UDS_ENTER_SECURITY_KEY);
			LCD_displayString(" Rand:");
			LCD_displayInteger(random_key);
		}
		else
		{
			/* Do nothing */
		}
	}
}

void CheckencryptMessage(void)
{
	uint32 received_Key;
	uint8  received_data[4];
	uint8  received_data_flag = FALSE;

	uint8* encrypted_key_str[4];

	while (received_data_flag != TRUE)
	{
		LCD_Goto_XY(0, 0);
		LCD_displayString("Enter MSG: ");
		UART_ReceiveMessage(received_data, 4);

		if (stringToHex(received_data) == UDS_CHECK_KEY)
		{
			LCD_Goto_XY(1, 0);
			LCD_displayString("Encrypted KEY:");
			LCD_Goto_XY(2, 0);
			UART_ReceiveMessage(received_data, 4);

			received_Key = stringtoInt(received_data);

			if (received_Key == encrypted_key)
			{
				AccessKey_flag == TRUE;
			}
			else
			{
				LCD_clearScreen();
				LCD_displayStringCenter(0, "Wrong Key");
			}
		}
		else
		{
			/* Do nothing */
		}
		LCD_clearScreen();
	}
}

void UDS_main()
{
	uint8 UDS_RoutineControl_str[8];

	UDS_init();

	while (AccessKey_flag != TRUE)
	{
		LCD_Goto_XY(0, 0);
		LCD_displayString("ENTER MASSAGE");

		LCD_Goto_XY(1, 0);
		UART_ReceiveMessage(UDS_RoutineControl_str, 8);

		if (stringToHex(UDS_RoutineControl_str) == UDS_TURN_ON_BUZZER)
		{
			if (AccessKey_flag == FALSE)
			{
				LCD_clearScreen();
				LCD_displayStringCenter(0, "ACCESS DENIED");

				UART_SendString(UDS_NEGATIVE_RESPONSE); // 0x3135
				_delay_ms(500);

				GetAccessKey();

				CheckencryptMessage();
			}
			else
			{
				Buzzer_Alarm();
				LCD_clearScreen();
				LCD_displayStringCenter(0, "ACCESS GRANTED");
				LCD_displayStringCenter(1, "BUZZER ON");
				UART_SendByte(UDS_POSITIVE_RESPONSE);	   // 0x71
				UART_SendByte(UDS_SUBROUTINE_CONTROL);	   // 0x01
				UART_SendByte(UDS_TURN_ON_BUZZER_ID >> 8); // 0xAA
				UART_SendByte(UDS_TURN_ON_BUZZER_ID);	   // 0x00
			}
		}
	}
}
