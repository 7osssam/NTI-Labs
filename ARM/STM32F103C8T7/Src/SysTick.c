/******************************************************************
 * @Title    : System Tick Driver Source
 * @Filename : SysTick.c
 * @Author   : Hossam Mohamed
 * @Compiler : 
 * @Target   : 
 * @Notes 	 :
 ********************************************************************/

#include "sysTick.h"
#include "SysTick_reg.h"

void SysTick_init(SysTick_ConfigType* Config_Ptr)
{
	/* disable systick */
	STK_CTRL.bits.ENABLE = 0;

	/* Set clock source
	 * 0: PIOSC/4
	 * 1: System Clock */
	STK_CTRL.bits.CLKSOURCE = Config_Ptr->ClkSrc;

	/* Set reload value */
	STK_LOAD.bits.RELOAD = Config_Ptr->ReloadValue - 1;

	/* Set interrupt enable
	 * 0: Disable
	 * 1: Enable */
	STK_CTRL.bits.TICKINT = Config_Ptr->Int;

	/* enable systick */
	STK_CTRL.bits.ENABLE = 1;
}

void SysTick_SetPriority(uint8 ExceptionPriority)
{
	/* set priority of the systick interrupt using TICK field in SYSPRI3 register in SCB */
	//SYSPRI3.bits.TICK = ExceptionPriority;
}

void SysTick_enableException(void)
{
	/* Set interrupt enable
	 * 0: Disable
	 * 1: Enable */
	STK_CTRL.bits.TICKINT = 1;
}

void SysTick_disableException(void)
{
	/* Set interrupt enable
	 * 0: Disable
	 * 1: Enable */
	STK_CTRL.bits.TICKINT = 0;
}
