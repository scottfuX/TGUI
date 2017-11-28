#include "winClass.h"

controlWin::controlWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue
):rootWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	textColor = BLACK;
	backColor = GREY;
	font = Font16x24;
}

controlWin::~controlWin()
{

}

//add
void controlWin::addInvalidArea(GUIArea * tarea)
{
	if(invalidList == NULL)
	{
			invalidList = new GUIList<GUIArea>();
	}
	invalidList->addNode(tarea);
}

//del
void controlWin::delInvalidArea(GUIArea * tarea)
{
	invalidList->resetCurrNode();
	getInvalidList()->delNode(tarea);
	if(getInvalidList()->getNum() == 0)
	{	
		getInvalidList()->destroyList();
		setInvalidList(NULL);
	}
}

//中心打印
void controlWin::displayStrCenter(sFONT font,uint32_t textColor,uint32_t backColor,char* str)
{
	if(str != NULL){
		uint16_t temp;
		uint8_t i = 0,num  = 0;
		while(str[num] != '\0' )
		{
			num++;
			if((getWinWidth()- font.Width*num) <= 0)
			{
				num--;
				break;
			}
		}
		uint16_t line = getAbsoluteY() + ((getWinHigh()- font.Height)/2);
		uint16_t column = getAbsoluteX() + ((getWinWidth()- font.Width*num)/2);
		//创建对象
	  GUIChar ctemp(column,line,&font,textColor,backColor,getInvalidList());
		//ctemp.setIsFull(false);//是否透明 倒是再设置
		ctemp.setIsFull(true);
		while(i < num )
		{
			temp = (uint16_t) str[i];
			//修改位置
			ctemp.setCharXY(column,line);
			//打印
			ctemp.displayChar(temp);
			column += font.Width;
			i++;
		}
	}
}
//在区域中从头打印
void controlWin::displayStrNormal(sFONT font,uint32_t textColor,uint32_t backColor,char* str)
{
	if(str != NULL){
		uint16_t temp;
		uint8_t i = 0;
		uint16_t line = getAbsoluteY() ;
		uint16_t column = getAbsoluteX() ;
		GUIChar ctemp(column,line,&font,textColor,backColor,getInvalidList());
		while(str[i] != '\0' )
		{
			temp = (uint16_t) str[i];
			if((getWinWidth() - (column - getAbsoluteX())) < font.Width )
			{
				if((getWinHigh()+getAbsoluteY()-line-font.Height) >= font.Height)
				{
					line += font.Height;
					column = getAbsoluteX();
				}
				else{
				return ;
				}
			}
			//修改位置
			ctemp.setCharXY(column,line);
			//打印
			ctemp.displayChar(temp);
			column += font.Width;
			i++;
		}
	}
}




