#ifndef TIMER_H
#define TIMER_H

#include "typedefine.h"

typedef const enum
{
	UNIT_S = 5000000,
	UNIT_MS = 5000,
	UNIT_US = 5,
} TimeUnit;

void waitTimer( const _UINT delay, const TimeUnit unit );
#endif