/******************************************************************
 * @Module   	: Universal Asynchronous Receiver Transmitter(UART)
 * @Title 	 	: ATmega32 UART static configuration file
 * @Filename 	: UART_config.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#ifndef UART_config_H_
#define UART_config_H_
#include "SETTINGS.h" // for F_CPU

/******************* UART configuration *********************************/
#define SPEED_MODE	   DOUBLE_SPEED
#define SYNCH_MODE	   ASYNCH
#define UART_MODE	   POLLING
#define ERROR_CHECKING FALSE

/******************* Mode of operation *******************************/
#define POLLING		   0
#define INTERRUPT	   1

/******************** speed mode *************************/
#define NORMAL_SPEED   0
#define DOUBLE_SPEED   1

/*************** Communication mode********************/
#define SYNCH		   1
#define ASYNCH		   0

#endif /* UART_config_H_ */