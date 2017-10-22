#include "winClass.h"

rootWin::rootWin()
{
	this->winTitle = &(this->id);
	this->winXpos = 0;
	this->winYpos = 0;
	this->winWidth = GUI_WIDTH;
	this->winHigh = GUI_HIGH;
	this->backColor = BACK_COLOR;
	this->statBarColor = STAT_COLOR;
}

rootWin::rootWin(uint8_t* winTitle,uint16_t winXpos,uint16_t winYpos,\
	uint16_t winWidth,uint16_t winHigh)
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



