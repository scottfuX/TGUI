#include "layout_class/layoutClass.h"

layoutWin::layoutWin(
			rootWin* backWin,
			uint16_t X,
			uint16_t Y,
			uint16_t Width,
			uint16_t High)
{
	this->backWin = backWin;
	this->layoutX = X;
	this->layoutY = Y;
	this->layoutWidth = Width;	
	this->layoutHigh = High;
	
	this->horizGap = 0;
	this->vertGap = 0;
	
}

layoutWin::~layoutWin()
{

}

