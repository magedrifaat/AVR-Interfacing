/*
 * CLCD_interface.h
 *
 *  Created on: 30 Aug 2021
 *      Author: Maged
 */

#ifndef HAL_01_CLCD_CLCD_INTERFACE_H_
#define HAL_01_CLCD_CLCD_INTERFACE_H_

void CLCD_voidInit(void);

void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendString(s8 *str);

void CLCD_voidSendNumber(u64 Copy_u64Number);

#define CLCD_u8ROW_00        0
#define CLCD_u8ROW_01        1

#define CLCD_u8COLUMN_00     0
#define CLCD_u8COLUMN_01     1
#define CLCD_u8COLUMN_02     2
#define CLCD_u8COLUMN_03     3
#define CLCD_u8COLUMN_04     4
#define CLCD_u8COLUMN_05     5
#define CLCD_u8COLUMN_06     6
#define CLCD_u8COLUMN_07     7
#define CLCD_u8COLUMN_08     8
#define CLCD_u8COLUMN_09     9
#define CLCD_u8COLUMN_10     10
#define CLCD_u8COLUMN_11     11
#define CLCD_u8COLUMN_12     12
#define CLCD_u8COLUMN_13     13
#define CLCD_u8COLUMN_14     14
#define CLCD_u8COLUMN_15     15

void CLCD_voidSetCursor(u8 Copy_u8Row, u8 Copy_u8Column);

void CLCD_voidSetCustomChar(u8 Copy_u8CharIndex, u8 * Copy_u8CharData);

void CLCD_voidClearDisplay(void);

void CLCD_voidShowCursor(u8 Copy_u8Show);
void CLCD_voidBlinkCursor(u8 Copy_u8Blink);

#define CLCD_u8_SHIFT_LEFT    0
#define CLCD_u8_SHIFT_RIGHT   1

void CLCD_voidShiftDisplay(u8 Copy_u8Direction);

#endif /* HAL_01_CLCD_CLCD_INTERFACE_H_ */
