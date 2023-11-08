#ifndef EXTI_REG_H
#define EXTI_REG_H

#include "STD_TYPES.h"

#define AFIO_BASE (0x40010000)
#define EXTI_BASE (0x40010400)

#define AFIO	  ((AFIO_TypeDef*)AFIO_BASE)
#define EXTI	  ((EXTI_TypeDef*)EXTI_BASE)

typedef struct
{
	volatile uint32 EVCR;
	volatile uint32 MAPR;
	volatile uint32 EXTICR[4];
	volatile uint32 RESERVED0;
	volatile uint32 MAPR2;
} AFIO_TypeDef;

typedef struct
{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RTSR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;
} EXTI_TypeDef;

/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for EXTI_IMR register  *******************/
#define EXTI_IMR_MR0		   ((uint32)0x00000001) /*!< Interrupt Mask on line 0 */
#define EXTI_IMR_MR1		   ((uint32)0x00000002) /*!< Interrupt Mask on line 1 */
#define EXTI_IMR_MR2		   ((uint32)0x00000004) /*!< Interrupt Mask on line 2 */
#define EXTI_IMR_MR3		   ((uint32)0x00000008) /*!< Interrupt Mask on line 3 */
#define EXTI_IMR_MR4		   ((uint32)0x00000010) /*!< Interrupt Mask on line 4 */
#define EXTI_IMR_MR5		   ((uint32)0x00000020) /*!< Interrupt Mask on line 5 */
#define EXTI_IMR_MR6		   ((uint32)0x00000040) /*!< Interrupt Mask on line 6 */
#define EXTI_IMR_MR7		   ((uint32)0x00000080) /*!< Interrupt Mask on line 7 */
#define EXTI_IMR_MR8		   ((uint32)0x00000100) /*!< Interrupt Mask on line 8 */
#define EXTI_IMR_MR9		   ((uint32)0x00000200) /*!< Interrupt Mask on line 9 */
#define EXTI_IMR_MR10		   ((uint32)0x00000400) /*!< Interrupt Mask on line 10 */
#define EXTI_IMR_MR11		   ((uint32)0x00000800) /*!< Interrupt Mask on line 11 */
#define EXTI_IMR_MR12		   ((uint32)0x00001000) /*!< Interrupt Mask on line 12 */
#define EXTI_IMR_MR13		   ((uint32)0x00002000) /*!< Interrupt Mask on line 13 */
#define EXTI_IMR_MR14		   ((uint32)0x00004000) /*!< Interrupt Mask on line 14 */
#define EXTI_IMR_MR15		   ((uint32)0x00008000) /*!< Interrupt Mask on line 15 */
#define EXTI_IMR_MR16		   ((uint32)0x00010000) /*!< Interrupt Mask on line 16 */
#define EXTI_IMR_MR17		   ((uint32)0x00020000) /*!< Interrupt Mask on line 17 */
#define EXTI_IMR_MR18		   ((uint32)0x00040000) /*!< Interrupt Mask on line 18 */
#define EXTI_IMR_MR19		   ((uint32)0x00080000) /*!< Interrupt Mask on line 19 */

