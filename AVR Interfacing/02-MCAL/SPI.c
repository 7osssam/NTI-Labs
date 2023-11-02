/******************************************************************
 * @Module   	: Serial Peripheral Interface(SPI)
 * @Title 	 	: SPI Module source file
 * @Filename 	: SPI.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#include "SPI.h"
#include "SPI_config.h"

#include "BIT_MACROS.h"
#include "DIO.h"
#include "DIO_map.h"

#include <avr/interrupt.h>

#define Clock_Rate_Mask 0x03

static void (*SPI_callBackPtr)(void) = NULL_PTR;

/******************************************* initialization  *********************************************/
void SPI_init(SPI_Master_Slave_Select_t Master_Slave_Select, SPI_Clock_Rate_t Clock_Rate)
{
	//***************************** Data Order *****************************************
#if Data_Order == LSB
	SET_BIT(SPCR, DORD);
#elif Data_Order == MSB
	CLEAR_BIT(SPCR, DORD);
#endif

	//***************************** Master/Slave Select ********************************/
	if (Master_Slave_Select == SPI_Master)
	{
		/******** Configure SPI Master Pins *********
		 * SS   --> Output
		 * MOSI --> Output
		 * MISO --> Input
		 * SCK  --> Output
		 ********************************************/
		DIO_SetPinDirection(SPI_PORT, SS_PIN, PIN_OUTPUT);
		DIO_SetPinDirection(SPI_PORT, MOSI_PIN, PIN_OUTPUT);
		DIO_SetPinDirection(SPI_PORT, MISO_PIN, PIN_INPUT);
		DIO_SetPinDirection(SPI_PORT, SCK_PIN, PIN_OUTPUT);
		SET_BIT(SPCR, MSTR);
	}
	else if (Master_Slave_Select == SPI_Slave)
	{
		/******** Configure SPI Slave Pins *********
		 * SS   --> Input
		 * MOSI --> Input
		 * MISO --> Output
		 * SCK  --> Input
		 ********************************************/
		DIO_SetPinDirection(SPI_PORT, SS_PIN, PIN_INPUT);
		DIO_SetPinDirection(SPI_PORT, MOSI_PIN, PIN_INPUT);
		DIO_SetPinDirection(SPI_PORT, MISO_PIN, PIN_OUTPUT);
		DIO_SetPinDirection(SPI_PORT, SCK_PIN, PIN_INPUT);
		CLEAR_BIT(SPCR, MSTR);
	}

	//***************************** Operation level (Clock polarity) ********************/
#if OPERATING_LEVEL == SPI_IDLE_LOW
	CLEAR_BIT(SPCR, CPOL);
#elif OPERATING_LEVEL == SPI_IDLE_HIGH
	SET_BIT(SPCR, CPOL);
#endif

	//***************************** Sampling Egde (Clock Phase) ************************/
#if SAMPLING_EDGE == SPI_RISING
	SET_BIT(SPCR, CPHA);
#elif SAMPLING_EDGE == SPI_FALLING
	CLEAR_BIT(SPCR, CPHA);
#endif

	//***************************** Clock Rate *****************************************/
	SPCR = (SPCR & ~Clock_Rate_Mask) | (Clock_Rate & Clock_Rate_Mask);

	//***************************** SPI Double Speed ***********************************/
#if SPI_Double_SPEED == SPI_Double_SPEED_ON
	SET_BIT(SPSR, SPI2X);
#elif SPI_Double_SPEED == SPI_Double_SPEED_OFF
	CLEAR_BIT(SPSR, SPI2X);
#endif

	//***************************** SPI Enable/Disable *********************************/
#if SPI_STATE == SPI_ENABLE
	SET_BIT(SPCR, SPE);
#elif SPI_STATE == SPI_DISABLE
	CLEAR_BIT(SPCR, SPE);
#endif
}

/**************************************** Interrupt Enable/Disable ********************************************/
void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR, SPIE);
}

void SPI_InterruptDisable(void)
{
	CLEAR_BIT(SPCR, SPIE);
}

/***************************************** Call Back functions ***********************************************/
void SPI_SetCallBack(void (*LocalFptr)(void))
{
	SPI_callBackPtr = LocalFptr;
}

/********************************************** ISR ************************************************************/
ISR(SPI_STC_vect)
{
	if (SPI_callBackPtr != NULL_PTR)
	{
		SPI_callBackPtr();
	}
}

/********************************** Send and receive functions with polling **************************************/

uint8 SPI_sendReceiveByte(uint8 sent_data)
{
	SPDR = sent_data; // send data

	while (IS_BIT_CLEAR(SPSR, SPIF)) // wait until data is received/sent
		;

	return SPDR; // received data
}

void SPI_SendByte(uint8 sent_data)
{
	SPDR = sent_data;
	while (IS_BIT_CLEAR(SPSR, SPIF)) // wait until data is sent
		;
}

uint8 SPI_ReceiveByte(void)
{
	while (IS_BIT_CLEAR(SPSR, SPIF)) // wait until data is received
		;
	return SPDR;
}

uint8 SPI_ReceiveByteCheck(uint8* ptr_data)
{
	uint8 status = FALSE;
	if (IS_BIT_CLEAR(SPSR, SPIF))
	{
		*ptr_data = SPDR;
		status = TRUE;
	}
	return status;
}

/********************************* Send and receive functions with no ckecking - for interrupt - *******************/

void SPI_SendByteNoBlock(uint8 sent_data)
{
	SPDR = sent_data;
}

uint8 SPI_GetReceivedByte(void)
{
	return SPDR;
}
