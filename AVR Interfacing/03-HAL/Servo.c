
/******************************************************************
 * @Module   	: Servo Motor
 * @Title 	 	: Servo Motor Module Source File
 * @Filename 	: Servo.c
 * @target  	: ATMEGA32
 * @Author 	 	: Hossam Mohamed
 * @Compiler 	: avr-gcc 
 * @Notes    	: using Timer1
 ********************************************************************/

#include "STD_TYPES.h"
#include "TIMER.h"
#include "Servo.h"

/************************** Module Private Data **************************/
static Timer1_ConfigType Servo_motor_config = {.initial_value = 0,
											   .compare_value = 0,
											   .Clock_source = TIMER_F_CPU_64,
											   .Timer1_Mode = TIMER1_FASTPWM_ICR_TOP_MODE,
											   .OC1A_Mode = OCRA_NON_INVERTING,
											   .OC1B_mode = OCRB_DISCONNECTED};

void Servo_Init(void)
{
	Timer1_init(&Servo_motor_config);

	// FPWM = FOSC / (N * (1 + TOP));
	// 50Hz = 16MHz / (64 * (1 + TOP));
	// TOP = 5000 - 1
	// ICR1 = 4999
	ICR1 = (uint16)4999; // TOP value
}

void Servo_setAngel(uint8 angel)
{
	SERVO_PWM_REG = ((((angel * (uint32)250) + 90) / 180) + 249);
}