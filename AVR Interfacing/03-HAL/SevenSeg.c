

#include "DIO.h"
#include "SevenSeg.h"

#include "SETTINGS.h"
#include <util/delay.h>

#include "STD_TYPES.h"

#define DECODER_PORT_MASK 0x0F

#if (SEVENSEG_MODE == SEVENSEG_DISPLAY_MODE)
static const uint8 SevenSeg_Matrix[10] = {
	0b00111111, /* 0 */
	0b00000110, /* 1 */
	0b01011011, /* 2 */
	0b01001111, /* 3 */
	0b01100110, /* 4 */
	0b01101101, /* 5 */
	0b01111101, /* 6 */
	0b00000111, /* 7 */
	0b01111111, /* 8 */
	0b01101111	/* 9 */
};
#endif /* SEVENSEG_MODE */

void SevenSeg_init(void)
{
	/****************** 7-segment display pins ******************/
	/* enable pin for each digit */
	DIO_SetPinDirection(SEVENSEG_FIRST_DIGIT_PORT_ID, SEVENSEG_FIRST_DIGIT_PIN_ID, PIN_OUTPUT);
	DIO_SetPinDirection(SEVENSEG_SECOND_DIGIT_PORT_ID, SEVENSEG_SECOND_DIGIT_PIN_ID, PIN_OUTPUT);
	DIO_SetPinDirection(SEVENSEG_THIRD_DIGIT_PORT_ID, SEVENSEG_THIRD_DIGIT_PIN_ID, PIN_OUTPUT);
	DIO_SetPinDirection(SEVENSEG_FOURTH_DIGIT_PORT_ID, SEVENSEG_FOURTH_DIGIT_PIN_ID, PIN_OUTPUT);

	/****************** 7-segment decoder pins ******************/
#if (SEVENSEG_MODE == SEVENSEG_DECODER_MODE)
	DIO_SetPortDirectionGroup(SEVENSEG_DECODER_PORT_ID, (DECODER_PORT_MASK << SEVENSEG_DECODER_PIN_FIRST_ID),
							  PORT_OUTPUT);

#elif (SEVENSEG_MODE == SEVENSEG_DISPLAY_MODE)
	DIO_SetPortDirection(SEVENSEG_DISPLAY_PORT_ID, PORT_OUTPUT);
#endif /* SEVENSEG_MODE */
}

//void SevenSeg_enable(SevenSeg_Digit_t Digit)
//{
//	/****************** Enable the required digit ******************/
//	uint8 digitValues[SEVENSEG_NUM_OF_DIGITS] = {SEVENSEG_DISABLE_VALUE, SEVENSEG_DISABLE_VALUE,
//												 SEVENSEG_DISABLE_VALUE, SEVENSEG_DISABLE_VALUE};
//	if (Digit >= FirstDigit && Digit <= FourthDigit)
//	{
//		digitValues[Digit] = SEVENSEG_ENABLE_VALUE;
//	}
//	DIO_SetPinValue(SEVENSEG_FIRST_DIGIT_PORT_ID, SEVENSEG_FIRST_DIGIT_PIN_ID, digitValues[FirstDigit]);
//	DIO_SetPinValue(SEVENSEG_SECOND_DIGIT_PORT_ID, SEVENSEG_SECOND_DIGIT_PIN_ID, digitValues[SecondDigit]);
//	DIO_SetPinValue(SEVENSEG_THIRD_DIGIT_PORT_ID, SEVENSEG_THIRD_DIGIT_PIN_ID, digitValues[ThirdDigit]);
//	DIO_SetPinValue(SEVENSEG_FOURTH_DIGIT_PORT_ID, SEVENSEG_FOURTH_DIGIT_PIN_ID, digitValues[FourthDigit]);
//}

//void SevenSeg_DisplayNumber(uint8 num)
//{
//	/****************** display the required number ******************/
//	if (0 <= num && num <= 9)
//	{
//		volatile uint8* Port_ptr = PORT[SEVENSEG_DECODER_PORT_ID];
//#if (SEVENSEG_MODE == SEVENSEG_DECODER_MODE)
//		*Port_ptr = (*Port_ptr & ~DECODER_PORT_MASK) | (num & DECODER_PORT_MASK);
//#elif (SEVENSEG_MODE == SEVENSEG_DISPLAY_MODE)
//		*Port_ptr = SevenSeg_Matrix[num];
//#endif /* SEVENSEG_MODE */
//	}
//	/****************** delay ******************/
//	_delay_ms(SEVENSEG_DELAY_MS);
//}

void SevenSeg_DisplayNumber(SevenSeg_Digit_t Digit, uint8 num)
{
	/****************** Enable the required digit ******************/
	uint8 digitValues[SEVENSEG_NUM_OF_DIGITS] = {SEVENSEG_DISABLE_VALUE, SEVENSEG_DISABLE_VALUE,
												 SEVENSEG_DISABLE_VALUE, SEVENSEG_DISABLE_VALUE};

	if (Digit >= FirstDigit && Digit <= FourthDigit)
	{
		digitValues[Digit] = SEVENSEG_ENABLE_VALUE;
	}

	DIO_SetPinValue(SEVENSEG_FIRST_DIGIT_PORT_ID, SEVENSEG_FIRST_DIGIT_PIN_ID, digitValues[FirstDigit]);
	DIO_SetPinValue(SEVENSEG_SECOND_DIGIT_PORT_ID, SEVENSEG_SECOND_DIGIT_PIN_ID, digitValues[SecondDigit]);
	DIO_SetPinValue(SEVENSEG_THIRD_DIGIT_PORT_ID, SEVENSEG_THIRD_DIGIT_PIN_ID, digitValues[ThirdDigit]);
	DIO_SetPinValue(SEVENSEG_FOURTH_DIGIT_PORT_ID, SEVENSEG_FOURTH_DIGIT_PIN_ID, digitValues[FourthDigit]);
	/****************** display the required number ******************/
	if (0 <= num && num <= 9)
	{
		volatile uint8* Port_ptr = PORT[SEVENSEG_DECODER_PORT_ID];
#if (SEVENSEG_MODE == SEVENSEG_DECODER_MODE)
		*Port_ptr = (*Port_ptr & ~DECODER_PORT_MASK) | (num & DECODER_PORT_MASK);
#elif (SEVENSEG_MODE == SEVENSEG_DISPLAY_MODE)
		*Port_ptr = SevenSeg_Matrix[num];
#endif /* SEVENSEG_MODE */
	}

	/****************** delay ******************/
	_delay_ms(SEVENSEG_DELAY_MS);
}