/******************************************************************
 * @Module   	: Two Wire Interface (TWI) (I2C)
 * @Title 	 	: Two Wire Interface header file
 * @Filename 	: TWI.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#ifndef TWI_H_
#define TWI_H_

#include "STD_TYPES.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* TWI Status Bits in the TWSR Register */
/* start has been sent */
#define TWI_START		 0x08
/* repeated start */
#define TWI_REP_START	 0x10
/* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_W_ACK 0x18
/* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK 0x40
/* Master transmit data and ACK has been received from Slave. */
#define TWI_MT_DATA_ACK	 0x28
/* Master received data and send ACK to slave. */
#define TWI_MR_DATA_ACK	 0x50
/* Master received data but doesn't send ACK to slave. */
#define TWI_MR_DATA_NACK 0x58

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NormalMode_100Kb = 100000u,
	FastMode_400Kb = 400000u,
	FastModePlus_1Mb = 1000000u,
	HighSpeedMode_3Mb = 3400000u
} SCL_Frquency;

typedef enum
{
	TWI_Prescaler_1,
	TWI_Prescaler_4,
	TWI_Prescaler_16,
	TWI_Prescaler_64

} TWI_Prescaler;

typedef enum
{
	TWI_GeneralCallRecognitionEnable_OFF,
	TWI_GeneralCallRecognitionEnable_ON
} TWI_GENERAL_CALL_RECOGNITION_ENABLE_MODE;

typedef struct
{
	SCL_Frquency							 SCL_Frq;
	TWI_Prescaler							 prescaler;
	TWI_GENERAL_CALL_RECOGNITION_ENABLE_MODE generalCallRecognitionMode;
	uint8									 TWI_slaveAddress;
} TWI_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/**
 * @brief Initialize the TWI (I2C) module based on the provided configuration.
 *
 * This function initializes the TWI module based on the configuration provided
 * through the \c Config_Ptr parameter. It sets the TWBR value, prescaler,
 * slave address, and enables the TWI module.
 *
 * @param Config_Ptr A pointer to the configuration structure.
 */
void TWI_init(const TWI_configType* Config_Ptr);

/**
 * @brief Start the TWI communication.
 *
 * This function generates a start condition on the TWI bus. It waits until the
 * start bit is sent successfully before returning.
 */
void TWI_start(void);

/**
 * @brief Stop the TWI communication.
 *
 * This function generates a stop condition on the TWI bus. It waits until the
 * stop bit is sent successfully before returning.
 */
void TWI_stop(void);

/**
 * @brief Write a byte to the TWI bus.
 *
 * This function writes a byte of data to the TWI bus. It puts the data into
 * the TWI data register, starts the data transmission, and waits until the
 * data is sent successfully before returning.
 *
 * @param data The byte of data to be written.
 */
void TWI_writeByte(uint8 data);

/**
 * @brief Read a byte from the TWI bus with ACK.
 *
 * This function reads a byte of data from the TWI bus with an acknowledgment (ACK).
 * It starts reading, sends an ACK after receiving the data, and waits until the
 * data is received before returning.
 *
 * @return The byte of data received.
 */
uint8 TWI_readByteWithACK(void); // read with send Ack

/**
 * @brief Read a byte from the TWI bus with NACK.
 *
 * This function reads a byte of data from the TWI bus with a not-acknowledgment (NACK).
 * It starts reading, does not send an ACK after receiving the data, and waits until
 * the data is received before returning.
 *
 * @return The byte of data received.
 */
uint8 TWI_readByteWithNACK(void); // read without send Ack

/**
 * @brief Get the current status of the TWI bus.
 *
 * This function returns the current status of the TWI bus by masking and extracting
 * the relevant status bits from the TWSR register.
 *
 * @return The current status of the TWI bus.
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
