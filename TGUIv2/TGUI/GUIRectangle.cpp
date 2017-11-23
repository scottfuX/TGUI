#include "drawingClass.h"

GUIRectangle::GUIRectangle(
		uint16_t x,
		uint16_t y,
		uint16_t w,
		uint16_t h,
		uint32_t textColor,
		uint32_t backColor
		):GUIShape(textColor,backColor)
{
	this->x1 = x;
	this->y1 = y;
	this->x2 = x+w;
	this->y2 = y+h;
}
		
GUIRectangle::~GUIRectangle()
{

}
	

//DMA2D模式
/*
*|---------------| 5个矩形----进行递归
*|--|---------|--|	
*|	| invlidal|	 |
*|--|---------|--|
*|---------------|	
*/
void GUIRectangle::drawFull()
{
#if HAVE_DMA2D
	if(getInvalidList() && getInvalidList()->getNum())//有覆盖区
	{
		rectCut(x1,y1,x2,y2);
	}
	else
	{
		GUIDma2d(x1,y1,(x2-x1),(y2-y1),getTextColor(),getBackColor());
	}
//非DMA2D模式
#else
	uint16_t w = x2 - x1;
	uint16_t h = y2 - y1;
	if(getInvalidArea())
	{
		GUIArea* inarea = getInvalidArea();
		for(int i=0;i < h;i++)
		{
			for(int j=0;j < w;j++)
			{
				if(x1+j >= inarea->getX1() && x1+j <= inarea->getX2()
					&& y1+i >= inarea->getY1() && y1+i <= inarea->getY2())
				{
					continue;
				}
				putPixel(x1+j,y1+i);
			}
		}
	}
	else
	{
		for(int i=0;i < h;i++)
		{
			for(int j=0;j < w;j++)
			{
				putPixel(x1+j,y1+i);
			}
		}
	}
	
#endif
}

void GUIRectangle::draw()
{
//DMA2D模式
#if HAVE_DMA2D

//非DMA2D模式
#else
	uint16_t w = x2 - x1;
	uint16_t h = y2 - y1;
	if(getInvalidArea())
	{
		GUIArea* inarea = getInvalidArea();
		for(int i=0;i < h;i++)
		{
			for(int j=0;j < w;j++)
			{
				if(!(j%(w-1))||!(i%(h-1)))
				{
					if(x1+j >= inarea->getX1() && x1+j <= inarea->getX2()
					&& y1+i >= inarea->getY1() && y1+i <= inarea->getY2())
					{continue;}
					putPixel(x1+j,y1+i);
				}
			}
		}
	}
	else
	{
	for(int i=0;i < h;i++)
		{
			for(int j=0;j < w;j++)
			{
				if(!(j%(w-1))||!(i%(h-1)))
				{
					putPixel(x1+j,y1+i);
				}
			}
		}
	}
#endif
}

void GUIRectangle::rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
		//记下当前的位置节点位置
	GUIArea* inarea = NULL;
	GUINode<GUIArea>* node = NULL;
	while(getInvalidList()->getNextData() != NULL)
	{
		GUIArea* a1 = new GUIArea(x1,y1,x2,y2);
		inarea = rectIntersect(a1,getInvalidList()->getCurrData());
		delete a1;
		if(inarea != NULL)//有交界区
		{
			node = getInvalidList()->getCurrNode();
			break;
		}
	}
	//遍历链表，出现交界就进入矩形切割，若为出现继续遍历，最后还是未出现，说明没有交界，全部画出
	if(inarea != NULL)
	{
		
		uint16_t xt1,yt1,xt2,yt2;
		//绘画上面部分的区域
		xt1 = x1;
		yt1 = y1;
		xt2 = x2;
		yt2 = inarea->getY1();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2);
		}
		//绘画左边部分的区域
		
		xt1 = x1;
		yt1 = inarea->getY1();
		xt2 = inarea->getX1();
		yt2 = inarea->getY2();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2);
		}
		//绘画右边部分的区域
		xt1 = inarea->getX2();
		yt1 = inarea->getY1();
		xt2 = x2;
		yt2 = inarea->getY2();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2);
		}
		//绘画下面部分的区域
		xt1 = x1;
		yt1 = inarea->getY2();
		xt2 = x2;
		yt2 = y2;
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
				rectCut(xt1,yt1,xt2,yt2);
		}
	}
	else//没有就直接画出来
	{
		GUIDma2d(x1,y1,(x2-x1),(y2-y1),getTextColor(),getBackColor());
	}
}
//交集
GUIArea* GUIRectangle::rectIntersect(GUIArea* area1,GUIArea* area2)
{
	uint16_t Xt1 = max(area1->getX1(),area2->getX1());
	uint16_t Yt1 = max(area1->getY1(),area2->getY1());
	uint16_t Xt2 = min(area1->getX2(),area2->getX2());
	uint16_t Yt2 = min(area1->getY2(),area2->getY2());
	if(Xt1 <= Xt2 && Yt1 <= Yt2)//判断是否相交
	{
		return new GUIArea(Xt1,Yt1,Xt2,Yt2);
	}
	return NULL;
}

uint16_t GUIRectangle::max(uint16_t n,uint16_t m)
{
	return n > m ? n : m;
}

uint16_t GUIRectangle::min(uint16_t n,uint16_t m)
{
	return n < m ? n : m;
}



void GUIRectangle::putPixel(uint16_t x, uint16_t y)
{
 if( x > GUI_WIDTH ||  y > GUI_HIGH)
 {
   return;
 }
#if HAVE_DMA2D
 LCD_DrawLine(x, y, 1, LCD_DIR_HORIZONTAL);
#else
 {
	uint32_t  Xaddress = 0;
    Xaddress = (uint32_t)GUI_BUFADDR + GUI_PIXELSIZE*(GUI_WIDTH*y + x);
    *(__IO uint16_t*) Xaddress = (uint16_t)getTextColor();
#if (GUI_PIXELSIZE-2)
		*(__IO uint8_t*)( Xaddress+2)= (0xFF0000 & getTextColor()) >> 16;
#endif
  }
#endif
}