/*******************  Bit definition for EXTI_EMR register  *******************/
#define EXTI_EMR_MR0		   ((uint32)0x00000001) /*!< Event Mask on line 0 */
#define EXTI_EMR_MR1		   ((uint32)0x00000002) /*!< Event Mask on line 1 */
#define EXTI_EMR_MR2		   ((uint32)0x00000004) /*!< Event Mask on line 2 */
#define EXTI_EMR_MR3		   ((uint32)0x00000008) /*!< Event Mask on line 3 */
#define EXTI_EMR_MR4		   ((uint32)0x00000010) /*!< Event Mask on line 4 */
#define EXTI_EMR_MR5		   ((uint32)0x00000020) /*!< Event Mask on line 5 */
#define EXTI_EMR_MR6		   ((uint32)0x00000040) /*!< Event Mask on line 6 */
#define EXTI_EMR_MR7		   ((uint32)0x00000080) /*!< Event Mask on line 7 */
#define EXTI_EMR_MR8		   ((uint32)0x00000100) /*!< Event Mask on line 8 */
#define EXTI_EMR_MR9		   ((uint32)0x00000200) /*!< Event Mask on line 9 */
#define EXTI_EMR_MR10		   ((uint32)0x00000400) /*!< Event Mask on line 10 */
#define EXTI_EMR_MR11		   ((uint32)0x00000800) /*!< Event Mask on line 11 */
#define EXTI_EMR_MR12		   ((uint32)0x00001000) /*!< Event Mask on line 12 */
#define EXTI_EMR_MR13		   ((uint32)0x00002000) /*!< Event Mask on line 13 */
#define EXTI_EMR_MR14		   ((uint32)0x00004000) /*!< Event Mask on line 14 */
#define EXTI_EMR_MR15		   ((uint32)0x00008000) /*!< Event Mask on line 15 */
#define EXTI_EMR_MR16		   ((uint32)0x00010000) /*!< Event Mask on line 16 */
#define EXTI_EMR_MR17		   ((uint32)0x00020000) /*!< Event Mask on line 17 */
#define EXTI_EMR_MR18		   ((uint32)0x00040000) /*!< Event Mask on line 18 */
#define EXTI_EMR_MR19		   ((uint32)0x00080000) /*!< Event Mask on line 19 */

/******************  Bit definition for EXTI_RTSR register  *******************/
#define EXTI_RTSR_TR0		   ((uint32)0x00000001) /*!< Rising trigger event configuration bit of line 0 */
#define EXTI_RTSR_TR1		   ((uint32)0x00000002) /*!< Rising trigger event configuration bit of line 1 */
#define EXTI_RTSR_TR2		   ((uint32)0x00000004) /*!< Rising trigger event configuration bit of line 2 */
#define EXTI_RTSR_TR3		   ((uint32)0x00000008) /*!< Rising trigger event configuration bit of line 3 */
#define EXTI_RTSR_TR4		   ((uint32)0x00000010) /*!< Rising trigger event configuration bit of line 4 */
#define EXTI_RTSR_TR5		   ((uint32)0x00000020) /*!< Rising trigger event configuration bit of line 5 */
#define EXTI_RTSR_TR6		   ((uint32)0x00000040) /*!< Rising trigger event configuration bit of line 6 */
#define EXTI_RTSR_TR7		   ((uint32)0x00000080) /*!< Rising trigger event configuration bit of line 7 */
#define EXTI_RTSR_TR8		   ((uint32)0x00000100) /*!< Rising trigger event configuration bit of line 8 */
#define EXTI_RTSR_TR9		   ((uint32)0x00000200) /*!< Rising trigger event configuration bit of line 9 */
#define EXTI_RTSR_TR10		   ((uint32)0x00000400) /*!< Rising trigger event configuration bit of line 10 */
#define EXTI_RTSR_TR11		   ((uint32)0x00000800) /*!< Rising trigger event configuration bit of line 11 */
#define EXTI_RTSR_TR12		   ((uint32)0x00001000) /*!< Rising trigger event configuration bit of line 12 */
#define EXTI_RTSR_TR13		   ((uint32)0x00002000) /*!< Rising trigger event configuration bit of line 13 */
#define EXTI_RTSR_TR14		   ((uint32)0x00004000) /*!< Rising trigger event configuration bit of line 14 */
#define EXTI_RTSR_TR15		   ((uint32)0x00008000) /*!< Rising trigger event configuration bit of line 15 */
#define EXTI_RTSR_TR16		   ((uint32)0x00010000) /*!< Rising trigger event configuration bit of line 16 */
#define EXTI_RTSR_TR17		   ((uint32)0x00020000) /*!< Rising trigger event configuration bit of line 17 */
#define EXTI_RTSR_TR18		   ((uint32)0x00040000) /*!< Rising trigger event configuration bit of line 18 */
#define EXTI_RTSR_TR19		   ((uint32)0x00080000) /*!< Rising trigger event configuration bit of line 19 */

