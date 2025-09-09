#include"lcd.h"
#include"timer.h"
#include "stdio.h"

static u8 is_initialized = 0;

void write4b(const u8 byte, const u8 rs)
{
	  LCD_DB = byte; //4ビット
	  LCD_RS = rs;//RS:Low(ｲﾝｽﾗｸｼｮﾝ)
	  
	  LCD_E = 1;//E:hight(書込み)
	  waitTimer(40,UNIT_US);//1ms_wait;
	  
	  LCD_E = 0;//E:Low(書込み終了)
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
//LCD初期化用構造体を受け取りその情報を基に初期化
void initLCD( const InitLcdDesc desc )
{
	//出力データの設定
	LCD_DB = LOWER_SET; // offに設定
	LCD_RS = 1; //データ書き込みモードに
	LCD_E = 0; //書き込み許可フラグ。下げておく
	
	//出力端子に設定
	LCD_DB_PDR |= LOWER_SET;
	LCD_PDR |= LCD_RS_E_OUT;
	
	//LCD初期化シーケンス
	
	//LCD初期化。LCDが安定するまで強制的に初期化を続ける
	//いったん8bitモードで初期化しないといけない
	for(int i=0; i<3; i++){
		write4b( (FUNC_SET_DL8 >> 4), 0);
		waitTimer(5,UNIT_MS);//最長が4.1msなのでそれ以上待ちながら初期化
	}
	
	//8bitで起動後まず、何ビットで扱うか決定。この時はまだ8bitで1命令と解釈するので、4bitで送信する必要がある
	write4b( (desc.function_set >> 4), 0);
	
	//function set
	commandWrite( desc.function_set );
	// display control
	commandWrite( desc.display_control );
	
	// display clear 
	commandWrite( INST_DISPLAY_CLEAR );
	waitTimer(3,UNIT_MS); //個々の処理は少し重めなので長めに待つ
	
	// entry mode
	commandWrite( desc.entry_mode );
	
	is_initialized = 1;
	
}

void putLCD(const u8 row, const u8 pos, const u8 ch)
{
	if(pos >= 8){ return; }//posが表示領域以上なら表示するものがないので何もせず戻る
	
	u8 rw = ( row == 2 ) ? 0xC0 : 0x80;
	
	//描画開始位置指定
	commandWrite( rw + pos ); //pos分ずらす
	charWrite( ch );
}

//LCDに文字列出力 8文字以上は表示しない
void printLCD(const u8 row, const u8 pos, const char* string)
{
	if(pos >= 8){ return; }//posが表示領域以上なら表示するものがないので何もせず戻る

	u8 rw = ( row == 2 ) ? 0xC0 : 0x80;
	
	//描画開始位置指定
	commandWrite( rw + pos ); //pos分ずらす
	
	u8 max_len = 8 - pos;
	for( u8 i =0; i < max_len; i++)
	{
		//終端文字以外描画
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
	waitTimer(1600,UNIT_US); //個々の処理は少し重めなので長めに待つ
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