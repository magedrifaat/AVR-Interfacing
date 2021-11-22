/*
 * TIMER_private.h
 *
 *  Created on: 13 Oct 2021
 *      Author: Maged
 */

#ifndef MCAL_05_TIMER_TIMER_PRIVATE_H_
#define MCAL_05_TIMER_TIMER_PRIVATE_H_

#define TCCR0     *((volatile u8 *) 0x53)
#define TCNT0     *((volatile u8 *) 0x52)
#define OCR0      *((volatile u8 *) 0x5C)
#define WGM00     6
#define WGM01     3
#define COM00     4
#define COM01     5
#define CS00      0
#define CS01      1
#define CS02      2

#define TCCR1A    *((volatile u8 *) 0x4F)
#define TCCR1B    *((volatile u8 *) 0x4E)
#define TCNT1H    *((volatile u8 *) 0x4D)
#define TCNT1L    *((volatile u8 *) 0x4C)
#define OCR1AH    *((volatile u8 *) 0x4B)
#define OCR1AL    *((volatile u8 *) 0x4A)
#define OCR1BH    *((volatile u8 *) 0x49)
#define OCR1BL    *((volatile u8 *) 0x48)
#define ICR1H     *((volatile u8 *) 0x47)
#define ICR1L     *((volatile u8 *) 0x46)
#define COM1A0    6
#define COM1A1    7
#define COM1B0    4
#define COM1B1    5
#define WGM10     0
#define WGM11     1
#define WGM12     3
#define WGM13     4
#define ICSES1    6
#define CS10      0
#define CS11      1
#define CS12      2


#define TCCR2     *((volatile u8 *) 0x45)
#define TCNT2     *((volatile u8 *) 0x44)
#define OCR2      *((volatile u8 *) 0x43)
#define WGM20     6
#define WGM21     3
#define COM20     4
#define COM21     5
#define CS20      0
#define CS21      1
#define CS22      2


#define TIMSK     *((volatile u8 *) 0x59)
#define TIFR      *((volatile u8 *) 0x58)
#define TOIE0     0
#define OCIE0     1
#define TOIE1     2
#define OCIE1B    3
#define OCIE1A    4
#define TICIE1    5
#define TOIE2     6
#define OCIE2     7
#define TOV0      0
#define OCF0      1
#define TOV1      2
#define OCF1B     3
#define OCF1A     4
#define ICF1      5
#define TOV2      6
#define OCF2      7

#define TIMER0_OVF_vec 11
#define TIMER0_COMP_vec 10
#define TIMER1_OVF_vec 9
#define TIMER1_COMPA_vec 7
#define TIMER2_OVF_vec 5
#define TIMER2_COMP_vec 4

#define CONCAT(A, B) A ## B
#define ISR(VEC_NUM) void CONCAT(__vector_, VEC_NUM)(void)
ISR(TIMER0_OVF_vec)  __attribute__ ((signal));
ISR(TIMER0_COMP_vec) __attribute__ ((signal));
ISR(TIMER1_OVF_vec)  __attribute__ ((signal));
ISR(TIMER1_COMPA_vec) __attribute__ ((signal));
ISR(TIMER2_OVF_vec)  __attribute__ ((signal));
ISR(TIMER2_COMP_vec) __attribute__ ((signal));

void Timer_voidSetPrescalar(u8 Copy_u8Timer, u8 Copy_u8Prescalar);

#define NULL 0
void (* volatile Timer_pvoidCTCCallbacks[3]) (void) = {NULL, NULL, NULL};
void (* volatile Timer_pvoidOVFCallbacks[3]) (void) = {NULL, NULL, NULL};

volatile u32 Timer_u16CountStart[3] = {0, 0, 0};
volatile u32 Timer_u32SWCounter[3] = {0, 0, 0};
volatile u32 Timer_u32SWIterator[3] = {0, 0, 0};
void Timer_voidTimer0Wrapper(void);
void Timer_voidTimer1Wrapper(void);
void Timer_voidTimer2Wrapper(void);
void (* const Timer_pvoidCallBackWrapper[3]) (void) = {Timer_voidTimer0Wrapper, Timer_voidTimer1Wrapper, Timer_voidTimer2Wrapper};
void (* volatile Timer_pvoidWrappedCallBack[3]) (void) = {NULL, NULL, NULL};


#endif /* MCAL_05_TIMER_TIMER_PRIVATE_H_ */