/******************  Bit definition for EXTI_FTSR register  *******************/
#define EXTI_FTSR_TR0		   ((uint32)0x00000001) /*!< Falling trigger event configuration bit of line 0 */
#define EXTI_FTSR_TR1		   ((uint32)0x00000002) /*!< Falling trigger event configuration bit of line 1 */
#define EXTI_FTSR_TR2		   ((uint32)0x00000004) /*!< Falling trigger event configuration bit of line 2 */
#define EXTI_FTSR_TR3		   ((uint32)0x00000008) /*!< Falling trigger event configuration bit of line 3 */
#define EXTI_FTSR_TR4		   ((uint32)0x00000010) /*!< Falling trigger event configuration bit of line 4 */
#define EXTI_FTSR_TR5		   ((uint32)0x00000020) /*!< Falling trigger event configuration bit of line 5 */
#define EXTI_FTSR_TR6		   ((uint32)0x00000040) /*!< Falling trigger event configuration bit of line 6 */
#define EXTI_FTSR_TR7		   ((uint32)0x00000080) /*!< Falling trigger event configuration bit of line 7 */
#define EXTI_FTSR_TR8		   ((uint32)0x00000100) /*!< Falling trigger event configuration bit of line 8 */
#define EXTI_FTSR_TR9		   ((uint32)0x00000200) /*!< Falling trigger event configuration bit of line 9 */
#define EXTI_FTSR_TR10		   ((uint32)0x00000400) /*!< Falling trigger event configuration bit of line 10 */
#define EXTI_FTSR_TR11		   ((uint32)0x00000800) /*!< Falling trigger event configuration bit of line 11 */
#define EXTI_FTSR_TR12		   ((uint32)0x00001000) /*!< Falling trigger event configuration bit of line 12 */
#define EXTI_FTSR_TR13		   ((uint32)0x00002000) /*!< Falling trigger event configuration bit of line 13 */
#define EXTI_FTSR_TR14		   ((uint32)0x00004000) /*!< Falling trigger event configuration bit of line 14 */
#define EXTI_FTSR_TR15		   ((uint32)0x00008000) /*!< Falling trigger event configuration bit of line 15 */
#define EXTI_FTSR_TR16		   ((uint32)0x00010000) /*!< Falling trigger event configuration bit of line 16 */
#define EXTI_FTSR_TR17		   ((uint32)0x00020000) /*!< Falling trigger event configuration bit of line 17 */
#define EXTI_FTSR_TR18		   ((uint32)0x00040000) /*!< Falling trigger event configuration bit of line 18 */
#define EXTI_FTSR_TR19		   ((uint32)0x00080000) /*!< Falling trigger event configuration bit of line 19 */

