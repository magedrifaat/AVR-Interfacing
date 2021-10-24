/*
 * TIMER_program.c
 *
 *  Created on: 13 Oct 2021
 *      Author: Maged
 */

#include "../../Services/STD_Types.h"
#include "../../Services/BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

void Timer_voidInit() {
	Timer_Config_t LOC_ConfigTimer0 = { .u8Mode = TIMER_u8_TIMER0_MODE,
			.u8Prescalar = TIMER_u8_TIMER0_PRESCALAR, .u8OVFInterruptState =
			TIMER_u8_TIMER0_OVF_INTERRUPT, .u8OCInterruptState =
			TIMER_u8_TIMER0_OC_INTERRUPT };
	Timer_voidPostInit(TIMER_u8_TIMER0, &LOC_ConfigTimer0);

	Timer_Config_t LOC_ConfigTimer1 = { .u8Mode = TIMER_u8_TIMER1_MODE,
			.u8Prescalar = TIMER_u8_TIMER1_PRESCALAR, .u8OVFInterruptState =
			TIMER_u8_TIMER1_OVF_INTERRUPT, .u8OCInterruptState =
			TIMER_u8_TIMER1_OC_INTERRUPT };
	Timer_voidPostInit(TIMER_u8_TIMER1, &LOC_ConfigTimer1);

	Timer_Config_t LOC_ConfigTimer2 = { .u8Mode = TIMER_u8_TIMER2_MODE,
			.u8Prescalar = TIMER_u8_TIMER2_PRESCALAR, .u8OVFInterruptState =
			TIMER_u8_TIMER2_OVF_INTERRUPT, .u8OCInterruptState =
			TIMER_u8_TIMER2_OC_INTERRUPT };
	Timer_voidPostInit(TIMER_u8_TIMER2, &LOC_ConfigTimer2);
}

void Timer_voidPostInit(u8 Copy_u8Timer, Timer_Config_t *Copy_Config) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		switch (Copy_Config->u8Mode) {
		case TIMER_u8_STOP:
			CLR_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
			break;
		case TIMER_u8_NORMAL:
			CLR_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
			Timer_voidSetPrescalar(Copy_u8Timer, Copy_Config->u8Prescalar);
			break;
		case TIMER_u8_CTC:
			CLR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			Timer_voidSetPrescalar(Copy_u8Timer, Copy_Config->u8Prescalar);
			break;
		}
		if (Copy_Config->u8OVFInterruptState == TIMER_u8_INTERRUPT_ENABLED) {
			Timer_voidEnableOVFInterrupt(Copy_u8Timer);
		} else {
			Timer_voidDisableOVFInterrupt(Copy_u8Timer);
		}
		if (Copy_Config->u8OCInterruptState == TIMER_u8_INTERRUPT_ENABLED) {
			Timer_voidEnableCTCInterrupt(Copy_u8Timer);
		} else {
			Timer_voidDisableCTCInterrupt(Copy_u8Timer);
		}
		break;
	case TIMER_u8_TIMER1:
		switch (Copy_Config->u8Mode) {
		case TIMER_u8_STOP:
			CLR_BIT(TCCR1B, CS10);
			CLR_BIT(TCCR1B, CS11);
			CLR_BIT(TCCR1B, CS12);
			break;
		case TIMER_u8_NORMAL:
			CLR_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			Timer_voidSetPrescalar(Copy_u8Timer, Copy_Config->u8Prescalar);
			break;
		case TIMER_u8_CTC:
			CLR_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			Timer_voidSetPrescalar(Copy_u8Timer, Copy_Config->u8Prescalar);
			break;
		}
		if (Copy_Config->u8OVFInterruptState == TIMER_u8_INTERRUPT_ENABLED) {
			Timer_voidEnableOVFInterrupt(Copy_u8Timer);
		} else {
			Timer_voidDisableOVFInterrupt(Copy_u8Timer);
		}
		if (Copy_Config->u8OCInterruptState == TIMER_u8_INTERRUPT_ENABLED) {
			Timer_voidEnableCTCInterrupt(Copy_u8Timer);
		} else {
			Timer_voidDisableCTCInterrupt(Copy_u8Timer);
		}
		break;
	case TIMER_u8_TIMER2:
		switch (Copy_Config->u8Mode) {
		case TIMER_u8_STOP:
			CLR_BIT(TCCR2, CS20);
			CLR_BIT(TCCR2, CS21);
			CLR_BIT(TCCR2, CS22);
			break;
		case TIMER_u8_NORMAL:
			CLR_BIT(TCCR2, WGM20);
			CLR_BIT(TCCR2, WGM21);
			Timer_voidSetPrescalar(Copy_u8Timer, Copy_Config->u8Prescalar);
			break;
		case TIMER_u8_CTC:
			CLR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);
			Timer_voidSetPrescalar(Copy_u8Timer, Copy_Config->u8Prescalar);
			break;
		}
		if (Copy_Config->u8OVFInterruptState == TIMER_u8_INTERRUPT_ENABLED) {
			Timer_voidEnableOVFInterrupt(Copy_u8Timer);
		} else {
			Timer_voidDisableOVFInterrupt(Copy_u8Timer);
		}
		if (Copy_Config->u8OVFInterruptState == TIMER_u8_INTERRUPT_ENABLED) {
			Timer_voidDisableCTCInterrupt(Copy_u8Timer);
		} else {
			Timer_voidDisableCTCInterrupt(Copy_u8Timer);
		}
		break;
	}
}

