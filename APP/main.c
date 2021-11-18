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

#include "../MCAL/04-ADC/ADC_interface.h"


#include <util/delay.h>

volatile f32 seconds;

void tick(void) {
	seconds += 1;
}

int main(void) {
	seconds = 0;
	DIO_voidSetPinDirection(DIO_u8_PIN_C1, DIO_u8_OUTPUT);
	ADC_voidInit();
	CLCD_voidInit();
	Timer_voidInit();

	// Configure Tick Time
	Timer_Time_t time = {.u16Seconds=1, .u16MilliSeconds=0, .u16MicroSeconds=0};
	Timer_voidCallEvery(TIMER_u8_TIMER0, &time, tick);
	GIE_voidEnableInterrupts();

	// Configure Manual PWM Mode
	Timer_Config_t config = {.u8Mode=TIMER_u8_PWM_PC, .u8Prescalar=TIMER_u8_PRESCALAR_64};
	Timer_voidPostInit(TIMER_u8_TIMER2, &config);
	Timer_voidSetCompare(TIMER_u8_TIMER2, 0x7F);
	Timer_voidSetCompareOutputMode(TIMER_u8_TIMER2, TIMER_u8_COM_CLEAR);
	DIO_voidSetPinDirection(DIO_u8_PIN_D7, DIO_u8_OUTPUT);

	// Configure Automatic PWM Mode
	Timer_voidTimer1PWM(TIMER_u8_PWM_FAST, 1500, TIMER_u8_COM_CLEAR, 0.5, TIMER_u8_COM_CLEAR, 0.25);

	while (1) {
		Timer_voidSetTimer1PWMDuty(ADC_u16Read(ADC_u8_CHANNEL_0) / 1023.0, 0.25);
		Timer_voidSetCompare(TIMER_u8_TIMER2, ADC_u16Read(ADC_u8_CHANNEL_0) >> 2);

		CLCD_voidSetCursor(CLCD_u8ROW_00, CLCD_u8COLUMN_00);
		CLCD_voidSendNumber(seconds);
		CLCD_voidSendString("                    ");
		if (seconds >= 10) {
			Timer_voidStopActiveCall(TIMER_u8_TIMER0);
		}
		_delay_ms(50);
	}
}
