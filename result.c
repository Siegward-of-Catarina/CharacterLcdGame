#include "result.h"
#include "lcd.h"
#include "hwtimer.h"
#include "timer.h"
#include "switch.h"

typedef enum ResultState
{
	RS_GAME_OVER_ANIM = 1,
	RS_GAME_OVER = 1 << 1,
	RS_NONE = 1 << 2,
	RS_SCORE = 1 << 3,
	RS_RESTART_CONFIG = 1 << 4,
	RS_END_GAME_CONFIG = 1 << 5,
} ResultState;

typedef struct ResultOBJ
{
	u8 is_running;
	u32 last;
	u32 update_speed;
	ResultState state;
	ResultState pre_state;
} ResultOBJ;

void createResultOBJ( ResultOBJ* obj )
{
	obj->is_running = 1;
	obj->last =0;
	obj->update_speed = 60;
	obj->state = RS_GAME_OVER_ANIM;
	obj->pre_state = RS_NONE;
}

typedef struct GameOverAnim
{
	u8 str_num;
	u8 str_last_idx; //3
	int stop_pos; //2
	int spown_pos; // 7
	u8 curt_pos;
	u8 curt_stop_pos ;
	
} GameOverAnim;

void createGameOverAnim( GameOverAnim* const goa )
{
	goa->str_num = 4; // \0除く
	goa->str_last_idx = 3; // \0除く
	goa->spown_pos = 7;
	goa->stop_pos = 2;
	goa->curt_pos = goa->spown_pos;
	goa->curt_stop_pos = goa->stop_pos;
}

/* ゲームオーバー表示のアニメーション
 * 引数1：関連の変数群のポインタ
 * 戻り値：アニメーション終了フラグ 
 */
void gameoverAnimationState( GameOverAnim* const goa, ResultOBJ* obj )
{
	char game[] = "GAME";
	char over[] = "OVER";
	
	int clear_pos = goa->curt_pos + 1;
	
	//stop_posをインデックスに補正して使う
	int idx = goa->curt_stop_pos - goa->stop_pos;
	
	clearLCD( 1, clear_pos );
	putLCD( 1, goa->curt_pos, game[ idx ] );
	
	clear_pos = ( goa->spown_pos - goa->curt_pos ) - 1;
	
	clearLCD( 2, clear_pos );
	putLCD( 2, goa->spown_pos - goa->curt_pos, over[ goa->str_last_idx -idx ] );
	
	if( goa->curt_pos > goa->curt_stop_pos ){ goa->curt_pos--; }
	else if( goa->curt_stop_pos <= goa->str_num ){ goa->curt_stop_pos++; goa->curt_pos = goa->spown_pos; }
	else{ obj->state = RS_GAME_OVER; }
}

void gameOverState( ResultOBJ* obj )
{
	printLCD( 1, 2, "GAME" );
	printLCD( 2, 2, "OVER" );
	obj->pre_state = RS_GAME_OVER;
	obj->state = RS_NONE;
	obj->update_speed = 2000;
}

void noneState( ResultOBJ* obj )
{
	clearAllLCD();
	
	if( obj->pre_state == RS_GAME_OVER )
		obj->state = RS_SCORE;
		
	if( obj->pre_state == RS_SCORE )
		obj->state = RS_RESTART_CONFIG;
		
	if( obj->pre_state == RS_RESTART_CONFIG )
		obj->state = RS_END_GAME_CONFIG;
		
	if( obj->pre_state == RS_END_GAME_CONFIG )
		obj->state = RS_SCORE;
		
	obj->update_speed = 800;
}

void scoreState( ResultOBJ* obj, const int score )
{
	printLCD( 1, 0, "SCORE" );
	printNUM3_LCD( 2, 5, score );
	obj->pre_state = RS_SCORE;
	obj->state = RS_NONE;
	obj->update_speed = 2000;
}

void restartConfigState( ResultOBJ* obj )
{
	printLCD( 1, 0, "RESTART" );
	printLCD( 2, 0, "   ->SW2" );
	obj->pre_state = RS_RESTART_CONFIG;
	obj->state = RS_NONE;
	obj->update_speed = 2000;
}

void endGameConfigState( ResultOBJ* obj )
{
	printLCD( 1, 0, "ENDGAME" );
	printLCD( 2, 0, "   ->SW3" );
	obj->pre_state = RS_END_GAME_CONFIG;
	obj->state = RS_NONE;
	obj->update_speed = 2000;
}

u8 result( const int score )
{
	
	ResultOBJ res_obj;
	createResultOBJ( &res_obj );
	
	GameOverAnim goa;
	createGameOverAnim( &goa );
	
	//この関数の戻り値に使用
	u8 out_state = 0; // 1 : re state, 0 : end game
	
	setHwTimer();
	
	while ( res_obj.is_running )
	{
		u32 now = getTimeMS();
		if( now - res_obj.last >= res_obj.update_speed )
		{
			res_obj.last = now;
			switch( res_obj.state )
			{
			case RS_GAME_OVER_ANIM:
				gameoverAnimationState( &goa, &res_obj );
				break;
			case RS_GAME_OVER :
				gameOverState( &res_obj );
				break;
			case RS_NONE :
				noneState( &res_obj );
				break;
			case RS_SCORE :
				scoreState( &res_obj, score );
				break;
			case RS_RESTART_CONFIG :
				restartConfigState( &res_obj );
				break;
			case RS_END_GAME_CONFIG :
				endGameConfigState( &res_obj );
				break;
			}
		}
		
		// RS_GAME_OVER_ANIM, RS_GAME_OVERの時は入力を受け付けない
		if(  sw2Down() && res_obj.state != RS_GAME_OVER && res_obj.state != RS_GAME_OVER_ANIM )
		{
			out_state = 1;
			res_obj.is_running = 0;
		}
		
		if(  sw3Down() && res_obj.state != RS_GAME_OVER && res_obj.state != RS_GAME_OVER_ANIM )
		{
			out_state = 0;
			res_obj.is_running = 0;
		}
		
	}
	stopHwTimer();
	clearAllLCD();
	waitTimer( 200, UNIT_MS );
	
	return out_state;
}