#include "item.h"
#include "stdlib.h"

static const u8 apple_sprite[ 4 ] = { 0, 1, 2, 1 };
static const u8 enemy_sprite[ 3 ] = { 5, 6, 7 };

void createApple( Item* const pitm, const u8 offset )
{
	createSprite( &pitm->sprite, apple_sprite, 3,200 );
	
	pitm->row = ( rand() ) % 2 + 1;
	pitm->position = 4+offset;
	pitm->point = 10;
}
void createEnemy( Item* const pitm, const u8 offset )
{
	createSprite( &pitm->sprite, enemy_sprite, 2, 200 );
	
	pitm->row = ( rand() ) % 2 + 1;
	pitm->position = 4+offset;
	pitm->point = 0;
}

void moveItem( Item* const pitm )
{
	if( pitm->position > -1 )
	{ 
		pitm->position--; 
	}
}

void drawItem( Item* const pitm )
{
	drawSprite( &pitm->sprite, pitm->row, pitm->position );
}

u8 animateItemSprite( Item* const pitm, const u32 now )
{
	return updateSprite( &pitm->sprite, now );
}

