/*
 * EXTI_program.c
 *
 *  Created on: 8 Sep 2021
 *      Author: Maged
 */

#include "../../Services/STD_Types.h"
#include "../../Services/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

void EXTI_voidInit(void) {
	if (EXTI_LINE_EN & EXTI_u8_LINE0) {
		EXTI_voidEnable(EXTI_u8_LINE0, EXTI_LINE_0_CONFIG);
	}

	if (EXTI_LINE_EN & EXTI_u8_LINE1) {
		EXTI_voidEnable(EXTI_u8_LINE1, EXTI_LINE_2_CONFIG);
	}

	if (EXTI_LINE_EN & EXTI_u8_LINE2) {
		EXTI_voidEnable(EXTI_u8_LINE2, EXTI_LINE_2_CONFIG);
	}
}

void EXTI_voidEnable(u8 Copy_u8Line, u8 Copy_u8SenseMode) {
	switch (Copy_u8Line) {
	case EXTI_u8_LINE0:
		switch (Copy_u8SenseMode) {
		case EXTI_u8_FALLING_EDGE:
			CLR_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;
		case EXTI_u8_RISING_EDGE:
			SET_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;
		case EXTI_u8_LOW_LEVEL:
			CLR_BIT(MCUCR, ISC00);
			CLR_BIT(MCUCR, ISC01);
			break;
		case EXTI_u8_ON_CHANGE:
			SET_BIT(MCUCR, ISC00);
			CLR_BIT(MCUCR, ISC01);
			break;
		}
		SET_BIT(GICR, INT0);
		break;
	case EXTI_u8_LINE1:
		switch (Copy_u8SenseMode) {
		case EXTI_u8_FALLING_EDGE:
			CLR_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
		case EXTI_u8_RISING_EDGE:
			SET_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
		case EXTI_u8_LOW_LEVEL:
			CLR_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
			break;
		case EXTI_u8_ON_CHANGE:
			SET_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
			break;
		}
		SET_BIT(GICR, INT1);
		break;
	case EXTI_u8_LINE2:
		switch (Copy_u8SenseMode) {
		case EXTI_u8_FALLING_EDGE:
			CLR_BIT(MCUCSR, ISC2);
			break;
		case EXTI_u8_RISING_EDGE:
			CLR_BIT(MCUCSR, ISC2);
			break;
		}
		SET_BIT(GICR, INT2);
		break;
	}
}

void EXTI_voidDisable(u8 Copy_u8Line) {
	switch (Copy_u8Line) {
	case EXTI_u8_LINE0:
		CLR_BIT(GICR, INT0);
		break;
	case EXTI_u8_LINE1:
		CLR_BIT(GICR, INT1);
		break;
	case EXTI_u8_LINE2:
		CLR_BIT(GICR, INT2);
		break;
	}
}

void EXTI_voidClearFlag(u8 Copy_u8Line) {
	switch (Copy_u8Line) {
	case EXTI_u8_LINE0:
		SET_BIT(GIFR, INTF0);
		break;
	case EXTI_u8_LINE1:
		SET_BIT(GIFR, INTF1);
		break;
	case EXTI_u8_LINE2:
		SET_BIT(GIFR, INTF2);
		break;
	}
}

void EXTI_voidCallBack(void (*Copy_pvoidCallBack)(void), u8 Copy_u8Line) {
	if (Copy_pvoidCallBack != NULL) {
		switch (Copy_u8Line) {
		case EXTI_u8_LINE0:
			EXTI_CallBack[0] = Copy_pvoidCallBack;
			break;
		case EXTI_u8_LINE1:
			EXTI_CallBack[1] = Copy_pvoidCallBack;
			break;
		case EXTI_u8_LINE2:
			EXTI_CallBack[2] = Copy_pvoidCallBack;
			break;
		}
	}
}

/* INT0 ISR */
ISR(INT0_vec) {
	if (EXTI_CallBack[0] != NULL) {
		EXTI_CallBack[0]();
	}
}

/* INT1 ISR */
ISR(INT1_vec) {
	if (EXTI_CallBack[1] != NULL) {
		EXTI_CallBack[1]();
	}
}

/* INT2 ISR */
ISR(INT2_vec) {
	if (EXTI_CallBack[2] != NULL) {
		EXTI_CallBack[2]();
	}
}
