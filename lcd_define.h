#ifndef LCD_DEFINE_H
#define LCD_DEFINE_H


#include "iodefine.h"
#include "my_define.h"

// LCD命令ビットの列挙または、マクロ定数==============
#define INST_DISPLAY_CLEAR 0x01
#define INST_CURSOR_HOME 0x02
#define INST_WRITE_CGRAM 0x40

typedef enum
{
	FUNC_SET_DL8 = 0x30,
	FUNC_SET_DL4 = 0x20,
	FUNC_SET_NUM2 = 0x28,
	FUNC_SET_NUM1 = 0x20,
	FUNC_SET_F5x11 = 0x24,
	FUNC_SET_F5x8 = 0x20,
	FUNC_SET_DEFAULT = ( FUNC_SET_DL4 | FUNC_SET_NUM2 | FUNC_SET_F5x8 )
}INST_FunctionBit;

typedef enum
{
	EN_MD_INC = 0x06,
	EN_MD_DEC = 0x04,
	EN_MD_SHIFT = 0x05,
	EN_MD_NON_SHIFT = 0x04
} INST_EntryModeBit;

typedef enum
{
	DISP_CNTL_DISPLAY_ON = 0x0C,
	DISP_CNTL_DISPLAY_OFF = 0x08,
	DISP_CNTL_DISP_CURSOR = 0x0A,
	DISP_CNTL_NON_DISP_CURSOR = 0x08,
	DISP_CNTL_CURSOR_BLINK_ON = 0x09,
	DISP_CNTL_CURSOR_BLINK_OFF = 0x08,
} INST_DispControlBit;

typedef enum
{
	CUSR_SHIFT_DISPLAY_SHIFT = 0x18,
	CUSR_SHIFT_CURSOR_MOVE = 0x10,
	CUSR_SHIFT_R_SHIFT = 0x14,
	CUSR_SHIFT_L_SHIFT = 0x10,
}INST_CursorShiftBit;
//============================================
//LCD関連の構造体アドレス
#define LCD PORTJ.PODR.BYTE
#define LCD_RS PORTJ.PODR.BIT.B1
#define LCD_E PORTJ.PODR.BIT.B3

#define LCD_PDR PORTJ.PDR.BYTE

#define LCD_DB PORTH.PODR.BYTE
#define LCD_DB_PDR PORTH.PDR.BYTE
#define LCD_RS_E_OUT 0x0A

#define LCD_LINE1_ST B7_SET
#define LCD_LINE2_ST 0xC0
//=============================================
//LCD初期化時の命令構造体
typedef struct
{
	u8 function_set;
	u8 display_control;
	u8 entry_mode;
} InitLcdDesc;

#endif // include guard LCD_DEFINE_H
