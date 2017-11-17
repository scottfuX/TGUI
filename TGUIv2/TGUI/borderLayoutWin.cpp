#include "winClass.hpp"

borderLayoutWin::borderLayoutWin(
	rootWin* backWin,	
	uint16_t X,			
	uint16_t Y,
	uint16_t Width,
	uint16_t High
	):layoutWin(backWin,X,Y,Width,High)
{
	northH = 0;
	southH = 0;
	westW = 0;
	eastW = 0;
	layoutStat =0;
}
borderLayoutWin::~borderLayoutWin()
{
}

//有空位就填入 不推荐
void borderLayoutWin::addWin(rootWin* rw)
{
	uint8_t temp,i;
	for(i=0 ; i<5 ; i++)
	{
		temp = (layoutStat & (1<<i));
		if(!temp)
		{
			addWin(rw,i);
			break;
		}
	}
}

/** |--------------|  seat 0
*		|--------------|
*		|  |        |  |
*		|  |			  |  |  seat 2 seat 4 seat 3
*		|--------------| 
*		|--------------|  seat 1
**/  //ָ指定位置填入 推荐
void borderLayoutWin::addWin(rootWin* rw,uint16_t seat)
{
	if(seat == 0)//north
	{
		if(rw->getWinHigh() <= northH && rw->getWinWidth() <= getLayoutWidth())
		{
			rw->setWinXpos((getLayoutWidth() - rw->getWinWidth())/2);
			rw->setWinYpos((northH -  rw->getWinHigh())/2);
			rw->setParent(getBackWin());
			layoutStat |= 1;  //00001 标志是否被填
		}
	}else if(seat == 1)//south
	{
		if(rw->getWinHigh() <= southH && rw->getWinWidth() <= getLayoutWidth())
		{
			uint16_t sY = getLayoutHigh() -  southH;
			rw->setWinXpos((getLayoutWidth() - rw->getWinWidth())/2);
			rw->setWinYpos( sY + (southH -  rw->getWinHigh())/2);
			rw->setParent(getBackWin());
			layoutStat |= 2;  //00010
		}
	}else if(seat == 2)//west
	{
		uint16_t wH = getLayoutHigh() - northH - southH - 2*getHorizGap();
		if(rw->getWinHigh() <= wH && rw->getWinWidth() <= westW)
		{
			rw->setWinXpos((westW - rw->getWinWidth())/2);
			rw->setWinYpos(northH + getHorizGap() + (wH -  rw->getWinHigh())/2);
			rw->setParent(getBackWin());
			layoutStat |= 4; //00100
		}
	}else if(seat == 3)//east
	{
		uint16_t eH = getLayoutHigh() - northH - southH - 2*getHorizGap();
		uint16_t eX = getLayoutWidth() - eastW;
		if(rw->getWinHigh() <= eH && rw->getWinWidth() <= eastW)
		{
			rw->setWinXpos(eX + (eastW - rw->getWinWidth())/2);
			rw->setWinYpos(northH + getHorizGap() + (eH -  rw->getWinHigh())/2);
			rw->setParent(getBackWin());
			layoutStat |= 8; //01000
		}
	}else{						//center
		uint16_t cX = westW + getVertGap();
		uint16_t cH = getLayoutHigh() - northH - southH - 2*getHorizGap();
		if(rw->getWinHigh() <= cH && rw->getWinWidth() <= (getLayoutWidth() - eastW - westW - getVertGap()))
		{
			rw->setWinXpos(cX + (getLayoutWidth() - cX - eastW - getHorizGap()- rw->getWinWidth())/2);
			rw->setWinYpos(northH + getHorizGap() + (cH -  rw->getWinHigh())/2);
			rw->setParent(getBackWin());
			layoutStat |= 16; //10000
		}
	}	
}

void borderLayoutWin::setBorderSize(uint16_t northH,uint16_t southH,uint16_t westW,uint16_t eastW)
{
	if(northH + southH +2*getHorizGap() <= getLayoutHigh() && westW + eastW +2*getVertGap() <= getLayoutWidth())
	{
		this->northH = northH;
		this->southH = southH;
		this->westW = westW;
		this->eastW = eastW;
	}
}
