/*
 * EXTI_config.h
 *
 *  Created on: 8 Sep 2021
 *      Author: Maged
 */

#ifndef MCAL_03_EXTI_EXTI_CONFIG_H_
#define MCAL_03_EXTI_EXTI_CONFIG_H_

/*
 * OPTIONS:
 * OR all required lines
 *
 */
#define EXTI_LINE_EN    EXTI_u8_LINE1

/*
 * EXTI_LINE_[i]_CONFIG -> OPTIONS:
 * -> EXTI_u8_FALLING_EDGE
 * -> EXTI_u8_RISING_EDGE
 * -> EXTI_u8_LOW_LEVEL
 * -> EXTI_u8_ON_CHANGE
 */
#define EXTI_LINE_0_CONFIG  EXTI_u8_FALLING_EDGE
#define EXTI_LINE_1_CONFIG  EXTI_u8_FALLING_EDGE
#define EXTI_LINE_2_CONFIG  EXTI_u8_FALLING_EDGE

#endif /* MCAL_03_EXTI_EXTI_CONFIG_H_ */
