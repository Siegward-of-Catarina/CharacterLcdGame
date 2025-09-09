#include "player.h"

static const u8 p_sprite[ 2 ] = { 3, 4 };

void createPlayer(Player* const ppl )
{
	// player sprite
	createSprite( &ppl->sprite, p_sprite, 1, 200 );
	
	ppl->row = 1;
	ppl->life = 3;
}

void upPlayer( Player* const ppl )
{
	ppl->row = 1;
}
void downPlayer( Player* const ppl )
{
	ppl->row = 2; 
}

void damagePlayer( Player* const ppl )
{
	if( ppl->life != 0){ ppl->life--; }
}

void drawPlayer( Player* const ppl )
{
	drawSprite( &ppl->sprite, ppl->row, 0 );
}

u8 animatePlayerSprite( Player* const ppl, const u32 now )
{
	//プレイヤーのスプライトアニメ
	return updateSprite( &ppl->sprite, now );
}


