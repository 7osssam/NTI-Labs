/******************************************************************
 * @Project	 	: Calculator  
 * @Description : A simple calculator with 2 modes (Basic and Programmer). 
 * 				  The calculator supports the following operations:	
 * 				  1. Basic Mode: +, -, *, /, %, =, AC, DEL (with precedence and associativity).
 * 				  2. Programmer Mode: DEC -> BIN and BIN.
 * @Note 		: The calculator handles Invalid inputs and operations.
 * @target  	: ATMEGA32 (eta32)
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc   
 ********************************************************************/
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#define DELAY_PRESS_TIME 300

/**
 * @brief Display the main menu on the LCD and handle user input to choose the calculator mode.
 */
void CalculatorMenu(void);

#endif /* __CALCULATOR_H__ */