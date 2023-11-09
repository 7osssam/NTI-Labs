#ifndef DMA_H_
#define DMA_H_

#include "STD_TYPES.h"

typedef enum
{
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7
} DMA_ChannelType;

typedef enum
{
	READ_FROM_PERIPHERAL,
	READ_FROM_MEMORY
} DMA_DirectionType;

typedef enum
{
	LOW,
	MEDIUM,
	HIGH,
	VERY_HIGH
} DMA_PriorityType;

typedef enum
{
	BYTE,	   // 8 bits
	HALF_WORD, // 16 bits
	WORD	   // 32 bits
} DMA_sizeType;

typedef struct
{
	DMA_ChannelType	  Channel;
	DMA_PriorityType  Priority;
	DMA_sizeType	  MemSize;
	DMA_sizeType	  PerSize;
	DMA_DirectionType Dir;
} DMA_ConfigType;

void DMA_init(DMA_ConfigType* Config_Ptr);
void DMA_enable(uint8 Channel);
void DMA_disable(uint8 Channel);
void DMA_setMemoryAddress(uint8 Channel, uint32* Address);
void DMA_setPeripheralAddress(uint8 Channel, uint32* Address);
void DMA_setNumberOfData(uint8 Channel, uint16 NumberOfData);
void DMA_clearInterruptFlag(uint8 Channel);
void DMA_channelStart(uint8 Channel, uint32* SourceAddress, uint32* DestinationAddress, uint16 NumberOfData);
#endif /* DMA_H_ */