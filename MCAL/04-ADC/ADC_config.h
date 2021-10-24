/*
 * ADC_config.h
 *
 *  Created on: 9 Oct 2021
 *      Author: Maged
 */

#ifndef MCAL_04_ADC_ADC_CONFIG_H_
#define MCAL_04_ADC_ADC_CONFIG_H_

#include "ADC_interface.h"


/*  ADC Reference Voltage Selection
 * Choices:
 * 	- ADC_u8_REF_AVCC
 * 	- ADC_u8_REF_AREF
 * 	- ADC_u8_REF_2V56
 */
#define ADC_u8_REF_SELECTION     ADC_u8_REF_AVCC

/*
 *  ADC Default Prescalar
 *  Choices:
 *    - ADC_u8_PRESCALAR_2
 *    - ADC_u8_PRESCALAR_4
 *    - ADC_u8_PRESCALAR_8
 *    - ADC_u8_PRESCALAR_16
 *    - ADC_u8_PRESCALAR_32
 *    - ADC_u8_PRESCALAR_64
 *    - ADC_u8_PRESCALAR_128
 */
#define ADC_u8_DEFAULT_PRESCALAR  ADC_u8_PRESCALAR_128

#endif /* MCAL_04_ADC_ADC_CONFIG_H_ */