/******************  Bit definition for EXTI_SWIER register  ******************/
#define EXTI_SWIER_SWIER0	   ((uint32)0x00000001) /*!< Software Interrupt on line 0 */
#define EXTI_SWIER_SWIER1	   ((uint32)0x00000002) /*!< Software Interrupt on line 1 */
#define EXTI_SWIER_SWIER2	   ((uint32)0x00000004) /*!< Software Interrupt on line 2 */
#define EXTI_SWIER_SWIER3	   ((uint32)0x00000008) /*!< Software Interrupt on line 3 */
#define EXTI_SWIER_SWIER4	   ((uint32)0x00000010) /*!< Software Interrupt on line 4 */
#define EXTI_SWIER_SWIER5	   ((uint32)0x00000020) /*!< Software Interrupt on line 5 */
#define EXTI_SWIER_SWIER6	   ((uint32)0x00000040) /*!< Software Interrupt on line 6 */
#define EXTI_SWIER_SWIER7	   ((uint32)0x00000080) /*!< Software Interrupt on line 7 */
#define EXTI_SWIER_SWIER8	   ((uint32)0x00000100) /*!< Software Interrupt on line 8 */
#define EXTI_SWIER_SWIER9	   ((uint32)0x00000200) /*!< Software Interrupt on line 9 */
#define EXTI_SWIER_SWIER10	   ((uint32)0x00000400) /*!< Software Interrupt on line 10 */
#define EXTI_SWIER_SWIER11	   ((uint32)0x00000800) /*!< Software Interrupt on line 11 */
#define EXTI_SWIER_SWIER12	   ((uint32)0x00001000) /*!< Software Interrupt on line 12 */
#define EXTI_SWIER_SWIER13	   ((uint32)0x00002000) /*!< Software Interrupt on line 13 */
#define EXTI_SWIER_SWIER14	   ((uint32)0x00004000) /*!< Software Interrupt on line 14 */
#define EXTI_SWIER_SWIER15	   ((uint32)0x00008000) /*!< Software Interrupt on line 15 */
#define EXTI_SWIER_SWIER16	   ((uint32)0x00010000) /*!< Software Interrupt on line 16 */
#define EXTI_SWIER_SWIER17	   ((uint32)0x00020000) /*!< Software Interrupt on line 17 */
#define EXTI_SWIER_SWIER18	   ((uint32)0x00040000) /*!< Software Interrupt on line 18 */
#define EXTI_SWIER_SWIER19	   ((uint32)0x00080000) /*!< Software Interrupt on line 19 */

/*******************  Bit definition for EXTI_PR register  ********************/
#define EXTI_PR_PR0			   ((uint32)0x00000001) /*!< Pending bit for line 0 */
#define EXTI_PR_PR1			   ((uint32)0x00000002) /*!< Pending bit for line 1 */
#define EXTI_PR_PR2			   ((uint32)0x00000004) /*!< Pending bit for line 2 */
#define EXTI_PR_PR3			   ((uint32)0x00000008) /*!< Pending bit for line 3 */
#define EXTI_PR_PR4			   ((uint32)0x00000010) /*!< Pending bit for line 4 */
#define EXTI_PR_PR5			   ((uint32)0x00000020) /*!< Pending bit for line 5 */
#define EXTI_PR_PR6			   ((uint32)0x00000040) /*!< Pending bit for line 6 */
#define EXTI_PR_PR7			   ((uint32)0x00000080) /*!< Pending bit for line 7 */
#define EXTI_PR_PR8			   ((uint32)0x00000100) /*!< Pending bit for line 8 */
#define EXTI_PR_PR9			   ((uint32)0x00000200) /*!< Pending bit for line 9 */
#define EXTI_PR_PR10		   ((uint32)0x00000400) /*!< Pending bit for line 10 */
#define EXTI_PR_PR11		   ((uint32)0x00000800) /*!< Pending bit for line 11 */
#define EXTI_PR_PR12		   ((uint32)0x00001000) /*!< Pending bit for line 12 */
#define EXTI_PR_PR13		   ((uint32)0x00002000) /*!< Pending bit for line 13 */
#define EXTI_PR_PR14		   ((uint32)0x00004000) /*!< Pending bit for line 14 */
#define EXTI_PR_PR15		   ((uint32)0x00008000) /*!< Pending bit for line 15 */
#define EXTI_PR_PR16		   ((uint32)0x00010000) /*!< Pending bit for line 16 */
#define EXTI_PR_PR17		   ((uint32)0x00020000) /*!< Pending bit for line 17 */
#define EXTI_PR_PR18		   ((uint32)0x00040000) /*!< Pending bit for line 18 */
#define EXTI_PR_PR19		   ((uint32)0x00080000) /*!< Pending bit for line 19 */

