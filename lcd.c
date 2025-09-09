#include"lcd.h"
#include"timer.h"
#include "stdio.h"

static u8 is_initialized = 0;

void write4b(const u8 byte, const u8 rs)
{
	  LCD_DB = byte; //4�r�b�g
	  LCD_RS = rs;//RS:Low(�ݽ׸���)
	  
	  LCD_E = 1;//E:hight(������)
	  waitTimer(40,UNIT_US);//1ms_wait;
	  
	  LCD_E = 0;//E:Low(�����ݏI��)
	  waitTimer(40,UNIT_US);//1ms_wait;
}

void commandWrite(const u8 byte)
{
	//upper
	u8 writebit = (byte & 0xf0) >> 4;
	write4b( writebit, 0);
	//lower
	writebit = (byte & 0x0f);
	write4b( writebit, 0);
}

void charWrite(const u8 byte)
{
	//upper
	u8 writebit = (byte & 0xf0) >> 4;
	write4b( writebit, 1);
	//lower
	writebit = (byte & 0x0f);
	write4b( writebit, 1);
}

void writeCGRAM(u8 pos, const u8 pattern[8])
{
	if( pos > 7 ) return;
	
	commandWrite( 0x40 | ( pos << 3) );
	
	for( int i = 0; i < 8; i++ )
	{
		charWrite( pattern[ i ] );
	}
	commandWrite( LCD_LINE1_ST );
}
//LCD�������p�\���̂��󂯎�肻�̏�����ɏ�����
void initLCD( const InitLcdDesc desc )
{
	//�o�̓f�[�^�̐ݒ�
	LCD_DB = LOWER_SET; // off�ɐݒ�
	LCD_RS = 1; //�f�[�^�������݃��[�h��
	LCD_E = 0; //�������݋��t���O�B�����Ă���
	
	//�o�͒[�q�ɐݒ�
	LCD_DB_PDR |= LOWER_SET;
	LCD_PDR |= LCD_RS_E_OUT;
	
	//LCD�������V�[�P���X
	
	//LCD�������BLCD�����肷��܂ŋ����I�ɏ������𑱂���
	//��������8bit���[�h�ŏ��������Ȃ��Ƃ����Ȃ�
	for(int i=0; i<3; i++){
		write4b( (FUNC_SET_DL8 >> 4), 0);
		waitTimer(5,UNIT_MS);//�Œ���4.1ms�Ȃ̂ł���ȏ�҂��Ȃ��珉����
	}
	
	//8bit�ŋN����܂��A���r�b�g�ň���������B���̎��͂܂�8bit��1���߂Ɖ��߂���̂ŁA4bit�ő��M����K�v������
	write4b( (desc.function_set >> 4), 0);
	
	//function set
	commandWrite( desc.function_set );
	// display control
	commandWrite( desc.display_control );
	
	// display clear 
	commandWrite( INST_DISPLAY_CLEAR );
	waitTimer(3,UNIT_MS); //�X�̏����͏����d�߂Ȃ̂Œ��߂ɑ҂�
	
	// entry mode
	commandWrite( desc.entry_mode );
	
	is_initialized = 1;
	
}

void putLCD(const u8 row, const u8 pos, const u8 ch)
{
	if(pos >= 8){ return; }//pos���\���̈�ȏ�Ȃ�\��������̂��Ȃ��̂ŉ��������߂�
	
	u8 rw = ( row == 2 ) ? 0xC0 : 0x80;
	
	//�`��J�n�ʒu�w��
	commandWrite( rw + pos ); //pos�����炷
	charWrite( ch );
}

//LCD�ɕ�����o�� 8�����ȏ�͕\�����Ȃ�
void printLCD(const u8 row, const u8 pos, const char* string)
{
	if(pos >= 8){ return; }//pos���\���̈�ȏ�Ȃ�\��������̂��Ȃ��̂ŉ��������߂�

	u8 rw = ( row == 2 ) ? 0xC0 : 0x80;
	
	//�`��J�n�ʒu�w��
	commandWrite( rw + pos ); //pos�����炷
	
	u8 max_len = 8 - pos;
	for( u8 i =0; i < max_len; i++)
	{
		//�I�[�����ȊO�`��
		if( *string != '\0' )
		{
			charWrite( *string );
			string++;
		}else
		{
			break;
		}
	}
}

void printNUM3_LCD(const u8 row, const u8 pos, const u32 num)
{
	char nums[4];
	sprintf( nums, "%3d", num);
	printLCD(row, pos, nums );
}

void clearAllLCD()
{
	commandWrite( INST_DISPLAY_CLEAR );
	waitTimer(1600,UNIT_US); //�X�̏����͏����d�߂Ȃ̂Œ��߂ɑ҂�
}

void clearLCD( const u8 row, const int pos )
{
	if( -1 < pos && pos < 8 )
	{
		putLCD( row, pos,' ' );
	}
}

u8 isLCDInitialized()
{
	return is_initialized;
}