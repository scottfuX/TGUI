#include "interface_conf/tgui_conf.h"

//id 数值 设置其实ID
volatile uint16_t win_id = 0;
//屏幕缓冲区，当有覆盖时进行存储
uint8_t __EXRAM win_buffer[GUI_BUFSIZE];


volatile uint16_t TouchX_pre = 65535;
volatile uint16_t TouchY_pre = 65535;
volatile uint16_t TouchX = 65535;
volatile uint16_t TouchY = 65535;
volatile uint8_t TouchUp = 0;//检查按键是否释放

void GUIDma2d(uint16_t x ,uint16_t y,uint16_t w,uint16_t h,
	uint32_t textColor,uint32_t backColor)
{
	LCD_SetColors(textColor,backColor);
	LCD_DrawFullRect(x,y,w,h);
}

void GUISetColors(uint32_t textColor,uint32_t backColor)
{
	LCD_SetColors(textColor,backColor);
}

void GUIPutPixel(uint16_t xpos,uint16_t ypos)
{//提供一个绘画一个点的驱动
	PutPixel(xpos,ypos);
}

void GUISetPoint(uint16_t x,uint16_t y)
{
	TouchX = x;
	TouchY = y;
}

void GUIGetPoint(uint16_t* x,uint16_t* y)
{
	*x = TouchX;
	*y = TouchY;
}

void GUIGetPrePoint(uint16_t* x,uint16_t* y)
{
	*x = TouchX_pre;
	*y = TouchY_pre;
}

void GUITouchDown(uint16_t pre_x,uint16_t pre_y,uint16_t x,uint16_t y)
{
	TouchX_pre = pre_x;
	TouchY_pre = pre_y;
	TouchX = x;
	TouchY = y;
	TouchUp = 0;
}

void GUITouchUp(int16_t xid,int16_t yid)
{
	TouchUp = 1 ;
}


//暂时是单点触控
uint8_t getTouchUP()
{
	return TouchUp;
}



