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

void code_e(char code_h){//4ﾋﾞｯﾄﾃﾞｰﾀのｲﾝｽﾄﾗｸｼｮﾝ書込み
	PORTH.PODR.BYTE = code_h;//FuctionSet(DL=1:8bitI/F)
	PORTJ.PODR.BIT.B1=0;//RS:Low(ｲﾝｽﾗｸｼｮﾝ)
	PORTJ.PODR.BIT.B3=1;//E:hight(書込み)
	timer_(1);//1ms_wait;
	PORTJ.PODR.BIT.B3=0;//E:Low(書込み終了)
	timer_(1);//1ms_wait;
}
void code_w(char code){//1ﾊﾞｲﾄ-ｲﾝｽﾄﾗｸｼｮﾝ書込み
	char code_4b;//4ﾋﾞｯﾄ-データ
	code_4b = (code & 0xF0) >>4;//上位4bit
	code_e(code_4b);
	code_4b = code & 0x0F;//下位4bit
	code_e(code_4b);
}
void chara_w(char chara_h){//4ﾋﾞｯﾄﾃﾞｰﾀの文字ｺｰﾄﾞ書込み
	PORTH.PODR.BYTE =chara_h;//１行目１文字
	PORTJ.PODR.BIT.B1=1;//RS:hight（DR)
	PORTJ.PODR.BIT.B3=1;//E:hight(書込み)
	timer_(1);//1ms_wait;
	PORTJ.PODR.BIT.B3=0;//E:Low(書込み終了)
	timer_(1);//1ms_wait;
}
void LCD_write(char LCD_char){//1文字ｺｰﾄﾞ転送
	char chara_4b;
	chara_4b = (LCD_char & 0xF0) >>4;//上位4bit
	chara_w(chara_4b);
	chara_4b = LCD_char & 0x0F;//下位4bit
	chara_w(chara_4b);
}
void LCD_init(void){
	int i;
	//出力データの設定
	LCD_DB =0x0F;//PH0-3:1
	LCD_RS =1;//PJ1(RS):1
	LCD_E =0;//PJ3(E):0
	//出力端子に設定
	LCD_DB_PDR |= 0x0f;
	LCD_PDR |= LCD_RS_E_OUT;
	
//LCD初期化シーケンス
	timer_(40);//40ms_wait
	
	for(i=0; i<3; i++){
//1.FuctionSet	8bitI/F-set（0ｘ3）３回設定
	  code_w(FUNC_SET_DL8);
	  timer_(5);//40ms_wait
	}
//2.FuctionSet	4bitI/F-set（0ｘ2）
	code_w( 0x20 );////FuctionSet(DL=1:4bitI/F)
	
//①.FuctionSet	4bitI/F-set+2行表示/5x8ﾄﾞｯﾄ（0ｘ28）
	code_w(0x28);//FuctionSet(DL=1:4bitI/F)
			//(N=1:2行表示.F=1:5x8ﾄﾞｯﾄ)
//②.FuctionSet	4bitI/F-set+2行表示/5x8ﾄﾞｯﾄ（0ｘ28）
	code_w(0x28);//FuctionSet(DL=1:4bitI/F)
			//(N=1:2行表示.F=1:5x8ﾄﾞｯﾄ)
			
//③.DisplayON/OFFcontrol 表示ON/ｶｰｿﾙON/ﾌﾞﾘﾝｸOFF（0ｘ0E）
	code_w(0x0E);//DisplayON/OFFcontro
           //(D=1:表示ON,C=1:カーソルON,B=0:ブリンクOFF)
	   
//④.Display Clear(表示ｸﾘｱ)（0ｘ01）
	code_w(0x01);;//Display Clear(表示ｸﾘｱ)
	timer_(2);//2ms_wait;
	
//⑤.EntryModeSet　ｲﾝｸﾘﾒﾝﾄ/表示をｼﾌﾄさせない（0ｘ06）
	code_w(0x06);//EntryModeSet
	         //(I/D=1:ｲﾝｸﾘﾒﾝﾄ,S=0:表示をｼﾌﾄしない)
//初期化終了
}	
void LCD_struct(const char *str){//文字列表示
	int i=0;
	while(*str != '\0'){//文字列
		LCD_write(*str);//1文字表示
		str++;//次の文字ｱﾄﾞﾚｽ設定
		i++;
		if(i==8){//8文字以上は表示せず
			break;
		}
	}
}
void LCD_cursor(int cur){//1:1行目,2：2行目の1文字目
	if(cur == 1){//１行目
		code_w(0x80);//１行目１文字目
	}
	if(cur == 2){//2行目
		code_w(0xC0);//１行目１文字目
	}
}

void main(void)
{
//LCDの初期設定
	LCD_init();//LCD初期化
//文字列表示
	LCD_cursor(1);//ｶｰｿﾙの移動1行目1文字目
	LCD_struct("0127");//8文字表示
	timer_(500);//500ms_wait
	LCD_cursor(2);///ｶｰｿﾙの移動2行目1文字目
	LCD_struct("abcdefghij");//10文字表示
}