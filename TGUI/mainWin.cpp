#include "winClass.h"

static void buttonWeakProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);

mainWin::mainWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue,
			uint8_t wsStyle
):rootWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	this->wsStyle = wsStyle;
	styleInit();
}

mainWin::~mainWin()
{
	
}

void mainWin::styleInit()
{
	switch(wsStyle)
	{
		case WS_DEFAULT:
		{
			setRwNum(3);
			comboBoxInit();
			getRwList()[0]	= new staticFrameWin(0,0,getWinWidth(),STAT_BAR,getWinName(),this,getQueue());
			((controlWin*)getRwList()[0])->setTextColor(WHITE);
			((controlWin*)getRwList()[0])->setBackColor(BLACK);
			getRwList()[1] = new staticFrameWin(0,STAT_BAR,getWinWidth(),(getWinHigh()-STAT_BAR),NULL,this,getQueue());
			((controlWin* )getRwList()[1])->setBackColor(GREY);
			getRwList()[2]	= new buttonWin(0,0,SYS_BTN_W,STAT_BAR,"x",	getRwList()[0],getQueue());
			((controlWin* )getRwList()[2])->setTextColor(BLACK);
			((controlWin* )getRwList()[2])->setBackColor(RED);
			getRwList()[2]->setWinProc(buttonWeakProc);
			backWin = getRwList()[1];
			int i = 0;
			for(i=0;i < getRwNum();i++)
			{
					getRwList()[i]->registerWin();
			}
		}break;
		case WS_BORDER:
		{
			
		}break;
		case WS_VSCROLL:
		{
		
		}break;
		case WS_HSCROLL:
		{
		
		}break;
		default:break;
	}
}

rootWin* mainWin::getBackWin()
{
	return backWin;
}

//绘画 就自己 不同的窗口实现不同
void mainWin::paintWin()
{}

//激活控件--注册 中间会调用createWin（其他根据不同的窗口变化）
void mainWin::registerWin()
{
	rootWin::registerWin();
}

//注销控件  会调用destroy（窗口 其他会根据不同窗口变化）
void mainWin::unregisterWin()
{
	rootWin::unregisterWin();
}

void mainWin::destroyWin()
{
	comboBoxDestroy();
	rootWin::destroyWin();
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
				message* msg = new message();
				msg->type = MSG_CLOSE;
				msg->data1 = d1;
				msg->data2 = d2;
				msg->destWin = rw->getParent();
				msg->fromWin = rw;
				rw->sendMSGtoBack(msg,rw->getQueue());
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
