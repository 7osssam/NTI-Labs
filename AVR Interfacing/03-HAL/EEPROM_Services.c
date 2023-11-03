/******************************************************************
 * @Module   	: External EEPROM services 
 * @Title 	 	: External EEPROM services Source File 
 * @Filename 	: EEPROM_Services.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#include "EEPROM_Services.h"

void EEPROM_WriteNofBytes(uint32 sent_data, uint8 NofBytes, uint8 address)
{
	uint8 i;

	for (i = 0; i < NofBytes; i++)
	{
		EEPROM_writeByte(address + i, (uint8)(sent_data >> (i * 8)));
		_delay_ms(EEPROM_DELAY_MS);
	}
}

void EEPROM_ReadNofBytes(uint32* sent_data, uint8 NofBytes, uint8 address)
{
	uint8 i;
	uint8 temp_data;

	for (i = 0; i < NofBytes; i++)
	{
		EEPROM_readByte(address + i, &temp_data);
		_delay_ms(EEPROM_DELAY_MS);
		*sent_data |= ((uint32)(temp_data << (i * 8)));
	}
}

void EEPROM_resetNofBytes(uint8 NofBytes, uint8 address)
{
	uint8 i;

	for (i = 0; i < NofBytes; i++)
	{
		EEPROM_writeByte(address + i, 0);
		_delay_ms(EEPROM_DELAY_MS);
	}
}