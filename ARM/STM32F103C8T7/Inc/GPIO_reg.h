#ifndef GPIO_REG_H_
#define GPIO_REG_H_

#include "GPIO.h"

#define PERIPH_BASE		  (0x40000000)

#define APB1PERIPH_OFFSET (0x00000)
#define APB2PERIPH_OFFSET (0x10000)
#define AHBPERIPH_OFFSET  (0x20000)

#define APB1PERIPH_BASE	  (PERIPH_BASE + APB1PERIPH_OFFSET)
#define APB2PERIPH_BASE	  (PERIPH_BASE + APB2PERIPH_OFFSET)
#define AHBPERIPH_BASE	  (PERIPH_BASE + AHBPERIPH_OFFSET)

#define GPIOA_OFFSET	  (0x0800)
#define GPIOB_OFFSET	  (0x0C00)
#define GPIOC_OFFSET	  (0x1000)

#define GPIOA_BASE		  (APB2PERIPH_BASE + GPIOA_OFFSET)
#define GPIOB_BASE		  (APB2PERIPH_BASE + GPIOB_OFFSET)
#define GPIOC_BASE		  (APB2PERIPH_BASE + GPIOC_OFFSET)

#define GPIOA			  ((GPIO_TypeDef*)(GPIOA_BASE))
#define GPIOB			  ((GPIO_TypeDef*)(GPIOB_BASE))
#define GPIOC			  ((GPIO_TypeDef*)(GPIOC_BASE))

#define PIN0			  (0)
#define PIN1			  (1)
#define PIN2			  (2)
#define PIN3			  (3)
#define PIN4			  (4)
#define PIN5			  (5)
#define PIN6			  (6)
#define PIN7			  (7)
#define PIN8			  (8)
#define PIN9			  (9)
#define PIN10			  (10)

#endif /* GPIO_REG_H_ */