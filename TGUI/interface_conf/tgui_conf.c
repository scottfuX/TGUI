#include "interface_conf/tgui_conf.h"

volatile uint16_t TouchX = 65535;
volatile uint16_t TouchY = 65535;
volatile uint8_t TouchUp = 0;//检查按键是否释放

void GUISetPoint(uint16_t x,uint16_t y)
{
	TouchX = x;
	TouchY = y;
	TouchUp = 0;
}

void GUIGetPoint(uint16_t* x,uint16_t* y)
{
	*x = TouchX;
	*y = TouchY;
}

void GUITouchUp(int16_t xid,int16_t yid)
{
	//暂且先用这个设置
	//如果为 1 表示未释放
	TouchUp = 1 ;
}

void GUITouchDown(uint16_t x,uint16_t y)
{
	TouchX = x;
	TouchY = y;
}

