/*INCLUDE FILES (SERVICES)*/
#include "../../Services/STD_Types.h"
#include "../../Services/BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"

void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction) {
	switch (Copy_u8Port) {
	case DIO_u8_PORTA:
		DDRA = Copy_u8Direction;
		break;
	case DIO_u8_PORTB:
		DDRB = Copy_u8Direction;
		break;
	case DIO_u8_PORTC:
		DDRC = Copy_u8Direction;
		break;
	case DIO_u8_PORTD:
		DDRD = Copy_u8Direction;
		break;
	}
}

void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value) {
	switch (Copy_u8Port) {
	case DIO_u8_PORTA:
		PORTA = Copy_u8Value;
		break;
	case DIO_u8_PORTB:
		PORTB = Copy_u8Value;
		break;
	case DIO_u8_PORTC:
		PORTC = Copy_u8Value;
		break;
	case DIO_u8_PORTD:
		PORTD = Copy_u8Value;
		break;
	}
}

void DIO_voidTogglePin(u8 Copy_u8Pin) {
	u8 Local_u8Port = Copy_u8Pin >> 4;
	u8 Local_u8PortPin = Copy_u8Pin & 0x0F;
	switch (Local_u8Port) {
	case DIO_u8_PORTA:
		TOGGLE_BIT(PORTA, Local_u8PortPin);
		break;
	case DIO_u8_PORTB:
		TOGGLE_BIT(PORTB, Local_u8PortPin);
		break;
	case DIO_u8_PORTC:
		TOGGLE_BIT(PORTC, Local_u8PortPin);
		break;
	case DIO_u8_PORTD:
		TOGGLE_BIT(PORTD, Local_u8PortPin);
		break;
	}
}

void DIO_voidSetPinDirection(u8 Copy_u8Pin, u8 Copy_u8Direction) {
	u8 Local_u8Port = (Copy_u8Pin & 0xF0) >> 4;
	u8 Local_u8PortPin = Copy_u8Pin & 0x0F;
	switch (Local_u8Port) {
	case DIO_u8_PORTA:
		switch (Copy_u8Direction) {
		case DIO_u8_INPUT:
			CLR_BIT(DDRA, Local_u8PortPin);
			break;
		case DIO_u8_OUTPUT:
			SET_BIT(DDRA, Local_u8PortPin);
			break;
		}
		break;
	case DIO_u8_PORTB:
		switch (Copy_u8Direction) {
		case DIO_u8_INPUT:
			CLR_BIT(DDRB, Local_u8PortPin);
			break;
		case DIO_u8_OUTPUT:
			SET_BIT(DDRB, Local_u8PortPin);
			break;
		}
		break;
	case DIO_u8_PORTC:
		switch (Copy_u8Direction) {
		case DIO_u8_INPUT:
			CLR_BIT(DDRC, Local_u8PortPin);
			break;
		case DIO_u8_OUTPUT:
			SET_BIT(DDRC, Local_u8PortPin);
			break;
		}
		break;
	case DIO_u8_PORTD:
		switch (Copy_u8Direction) {
		case DIO_u8_INPUT:
			CLR_BIT(DDRD, Local_u8PortPin);
			break;
		case DIO_u8_OUTPUT:
			SET_BIT(DDRD, Local_u8PortPin);
			break;
		}
		break;
	}
}

void DIO_voidSetPinValue(u8 Copy_u8Pin, u8 Copy_u8Value) {
	u8 Local_u8Port = (Copy_u8Pin & 0xF0) >> 4;
	u8 Local_u8PortPin = Copy_u8Pin & 0x0F;
	switch (Local_u8Port) {
	case DIO_u8_PORTA:
		switch (Copy_u8Value) {
		case DIO_u8_LOW:
			CLR_BIT(PORTA, Local_u8PortPin);
			break;
		case DIO_u8_HIGH:
			SET_BIT(PORTA, Local_u8PortPin);
			break;
		}
		break;
	case DIO_u8_PORTB:
		switch (Copy_u8Value) {
		case DIO_u8_LOW:
			CLR_BIT(PORTB, Local_u8PortPin);
			break;
		case DIO_u8_HIGH:
			SET_BIT(PORTB, Local_u8PortPin);
			break;
		}
		break;
	case DIO_u8_PORTC:
		switch (Copy_u8Value) {
		case DIO_u8_LOW:
			CLR_BIT(PORTC, Local_u8PortPin);
			break;
		case DIO_u8_HIGH:
			SET_BIT(PORTC, Local_u8PortPin);
			break;
		}
		break;
	case DIO_u8_PORTD:
		switch (Copy_u8Value) {
		case DIO_u8_LOW:
			CLR_BIT(PORTD, Local_u8PortPin);
			break;
		case DIO_u8_HIGH:
			SET_BIT(PORTD, Local_u8PortPin);
			break;
		}
		break;
	}
}

u8 DIO_u8ReadPinValue(u8 Copy_u8Pin) {
	u8 Local_u8Port = (Copy_u8Pin & 0xF0) >> 4;
	u8 Local_u8PortPin = Copy_u8Pin & 0x0F;
	u8 LOC_u8PinState = 0;
	switch (Local_u8Port) {
	case DIO_u8_PORTA:
		LOC_u8PinState = GET_BIT(PINA, Local_u8PortPin);
		break;
	case DIO_u8_PORTB:
		LOC_u8PinState = GET_BIT(PINB, Local_u8PortPin);
		break;
	case DIO_u8_PORTC:
		LOC_u8PinState = GET_BIT(PINC, Local_u8PortPin);
		break;
	case DIO_u8_PORTD:
		LOC_u8PinState = GET_BIT(PIND, Local_u8PortPin);
		break;
	}

	return LOC_u8PinState;
}

void DIO_voidActivatePullUp(u8 Copy_u8Pin) {
	DIO_voidSetPinDirection(Copy_u8Pin, DIO_u8_INPUT);
	DIO_voidSetPinValue(Copy_u8Pin, DIO_u8_HIGH);
}
