#include "drawFunc.h"


static uint16_t max(uint16_t n,uint16_t m);
static uint16_t min(uint16_t n,uint16_t m);
static void rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,controlWin* cw,uint32_t textColor,uint32_t backColor);
static GUIArea* rectIntersect(GUIArea* area1,GUIArea* area2);
static void rectIntersect(GUIArea* area1,GUIArea* area2,GUIArea** out);
static void drawShape(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint32_t textColor,uint32_t backColor);//画一个矩形 DMA2D/循环实现
static void putPixel(uint16_t x,uint16_t y,uint32_t textColor);

void drawRect(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,controlWin* cw,uint32_t textColor,uint32_t backColor,bool isFull)
{
	if(isFull)//画实心矩形
	{
		if(cw->getInvalidList() && cw->getInvalidList()->getNum())//有覆盖区
		{
			cw->getInvalidList()->resetCurrNode(); //重制当前下标
			rectCut(x1,y1,x2,y2,cw,textColor,backColor);//递归
		}
		else
		{
			drawShape(x1,y1,(x2-x1),(y2-y1),textColor,backColor);
		}
	}
	else //画空心矩形
	{
		if(cw->getInvalidList() && cw->getInvalidList()->getNum())//有覆盖区
		{
			cw->getInvalidList()->resetCurrNode();//重制当前下标
			rectCut(x1,y1,x2,y1+1,cw,textColor,backColor);						//递归 上横
			cw->getInvalidList()->resetCurrNode();
			rectCut(x1,y1,x1+1,y2,cw,textColor,backColor);						//递归 左竖
			cw->getInvalidList()->resetCurrNode();
			rectCut(x2-1,y1,x2,y2,cw,textColor,backColor);						//递归 右竖
			cw->getInvalidList()->resetCurrNode();
			rectCut(x1,y2-1,x2,y2,cw,textColor,backColor);						//递归 下横
		}
		else
		{
			drawShape(x1,y1,x2-x1,1,textColor,backColor);
			drawShape(x1,y1,1,y2-y1,textColor,backColor);
			drawShape(x2,y1,1,y2-y1,textColor,backColor);
			drawShape(x1,y2,x2-x1,y2-y1,textColor,backColor);
		}
	}
}

void drawInArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,GUIArea * tarea,controlWin* cw,uint32_t textColor,uint32_t backColor,bool isFull)
{
	if(isFull)
	{
		GUIArea* atemp = new GUIArea(x1,y1,x2,y2);
		GUIArea* interarea = rectIntersect(atemp,tarea);//和原本的进行区域进行交集
		delete atemp;
		rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2(),cw,textColor,backColor);//递归绘画
		delete interarea;
	}
	else
	{
		GUIArea* atemp = new GUIArea(x1,y1,x2,y1+1);
		GUIArea* interarea = rectIntersect(atemp,tarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2(),cw,textColor,backColor);//递归绘画
		}
		
		atemp->setX1(x1);
		atemp->setY1(y1);
		atemp->setX2(x1-1);
		atemp->setY2(y2);
		rectIntersect(atemp,tarea,&interarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2(),cw,textColor,backColor);//递归绘画
		}
		
		atemp->setX1(x2-1);
		atemp->setY1(y1);
		atemp->setX2(x2);
		atemp->setY2(y2);
		rectIntersect(atemp,tarea,&interarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2(),cw,textColor,backColor);//递归绘画
		}		
		
		atemp->setX1(x1);
		atemp->setY1(y2-1);
		atemp->setX2(x2);
		atemp->setY2(y2);
		rectIntersect(atemp,tarea,&interarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2(),cw,textColor,backColor);//递归绘画
		}		
		delete interarea;
	}
}

/*
*|---------------| 5个矩形----进行递归
*|--|---------|--|	
*|	| invlidal|	 |
*|--|---------|--|
*|---------------|	
*/
static void rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,controlWin* cw,uint32_t textColor,uint32_t backColor)
{
	//记下当前的位置节点位置
	GUIArea* inarea = NULL;
	GUINode<GUIArea>* node = NULL;
	while(cw->getInvalidList()->getNextData() != NULL)
	{
		GUIArea* a1 = new GUIArea(x1,y1,x2,y2);
		inarea = rectIntersect(a1,cw->getInvalidList()->getCurrData());
		delete a1;
		if(inarea != NULL)//有交界区
		{
			node = cw->getInvalidList()->getCurrNode();
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
			cw->getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,cw,textColor,backColor);
		}
		//绘画左边部分的区域
		
		xt1 = x1;
		yt1 = inarea->getY1();
		xt2 = inarea->getX1();
		yt2 = inarea->getY2();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			cw->getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,cw,textColor,backColor);
		}
		//绘画右边部分的区域
		xt1 = inarea->getX2();
		yt1 = inarea->getY1();
		xt2 = x2;
		yt2 = inarea->getY2();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			cw->getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,cw,textColor,backColor);
		}
		//绘画下面部分的区域
		xt1 = x1;
		yt1 = inarea->getY2();
		xt2 = x2;
		yt2 = y2;
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			cw->getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,cw,textColor,backColor);
		}
		delete inarea;
	}
	else//没有就直接画出来
	{
		drawShape(x1,y1,(x2-x1),(y2-y1),textColor,backColor);
	}
}

//交集
static GUIArea* rectIntersect(GUIArea* area1,GUIArea* area2)
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

static void rectIntersect(GUIArea* area1,GUIArea* area2,GUIArea** out)
{
	uint16_t Xt1 = max(area1->getX1(),area2->getX1());
	uint16_t Yt1 = max(area1->getY1(),area2->getY1());
	uint16_t Xt2 = min(area1->getX2(),area2->getX2());
	uint16_t Yt2 = min(area1->getY2(),area2->getY2());
	if(Xt1 <= Xt2 && Yt1 <= Yt2)//判断是否相交
	{
		(*out)->setX1(Xt1);
		(*out)->setY1(Yt1);
		(*out)->setX2(Xt2);
		(*out)->setY2(Yt2);
		return;
	}
	(*out) = NULL;
}


//画一个矩形 DMA2D/循环实现
static void drawShape(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint32_t textColor,uint32_t backColor)
{
#if  HAVE_DMA2D
	GUIDma2d(x,y,w,h,textColor,backColor);
#else //循环画图
	for(uint16_t i=0;i < h;i++)
	{
		for(uint16_t j=0;j < w;j++)
		{
			putPixel(x+j,y+i,textColor);
			//可以只画框
			//if(!(j%(w-1))||!(i%(h-1))){putPixel(x+j,y+i);}
		}
	}
#endif
}

//画一个点
static void putPixel(uint16_t x,uint16_t y,uint32_t textColor)
{
	if( x > GUI_WIDTH ||  y > GUI_HIGH)
	{
		return;
	}
	uint32_t  Xaddress = 0;
	Xaddress = (uint32_t)GUI_BUFADDR + GUI_PIXELSIZE*(GUI_WIDTH*y + x);
	*(__IO uint16_t*) Xaddress = (uint16_t)textColor;
#if (GUI_PIXELSIZE-2)
	*(__IO uint8_t*)(Xaddress+2)= (0xFF0000 & textColor) >> 16;
#endif
}


static uint16_t max(uint16_t n,uint16_t m)
{
	return n > m ? n : m;
}

static uint16_t min(uint16_t n,uint16_t m)
{
	return n < m ? n : m;
}





