/*
 * main.c
 *
 *  Created on: 25 Aug 2021
 *      Author: Maged
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include <util/delay.h>

int main(void) {
	DIO_voidSetPinDirection(DIO_u8_PIN_C1, DIO_u8_INPUT);
	DIO_voidActivatePullUp(DIO_u8_PIN_C1);

	DIO_voidSetPinDirection(DIO_u8_PIN_A2, DIO_u8_OUTPUT);

	while(1) {
		if (DIO_u8ReadPinValue(DIO_u8_PIN_C1) == DIO_u8_LOW) {
			DIO_voidSetPinValue(DIO_u8_PIN_A2, DIO_u8_HIGH);
		}
		else {
			DIO_voidSetPinValue(DIO_u8_PIN_A2, DIO_u8_LOW);
		}
	}

	return 0;
}
