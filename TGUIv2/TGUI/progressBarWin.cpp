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
	//paintWin();
	if(pBarWidth)
	{
		GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),BLUE,getInvalidList());
		a.setIsFull(true);
		a.setW(pBarWidth);
		a.draw();

	}
}
	
void progressBarWin::paintWin()
{
	//背景
	GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),GREY1,getInvalidList());
	a.setIsFull(true);
	a.draw();
	//进度条
	if(pBarWidth)
	{
		a.setColor(BLUE);
		a.setW(pBarWidth);
		a.draw();
	}
}

void progressBarWin::paintInvalid(GUIArea * tarea)
{
	//背景
	GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),GREY1,getInvalidList());
	a.setIsFull(true);
	a.drawInArea(tarea);
	//进度条
	if(pBarWidth)
	{
		a.setColor(BLUE);
		a.setW(pBarWidth);
		a.drawInArea(tarea);
	}
}


void progressBarWin::paintBarWin()
{
	if(pBarWidth)
	{
		GUIRectangle a(getAbsoluteX(),getAbsoluteY(),pBarWidth,getWinHigh(),BLUE,getInvalidList());
		a.draw();
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


