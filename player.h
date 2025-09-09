#ifndef PLAYER_H
#define PLAYER_H
#include "my_define.h"
#include "sprite.h"

typedef struct Player
{
	struct Sprite sprite;
	u8 row;
	int life;
} Player;

void createPlayer( Player* const ppl  );
void upPlayer( Player* const ppl );
void downPlayer( Player* const ppl );
void damagePlayer( Player* const ppl );
void drawPlayer( Player* const ppl );
u8 animatePlayerSprite( Player* const ppl, const u32 now );
#endif