/*
 * EXTI_private.h
 *
 *  Created on: 8 Sep 2021
 *      Author: Maged
 */

#ifndef MCAL_03_EXTI_EXTI_PRIVATE_H_
#define MCAL_03_EXTI_EXTI_PRIVATE_H_

#define MCUCR  *((volatile u8 *) 0x55)
#define MCUCSR *((volatile u8 *) 0x54)
#define GICR   *((volatile u8 *) 0x5B)
#define GIFR   *((volatile u8 *) 0x5A)

#define ISC00    0
#define ISC01    1
#define ISC10    2
#define ISC11    3

#define ISC2     6

#define INT0     6
#define INT1     7
#define INT2     5

#define INTF0    6
#define INTF1    7
#define INTF2    5

#define INT0_vec 1
#define INT1_vec 2
#define INT2_vec 3

#define CONCAT(A, B) A ## B
#define ISR(VEC_NUM) void CONCAT(__vector_, VEC_NUM)(void)
ISR(INT0_vec)  __attribute__ ((signal));
ISR(INT1_vec) __attribute__ ((signal));
ISR(INT2_vec) __attribute__ ((signal));


#define NULL    0

void (*EXTI_CallBack[3]) (void) = {NULL};

#endif /* MCAL_03_EXTI_EXTI_PRIVATE_H_ */
