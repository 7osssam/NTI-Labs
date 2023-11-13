#ifndef SERVICES_H
#define SERVICES_H

#include "STD_TYPES.h"

uint32 stringToHex(const uint8* str);

uint32 generateRandomNumber();

uint16 encryptMessage(uint16 message);

#endif // SERVICES_H