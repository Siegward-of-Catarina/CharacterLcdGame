#include "sprite.h"
#include "lcd.h"
#include "string.h"

u8 getCurrentSprirte( Sprite* const psp ){ return psp->data[psp->idx]; }

void createSprite( Sprite* const psp, const u8* const sprite_data, const u8 last_idx, const u8 interval )
{
	psp->data = sprite_data;
	psp->idx = 0;
	psp->last_idx = last_idx;
	psp->last_update_time = 0;
	psp->interval_time = interval;
}

u8 updateSprite( Sprite* const psp, const u32 now )
{
	if( now - psp->last_update_time >=   psp->interval_time )
	{
		psp->last_update_time = now;
		// 範囲指定加算
		psp->idx = ( psp->idx < psp->last_idx ) ? psp->idx + 1 : 0;
		
		return 1; // 更新
	}
	
	return 0; // 未更新
}

void drawSprite( Sprite* const psp, const u8 row, const u8 pos )
{
	putLCD( row, pos, getCurrentSprirte( psp ) );
}