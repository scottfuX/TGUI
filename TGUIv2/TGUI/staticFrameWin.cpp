#include "winClass.hpp"

staticFrameWin::staticFrameWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue
):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
}

staticFrameWin::~staticFrameWin()
{

}

//绘画 就自己 不同的窗口实现不同
void staticFrameWin::paintWin()
{
	LCD_SetColors(getBackColor(),getBackColor());
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	displayStrCenter(getFont(),getTextColor(),getBackColor(),getWinName());
}

//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
void staticFrameWin::registerWin()
{
	rootWin::registerWin();
}

//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
void staticFrameWin::unregisterWin()
{
	rootWin::unregisterWin();
}

void staticFrameWin::destroyWin()
{
	rootWin::destroyWin();
}

 

