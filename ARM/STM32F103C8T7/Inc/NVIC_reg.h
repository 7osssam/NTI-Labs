#ifndef NVIC_MAP_H
#define NVIC_MAP_H

#include "BIT_MACROS.h"
#include "STD_TYPES.h"

/* Core Peripheral Base Address */
#define NVIC_BASE_ADDRESS					0xE000E100

/* Nested Vectored Interrupt Controller (NVIC) Registers offset */
/* Interrupt set-enable registers */
#define ISE0_OFFSET							0x000

/* Interrupt clear-enable registers */
#define ICE0_OFFSET							0x080

/* Interrupt set-pending registers */
#define ISP0_OFFSET							0x100

/* Interrupt clear-pending registers */
#define ICP0_OFFSET							0x180

/* Interrupt active bit registers */
#define IAB0_OFFSET							0x200

/* Interrupt priority registers */
#define IPR0_OFFSET							0x300

/* Software trigger interrupt register */
#define STI_BASE_ADDRESS					0xE000EF00 // TODO: Check later
/* Software trigger interrupt register offset */
#define STI_OFFSET							0xE00 // TODO: Check later

/* System Control (SCB) Registers offset */
#define ACTLR_OFFSET						0x008
#define CPUID_OFFSET						0xD00
#define INTCTRL_OFFSET						0xD04
#define VTABLE_OFFSET						0xD08
#define APINT_OFFSET						0xD0C
#define SYSCTRL_OFFSET						0xD10
#define CFGCTRL_OFFSET						0xD14
#define SYSPRI1_OFFSET						0xD18
#define SYSPRI2_OFFSET						0xD1C
#define SYSPRI3_OFFSET						0xD20
#define SYSHNDCTRL_OFFSET					0xD24
#define FAULTSTAT_OFFSET					0xD28
#define HFAULTSTAT_OFFSET					0xD2C
#define MMADDR_OFFSET						0xD34
#define FAULTADDR_OFFSET					0xD38

/* Nested Vectored Interrupt Controller (NVIC) Registers Structure */

/*Preprocessor Macro To Enable interrupts and show which interrupts Through ISEn Reg*/
#define ENABLE_REG(ISEn)					(*((volatile uint32*)(NVIC_BASE_ADDRESS + ISE0_OFFSET + ISEn)))
#define IRQ_SET_ENABLE(ISEn, IRQ_BIT)		(SET_BIT(ENABLE_REG(ISEn), IRQ_BIT))

// for example:
//  0xE000E100 + 0x000 + 7 = 0xE000E107

/*Preprocessor Macro To Disable interrupts Through ICEn Reg*/
#define DISABLE_REG(ICEn)					(*((volatile uint32*)(NVIC_BASE_ADDRESS + ICE0_OFFSET + ICEn)))
#define IRQ_SET_DISABLE(ICEn, IRQ_BIT)		(SET_BIT(DISABLE_REG(DISn), IRQ_BIT))

/*Preprocessor Macro To Set the pending state of interrupts through PENDn reg*/
#define PEND_REG(PENDn)						(*((volatile uint32*)(NVIC_BASE_ADDRESS + ISP0_OFFSET + PENDn)))
#define IRQ_SET_PENDING(PENDn, IRQ_BIT)		(SET_BIT(PEND_REG(PENDn), IRQ_BIT))

/*Preprocessor Macro To Clear the pending state of interrupts through UNPENDn reg*/
#define UNPEND_REG(UNPENDn)					(*((volatile uint32*)(NVIC_BASE_ADDRESS + ICP0_OFFSET + UNPENDn)))
#define IRQ_CLEAR_PENDING(UNPENDn, IRQ_BIT) (SET_BIT(UNPEND_REG(UNPENDn), IRQ_BIT))

/*Preprocessor Macro To Trigger interrupts By Software*/
#define STI_REG								(*((volatile uint16*)(STI_BASE_ADDRESS + STI_OFFSET)))
#define IRQ_TRIGGER(IRQ_ID)					(SWTRIG_REG = IRQ_ID)

/*Preprocessor Macro  To Acess IPRn Reg*/
#define PRI_REG(IPRn)						(*((volatile uint8*)(NVIC_BASE_ADDRESS + IPR0_OFFSET + IPRn)))

// 0xE000E100 + 0x300 + 7 = 0xE000E407

#define IP0_MASK							0x000000FF
#define IP1_MASK							0x0000FF00
#define IP2_MASK							0x00FF0000
#define IP3_MASK							0xFF000000

#define IP0_SHIFT							0
#define IP1_SHIFT							8
#define IP2_SHIFT							16
#define IP3_SHIFT							24

/* System Control (SCB) Registers */
#define APINT_VECTKEY						0x05FA // Vector key
typedef union
{
	uint32 REG;
	struct
	{
		uint32 VECTRESET  : 1;
		uint32 VECTCLRACT : 1;
		uint32 SYSRESREQ  : 1;
		uint32			  : 5;
		uint32 PRIGROUP	  : 3;
		uint32			  : 4;
		uint32 ENDIANESS  : 1;
		uint32 VECTKEY	  : 16;
	} bits;
} APINT_REG_t;

#define APINT_VECTKEY_SHIFT	 16
#define APINT_PRIGROUP_SHIFT 8

#define APINT				 (*((volatile APINT_REG_t*)(NVIC_BASE_ADDRESS + APINT_OFFSET)))

#endif // NVIC_MAP_H