#include "iodefine.h"  
#include "lcd.h"
void timer_(int delay){//1ms x delay
	int i,j;
	for( i=0; i<delay; i++){
		for( j=0; j< 5000; j++){//1m_wait
			;
		}
	}
}

void code_e(char code_h){//4�ޯ��ް��̲ݽ�׸��ݏ�����
	PORTH.PODR.BYTE = code_h;//FuctionSet(DL=1:8bitI/F)
	PORTJ.PODR.BIT.B1=0;//RS:Low(�ݽ׸���)
	PORTJ.PODR.BIT.B3=1;//E:hight(������)
	timer_(1);//1ms_wait;
	PORTJ.PODR.BIT.B3=0;//E:Low(�����ݏI��)
	timer_(1);//1ms_wait;
}
void code_w(char code){//1�޲�-�ݽ�׸��ݏ�����
	char code_4b;//4�ޯ�-�f�[�^
	code_4b = (code & 0xF0) >>4;//���4bit
	code_e(code_4b);
	code_4b = code & 0x0F;//����4bit
	code_e(code_4b);
}
void chara_w(char chara_h){//4�ޯ��ް��̕������ޏ�����
	PORTH.PODR.BYTE =chara_h;//�P�s�ڂP����
	PORTJ.PODR.BIT.B1=1;//RS:hight�iDR)
	PORTJ.PODR.BIT.B3=1;//E:hight(������)
	timer_(1);//1ms_wait;
	PORTJ.PODR.BIT.B3=0;//E:Low(�����ݏI��)
	timer_(1);//1ms_wait;
}
void LCD_write(char LCD_char){//1�������ޓ]��
	char chara_4b;
	chara_4b = (LCD_char & 0xF0) >>4;//���4bit
	chara_w(chara_4b);
	chara_4b = LCD_char & 0x0F;//����4bit
	chara_w(chara_4b);
}
void LCD_init(void){
	int i;
	//�o�̓f�[�^�̐ݒ�
	LCD_DB =0x0F;//PH0-3:1
	LCD_RS =1;//PJ1(RS):1
	LCD_E =0;//PJ3(E):0
	//�o�͒[�q�ɐݒ�
	LCD_DB_PDR |= 0x0f;
	LCD_PDR |= LCD_RS_E_OUT;
	
//LCD�������V�[�P���X
	timer_(40);//40ms_wait
	
	for(i=0; i<3; i++){
//1.FuctionSet	8bitI/F-set�i0��3�j�R��ݒ�
	  code_w(FUNC_SET_DL8);
	  timer_(5);//40ms_wait
	}
//2.FuctionSet	4bitI/F-set�i0��2�j
	code_w( 0x20 );////FuctionSet(DL=1:4bitI/F)
	
//�@.FuctionSet	4bitI/F-set+2�s�\��/5x8�ޯāi0��28�j
	code_w(0x28);//FuctionSet(DL=1:4bitI/F)
			//(N=1:2�s�\��.F=1:5x8�ޯ�)
//�A.FuctionSet	4bitI/F-set+2�s�\��/5x8�ޯāi0��28�j
	code_w(0x28);//FuctionSet(DL=1:4bitI/F)
			//(N=1:2�s�\��.F=1:5x8�ޯ�)
			
//�B.DisplayON/OFFcontrol �\��ON/����ON/���ݸOFF�i0��0E�j
	code_w(0x0E);//DisplayON/OFFcontro
           //(D=1:�\��ON,C=1:�J�[�\��ON,B=0:�u�����NOFF)
	   
//�C.Display Clear(�\���ر)�i0��01�j
	code_w(0x01);;//Display Clear(�\���ر)
	timer_(2);//2ms_wait;
	
//�D.EntryModeSet�@�ݸ����/�\�����Ă����Ȃ��i0��06�j
	code_w(0x06);//EntryModeSet
	         //(I/D=1:�ݸ����,S=0:�\�����Ă��Ȃ�)
//�������I��
}	
void LCD_struct(const char *str){//������\��
	int i=0;
	while(*str != '\0'){//������
		LCD_write(*str);//1�����\��
		str++;//���̕������ڽ�ݒ�
		i++;
		if(i==8){//8�����ȏ�͕\������
			break;
		}
	}
}
void LCD_cursor(int cur){//1:1�s��,2�F2�s�ڂ�1������
	if(cur == 1){//�P�s��
		code_w(0x80);//�P�s�ڂP������
	}
	if(cur == 2){//2�s��
		code_w(0xC0);//�P�s�ڂP������
	}
}

void main(void)
{
//LCD�̏����ݒ�
	LCD_init();//LCD������
//������\��
	LCD_cursor(1);//���ق̈ړ�1�s��1������
	LCD_struct("0127");//8�����\��
	timer_(500);//500ms_wait
	LCD_cursor(2);///���ق̈ړ�2�s��1������
	LCD_struct("abcdefghij");//10�����\��
}