void Timer_voidSetPrescalar(u8 Copy_u8Timer, u8 Copy_u8Prescalar) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_1
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_64
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_1024
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_RISING) {
			SET_BIT(TCCR0, CS00);
		} else {
			CLR_BIT(TCCR0, CS00);
		}

		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_8
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_64
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_FALLING
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_RISING) {
			SET_BIT(TCCR0, CS01);
		} else {
			CLR_BIT(TCCR0, CS01);
		}

		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_256
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_1024
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_FALLING
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_RISING) {
			SET_BIT(TCCR0, CS02);
		} else {
			CLR_BIT(TCCR0, CS02);
		}
		break;
	case TIMER_u8_TIMER1:
		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_1
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_64
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_1024
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_RISING) {
			SET_BIT(TCCR1B, CS10);
		} else {
			CLR_BIT(TCCR1B, CS10);
		}

		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_8
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_64
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_FALLING
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_RISING) {
			SET_BIT(TCCR1B, CS11);
		} else {
			CLR_BIT(TCCR1B, CS11);
		}

		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_256
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_1024
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_FALLING
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_RISING) {
			SET_BIT(TCCR1B, CS12);
		} else {
			CLR_BIT(TCCR1B, CS12);
		}
		break;
	case TIMER_u8_TIMER2:
		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_1
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_32
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_128
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_1024) {
			SET_BIT(TCCR2, CS20);
		} else {
			CLR_BIT(TCCR2, CS20);
		}

		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_8
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_32
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_256
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_1024) {
			SET_BIT(TCCR2, CS21);
		} else {
			CLR_BIT(TCCR2, CS21);
		}

		if (Copy_u8Prescalar == TIMER_u8_PRESCALAR_64
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_128
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_256
				|| Copy_u8Prescalar == TIMER_u8_PRESCALAR_1024) {
			SET_BIT(TCCR2, CS22);
		} else {
			CLR_BIT(TCCR2, CS22);
		}
		break;
	}
}

void Timer_voidSetCount(u8 Copy_u8Timer, u16 Copy_u16Value) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		TCNT0 = (u8) Copy_u16Value;
		break;
	case TIMER_u8_TIMER1:
		TCNT1L = Copy_u16Value & 0xFF;
		TCNT1H = Copy_u16Value >> 8;
		break;
	case TIMER_u8_TIMER2:
		TCNT2 = (u8) Copy_u16Value;
		break;
	}
}

void Timer_voidSetCompare(u8 Copy_u8Timer, u16 Copy_u16Value) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		OCR0 = (u8) Copy_u16Value;
		break;
	case TIMER_u8_TIMER1:
		OCR1AL = Copy_u16Value & 0xFF;
		OCR1AH = Copy_u16Value >> 8;
		break;
	case TIMER_u8_TIMER2:
		OCR2 = (u8) Copy_u16Value;
		break;
	}
}