/*****************  Bit definition for AFIO_EXTICR1 register  *****************/
#define AFIO_EXTICR1_EXTI0	   ((uint16)0x000F) /*!< EXTI 0 configuration */
#define AFIO_EXTICR1_EXTI1	   ((uint16)0x00F0) /*!< EXTI 1 configuration */
#define AFIO_EXTICR1_EXTI2	   ((uint16)0x0F00) /*!< EXTI 2 configuration */
#define AFIO_EXTICR1_EXTI3	   ((uint16)0xF000) /*!< EXTI 3 configuration */

/*!< EXTI0 configuration */
#define AFIO_EXTICR1_EXTI0_PA  ((uint16)0x0000) /*!< PA[0] pin */
#define AFIO_EXTICR1_EXTI0_PB  ((uint16)0x0001) /*!< PB[0] pin */
#define AFIO_EXTICR1_EXTI0_PC  ((uint16)0x0002) /*!< PC[0] pin */
#define AFIO_EXTICR1_EXTI0_PD  ((uint16)0x0003) /*!< PD[0] pin */
#define AFIO_EXTICR1_EXTI0_PE  ((uint16)0x0004) /*!< PE[0] pin */
#define AFIO_EXTICR1_EXTI0_PF  ((uint16)0x0005) /*!< PF[0] pin */
#define AFIO_EXTICR1_EXTI0_PG  ((uint16)0x0006) /*!< PG[0] pin */

/*!< EXTI1 configuration */
#define AFIO_EXTICR1_EXTI1_PA  ((uint16)0x0000) /*!< PA[1] pin */
#define AFIO_EXTICR1_EXTI1_PB  ((uint16)0x0010) /*!< PB[1] pin */
#define AFIO_EXTICR1_EXTI1_PC  ((uint16)0x0020) /*!< PC[1] pin */
#define AFIO_EXTICR1_EXTI1_PD  ((uint16)0x0030) /*!< PD[1] pin */
#define AFIO_EXTICR1_EXTI1_PE  ((uint16)0x0040) /*!< PE[1] pin */
#define AFIO_EXTICR1_EXTI1_PF  ((uint16)0x0050) /*!< PF[1] pin */
#define AFIO_EXTICR1_EXTI1_PG  ((uint16)0x0060) /*!< PG[1] pin */

/*!< EXTI2 configuration */
#define AFIO_EXTICR1_EXTI2_PA  ((uint16)0x0000) /*!< PA[2] pin */
#define AFIO_EXTICR1_EXTI2_PB  ((uint16)0x0100) /*!< PB[2] pin */
#define AFIO_EXTICR1_EXTI2_PC  ((uint16)0x0200) /*!< PC[2] pin */
#define AFIO_EXTICR1_EXTI2_PD  ((uint16)0x0300) /*!< PD[2] pin */
#define AFIO_EXTICR1_EXTI2_PE  ((uint16)0x0400) /*!< PE[2] pin */
#define AFIO_EXTICR1_EXTI2_PF  ((uint16)0x0500) /*!< PF[2] pin */
#define AFIO_EXTICR1_EXTI2_PG  ((uint16)0x0600) /*!< PG[2] pin */

/*!< EXTI3 configuration */
#define AFIO_EXTICR1_EXTI3_PA  ((uint16)0x0000) /*!< PA[3] pin */
#define AFIO_EXTICR1_EXTI3_PB  ((uint16)0x1000) /*!< PB[3] pin */
#define AFIO_EXTICR1_EXTI3_PC  ((uint16)0x2000) /*!< PC[3] pin */
#define AFIO_EXTICR1_EXTI3_PD  ((uint16)0x3000) /*!< PD[3] pin */
#define AFIO_EXTICR1_EXTI3_PE  ((uint16)0x4000) /*!< PE[3] pin */
#define AFIO_EXTICR1_EXTI3_PF  ((uint16)0x5000) /*!< PF[3] pin */
#define AFIO_EXTICR1_EXTI3_PG  ((uint16)0x6000) /*!< PG[3] pin */

