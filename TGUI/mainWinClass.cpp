#include "winClass.h"

mainWin::mainWin():rootWin()
{
	//创建id
	setWinID(255);
	winStyle = WS_DEFAULT;
	//创建列表
	list = new CircularList<controlWin>();
	//创建消息队列
	queue = xQueueCreate( MSG_QUENUM, sizeof( Message));
}

//传入执行函数
mainWin::mainWin(void (*tempFunc)()):rootWin()
{
	//创建id
	setWinID(255);
	winStyle = WS_DEFAULT;
	this->userFunc = tempFunc;
	//创建列表
	list = new CircularList<controlWin>();
	//创建消息队列
	queue = xQueueCreate( MSG_QUENUM, sizeof( Message));
}
	
mainWin::mainWin(uint8_t* winTitle,uint16_t winStyle,uint16_t winXpos,uint16_t winYpos,uint16_t winWidth,uint16_t winHigh,void (*tempFunc)())\
:rootWin(winTitle,winXpos,winYpos,winWidth,winHigh)
{
	//创建id
	setWinID(255);
	this->winStyle = winStyle;
	this->userFunc = tempFunc;
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

bool mainWin::isInArea(uint16_t wXpos,uint16_t wYpos)
{
	if(wXpos >= getWinXpos() && wXpos <=(getWinXpos()+ getWinWidth()) && \
		wYpos >= getWinYpos() && wYpos <=(getWinYpos()+ getWinHigh()))
	{
		return true;
	}
	return false;
}

//寻找并执行
retStatus mainWin::findExecControl(uint16_t wXpos,uint16_t wYpos)
{
	uint8_t cnum = (uint8_t)list->getLength();
	controlWin* cwTemp = NULL ;
	while(cnum > 0)
	{
		cnum--;
		cwTemp = list->Next();	
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
			
		}else{
			GUISetPoint(65535,65535);//释放按键
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
	
	LCD_SetTextColor(getBackColor());
	LCD_DrawFullRect(getWinXpos(),getWinYpos(),getWinWidth(),getWinHigh());
	LCD_SetTextColor(getStatBarColor());
	LCD_DrawFullRect(getWinXpos(),getWinYpos(),getWinWidth(),STAT_BAR);
	
	//--------根据风格设置控件--------
	if((getWinStyle()&WS_DEFAULT) != 0 )
	{
		uint8_t tital1[] = "x";
		uint8_t tital2[] = "-";
		Message *m1 = new Message();
		Message *m2 = new Message();
		m1->type = MSG_DESTROY;
		m1->data = 0;
		m2->type = MSG_CLOSE;
		m1->data = 0;
		//controlWin* bt1 = new button(tital1,0,0,STAT_BAR*2,STAT_BAR,m1);
		//controlWin* bt2 = new button(tital2,STAT_BAR*2,0,STAT_BAR*2,STAT_BAR,m2);
		controlWin* bt1 = new button(tital1,3,3,STAT_BAR*2-6,STAT_BAR-6,m1);//根据自己的lcd改的  好看用
		controlWin* bt2 = new button(tital2,STAT_BAR*2,3,STAT_BAR*2-6,STAT_BAR-6,m2);
		bt1->setBackColor(DESTROYCOLOR);
		bt2->setBackColor(CLOSECOLOR);
		//添加到控件列表
		while(this->addControl(bt1)!=GUI_OK)
		{printf("bt1 error!");}
		while(this->addControl(bt2)!=GUI_OK)
		{printf("bt2 error!");}
	}
	
	//------循环遍历控件列表并布局-------
	uint8_t cnum = (uint8_t)list->getLength();
	controlWin* ctemp = NULL;
	while(cnum > 0)
	{
		cnum--;
		ctemp = list->Next();
		ctemp->layoutControl(this);
	}
}

void mainWin::closeWin()
{
	//即刷新桌面 
	currentWin = desktop->getWinID();
	
	//调用Desktop 重绘桌面
	desktop->layoutWin();
	
	//后台运行Win
	printf("Win CLOSE!!! ");
	
}
void mainWin::destroyWin()
{
	//即刷新桌面 
	currentWin = desktop->getWinID();
	desktop->layoutWin();
	vTaskPrioritySet(NULL,HUP_TASK_PRIORITY);
}



void mainWin::moveWin(uint32_t data)//移动窗口
{
	//从data中分离获得数据
	
	//设置点和长宽
	
	//重绘
	repaintWin();
}

void mainWin::changeFont(uint32_t data)
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
	uint16_t wXpos;
	uint16_t wYpos;
	layoutWin();
	while(1)
	{
		//获取点 判断是否在窗口内
		GUIGetPoint(&wXpos,&wYpos);
		if(getMessage(buffer)==GUI_OK) //获得消息
		{
			switch(buffer[0].type)
			{
				case MSG_EMPTY: printf("\n empty! "); break;	
				case MSG_CLOSE: closeWin(); break;	
				case MSG_DESTROY: destroyWin();break;//降低优先级 挂起自己
				case MSG_WINMOV: moveWin(buffer[0].data);break;			
				case MSG_FONTCHANGE: changeFont(buffer[0].data);break;	
				case MSG_ERASURE: erasureWin();break;	
				case MSG_REPAINT: repaintWin();break;	
				case MSG_APP:/*到时在转到desk机制里*/;break;
				case MSG_OTHER: (*userFunc)();break;//自定义数据--调用传入的处理函数
			}
		}
		if(isInArea(wXpos,wYpos)&&currentWin == (this->getWinID()))//且为本桌面
		{
			printf("%d,%d",wXpos,wYpos);
			findExecControl(wXpos,wYpos); //列表中寻找控件并执行
		}
	}
}


