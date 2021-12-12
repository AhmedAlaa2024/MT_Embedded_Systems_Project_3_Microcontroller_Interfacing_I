/*
 * adc.c
 *
 *  Created on: Oct 2, 2021
 *      Author: ahmed
 */
#include <avr/io.h>
#include "adc.h"
/*******************************************************************************
 *                         		Global Variables	                	       *
 *******************************************************************************/
ADC_ConfigType ADC_Configs =
{
		INTERNAL_2_56V, /* ADC_MAXIMUM_REFERENCE_VOLTAGE = 2.56V */
		FACTOR_8 /* ADC_MAXIMUM_DIGITAL_VALUE = 1023 */
};
/*******************************************************************************
 *                         	    		Functions	                  	       *
 *******************************************************************************/

/*
 * Description: Initialize the ADC by setting the prescaler and reference voltage
 * Input: Pointer to ADC_ConfigType
 * Output: None
 */
void ADC_init(ADC_ConfigType* Config_Ptr)
{
	ADMUX = (((Config_Ptr->ref_volt) & 0x03)<<6); /* Set the reference selection bits */
	SET_BIT(ADCSRA, ADEN); /* Enable the ADC */
	ADCSRA = (ADCSRA & 0xF8) | ((Config_Ptr->prescaler) & 0x07); /* Set the prescaler configurations */
	CLEAR_BIT(ADCSRA, ADIE); /* Disable Interrupt Mode */
}
/*
 * Description: Read the analog signal and convert it to digital
 * Input: The channel number
 * Output: The digital value
 */
uint16 ADC_readChannel(uint8 ch_num)
{
	ADMUX &= 0xE0; /* Remain the last 3 bits */
	ADMUX |= (ch_num & 0x07); /* Assign the channel number */
	SET_BIT(ADCSRA, ADSC); /* Start Conversion */
	while(!(ADCSRA & (1 << ADIF))); /* Busy wait until the flag is raised */
	SET_BIT(ADCSRA, ADIF); /* Reset the flag by 1 */

	return ADC; /* Return the data */
}
