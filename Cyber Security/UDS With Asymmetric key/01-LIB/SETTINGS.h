/******************************************************************************
 *
 * File Name: SETTINGS.h
 *
 * Description: Static configuration file for the project
 * 					- CPU CLOCK FREQUENCY
 * 					- MCU MODE
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/

#ifndef SETTINGS_H /* HEADER GUARD*/
#define SETTINGS_H

#define Eta32mega

#ifdef Eta32mega
	#define F_CPU 16000000UL
#endif

#endif /* SETTINGS_H */