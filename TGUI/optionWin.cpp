#include "winClass.h"

optionWin::optionWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue,
			bool RadioorCheck
			):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	this->RadioorCheck = RadioorCheck;
	selectStat = false;
}

optionWin::~optionWin()
{

}

void optionWin::paintWin()
{
	paintOption();
	optionString();
}	 

void optionWin::defocusOption()	 //选项失焦
{
	//失效
}


void optionWin::clickOption() 	 	//改变选项
{
	setWinSelectedStat(false);
	changSelectStat();
	paintOption();//不必都重绘 只用绘图标
}

//注册
void optionWin::registerWin()
{	  
		rootWin::registerWin();
}
//注销
void optionWin::unregisterWin()
{
		rootWin::unregisterWin();
	
}
//销毁
void optionWin::destroyWin()
{
		rootWin::destroyWin();
	
}

void optionWin::paintInvalid(GUIArea * tarea)
{
	if(RadioorCheck)
	{
		uint16_t r = 	getWinHigh();
		uint16_t x =  getWinHigh()/2+getAbsoluteX();
		uint16_t y =  getWinHigh()/2+getAbsoluteY();
		GUICircle cir(x,y,r/2,GREY2,getInvalidList());
		cir.drawInArea(tarea);
		cir.setColor(BLACK);
		cir.setR(r/2-r/8);
		cir.drawInArea(tarea);
		cir.setColor(WHITE);
		cir.setR(r/2-r/4);
		cir.drawInArea(tarea);

		if(selectStat == true)
		{//选中
			cir.setColor(BLACK);
			cir.setR(r/2-r/3);
			cir.drawInArea(tarea);
		}
		optionString();
	}
	else
	{
		uint16_t x =  getAbsoluteX();
		uint16_t y =  getAbsoluteY();	
		uint16_t w = getWinHigh();
		GUIRectangle a(x,y,w,w,BLACK,getInvalidList());
		a.setIsFull(true);
		a.drawInArea(tarea);
		x += getWinHigh()/10;
		y += getWinHigh()/10;
		w -= getWinHigh()/5;
		a.setX(x);
		a.setY(y);
		a.setW(w);
		a.setH(w);
		a.setColor(WHITE);
		a.drawInArea(tarea);
		if(selectStat == true)
		{//选中//需要线段---待定
			GUILine gline(x,y+w/2,x+w/2,y+w,BLACK,getInvalidList());
			gline.drawInArea(tarea);
			gline.setX1(x+w/2);
			gline.setY1(y+w);
			gline.setX2(x+w);
			gline.setY2(y);
			gline.drawInArea(tarea);
		}
		optionString();
	}
}

//---------------------------------private---------------------------------
void optionWin::changSelectStat()
{
	if(selectStat == false)
	{selectStat = true;}
	else
	{selectStat = false;}
}

void optionWin::optionString()
{
	sFONT f =  getFont();
	if(getWinName() != NULL && getWinHigh() >= f.Height && getWinWidth()-getWinHigh() >= f.Width)
	{
		uint16_t temp;  //打印
		uint8_t i = 0;
		uint16_t line = getAbsoluteY()+(getWinHigh()-f.Height)/2;
		uint16_t column = getAbsoluteX() + getWinHigh()+1;
		GUIChar ctemp(column,line,&f,getTextColor(),((controlWin*)getParent())->getBackColor(),getInvalidList());
		ctemp.setIsFull(false);
		while(getWinName()[i] != '\0' )
		{
			temp = (uint16_t) getWinName()[i];
			ctemp.setCharXY(column,line);
			ctemp.displayChar(temp);
			column += f.Width;
			if(column > getAbsoluteX()+getWinWidth())
			{
				break;
			}
			i++;
		}
	}	
}

//只重绘选项图标
void optionWin::paintOption()
{
	if(RadioorCheck)
	{
		uint16_t r = 	getWinHigh();
		uint16_t x =  getWinHigh()/2+getAbsoluteX();
		uint16_t y =  getWinHigh()/2+getAbsoluteY();
		GUICircle cir(x,y,r/2,GREY2,getInvalidList());
		cir.draw();
		cir.setX(x);
		cir.setY(y);
		cir.setR(r/2-r/8);
		cir.setColor(BLACK);
		cir.draw();
		cir.setX(x);
		cir.setY(y);
		cir.setR(r/2-r/4);
		cir.setColor(WHITE);
		cir.draw();
		if(selectStat == true)
		{//选中
			cir.setX(x);
			cir.setY(y);
			cir.setR(r/2-r/3);
			cir.setColor(BLACK);
			cir.draw();
		}
	}
	else
	{
		uint16_t x =  getAbsoluteX();
		uint16_t y =  getAbsoluteY();	
		uint16_t w = getWinHigh();
		GUIRectangle a(x,y,w,w,BLACK,getInvalidList());
		a.setIsFull(true);
		a.draw();
		x += getWinHigh()/10;
		y += getWinHigh()/10;
		w -= getWinHigh()/5;
		a.setX(x);
		a.setY(y);
		a.setW(w);
		a.setH(w);
		a.setColor(WHITE);
		a.draw();
		if(selectStat == true)
		{//选中//需要线段--待定
			GUILine gline(x,y+w/2,x+w/2,y+w,BLACK,getInvalidList());
			gline.draw();
			gline.setX1(x+w/2);
			gline.setY1(y+w);
			gline.setX2(x+w);
			gline.setY2(y);
			gline.draw();
		}
	}
}
