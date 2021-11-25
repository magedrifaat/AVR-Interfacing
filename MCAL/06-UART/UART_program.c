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

#include "../02-GIE/GIE_interface.h"

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

#if UART_u8_BUFFER_MODE == UART_u8_BUFFERED
	UART_voidSetRCCallback(UART_voidRXHandler);
	UART_voidEnableRCInterrupt();
	GIE_voidEnableInterrupts();
#endif
}

void UART_voidSetBaudrate(u32 Copy_u32Baudrate) {
	u16 Loc_u16UBRR = (F_CPU / 8 / Copy_u32Baudrate - 1) / 2;

	UBRRH = Loc_u16UBRR >> 8;
	UBRRL = (u8)Loc_u16UBRR;
}

void UART_voidWrite(u16 Copy_u16Data) {
#if UART_u8_BUFFER_MODE == UART_u8_UNBUFFERED
	while (!GET_BIT(UCSRA, UDRE));

	CLR_BIT(UCSRB, TXB8);
	if (GET_BIT(UCSRB, UCSZ2) && GET_BIT(Copy_u16Data, 8)) {
		SET_BIT(UCSRB, TXB8);
	}

	UDR = (u8)Copy_u16Data;
#else
	UART_u8TXBuff[UART_u8TXEnd] = (u8)Copy_u16Data;
	UART_u8TXEnd = (UART_u8TXEnd + 1) % UART_u8_TX_BUFFER_SIZE;
	if ((UART_u8TXEnd - UART_u8TXStart + UART_u8_TX_BUFFER_SIZE) % UART_u8_TX_BUFFER_SIZE == 1) {
		UART_voidSetTCCallback(UART_s16TXHandler);
		UART_voidEnableTCInterrupt();
	}
#endif
}

u8  UART_u8IsAvailable() {
#if UART_u8_BUFFER_MODE == UART_u8_UNBUFFERED
	return GET_BIT(UCSRA, RXC);
#else
	return (UART_u8RXEnd - UART_u8RXStart + UART_u8_RX_BUFFER_SIZE) % UART_u8_RX_BUFFER_SIZE > 0;
#endif
}

s16 UART_s16Read() {
#if UART_u8_BUFFER_MODE == UART_u8_UNBUFFERED
	if (!GET_BIT(UCSRA, RXC)) {
		return -1;
	}

	s16 res = 0;
	if (GET_BIT(UCSRB, UCSZ2) && GET_BIT(UCSRB, RXB8)) {
		res = 0x100;
	}

	res |= UDR;

	return res;
#else
	if ((UART_u8RXEnd - UART_u8RXStart + UART_u8_RX_BUFFER_SIZE) % UART_u8_RX_BUFFER_SIZE > 0) {
		if (UART_u8RXStart < UART_u8_RX_BUFFER_SIZE - 1) {
			return UART_u8RXBuff[UART_u8RXStart++];
		}
		else {
			UART_u8RXStart = 0;
			return UART_u8RXBuff[UART_u8_RX_BUFFER_SIZE - 1];
		}
	}
	else {
		return UART_s16_NO_DATA;
	}
#endif
}

void UART_voidFlush() {
#if UART_u8_BUFFER_MODE == UART_u8_BUFFERED
	UART_u8RXStart = UART_u8RXEnd;
#else
	u8 Loc_u8Dummy;
	while (GET_BIT(UCSRA, RXC)) {
		Loc_u8Dummy = UDR;
	}
	Loc_u8Dummy++;
#endif
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

void UART_voidEnableTCInterrupt() {
	SET_BIT(UCSRB, UDRIE);
}

void UART_voidDisableTCInterrupt() {
	CLR_BIT(UCSRB, UDRIE);
}

void UART_voidSetTCCallback(s16 (* Copy_ps16Callback) (void)) {
	UART_ps16TCCallback = Copy_ps16Callback;
}

void UART_voidEnableRCInterrupt() {
	SET_BIT(UCSRB, RXCIE);
}

void UART_voidDisableRCInterrupt() {
	CLR_BIT(UCSRB, RXCIE);
}

void UART_voidSetRCCallback(void (* Copy_pvoidCallback) (u16)) {
	UART_pvoidRCCallback = Copy_pvoidCallback;
}

#if UART_u8_BUFFER_MODE == UART_u8_BUFFERED
s16 UART_s16TXHandler(void) {
	if ((UART_u8TXEnd - UART_u8TXStart + UART_u8_TX_BUFFER_SIZE) % UART_u8_TX_BUFFER_SIZE > 0) {
		if (UART_u8TXStart < UART_u8_TX_BUFFER_SIZE - 1) {
			return UART_u8TXBuff[UART_u8TXStart++];
		}
		else {
			UART_u8TXStart = 0;
			return UART_u8TXBuff[UART_u8_TX_BUFFER_SIZE - 1];
		}
	}
	else {
		return UART_s16_NO_DATA;
	}
}

void UART_voidRXHandler(u16 data) {
	UART_u8RXBuff[UART_u8RXEnd] = (u8)data;
	UART_u8RXEnd = (UART_u8RXEnd + 1) % UART_u8_RX_BUFFER_SIZE;
}
#endif


ISR(UART_UDRE_vec) {
	if (UART_ps16TCCallback == NULL) {
		UART_voidDisableTCInterrupt();
		return;
	}

	s16 Loc_s16Data = UART_ps16TCCallback();

	if (Loc_s16Data == UART_s16_NO_DATA) {
		UART_voidDisableTCInterrupt();
	}
	else {
		u16 Loc_u16Data = (u16)Loc_s16Data;
		CLR_BIT(UCSRB, TXB8);
		if (GET_BIT(UCSRB, UCSZ2) && GET_BIT(Loc_u16Data, 8)) {
			SET_BIT(UCSRB, TXB8);
		}

		UDR = (u8)Loc_u16Data;
	}
}

ISR(UART_RXC_vec) {
	if (UART_pvoidRCCallback == NULL) {
		UART_voidDisableRCInterrupt();
		return;
	}

	u16 res = 0;
	if (GET_BIT(UCSRB, UCSZ2) && GET_BIT(UCSRB, RXB8)) {
		res = 0x100;
	}

	res |= UDR;

	UART_pvoidRCCallback(res);
}
