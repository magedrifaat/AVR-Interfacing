/*
 * main.c
 *
 *  Created on: 8 Sep 2021
 *      Author: Maged
 */

#include "../Services/STD_Types.h"
#include "../Services/BIT_MATH.h"

#include "../MCAL/06-UART/UART_interface.h"
#include "../HAL/01-CLCD/CLCD_interface.h"

#include <util/delay.h>


int main(void) {
	UART_voidInit();
	CLCD_voidInit();

	while (1) {
		if (UART_u8IsAvailable()) {
			UART_voidWrite(UART_s16Read());
		}
	}
}
