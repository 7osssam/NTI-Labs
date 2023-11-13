
#include "Services.h"
#include <stdlib.h> // for rand() function
#include <string.h>
#include <time.h>

uint32 stringToHex(const uint8* str)
{
	uint8* endptr;
	return strtoul(str, &endptr, 16);
}

uint32 generateRandomNumber()
{
	// Seed the random number generator with the current time
	srand((uint32)time(NULL));

	// Generate a random number in the range [1000, 9999]
	return rand() % (9999 - 1000 + 1) + 1000;
}
