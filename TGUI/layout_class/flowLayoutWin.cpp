#include "layout_class/layoutClass.h"

flowLayoutWin::flowLayoutWin(
	rootWin* backWin,	
	uint16_t X,			
	uint16_t Y,
	uint16_t Width,
	uint16_t High,
	uint16_t Hgap,
	uint16_t Vgap
	):layoutWin(backWin,X,Y,Width,High)
{
	setHorizGap(Hgap);
	setVertGap(Vgap);
	residualW = Width - Hgap;
	residualH = High - Vgap;
	maxH = 0;
}

flowLayoutWin::~flowLayoutWin()
{
	
}


//流式布局 超过就换行
void flowLayoutWin::addWin(rootWin* rw)
{
	if((rw->getWinWidth() + getHorizGap()) <= residualW )		
	{
		if((rw->getWinHigh() + getVertGap()) <= residualH)
		{//宽高 都小于
			rw->setWinXpos(getLayoutX()+getLayoutWidth()-residualW);
			rw->setWinYpos(getLayoutY()+getLayoutHigh()-residualH);
			rw->setParent(getBackWin());
			residualW -= (rw->getWinWidth()+getHorizGap());
			if(maxH < (rw->getWinHigh() + getVertGap()))
			{
				maxH  = (rw->getWinHigh() + getVertGap());
			}
		}
	}else if((rw->getWinWidth() + 2*getHorizGap()) <= getLayoutWidth() )
	{//换行
		residualH -= maxH;
		residualW = getLayoutWidth() - getHorizGap();
		maxH = 0;
		if((rw->getWinHigh() + getVertGap()) <= residualH)
		{
			rw->setWinXpos(getLayoutX()+getLayoutWidth()-residualW);
			rw->setWinYpos(getLayoutY()+getLayoutHigh()-residualH);
			residualW -= (rw->getWinWidth()+getHorizGap());
			maxH = (rw->getWinHigh() + getVertGap());
		}
	}
}
