#include "title.h"

#include "iodefine.h"
#include "my_define.h"
#include "hwtimer.h"
#include "timer.h"
#include "lcd.h"
#include "switch.h"

typedef enum TitleState
{
	TL_NEUTRAL=0,
	TL_TITLE,
	TL_NONE,
	TL_CONFIG
} TitleState;

void title()
{
// ----init------------------------
	setHwTimer();
	u32 last_update = 0;
	u32 update_intv = 1000;
	
	TitleState state = TL_TITLE;
	TitleState  pre_state = TL_TITLE;
	
	int is_running = 1;
	
//----初期描画-----------------
	printLCD( 1, 0, "START" );
	printLCD( 2, 0, "GAME>SW2" );
//----main loop------------------
	while( is_running )
	{
		u32 now = getTimeMS();
		
		if( now - last_update >= update_intv )
		{
			// ステートマシン
			switch( state )
			{
			case TL_TITLE :
				printLCD( 1, 0, "START" );
				printLCD( 2, 0, "GAME>SW2" );
				pre_state = state;
				state = TL_NONE;
				break;
			case TL_NONE :
				clearAllLCD();
				state = ( pre_state == TL_TITLE ) ? TL_CONFIG : TL_TITLE;
				break;
			case TL_CONFIG :
				printLCD( 1, 0, "UP  >SW1" );
				printLCD( 2, 0, "DOWN>SW3" );
				pre_state = state;
				state = TL_NONE;
				break;
			}
			//時間を取っておく
			last_update = now;
		}
		
		// 入力
		if( sw2Down() )
		{
			is_running = 0;
		}
	}
//----後処理-----------------------
	clearAllLCD();
	stopHwTimer();
	
	waitTimer( 200,UNIT_MS );
}