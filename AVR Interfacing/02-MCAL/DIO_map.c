/******************************************************************
 * @Module   	: DIO
 * @Title 	 	: Source file for DIO mapping Module
 * @Filename 	: DIO_map.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/
#include "DIO_map.h"

volatile uint8* const PORT[NUM_OF_PORTS] = {PORTA, PORTB, PORTC, PORTD};

volatile uint8* const DDR[NUM_OF_PORTS] = {DDRA, DDRB, DDRC, DDRD};

volatile uint8* const PIN[NUM_OF_PORTS] = {PINA, PINB, PINC, PIND};
