
#include "UDS_APP.h"

#include "UART.h"
#include "UART_Services.h"
#include "Buzzer.h"
#include "LCD.h"

#include "SETTINGS.h"
#include <util/delay.h>

#include "STD_TYPES.h"

#include "Services.h"

#define UDS_NEGATIVE_RESPONSE		 0x7F3135
#define UDS_TURN_ON_BUZZER			 0x3101AA00
#define UDS_POSITIVE_RESPONSE_BUZZER 0x7101AA00
#define UDS_SECURITY_ACCESS			 0x2701
#define UDS_CHECK_KEY				 0x2702
#define UDS_ENTER_SECURITY_KEY		 0x6701

#define UDS_MAX_MESSAGE_SIZE		 8

#define UDS_LARGE_MESSAGE			 8
#define UDS_SMALL_MESSAGE			 4

uint16 encrypted_key;
uint8  AccessKey_flag = FALSE;

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

uint32 UART_UDSReceive(uint8 len)
{
	uint8  Str[UDS_MAX_MESSAGE_SIZE];
	uint8  i = 0;
	uint8  temp;
	uint32 Hex_num;
	do
	{
		temp = UART_ReceiveByte();
		// if temp is not a valid hex character
		if (!((temp >= '0' && temp <= '9') || (temp >= 'A' && temp <= 'F') || (temp >= 'a' && temp <= 'f')))
		{
			// ignore it
			continue;
		}

		Str[i] = temp;
		LCD_displayCharacter(Str[i]);
		i++;
	} while (i < len);
	Str[i] = '\0';

	Hex_num = stringToHex(Str);

	return Hex_num;
}

void UART_UDSSend(uint32 Sent_Hex, uint8 len)
{
	uint8 hexLookup[] = "0123456789ABCDEF";
	uint8 size = 0;

	for (uint8 shift = 28; shift >= 0; shift -= 4)
	{
		size++;

		uint8 hex = (Sent_Hex >> shift) & 0x0F;
		UART_SendByte(hexLookup[hex]);

		if (size == len)
		{
			break;
		}
	}
}

uint16 encryptMessage(uint16 message)
{
	return message ^ (message % 100);
}

void GetAccessKey()
{
	uint32 random_key = generateRandomNumber();
	uint8  rand_str[5];
	uint16 security_access_key;

	uint8 security_access_flag = FALSE;

	while (security_access_flag != TRUE)
	{
		LCD_clearScreen();
		LCD_Goto_XY(0, 0);
		LCD_displayString("Get Key: ");
		security_access_key = UART_UDSReceive(UDS_SMALL_MESSAGE);

		if (security_access_key == UDS_SECURITY_ACCESS)
		{
			// Send the security access key through UART
			UART_UDSSend(UDS_ENTER_SECURITY_KEY, UDS_LARGE_MESSAGE);

			UART_SendFourBytes(random_key);

			// Encrypt the random key
			encrypted_key = encryptMessage((random_key << 16));
			security_access_flag = TRUE;

			LCD_clearScreen();
			LCD_Goto_XY(2, 0);
			LCD_displayString(UDS_ENTER_SECURITY_KEY);
			LCD_Goto_XY(3, 0);
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
	uint32 received_data;
	uint8  received_data_flag = FALSE;

	while (received_data_flag != TRUE)
	{
		LCD_Goto_XY(0, 0);
		LCD_displayString("Enter MSG: ");
		//LCD_displayInteger(encrypted_key); // FOR TESTING
		received_data = UART_UDSReceive(UDSSMALL_MESSAGE);

		if (received_data == UDS_CHECK_KEY)
		{
			LCD_Goto_XY(1, 0);
			LCD_displayString("Encrypted KEY:");
			LCD_Goto_XY(2, 0);
			received_Key = UART_UDSReceive(UDS_LARGE_MESSAGE);

			if (received_Key == encrypted_key)
			{
				AccessKey_flag = TRUE;
				received_data_flag = TRUE;
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
	UDS_init();
	while (1)
	{
		uint32 UDS_RoutineControl;

		LCD_Goto_XY(0, 0);
		LCD_displayString("ENTER MASSAGE");

		LCD_Goto_XY(1, 0);
		UDS_RoutineControl = UART_UDSReceive(UDS_LARGE_MESSAGE);
		if (UDS_RoutineControl == UDS_TURN_ON_BUZZER)
		{
			if (AccessKey_flag == FALSE)
			{
				LCD_clearScreen();
				LCD_displayStringCenter(0, "ACCESS DENIED");
				_delay_ms(500);

				UART_UDSSend(UDS_NEGATIVE_RESPONSE, UDS_LARGE_MESSAGE);

				GetAccessKey();

				CheckencryptMessage();
			}
			else
			{
				Buzzer_Alarm();
				LCD_clearScreen();
				LCD_displayStringCenter(0, "ACCESS GRANTED");
				LCD_displayStringCenter(1, "BUZZER ON");

				UART_UDSSend(UDS_POSITIVE_RESPONSE_BUZZER, UDS_LARGE_MESSAGE);

				AccessKey_flag = FALSE; // Reset the flag
			}
		}
		else
		{
			LCD_clearScreen();
		}
	}
}
