#include "DelayTemp/DelayTemp.h"

int TimeCount;

/*T INT = VALUE LOAD / CLK AHB-------这里只需设置Value LOAD即可
		SystemCoreClock =180MHZ
		SystemCoreClock/1000=1ms
		SystemCoreClock/100000=10us
		SystemCoreClock/1000000=1us
*/
/*
void Delay10MSConfig()
{
	SysTick_Config(SystemCoreClock / 100);
}
void DelayMSConfig()
{
	SysTick_Config(SystemCoreClock / 1000);
}
void Delay10USConfig()
{
	SysTick_Config(SystemCoreClock / 100000);
}
void DelayUSConfig()
{
	SysTick_Config(SystemCoreClock / 1000000);
}

void DelayHandler(int num)
{
	TimeCount = num;
	while (TimeCount > 0);
	TimeCount = 0;
}
*/



//普通延迟
void Delay(__IO uint32_t nCount)	 //简单的延时函数 大概为1/10000ms
{
	for (; nCount != 0; nCount--)
		;
}



