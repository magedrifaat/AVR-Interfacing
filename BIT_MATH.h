#define SET_BIT(BYTE, BIT_NO) BYTE |= (0x01 << (BIT_NO))
#define CLR_BIT(BYTE, BIT_NO) BYTE &= ~(0x01 << (BIT_NO))
#define TOGGLE_BIT(BYTE, BIT_NO) BYTE ^= (0x01 << (BIT_NO))
#define GET_BIT(BYTE, BIT_NO) (((BYTE)>>(BIT_NO)) & 0x01)
