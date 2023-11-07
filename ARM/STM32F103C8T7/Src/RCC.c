
#include "STD_TYPES.h"
#include "BIT_MACROS.h"

#include "RCC_config.h"
#include "RCC_reg.h"
#include "RCC.h"

void RCC_EnableHSI(void)
{
	SET_BIT(RCC->RCC_CR, HSION); //Enable HSI.
	while (IS_BIT_CLEAR(RCC->RCC_CR, HSIRDY))
		;							//Polling until HSI is ready.
	SET_BIT(RCC->RCC_CIR, HSIRDYC); //Clear HSI ready flag.

	CLEAR_BIT(RCC->RCC_CFGR, SW0); //Select HSI as system clock.
	CLEAR_BIT(RCC->RCC_CFGR, SW1); //Select HSI as system clock.
}

void RCC_EnableHSE(void)
{
	SET_BIT(RCC->RCC_CR, HSEON); //Enable HSE.
	while (IS_BIT_CLEAR(RCC->RCC_CR, HSERDY))
		;							//Polling until HSE is ready.
	SET_BIT(RCC->RCC_CIR, HSERDYC); //Clear HSE ready flag.
	SET_BIT(RCC->RCC_CFGR, SW0);	//Select HSE as system clock.
	CLEAR_BIT(RCC->RCC_CFGR, SW1);	//Select HSE as system clock.
}

void RCC_EnablePLL(PLL_CLKSource_t PLL_CLKSource, PLL_Value_t PLL_Value)
{
	SET_BIT(RCC->RCC_CR, PLLON); //Enable PLL.
	while (IS_BIT_CLEAR(RCC->RCC_CR, PLLRDY))
		;							//Polling until PLL is ready.
	SET_BIT(RCC->RCC_CIR, PLLRDYC); //Clear PLL ready flag.
	switch (PLL_CLKSource)
	{										  //Jump to CLK source of PLL.
		case Half_HSI:						  //If PLL CLK source is half HSI.
			CLEAR_BIT(RCC->RCC_CFGR, PLLSRC); //HSI oscillator clock / 2 selected as PLL input clock.
			break;
		case Half_HSE:						  //If PLL CLK source is half HSE.
			SET_BIT(RCC->RCC_CFGR, PLLSRC);	  //HSE oscillator clock selected as PLL input clock.
			SET_BIT(RCC->RCC_CFGR, PLLXTPRE); //HSE clock divided by 2.
			break;
		case HSE:								//If PLL CLK source is HSE.
			SET_BIT(RCC->RCC_CFGR, PLLSRC);		//HSE oscillator clock selected as PLL input clock.
			CLEAR_BIT(RCC->RCC_CFGR, PLLXTPRE); //HSE clock not divided.
			break;
		default:
			// Error Message
			break;
	}
	RCC->RCC_CFGR =
		((RCC->RCC_CFGR) & PLL_VALUE_MASK) | (PLL_Value << PLLMUL0); //Set value of PLL multiplication factor.
}

void Reset_Module(RCC_APBRSTR_t peripheralIdx)
{
	if (PERIPHERAL_IN_RCC_APB2RSTR)
	{											   //Check if this HW module is in RCC_APB2RSTR Register.
		SET_BIT(RCC->RCC_APB2RSTR, peripheralIdx); //Reset the chosen HW module.
	}
	else if (PERIPHERAL_IN_RCC_APB1RSTR)
	{											   //Check if this HW module is in RCC_APB1RSTR Register.
		peripheralIdx %= SIZE_OF_REGISTER;		   //peripheralIdx = peripheralIdx - 32
		SET_BIT(RCC->RCC_APB1RSTR, peripheralIdx); //Reset CLK for the chosen HW module.
	}
}

void Remove_ResetFlag(void)
{
	SET_BIT(RCC->RCC_CSR, RMVF); //Remove reset flag.
}

void RCC_EnableCLK(uint8 peripheralIdx)
{
	if (PERIPHERAL_IN_RCC_AHBENR)
	{											 //Check if this HW module is in RCC_AHBENR Register.
		SET_BIT(RCC->RCC_AHBENR, peripheralIdx); //Enable CLK for the chosen HW module.
	}
	else if (PERIPHERAL_IN_RCC_APB2ENR)
	{											  //Check if this HW module is in RCC_APB2ENR Register.
		peripheralIdx %= SIZE_OF_REGISTER;		  //peripheralIdx = peripheralIdx - 32
		SET_BIT(RCC->RCC_APB2ENR, peripheralIdx); //Enable CLK for the chosen HW module.
	}
	else if (PERIPHERAL_IN_RCC_APB1ENR)
	{											  //Check if this HW module is in RCC_APB1ENR Register.
		peripheralIdx %= SIZE_OF_REGISTER;		  //peripheralIdx = peripheralIdx - 64
		SET_BIT(RCC->RCC_APB1ENR, peripheralIdx); //Enable CLK for the chosen HW module.
	}
}

void RCC_DisableCLK(uint8 peripheralIdx)
{
	if (PERIPHERAL_IN_RCC_AHBENR)
	{											   //Check if this HW module is in RCC_AHBENR Register.
		CLEAR_BIT(RCC->RCC_AHBENR, peripheralIdx); //Disable CLK for the chosen HW module.
	}
	else if (PERIPHERAL_IN_RCC_APB2ENR)
	{												//Check if this HW module is in RCC_APB2ENR Register.
		peripheralIdx %= SIZE_OF_REGISTER;			//peripheralIdx = peripheralIdx - 32
		CLEAR_BIT(RCC->RCC_APB2ENR, peripheralIdx); //Disable CLK for the chosen HW module.
	}
	else if (PERIPHERAL_IN_RCC_APB1ENR)
	{												//Check if this HW module is in RCC_APB1ENR Register.
		peripheralIdx %= SIZE_OF_REGISTER;			//peripheralIdx = peripheralIdx - 64
		CLEAR_BIT(RCC->RCC_APB1ENR, peripheralIdx); //Disable CLK for the chosen HW module.
	}
}

void RCC_Config(void)
{
	/*******************************************
	 - This function enables system clock based
	   on the user configuration.
	 - It also configure some registers in the RCC
	   Peripheral.
	 *******************************************/
#if (RCC_CLOCK == Enable_HSI)
	RCC_EnableHSI();
#elif (RCC_CLOCK == Enable_HSE)
	RCC_EnableHSE();
#elif (RCC_CLOCK == Enable_PLL)
	RCC_EnablePLL(PLL_CLK_Source, PLL_Multiplication_Factor);
#else
	/* Error message: No system clock is enabled */
	#error "RCC_Config() NO SYSTEM CLOCK IS ENABLED"
#endif
}
