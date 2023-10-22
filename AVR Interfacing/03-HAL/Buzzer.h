/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "DIO.h"

/*******************************************************************************
 *                      Static Configurations                                  *
 *******************************************************************************/
#define BUZZER_PORT PORTC_ID
#define BUZZER_PIN	PIN6_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*******************************************************************************
 * Description: Function responsible for initialize the Buzzer driver.
 * It sets the direction of the Buzzer pin to output pin and turn it off
 * @param void
 * @return void
 *******************************************************************************/
void Buzzer_init();

/*******************************************************************************
 * Description: Function responsible for turn on the Buzzer by set the Buzzer pin.
 * @param void
 * @return void
 *******************************************************************************/
void Buzzer_on();

/*******************************************************************************
 * Description: Function responsible for turn off the Buzzer by clear the Buzzer pin.
 * @param void
 * @return void
 *******************************************************************************/
void Buzzer_off();

/*******************************************************************************
 * Description: Function responsible for make alarm sound pattern. 
 * @param void
 * @return void
 *******************************************************************************/
void Buzzer_Alarm(void);
#endif /* BUZZER_H_ */