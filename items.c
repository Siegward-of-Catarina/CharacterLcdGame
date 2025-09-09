#include "items.h"
#include "stdlib.h"
#include "lcd.h"

void createItems( Items* const pitms )
{
	pitms->default_sporn_pos = 4;
	pitms->default_offset = 2;
	
	pitms->active_item_num = 1;
	//�������̊֌W��X�|�[���ʒu��1��납��n�߂�
	createApple( &pitms->item[0], 1 );
}

void moveItems( Items* const pitms )
{
	pitms->last_item_pos = -1; //���񃊃Z�b�g
	for( int i=0; i < pitms->active_item_num; i++ )
	{
		//�A�C�e������ʔ͈͓��ɂ���ꍇ���Z
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
		// �͈͎w����Z
		u8 tmp = animateItemSprite( &pitms->item[i], now );
		if( tmp ){ out = 1; }
	}
	return out;
}

void itemsClear( Items* const pitms, const u8 pl_row )
{
	u8 row = pl_row == 1 ? 2 : 1; //�v���C���[�����Ȃ��ق�
	printLCD( row, 0,"     " );// ���Ȃ��ق��� 0 ~ 4
	printLCD( pl_row, 1,"    " ); // ����ق� 1 ~ 4
}

void drawItems( Items* const pitms )
{
	for( int i=0; i < pitms->active_item_num; i++ )
	{
		//�q�b�g���͕`�悵�Ȃ�
		if( pitms->item[i].position >= 0 && pitms->item[i].position <= pitms->default_sporn_pos )
		{
			drawItem( &pitms->item[i] );
		}
	}
}

void ReSpawnItems( Items* const pitms, const u8 idx, const int score )
{
	//�����_���Ńv���X�A�C�e�����}�C�i�X�A�C�e������I��
	int random = rand() % 2;
	u8 offset  = pitms->active_item_num > 1 ? abs( pitms->last_item_pos - pitms->default_offset ) : 0;
	if( random )
	{	//�����S�@�v���X�A�C�e��
		createApple( &pitms->item[ idx ], offset );
	}
	else
	{	//�藠���I�Ȃ́@�}�C�i�X�A�C�e��
		createEnemy( &pitms->item[ idx ], offset );
	}
	
	//2�ڂ�ǉ�
	if( pitms->active_item_num == 1 && score == 50 )
	{
		createApple( &pitms->item[ 1 ], 2 );
		pitms->active_item_num++;
	}
	//3�ڂ�ǉ�
	if( pitms->active_item_num == 2 && score == 100 )
	{
		createApple( &pitms->item[ 2 ], 4 );
		pitms->active_item_num++;
	}
}