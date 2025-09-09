#include "switch.h"
#include "iodefine.h"
#include "my_define.h"

typedef enum
{
	SW_DOWN,
	SW_UP,
	SW_NONE
}SW_STATE;

static SW_STATE state1 = SW_NONE;
static SW_STATE state2 = SW_NONE;
static SW_STATE state3 = SW_NONE;

int sw1Down()
{
	 if( state1 == SW_DOWN )
	 { 
		 state1 = SW_NONE;
	 	return 1; 
	 }
	 
	 return 0;
}
int sw1Up()
{
	 if( state1 == SW_UP )
	 { 
		 state1 = SW_NONE;
	 	return 1; 
	 }
	 
	 return 0;
}
int sw1Both()
{
	if(state1 == SW_UP || state1 == SW_DOWN )
	{
		state1 = SW_NONE;
		return 1;
	}
	return 0;
}

int sw2Down()
{
	 if( state2 == SW_DOWN )
	 { 
		 state2 = SW_NONE;
	 	return 1; 
	 }
	 
	 return 0;
}
int sw2Up()
{
	 if( state2 == SW_UP )
	 { 
		 state2 = SW_NONE;
	 	return 1; 
	 }
	 return 0;
}
int sw2Both()
{
	if(state2 == SW_UP || state2 == SW_DOWN )
	{
		state2= SW_NONE;
		return 1;
	}
	return 0;
}


int sw3Down()
{
	  if( state3 == SW_DOWN )
	 { 
		 state3 = SW_NONE;
	 	return 1; 
	 }
	 
	 return 0;
}
int sw3Up()
{
	 if( state3 == SW_UP )
	 { 
		 state3 = SW_NONE;
	 	return 1; 
	 }
	 
	 return 0;
}
int sw3Both()
{
	if(state3 == SW_UP || state3 == SW_DOWN )
	{
		state3 = SW_NONE;
		return 1;
	}
	return 0;
}

void  IRQ1_get()
{
	if( SW1 )
	{
		state1 = SW_UP;
	}
	else
	{
		state1 = SW_DOWN;
	}
}

void  IRQ3_get()
{
	if( SW2 )
	{
		state2 = SW_UP;
	}
	else
	{
		state2 = SW_DOWN;
	}
}

void  IRQ4_get()
{
	if( SW3 )
	{
		state3 = SW_UP;
	}
	else
	{
		state3 = SW_DOWN;
	}
}