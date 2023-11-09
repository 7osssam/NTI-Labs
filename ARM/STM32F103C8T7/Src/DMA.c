#include "DMA.h"
#include "BIT_MACROS.h"
#include "DMA_config.h"
#include "DMA_reg.h"

// PRIORITY_MASK - Bits 13:12
#define PRIORITY_MASK	 0xFFFFE7FF
// PSIZE_MASK -  Bits 9:8
#define PSIZE_MASK		 0xFFFFFCFF
// MSIZE_MASK - Bits 11:10
#define MSIZE_MASK		 0xFFFFF9FF

#define DMA_CCR(channel) DMA1->DMA_Channel[channel].DMA_CCR

void DMA_init(DMA_ConfigType* Config_Ptr)
{
	uint32 DMA_CCR_Value = 0;

	/* Memory to memory mode */
#if DMA_MEMORY_TO_MEMORY == TRUE
	SET_BIT(DMA_CCR_Value, MEM2MEM);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), MEM2MEM);
#endif // DMA_MEMORY_TO_MEMORY

	/* Set priority */
	DMA_CCR_Value = (DMA_CCR_Value & PRIORITY_MASK) | (Config_Ptr->Priority << PL);

	/* Set memory size */
	DMA_CCR_Value = (DMA_CCR_Value & MSIZE_MASK) | (Config_Ptr->MemSize << MSIZE);

	/* Set peripheral size */
	DMA_CCR_Value = (DMA_CCR_Value & PSIZE_MASK) | (Config_Ptr->PerSize << PSIZE);

	/* Set memory increment */
#if DMA_MEMORY_INCREMENT == TRUE
	SET_BIT(DMA_CCR_Value, MINC);
#else
	CLEAR_BIT(DMA_CCR_Value, MINC);
#endif // DMA_MEMORY_INCREMENT

	/* Set peripheral increment */
#if DMA_PERIPHERAL_INCREMENT == TRUE
	SET_BIT(DMA_CCR_Value, PINC);
#else
	CLEAR_BIT(DMA_CCR_Value, PINC);
#endif // DMA_PERIPHERAL_INCREMENT

	/* Set circular mode */
#if DMA_CIRCULAR_MODE == TRUE
	SET_BIT(DMA_CCR_Value, CIRC);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), CIRC);
#endif // DMA_CIRCULAR_MODE

	/* Set direction */
	if (Config_Ptr->Dir == READ_FROM_MEMORY)
	{
		SET_BIT(DMA_CCR_Value, DIR);
	}
	else if (Config_Ptr->Dir == READ_FROM_PERIPHERAL)
	{
		CLEAR_BIT(DMA_CCR_Value, DIR);
	}
	else
	{
		/* Do nothing */
	}

	/* Set transfer complete interrupt */
#if DMA_TRANSFER_COMPLETE_INT == TRUE
	SET_BIT(DMA_CCR_Value, TCIE);
#else
	CLEAR_BIT(DMA_CCR_Value, TCIE);
#endif // DMA_TRANSFER_COMPLETE_INT

	/* Set half transfer interrupt */
#if DMA_HALF_TRANSFER_INT == TRUE
	SET_BIT(DMA_CCR_Value, HTIE);
#else
	CLEAR_BIT(DMA_CCR_Value, HTIE);
#endif // DMA_HALF_TRANSFER_INT

	/* Set transfer error interrupt */
#if DMA_TRANSFER_ERROR_INT == TRUE
	SET_BIT(DMA_CCR_Value, TEIE);
#else
	CLEAR_BIT(DMA_CCR_Value, TEIE);
#endif // DMA_TRANSFER_ERROR_INT

	/* Disable DMA */
	CLEAR_BIT(DMA_CCR_Value, EN);

	/* Set CCR */
	DMA_CCR(Config_Ptr->Channel) = DMA_CCR_Value;
}

void DMA_enable(uint8 Channel)
{
	SET_BIT(DMA_CCR(Channel), EN);
}

void DMA_disable(uint8 Channel)
{
	CLEAR_BIT(DMA_CCR(Channel), EN);
}

void DMA_setMemoryAddress(uint8 Channel, uint32* Address)
{
	DMA1->DMA_Channel[Channel].DMA_CMAR = Address;
}

void DMA_setPeripheralAddress(uint8 Channel, uint32* Address)
{
	DMA1->DMA_Channel[Channel].DMA_CPAR = Address;
}

void DMA_setNumberOfData(uint8 Channel, uint16 NumberOfData)
{
	DMA1->DMA_Channel[Channel].DMA_CNDTR = NumberOfData;
}

void DMA_clearInterruptFlag(uint8 Channel)
{
	SET_BIT(DMA1->DMA_IFCR, Channel);
}

void DMA_channelStart(uint8 Channel, uint32* SourceAddress, uint32* DestinationAddress, uint16 NumberOfData)
{
	DMA_setPeripheralAddress(Channel, SourceAddress);
	DMA_setMemoryAddress(Channel, DestinationAddress);
	DMA_setNumberOfData(Channel, NumberOfData);
	DMA_enable(Channel);
}
