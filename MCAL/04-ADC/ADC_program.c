/*
 * ADC_program.c
 *
 *  Created on: 9 Oct 2021
 *      Author: Maged
 */

#include "../../Services/STD_Types.h"
#include "../../Services/BIT_MATH.h"

#include "ADC_private.h"
#include "ADC_interface.h"
#include "ADC_config.h"

#include <util/delay.h>

void ADC_voidInit(void) {
	// SET Voltage Reference
	switch (ADC_u8_REF_SELECTION) {
	case ADC_u8_REF_AREF:
			CLR_BIT(ADMUX, REFS0);
			CLR_BIT(ADMUX, REFS1);
			break;
	case ADC_u8_REF_AVCC:
			SET_BIT(ADMUX, REFS0);
			CLR_BIT(ADMUX, REFS1);
			break;
	case ADC_u8_REF_2v56:
			SET_BIT(ADMUX, REFS0);
			SET_BIT(ADMUX, REFS1);
			break;
	}

	// Set Left Adjustment
	CLR_BIT(ADMUX, ADLAR);

	// Set Prescalar and Enable
	ADCSRA = ADC_u8_DEFAULT_PRESCALAR;
	SET_BIT(ADCSRA, ADEN);
}

u16 ADC_u16Read(u8 Copy_u8Channel) {
	// Avoid infinite loop if ADC is not enabled
	if (!GET_BIT(ADCSRA, ADEN)) {
		return 0;
	}

	// Set Channel
	ADMUX = (ADMUX & 0xE0) | (Copy_u8Channel & 0x1F);

	// Set start bit and wait until cleared
	SET_BIT(ADCSRA, ADSC);
	while (GET_BIT(ADCSRA, ADSC));

	// ADCL must be read first before ADCH
	return (u16)(ADCL | (ADCH << 8));
}

void ADC_voidSetPrescalar(u8 Copy_u8Prescalar) {
	ADCSRA = (ADCSRA & 0xF8) | (Copy_u8Prescalar & 0x07);
}

void ADC_voidEnable(void) {
	SET_BIT(ADCSRA, ADEN);
}

void ADC_voidDisable(void) {
	CLR_BIT(ADCSRA, ADEN);
}
