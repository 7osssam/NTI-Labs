/******************************************************************
 * @Module   	: Universal Asynchronous Receiver Transmitter(UART)
 * @Title 	 	: UART Module source file
 * @Filename 	: UART.c 
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#include "UART.h"
#include "BIT_MACROS.h"
#include "UART_config.h"

#include <avr/interrupt.h>
#include "DIO_map.h"
//#include <avr/io.h>

#include "SETTINGS.h" // for F_CPU

#define BAUD_RATE_ASYNC_NORMAL(baud_rate) ((F_CPU / (16UL * (baud_rate))) - 1)
#define BAUD_RATE_ASYNC_DOUBLE(baud_rate) ((F_CPU / (8UL * (baud_rate))) - 1)
#define BAUD_RATE_SYNC_MASTER(baud_rate)  ((F_CPU / (2UL * (baud_rate))) - 1)

#define PARITY_BITS_MASK				  0xCF // 0b11001111
#define DATA_BITS_MASK					  0xF9 // 0b11111001 -Note that UCSZ2 is not included as it is not in UCSRC register
#define UART_MODE_MASK					  0xBF // 0b10111111

/*************************** Pointer to functions to be assigned to ISR ********************************/
static void (*UART_RX_callBackPtr)(void) = NULL_PTR;
static void (*UART_TX_callBackPtr)(void) = NULL_PTR;

/************************* Array of  UBRR values ***************************/

/******************************************* initialization  *********************************************/
void UART_init(UART_ConfigType* a_config_ptr)
{
	volatile uint8 UCSRC_var = 0; // write UCSRC settings in one step then write it to UCSRC register
	uint16		   UBRR_var = 0;

	//***************************** transmission speed ***************************/
#if (SPEED_MODE == NORMAL_SPEED)
	CLEAR_BIT(UCSRA, U2X);
#elif (SPEED_MODE == DOUBLE_SPEED)
	SET_BIT(UCSRA, U2X);
#endif

	//********************* Communication mode *******************************/
	UCSRC_var = (UCSRC_var & UART_MODE_MASK) | ((SYNCH_MODE) << UMSEL);

	//**************************** Parity bits *******************************/
	UCSRC_var = (UCSRC_var & PARITY_BITS_MASK) | ((a_config_ptr->parity) << UPM0);

	//*********************** Number of data bits *******************************/
	UCSRC_var = (UCSRC_var & DATA_BITS_MASK) | ((a_config_ptr->bit_data) << UCSZ0);
	if (a_config_ptr->bit_data == UART_9_BIT_DATA)
		SET_BIT(UCSRB, UCSZ2);

	//*********************** Number of stop bits *******************************/
	WRITE_BIT(UCSRC_var, USBS, a_config_ptr->stop_bit);

	//****************** Set URSEL to access UCSRC register *********************/
	SET_BIT(UCSRC_var, URSEL);

	//***************** Write UCSRC register *******************************/
	UCSRC = (uint8)UCSRC_var;

	//************************ Set baud rate *******************************/
#if (SYNCH_MODE == ASYNCH)
	#if (SPEED_MODE == NORMAL_SPEED)
	UBRR_var = (uint16)BAUD_RATE_ASYNC_NORMAL(a_config_ptr->baud_rate)
	#elif (SPEED_MODE == DOUBLE_SPEED)
	UBRR_var = (uint16)BAUD_RATE_ASYNC_DOUBLE(a_config_ptr->baud_rate);
	#endif
#elif (SYNCH_MODE == SYNCH)
	UBRR_var = (uint16)BAUD_RATE_SYNC_MASTER(a_config_ptr->baud_rate);
#endif

		UBRRH = (uint8)(UBRR_var >> 8);
	UBRRL = (uint8)UBRR_var;

	//************************ Enable receiver and transmitter *******************************/
	// enable UART  receiver.
	SET_BIT(UCSRB, RXEN);
	// enable UART  transmitter .
	SET_BIT(UCSRB, TXEN);
}

/**************************************** Interrupt Enable/Disable ********************************************/
void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB, RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB, RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB, TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB, TXCIE);
}

/**************************************** Set Call Back Functions ********************************************/
void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_callBackPtr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_callBackPtr = LocalFptr;
}

/********************************************** ISR ************************************************************/
ISR(USART_RXC_vect) // ISR for receive complete interrupt
{
	if (UART_RX_callBackPtr != NULL_PTR)
	{
		UART_RX_callBackPtr();
	}
}

ISR(USART_TXC_vect) // ISR for transmit complete interrupt
{
	if (UART_TX_callBackPtr != NULL_PTR)
	{
		UART_TX_callBackPtr();
	}
}

/********************************** Send and receive functions with polling **************************************/
void UART_SendByte(uint8 sent_data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready
	for transmitting a new byte so wait until this flag is set to one */
	while (IS_BIT_CLEAR(UCSRA, UDRE))
		; // Busy wait polling

	/* the UDRE flag will be cleared by hardware when u write new data to buffer.*/
	UDR = sent_data;

	// ================== Another Method ==================
	//UDR = sent_data;
	//while (IS_BIT_CLEAR(UCSRA, TXC)) // Wait until the transmission is complete TXC = 1
	//	;
	//SET_BIT(UCSRA, TXC); // Clear the TXC flag
}

uint8 UART_ReceiveByte(void)
{
	/* RXC flag is set when the UART receive data so  wait until this flag is set to one
	and it will cleared by hardware when u read the data */
	while (IS_BIT_CLEAR(UCSRA, RXC)) // Busy wait polling
		;

#if (ERROR_CHECKING == TRUE)
	/************************* Error Checkings *************************
	 * FE: Frame Error (Stop Bit)
	 * DOR: Data OverRun
	 * PE: Parity Error
	 *******************************************************************/
	UART_error_t status = UART_NO_ERROR;

	if (IS_BIT_SET(UCSRA, FE)) // Frame Error
	{
		status = UART_FRAMING_ERROR;
	}
	else if (IS_BIT_SET(UCSRA, DOR)) // Data OverRun
	{
		status = UART_DATA_OVERRUN_ERROR;
	}
	else if (IS_BIT_SET(UCSRA, PE)) // Parity Error
	{
		status = UART_PARITY_ERROR;
	}
	else
	{
		status = UART_NO_ERROR;
	}

	if (status == UART_NO_ERROR)
	{
		return UDR;
	}
	else
	{
		return status;
	}
#endif /* ERROR_CHECKING */

	return UDR;
}

uint8 UART_ReceiveByteCheck(uint8* ptr_data)
{
	uint8 status = FALSE;
	if (IS_BIT_SET(UCSRA, RXC))
	{
		*ptr_data = UDR;
		status = TRUE;
	}
	return status;
}

/********************************* Send and receive functions with no ckecking - for interrupt - *******************/
void UART_SendByteNoBlock(uint8 sent_data)
{
	UDR = sent_data;
}

uint8 UART_GetReceivedByte(void)
{
	return UDR;
}
