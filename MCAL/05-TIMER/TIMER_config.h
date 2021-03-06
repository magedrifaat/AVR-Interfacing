/*
 * TIMER_config.h
 *
 *  Created on: 13 Oct 2021
 *      Author: Maged
 */

#ifndef MCAL_05_TIMER_TIMER_CONFIG_H_
#define MCAL_05_TIMER_TIMER_CONFIG_H_

/*********** TIMER 0 CONFIGURATIONS ***********/

/* Mode of operation for Timer 0
 * Options:
 * 	- TIMER_u8_STOP
 * 	- TIMER_u8_NORMAL
 * 	- TIMER_u8_CTC
 * 	- TIMER_u8_PWM_FAST
 * 	- TIMER_u8_PWM_PC
 */
#define TIMER_u8_TIMER0_MODE  TIMER_u8_STOP

/* Compare Output Mode for Timer 0
 * Options:
 * 	- TIMER_u8_COM_DISABLE
 * 	- TIMER_u8_COM_TOGGLE
 * 	- TIMER_u8_COM_CLEAR
 * 	- TIMER_u8_COM_SET
 */
#define TIMER_u8_TIMER0_COM    TIMER_u8_COM_DISABLE

/*
 * Prescalar for Timer 0
 * Options:
 * 	- TIMER_u8_PRESCALAR_1
 * 	- TIMER_u8_PRESCALAR_8
 * 	- TIMER_u8_PRESCALAR_64
 * 	- TIMER_u8_PRESCALAR_256
 * 	- TIMER_u8_PRESCALAR_1024
 * 	- TIMER_u8_PRESCALAR_RISING
 * 	- TIMER_u8_PRESCALAR_FALLING
 */
#define TIMER_u8_TIMER0_PRESCALAR   TIMER_u8_PRESCALAR_1

/*
 * Interrupt State for Timer 0
 * Options:
 * 	- TIMER_u8_INTERRUPT_ENABLED
 * 	- TIMER_u8_INTERRUPT_DISABLED
 */
#define TIMER_u8_TIMER0_OVF_INTERRUPT   TIMER_u8_INTERRUPT_DISABLED
#define TIMER_u8_TIMER0_OC_INTERRUPT    TIMER_u8_INTERRUPT_DISABLED


/*********** TIMER 1 CONFIGURATIONS ***********/

/* Mode of operation for Timer 1
 * Options:
 * 	- TIMER_u8_STOP
 * 	- TIMER_u8_NORMAL
 * 	- TIMER_u8_CTC
 * 	- TIMER_u8_PWM_FAST
 * 	- TIMER_u8_PWM_PC
 * 	- TIMER_u8_PWM_PFC
 */
#define TIMER_u8_TIMER1_MODE  TIMER_u8_STOP

/* Compare Output Mode for Timer 1
 * Options:
 * 	- TIMER_u8_COM_DISABLE
 * 	- TIMER_u8_COM_TOGGLE
 * 	- TIMER_u8_COM_CLEAR
 * 	- TIMER_u8_COM_SET
 */
#define TIMER_u8_TIMER1_COM    TIMER_u8_COM_DISABLE

/*
 * Prescalar for Timer 1
 * Options:
 * 	- TIMER_u8_PRESCALAR_1
 * 	- TIMER_u8_PRESCALAR_8
 * 	- TIMER_u8_PRESCALAR_64
 * 	- TIMER_u8_PRESCALAR_256
 * 	- TIMER_u8_PRESCALAR_1024
 * 	- TIMER_u8_PRESCALAR_RISING
 * 	- TIMER_u8_PRESCALAR_FALLING
 */
#define TIMER_u8_TIMER1_PRESCALAR   TIMER_u8_PRESCALAR_1

/*
 * Interrupt State for Timer 1
 * Options:
 * 	- TIMER_u8_INTERRUPT_ENABLED
 * 	- TIMER_u8_INTERRUPT_DISABLED
 */
#define TIMER_u8_TIMER1_OVF_INTERRUPT   TIMER_u8_INTERRUPT_DISABLED
#define TIMER_u8_TIMER1_OC_INTERRUPT    TIMER_u8_INTERRUPT_DISABLED


/*********** TIMER 2 CONFIGURATIONS ***********/

/* Mode of operation for Timer 2
 * Options:
 * 	- TIMER_u8_STOP
 * 	- TIMER_u8_NORMAL
 * 	- TIMER_u8_CTC
 * 	- TIMER_u8_PWM_FAST
 * 	- TIMER_u8_PWM_PC
 */
#define TIMER_u8_TIMER2_MODE  TIMER_u8_STOP

/* Compare Output Mode for Timer 2
 * Options:
 * 	- TIMER_u8_COM_DISABLE
 * 	- TIMER_u8_COM_TOGGLE
 * 	- TIMER_u8_COM_CLEAR
 * 	- TIMER_u8_COM_SET
 */
#define TIMER_u8_TIMER2_COM    TIMER_u8_COM_DISABLE

/*
 * Prescalar for Timer 2
 * Options:
 * 	- TIMER_u8_PRESCALAR_1
 * 	- TIMER_u8_PRESCALAR_8
 * 	- TIMER_u8_PRESCALAR_32
 * 	- TIMER_u8_PRESCALAR_64
 * 	- TIMER_u8_PRESCALAR_128
 * 	- TIMER_u8_PRESCALAR_256
 * 	- TIMER_u8_PRESCALAR_1024
 */
#define TIMER_u8_TIMER2_PRESCALAR   TIMER_u8_PRESCALAR_1

/*
 * Interrupt State for Timer 2
 * Options:
 * 	- TIMER_u8_INTERRUPT_ENABLED
 * 	- TIMER_u8_INTERRUPT_DISABLED
 */
#define TIMER_u8_TIMER2_OVF_INTERRUPT   TIMER_u8_INTERRUPT_DISABLED
#define TIMER_u8_TIMER2_OC_INTERRUPT    TIMER_u8_INTERRUPT_DISABLED

#endif /* MCAL_05_TIMER_TIMER_CONFIG_H_ */
