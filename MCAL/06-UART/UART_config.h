/*
 * UART_config.h
 *
 *  Created on: 21 Nov 2021
 *      Author: Maged
 */

#ifndef MCAL_06_UART_UART_CONFIG_H_
#define MCAL_06_UART_UART_CONFIG_H_

// Comment out to disable transmitter
#define UART_ENABLE_TRANSMITER

// Comment out to disable receiver
#define UART_ENABLE_RECEIVER


/* UART Baudrate
 * Common Values:
 * 	- 9600
 * 	- 19200
 * 	- 38400
 * 	- 57600
 * 	- 115200
 * 	- 250000
 *
 */
#define UART_u32_BAUDRATE      9600


/*
 * UART Frame Size
 * Options: 5, 6, 7, 8, 9
 */
#define UART_u8_FRAME_SIZE     8


/* UART Stop Bits
 * Options: 1, 2
 */
#define UART_u8_STOP_BITS      1


/*
 * UART Parity Mode
 * Options:
 * 	- UART_u8_PARITY_DISABLED
 * 	- UART_u8_PARITY_ODD
 * 	- UART_u8_PARITY_EVEN
 */
#define UART_u8_PARITY_MODE     UART_u8_PARITY_DISABLED


/*
 * UART Buffering Mode
 * Options:
 * 	- UART_u8_UNBUFFERED
 * 	- UART_u8_BUFFERED
 */
#define UART_u8_BUFFER_MODE     UART_u8_UNBUFFERED

#endif /* MCAL_06_UART_UART_CONFIG_H_ */
