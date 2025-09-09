#include "timer.h"

void waitTimer( const _UINT delay, const TimeUnit unit )
{
	for( int i = 0; i < delay; i++)
	{
		for( int j = 0;  j < unit; j++)
		{;}
	}
}