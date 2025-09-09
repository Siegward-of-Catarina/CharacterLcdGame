#include "safe_input.h"
#include "iodefine.h"

u8 safe_in_sw1()
{
	static u8 in_state = 0;
	static u16 time = 0;
	static const u16 t_max = 500; // 約0.1ms
	
	u8 in = SW1 & 0x01;
	
	if( !in )
	{
		//ボタンが押されてる間カウントし、0.1ms待機後入力に状態を変える
		if( t_max < time++ )
			in_state = 1;
	}
	
	//ボタンが離された時に、in_stateが立っていれば入力を返す。　タイマーはリセット
	if( in )
	{
		if( in_state )
		{
			in_state = 0;
			return 1;
		}
		
		time = 0;
	}
	
	return 0;
}

u8 safe_in_sw2()
{
	static u8 in_state = 0;
	static u16 time = 0;
	static const u16 t_max = 500; // 約0.1ms
	
	u8 in = SW2 & 0x01;
	
	if( !in )
	{
		//ボタンが押されてる間カウントし、0.1ms待機後入力に状態を変える
		if( t_max < time++ )
			in_state = 1;
	}
	
	//ボタンが離された時に、in_stateが立っていれば入力を返す。　タイマーはリセット
	if( in )
	{
		if( in_state )
		{
			in_state = 0;
			return 1;
		}
		
		time = 0;
	}
	
	return 0;
}

u8 safe_in_sw3()
{
	static u8 in_state = 0;
	static u16 time = 0;
	static const u16 t_max = 500; // 約0.1ms
	
	u8 in = SW3 & 0x01;
	
	if( !in )
	{
		//ボタンが押されてる間カウントし、0.1ms待機後入力に状態を変える
		if( t_max < time++ )
			in_state = 1;
	}
	
	//ボタンが離された時に、in_stateが立っていれば入力を返す。　タイマーはリセット
	if( in )
	{
		if( in_state )
		{
			in_state = 0;
			return 1;
		}
		
		time = 0;
	}
	
	return 0;
}