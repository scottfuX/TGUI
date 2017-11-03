#include "winClass.hpp"

buttonWin::buttonWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue,
			uint32_t winColor
):controlWin(winXpos,winYpos,winWidth,winHigh,name,wsStyle,parent,queue)
{
	this->winColor = winColor;
}

buttonWin::~buttonWin()
{

}

//绘画 就自己 不同的窗口实现不同
void buttonWin::paintWin()
{
	LCD_SetColors(winColor,winColor);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
}

//按钮失焦
void buttonWin::defocusButton()
{
	//绘画成纯灰色
	LCD_SetColors(GREY,GREY);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
}
//按钮按下
void buttonWin::pressButton()
{
	LCD_SetColors(WHITE,WHITE);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	//不准执行窗口过程函数
}

//按钮释放
void buttonWin::releaseButton()
{
	//重绘
	paintWin();
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
