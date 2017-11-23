#include "winClass.h"

progressBarWin::progressBarWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	pBarWidth = 0;
	progressValue = 0;
}
progressBarWin::~progressBarWin()
{
	
}

void progressBarWin::setProgressValue(uint8_t pv)
{
	progressValue = pv;
	pBarWidth = pv*getWinWidth()/100;//设置相应的进度条宽度
	paintAll();
}
	
void progressBarWin::paintWin()
{
	//背景
	LCD_SetTextColor(GREY1);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	//进度条
	if(pBarWidth)
	{
		LCD_SetTextColor(BLUE);
		LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),pBarWidth,getWinHigh());
	}
	
}

void progressBarWin::paintBarWin()
{
	if(pBarWidth)
	{
		LCD_SetTextColor(BLUE);
		LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),pBarWidth,getWinHigh());
	}
}
void progressBarWin::registerWin()
{
	rootWin::registerWin();
}	
void progressBarWin::unregisterWin()
{
	rootWin::unregisterWin();
}
void progressBarWin::destroyWin()
{
	rootWin::destroyWin();
}


