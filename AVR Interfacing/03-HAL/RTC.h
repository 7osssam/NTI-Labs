#ifndef _RTC_INTERFACE_H
#define _RTC_INTERFACE_H

#include "STD_TYPES.h"
#include "TWI.h"

typedef struct
{
	uint8  Seconds;
	uint8  Minutes;
	uint8  Hours;
	uint8  DayOfWeek;
	uint8  Days;
	uint8  Months;
	uint16 Years;
} RTC_t;

#define C_Ds1307ReadMode_uint8	0xD1u // DS1307 ID
#define C_Ds1307WriteMode_uint8 0xD0u // DS1307 ID

#define RTC_DEVICE_ADDRESS		0xD0
#define RTC_SLAVE_ADDRESS		0x02

#define WRITEMODE				(0x00)
#define READMODE				(0x01)

#define RTC_DECIMAL_2_BCD(val)	((val) + (6 * ((val) / 10)))
#define RTC_BCD_2_DECIMAL(val)	((val) - (6 * ((val) >> 4)))

TWI_STATUS_t RTC_init(void);

void RTC_SetTime(RTC_t* rtc);
void RTC_GetTime(RTC_t* rtc);
void RTC_SetDate(RTC_t* rtc);

void RTC_GetDate(RTC_t* rtc);

void RTC_SetDayOfWeek(RTC_t* rtc);

void RTC_GetDayOfWeek(RTC_t* rtc);
#endif
