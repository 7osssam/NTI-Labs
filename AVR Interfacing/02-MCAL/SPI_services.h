/******************************************************************
 * @Module   	: Serial Peripheral Interface(SPI)
 * @Title 	 	: SPI services header file
 * @Filename 	: SPI_services.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#ifndef SPI_SERVICES_H_
#define SPI_SERVICES_H_

#include "SPI.h"
#include "STD_TYPES.h"

#define SPI_DEFAULT_DATA_VALUE 0xFF

/*******************************************************************************
 *                    Functions Prototypes                                     *
 *******************************************************************************/
void SPI_sendString(const uint8* str);
void SPI_receiveString(uint8* str);

#endif /* SPI_SERVICES_H_ */