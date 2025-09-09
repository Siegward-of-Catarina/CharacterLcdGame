#include "iodefine.h"
#include "my_define.h"
#include "timer.h"
#include "hwTimer.h"
#include "lcd.h"

#include "title.h"
#include "game.h"
#include "result.h"

void init()
{
	InitLcdDesc desc;
	desc.function_set = FUNC_SET_DEFAULT;
	desc.display_control = DISP_CNTL_DISPLAY_ON | DISP_CNTL_NON_DISP_CURSOR | DISP_CNTL_CURSOR_BLINK_OFF;
	desc.entry_mode = EN_MD_INC | EN_MD_NON_SHIFT;
	
	initLCD( desc );
	
	const u8 apple[3][8] =
	{
		{ 0x00, 0x06, 0x04, 0x0e, 0x1f, 0x17, 0x13, 0x0e },
		{ 0x00, 0x04, 0x04, 0x0e, 0x1f, 0x1b, 0x1b, 0x0e },
		{ 0x00, 0x0c, 0x04, 0x0e, 0x1f, 0x1d, 0x19, 0x0e }
	};
	
	writeCGRAM( 0, apple[ 0 ] );
	writeCGRAM( 1, apple[ 1 ] );
	writeCGRAM( 2, apple[ 2 ] );
	
	const u8 player[2][8] =
	{
		{ 0x00, 0x00, 0x0e, 0x1b, 0x1e, 0x1c, 0x1f, 0x0e },
		{ 0x00, 0x00, 0x0e, 0x1b, 0x1f, 0x1f, 0x1f, 0x0e }
	};
	
	writeCGRAM( 3, player[ 0 ] );
	writeCGRAM( 4, player[ 1 ] );

	
	const u8 enemy[3][8] =
	{
		{ 0x00, 0x00, 0x02, 0x1e, 0x0a, 0x0f, 0x08, 0x00 },
		{ 0x00, 0x00, 0x04, 0x0e, 0x1b, 0x0e, 0x04, 0x00 },
		{ 0x00, 0x00, 0x08, 0x0f, 0x0a, 0x1e, 0x02, 0x00 }
	};
	
	writeCGRAM( 5, enemy[ 0 ] );
	writeCGRAM( 6, enemy[ 1 ] );
	writeCGRAM( 7, enemy[ 2 ] );
}

void main(void)
{
	init();
	
	
	u8 is_running=1;
	
	while ( is_running )
	{
		title();
		int score = game();
		//リザルトの戻り値がリスタートするか終了するか決める
		is_running = result( score );
	}
	printLCD( 1, 0, "thankyou");
	printLCD( 2, 0, "playing" );
}