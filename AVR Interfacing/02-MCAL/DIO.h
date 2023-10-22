/******************************************************************
 * @Module   	: DIO
 * @Title 	 	: Header file for the AVR DIO driver
 * @Filename 	: DIO.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc
 * @Notes    	:
 ********************************************************************/

#ifndef DIO_H_
#define DIO_H_

#include "STD_TYPES.h"

#include "DIO_config.h"
#include "DIO_map.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PORTA_ID = 0,
	PORTB_ID,
	PORTC_ID,
	PORTD_ID
} DIO_PortType;

typedef enum
{
	PIN0_ID = 0,
	PIN1_ID,
	PIN2_ID,
	PIN3_ID,
	PIN4_ID,
	PIN5_ID,
	PIN6_ID,
	PIN7_ID
} DIO_PinType;

typedef enum
{
	PIN_INPUT,
	PIN_OUTPUT
} DIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,
	PORT_OUTPUT = 0xFF
} DIO_PortDirectionType;

typedef struct
{
	DIO_PortType		 port_num;
	DIO_PinType			 pin_num;
	DIO_PinDirectionType direction;
	uint8				 initial_value;
} DIO_type;

typedef struct
{
	DIO_type DIO_pins[NUM_OF_PINS];
} DIO_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**
 * The function DIO_init initializes the direction and initial value of DIO pins based on the provided
 * configuration.
 * 
 * @param ConfigPtr A pointer to a structure of type DIO_ConfigType. This structure contains
 * information about the DIO pins to be initialized.
 */
void DIO_init(const DIO_ConfigType* ConfigPtr);

/**
 * The function DIO_SetPinDirection sets the direction of a specific pin on a specific port to either
 * input or output.
 * 
 * @param port_num The port number is used to specify which DIO port to configure. It is of type
 * DIO_PortType.
 * @param pin_num The pin number of the DIO pin that you want to set the direction for.
 * @param direction The "direction" parameter is of type DIO_PinDirectionType, which is an enumeration
 * that specifies whether the pin should be set as an output or an input. The possible values for this
 * parameter are PIN_OUTPUT and PIN_INPUT.
 */
void DIO_SetPinDirection(DIO_PortType port_num, DIO_PinType pin_num, DIO_PinDirectionType direction);

/**
 * The function DIO_ReadPin reads the value of a specific pin on a specific port and returns the value
 * as either LOGIC_HIGH or LOGIC_LOW.
 * 
 * @param port_num The port number is the identifier for the DIO port that the pin belongs to. It is
 * of type DIO_PortType, which is likely an enumeration or typedef representing the different DIO
 * ports available on the microcontroller.
 * @param pin_num The pin number of the DIO pin that you want to read.
 * 
 * @return the value of the pin, which can be either LOGIC_HIGH or LOGIC_LOW.
 */
uint8 DIO_ReadPin(DIO_PortType port_num, DIO_PinType pin_num);

/**
 * The function DIO_SetPinValue sets the value of a specific pin in a specific port.
 * 
 * @param port_num The port number is used to specify which DIO port to access. It is of type
 * DIO_PortType, which is an enumeration that defines the available DIO ports.
 * @param pin_num The pin number of the DIO pin that you want to set the value for.
 * @param value The value parameter is the value to be set for the specified pin. It can be either 0 or
 * 1, representing low or high logic level respectively.
 */
void DIO_SetPinValue(DIO_PortType port_num, DIO_PinType pin_num, uint8 value);

/**
 * The function sets the direction of a specific port on a microcontroller.
 * 
 * @param port_num The port number is an enumeration type (DIO_PortType) that represents the specific
 * port on the microcontroller. It is used to select the appropriate DDR (Data Direction Register) for
 * that port.
 * @param direction The direction parameter is of type DIO_PortDirectionType, which is an enumeration
 * that specifies the direction of the port. It can have two possible values: DIO_PORT_INPUT or
 * DIO_PORT_OUTPUT.
 */
void DIO_SetPortDirection(DIO_PortType port_num, DIO_PortDirectionType direction);

/**
 * The function DIO_ReadPort reads the value of a specified DIO port and returns it.
 * 
 * @param port_num The parameter `port_num` is of type `DIO_PortType`, which is an enumeration
 * representing the port number. It is used to specify the port from which to read the value.
 * 
 * @return a uint8 value, which is the value read from the specified DIO port.
 */
uint8 DIO_ReadPort(DIO_PortType port_num);

/**
 * The function DIO_SetPortValue sets the value of a specified DIO port.
 * 
 * @param port_num The port number is an enumeration type (DIO_PortType) that represents the specific
 * port to set the value for. It could be one of the available ports on the microcontroller, such as
 * DIO_PORTA, DIO_PORTB, DIO_PORTC, etc.
 * @param value The value to be written to the port. It should be an 8-bit unsigned integer.
 */
void DIO_SetPortValue(DIO_PortType port_num, uint8 value);

/**
 * The function DIO_SetPortDirectionGroup sets the direction of a group of pins in a specific port.
 * 
 * @param port_num The port number is an enumeration type (DIO_PortType) that represents the specific
 * port on the microcontroller. It could be PORT_A, PORT_B, PORT_C, etc.
 * @param mask The mask parameter is used to specify which bits of the port's direction register should
 * be modified. It is a bitmask where each bit represents a pin on the port. If a bit in the mask is
 * set to 1, the corresponding pin's direction will be modified. If a bit is set to
 * @param direction The "direction" parameter is of type DIO_PortDirectionType, which is an enumeration
 * that represents the direction of the port. It can have two possible values: DIO_PORT_INPUT or
 * DIO_PORT_OUTPUT. This parameter is used to set the direction of the port pins specified by the "mask
 */
void DIO_SetPortDirectionGroup(DIO_PortType port_num, uint8 mask, DIO_PortDirectionType direction);

/**
 * The function DIO_SetPortValueGroup sets the value of a specific port by masking the current value
 * and then applying the desired value.
 * 
 * @param port_num The port number is an enumeration type (DIO_PortType) that represents the specific
 * port to be accessed. It could be PORTA, PORTB, PORTC, etc.
 * @param mask The mask parameter is used to specify which bits in the port should be modified. It is a
 * bitmask where each bit represents a specific pin in the port. If a bit in the mask is set to 1, the
 * corresponding pin in the port will be modified. If a bit in the mask is
 * @param value The value parameter is the value that you want to set for the specified port.
 */
void DIO_SetPortValueGroup(DIO_PortType port_num, uint8 mask, uint8 value);

extern const DIO_ConfigType DIO_Configuration;

#endif /* DIO_H_ */