/*****************  Bit definition for AFIO_EXTICR2 register  *****************/
#define AFIO_EXTICR2_EXTI4	   ((uint16)0x000F) /*!< EXTI 4 configuration */
#define AFIO_EXTICR2_EXTI5	   ((uint16)0x00F0) /*!< EXTI 5 configuration */
#define AFIO_EXTICR2_EXTI6	   ((uint16)0x0F00) /*!< EXTI 6 configuration */
#define AFIO_EXTICR2_EXTI7	   ((uint16)0xF000) /*!< EXTI 7 configuration */

/*!< EXTI4 configuration */
#define AFIO_EXTICR2_EXTI4_PA  ((uint16)0x0000) /*!< PA[4] pin */
#define AFIO_EXTICR2_EXTI4_PB  ((uint16)0x0001) /*!< PB[4] pin */
#define AFIO_EXTICR2_EXTI4_PC  ((uint16)0x0002) /*!< PC[4] pin */
#define AFIO_EXTICR2_EXTI4_PD  ((uint16)0x0003) /*!< PD[4] pin */
#define AFIO_EXTICR2_EXTI4_PE  ((uint16)0x0004) /*!< PE[4] pin */
#define AFIO_EXTICR2_EXTI4_PF  ((uint16)0x0005) /*!< PF[4] pin */
#define AFIO_EXTICR2_EXTI4_PG  ((uint16)0x0006) /*!< PG[4] pin */

/* EXTI5 configuration */
#define AFIO_EXTICR2_EXTI5_PA  ((uint16)0x0000) /*!< PA[5] pin */
#define AFIO_EXTICR2_EXTI5_PB  ((uint16)0x0010) /*!< PB[5] pin */
#define AFIO_EXTICR2_EXTI5_PC  ((uint16)0x0020) /*!< PC[5] pin */
#define AFIO_EXTICR2_EXTI5_PD  ((uint16)0x0030) /*!< PD[5] pin */
#define AFIO_EXTICR2_EXTI5_PE  ((uint16)0x0040) /*!< PE[5] pin */
#define AFIO_EXTICR2_EXTI5_PF  ((uint16)0x0050) /*!< PF[5] pin */
#define AFIO_EXTICR2_EXTI5_PG  ((uint16)0x0060) /*!< PG[5] pin */

/*!< EXTI6 configuration */
#define AFIO_EXTICR2_EXTI6_PA  ((uint16)0x0000) /*!< PA[6] pin */
#define AFIO_EXTICR2_EXTI6_PB  ((uint16)0x0100) /*!< PB[6] pin */
#define AFIO_EXTICR2_EXTI6_PC  ((uint16)0x0200) /*!< PC[6] pin */
#define AFIO_EXTICR2_EXTI6_PD  ((uint16)0x0300) /*!< PD[6] pin */
#define AFIO_EXTICR2_EXTI6_PE  ((uint16)0x0400) /*!< PE[6] pin */
#define AFIO_EXTICR2_EXTI6_PF  ((uint16)0x0500) /*!< PF[6] pin */
#define AFIO_EXTICR2_EXTI6_PG  ((uint16)0x0600) /*!< PG[6] pin */

/*!< EXTI7 configuration */
#define AFIO_EXTICR2_EXTI7_PA  ((uint16)0x0000) /*!< PA[7] pin */
#define AFIO_EXTICR2_EXTI7_PB  ((uint16)0x1000) /*!< PB[7] pin */
#define AFIO_EXTICR2_EXTI7_PC  ((uint16)0x2000) /*!< PC[7] pin */
#define AFIO_EXTICR2_EXTI7_PD  ((uint16)0x3000) /*!< PD[7] pin */
#define AFIO_EXTICR2_EXTI7_PE  ((uint16)0x4000) /*!< PE[7] pin */
#define AFIO_EXTICR2_EXTI7_PF  ((uint16)0x5000) /*!< PF[7] pin */
#define AFIO_EXTICR2_EXTI7_PG  ((uint16)0x6000) /*!< PG[7] pin */

