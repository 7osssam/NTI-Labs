#ifndef ALGO_H
#define ALGO_H

#include "STD_TYPES.h"

#define MAX_EXPRESSION_LENGTH 17
#define STACK_SIZE			  100

typedef struct
{
	uint16 Data[STACK_SIZE];
	uint16 top;
} Stack_t;

/**
 * @brief Check if a character is an operator.
 * @param c The character to check.
 * @return 1 if the character is an operator, 0 otherwise.
 */
uint8 isOperator(uint8 c);

/**
 * @brief Check if a character is a digit.
 * @param c The character to check.
 * @return 1 if the character is a digit, 0 otherwise.
 */
uint16 isCharDigit(uint8 c);

/**
 * @brief Calculate the result of a simple arithmetic expression in a postfix notation.
 *
 * This function takes an input string `str` representing a postfix notation arithmetic
 * expression and calculates the result. It calculates the result using a stack-based algorithm.
 *
 * @param str Pointer to the input string containing the postfix expression.
 * @return The result of the arithmetic expression.
 */
sint16 CalculateExpression(const uint8* s);

#endif // ALGO_H