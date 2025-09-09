#ifndef SPRITE_H
#define SPRITE_H

#include "my_define.h"

typedef struct Sprite
{
	const u8* data;
	u8 idx;
	u8 last_idx;
	u32 last_update_time;
	u32 interval_time;
} Sprite;

void createSprite( Sprite* const psp, const u8* const sprite_data, const u8 last_idx, const u8 interval );
u8 updateSprite( Sprite* const psp, const u32 now );
void drawSprite(  Sprite* const psp, const u8 row, const u8 pos );
#endif