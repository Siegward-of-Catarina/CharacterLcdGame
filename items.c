#include "items.h"
#include "stdlib.h"
#include "lcd.h"

void createItems( Items* const pitms )
{
	pitms->default_sporn_pos = 4;
	pitms->default_offset = 2;
	
	pitms->active_item_num = 1;
	//処理順の関係上スポーン位置の1個後ろから始める
	createApple( &pitms->item[0], 1 );
}

void moveItems( Items* const pitms )
{
	pitms->last_item_pos = -1; //毎回リセット
	for( int i=0; i < pitms->active_item_num; i++ )
	{
		//アイテムが画面範囲内にいる場合減算
		moveItem( &pitms->item[i] );
		pitms->last_item_pos = ( pitms->last_item_pos < pitms->item[i].position ) 
							? pitms->item[i].position : pitms->last_item_pos;
	}
}

u8 animateItemsSprite( Items* const pitms, const u32 now )
{
	u8 out = 0;
	for( int i=0; i < pitms->active_item_num; i++ )
	{
		// 範囲指定加算
		u8 tmp = animateItemSprite( &pitms->item[i], now );
		if( tmp ){ out = 1; }
	}
	return out;
}

void itemsClear( Items* const pitms, const u8 pl_row )
{
	u8 row = pl_row == 1 ? 2 : 1; //プレイヤーがいないほう
	printLCD( row, 0,"     " );// いないほうは 0 ~ 4
	printLCD( pl_row, 1,"    " ); // いるほう 1 ~ 4
}

void drawItems( Items* const pitms )
{
	for( int i=0; i < pitms->active_item_num; i++ )
	{
		//ヒット時は描画しない
		if( pitms->item[i].position >= 0 && pitms->item[i].position <= pitms->default_sporn_pos )
		{
			drawItem( &pitms->item[i] );
		}
	}
}

void ReSpawnItems( Items* const pitms, const u8 idx, const int score )
{
	//ランダムでプラスアイテムかマイナスアイテムかを選定
	int random = rand() % 2;
	u8 offset  = pitms->active_item_num > 1 ? abs( pitms->last_item_pos - pitms->default_offset ) : 0;
	if( random )
	{	//リンゴ　プラスアイテム
		createApple( &pitms->item[ idx ], offset );
	}
	else
	{	//手裏剣的なの　マイナスアイテム
		createEnemy( &pitms->item[ idx ], offset );
	}
	
	//2個目を追加
	if( pitms->active_item_num == 1 && score == 50 )
	{
		createApple( &pitms->item[ 1 ], 2 );
		pitms->active_item_num++;
	}
	//3個目を追加
	if( pitms->active_item_num == 2 && score == 100 )
	{
		createApple( &pitms->item[ 2 ], 4 );
		pitms->active_item_num++;
	}
}