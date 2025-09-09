#ifndef ITEM_H
#define ITEM_H
#include "my_define.h"
#include "sprite.h"

typedef struct Item
{
	Sprite sprite;
	u8 row;
	int position;
	int point;
}Item;

void createApple( Item* const pitm, const u8 offset );
void createEnemy( Item* const pitm, const u8 offset );
void moveItem(  Item* const pitm );
void drawItem( Item* const pitm );
u8 animateItemSprite( Item* const pitm, const u32 now );
#endif