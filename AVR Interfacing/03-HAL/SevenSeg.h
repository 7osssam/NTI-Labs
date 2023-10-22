
#ifndef SEVENSEG_H_
#define SEVENSEG_H_

#include "STD_TYPES.h"
#include "BIT_MACROS.h"

#define SEVENSEG_COMMON_CATHODE 0
#define SEVENSEG_COMMON_ANODE	1

#define SEVENSEG_DECODER_MODE	0
#define SEVENSEG_DISPLAY_MODE	1

#define SEVENSEG_NUM_OF_DIGITS	4

#define SEVENSEG_DELAY_MS		(20 / SEVENSEG_NUM_OF_DIGITS)

/****************************************************************
 * 	Configurations 
 ****************************************************************/
#define SEVENSEG_MODE			SEVENSEG_DECODER_MODE
#define SEVENSEG_COMMON_TYPE	SEVENSEG_COMMON_CATHODE
/****************************************************************/

#if (SEVENSEG_COMMON_TYPE == SEVENSEG_COMMON_CATHODE)
	#define SEVENSEG_ENABLE_VALUE  LOGIC_LOW
	#define SEVENSEG_DISABLE_VALUE LOGIC_HIGH
#elif (SEVENSEG_COMMON_TYPE == SEVENSEG_COMMON_ANODE)
	#define SEVENSEG_ENABLE_VALUE  LOGIC_HIGH
	#define SEVENSEG_DISABLE_VALUE LOGIC_LOW
#endif

/* the number to be displayed on 7-segment will be sent to the decoder port or the display port */
#if (SEVENSEG_MODE == SEVENSEG_DECODER_MODE)
	#define SEVENSEG_DECODER_PORT_ID	  PORTB_ID
	#define SEVENSEG_DECODER_PIN_FIRST_ID PIN0_ID
#elif (SEVENSEG_MODE == SEVENSEG_DISPLAY_MODE)
	#define SEVENSEG_DISPLAY_PORT_ID PORTC_ID
#endif /* SEVENSEG_MODE */

/* 7-segment display pins */
/* enable pin for each digit */
#define SEVENSEG_FIRST_DIGIT_PORT_ID  PORTA_ID
#define SEVENSEG_FIRST_DIGIT_PIN_ID	  PIN3_ID

#define SEVENSEG_SECOND_DIGIT_PORT_ID PORTA_ID
#define SEVENSEG_SECOND_DIGIT_PIN_ID  PIN2_ID

#define SEVENSEG_THIRD_DIGIT_PORT_ID  PORTB_ID
#define SEVENSEG_THIRD_DIGIT_PIN_ID	  PIN5_ID

#define SEVENSEG_FOURTH_DIGIT_PORT_ID PORTB_ID
#define SEVENSEG_FOURTH_DIGIT_PIN_ID  PIN6_ID

typedef enum
{
	FirstDigit,
	SecondDigit,
	ThirdDigit,
	FourthDigit
} SevenSeg_Digit_t;

void SevenSeg_init(void);
void SevenSeg_DisplayNumber(SevenSeg_Digit_t Digit, uint8 num);
#endif /* SEVENSEG_H_ */