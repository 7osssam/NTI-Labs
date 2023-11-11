
#include "Services.h"
#include "LCD.h"
#include <stdlib.h> // for rand() function
#include <string.h>
void LCD_displayHex_u32(uint32 num)
{
	const char hexLookup[] = "0123456789ABCDEF";
	for (int shift = sizeof(uint32) * 8 - 4; shift >= 0; shift -= 4)
	{
		uint8 hex = (num >> shift) & 0x0F;
		LCD_displayCharacter(hexLookup[hex]);
	}
}

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

void intToString(uint32 num, uint8* str)
{
	uint8 i = 0;
	do
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	} while (num != 0);

	// Add a null terminator at the end of the string
	str[i] = '\0';

	// Reverse the string to get the correct order
	reverseString(str);
}

void reverseString(uint8* str)
{
	int length = strlen(str);
	int start = 0;
	int end = length - 1;
	while (start < end)
	{
		// Swap characters at start and end
		uint8 temp = str[start];
		str[start] = str[end];
		str[end] = temp;

		// Move the pointers toward each other
		start++;
		end--;
	}
}

uint32 generateRandomNumber()
{
	// Seed the random number generator with the current time
	srand((uint32)time(NULL));

	// Generate a random number in the range [1000, 9999]
	return rand() % (9999 - 1000 + 1) + 1000;
}
