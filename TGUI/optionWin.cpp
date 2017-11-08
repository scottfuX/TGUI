#include "winClass.hpp"

optionWin::optionWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
			):controlWin(winXpos,winYpos,winWidth,winHigh,name,wsStyle,parent,queue)
{
	selectStat = false;
}

optionWin::~optionWin()
{

}

void optionWin::paintWin()
{
		//绘画 就自己 不同的窗口实现不同
	paintOption();
	sFONT f =  getFont();
	if(getWinName() != NULL && getWinHigh() >= f.Height && getWinWidth()-getWinHigh() >= f.Width)
	{//打印
		LCD_SetFont(&f);
		LCD_SetColors(getTextColor(),((controlWin*)getParent())->getBackColor());
		uint16_t temp;
		uint8_t i = 0;
		uint16_t line = getAbsoluteY()+(getWinHigh()-f.Height)/2;
		uint16_t column = getAbsoluteX() + getWinHigh()+1;
		while(getWinName()[i] != '\0' )
		{
			temp = (uint16_t) getWinName()[i];
			LCD_DisplayChar(line,column,temp);
			column += f.Width;
			if(column > getAbsoluteX()+getWinWidth())
			{
				break;
			}
				i++;
		}
	}	
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

//---------------------------------private---------------------------------
void optionWin::changSelectStat()
{
	if(selectStat == false)
	{selectStat = true;}
	else
	{selectStat = false;}
}

//只重绘选项图标
void optionWin::paintOption()
{
	uint16_t r = 	getWinHigh();
	uint16_t x =  getWinHigh()/2+getAbsoluteX();
	uint16_t y =  getWinHigh()/2+getAbsoluteY();
	
	LCD_SetColors(GREY2,GREY2);
	LCD_DrawFullCircle(x,y,r/2);
	LCD_SetColors(BLACK,BLACK);
	LCD_DrawFullCircle(x,y,r/2-r/8);
	LCD_SetColors(WHITE,WHITE);
	LCD_DrawFullCircle(x,y,r/2-r/4);
	
	if(selectStat == true)
	{//选中
		LCD_SetColors(BLACK,BLACK);
		LCD_DrawFullCircle(x,y,r/2-r/3);
	}
	LCD_SetColors(getTextColor(),((controlWin*)(this->getParent()))->getBackColor());
}
