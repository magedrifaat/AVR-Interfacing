/*
 * UART_interface.h
 *
 *  Created on: 21 Nov 2021
 *      Author: Maged
 */

#ifndef MCAL_06_UART_UART_INTERFACE_H_
#define MCAL_06_UART_UART_INTERFACE_H_

#define UART_u8_PARITY_DISABLED     0
#define UART_u8_PARITY_ODD          1
#define UART_u8_PARITY_EVEN         2

#define UART_u8_UNBUFFERED          0
#define UART_u8_BUFFERED            1

void UART_voidInit();

void UART_voidWrite(u16 Copy_u16Data);
u8  UART_u8IsAvailable();
s16 UART_s16Read();
void UART_voidFlush();

void UART_voidEnableTransmitter();
void UART_voidDisableTransmitter();

void UART_voidEnableReceiver();
void UART_voidDisableReceiver();

void UART_voidEnableTCInterrupt();
void UART_voidDisableTCInterrupt();
void UART_voidSetTCCallback(u16 (* Copy_pu16Callback) (void));

void UART_voidEnableRCInterrupt();
void UART_voidDisableRCInterrupt();
void UART_voidSetRCCallback(void (* Copy_pvoidCallback) (u16));

#endif /* MCAL_06_UART_UART_INTERFACE_H_ */
