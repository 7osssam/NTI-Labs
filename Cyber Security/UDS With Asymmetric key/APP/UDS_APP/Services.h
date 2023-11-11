#ifndef SERVICES_H
#define SERVICES_H

#include "STD_TYPES.h"

void   LCD_displayHex_u32(uint32 num);
uint32 stringtoInt(uint8* str);
void   intToString(uint32 num, uint8* str);
void   reverseString(uint8* str);
uint32 generateRandomNumber();

#endif // SERVICES_H