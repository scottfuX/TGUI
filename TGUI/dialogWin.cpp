#include "winClass.hpp"
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
	
}
dialogWin::~dialogWin()
{

}


void dialogWin::dialogInit()
{
			setRwNum(2);
			comboBoxInit();
			getRwList()[0]	= new buttonWin(getWinWidth()/7,getWinHigh()/4,2*getWinWidth()/7,getWinHigh()/2,"ok",this->getBackWin(),getQueue());
			((controlWin* )getRwList()[0])->setTextColor(BLACK);
			((controlWin* )getRwList()[0])->setBackColor(GREY2);
			getRwList()[1] = new buttonWin(4*getWinWidth()/7,getWinHigh()/4,2*getWinWidth()/7,getWinHigh()/2,"cancel",this->getBackWin(),getQueue());
			((controlWin* )getRwList()[1])->setTextColor(BLACK);
			((controlWin* )getRwList()[1])->setBackColor(GREY2);
			getRwList()[0]->setWinProc(buttonWeakProc);
			getRwList()[1]->setWinProc(buttonWeakProc);
			getRwList()[0]->registerWin();
			getRwList()[1]->registerWin();
}


static void buttonWeakProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("buttonWeakProc 0\n");
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
				printf(" mainWin will be closed!\n");
				rootWin* t = rw->getParent()->getParent()->getParent();
				rw->getParent()->getParent()->unregisterWin();
				t->paintAll();
				//rw->getParent()->getParent()->destroyWin();
			}
		}break;
		default:	//处理不了就给父类
		if(rw->getParent() != NULL)
		{
			message* msg = new message();
			msg->type = mt;
			msg->data1 = d1;
			msg->data2 = d2;
			msg->destWin = rw->getParent();
			msg->fromWin = fw; //
			rw->sendMSGtoBack(msg,rw->getQueue());
		}break;
	}
}

