#include "winClass.h"

mainWin::mainWin():rootWin()
{
	winStyle = WS_DEFAULT;
	//创建列表
	list = new CircularList<controlWin>();
	//创建消息队列
	queue = xQueueCreate( MSG_QUENUM, sizeof( Message));
}
	
mainWin::mainWin(uint8* winTitle,uint16 winStyle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh)\
:rootWin(winTitle,winXpos,winYpos,winWidth,winHigh)
{
	this->winStyle = winStyle;
	//创建列表
	list = new CircularList<controlWin>();
	//创建消息队列
	queue = xQueueCreate( MSG_QUENUM, sizeof( Message));
}

mainWin::~mainWin()
{
	//撤销列表
	list->~CircularList();
	//撤销消息列表 1
	//删除对象 2
	//删除进程 删除自己 3
	vTaskDelete(NULL);
}

bool mainWin::isInArea(uint16 Xpos,uint16 Ypos)
{
	if(Xpos >= getWinXpos() && Xpos <=(getWinXpos()+ getWinWidth()) && \
		Ypos >= getWinYpos() && Ypos <=(getWinYpos()+ getWinHigh()))
	{
		return true;
	}
	return false;
}


retStatus mainWin::findExecControl(uint16 Xpos,uint16 Ypos)
{
	uint8 i= 0;
	while(i < list->getLength())
	{
		controlWin* cwTemp = list->Next();
		if(cwTemp->isInArea(Xpos,Ypos))
		{
				return cwTemp->execControl();
		}
		i++;
	}
	return GUI_NOFIND;
}

retStatus mainWin::addControl(controlWin* cw)
{
	if(!list->Insert(cw))
	{return GUI_ERROR;}
	return GUI_OK;
}

retStatus mainWin::delControl(controlWin* cw)
{
	if(!list->Remove(cw))
	{return GUI_ERROR;}
	//同时清空内存
	cw->~controlWin();
	return GUI_OK;
}

retStatus mainWin::getMessage(Message* buffer)
{
	portBASE_TYPE xStatus = xQueueReceive(queue,buffer,0);
	if(xStatus == pdPASS)
	{return GUI_OK;}
	return GUI_ERROR;
}

void mainWin::layoutWin()
{
	LCD_SetTextColor(backColor);
	LCD_DrawFullRect(winXpos,winYpos,winWidth,winHigh);
	LCD_SetTextColor(statBarColor);
	LCD_DrawFullRect(winXpos,winYpos,winWidth,winHigh/15);
}

void mainWin::closeWin()
{
	//即刷新桌面 currentWin = desktop
	
	//后台运行Win
	
}

//移动窗口
void mainWin::moveWin(uint16 x,uint16 y,uint16 w,uint16 h)
{
	//设置点和长宽
	
	//重绘
	repaintWin();
}
void mainWin::changeFont()
{
	//改变字体
	
	//重绘
	repaintWin();
}
void mainWin::erasureWin()
{
	//清空数据,其他都在
}
void mainWin::repaintWin()
{
	//重新绘画，按照现在的数据全部重画一遍
}


void mainWin::execWin()
{
	Message buffer[1];
	while(1)
	{
		getMessage(buffer);
		switch(*buffer)
			{
				case MSG_CLOSE:  closeWin(); break;	
				case MSG_DESTROY: mainWin::~mainWin();break;		
				case MSG_WINMOV: /*moveWin()仍有困难 之后处理*/ break;			
				case MSG_FONTCHANGE: changeFont();break;	
				case MSG_ERASURE: erasureWin();break;	
				case MSG_REPAINT: repaintWin();break;	
			}
			
		
		if(findExecControl(Xpos,Ypos)!=GUI_OK)
		{
			//出现问题予以警告
		}
		
	}
}