void Timer_voidEnableOVFInterrupt(u8 Copy_u8Timer) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		SET_BIT(TIMSK, TOIE0);
		break;
	case TIMER_u8_TIMER1:
		SET_BIT(TIMSK, TOIE1);
		break;
	case TIMER_u8_TIMER2:
		SET_BIT(TIMSK, TOIE2);
		break;
	}
}

void Timer_voidDisableOVFInterrupt(u8 Copy_u8Timer) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		CLR_BIT(TIMSK, TOIE0);
		break;
	case TIMER_u8_TIMER1:
		CLR_BIT(TIMSK, TOIE1);
		break;
	case TIMER_u8_TIMER2:
		CLR_BIT(TIMSK, TOIE2);
		break;
	}
}

void Timer_voidClearOVFFlag(u8 Copy_u8Timer) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		SET_BIT(TIFR, TOV0);
		break;
	case TIMER_u8_TIMER1:
		SET_BIT(TIFR, TOV1);
		break;
	case TIMER_u8_TIMER2:
		SET_BIT(TIFR, TOV2);
		break;
	}
}

void Timer_voidEnableCTCInterrupt(u8 Copy_u8Timer) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		SET_BIT(TIMSK, OCIE0);
		break;
	case TIMER_u8_TIMER1:
		SET_BIT(TIMSK, OCIE1A);
		break;
	case TIMER_u8_TIMER2:
		SET_BIT(TIMSK, OCIE2);
		break;
	}
}

void Timer_voidDisableCTCInterrupt(u8 Copy_u8Timer) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		CLR_BIT(TIMSK, OCIE0);
		break;
	case TIMER_u8_TIMER1:
		CLR_BIT(TIMSK, OCIE1A);
		break;
	case TIMER_u8_TIMER2:
		CLR_BIT(TIMSK, OCIE2);
		break;
	}
}

void Timer_voidClearCTCFlag(u8 Copy_u8Timer) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		SET_BIT(TIFR, OCF0);
		break;
	case TIMER_u8_TIMER1:
		SET_BIT(TIFR, OCF1A);
		break;
	case TIMER_u8_TIMER2:
		SET_BIT(TIFR, OCF2);
		break;
	}
}

void Timer_voidSetCallback(u8 Copy_u8Timer, u8 Copy_u8Mode,
		void (*Copy_pvoidCallBack)(void)) {
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		switch (Copy_u8Mode) {
		case TIMER_u8_CTC:
			Timer_pvoidCTCCallbacks[0] = Copy_pvoidCallBack;
			break;
		case TIMER_u8_NORMAL:
			Timer_pvoidOVFCallbacks[0] = Copy_pvoidCallBack;
			break;
		}
		break;
	case TIMER_u8_TIMER1:
		switch (Copy_u8Mode) {
		case TIMER_u8_CTC:
			Timer_pvoidCTCCallbacks[1] = Copy_pvoidCallBack;
			break;
		case TIMER_u8_NORMAL:
			Timer_pvoidOVFCallbacks[1] = Copy_pvoidCallBack;
			break;
		}
		break;
	case TIMER_u8_TIMER2:
		switch (Copy_u8Mode) {
		case TIMER_u8_CTC:
			Timer_pvoidCTCCallbacks[2] = Copy_pvoidCallBack;
			break;
		case TIMER_u8_NORMAL:
			Timer_pvoidOVFCallbacks[2] = Copy_pvoidCallBack;
			break;
		}
		break;
	}
}

