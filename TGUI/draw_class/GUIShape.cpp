#include "drawingClass.h"


GUIShape::GUIShape(uint32_t color,GUIList<GUIArea> * tempList)
{
	this->color = color;
	this->invalidList = tempList;
	this->isFull = true;
}

GUIShape::~GUIShape()
{

}
	

//画一个矩形 DMA2D/循环实现
void GUIShape::drawShape(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint32_t color)
{
#if  HAVE_DMA2D
	GUIDma2d(x,y,w,h,color,color);
#else //循环画图
	for(uint16_t i=0;i < h;i++)
	{
		for(uint16_t j=0;j < w;j++)
		{
			putPixel(x+j,y+i);
			//可以只画框
			//if(!(j%(w-1))||!(i%(h-1))){putPixel(x+j,y+i);}
		}
	}
#endif
}

//画一个点
void GUIShape::putPixel(uint16_t x,uint16_t y)
{
	if( x > GUI_WIDTH ||  y > GUI_HIGH)
	{
		return;
	}
	uint32_t  Xaddress = 0;
	Xaddress = (uint32_t)GUI_BUFADDR + GUI_PIXELSIZE*(GUI_WIDTH*y + x);
	*(__IO uint16_t*) Xaddress = (uint16_t)getColor();
#if (GUI_PIXELSIZE-2)
	*(__IO uint8_t*)(Xaddress+2)= (0xFF0000 & getColor()) >> 16;
#endif
}

//交集
GUIArea* GUIShape::rectIntersect(GUIArea* area1,GUIArea* area2)
{
	uint16_t Xt1 = max(area1->getX1(),area2->getX1());
	uint16_t Yt1 = max(area1->getY1(),area2->getY1());
	uint16_t Xt2 = min(area1->getX2(),area2->getX2());
	uint16_t Yt2 = min(area1->getY2(),area2->getY2());
	if(Xt1 < Xt2 && Yt1 < Yt2)//判断是否相交
	{
		return new GUIArea(Xt1,Yt1,Xt2,Yt2);
	}
	return NULL;
}

void GUIShape::rectIntersect(GUIArea* area1,GUIArea* area2,GUIArea* out)
{
	uint16_t Xt1 = max(area1->getX1(),area2->getX1());
	uint16_t Yt1 = max(area1->getY1(),area2->getY1());
	uint16_t Xt2 = min(area1->getX2(),area2->getX2());
	uint16_t Yt2 = min(area1->getY2(),area2->getY2());
	if(Xt1 < Xt2 && Yt1 < Yt2)//判断是否相交
	{
		(out)->setX1(Xt1);
		(out)->setY1(Yt1);
		(out)->setX2(Xt2);
		(out)->setY2(Yt2);
		return;
	}
	(out) = NULL;
}

uint16_t GUIShape::max(uint16_t n,uint16_t m)
{
	return n >= m ? n : m;
}

uint16_t GUIShape::min(uint16_t n,uint16_t m)
{
	return n < m ? n : m;
}

