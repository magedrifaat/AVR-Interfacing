/*
 * ADC_interface.h
 *
 *  Created on: 9 Oct 2021
 *      Author: Maged
 */

#ifndef MCAL_04_ADC_ADC_INTERFACE_H_
#define MCAL_04_ADC_ADC_INTERFACE_H_

#define ADC_u8_CHANNEL_0   0
#define ADC_u8_CHANNEL_1   1
#define ADC_u8_CHANNEL_2   2
#define ADC_u8_CHANNEL_3   3
#define ADC_u8_CHANNEL_4   4
#define ADC_u8_CHANNEL_5   5
#define ADC_u8_CHANNEL_6   6
#define ADC_u8_CHANNEL_7   7

#define ADC_u8_REF_AREF   0
#define ADC_u8_REF_AVCC   1
#define ADC_u8_REF_2v56   2

#define ADC_u8_PRESCALAR_2     1
#define ADC_u8_PRESCALAR_4     2
#define ADC_u8_PRESCALAR_8     3
#define ADC_u8_PRESCALAR_16    4
#define ADC_u8_PRESCALAR_32    5
#define ADC_u8_PRESCALAR_64    6
#define ADC_u8_PRESCALAR_128   7

void ADC_voidInit(void);
u16 ADC_u16Read(u8 Copy_u8Channel);
void ADC_voidSetPrescalar(u8 Copy_u8Prescalar);
void ADC_voidEnable(void);
void ADC_voidDisable(void);

#endif /* MCAL_04_ADC_ADC_INTERFACE_H_ */
