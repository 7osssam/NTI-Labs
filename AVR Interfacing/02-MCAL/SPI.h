/******************************************************************
 * @Module   	: Serial Peripheral Interface(SPI)
 * @Title 	 	: SPI Module interface file
 * @Filename 	: SPI.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "STD_TYPES.h"

/*******************************************************************************
 *                    Module Data Types                                        *
 *******************************************************************************/

typedef enum
{
	SPI_Master,
	SPI_Slave
} SPI_Master_Slave_Select_t;

typedef enum
{
	SPI_FOSC_4,
	SPI_FOSC_16,
	SPI_FOSC_64,
	SPI_FOSC_128,
} SPI_Clock_Rate_t;

/*******************************************************************************
 *                    Functions Prototypes                                     *
 *******************************************************************************/

/**
 * The SPI_init function initializes the SPI module based on the specified master/slave select, clock
 * rate, data order, operation level, sampling edge, clock polarity, and SPI enable/disable settings.
 * 
 * @param Master_Slave_Select This parameter is used to select whether the SPI module will operate as a
 * master or a slave. It can take two values: SPI_Master or SPI_Slave.
 * @param Clock_Rate The Clock_Rate parameter is used to set the clock rate for the SPI communication.
 * It is of type SPI_Clock_Rate_t, which is an enumeration type that defines different clock rate options.
 * The available options depend on the specific microcontroller being used.
 * 
 * @note The SPI module must be initialized before any other SPI module function is used.
 */
void SPI_init(SPI_Master_Slave_Select_t Master_Slave_Select, SPI_Clock_Rate_t Clock_Rate);

/**
 * The function SPI_sendReceiveByte sends and receives a byte of data (at the same time) using the SPI protocol.
 * 
 * @param sent_data The parameter "sent_data" is of type uint8, which means it is an 8-bit unsigned integer.
 * It represents the data that will be sent over the SPI (Serial Peripheral Interface) bus.
 * 
 * @return 8-bit data that will be received from the SPI communication.
 */
uint8 SPI_sendReceiveByte(uint8 sent_data);

/**
 * The function SPI_SendByte sends a byte of data using the SPI protocol.
 * 
 * @param sent_data The parameter "sent_data" is of type uint8, which means it is an unsigned 8-bit integer.
 * It represents the data that needs to be sent over the SPI (Serial Peripheral Interface) bus.
 * 
 * @note This function is a blocking function until the byte is sent. It uses the busy waiting polling method.
 */
void SPI_SendByte(uint8 sent_data);

/**
 * The function SPI_ReceiveByte waits until data is received and then returns the received byte.
 * 
 * @return an 8-bit unsigned integer (uint8).
 * 
 * @note This function is a blocking function until the byte is received. It uses the busy waiting polling method.
 */
uint8 SPI_ReceiveByte(void);

/**
 * The function SPI_ReceiveByteCheck checks if the SPI receive flag is set and if so, it receives a
 * byte of data and returns true, otherwise it returns false.
 * 
 * @param ptr_data A pointer to a uint8 variable where the received byte will be stored.
 * 
 * @return a uint8 value, which represents the status of the SPI receive operation.
 * 
 * @note This function is a non-blocking function. It uses the periodic polling method.
 */
uint8 SPI_ReceiveByteCheck(uint8* ptr_data);

/**************************************** Interrupt Enable/Disable ********************************************/
void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);

/***************************************** Call Back Function ***********************************************/
void SPI_SetCallBack(void (*LocalFptr)(void));

/********************************* Send and receive functions with no ckecking - for interrupt - *******************/
/**
 * The function SPI_SendByteNoBlock sends a byte of data using SPI communication without blocking the
 * program execution.
 * 
 * @param sent_data The parameter "sent_data" is of type uint8, which means it is an unsigned 8-bit integer.
 * It represents the data that needs to be sent via SPI (Serial Peripheral Interface).
 * 
 * @note This function is a non-blocking function. this function is used in the interrupt service routine.
 */
void SPI_SendByteNoBlock(uint8 sent_data);

/**
 * The function SPI_GetReceivedByte returns the value of the SPDR register.
 * 
 * @return the value of the SPDR register, which is an 8-bit data register used for SPI communication.
 * 
 * @note This function is a non-blocking function. this function is used in the interrupt service routine.
 */
uint8 SPI_GetReceivedByte(void);
#endif /* SPI_H_ */