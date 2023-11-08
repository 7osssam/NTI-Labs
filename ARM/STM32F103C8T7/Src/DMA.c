#include "DMA.h"
#include "BIT_MACROS.h"
#include "DMA_config.h"
#include "DMA_reg.h"

#define PRIORITY_MASK	 0xFFFF1FFF
#define PSIZE_MASK		 0xFFFFFCFF
#define MSIZE_MASK		 0xFFFFF3FF

#define DMA_CCR(channel) DMA1->DMA_Channel[channel].DMA_CCR

void DMA_init(DMA_ConfigType* Config_Ptr)
{
	/* Set priority */
	DMA_CCR(Config_Ptr->Channel) =
		(DMA_CCR(Config_Ptr->Channel) & PRIORITY_MASK) | (Config_Ptr->Priority << PL);

	/* Set memory size */
	DMA_CCR(Config_Ptr->Channel) =
		(DMA_CCR(Config_Ptr->Channel) & MSIZE_MASK) | (Config_Ptr->MemSize << MSIZE);

	/* Set peripheral size */
	DMA_CCR(Config_Ptr->Channel) =
		(DMA_CCR(Config_Ptr->Channel) & PSIZE_MASK) | (Config_Ptr->PerSize << PSIZE);

/* Set memory increment */
#if DMA_MEMORY_INCREMENT == ENABLE
	SET_BIT(DMA_CCR(Config_Ptr->Channel), MINC);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), MINC);
#endif // DMA_MEMORY_INCREMENT

	/* Set peripheral increment */
#if DMA_PERIPHERAL_INCREMENT == ENABLE
	SET_BIT(DMA_CCR(Config_Ptr->Channel), PINC);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), PINC);
#endif // DMA_PERIPHERAL_INCREMENT

	/* Set circular mode */
#if DMA_CIRCULAR_MODE == ENABLE
	SET_BIT(DMA_CCR(Config_Ptr->Channel), CIRC);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), CIRC);
#endif // DMA_CIRCULAR_MODE

	/* Set direction */
	if (Config_Ptr->Dir == READ_FROM_MEMORY)
	{
		SET_BIT(DMA_CCR(Config_Ptr->Channel), DIR);
	}
	else
	{
		CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), DIR);
	}

/* Set transfer complete interrupt */
#if DMA_TRANSFER_COMPLETE_INT == ENABLE
	SET_BIT(DMA_CCR(Config_Ptr->Channel), TCIE);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), TCIE);
#endif // DMA_TRANSFER_COMPLETE_INT

	/* Set half transfer interrupt */
#if DMA_HALF_TRANSFER_INT == ENABLE
	SET_BIT(DMA_CCR(Config_Ptr->Channel), HTIE);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), HTIE);
#endif // DMA_HALF_TRANSFER_INT

	/* Set transfer error interrupt */
#if DMA_TRANSFER_ERROR_INT == ENABLE
	SET_BIT(DMA_CCR(Config_Ptr->Channel), TEIE);
#else
	CLEAR_BIT(DMA_CCR(Config_Ptr->Channel), TEIE);
#endif // DMA_TRANSFER_ERROR_INT

	/* Disable DMA */
	DMA_disable(Config_Ptr->Channel);
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
	DMA_setMemoryAddress(Channel, SourceAddress);
	DMA_setPeripheralAddress(Channel, DestinationAddress);
	DMA_setNumberOfData(Channel, NumberOfData);
	DMA_enable(Channel);
}
