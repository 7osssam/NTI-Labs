#ifndef DMA_REG_H
#define DMA_REG_H

#include "STD_TYPES.h"
#include "DMA_config.h"

#define DMA_NUM_OF_CHANNELS 7

#define DMA1_BASE_ADDRESS	0x40020000

typedef struct
{
	uint32 DMA_CCR;		 // DMA channel x configuration register (RW)
	uint32 DMA_CNDTR;	 // DMA channel x number of data register (RW)
	uint32 DMA_CPAR;	 // DMA channel x peripheral address register (RW)
	uint32 DMA_CMAR;	 // DMA channel x memory address register (RW)
	uint32 DMA_RESERVED; // DMA channel x reserved (RW)
} DMA_Channel_Reg;

typedef struct
{
	uint32 DMA_ISR;	 // DMA interrupt status register (RO)
	uint32 DMA_IFCR; // DMA interrupt flag clear register (WO)

	DMA_Channel_Reg DMA_Channel[DMA_NUM_OF_CHANNELS];

} DMA_Reg;

#define DMA1	((volatile DMA_Reg*)(DMA1_BASE_ADDRESS))

#define EN		0
#define TCIE	1
#define HTIE	2
#define TEIE	3
#define DIR		4
#define CIRC	5
#define PINC	6
#define MINC	7
#define PSIZE	8
#define MSIZE	10
#define PL		12
#define MEM2MEM 14

#endif // DMA_REG_H