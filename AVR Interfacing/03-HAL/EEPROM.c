/******************************************************************
 * @Module   	: External EEPROM 
 * @Title 	 	: External EEPROM Source File 
 * @Filename 	: EEPROM.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: 
 ********************************************************************/

#include "EEPROM.h"

#include "TWI.h"

#define A0_A1_A2_BITS_FROM_ADDRESS(address) ((address & 0x0700) >> 7)

void EEPROM_init(void)
{
	/* set the configuration of the TWI module inside the MC */
	TWI_configType TWI_EEPROM_Config = {.SCL_Frq = FastMode_400Kb,
										.prescaler = TWI_Prescaler_1,
										.generalCallRecognitionMode = TWI_GeneralCallRecognitionEnable_ON,
										.TWI_slaveAddress = EEPROM_SLAVE_ADDRESS};

	/* just initialize the I2C(TWI) module inside the MC */
	TWI_init(&TWI_EEPROM_Config);
}

TWI_STATUS_t EEPROM_writeByte(uint16 u16address, uint8 u8data)
{
	/* Send the Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return TWI_START;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(EEPROM_DEVICE_ADDRESS | A0_A1_A2_BITS_FROM_ADDRESS(u16address) | WRITEMODE));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return TWI_MT_SLA_W_ACK;

	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16address));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_MT_DATA_ACK;

	/* write byte to eeprom */
	TWI_writeByte(u8data);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_MT_DATA_ACK;

	/* Send the Stop Bit */
	TWI_stop();

	return TWI_SUCCESS;
}

TWI_STATUS_t EEPROM_readByte(uint16 u16address, uint8* u8data)
{
	/* Send the Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return TWI_START;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(EEPROM_DEVICE_ADDRESS | A0_A1_A2_BITS_FROM_ADDRESS(u16address) | WRITEMODE));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return TWI_MT_SLA_W_ACK;

	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16address));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_MT_DATA_ACK;

	/* Send the Repeated Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_REP_START)
		return TWI_REP_START;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (Read) */
	TWI_writeByte((uint8)(EEPROM_DEVICE_ADDRESS | A0_A1_A2_BITS_FROM_ADDRESS(u16address) | READMODE));
	if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
		return TWI_MT_SLA_R_ACK;

	/* Read Byte from Memory without send ACK */
	*u8data = TWI_readByteWithNACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
		return TWI_MR_DATA_NACK;

	/* Send the Stop Bit */
	TWI_stop();

	return TWI_SUCCESS;
}

TWI_STATUS_t EEPROM_writePage(uint16 u16address, uint8* u8data, uint8 u8length)
{
	uint8 i;
	/* Send the Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return TWI_START;
	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(EEPROM_DEVICE_ADDRESS | A0_A1_A2_BITS_FROM_ADDRESS(u16address) | WRITEMODE));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return TWI_MT_SLA_W_ACK;
	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16address));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_MT_DATA_ACK;
	/* write byte to eeprom */
	for (i = 0; i < u8length; i++)
	{
		TWI_writeByte(u8data[i]);
		if (TWI_getStatus() != TWI_MT_DATA_ACK)
			return TWI_MT_DATA_ACK;
	}
	/* Send the Stop Bit */
	TWI_stop();
	return TWI_SUCCESS;
}

TWI_STATUS_t EEPROM_readPage(uint16 u16address, uint8* u8data, uint8 u8length)
{
	uint8 i;
	/* Send the Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return TWI_START;
	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(EEPROM_DEVICE_ADDRESS | A0_A1_A2_BITS_FROM_ADDRESS(u16address) | WRITEMODE));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return TWI_MT_SLA_W_ACK;
	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16address));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_MT_DATA_ACK;
	/* Send the Repeated Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_REP_START)
		return TWI_REP_START;
	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (Read) */
	TWI_writeByte((uint8)((0xA0) | A0_A1_A2_BITS_FROM_ADDRESS(u16address) | READMODE));
	if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
		return TWI_MT_SLA_R_ACK;
	/* Read Byte from Memory without send ACK */
	for (i = 0; i < u8length; i++)
	{
		u8data[i] = TWI_readByteWithACK();
		if (TWI_getStatus() != TWI_MR_DATA_ACK)
			return TWI_MR_DATA_ACK;
	}
	/* Send the Stop Bit */
	TWI_stop();
	return TWI_SUCCESS;
}
