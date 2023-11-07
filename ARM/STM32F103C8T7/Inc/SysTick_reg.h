#ifndef SYS_TICK_REG_H
#define SYS_TICK_REG_H

#include "STD_TYPES.h"

/* Core Peripheral Base Address */
#define SYSTICK_BASE_ADDRESS 0xE000E010

/* System Timer (SysTick) Registers offset */
#define STK_CTRL_OFFSET		 0x00
#define STK_LOAD_OFFSET		 0x04
#define STK_VAL_OFFSET		 0x08

/* System Timer (SysTick) Registers Structure */

typedef union
{
	uint32 REG;
	struct
	{
		uint32 ENABLE	 : 1;
		uint32 TICKINT	 : 1;
		uint32 CLKSOURCE : 1;
		uint32			 : 13;
		uint32 COUNTFLAG : 1; // Read only
		uint32			 : 15;
	} bits;
} STK_CTRL_REG_t;

typedef union
{
	uint32 REG;
	struct
	{
		uint32 RELOAD : 24;
		uint32		  : 8;
	} bits;
} STK_LOAD_REG_t;

typedef union
{
	uint32 REG;
	struct
	{
		uint32 CURRENT : 24;
		uint32		   : 8;
	} bits;
} STK_VAL_REG_t;

/* Systick Registers */
#define STK_CTRL (*((volatile STK_CTRL_REG_t*)(SYSTICK_BASE_ADDRESS + STK_CTRL_OFFSET)))
#define STK_LOAD (*((volatile STK_LOAD_REG_t*)(SYSTICK_BASE_ADDRESS + STK_LOAD_OFFSET)))
#define STK_VAL	 (*((volatile STK_VAL_REG_t*)(SYSTICK_BASE_ADDRESS + STK_VAL_OFFSET)))

#endif /* SYS_TICK_REG_H */
