#ifndef MY_DEFINE_H
#define MY_DEFINE_H

#define TRUE 1
#define FALSE 0
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef  char i8;
typedef  short i16;
typedef  int i32;
typedef  long long i64;

#define UPPER_SET 0xf0
#define LOWER_SET 0x0f
#define LED_ALL_OFF 0xf0
#define LED_ALL_ON 0x00

typedef const enum
{
	B0_SET = 0x01,
	B1_SET = 0x02,
	B2_SET = 0x04,
	B3_SET = 0x08,
	B4_SET = 0x10,
	B5_SET = 0x20,
	B6_SET = 0x40,
	B7_SET = 0x80
} BIT_SET;

typedef const enum
{
	B0_CLR = ~B0_SET,
	B1_CLR = ~B1_SET,
	B2_CLR = ~B2_SET,
	B3_CLR = ~B3_SET,
	B4_CLR = ~B4_SET,
	B5_CLR = ~B5_SET,
	B6_CLR = ~B6_SET,
	B7_CLR = ~B7_SET
} BIT_CLR;

#define SW PORT3.PIDR.BYTE
#define SW1 PORT3.PIDR.BIT.B1
#define SW2 PORT3.PIDR.BIT.B3
#define SW3 PORT3.PIDR.BIT.B4

#define SW_PDR PORT3.PDR.BYTE
#define SW1_PDR PORT3.PDR.BIT.B1
#define SW2_PDR PORT3.PDR.BIT.B3
#define SW3_PDR PORT3.PDR.BIT.B4

#define SW_PMR PORT3.PMR.BYTE
#define SW1_PMR PORT3.PMR.BIT.B1
#define SW2_PMR PORT3.PMR.BIT.B3
#define SW3_PMR PORT3.PMR.BIT.B4

#define LED PORT1.PODR.BYTE
#define LED0 PORT1.PODR.BIT.B4
#define LED1 PORT1.PODR.BIT.B5
#define LED2 PORT1.PODR.BIT.B6
#define LED3 PORT1.PODR.BIT.B7

#define LED_PDR PORT1.PDR.BYTE
#define LED0_PDR PORT1.PDR.BIT.B4
#define LED1_PDR PORT1.PDR.BIT.B5
#define LED2_PDR PORT1.PDR.BIT.B6
#define LED3_PDR PORT1.PDR.BIT.B7

#endif // include guard MY_DEFINE_H