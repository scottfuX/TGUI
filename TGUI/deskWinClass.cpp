#include "winClass.h"

deskWin::deskWin():mainWin()
{
	setWinStyle(WS_DESKTOP);
	setWinXpos(0);
	setWinYpos(0);
	setWinWidth(GUI_WIDTH);
	setWinHigh(GUI_HIGH);
	setWinID(251);
	winList = new CircularList<mainWin>();
}
deskWin::~deskWin()
{
	delete winList;
	delete list;
	delete &queue;
}

retStatus deskWin::addAPP(mainWin* mw,uint8_t num)
{
	uint16_t x,y;
	uint8_t i;
	//暂时用来设置ID
	mw->setWinID(num);
	Message* msg = new Message();
	msg->type = MSG_APP;
	msg->data = (uint32_t)(mw->getWinID());
	//新建button 找到APP相应的位置
	//printf("APP_LINE_NUM = %d\n",APP_LINE_NUM);
	for(i=0;(i*APP_LINE_NUM) < APP_MAX_NUM;i++)
	{
		if((num-(APP_LINE_NUM*(i+1))) < 0)
		{
			x = (num-(APP_LINE_NUM*i))*APP_HIGH+APP_ETR_HIGH;
			y =  STAT_BAR+APP_ETR_HIGH+APP_HIGH*i;
			break ;
		}
	}
	if((i*APP_LINE_NUM)>=APP_MAX_NUM)
	{
		printf("out app max");
		return GUI_APPOUT;
	}
	printf("x = %d\n",x);
	printf("y = %d\n",y);
	controlWin* app = new button(mw->getWinTitle(),x,y,APP_INT_HIGH,APP_INT_HIGH,msg);
	app->setBackColor(RED);//默认没有图标的app为红色
	//加入ControlList
	this->addControl(app);
	//加入WinList
	addWin(mw);//
	return GUI_OK;
}

retStatus deskWin::findExecControl(uint16_t wXpos,uint16_t wYpos)
{
	uint8_t cnum = (uint8_t)list->getLength();
	controlWin* cwTemp = NULL ;
	while(cnum > 0)
	{
		cnum--;
		cwTemp = list->Next();
		printf("\n desk app control finding  ");	
		bool bl = cwTemp->isInArea(wXpos,wYpos);
		if(bl)
		{
			if(cwTemp->execControl(this) == GUI_OK)
			{	
				printf("ok");
				GUISetPoint(65535,65535);
				cwTemp->releaseControl(this);
				return GUI_OK;
			}
		}else{
			GUISetPoint(65535,65535);
		}
	}
	return GUI_NOFIND;
}

retStatus deskWin::getMessage(Message* buffer)
{
	portBASE_TYPE xStatus = xQueueReceive(queue,buffer,0);
	if(xStatus == pdPASS)
	{return GUI_OK;}
	return GUI_QEMPTY;

}

retStatus deskWin::addControl(controlWin* cw)
{
	if(!list->Insert(cw))
	{return GUI_ERROR;}
	return GUI_OK;
}
retStatus deskWin::delControl(controlWin* cw)
{
	if(!list->Remove(cw))
	{return GUI_ERROR;}
	return GUI_OK;
}
	

retStatus deskWin::findWin(uint8_t winID)
{
	uint8_t cnum = (uint8_t)winList->getLength();
	mainWin* mwTemp = NULL ;
	while(cnum > 0)
	{
		cnum--;
		mwTemp = winList->Next();
		printf("\n desk app win finding  ");	
		if(mwTemp->getWinID() == winID)
		{
			//重绘
			mwTemp->layoutWin();
			//设置当前窗口
			currentWin = mwTemp->getWinID();
			//提升优先级
			vTaskPrioritySet(app[winID], RUN_TASK_PRIORITY); 
			return GUI_OK;
		}
	}
	return GUI_NOFIND;
}

//添加窗口
retStatus deskWin::addWin(mainWin* mw)
{
	if(!winList->Insert(mw))
	{return GUI_ERROR;}
	return GUI_OK;
}

//删除暂时不用
retStatus deskWin::delWin(mainWin* mw)
{
	if(!winList->Remove(mw))
	{return GUI_ERROR;}
	return GUI_OK;
}

void deskWin::layoutWin()
{
	//绘画基本界面
	LCD_SetTextColor(GREEN);
	LCD_DrawFullRect(0,0,GUI_WIDTH,GUI_HIGH);
	LCD_SetTextColor(STAT_COLOR);
	LCD_DrawFullRect(0,0,GUI_WIDTH,STAT_BAR);	
	
	uint8_t spr[]="This is Desktop!";
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,STAT_COLOR);
	LCD_DisplayStringLine(LCD_LINE_0,spr );
	
	uint8_t cnum = (uint8_t)list->getLength();
	controlWin* ctemp = NULL;
	while(cnum > 0)
	{
		cnum--;
		ctemp = list->Next();
		ctemp->layoutControl(this);
	}
}


//执行函数
void deskWin::execDesk()
{
	Message buffer[1];
	uint16_t wXpos;
	uint16_t wYpos;
	this->layoutWin();
	while(1)
	{
		GUIGetPoint(&wXpos,&wYpos);
		if(getMessage(buffer)==GUI_OK) 
		{
			if(buffer[0].type == MSG_APP)
			{
				if(findWin((uint8_t)buffer[0].data) != GUI_OK)
				{return;}
			}
		}
		if(wXpos < GUI_WIDTH &&  wYpos < GUI_HIGH){
			if(currentWin == this->getWinID())
			{
				findExecControl(wXpos,wYpos);
			}
		}
	}
}
