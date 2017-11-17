#include "winClass.hpp"

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
	LCD_SetColors(getBackColor(),getBackColor());
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	LCD_SetColors(getTextColor(),getTextColor());
	LCD_DrawRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	displayStrCenter(getFont(),getTextColor(),getBackColor(),getWinName());
}

//按钮失焦
void buttonWin::defocusButton()
{
	//绘画成纯灰色
	LCD_SetColors(GREY,GREY);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	LCD_SetColors(getTextColor(),getTextColor());
	LCD_DrawRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	displayStrCenter(getFont(),BLACK,GREY,getWinName());
}

//按钮按下
void buttonWin::pressButton()
{
	if(!isWinSelected())//之前未被选中 改为选中
	{
		LCD_SetColors(WHITE,WHITE);
		LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
		LCD_SetColors(getTextColor(),getTextColor());
		LCD_DrawRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
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
