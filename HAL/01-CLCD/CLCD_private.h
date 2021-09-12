/*
 * CLCD_private.h
 *
 *  Created on: 30 Aug 2021
 *      Author: Maged
 */

#ifndef HAL_01_CLCD_CLCD_PRIVATE_H_
#define HAL_01_CLCD_CLCD_PRIVATE_H_

void CLCD_voidSendByte(u8 Copy_u8Byte);
void CLCD_voidSendTwoNibbles(u8 Copy_u8Byte);

#define CLCD_u8_4BIT_FUNCTION_SET_H  0b00000010
#define CLCD_u8_4BIT_FUNCTION_SET_L  0b00001000
#define CLCD_u8_8BIT_FUNCTION_SET    0b00111100
#define CLCD_u8_DISPLAY_CONTROL      0b00001110
#define CLCD_u8_DISPLAY_CLEAR        0b00000001
#define CLCD_u8_ENTRY_MODE_SET       0b00000110
#define CLCD_u8_CLEAR_DISPLAY        0b00000001
#define CLCD_u8_DISPLAY_SHIFT        0b00011000

#define CURSOR_BIT    1
#define BLINK_BIT     0

#define CLCD_u8_DDRAM_OFFSET    0x80
#define CLCD_u8_ROW2_OFFSET     0x40

#define CLCD_u8_CGRAM_OFFSET    0x40

#ifdef CLCD_4BIT_MODE
	u8 CLCD_u8DataPins[] = { CLCD_DATA_PIN_D4, CLCD_DATA_PIN_D5, CLCD_DATA_PIN_D6, CLCD_DATA_PIN_D7 };
#else
	u8 CLCD_u8DataPins[] = { CLCD_DATA_PIN_D0, CLCD_DATA_PIN_D1, CLCD_DATA_PIN_D2, CLCD_DATA_PIN_D3,
							CLCD_DATA_PIN_D4, CLCD_DATA_PIN_D5, CLCD_DATA_PIN_D6, CLCD_DATA_PIN_D7 };
#endif


#endif /* HAL_01_CLCD_CLCD_PRIVATE_H_ */