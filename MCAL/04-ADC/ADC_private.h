/*
 * ADC_private.h
 *
 *  Created on: 9 Oct 2021
 *      Author: Maged
 */

#ifndef MCAL_04_ADC_ADC_PRIVATE_H_
#define MCAL_04_ADC_ADC_PRIVATE_H_

#include "../../Services/STD_Types.h"
#include "../../Services/BIT_MATH.h"

#define ADMUX    *((volatile u8 *) 0x27)
#define REFS1    7
#define REFS0    6
#define ADLAR    5

#define ADCSRA   *((volatile u8 *) 0x26)
#define ADEN     7
#define ADSC     6

#define ADCH     *((volatile u8 *) 0x25)
#define ADCL     *((volatile u8 *) 0x24)
#define SFIOR    *((volatile u8 *) 0x50)

#endif /* MCAL_04_ADC_ADC_PRIVATE_H_ */
