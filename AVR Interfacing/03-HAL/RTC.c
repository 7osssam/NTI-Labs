#include "BIT_MACROS.h"
#include "TWI.h"
#include "RTC.h"

#define A0_A1_A2_BITS_FROM_ADDRESS(address) ((address & 0x0700) >> 7)

#define WRITEMODE							(0x00)
#define READMODE							(0x01)

static TWI_configType RTC_config = {.TWI_slaveAddress = RTC_SLAVE_ADDRESS,
									.prescaler = TWI_Prescaler_1,
									.SCL_Frq = NormalMode_100Kb,
									.generalCallRecognitionMode = TWI_GeneralCallRecognitionEnable_OFF};

TWI_STATUS_t RTC_init(void)
{
	TWI_init(&RTC_config);

	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return TWI_START;

	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | WRITEMODE));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return TWI_MT_SLA_W_ACK;

	TWI_writeByte(0x07);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_MT_DATA_ACK;

	TWI_writeByte(0x00);
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return TWI_MT_DATA_ACK;

	TWI_stop();

	return TWI_SUCCESS;
}

void RTC_SetTime(RTC_t* rtc)
{
	TWI_start();

	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | WRITEMODE));

	TWI_writeByte(0x00);

	TWI_writeByte(rtc->Seconds);
	TWI_writeByte(rtc->Minutes);
	TWI_writeByte(rtc->Hours);

	TWI_writeByte(0x00);
	TWI_stop();
}

void RTC_GetTime(RTC_t* rtc)
{
	TWI_start();

	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | WRITEMODE));

	TWI_writeByte(0x00);
	TWI_stop();

	TWI_start();
	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | READMODE));

	rtc->Seconds = TWI_readByteWithACK();
	rtc->Minutes = TWI_readByteWithACK();
	rtc->Hours = TWI_readByteWithNACK();

	TWI_stop();
}

void RTC_SetDate(RTC_t* rtc)
{
	TWI_start();

	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | WRITEMODE));

	TWI_writeByte(0x04);
	TWI_writeByte(rtc->Days);
	TWI_writeByte(rtc->Months);
	TWI_writeByte(rtc->Years);
	TWI_writeByte(0x00);

	TWI_stop();
}

void RTC_GetDate(RTC_t* rtc)
{
	TWI_start();
	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | WRITEMODE));

	TWI_writeByte(0x04);
	TWI_stop();

	TWI_start();
	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | READMODE));

	rtc->Days = TWI_readByteWithACK();

	rtc->Months = TWI_readByteWithACK();

	rtc->Years = TWI_readByteWithNACK();

	TWI_stop();
}

void RTC_SetDayOfWeek(RTC_t* rtc)
{
	TWI_start();
	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | WRITEMODE));

	TWI_writeByte(0x03);

	TWI_writeByte(rtc->DayOfWeek);
	TWI_stop();
}

void RTC_GetDayOfWeek(RTC_t* rtc)
{
	TWI_start();
	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | WRITEMODE));

	TWI_writeByte(0x03);
	TWI_stop();

	TWI_start();
	TWI_writeByte((uint8)(RTC_DEVICE_ADDRESS | READMODE));

	rtc->DayOfWeek = TWI_readByteWithNACK();
	TWI_stop();
}
