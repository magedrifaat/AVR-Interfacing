/*
 * CLCD_program.c
 *
 *  Created on: 30 Aug 2021
 *      Author: Maged
 */
#include "../../Services/STD_Types.h"
#include "../../Services/BIT_MATH.h"

#include "../../MCAL/01-DIO/DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"

#include <util/delay.h>

void CLCD_voidInit(void) {
	for (u8 i = 0; i < sizeof(CLCD_u8DataPins); i++) {
		DIO_voidSetPinDirection(CLCD_u8DataPins[i], DIO_u8_OUTPUT);
	}
	DIO_voidSetPinDirection(CLCD_RS, DIO_u8_OUTPUT);
	DIO_voidSetPinDirection(CLCD_EN, DIO_u8_OUTPUT);
#ifdef CLCD_RW
	DIO_voidSetPinDirection(CLCD_RW, DIO_u8_OUTPUT);
	DIO_voidSetPinValue(CLCD_RW, DIO_u8_LOW);
#endif

	_delay_ms(50);

#ifdef CLCD_4BIT_MODE
	DIO_voidSetPinValue(CLCD_RS, DIO_u8_LOW);
	/*
	 * The LCD starts in 8-bit mode, so it is required to send
	 * the first half of a function set command specifying 4-bit
	 * interface first.
	 * However, this won't work if the LCD is already in 4-bit
	 * mode so a function set command is sent first to set the
	 * interface to 8-bit to ensure a repeatable state every time.
	 * The command is sent 3 times to handle cases when the LCD is
	 * waiting for the second half of a command in 4-bit mode.
	 */
	CLCD_voidSendByte(CLCD_u8_8BIT_FUNCTION_SET >> 4);
	_delay_ms(5);
	CLCD_voidSendByte(CLCD_u8_8BIT_FUNCTION_SET >> 4);
	_delay_ms(5);
	CLCD_voidSendByte(CLCD_u8_8BIT_FUNCTION_SET >> 4);
	_delay_ms(5);
	CLCD_voidSendByte(CLCD_u8_4BIT_FUNCTION_SET_H);
	_delay_ms(5);

	CLCD_voidSendByte(CLCD_u8_4BIT_FUNCTION_SET_H);
	_delay_ms(1);
	CLCD_voidSendByte(CLCD_u8_4BIT_FUNCTION_SET_L);
	_delay_ms(1);
#else
	CLCD_voidSendCommand(CLCD_u8_8BIT_FUNCTION_SET);
	_delay_ms(1);
#endif

	CLCD_voidSendCommand(CLCD_u8_DISPLAY_CONTROL);
	_delay_ms(1);

	CLCD_voidSendCommand(CLCD_u8_DISPLAY_CLEAR);
	_delay_ms(5);

	CLCD_voidSendCommand(CLCD_u8_ENTRY_MODE_SET);
	_delay_ms(1);
}

void CLCD_voidSetCursor(u8 Copy_u8Row, u8 Copy_u8Column) {
	CLCD_voidSendCommand(
	CLCD_u8_DDRAM_OFFSET + CLCD_u8_ROW2_OFFSET * Copy_u8Row + Copy_u8Column);
	_delay_ms(1);
}

void CLCD_voidSendString(s8 *Copy_u8PtrString) {
	while (*Copy_u8PtrString) {
		CLCD_voidSendData(*Copy_u8PtrString++);
	}
}

void CLCD_voidSendNumber(u64 Copy_u64Number) {
	if (Copy_u64Number / 10 == 0) {
		CLCD_voidSendData((Copy_u64Number % 10) + '0');
	} else {
		CLCD_voidSendNumber(Copy_u64Number / 10);
		CLCD_voidSendData((Copy_u64Number % 10) + '0');
	}
}

void CLCD_voidSetCustomChar(u8 Copy_u8CharIndex, u8 *Copy_u8CharData) {
	if (Copy_u8CharIndex >= 0 && Copy_u8CharIndex < 8) {
		CLCD_voidSendCommand(CLCD_u8_CGRAM_OFFSET + (Copy_u8CharIndex << 3));
		_delay_ms(1);
		for (u8 i = 0; i < 8; i++) {
			CLCD_voidSendData(Copy_u8CharData[i]);
		}
		CLCD_voidSendCommand(CLCD_u8_DDRAM_OFFSET);
		_delay_ms(1);
	}
}

void CLCD_voidClearDisplay(void) {
	CLCD_voidSendCommand(CLCD_u8_CLEAR_DISPLAY);
	_delay_ms(5);
}

void CLCD_voidShowCursor(u8 Copy_u8Show) {
	if (Copy_u8Show) {
		CLCD_voidSendCommand(CLCD_u8_DISPLAY_CONTROL | (1<<CURSOR_BIT));
	} else {
		CLCD_voidSendCommand(CLCD_u8_DISPLAY_CONTROL & (~(1<<CURSOR_BIT)));
	}
}

void CLCD_voidBlinkCursor(u8 Copy_u8Blink) {
	if (Copy_u8Blink) {
		CLCD_voidSendCommand(CLCD_u8_DISPLAY_CONTROL | (1<<BLINK_BIT));
	} else {
		CLCD_voidSendCommand(CLCD_u8_DISPLAY_CONTROL & (~(1<<BLINK_BIT)));
	}
}

void CLCD_voidShiftDisplay(u8 Copy_u8Direction) {
	CLCD_voidSendCommand(CLCD_u8_DISPLAY_SHIFT + (Copy_u8Direction<<2));
}

void CLCD_voidSendData(u8 Copy_u8Data) {
	DIO_voidSetPinValue(CLCD_RS, DIO_u8_HIGH);
#ifdef CLCD_4BIT_MODE
	CLCD_voidSendTwoNibbles(Copy_u8Data);
#else
	CLCD_voidSendByte(Copy_u8Data);
#endif
	_delay_ms(1);
}

void CLCD_voidSendCommand(u8 Copy_u8Command) {
	DIO_voidSetPinValue(CLCD_RS, DIO_u8_LOW);
#ifdef CLCD_4BIT_MODE
	CLCD_voidSendTwoNibbles(Copy_u8Command);
#else
	CLCD_voidSendByte(Copy_u8Command);
#endif
}

void CLCD_voidSendTwoNibbles(u8 Copy_u8Byte) {
	CLCD_voidSendByte(Copy_u8Byte >> 4);
	CLCD_voidSendByte(Copy_u8Byte & 0x0F);
}

void CLCD_voidSendByte(u8 Copy_u8Byte) {
	for (u8 i = 0; i < sizeof(CLCD_u8DataPins); i++) {
		DIO_voidSetPinValue(CLCD_u8DataPins[i], Copy_u8Byte % 2);
		Copy_u8Byte /= 2;
	}

	DIO_voidSetPinValue(CLCD_EN, DIO_u8_HIGH);
	_delay_us(10);
	DIO_voidSetPinValue(CLCD_EN, DIO_u8_LOW);
}
