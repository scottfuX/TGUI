#include "winClass.h"

gridLayoutWin::gridLayoutWin(
		rootWin* backWin,	
		uint16_t X,			
		uint16_t Y,
		uint16_t Width,
		uint16_t High,
		uint8_t  row,
		uint8_t  column
		):layoutWin(backWin,X,Y,Width,High)
{
	this->row = row;
	this->column = column;
	currSeat = 0;
	gridW = getLayoutWidth()/column;
	gridH = getLayoutHigh()/row;
}

gridLayoutWin::~gridLayoutWin()
{

}

void gridLayoutWin::generateGridWH(uint16_t horizGap,uint16_t vertGap)
{
	gridW = (getLayoutWidth() -  vertGap)/column - vertGap;
	gridH = (getLayoutHigh() -  horizGap)/row - horizGap;
	setHorizGap(horizGap);
	setVertGap(vertGap);
}

void gridLayoutWin::addWin(rootWin* rw)
{
	if(currSeat < row*column && rw->getWinWidth() <= gridW && rw->getWinHigh() <= gridH )
	{
		uint16_t x = getLayoutX() + getVertGap() + (gridW + getVertGap())*(currSeat%column);
		uint16_t y = getLayoutY() + getHorizGap() + (gridH + getHorizGap())*(currSeat/column);
		rw->setWinXpos(x + (gridW - rw->getWinWidth())/2);
		rw->setWinYpos(y + (gridH - rw->getWinHigh())/2);
		rw->setParent(getBackWin());
		currSeat ++;
	}
}
	
