/*
 * main.c
 *
 *  Created on: 8 Sep 2021
 *      Author: Maged
 */

#include "../Services/STD_Types.h"
#include "../Services/BIT_MATH.h"

#include "../MCAL/01-DIO/DIO_interface.h"
#include "../MCAL/02-GIE/GIE_interface.h"
#include "../MCAL/03-EXTI/EXTI_interface.h"

#include <util/delay.h>

#define LED1_PIN  DIO_u8_PIN_D0
#define LED2_PIN  DIO_u8_PIN_D1

#define SW1_PIN    DIO_u8_PIN_D2
#define SW2_PIN    DIO_u8_PIN_D3

void sw1_handler(void);
void sw2_handler(void);

int main(void) {
	DIO_voidSetPinDirection(LED1_PIN, DIO_u8_OUTPUT);
	DIO_voidSetPinDirection(LED2_PIN, DIO_u8_OUTPUT);

	DIO_voidActivatePullUp(SW1_PIN);
	DIO_voidActivatePullUp(SW2_PIN);

	EXTI_voidEnable(EXTI_u8_LINE0, EXTI_u8_ON_CHANGE);
	EXTI_voidEnable(EXTI_u8_LINE1, EXTI_u8_ON_CHANGE);
	EXTI_voidCallBack(sw1_handler, EXTI_u8_LINE0);
	EXTI_voidCallBack(sw2_handler, EXTI_u8_LINE1);
	GIE_voidEnableInterrupts();

	while (1) {
	}
}


void sw1_handler(void) {
	DIO_voidTogglePin(LED1_PIN);
}

void sw2_handler(void) {
	DIO_voidTogglePin(LED2_PIN);
}
