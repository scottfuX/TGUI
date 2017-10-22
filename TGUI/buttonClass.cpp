#include "winClass.h"

button::button(Message* controlMsg):controlWin(controlMsg)
{
	//其中的 x,y都是相对位置
	uint8_t defaultTitle[]= "default Button";//内存回收的问题
	setWinTitle(defaultTitle);
	setWinXpos(0);
	setWinYpos(0);
	setWinWidth(GUI_WIDTH/15);
	setWinHigh(GUI_HIGH/15);
}
button:: button(uint8_t* winTitle,uint16_t winXpos,uint16_t winYpos,uint16_t winWidth,uint16_t winHigh,Message* controlMsg)\
:controlWin(winTitle,winXpos,winYpos,winWidth,winHigh,controlMsg)
{
	
}
button::~button()
{
	printf("button exit");
}

bool button::isInArea(uint16_t bXpos,uint16_t bYpos)
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
	//如果由控件图标，就用图标
	/*if(icon){
	}else{
		LCD_SetTextColor(getBackColor());
		LCD_DrawFullRect(getWinXpos()+mw->getWinXpos(),getWinYpos()+mw->getWinYpos(),getWinWidth(),getWinHigh());
	}*/
	//先这么用
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
		Message* msg ;
		//默认选中即被触发 按钮出现反应
		triggerControl(mw);
	
		if(getControlMsg()->type == MSG_CLOSE||getControlMsg()->type == MSG_DESTROY)
		{//若是关闭或注销，直接发送即可 由窗口处理
			msg = this->getControlMsg();
		}else if(getControlMsg()->type == MSG_APP)
		{
			msg = this->getControlMsg();
		}
		//发送队列会拷贝数据过去 
		stat = sendMessage(*msg,mw->getQueue());	
		if(stat != GUI_OK)
		{return stat;}
		if(getControlMsg()->type == MSG_CLOSE||getControlMsg()->type == MSG_DESTROY)
		{
			delete msg;//如果是缩小，或者关闭的话 删除信息体 因为下一次还是会从新创建的
		}
		return GUI_OK;
}
