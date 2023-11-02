/******************************************************************
 * @Module   	: DIO
 * @Title 	 	: Configuration Header file for DIO Module
 * @Filename 	: DIO_config.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_

#define NUM_OF_PORTS		  4
#define NUM_OF_PINS_PER_PORT  8
#define NUM_OF_PINS			  32

/* PORTA PINS */
#define PA0_PIN_ID_INDEX	  (uint8)0
#define PA1_PIN_ID_INDEX	  (uint8)1
#define PA2_PIN_ID_INDEX	  (uint8)2
#define PA3_PIN_ID_INDEX	  (uint8)3
#define PA4_PIN_ID_INDEX	  (uint8)4
#define PA5_PIN_ID_INDEX	  (uint8)5
#define PA6_PIN_ID_INDEX	  (uint8)6
#define PA7_PIN_ID_INDEX	  (uint8)7
/* PORTB PINS */
#define PB0_PIN_ID_INDEX	  (uint8)8
#define PB1_PIN_ID_INDEX	  (uint8)9
#define PB2_PIN_ID_INDEX	  (uint8)10
#define PB3_PIN_ID_INDEX	  (uint8)11
#define PB4_PIN_ID_INDEX	  (uint8)12
#define PB5_PIN_ID_INDEX	  (uint8)13
#define PB6_PIN_ID_INDEX	  (uint8)14
#define PB7_PIN_ID_INDEX	  (uint8)15
/* PORTC PINS */
#define PC0_PIN_ID_INDEX	  (uint8)16
#define PC1_PIN_ID_INDEX	  (uint8)17
#define PC2_PIN_ID_INDEX	  (uint8)18
#define PC3_PIN_ID_INDEX	  (uint8)19
#define PC4_PIN_ID_INDEX	  (uint8)20
#define PC5_PIN_ID_INDEX	  (uint8)21
#define PC6_PIN_ID_INDEX	  (uint8)22
#define PC7_PIN_ID_INDEX	  (uint8)23
/* PORTD PINS */
#define PD0_PIN_ID_INDEX	  (uint8)24
#define PD1_PIN_ID_INDEX	  (uint8)25
#define PD2_PIN_ID_INDEX	  (uint8)26
#define PD3_PIN_ID_INDEX	  (uint8)27
#define PD4_PIN_ID_INDEX	  (uint8)28
#define PD5_PIN_ID_INDEX	  (uint8)29
#define PD6_PIN_ID_INDEX	  (uint8)30
#define PD7_PIN_ID_INDEX	  (uint8)31

/* Direction of pins */
/* PORTA PINS */
#define PA0_PIN_DIRECTION	  PIN_OUTPUT
#define PA1_PIN_DIRECTION	  PIN_INPUT
#define PA2_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment 2st digit Eta32 mega */
#define PA3_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment 1st digit Eta32 mega */
#define PA4_PIN_DIRECTION	  PIN_INPUT
#define PA5_PIN_DIRECTION	  PIN_INPUT
#define PA6_PIN_DIRECTION	  PIN_INPUT
#define PA7_PIN_DIRECTION	  PIN_INPUT
/* PORTB PINS */
#define PB0_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment decoder 1st Eta32 mega */
#define PB1_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment decoder 2st Eta32 mega */
#define PB2_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment decoder 3st Eta32 mega */
#define PB3_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment decoder 4st Eta32 mega */
#define PB4_PIN_DIRECTION	  PIN_INPUT
#define PB5_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment 3st digit Eta32 mega */
#define PB6_PIN_DIRECTION	  PIN_OUTPUT /* 7-segment 4st digit Eta32 mega */
#define PB7_PIN_DIRECTION	  PIN_INPUT
/* PORTC PINS */
#define PC0_PIN_DIRECTION	  PIN_INPUT
#define PC1_PIN_DIRECTION	  PIN_INPUT
#define PC2_PIN_DIRECTION	  PIN_INPUT
#define PC3_PIN_DIRECTION	  PIN_INPUT
#define PC4_PIN_DIRECTION	  PIN_INPUT
#define PC5_PIN_DIRECTION	  PIN_INPUT
#define PC6_PIN_DIRECTION	  PIN_INPUT
#define PC7_PIN_DIRECTION	  PIN_INPUT
/* PORTD PINS */
#define PD0_PIN_DIRECTION	  PIN_INPUT
#define PD1_PIN_DIRECTION	  PIN_INPUT
#define PD2_PIN_DIRECTION	  PIN_OUTPUT /* INT0 - EXTI */
#define PD3_PIN_DIRECTION	  PIN_OUTPUT
#define PD4_PIN_DIRECTION	  PIN_INPUT
#define PD5_PIN_DIRECTION	  PIN_OUTPUT /* OC1A - PWM */
#define PD6_PIN_DIRECTION	  PIN_INPUT	 /* ICP1 - ICU */
#define PD7_PIN_DIRECTION	  PIN_INPUT

/* Initial value of pins */
/* PORTA PINS */
#define PA0_PIN_INITIAL_VALUE LOGIC_LOW
#define PA1_PIN_INITIAL_VALUE LOGIC_LOW
#define PA2_PIN_INITIAL_VALUE LOGIC_LOW
#define PA3_PIN_INITIAL_VALUE LOGIC_LOW
#define PA4_PIN_INITIAL_VALUE LOGIC_LOW
#define PA5_PIN_INITIAL_VALUE LOGIC_LOW
#define PA6_PIN_INITIAL_VALUE LOGIC_LOW
#define PA7_PIN_INITIAL_VALUE LOGIC_LOW
/* PORTB PINS */
#define PB0_PIN_INITIAL_VALUE LOGIC_LOW
#define PB1_PIN_INITIAL_VALUE LOGIC_LOW
#define PB2_PIN_INITIAL_VALUE LOGIC_LOW
#define PB3_PIN_INITIAL_VALUE LOGIC_LOW
#define PB4_PIN_INITIAL_VALUE LOGIC_LOW
#define PB5_PIN_INITIAL_VALUE LOGIC_LOW
#define PB6_PIN_INITIAL_VALUE LOGIC_LOW
#define PB7_PIN_INITIAL_VALUE LOGIC_LOW
/* PORTC PINS */
#define PC0_PIN_INITIAL_VALUE LOGIC_LOW
#define PC1_PIN_INITIAL_VALUE LOGIC_LOW
#define PC2_PIN_INITIAL_VALUE LOGIC_LOW
#define PC3_PIN_INITIAL_VALUE LOGIC_LOW
#define PC4_PIN_INITIAL_VALUE LOGIC_LOW
#define PC5_PIN_INITIAL_VALUE LOGIC_LOW
#define PC6_PIN_INITIAL_VALUE LOGIC_LOW
#define PC7_PIN_INITIAL_VALUE LOGIC_LOW
/* PORTD PINS */
#define PD0_PIN_INITIAL_VALUE LOGIC_HIGH /* pull up resistor */
#define PD1_PIN_INITIAL_VALUE LOGIC_LOW
#define PD2_PIN_INITIAL_VALUE LOGIC_HIGH
#define PD3_PIN_INITIAL_VALUE LOGIC_LOW
#define PD4_PIN_INITIAL_VALUE LOGIC_LOW
#define PD5_PIN_INITIAL_VALUE LOGIC_LOW
#define PD6_PIN_INITIAL_VALUE LOGIC_LOW
#define PD7_PIN_INITIAL_VALUE LOGIC_LOW

#endif /* DIO_CONFIG_H_ */