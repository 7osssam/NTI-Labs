/******************************************************************
 * @Title    : Nested Vector Interrupt Controller (NVIC) Driver Source
 * @Filename : NVIC.c
 * @Author   : Hossam Mohamed
 * @Compiler : 
 * @Target   : 
 * @Notes 	 : 
 ********************************************************************/

#include "NVIC.h"
#include "BIT_MACROS.h"
#include "NVIC_reg.h"

/**********************************************************************************************************************
 *                                                  LOCAL DATA                                                        *
 *********************************************************************************************************************/

void NVIC_Init(const NVIC_ConfigType* configPtr)
{
	uint32 ISEn;		   /*ISEn Register Which Irq resident in*/
	uint32 IRQ_ISE_Offset; /*IRQ_Num in ISEn Register*/
	uint32 IPRn;
	uint32 IRQ_PriOffset;
	uint32 totalPriority;

	/*Get Offset Of ISEn Register Which Irq resident in */
	ISEn = configPtr->IRQ_Num / 32;

	/*Get Offset Of IRQ_Num in ISEn Register */
	IRQ_ISE_Offset = configPtr->IRQ_Num % 32;

	/*Enable Interrupt*/
	IRQ_SET_ENABLE(ISEn, IRQ_ISE_Offset);

	/*Get Offset Of IPRn Register Which Irq resident in */
	IPRn = configPtr->IRQ_Num / NVIC_PRIORITY_FIELDS_PER_REG;

	/*Get Offset Of IRQ_Num in IPRn Register (INTA/INTB/INTC/INTD) */
	IRQ_PriOffset = configPtr->IRQ_Num % NVIC_PRIORITY_FIELDS_PER_REG;

	/*Caclulate Total Priority For Irq*/
	totalPriority = configPtr->groupPriority | configPtr->subGroupPriority;

	/*Make Sure That Total Priority Doesnot Exceed 3 Bits*/
	totalPriority &= 0x00000007;

	/*Set Irq Priority According TO PRiority Grouping System In APINT Reg*/ // using BitField Access
	APINT.bits.VECTKEY = APINT_VECTKEY;
	APINT.bits.PRIGROUP = NVIC_PRIORITY_GROUPING;

	//APINT.REG = (APINT_VECTKEY << APINT_VECTKEY_SHIFT) | (NVIC_PRIORITY_GROUPING << APINT_PRIGROUP_SHIFT);

	/*Set Priority For Irq*/
	PRI_REG(IPRn) = (PRI_REG(IPRn) & ~(0xFF << (8 * IRQ_PriOffset))) | (totalPriority << (8 * IRQ_PriOffset));
}

void NVIC_SetPending(NVIC_IrqNumberType IRQ_Num)
{
	uint32 ISPn;
	uint32 IRQ_ISP_Offset;

	/*Get Offset Of ISPn Register Which Irq resident in */
	ISPn = IRQ_Num / 32;

	/*Get Offset Of IRQ_Num in ISPn Register */
	IRQ_ISP_Offset = IRQ_Num % 32;

	/*Force interrupts into the pending state*/
	IRQ_SET_PENDING(ISPn, IRQ_ISP_Offset);
}

void NVIC_ClearPending(NVIC_IrqNumberType IRQ_Num)
{
	uint32 ICPn;
	uint32 IRQ_ICP_Offset;

	/*Get Offset Of ICPn Register Which Irq resident in */
	ICPn = IRQ_Num / 32;

	/*Get Offset Of IRQ_Num in ICPn Register */
	IRQ_ICP_Offset = IRQ_Num % 32;

	/* remove the pending state from interrupts through ICPn reg*/
	IRQ_CLEAR_PENDING(ICPn, IRQ_ICP_Offset);
}

void NVIC_SetEnable(NVIC_IrqNumberType IRQ_Num)
{
	uint32 ISEn;		   /*ISEn Register Which Irq resident in*/
	uint32 IRQ_ISE_Offset; /*IRQ_Num in ISEn Register*/

	/*Get Offset Of ISEn Register Which Irq resident in */
	ISEn = IRQ_Num / 32;

	/*Get Offset Of IRQ_Num in ISEn Register */
	IRQ_ISE_Offset = IRQ_Num % 32;

	/*Enable Interrupt*/
	IRQ_SET_ENABLE(ISEn, IRQ_ISE_Offset);
}

void NVIC_SetDisable(NVIC_IrqNumberType IRQ_Num)
{
	uint32 ICEn;
	uint32 IRQ_DisOffset;

	ICEn = IRQ_Num / 32;
	IRQ_DisOffset = IRQ_Num % 32;

	IRQ_SET_PENDING(ICEn, IRQ_DisOffset);
}

void NVIC_SetPriority(NVIC_IrqNumberType IRQ_Num, uint8 groupPriority, uint8 subGroupPriority)
{
	uint32 IPRn;
	uint32 IRQ_PriOffset;
	uint8  priority;

	/*Get Offset Of IPRn Register Which Irq resident in */
	IPRn = IRQ_Num / NVIC_PRIORITY_FIELDS_PER_REG;

	/*Get Offset Of IRQ_Num in IPRn Register (INTA/INTB/INTC/INTD) */
	IRQ_PriOffset = IRQ_Num % NVIC_PRIORITY_FIELDS_PER_REG;

	/*Caclulate Total Priority For Irq*/
	groupPriority = NVIC_GROUP_PRIORITY_SHIFT << (groupPriority & NVIC_GROUP_PRIORITY_MASK);
	subGroupPriority = NVIC_SUBGROUP_PRIORITY_SHIFT << (subGroupPriority & NVIC_SUBGROUP_PRIORITY_MASK);

	priority = groupPriority | subGroupPriority;

	/*Set Irq Priority According TO PRiority Grouping System In APINT Reg*/
	APINT.REG = (APINT_VECTKEY << APINT_VECTKEY_SHIFT) | (NVIC_PRIORITY_GROUPING << APINT_PRIGROUP_SHIFT);

	/*Set Priority For Irq*/
	PRI_REG(IPRn) = (((PRI_REG(IPRn) & ~(0xF << (8 * IRQ_PriOffset)))) | (priority << (8 * IRQ_PriOffset)));
}