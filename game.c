#include "game.h"
#include "iodefine.h"
#include "my_define.h"
#include "timer.h"
#include "lcd.h"
#include "switch.h"
#include "stdlib.h"
#include "hwtimer.h"
#include "player.h"
#include "items.h"

typedef enum
{
	NONE = 0,
	PLAYER_DRAW = 1,
	PLAYER_CLEAR_DRAW = 1 << 1,
	ITEM_DRAW = 1 << 2,
	ITEM_CLEAR_DRAW = 1 << 3,
	UI_DRAW = 1 << 4,
} DrawFlagBit;

typedef struct GameOBJ
{
	Items items;
	Player player;
	int game_speed;
	u32 pre_update_time;
	int draw_flags;
	int score;
}GameOBJ;

void createGameOBJ( GameOBJ* const obj )
{
	createItems( &obj->items );
	createPlayer( &obj->player );
	obj->game_speed = 700;
	obj->pre_update_time = 0;
	obj->draw_flags = PLAYER_DRAW | ITEM_DRAW | UI_DRAW;
	obj->score = 0;
}

u8 isHitItemPlayer( Item* const pitm, Player* const target )
{
	return pitm->position == 0 && pitm->row == target->row;
}

void onHitItemPlayer( Item* const pitm, Player* const target, int* score )
{
	if( pitm->point == 0 ){ damagePlayer( target ); }
	else{ *score += pitm->point; }
	pitm->position = -1; //画面外へ強制的に移行
}

u8 Collision( Items* const pitms, Player* const target, int* score  )
{
	u8 out =0;
	for( int i=0; i < pitms->active_item_num; i++ )
	{
		// アイテムとプレイヤーが重なってたらヒットしスコア加算
		 if( isHitItemPlayer( &pitms->item[i], target ) )
		{
			onHitItemPlayer( &pitms->item[i], target, score ) ;
			out = 1; // 更新
		}
		if( pitms->item[i].position == -1 )
		{
			 ReSpawnItems( pitms, i, *score );
			out = 1;
		}
	}
	return out; // 更新なし
}

void input( GameOBJ* const obj )
{
	// player move input
	if( sw1Down() )
	{
		upPlayer( &obj->player );
		obj->draw_flags |= PLAYER_CLEAR_DRAW;
	}
	if( sw3Down() )
	{
		downPlayer( &obj->player );
		obj->draw_flags |= PLAYER_CLEAR_DRAW;
	}
}

void update( GameOBJ* const obj )
{
	u32 now = getTimeMS();
	//itemの移動と当たり判定
	if( now - obj->pre_update_time >= obj->game_speed )
	{
		obj->pre_update_time = now;
		
		moveItems( &obj->items );
		obj->draw_flags |= ITEM_CLEAR_DRAW;
		
		if( Collision( &obj->items, &obj->player, &obj->score ) )
		{
			obj->draw_flags |= UI_DRAW;
		}
	}
	
	//アイテムのスプライトアニメーションの変更
	if( animateItemsSprite( &obj->items, now ) )
	{
		obj->draw_flags |= PLAYER_DRAW;
	}
	
	//プレイヤーのスプライトアニメ
	if( animatePlayerSprite( &obj->player, now ) )
	{
		obj->draw_flags |= ITEM_DRAW;
	}
	
}

void draw( GameOBJ* const obj )
{
	//描画関係
	if( obj->draw_flags != NONE )
	{	
		//アイテムを一番後ろに描画
		if(  obj->draw_flags & ( ITEM_CLEAR_DRAW | ITEM_DRAW ) )
		{
			if(  obj->draw_flags & ITEM_CLEAR_DRAW )
			{
				itemsClear( &obj->items, obj->player.row );
			}
			
			drawItems( &obj->items );
		}
		
		//プレイヤー
		if(  obj->draw_flags & ( PLAYER_CLEAR_DRAW | PLAYER_DRAW ) )
		{
			if(   obj->draw_flags & PLAYER_CLEAR_DRAW )
			{
				clearLCD( 1, 0 );
				clearLCD( 2, 0 );
			}
			
			drawPlayer( &obj->player );
		}
		
		//スコア
		if(  obj->draw_flags & UI_DRAW )
		{
			printNUM3_LCD(1,5,obj->score);
			// 残機クリア
			printLCD(2, 5, "   ");
			//残機
			for( int i=0; i < obj->player.life; i++ )
			{
				putLCD( 2, 5+i,  obj->player.sprite.data[0] );
			}
		}
		
		//再描画完了したのでフラグを下す
		 obj->draw_flags = NONE;
		
	}
}


int game()
{
	setHwTimer();
	GameOBJ game_obj;
	createGameOBJ( &game_obj );
	
	while( game_obj.player.life != 0 )
	{
		input( &game_obj );
		update( &game_obj );
		draw( &game_obj );
	}
	
	stopHwTimer();
	clearAllLCD();
	waitTimer( 200,UNIT_MS );
	return game_obj.score;
}