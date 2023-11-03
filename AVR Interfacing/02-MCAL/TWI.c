/******************************************************************
 * @Module   	: Two Wire Interface (TWI) (I2C)
 * @Title 	 	: Two Wire Interface implementation Source file
 * @Filename 	: TWI.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#include "TWI.h"

#include "BIT_MACROS.h"
#include "SETTINGS.h" /* For F_CPU */
#include "DIO_map.h"

// Calculate the TWBR value for a given SCL frequency and prescaler value
#define TWBR_VALUE(SCL_freq, TWPS_value) ((F_CPU / SCL_freq) - 16u) / (2u * (1 << TWPS_value))

#define STATUS_MASK						 0xF8
#define GENERAL_CALL_MASK				 0x01

void TWI_init(const TWI_configType* Config_Ptr)
{
	//**************** Configure Slave Address and General Call Recognition Mode ***************
	TWAR = ((Config_Ptr->TWI_slaveAddress) << 1);

	//***************************** Prescaler *************************
	TWSR = Config_Ptr->prescaler;

	//***************************** Bit Rate *************************
	TWBR = TWBR_VALUE(Config_Ptr->SCL_Frq, Config_Ptr->prescaler);

	//***************************** General Call Recognition Mode *************************
	TWAR = (TWAR & ~GENERAL_CALL_MASK) |
		   ((Config_Ptr->generalCallRecognitionMode & GENERAL_CALL_MASK) << (TWGCE));

	//***************************** Enable TWI *************************
	SET_BIT(TWCR, TWEN);

	/* Enable pull up resistors at SCL and SDA Pins */
	//SET_BIT(PORTC, 4);
	//SET_BIT(PORTC, 5);
}

void TWI_start(void)
{
	/*
	 * - Enable the start bit (TWSTA)
	 * - clear the interrupt flag by setting (TWINT)
	 * - Enable TWI Module (TWEN)
	 */
	TWCR = BIT(TWINT) | BIT(TWEN) | BIT(TWSTA);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (IS_BIT_CLEAR(TWCR, TWINT))
		;
}

void TWI_stop(void)
{
	/*
	 * - Enable the stop bit (TWSTO)
	 * - clear the interrupt flag by setting (TWINT)
	 * - Enable TWI Module (TWEN)
	 */
	TWCR = BIT(TWINT) | BIT(TWEN) | BIT(TWSTO);
}

void TWI_writeByte(uint8 data)
{
	///* Put data On TWI data Register */
	TWDR = data;

	/*
	 * - clear the interrupt flag by setting (TWINT)
	 * - Enable TWI Module (TWEN)
	 */
	TWCR = BIT(TWINT) | BIT(TWEN);

	/* Wait for data is send successfully */
	while (IS_BIT_CLEAR(TWCR, TWINT))
		;
}

uint8 TWI_readByteWithACK(void)
{
	/*
	 * - clear the interrupt flag by setting (TWINT)
	 * - Enable sending ACK after reading or receiving data TWEA=1
	 * - Enable TWI Module TWEN=1
	 */
	TWCR = BIT(TWINT) | BIT(TWEN) | BIT(TWEA);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (IS_BIT_CLEAR(TWCR, TWINT))
		;

	/* Read Data */
	return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * - clear the interrupt flag by setting (TWINT)
	 * - Enable TWI Module TWEN=1
	 */
	TWCR = BIT(TWINT) | BIT(TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (IS_BIT_CLEAR(TWCR, TWINT))
		;

	/* Read Data */
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & STATUS_MASK;
	return status;
}