/*****************  Bit definition for AFIO_EXTICR3 register  *****************/
#define AFIO_EXTICR3_EXTI8	   ((uint16)0x000F) /*!< EXTI 8 configuration */
#define AFIO_EXTICR3_EXTI9	   ((uint16)0x00F0) /*!< EXTI 9 configuration */
#define AFIO_EXTICR3_EXTI10	   ((uint16)0x0F00) /*!< EXTI 10 configuration */
#define AFIO_EXTICR3_EXTI11	   ((uint16)0xF000) /*!< EXTI 11 configuration */

/*!< EXTI8 configuration */
#define AFIO_EXTICR3_EXTI8_PA  ((uint16)0x0000) /*!< PA[8] pin */
#define AFIO_EXTICR3_EXTI8_PB  ((uint16)0x0001) /*!< PB[8] pin */
#define AFIO_EXTICR3_EXTI8_PC  ((uint16)0x0002) /*!< PC[8] pin */
#define AFIO_EXTICR3_EXTI8_PD  ((uint16)0x0003) /*!< PD[8] pin */
#define AFIO_EXTICR3_EXTI8_PE  ((uint16)0x0004) /*!< PE[8] pin */
#define AFIO_EXTICR3_EXTI8_PF  ((uint16)0x0005) /*!< PF[8] pin */
#define AFIO_EXTICR3_EXTI8_PG  ((uint16)0x0006) /*!< PG[8] pin */

/*!< EXTI9 configuration */
#define AFIO_EXTICR3_EXTI9_PA  ((uint16)0x0000) /*!< PA[9] pin */
#define AFIO_EXTICR3_EXTI9_PB  ((uint16)0x0010) /*!< PB[9] pin */
#define AFIO_EXTICR3_EXTI9_PC  ((uint16)0x0020) /*!< PC[9] pin */
#define AFIO_EXTICR3_EXTI9_PD  ((uint16)0x0030) /*!< PD[9] pin */
#define AFIO_EXTICR3_EXTI9_PE  ((uint16)0x0040) /*!< PE[9] pin */
#define AFIO_EXTICR3_EXTI9_PF  ((uint16)0x0050) /*!< PF[9] pin */
#define AFIO_EXTICR3_EXTI9_PG  ((uint16)0x0060) /*!< PG[9] pin */

/*!< EXTI10 configuration */
#define AFIO_EXTICR3_EXTI10_PA ((uint16)0x0000) /*!< PA[10] pin */
#define AFIO_EXTICR3_EXTI10_PB ((uint16)0x0100) /*!< PB[10] pin */
#define AFIO_EXTICR3_EXTI10_PC ((uint16)0x0200) /*!< PC[10] pin */
#define AFIO_EXTICR3_EXTI10_PD ((uint16)0x0300) /*!< PD[10] pin */
#define AFIO_EXTICR3_EXTI10_PE ((uint16)0x0400) /*!< PE[10] pin */
#define AFIO_EXTICR3_EXTI10_PF ((uint16)0x0500) /*!< PF[10] pin */
#define AFIO_EXTICR3_EXTI10_PG ((uint16)0x0600) /*!< PG[10] pin */

/*!< EXTI11 configuration */
#define AFIO_EXTICR3_EXTI11_PA ((uint16)0x0000) /*!< PA[11] pin */
#define AFIO_EXTICR3_EXTI11_PB ((uint16)0x1000) /*!< PB[11] pin */
#define AFIO_EXTICR3_EXTI11_PC ((uint16)0x2000) /*!< PC[11] pin */
#define AFIO_EXTICR3_EXTI11_PD ((uint16)0x3000) /*!< PD[11] pin */
#define AFIO_EXTICR3_EXTI11_PE ((uint16)0x4000) /*!< PE[11] pin */
#define AFIO_EXTICR3_EXTI11_PF ((uint16)0x5000) /*!< PF[11] pin */
#define AFIO_EXTICR3_EXTI11_PG ((uint16)0x6000) /*!< PG[11] pin */

