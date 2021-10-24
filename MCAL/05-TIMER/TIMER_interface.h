/*
 * TIMER_interface.h
 *
 *  Created on: 13 Oct 2021
 *      Author: Maged
 */

#ifndef MCAL_05_TIMER_TIMER_INTERFACE_H_
#define MCAL_05_TIMER_TIMER_INTERFACE_H_

#include "../../Services/STD_Types.h"

typedef struct
{
	u8 u8Mode;
	u8 u8Prescalar;
	u8 u8OVFInterruptState;
	u8 u8OCInterruptState;
}
Timer_Config_t;

typedef struct
{
	u16 u16Seconds;
	u16 u16MilliSeconds;
	u16 u16MicroSeconds;
}
Timer_Time_t;

#define TIMER_u8_TIMER0                           0
#define TIMER_u8_TIMER1                           1
#define TIMER_u8_TIMER2                           2

#define TIMER_u8_STOP                             0
#define TIMER_u8_NORMAL                           1
#define TIMER_u8_CTC                              2
#define TIMER_u8_PWM_FAST                         3
#define TIMER_u8_PWM_PHASECORRECT                 4
#define TIMER_u8_PWM_PHASEANDFREQUENCYCORRECT     5

#define TIMER_u8_PRESCALAR_1                      0
#define TIMER_u8_PRESCALAR_8                      1
#define TIMER_u8_PRESCALAR_32                     2
#define TIMER_u8_PRESCALAR_64                     3
#define TIMER_u8_PRESCALAR_128                    4
#define TIMER_u8_PRESCALAR_256                    5
#define TIMER_u8_PRESCALAR_1024                   6
#define TIMER_u8_PRESCALAR_FALLING                7
#define TIMER_u8_PRESCALAR_RISING                 8

#define TIMER_u8_INTERRUPT_DISABLED               0
#define TIMER_u8_INTERRUPT_ENABLED                1

void Timer_voidInit();
void Timer_voidPostInit(u8 Copy_u8Timer, Timer_Config_t * Copy_Config);

void Timer_voidSetCount(u8 Copy_u8Timer, u16 Copy_u16Value);
void Timer_voidSetCompare(u8 Copy_u8Timer, u16 Copy_u16Value);

void Timer_voidEnableOVFInterrupt(u8 Copy_u8Timer);
void Timer_voidDisableOVFInterrupt(u8 Copy_u8Timer);
void Timer_voidClearOVFFlag(u8 Copy_u8Timer);

void Timer_voidEnableCTCInterrupt(u8 Copy_u8Timer);
void Timer_voidDisableCTCInterrupt(u8 Copy_u8Timer);
void Timer_voidClearCTCFlag(u8 Copy_u8Timer);

void Timer_voidSetCallback(u8 Copy_u8Timer, u8 Copy_u8Mode, void (* Copy_pvoidCallBack) (void));

void Timer_voidCallEvery(u8 Copy_u8Timer, Timer_Time_t * time, void (* Copy_pvoidCallBack) (void));
void Timer_voidStopActiveCall(u8 Copy_u8Timer);

#endif /* MCAL_05_TIMER_TIMER_INTERFACE_H_ */
