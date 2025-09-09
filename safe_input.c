#include "safe_input.h"
#include "iodefine.h"

u8 safe_in_sw1()
{
	static u8 in_state = 0;
	static u16 time = 0;
	static const u16 t_max = 500; // ��0.1ms
	
	u8 in = SW1 & 0x01;
	
	if( !in )
	{
		//�{�^����������Ă�ԃJ�E���g���A0.1ms�ҋ@����͂ɏ�Ԃ�ς���
		if( t_max < time++ )
			in_state = 1;
	}
	
	//�{�^���������ꂽ���ɁAin_state�������Ă���Γ��͂�Ԃ��B�@�^�C�}�[�̓��Z�b�g
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
	static const u16 t_max = 500; // ��0.1ms
	
	u8 in = SW2 & 0x01;
	
	if( !in )
	{
		//�{�^����������Ă�ԃJ�E���g���A0.1ms�ҋ@����͂ɏ�Ԃ�ς���
		if( t_max < time++ )
			in_state = 1;
	}
	
	//�{�^���������ꂽ���ɁAin_state�������Ă���Γ��͂�Ԃ��B�@�^�C�}�[�̓��Z�b�g
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
	static const u16 t_max = 500; // ��0.1ms
	
	u8 in = SW3 & 0x01;
	
	if( !in )
	{
		//�{�^����������Ă�ԃJ�E���g���A0.1ms�ҋ@����͂ɏ�Ԃ�ς���
		if( t_max < time++ )
			in_state = 1;
	}
	
	//�{�^���������ꂽ���ɁAin_state�������Ă���Γ��͂�Ԃ��B�@�^�C�}�[�̓��Z�b�g
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