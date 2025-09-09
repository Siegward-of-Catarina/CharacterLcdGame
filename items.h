#ifndef ITEMS_H
#define ITEMS_H

#include "my_define.h"
#include "item.h"

typedef struct Items
{
	Item item[3];
	u8 active_item_num;
	u8 default_sporn_pos;
	u8 default_offset;
	i16 last_item_pos; // ÅŒã”ö‚Ìƒ|ƒWƒVƒ‡ƒ“
} Items;

void createItems( Items* const pitms );
void moveItems( Items* const pitms );
u8 animateItemsSprite( Items* const pitms, const u32 now );
void itemsClear( Items* const pitms, const u8 pl_row );
void drawItems( Items* const pitms );
void ReSpawnItems( Items* const pitms, const u8 idx, const int score );

#endif // ITEMS_H