/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Header file for the ADC drivers
 *
 * Author: Hossam Mohamed
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "STD_TYPES.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE  1023 /* 10-bit resolution (2^10 - 1 = 1023)*/
#define ADC_REF_VOLT_VALUE 5	/* ADC reference voltage value (5V or 3.3V)*/

/* static configuration for ADC driver */
#define ADC_INTERRUPT_MODE FALSE

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

typedef enum
{
	ADC_AREF,	 /* AREF, Internal Vref turned off */
	ADC_AVCC,	 /* AVCC with external capacitor at AREF pin */
	ADC_INTERNAL /* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
} ADC_ReferenceVoltage_t;

typedef enum
{
	NO_PRESCALING = 0,
	ADC_PRESCALER_2,
	ADC_PRESCALER_4,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128
} ADC_Prescaler_t;

typedef enum
{
	ADC_INTERRUPT_DISABLE = 0,
	ADC_INTERRUPT_ENABLE
} ADC_interrupt_t;

typedef enum
{
	ADC_FREE_RUNNING_MODE = 0,
	ADC_ANALOG_COMPARATOR,
	ADC_EXTERNAL_INTERRUPT_REQUEST_0,
	ADC_TIMER0_COMPARE_MATCH,
	ADC_TIMER0_OVERFLOW,
	ADC_TIMER1_COMPARE_MATCH_B,
	ADC_TIMER1_OVERFLOW,
	ADC_TIMER1_CAPTURE_EVENT,
	ADC_SINGLE_CONVERSION_MODE
} ADC_AutoTriggerSource_t;

typedef enum
{
	ADC0 = 0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
} ADC_Channel_t;

typedef struct
{
	ADC_ReferenceVoltage_t	ref_volt;
	ADC_Prescaler_t			prescaler;
	ADC_AutoTriggerSource_t auto_trigger_source;
} ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*******************************************************************************
 * @fn              - ADC_init
 * @brief           - This function is used to initialize the ADC driver 
 * @param[in]       - ADC_ConfigType *config_ptr (Struct members are ref_volt, prescaler and auto_trigger_source)
 * @return          - void
 *******************************************************************************/
void ADC_init(ADC_ConfigType* config_struct);

/*******************************************************************************
 * @fn              - ADC_Deinit
 * @brief           - This function is used to deinitialize the ADC driver by disabling the ADC
 * @param[in]       - void
 * @return          - void
 *******************************************************************************/
void ADC_Deinit(void);

/*******************************************************************************
 * @fn              - ADC_InterruptEnable
 * @brief           - This function is used to enable the ADC interrupt
 * @param[in]       - void
 * @return          - void
 *******************************************************************************/
void ADC_InterruptEnable(void);

/*******************************************************************************
 * @fn              - ADC_InterruptDisable
 * @brief           - This function is used to disable the ADC interrupt
 * @param[in]       - void
 * @return          - void
 *******************************************************************************/
void ADC_InterruptDisable(void);

/*******************************************************************************
 * @fn              - ADC_setAutoTriggerSource
 * @brief           - This function is used to set the auto trigger source
 * @param[in]       - ADC_AutoTriggerSource_t auto_trigger_source
 * @return          - void
 *******************************************************************************/
void ADC_setAutoTriggerSource(ADC_AutoTriggerSource_t auto_trigger_source);

/*******************************************************************************
 * @fn              - ADC_setCallBack
 * @brief           - This function is used to set the callback function address
 * @param[in]       - void (*a_ptr)(void)
 * @return          - void
 *******************************************************************************/
void ADC_setCallback(void (*a_ptr)(void));

/*******************************************************************************
 * @fn              - ADC_readChannelBlocking
 * @brief           - This function starts the conversion and waits for it to finish and return the digital value
 * @param[in]       - ADC_Channel_t channel_num (0-7)
 * @return          - uint16
 * @note			- This function is used in case of polling
 *******************************************************************************/
uint16 ADC_readChannelBlocking(ADC_Channel_t channel_num);

/*******************************************************************************
 * @fn              - ADC_readChannelNonBlocking
 * @brief           - This function is used to read the ADC channel non-blocking
 * @param[in]       - ADC_Channel_t channel_num (0-7)
 * @return          - void
 * @note			- This function is used in case of interrupt
 *******************************************************************************/
void ADC_startConversionNonBlocking(ADC_Channel_t channel_num);

/*******************************************************************************
 * @fn              - ADC_getValue
 * @brief           - This function is used to get the ADC value
 * @param[in]       - void
 * @return          - uint16
 *******************************************************************************/
uint16 ADC_getValue(void);

#endif /* ADC_H_ */