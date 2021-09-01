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

#define LEDS_PORT DIO_u8_PORTA
#define SW1_PIN   DIO_u8_PIN_C0
#define SW2_PIN   DIO_u8_PIN_C1
#define SW3_PIN   DIO_u8_PIN_C2
#define SW4_PIN   DIO_u8_PIN_C3

void voidStateNone(u8);
void voidStateFlash(u8);
void voidStateShift(u8);
void voidStateOutsideIn(u8);
void voidStateInsideOut(u8);

enum State                  {NONE,          FLASH,          SHIFT,          OUTSIDE_IN,         INSIDE_OUT};
void (*STATE_FUNCS[])(u8) = {voidStateNone, voidStateFlash, voidStateShift, voidStateOutsideIn, voidStateInsideOut};
u8 STATE_STEPS[] =          {1,             2,              9,              5,                  5};
u16 STATE_DELAY[] =         {0,             500,            200,            100,                100};

int main(void) {
	DIO_voidSetPortDirection(LEDS_PORT, DIO_u8_PORT_OUTPUT);
	DIO_voidSetPortValue(LEDS_PORT, DIO_u8_PORT_HIGH);

	DIO_voidActivatePullUp(SW1_PIN);
	DIO_voidActivatePullUp(SW2_PIN);
	DIO_voidActivatePullUp(SW3_PIN);
	DIO_voidActivatePullUp(SW4_PIN);

	enum State state = NONE;
	u8 Local_u8Step = 0;
	while(1) {
		if (DIO_u8ReadPinValue(SW1_PIN) == DIO_u8_LOW && state == NONE) {
			state = FLASH;
			Local_u8Step = 0;
		}
		else if (DIO_u8ReadPinValue(SW1_PIN) == DIO_u8_HIGH && state == FLASH) {
			state = NONE;
			Local_u8Step = 0;
		}
		else if (DIO_u8ReadPinValue(SW2_PIN) == DIO_u8_LOW && state == NONE) {
			state = SHIFT;
			Local_u8Step = 0;
		}
		else if (DIO_u8ReadPinValue(SW2_PIN) == DIO_u8_HIGH && state == SHIFT) {
			state = NONE;
			Local_u8Step = 0;
		}
		else if (DIO_u8ReadPinValue(SW3_PIN) == DIO_u8_LOW && state == NONE) {
			state = OUTSIDE_IN;
			Local_u8Step = 0;
		}
		else if (DIO_u8ReadPinValue(SW3_PIN) == DIO_u8_HIGH && state == OUTSIDE_IN) {
			state = NONE;
			Local_u8Step = 0;
		}
		else if (DIO_u8ReadPinValue(SW4_PIN) == DIO_u8_LOW && state == NONE) {
			state = INSIDE_OUT;
			Local_u8Step = 0;
		}
		else if (DIO_u8ReadPinValue(SW4_PIN) == DIO_u8_HIGH && state == INSIDE_OUT) {
			state = NONE;
			Local_u8Step = 0;
		}

		STATE_FUNCS[state](Local_u8Step);
		Local_u8Step = (Local_u8Step + 1) % STATE_STEPS[state];
		for (int i = 0; i < STATE_DELAY[state]; i++) {
			_delay_ms(1);
		}
	}

	return 0;
}

void voidStateNone(u8 Copy_u8Step) {
	DIO_voidSetPortValue(LEDS_PORT, DIO_u8_PORT_LOW);
}

void voidStateFlash(u8 Copy_u8Step) {
	DIO_voidSetPortValue(LEDS_PORT, Copy_u8Step? DIO_u8_PORT_HIGH: DIO_u8_PORT_LOW);
}

void voidStateShift(u8 Copy_u8Step) {
	DIO_voidSetPortValue(LEDS_PORT, 0xFF>>(8 - Copy_u8Step));
}

void voidStateOutsideIn(u8 Copy_u8Step) {
	u8 Local_u8PortValue = (0x0F>>(4-Copy_u8Step)) | (0xF0<<(4-Copy_u8Step));
	DIO_voidSetPortValue(LEDS_PORT, Local_u8PortValue);
}

void voidStateInsideOut(u8 Copy_u8Step) {
	u8 Local_u8PortValue = (0x0F>>Copy_u8Step) | (0xF0<<Copy_u8Step);
	DIO_voidSetPortValue(LEDS_PORT, Local_u8PortValue);
}
