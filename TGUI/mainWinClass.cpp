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
	//撤销列表 并 删除了内部对象
	list->~CircularList();
	//撤销消息列表 1
	delete &queue;
	printf("mainWin exit");
}

bool mainWin::isInArea(uint16 wXpos,uint16 wYpos)
{
	if(wXpos >= getWinXpos() && wXpos <=(getWinXpos()+ getWinWidth()) && \
		wYpos >= getWinYpos() && wYpos <=(getWinYpos()+ getWinHigh()))
	{
		return true;
	}
	return false;
}

//寻找并执行
retStatus mainWin::findExecControl(uint16 wXpos,uint16 wYpos)
{
	uint8 cnum = (uint8)list->getLength();
	controlWin* cwTemp = NULL ;
	while(cnum > 0)
	{
		cnum--;
		cwTemp = list->Next();
		printf("\nfinding  ");	
		bool bl = cwTemp->isInArea(wXpos,wYpos);
		if(bl)
		{
			printf("\nexist");
				//重画选择框（先不实现，默认选中既是点击）
				//如果被点击执行 顺带发送一个类（默认本类）
			if(cwTemp->execControl(this) == GUI_OK)
			{	//把点设为无效
				GUISetPoint(65535,65535);
				//释放按键
				cwTemp->releaseControl(this);
				return GUI_OK;
			}	
			
		}
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
	
	return GUI_OK;
}

retStatus mainWin::getMessage(Message* buffer)
{
	portBASE_TYPE xStatus = xQueueReceive(queue,buffer,0);
	if(xStatus == pdPASS)
	{return GUI_OK;}
	return GUI_QEMPTY;
}

void mainWin::layoutWin()
{
	uint8 cnum = (uint8)list->getLength();
	controlWin* ctemp = NULL;
	
	LCD_SetTextColor(getBackColor());
	LCD_DrawFullRect(getWinXpos(),getWinYpos(),getWinWidth(),getWinHigh());
	LCD_SetTextColor(getStatBarColor());
	LCD_DrawFullRect(getWinXpos(),getWinYpos(),getWinWidth(),getWinHigh()/15);
	
	if(winStyle == WS_DESKTOP)
	{
			uint8_t spr[]="This is Desktop!";
			LCD_SetFont(&Font16x24);
			LCD_SetColors(BLACK,getStatBarColor());
			LCD_DisplayStringLine(LCD_LINE_0,spr );
	}
	
	while(cnum > 0)//循环遍历控件列表并布局
	{
		cnum--;
		ctemp = list->Next();
		ctemp->layoutControl(this);
	}
	printf("layout ");
}

void mainWin::closeWin()
{
	//即刷新桌面 
	//currentWin = Desktop;
	
	//调用Desktop 重绘代码。sendMssage(desktop) //怎么解决desktop queue的句柄
	
	//后台运行Win
	printf("Win CLOSE!!! ");
	
}


void mainWin::moveWin(uint32 data)//移动窗口
{
	//从data中分离获得数据
	
	//设置点和长宽
	
	//重绘
	repaintWin();
}

void mainWin::changeFont(uint32 data)
{
	//从data中分离获得数据
	
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
	layoutWin();
}


void mainWin::execWin()
{
	Message buffer[1];
	uint16 wXpos;
	uint16 wYpos;
	while(1)
	{
		//获取点 判断是否在窗口内
		GUIGetPoint(&wXpos,&wYpos);
		if(getMessage(buffer)==GUI_OK) //获得消息
		{
			switch(buffer[0].type)
			{
				case MSG_EMPTY: printf("\n empty! "); break;	
				case MSG_CLOSE:  closeWin(); break;	
				case MSG_DESTROY: return;		//强制退出就返回 让上一层回收内存
				case MSG_WINMOV: moveWin(buffer[1].data);break;			
				case MSG_FONTCHANGE: changeFont(buffer[1].data);break;	
				case MSG_ERASURE: erasureWin();break;	
				case MSG_REPAINT: repaintWin();break;	
			}
		}
		if(isInArea(wXpos,wYpos))
		{
			printf("%d,%d",wXpos,wYpos);
			findExecControl(wXpos,wYpos); //列表中寻找控件并执行
		}
	}
}


