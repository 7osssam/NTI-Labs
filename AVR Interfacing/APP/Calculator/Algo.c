#include "Algo.h"

/********************************************************************
 *                      Private Functions                            *
 ********************************************************************/
/**
 * @brief Pushes a number onto the stack.
 *
 * This function pushes a number onto the stack. The number is added to the top of the stack.
 *
 * @param Stack Pointer to the stack structure.
 * @param Num The number to push onto the stack.
 */
static void push(Stack_t* Stack, uint16 Num)
{
	Stack->Data[++Stack->top] = Num;
}

/**
 * @brief Pops a number from the stack.
 *
 * This function pops a number from the stack. The number is removed from the top of the stack.
 *
 * @param Stack Pointer to the stack structure.
 * @return The number that was popped from the stack, or 0 if the stack is empty.
 */
static uint16 pop(Stack_t* Stack)
{
	if (Stack->top < 0)
	{
		// Handle underflow error
		return 0;
	}
	return Stack->Data[Stack->top--];
}

/********************************************************************
 *                      Public Functions                            *
 ********************************************************************/

/**
 * @brief Check if a character is an operator.
 *
 * @param c The character to check.
 * @return 1 if the character is an operator, 0 otherwise.
 */
uint8 isOperator(uint8 c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

/**
 * @brief Check if a character is a digit.
 *
 * @param c The character to check.
 * @return 1 if the character is a digit, 0 otherwise.
 */
uint16 isCharDigit(uint8 c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Calculate the result of a simple arithmetic expression in a postfix notation.
 *
 * This function takes an input string `str` representing a postfix notation arithmetic
 * expression and calculates the result. It calculates the result using a stack-based algorithm.
 *
 * @param str Pointer to the input string containing the postfix expression.
 * @return The result of the arithmetic expression.
 */
sint16 CalculateExpression(const uint8* str)
{
	uint16	i = 0;
	uint32	CurrentNum = 0;
	uint8	prevOP, Ch;
	Stack_t Stack;

	// Initialize previous operator and current character to '+' to handle the first number.
	prevOP = Ch = '+';
	// Initialize the stack's top index to -1 to indicate an empty stack.
	Stack.top = -1;

	while ('\0' != Ch)
	{
		Ch = str[i]; // Get the current character.

		if (' ' == Ch)
		{
			// Ignore spaces.
		}
		else if (isCharDigit(Ch))
		{
			// If the character is a digit, update the current numeric value.
			CurrentNum = CurrentNum * 10 + Ch - '0';
		}
		else
		{
			// Handle operators.
			switch (prevOP)
			{
				case ('-'):
					CurrentNum = -CurrentNum; // Handle subtraction.

					// Fall through to '+' case intentionally.
				case ('+'):
					push(&Stack, CurrentNum); // Push the current value onto the stack.
					break;
				case ('/'):
					push(&Stack, pop(&Stack) / CurrentNum); // Handle division.
					break;
				case ('*'):
					push(&Stack, pop(&Stack) * CurrentNum); // Handle multiplication.
			}
			prevOP = Ch;	// Update the previous operator.
			CurrentNum = 0; // Reset the current numeric value.
		}
		++i; // Move to the next character in the input string.
	}

	sint16 result = 0;

	// Calculate the final result by summing up the values in the stack.
	for (i = 0; i <= Stack.top; ++i)
	{
		result += Stack.Data[i];
	}

	return result;
}
