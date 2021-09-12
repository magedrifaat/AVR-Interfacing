/*
 * CLCD_config.h
 *
 *  Created on: 30 Aug 2021
 *      Author: Maged
 */

#ifndef HAL_01_CLCD_CLCD_CONFIG_H_
#define HAL_01_CLCD_CLCD_CONFIG_H_
/*
 * CLCD_DATA_PIN_D[0-7]  -> OPTIONS
 *
 * 1- DIO_u8_PIN_A[0-7]
 * 2- DIO_u8_PIN_B[0-7]
 * 3- DIO_u8_PIN_C[0-7]
 * 4- DIO_u8_PIN_D[0-7]
 */
#define CLCD_DATA_PIN_D0    DIO_u8_PIN_A0
#define CLCD_DATA_PIN_D1    DIO_u8_PIN_A1
#define CLCD_DATA_PIN_D2    DIO_u8_PIN_A2
#define CLCD_DATA_PIN_D3    DIO_u8_PIN_A3
#define CLCD_DATA_PIN_D4    DIO_u8_PIN_A4
#define CLCD_DATA_PIN_D5    DIO_u8_PIN_A5
#define CLCD_DATA_PIN_D6    DIO_u8_PIN_A6
#define CLCD_DATA_PIN_D7    DIO_u8_PIN_A7

/*
 * CLCD_RS, CLCD_EN, CLCD_RW  -> OPTIONS
 *
 * 1- DIO_u8_PIN_A[0-7]
 * 2- DIO_u8_PIN_B[0-7]
 * 3- DIO_u8_PIN_C[0-7]
 * 4- DIO_u8_PIN_D[0-7]
 */
#define CLCD_RS  DIO_u8_PIN_B0
#define CLCD_EN  DIO_u8_PIN_B1
//#define CLCD_RW  DIO_u8_PIN_B2

/*
 * CLCD_4BIT_MODE Preprocessor flag
 */
#define CLCD_4BIT_MODE

#endif /* HAL_01_CLCD_CLCD_CONFIG_H_ */
