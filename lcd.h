#ifndef LCD_H
#define LCD_H

#include "lcd_define.h"

void writeCGRAM(u8 pos, const u8 pattern[8]);
void initLCD( const InitLcdDesc desc );
void putLCD(const u8 row, const u8 pos, const u8 ch);
void printLCD(const u8 row, const u8 pos, const char* string);
void printNUM3_LCD(const u8 row, const u8 pos, const u32 num);
void clearAllLCD();
void clearLCD( const u8 row, const int pos );
u8 isLCDInitialized();

#endif // include guard LCD_H
