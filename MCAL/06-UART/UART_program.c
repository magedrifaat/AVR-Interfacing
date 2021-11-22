/*
 * UART_program.c
 *
 *  Created on: 21 Nov 2021
 *      Author: Maged
 */

#include "../../Services/STD_Types.h"
#include "../../Services/BIT_MATH.h"

#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"

void UART_voidInit() {
	UART_voidSetBaudrate(UART_u32_BAUDRATE);

#ifdef UART_ENABLE_TRANSMITER
	SET_BIT(UCSRB, TXEN);
#else
	CLR_BIT(UCSRB, TXEN);
#endif

#ifdef UART_ENABLE_RECEIVER
	SET_BIT(UCSRB, RXEN);
#else
	CLR_BIT(UCSRB, RXEN);
#endif

	u8 Loc_u8Config = 0;
#if UART_u8_FRAME_SIZE == 6 || UART_u8_FRAME_SIZE == 8 || UART_u8_FRAME_SIZE == 9
	SET_BIT(Loc_u8Config, UCSZ0);
#endif

#if UART_u8_FRAME_SIZE == 7 || UART_u8_FRAME_SIZE == 8 || UART_u8_FRAME_SIZE == 9
	SET_BIT(Loc_u8Config, UCSZ1);
#endif

#if UART_u8_FRAME_SIZE == 9
	SET_BIT(UCSRB, UCSZ2);
#endif

#if UART_u8_STOP_BITS == 2
	SET_BIT(Loc_u8Config, USBS);
#endif

#if UART_u8_PARITY_MODE == UART_u8_PARITY_ODD || UART_u8_PARITY_MODE == UART_u8_PARITY_EVEN
	SET_BIT(Loc_u8Config, UPM1);
#if UART_u8_PARITY_MODE == UART_u8_PARITY_ODD
	SET_BIT(Loc_u8Config, UPM0);
#endif
#endif

	UCSRC = (1 << URSEL) | Loc_u8Config;
}

void UART_voidSetBaudrate(u32 Copy_u32Baudrate) {
	u16 Loc_u16UBRR = (F_CPU / 8 + Copy_u32Baudrate) / (2 * Copy_u32Baudrate) - 1;

	UBRRH = Loc_u16UBRR >> 8;
	UBRRL = (u8)Loc_u16UBRR;
}

void UART_voidWrite(u16 Copy_u16Data) {
	while (!GET_BIT(UCSRA, UDRE));

	CLR_BIT(UCSRB, TXB8);
	if (GET_BIT(UCSRB, UCSZ2) && GET_BIT(Copy_u16Data, 8)) {
		SET_BIT(UCSRB, TXB8);
	}

	UDR = (u8)Copy_u16Data;
}

u8  UART_u8IsAvailable() {
	return GET_BIT(UCSRA, RXC);
}

s16 UART_s16Read() {
	if (!GET_BIT(UCSRA, RXC)) {
		return -1;
	}

	s16 res = 0;
	if (GET_BIT(UCSRB, UCSZ2) && GET_BIT(UCSRB, RXB8)) {
		res = 0x100;
	}

	res |= UDR;

	return res;
}

void UART_voidFlush() {
	u8 Loc_u8Dummy;
	while (GET_BIT(UCSRA, RXC)) {
		Loc_u8Dummy = UDR;
	}
	Loc_u8Dummy++;
}

void UART_voidEnableTransmitter() {
	SET_BIT(UCSRB, TXEN);
}

void UART_voidDisableTransmitter() {
	CLR_BIT(UCSRB, TXEN);
}

void UART_voidEnableReceiver() {
	SET_BIT(UCSRB, RXEN);
}

void UART_voidDisableReceiver() {
	CLR_BIT(UCSRB, RXEN);
}

