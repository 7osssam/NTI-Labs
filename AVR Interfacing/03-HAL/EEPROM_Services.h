/******************************************************************
 * @Module   	: External EEPROM services 
 * @Title 	 	: External EEPROM services Header file 
 * @Filename 	: EEPROM_Services.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#ifndef __EEPROM_SERVICES_H__
#define __EEPROM_SERVICES_H__

#include "STD_TYPES.h"

/**
 * @brief Writes a specified number of bytes to the EEPROM starting at the specified address.
 * 
 * @param sent_data The data to be written to the EEPROM.
 * @param NofBytes The number of bytes to be written.
 * @param address The starting address of the write operation.
 */
void EEPROM_WriteNofBytes(uint32 sent_data, uint8 NofBytes, uint16 address);

/**
 * @brief Reads a specified number of bytes from the EEPROM starting at the specified address.
 * 
 * @param sent_data A pointer to the location where the read data will be stored.
 * @param NofBytes The number of bytes to be read.
 * @param address The starting address of the read operation.
 */
void EEPROM_ReadNofBytes(uint32* sent_data, uint8 NofBytes, uint16 address);
/**
 * @brief Resets a specified number of bytes in the EEPROM starting at the specified address to 0.
 * 
 * @param NofBytes The number of bytes to be reset.
 * @param address The starting address of the reset operation.
 */
void EEPROM_resetNofBytes(uint8 NofBytes, uint16 address);

#endif /* __EEPROM_SERVICES_H__ */