void Timer_voidCallEvery(u8 Copy_u8Timer, Timer_Time_t *Copy_Time,
		void (*Copy_pvoidCallBack)(void)) {
	if (Copy_u8Timer != TIMER_u8_TIMER0 && Copy_u8Timer != TIMER_u8_TIMER1
			&& Copy_u8Timer != TIMER_u8_TIMER2) {
		return;
	}

	Timer_voidDisableOVFInterrupt(Copy_u8Timer);
	Timer_voidClearOVFFlag(Copy_u8Timer);
	Timer_voidDisableCTCInterrupt(Copy_u8Timer);
	Timer_voidClearCTCFlag(Copy_u8Timer);

	f32 LOC_f32Time = Copy_Time->u16Seconds
			+ Copy_Time->u16MilliSeconds / 1000.0
			+ Copy_Time->u16MicroSeconds / 1000000.0;
	f32 LOC_f32CpuTicks = F_CPU * LOC_f32Time;

	u16 LOC_u16Prescalar;
	u32 LOC_u32PrescaledTicks, LOC_u32OverflowCount;
	Timer_Config_t LOC_config;
	switch (Copy_u8Timer) {
	case TIMER_u8_TIMER0:
		LOC_u32OverflowCount = LOC_f32CpuTicks / 0x100;
		if (LOC_u32OverflowCount == 0) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_1;
			LOC_u16Prescalar = 1;
		} else if (LOC_u32OverflowCount < 8) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_8;
			LOC_u16Prescalar = 8;
		} else if (LOC_u32OverflowCount < 64) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_64;
			LOC_u16Prescalar = 64;
		} else if (LOC_u32OverflowCount < 256) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_256;
			LOC_u16Prescalar = 256;
		} else {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_1024;
			LOC_u16Prescalar = 1024;
		}
		LOC_u32PrescaledTicks = LOC_f32CpuTicks / LOC_u16Prescalar + 0.5;
		Timer_u16CountStart[0] = (0x100 - (LOC_u32PrescaledTicks % 0x100))
				% 0x100;
		Timer_u32SWCounter[0] = LOC_u32PrescaledTicks / 0x100;
		if (LOC_u32PrescaledTicks % 0x100 != 0) {
			Timer_u32SWCounter[0]++;
		}
		break;
	case TIMER_u8_TIMER1:
		LOC_u32OverflowCount = LOC_f32CpuTicks / 0x10000;
		if (LOC_u32OverflowCount == 0) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_1;
			LOC_u16Prescalar = 1;
		} else if (LOC_u32OverflowCount < 8) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_8;
			LOC_u16Prescalar = 8;
		} else if (LOC_u32OverflowCount < 64) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_64;
			LOC_u16Prescalar = 64;
		} else if (LOC_u32OverflowCount < 256) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_256;
			LOC_u16Prescalar = 256;
		} else {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_1024;
			LOC_u16Prescalar = 1024;
		}
		LOC_u32PrescaledTicks = LOC_f32CpuTicks / LOC_u16Prescalar + 0.5;
		Timer_u16CountStart[1] = (0x10000 - (LOC_u32PrescaledTicks % 0x10000))
				% 0x10000;
		Timer_u32SWCounter[1] = LOC_u32PrescaledTicks / 0x10000;
		if (LOC_u32PrescaledTicks % 0x10000 != 0) {
			Timer_u32SWCounter[1]++;
		}
		break;
	case TIMER_u8_TIMER2:
		LOC_u32OverflowCount = LOC_f32CpuTicks / 0x100;
		if (LOC_u32OverflowCount == 0) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_1;
			LOC_u16Prescalar = 1;
		} else if (LOC_u32OverflowCount < 8) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_8;
			LOC_u16Prescalar = 8;
		} else if (LOC_u32OverflowCount < 32) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_32;
			LOC_u16Prescalar = 32;
		} else if (LOC_u32OverflowCount < 64) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_64;
			LOC_u16Prescalar = 64;
		} else if (LOC_u32OverflowCount < 128) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_128;
			LOC_u16Prescalar = 128;
		} else if (LOC_u32OverflowCount < 256) {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_256;
			LOC_u16Prescalar = 256;
		} else {
			LOC_config.u8Prescalar = TIMER_u8_PRESCALAR_1024;
			LOC_u16Prescalar = 1024;
		}
		LOC_u32PrescaledTicks = LOC_f32CpuTicks / LOC_u16Prescalar + 0.5;
		Timer_u16CountStart[2] = (0x100 - (LOC_u32PrescaledTicks % 0x100))
				% 0x100;
		Timer_u32SWCounter[2] = LOC_u32PrescaledTicks / 0x100;
		if (LOC_u32PrescaledTicks % 0x100 != 0) {
			Timer_u32SWCounter[2]++;
		}
		break;
	}

	LOC_config.u8Mode = TIMER_u8_NORMAL;
	LOC_config.u8OVFInterruptState = TIMER_u8_INTERRUPT_DISABLED;
	LOC_config.u8OCInterruptState = TIMER_u8_INTERRUPT_DISABLED;
	Timer_voidPostInit(Copy_u8Timer, &LOC_config);
	Timer_voidSetCount(Copy_u8Timer, Timer_u16CountStart[Copy_u8Timer]);
	Timer_u32SWIterator[Copy_u8Timer] = 0;
	Timer_pvoidWrappedCallBack[Copy_u8Timer] = Copy_pvoidCallBack;
	Timer_voidSetCallback(TIMER_u8_TIMER0, TIMER_u8_NORMAL,
			Timer_pvoidCallBackWrapper[Copy_u8Timer]);
	Timer_voidEnableOVFInterrupt(Copy_u8Timer);
}

