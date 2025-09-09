#include "iodefine.h"
#include "hwTimer.h"
#include "hwTimer_interrupt.h"

static u64 time_count0 =0;
static u64 time_count1 =0;

void setHwTimer()
{
	CMT.CMSTR0.WORD = 0x0003;
};
void stopHwTimer()
{
	CMT.CMSTR0.WORD = 0x0000;
}

u32 getTimeS()
{
	return time_count1 / 1000;
}
u64 getTimeMS()
{
	return time_count1;
}
u64 getTimeUS()
{
	return time_count0;
}

//@Š„‚è‚İŒÄ‚ÔŠÖ”
void call_cmt0()
{	
	time_count0++;
};
void call_cmt1()
{
	time_count1++;
};