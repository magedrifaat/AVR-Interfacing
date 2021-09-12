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

#define LED_PORT  DIO_u8_PORTC

#define SW_PIN    DIO_u8_PIN_D2

void sw_handler(void);

void voidBlink(u8 Copy_u8Step);
void voidSweepDown(u8 Copy_u8Step);
void voidSweepUp(u8 Copy_u8Step);
void voidFillDown(u8 Copy_u8Step);
void voidFillUp(u8 Copy_u8Step);
void voidInsideOut(u8 Copy_u8Step);
void voidOutsideIn(u8 Copy_u8Step);
void voidVibrate(u8 Copy_u8Step);

const u8 u8PATTERN_COUNT = 8;
void (*pvoidPatterns[])(u8 Copy_u8Step) = {voidBlink, voidSweepDown, voidSweepUp, voidFillDown, \
										   voidFillUp, voidInsideOut, voidOutsideIn, voidVibrate};

volatile u8 u8CurrentPattern;
volatile u8 u8CurrentStep;

int main(void) {
	u8CurrentPattern = 0;
	u8CurrentStep = 0;

	DIO_voidSetPortDirection(LED_PORT, DIO_u8_PORT_OUTPUT);

	DIO_voidActivatePullUp(SW_PIN);

	EXTI_voidEnable(EXTI_u8_LINE0, EXTI_u8_RISING_EDGE);
	EXTI_voidCallBack(sw_handler, EXTI_u8_LINE0);
	GIE_voidEnableInterrupts();

	while (1) {
		pvoidPatterns[u8CurrentPattern](u8CurrentStep++);
	}
}

void sw_handler(void) {
	u8CurrentPattern = (u8CurrentPattern + 1) % u8PATTERN_COUNT;
	u8CurrentStep = 0;
}

void voidBlink(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 2;
	DIO_voidSetPortValue(LED_PORT, 0xFF * LOC_u8Step);
	_delay_ms(500);
}

void voidSweepDown(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 9;
	DIO_voidSetPortValue(LED_PORT, 1 << LOC_u8Step);
	_delay_ms(50);
}

void voidSweepUp(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 9;
	DIO_voidSetPortValue(LED_PORT, 0x80 >> LOC_u8Step);
	_delay_ms(50);
}

void voidFillDown(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 9;
	DIO_voidSetPortValue(LED_PORT, 0xFF >> (8 - LOC_u8Step));
	_delay_ms(50);
}

void voidFillUp(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 9;
	DIO_voidSetPortValue(LED_PORT, 0xFF << (8 - LOC_u8Step));
	_delay_ms(50);
}

void voidInsideOut(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 5;
	DIO_voidSetPortValue(LED_PORT, (0x0F >> LOC_u8Step) | (0xF0 << LOC_u8Step));
	_delay_ms(100);
}

void voidOutsideIn(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 5;
	DIO_voidSetPortValue(LED_PORT, (0x0F >> (4 - LOC_u8Step)) | (0xF0 << (4 - LOC_u8Step)));
	_delay_ms(100);
}

void voidVibrate(u8 Copy_u8Step) {
	u8 LOC_u8Step = Copy_u8Step % 2;
	DIO_voidSetPortValue(LED_PORT, 0x55 << LOC_u8Step);
	_delay_ms(200);
}
