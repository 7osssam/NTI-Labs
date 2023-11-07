
#include "STD_TYPES.h"
#include "BIT_MACROS.h"

#include "GPIO.h"
#include "GPIO_reg.h"

#define CNF_BITS(x)	 (((4 * (x)) + 2))
#define MODE_BITS(x) (((4 * (x)) + 0))

#define MIN_PIN_LOW	 0
#define MAX_PIN_LOW	 7

#define MIN_PIN_HIGH 8
#define MAX_PIN_HIGH 15

void GPIO_SetPinDirection(GPIO_TypeDef* port, uint8 pinNumber, GPIO_CNF CNF, GPIO_MODE MODE)
{
	// Port configuration register low
	if (pinNumber <= MAX_PIN_LOW && pinNumber >= MIN_PIN_LOW)
	{
		port->CRL = (port->CRL & ~(0xF << CNF_BITS(pinNumber))) | ((CNF << CNF_BITS(pinNumber)));
		port->CRL = (port->CRL & ~(0xF << MODE_BITS(pinNumber))) | ((MODE << MODE_BITS(pinNumber)));
	}
	// Port configuration register high
	else if (pinNumber >= MIN_PIN_HIGH && pinNumber <= MAX_PIN_HIGH)
	{
		port->CRH = (port->CRH & ~(0xF << CNF_BITS(pinNumber - 8))) | ((CNF << CNF_BITS(pinNumber - 8)));
		port->CRH = (port->CRH & ~(0xF << MODE_BITS(pinNumber - 8))) | ((MODE << MODE_BITS(pinNumber - 8)));
	}
}

void GPIO_SetPinValue(GPIO_TypeDef* port, uint8 pinNumber, uint8 value)
{
	if (value == LOGIC_LOW)
	{
		CLEAR_BIT(port->ODR, pinNumber);
	}
	else
	{
		SET_BIT(port->ODR, pinNumber);
	}
}

void GPIO_TogglePinValue(GPIO_TypeDef* port, uint8 pinNumber)
{
	TOGGLE_BIT(port->ODR, pinNumber);
}

uint8 GPIO_GetPinValue(GPIO_TypeDef* port, uint8 pinNumber)
{
	return READ_BIT(port->IDR, pinNumber);
}