/*****************  Bit definition for AFIO_EXTICR4 register  *****************/
#define AFIO_EXTICR4_EXTI12	   ((uint16)0x000F) /*!< EXTI 12 configuration */
#define AFIO_EXTICR4_EXTI13	   ((uint16)0x00F0) /*!< EXTI 13 configuration */
#define AFIO_EXTICR4_EXTI14	   ((uint16)0x0F00) /*!< EXTI 14 configuration */
#define AFIO_EXTICR4_EXTI15	   ((uint16)0xF000) /*!< EXTI 15 configuration */

/* EXTI12 configuration */
#define AFIO_EXTICR4_EXTI12_PA ((uint16)0x0000) /*!< PA[12] pin */
#define AFIO_EXTICR4_EXTI12_PB ((uint16)0x0001) /*!< PB[12] pin */
#define AFIO_EXTICR4_EXTI12_PC ((uint16)0x0002) /*!< PC[12] pin */
#define AFIO_EXTICR4_EXTI12_PD ((uint16)0x0003) /*!< PD[12] pin */
#define AFIO_EXTICR4_EXTI12_PE ((uint16)0x0004) /*!< PE[12] pin */
#define AFIO_EXTICR4_EXTI12_PF ((uint16)0x0005) /*!< PF[12] pin */
#define AFIO_EXTICR4_EXTI12_PG ((uint16)0x0006) /*!< PG[12] pin */

/* EXTI13 configuration */
#define AFIO_EXTICR4_EXTI13_PA ((uint16)0x0000) /*!< PA[13] pin */
#define AFIO_EXTICR4_EXTI13_PB ((uint16)0x0010) /*!< PB[13] pin */
#define AFIO_EXTICR4_EXTI13_PC ((uint16)0x0020) /*!< PC[13] pin */
#define AFIO_EXTICR4_EXTI13_PD ((uint16)0x0030) /*!< PD[13] pin */
#define AFIO_EXTICR4_EXTI13_PE ((uint16)0x0040) /*!< PE[13] pin */
#define AFIO_EXTICR4_EXTI13_PF ((uint16)0x0050) /*!< PF[13] pin */
#define AFIO_EXTICR4_EXTI13_PG ((uint16)0x0060) /*!< PG[13] pin */

/*!< EXTI14 configuration */
#define AFIO_EXTICR4_EXTI14_PA ((uint16)0x0000) /*!< PA[14] pin */
#define AFIO_EXTICR4_EXTI14_PB ((uint16)0x0100) /*!< PB[14] pin */
#define AFIO_EXTICR4_EXTI14_PC ((uint16)0x0200) /*!< PC[14] pin */
#define AFIO_EXTICR4_EXTI14_PD ((uint16)0x0300) /*!< PD[14] pin */
#define AFIO_EXTICR4_EXTI14_PE ((uint16)0x0400) /*!< PE[14] pin */
#define AFIO_EXTICR4_EXTI14_PF ((uint16)0x0500) /*!< PF[14] pin */
#define AFIO_EXTICR4_EXTI14_PG ((uint16)0x0600) /*!< PG[14] pin */

/*!< EXTI15 configuration */
#define AFIO_EXTICR4_EXTI15_PA ((uint16)0x0000) /*!< PA[15] pin */
#define AFIO_EXTICR4_EXTI15_PB ((uint16)0x1000) /*!< PB[15] pin */
#define AFIO_EXTICR4_EXTI15_PC ((uint16)0x2000) /*!< PC[15] pin */
#define AFIO_EXTICR4_EXTI15_PD ((uint16)0x3000) /*!< PD[15] pin */
#define AFIO_EXTICR4_EXTI15_PE ((uint16)0x4000) /*!< PE[15] pin */
#define AFIO_EXTICR4_EXTI15_PF ((uint16)0x5000) /*!< PF[15] pin */
#define AFIO_EXTICR4_EXTI15_PG ((uint16)0x6000) /*!< PG[15] pin */

#endif // EXTI_REG_H