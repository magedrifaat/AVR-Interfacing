/*
 * main.c
 *
 *  Created on: 8 Sep 2021
 *      Author: Maged
 */

#include "../Services/STD_Types.h"
#include "../Services/BIT_MATH.h"

#include "../HAL/01-CLCD/CLCD_interface.h"
#include "../MCAL/05-TIMER/TIMER_interface.h"
#include "../MCAL/01-DIO/DIO_interface.h"

#include "../MCAL/02-GIE/GIE_interface.h"


#include <util/delay.h>

volatile f32 seconds;

void tick(void) {
	DIO_voidTogglePin(DIO_u8_PIN_C1);
	seconds += 1;
}

int main(void) {
	seconds = 0;
	DIO_voidSetPinDirection(DIO_u8_PIN_C1, DIO_u8_OUTPUT);
	CLCD_voidInit();
	Timer_voidInit();
	Timer_Time_t time = {.u16Seconds=1, .u16MilliSeconds=0, .u16MicroSeconds=0};
	Timer_voidCallEvery(TIMER_u8_TIMER0, &time, tick);
	GIE_voidEnableInterrupts();
	while (1) {
		CLCD_voidSetCursor(CLCD_u8ROW_00, CLCD_u8COLUMN_00);
		CLCD_voidSendNumber(seconds);
		CLCD_voidSendString("                    ");
		if (seconds >= 10) {
			Timer_voidStopActiveCall(TIMER_u8_TIMER0);
		}
		_delay_ms(50);
	}
}
