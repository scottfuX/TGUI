#include "winClass.h"

buttonWin::buttonWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue
):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	setTextColor(BLACK);
	setBackColor(GREY1);
}

buttonWin::~buttonWin()
{

}

//绘画 就自己 不同的窗口实现不同
void buttonWin::paintWin()
{	
	GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),getBackColor(),getInvalidList());
	a.setIsFull(true);
	a.draw();
	a.setIsFull(false);
	a.setColor(getTextColor());
	a.draw();
	//字就从头打好了
	displayStrCenter(getFont(),getTextColor(),getBackColor(),getWinName());
}

void buttonWin::paintInvalid(GUIArea * tarea)
{printf("button...\n");
	GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),getBackColor(),getInvalidList());
	a.setIsFull(true);
	a.drawInArea(tarea);
	a.setIsFull(false);
	a.setColor(getTextColor());
	a.drawInArea(tarea);
	//字就从头打好了
	displayStrCenter(getFont(),getTextColor(),getBackColor(),getWinName());
}

//按钮失焦
void buttonWin::defocusButton()
{
	//绘画成纯灰色
		GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),GREY,getInvalidList());
		a.setIsFull(true);
		a.draw();
		a.setIsFull(false);
		a.setColor(getTextColor());
		a.draw();
		displayStrCenter(getFont(),getTextColor(),getBackColor(),getWinName());
}

//按钮按下
void buttonWin::pressButton()
{
	if(!isWinSelected())//之前未被选中 改为选中
	{
		GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),WHITE,getInvalidList());
		a.setIsFull(true);
		a.draw();
		a.setIsFull(false);
		a.setColor(getTextColor());
		a.draw();
		displayStrCenter(getFont(),getTextColor(),WHITE,getWinName());
		changSelectedStat();		
	}
}


//按钮释放
void buttonWin::releaseButton()
{
	if(isWinSelected())//若之前选中 改为未选中
	{
		paintAll();
		changSelectedStat();
	}
}

//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
void buttonWin::registerWin()
{
	rootWin::registerWin();
}

//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
void buttonWin::unregisterWin()
{
	rootWin::unregisterWin();
}

void buttonWin::destroyWin()
{
	rootWin::destroyWin();
}
