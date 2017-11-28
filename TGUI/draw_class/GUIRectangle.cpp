#include "drawingClass.h"

GUIRectangle::GUIRectangle(
		uint16_t x,
		uint16_t y,
		uint16_t w,
		uint16_t h,
		uint32_t color,
		GUIList<GUIArea> * tempList
		):GUIShape(color,tempList)
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
void GUIRectangle::draw()
{
	if(getIsFull())//画实心矩形
	{
		if(getInvalidList() && getInvalidList()->getNum())//有覆盖区
		{
			getInvalidList()->resetCurrNode(); //重制当前下标
			rectCut(x1,y1,x2,y2);//递归
		}
		else
		{
			drawShape(x1,y1,(x2-x1),(y2-y1),getColor());
		}
	}
	else //画空心矩形
	{
		if(getInvalidList() && getInvalidList()->getNum())//有覆盖区
		{
			getInvalidList()->resetCurrNode();//重制当前下标
			rectCut(x1,y1,x2,y1+1);						//递归 上横
			getInvalidList()->resetCurrNode();
			rectCut(x1,y1,x1+1,y2);						//递归 左竖
			getInvalidList()->resetCurrNode();
			rectCut(x2-1,y1,x2,y2);						//递归 右竖
			getInvalidList()->resetCurrNode();
			rectCut(x1,y2-1,x2,y2);						//递归 下横
		}
		else
		{
			drawShape(x1,y1,x2-x1,1,getColor());
			drawShape(x1,y1,1,y2-y1,getColor());
			drawShape(x2,y1,1,y2-y1,getColor());
			drawShape(x1,y2,x2-x1,1,getColor());
		}
	}
	
}

void GUIRectangle::drawInArea(GUIArea * tarea)
{
	if(getIsFull())
	{
		GUIArea atemp(x1,y1,x2,y2);
		GUIArea* interarea = rectIntersect(&atemp,tarea);//和原本的进行区域进行交集
		if(interarea != NULL)
		{
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2());//递归绘画
		}
		delete interarea;
	}
	else
	{
		GUIArea atemp(x1,y1,x2,y1+1);
		GUIArea* interarea = rectIntersect(&atemp,tarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2());//递归绘画
		}
		delete interarea;
		
		atemp.setX1(x1);
		atemp.setY1(y1);
		atemp.setX2(x1-1);
		atemp.setY2(y2);
		interarea = rectIntersect(&atemp,tarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2());//递归绘画
		}
		delete interarea;
		
		atemp.setX1(x2-1);
		atemp.setY1(y1);
		atemp.setX2(x2);
		atemp.setY2(y2);
		interarea = rectIntersect(&atemp,tarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2());//递归绘画
		}	
		delete interarea;		
		
		atemp.setX1(x1);
		atemp.setY1(y2-1);
		atemp.setX2(x2);
		atemp.setY2(y2);
		interarea = rectIntersect(&atemp,tarea);//和原本的进行区域进行交集
		if(interarea != NULL)//有交界区
		{		
			rectCut(interarea->getX1(),interarea->getY1(),interarea->getX2(),interarea->getY2());//递归绘画
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
void GUIRectangle::rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	//记下当前的位置节点位置
	GUIArea* inarea = NULL;
	GUINode<GUIArea>* node = NULL;
	if(getInvalidList() != NULL)
	{
		GUIArea a1(x1,y1,x2,y2);
		while(getInvalidList()->getNextData() != NULL)
		{
			inarea = rectIntersect(&a1,getInvalidList()->getCurrData());
			if(inarea != NULL)//有交界区
			{
				node = getInvalidList()->getCurrNode();
				break;
			}
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
		delete inarea;
	}
	else//没有就直接画出来
	{
		drawShape(x1,y1,(x2-x1),(y2-y1),getColor());
	}
}



