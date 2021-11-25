/*
 * UART_private.h
 *
 *  Created on: 21 Nov 2021
 *      Author: Maged
 */

#ifndef MCAL_06_UART_UART_PRIVATE_H_
#define MCAL_06_UART_UART_PRIVATE_H_

#define UDR       (*((volatile u8 *)0x2C))

#define UCSRA     (*((volatile u8 *)0x2B))
#define RXC       7
#define TXC       6
#define UDRE      5
#define FE        4
#define DOR       3
#define PE        2
#define U2X       1

#define UCSRB     (*((volatile u8 *)0x2A))
#define RXCIE     7
#define TXCIE     6
#define UDRIE     5
#define RXEN      4
#define TXEN      3
#define UCSZ2     2
#define RXB8      1
#define TXB8      0


#define UCSRC     (*((volatile u8 *)0x40))
#define URSEL     7
#define UMSEL     6
#define UPM1      5
#define UPM0      4
#define USBS      3
#define UCSZ1     2
#define UCSZ0     1
#define UCPOL     0


#define UBRRL     (*((volatile u8 *)0x29))
#define UBRRH     (*((volatile u8 *)0x40))

void UART_voidSetBaudrate(u32 Copy_u32Baudrate);

#if UART_u8_BUFFER_MODE == UART_u8_BUFFERED
#define UART_u8_TX_BUFFER_SIZE    64
#define UART_u8_RX_BUFFER_SIZE    64

volatile u8 UART_u8TXBuff[UART_u8_TX_BUFFER_SIZE];
volatile u8 UART_u8TXStart = 0;
volatile u8 UART_u8TXEnd = 0;

volatile u8 UART_u8RXBuff[UART_u8_RX_BUFFER_SIZE];
volatile u8 UART_u8RXStart = 0;
volatile u8 UART_u8RXEnd = 0;

s16 UART_s16TXHandler(void);
void UART_voidRXHandler(u16 data);
#endif

#define NULL 0
s16 (* UART_ps16TCCallback) (void) = NULL;
void (* UART_pvoidRCCallback) (u16) = NULL;

#define UART_UDRE_vec   14
#define UART_RXC_vec    13

#define CONCAT(A, B) A ## B
#define ISR(VEC_NUM) void CONCAT(__vector_, VEC_NUM)(void)
ISR(UART_UDRE_vec) __attribute__ ((signal));
ISR(UART_RXC_vec) __attribute__ ((signal));


#endif /* MCAL_06_UART_UART_PRIVATE_H_ */
