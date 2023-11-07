#ifndef GPIO_H_
#define GPIO_H_

#include "STD_TYPES.h"
#include "GPIO_reg.h"

typedef enum
{
	// output mode
	OUT_PUSH_PULL = 0,
	OUT_OPEN_DRAIN,
	OUT_ALT_PUSH_PULL,
	OUT_ALT_OPEN_DRAIN,
	// input mode
	IN_ANALOG = 0,
	IN_FLOATING,
	IN_PULLUP_PULLDOWN

} GPIO_CNF;

typedef enum
{
	INPUT = 0, // reset state
	OUTPUT_10MHZ,
	OUTPUT_2MHZ,
	OUTPUT_50MHZ
} GPIO_MODE;

typedef struct
{
	volatile uint32 CRL;
	volatile uint32 CRH;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 BRR;
	volatile uint32 LCKR;
} GPIO_TypeDef;

void  GPIO_SetPinDirection(GPIO_TypeDef* port, uint8 pinNumber, GPIO_CNF CNF, GPIO_MODE MODE);
void  GPIO_SetPinValue(GPIO_TypeDef* port, uint8 pinNumber, uint8 value);
void  GPIO_TogglePinValue(GPIO_TypeDef* port, uint8 pinNumber);
uint8 GPIO_GetPinValue(GPIO_TypeDef* port, uint8 pinNumber);

#endif /* GPIO_H_ */