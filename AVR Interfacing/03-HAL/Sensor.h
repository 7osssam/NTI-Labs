/******************************************************************************
 *
 * Module: Sensor
 *
 * File Name: Sensor.h
 *
 * Description: Header file for the Sensor driver
 * 				- LM35 Sensor
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/
#ifndef SENSOR_H_
#define SENSOR_H_

#include "ADC.h"
#include "std_types.h"

/******************************************************************************
 *                                LM35 Definitions                            *
 * ****************************************************************************/
/* Channel of the ADC to which the sensor is connected */
#define LM35_CH				 ADC1
/* Maximum temperature that can be measured by the sensor */
#define LM35_MAX_TEMPERATURE 150
/* the voltage of the sensor at the maximum temperature */
#define LM35_MAX_VOLT		 1.5

/******************************************************************************
 *                                Functions Prototypes                        *
 * ****************************************************************************/

/******************************************************************************
 * Description: Function to read the temperature from the LM35 sensor
 * @param void
 * @return uint8
 * 		   Description: Temperature value
 * 		   Range: 0 ~ 150
 ******************************************************************************/
uint8 LM35_Read(void);

#endif /* SENSOR_H_ */