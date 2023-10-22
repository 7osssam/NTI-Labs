/******************************************************************
 * @Module   	: DIO
 * @Title 	 	: Source file for the AVR DIO driver
 * @Filename 	: DIO.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#include "BIT_MACROS.h"

#include "DIO.h"	 /* To include the DIO header file */
#include "DIO_map.h" /* To use the DIO Registers Addresses */

void DIO_init(const DIO_ConfigType* ConfigPtr)
{
	/* Pointer to the required PORT register */
	volatile uint8* PORT_ptr = NULL_PTR;

	/* Pointer to the required DDR register */
	volatile uint8* DDR_ptr = NULL_PTR;

	for (int ID = 0; ID < NUM_OF_PINS; ID++)
	{
		/* Get the required PORT register address */
		PORT_ptr = PORT[ConfigPtr->DIO_pins[ID].port_num];

		/* Get the required DDR register address */
		DDR_ptr = DDR[ConfigPtr->DIO_pins[ID].port_num];

		/* Setup the pin direction as required */
		if (ConfigPtr->DIO_pins[ID].direction == PIN_OUTPUT)
		{
			SET_BIT(*DDR_ptr, ConfigPtr->DIO_pins[ID].pin_num);
		}
		else
		{
			CLEAR_BIT(*DDR_ptr, ConfigPtr->DIO_pins[ID].pin_num);
		}

		/* Write the pin value as required */
		WRITE_BIT(*PORT_ptr, ConfigPtr->DIO_pins[ID].pin_num, ConfigPtr->DIO_pins[ID].initial_value);
	}
}

void DIO_SetPinDirection(DIO_PortType port_num, DIO_PinType pin_num, DIO_PinDirectionType direction)
{
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Pointer to the required DDR register */
		volatile uint8* DDR_ptr = NULL_PTR;

		/* Get the required DDR register address */
		DDR_ptr = DDR[port_num];

		/* Setup the pin direction as required */
		if (direction == PIN_OUTPUT)
		{
			SET_BIT(*DDR_ptr, pin_num);
		}
		else
		{
			CLEAR_BIT(*DDR_ptr, pin_num);
		}
	}
}

uint8 DIO_ReadPin(DIO_PortType port_num, DIO_PinType pin_num)
{
	uint8 pin_value = LOGIC_LOW;

	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		volatile uint8* PIN_ptr = NULL_PTR;

		/* Get the required PIN register address */
		PIN_ptr = PIN[port_num];

		/* Read the pin value as required */
		if (IS_BIT_SET(*PIN_ptr, pin_num))
		{
			pin_value = LOGIC_HIGH;
		}
		else
		{
			pin_value = LOGIC_LOW;
		}
	}

	return pin_value;
}

void DIO_SetPinValue(DIO_PortType port_num, DIO_PinType pin_num, uint8 value)
{
	/* Pointer to the required PORT register */

	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		volatile uint8* PORT_ptr = NULL_PTR;
		/* Get the required PORT register address */
		PORT_ptr = PORT[port_num];

		/* Write the pin value as required */
		WRITE_BIT(*PORT_ptr, pin_num, value);
	}
}

void DIO_SetPortDirection(DIO_PortType port_num, DIO_PortDirectionType direction)
{
	if (port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Pointer to the required DDR register */
		volatile uint8* DDR_ptr = NULL_PTR;
		/* Get the required DDR register address */
		DDR_ptr = DDR[port_num];

		/* Setup the port direction as required */
		*DDR_ptr = direction;
	}
}

uint8 DIO_ReadPort(DIO_PortType port_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Pointer to the required PIN register */
		volatile uint8* PIN_ptr = NULL_PTR;
		/* Get the required PIN register address */
		PIN_ptr = PIN[port_num];

		/* Read the port value as required */
		value = *PIN_ptr;
	}

	return value;
}

void DIO_SetPortValue(DIO_PortType port_num, uint8 value)
{
	if (port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Pointer to the required PORT register */
		volatile uint8* PORT_ptr = NULL_PTR;
		/* Get the required PORT register address */
		PORT_ptr = PORT[port_num];

		/* Write the port value as required */
		*PORT_ptr = value;
	}
}

void DIO_SetPortDirectionGroup(DIO_PortType port_num, uint8 mask, DIO_PortDirectionType direction)
{
	volatile uint8* DDR_ptr = NULL_PTR;

	if (port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Get the required DDR register address */
		DDR_ptr = DDR[port_num];

		/* Setup the port direction as required */
		*DDR_ptr = (*DDR_ptr & mask) | (direction & ~mask);
	}
}

void DIO_SetPortValueGroup(DIO_PortType port_num, uint8 mask, uint8 value)
{
	volatile uint8* PORT_ptr = NULL_PTR;

	if (port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Get the required PORT register address */
		PORT_ptr = PORT[port_num];

		/* Write the port value as required */
		*PORT_ptr = (*PORT_ptr & mask) | (value & ~mask);
	}
}
