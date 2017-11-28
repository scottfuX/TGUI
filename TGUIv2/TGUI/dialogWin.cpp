#include "winClass.h"
static void buttonWeakProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);

dialogWin::dialogWin(
	uint16_t winXpos,
	uint16_t winYpos,
	uint16_t winWidth,
	uint16_t winHigh,
	char* name,
	rootWin* parent,
	xQueueHandle queue,
	uint8_t wsStyle
):mainWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue,wsStyle)
{
	setIsMutable(true);
}
dialogWin::~dialogWin()
{

}


void dialogWin::dialogInit()
{
//	setRwNum(2);
//	comboBoxInit();
//	getRwList()[0]= new buttonWin(getWinWidth()/7,getWinHigh()/4,2*getWinWidth()/7,getWinHigh()/2,"ok",this->getBackWin(),getQueue());	
//	((controlWin* )getRwList()[0])->setTextColor(BLACK);
//	((controlWin* )getRwList()[0])->setBackColor(GREY2);
//	getRwList()[1] = new buttonWin(4*getWinWidth()/7,getWinHigh()/4,2*getWinWidth()/7,getWinHigh()/2,"cancel",this->getBackWin(),getQueue());
//	((controlWin* )getRwList()[1])->setTextColor(BLACK);
//	((controlWin* )getRwList()[1])->setBackColor(GREY2);
//	getRwList()[0]->setWinProc(buttonWeakProc);
//	getRwList()[1]->setWinProc(buttonWeakProc);
//	getRwList()[0]->registerWin();
//	getRwList()[1]->registerWin();
	buttonWin* bt1= new buttonWin(getWinWidth()/7,getWinHigh()/4,2*getWinWidth()/7,getWinHigh()/2,"ok",this->getBackWin(),getQueue());
	bt1->setTextColor(BLACK);
	bt1->setBackColor(GREY2);
	buttonWin* bt2	= new buttonWin(4*getWinWidth()/7,getWinHigh()/4,2*getWinWidth()/7,getWinHigh()/2,"cancel",this->getBackWin(),getQueue());
	bt2->setTextColor(BLACK);
	bt2->setBackColor(GREY2);
	bt1->setWinProc(buttonWeakProc);
	bt2->setWinProc(buttonWeakProc);
	bt1->registerWin();
	bt2->registerWin();
}
void dialogWin::closeDialog()
{
	delCoverArea();
	unregisterWin();
}

void dialogWin::registerWin()
{
	if(!isRegisterWin())
	{
		addCoverArea();
		mainWin::registerWin();
	}
}


static void buttonWeakProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2)
{
	switch(mt)
	{
		case MSG_CLICK: 
		{
			if(rw->isInArea((uint16_t)d1,(uint16_t)d2))
			{
				((buttonWin*)rw)->pressButton();//显示被按下
			}else{
				((buttonWin*)rw)->releaseButton();//显示松开
			}
		}break;
		case MSG_RELEASECLICK: 
		{
			((buttonWin*)rw)->releaseButton();//显示松开
			if(rw->isInArea(d1,d2))
			{
				//这里应该发送信息并注销dialog 
				message* msg = new message();
				msg->type = MSG_DIALOG;
				msg->data1 = (uint32_t)rw->getWinName();
				msg->data2 = rw->getWinID();
				msg->destWin = rw->getParent();
				msg->fromWin = rw; //
				rw->sendMSGtoBack(msg,rw->getQueue());
				//
			}
		}break;
		default:break;
	}
}

