

#include "DIO.h"

int main(void)
{
	DIO_init(&DIO_Configuration);

	while (1)
	{
		DIO_SetPinValue(PORTA_ID, PIN0_ID, LOGIC_HIGH);
	}
}