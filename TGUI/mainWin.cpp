#include "winClass.hpp"

mainWin::mainWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue,
			uint8_t wsStyle
):rootWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	this->wsStyle = wsStyle;
}

mainWin::~mainWin()
{

}

//绘画 就自己 不同的窗口实现不同
void mainWin::paintWin()
{
	;
}

//激活控件--注册 中间会调用createWin（其他根据不同的窗口变化）
void mainWin::registerWin()
{
	rootWin::registerWin();
}

//注销控件  会调用destroy（窗口 其他会根据不同窗口变化）
void mainWin::unregisterWin()
{
	rootWin::unregisterWin();
}

void mainWin::destroyWin()
{
	rootWin::destroyWin();
}
