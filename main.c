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

#define SEG_PORT        DIO_u8_PORTC
#define TRAFFIC_PORT    DIO_u8_PORTD
#define DIG1_PIN        DIO_u8_PIN_00
#define DIG2_PIN        DIO_u8_PIN_01
#define GREEN_LED_PIN   DIO_u8_PIN_02
#define YELLOW_LED_PIN  DIO_u8_PIN_03
#define RED_LED_PIN     DIO_u8_PIN_04

#define T_GREEN  30
#define T_YELLOW 5
#define T_RED    30

enum State {RED, YELLOW_TO_RED, YELLOW_TO_GREEN, GREEN};

const u8 seg_digits[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
int main(void) {
	DIO_voidSetPortDirection(DIO_u8_PORTC, DIO_u8_PORT_OUTPUT);
	DIO_voidSetPortDirection(DIO_u8_PORTD, DIO_u8_PORT_OUTPUT);

	DIO_voidSetPortValue(DIO_u8_PORTC, DIO_u8_PORT_LOW);
	DIO_voidSetPortValue(DIO_u8_PORTD, DIO_u8_PORT_LOW);

	DIO_voidSetPinValue(TRAFFIC_PORT, DIG1_PIN, DIO_u8_HIGH);
	DIO_voidSetPinValue(TRAFFIC_PORT, DIG2_PIN, DIO_u8_HIGH);

	u8 t = T_GREEN;
	DIO_voidSetPinValue(TRAFFIC_PORT, GREEN_LED_PIN, DIO_u8_HIGH);
	enum State state = GREEN;

	while(1) {
		for (int i = 0; i < 100; i++) {
			DIO_voidSetPinValue(TRAFFIC_PORT, DIG2_PIN, DIO_u8_HIGH);
			DIO_voidSetPortValue(DIO_u8_PORTC, seg_digits[t / 10]);
			DIO_voidSetPinValue(TRAFFIC_PORT, DIG1_PIN, DIO_u8_LOW);
			_delay_ms(5);
			DIO_voidSetPinValue(TRAFFIC_PORT, DIG1_PIN, DIO_u8_HIGH);
			DIO_voidSetPortValue(DIO_u8_PORTC, seg_digits[t % 10]);
			DIO_voidSetPinValue(TRAFFIC_PORT, DIG2_PIN, DIO_u8_LOW);
			_delay_ms(5);
		}

		if (t > 0) {
			t -= 1;
		}
		else {
			switch (state) {
				case RED:
					t = T_YELLOW;
					DIO_voidSetPinValue(TRAFFIC_PORT, RED_LED_PIN, DIO_u8_LOW);
					DIO_voidSetPinValue(TRAFFIC_PORT, YELLOW_LED_PIN, DIO_u8_HIGH);
					state = YELLOW_TO_GREEN;
					break;
				case YELLOW_TO_RED:
					t = T_RED;
					DIO_voidSetPinValue(TRAFFIC_PORT, YELLOW_LED_PIN, DIO_u8_LOW);
					DIO_voidSetPinValue(TRAFFIC_PORT, RED_LED_PIN, DIO_u8_HIGH);
					state = RED;
					break;
				case YELLOW_TO_GREEN:
					t = T_GREEN;
					DIO_voidSetPinValue(TRAFFIC_PORT, YELLOW_LED_PIN, DIO_u8_LOW);
					DIO_voidSetPinValue(TRAFFIC_PORT, GREEN_LED_PIN, DIO_u8_HIGH);
					state = GREEN;
					break;
				case GREEN:
					t = T_YELLOW;
					DIO_voidSetPinValue(TRAFFIC_PORT, GREEN_LED_PIN, DIO_u8_LOW);
					DIO_voidSetPinValue(TRAFFIC_PORT, YELLOW_LED_PIN, DIO_u8_HIGH);
					state = YELLOW_TO_RED;
					break;
			}
		}
	}


	return 0;
}
