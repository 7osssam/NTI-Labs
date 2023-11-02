
/******************************************************************
 * @Module   	: Servo Motor
 * @Title 	 	: Servo Motor Module Interface
 * @Filename 	: Servo.h
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: using Timer1
 ********************************************************************/
#ifndef SERVO_H_
#define SERVO_H_

#include "STD_TYPES.h"
#include "DIO_map.h"

#define SERVO_PWM_REG OCR1A

/**
 * The function Servo_Init initializes the servo motor by configuring Timer1 and setting the input
 * capture register (ICR1) to a value of 4999.
 */
void Servo_Init(void);

/**
 * The function Servo_setAngel calculates the PWM value for a given angle and sets it in the
 * SERVO_PWM_REG register.
 * 
 * @param angel The parameter "angel" represents the angle in degrees that you want to set for the
 * servo motor.
 */
void Servo_setAngel(uint8 angel);

#endif /* SERVO_H_ */