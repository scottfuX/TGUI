#include "winClass.h"

button::button()
{
	//其中的 x,y都是相对位置
	uint8 defaultTitle[]= "default Button";//内存回收的问题
	setWinTitle(defaultTitle);
	setWinXpos(0);
	setWinYpos(0);
	setWinWidth(GUI_WIDTH/15);
	setWinHigh(GUI_HIGH/15);
}
button:: button(uint8* winTitle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh)\
:controlWin(winTitle,winXpos,winYpos,winWidth,winHigh)
{}
button::~button()
{
	printf("button exit");
}

bool button::isInArea(uint16 bXpos,uint16 bYpos)
{
	if(bXpos >= getWinXpos() && bXpos <=(getWinXpos()+ getWinWidth()) && \
		bYpos >= getWinYpos() && bYpos <=(getWinYpos()+ getWinHigh()))
	{
		return true;
	}
	return false;
}

retStatus button::sendMessage(Message msg,xQueueHandle* que)
{
	if(xQueueSendToBack(*que,&msg,0)!= pdPASS)//等待时间为0
	{
			return GUI_QFULL;
	}
	return GUI_OK;
}

void button::layoutControl(mainWin* mw)
{
		LCD_SetTextColor(getBackColor());
		LCD_DrawFullRect(getWinXpos()+mw->getWinXpos(),getWinYpos()+mw->getWinYpos(),getWinWidth(),getWinHigh());
}
void button::triggerControl(mainWin* mw)
{
	//被触发 白色覆盖按钮 表示被按下
	LCD_SetTextColor(WHITE);
	LCD_DrawFullRect(getWinXpos()+mw->getWinXpos(),getWinYpos()+mw->getWinYpos(),getWinWidth(),getWinHigh());
	while(TouchUp != 1);
	TouchUp = 0;
}
void button::releaseControl(mainWin* mw)
{
	layoutControl(mw);
}

retStatus button::execControl(mainWin* mw)
{
		retStatus stat;
		//默认选中即被触发 按钮出现反应
		triggerControl(mw);
		
		//发送message 或者打开dialog box 或打开新窗口//测试发送关闭信息
		Message* msg = new Message();
		msg->type = MSG_CLOSE;
		msg->data = 0;
		//发送队列会拷贝数据过去 
		stat = sendMessage(*msg,&(mw->queue));	
		if(stat != GUI_OK)
		{return stat;}
		
		delete msg;//删除信息体
		return GUI_OK;
}
