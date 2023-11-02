/******************************************************************
 * @Module   	: Serial Peripheral Interface(SPI)
 * @Title 	 	: SPI Static Configurations header file
 * @Filename 	: SPI_config.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/
#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/*********************************************
 * 			Static Configurations			 *
 *********************************************/
#define Data_Order			 MSB
#define OPERATING_LEVEL		 SPI_IDLE_LOW
#define SAMPLING_EDGE		 SPI_RISING
#define SPI_STATE			 SPI_ENABLE
#define SPI_Double_SPEED	 SPI_Double_SPEED_OFF

#define SPI_PORT			 PORTB_ID
#define SS_PIN				 PIN4_ID
#define MOSI_PIN			 PIN5_ID
#define MISO_PIN			 PIN6_ID
#define SCK_PIN				 PIN7_ID

/********** Data Order **************/
#define LSB					 0
#define MSB					 1
/********* Master/Slave Select ******/
#define SPI_Master			 0
#define SPI_Slave			 1
/********* Clock Polarity **********/
#define SPI_IDLE_LOW		 0
#define SPI_IDLE_HIGH		 1
/********* Clock Phase *************/
#define SPI_RISING			 0
#define SPI_FALLING			 1
/******** SPI STATE ****************/
#define SPI_ENABLE			 0
#define SPI_DISABLE			 1
/********* SPI Double Speed ********/
#define SPI_Double_SPEED_ON	 0
#define SPI_Double_SPEED_OFF 1

#endif /* SPI_CONFIG_H_ */