void Timer_voidStopActiveCall(u8 Copy_u8Timer) {
	if (Copy_u8Timer != TIMER_u8_TIMER0 && Copy_u8Timer != TIMER_u8_TIMER1
			&& Copy_u8Timer != TIMER_u8_TIMER2) {
		return;
	}

	Timer_voidDisableOVFInterrupt(Copy_u8Timer);
	Timer_voidDisableCTCInterrupt(Copy_u8Timer);
	Timer_voidClearOVFFlag(Copy_u8Timer);
	Timer_voidClearCTCFlag(Copy_u8Timer);

	Timer_pvoidOVFCallbacks[Copy_u8Timer] = NULL;
	Timer_pvoidWrappedCallBack[Copy_u8Timer] = NULL;

	Timer_Config_t LOC_config = { .u8Mode = TIMER_u8_STOP,
			.u8OVFInterruptState = TIMER_u8_INTERRUPT_DISABLED,
			.u8OCInterruptState = TIMER_u8_INTERRUPT_DISABLED };
	Timer_voidPostInit(Copy_u8Timer, &LOC_config);
}

void Timer_voidTimer0Wrapper(void) {
	Timer_u32SWIterator[0]++;
	if (Timer_u32SWIterator[0] >= Timer_u32SWCounter[0]) {
		TCNT0 = Timer_u16CountStart[0];
		Timer_u32SWIterator[0] = 0;
		if (Timer_pvoidWrappedCallBack[0] != NULL) {
			Timer_pvoidWrappedCallBack[0]();
		}
	}
}

void Timer_voidTimer1Wrapper(void) {
	Timer_u32SWIterator[1]++;
	if (Timer_u32SWIterator[1] >= Timer_u32SWCounter[1]) {
		if (Timer_pvoidWrappedCallBack[1] != NULL) {
			Timer_pvoidWrappedCallBack[1]();
		}
		Timer_u32SWIterator[1] = 0;
		TCNT1L = Timer_u16CountStart[1] % 0xFF;
		TCNT1H = Timer_u16CountStart[1] >> 8;
	}
}

void Timer_voidTimer2Wrapper(void) {
	Timer_u32SWIterator[2]++;
	if (Timer_u32SWIterator[2] >= Timer_u32SWCounter[2]) {
		if (Timer_pvoidWrappedCallBack[2] != NULL) {
			Timer_pvoidWrappedCallBack[2]();
		}
		Timer_u32SWIterator[2] = 0;
		TCNT2 = Timer_u16CountStart[2];
	}
}

ISR(TIMER0_OVF_vec) {
	if (Timer_pvoidOVFCallbacks[0] != NULL) {
		Timer_pvoidOVFCallbacks[0]();
	}
}

ISR(TIMER1_OVF_vec) {
	if (Timer_pvoidOVFCallbacks[1] != NULL) {
		Timer_pvoidOVFCallbacks[1]();
	}
}

ISR(TIMER2_OVF_vec) {
	if (Timer_pvoidOVFCallbacks[2] != NULL) {
		Timer_pvoidOVFCallbacks[2]();
	}
}

ISR(TIMER0_COMP_vec) {
	if (Timer_pvoidCTCCallbacks[0] != NULL) {
		Timer_pvoidCTCCallbacks[0]();
	}
}

ISR(TIMER1_COMPA_vec) {
	if (Timer_pvoidCTCCallbacks[1] != NULL) {
		Timer_pvoidCTCCallbacks[1]();
	}
}

ISR(TIMER2_COMP_vec) {
	if (Timer_pvoidCTCCallbacks[2] != NULL) {
		Timer_pvoidCTCCallbacks[2]();
	}
}
