#include "winClass.h"

rootWin::rootWin()
{
	uint8 defaultTitle[]= "default Title";//内存回收的问题
	this->winTitle = defaultTitle;
	this->winXpos = 0;
	this->winYpos = 0;
	this->winWidth = GUI_WIDTH;
	this->winHigh = GUI_HIGH;
	this->backColor = BACK_COLOR;
	this->statBarColor = STAT_COLOR;
}

rootWin::rootWin(uint8* winTitle,uint16 winXpos,uint16 winYpos,\
	uint16 winWidth,uint16 winHigh)
{
	this->winTitle = winTitle;
	this->winXpos = winXpos;
	this->winYpos = winYpos;
	this->winWidth = winWidth;
	this->winHigh = winHigh;
	this->backColor = BACK_COLOR;
	this->statBarColor = STAT_COLOR;
}

rootWin::~rootWin(){
	printf("rootWin exit");
}



