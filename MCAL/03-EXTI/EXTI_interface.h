/*
 * EXTI_interface.h
 *
 *  Created on: 8 Sep 2021
 *      Author: Maged
 */

#ifndef MCAL_03_EXTI_EXTI_INTERFACE_H_
#define MCAL_03_EXTI_EXTI_INTERFACE_H_

#define EXTI_u8_LINE0     1
#define EXTI_u8_LINE1     2
#define EXTI_u8_LINE2     4

#define EXTI_u8_FALLING_EDGE     0
#define EXTI_u8_RISING_EDGE      1
#define EXTI_u8_LOW_LEVEL        2
#define EXTI_u8_ON_CHANGE        3

void EXTI_voidInit(void);
void EXTI_voidEnable(u8 Copy_u8Line, u8 Copy_u8SenseMode);
void EXTI_voidDisable(u8 Copy_u8Line);

void EXTI_voidClearFlag(u8 Copy_u8Line);

void EXTI_voidCallBack(void (*Copy_pvoidCallBack) (void), u8 Copy_u8Line);

#endif /* MCAL_03_EXTI_EXTI_INTERFACE_H_ */
