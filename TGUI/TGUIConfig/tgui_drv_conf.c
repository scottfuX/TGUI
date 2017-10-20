#include "TGUIConfig/tgui_drv_conf.h"
volatile uint16 TouchX = 65535;
volatile uint16 TouchY = 65535;
volatile uint8 TouchUp = 0;//未被按下

void GUISetPoint(uint16 x,uint16 y)
{
	TouchX = x;
	TouchY = y;
}

void GUIGetPoint(uint16* x,uint16* y)
{
	*x = TouchX;
	*y = TouchY;
}

void GUITouchUp(int16 xid,int16 yid)
{
	//释放函数 暂时不处理 只是出现一个标志位
	TouchUp = 1 ;
}

void GUITouchDown(uint16 x,uint16 y)
{
	TouchX = x;
	TouchY = y;
}
