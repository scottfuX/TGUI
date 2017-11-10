#include "winClass.hpp"

static  void optionWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);

radioBtnWin::radioBtnWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue
):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	this->HorizorVert = true;
	this->optionNum = 0;
	optionList = NULL;
}


radioBtnWin::~radioBtnWin()
{

}


//传入名字值，数量，横竖排列
void radioBtnWin::radioBtnInit(char** list,uint8_t num,bool hv)
{
	nameList = list;
	optionNum = num;
	HorizorVert = hv;
	optionList = new optionWin*[optionNum];
	int i;
	if(HorizorVert)
	{
		for(i=0;i < optionNum;i++)
		{
			optionList[i] = new optionWin(i*getWinWidth()/optionNum,0,getWinWidth()/optionNum,getWinHigh(),\
				list[i],this,getQueue(),true);
			optionList[i]->registerWin();
			optionList[i]->setWinProc(optionWinProc);
		}
	}else{
		for(i=0;i < optionNum;i++)
		{
			optionList[i] = new optionWin(0,i*getWinHigh()/optionNum,getWinWidth(),getWinHigh()/optionNum,\
				list[i],this,getQueue(),true);
			optionList[i]->registerWin();
			optionList[i]->setWinProc(optionWinProc);
		}
	}
}

void radioBtnWin::optionSelect(optionWin* opw)
{
	if(opw->isSelect()) //if selected change stat
	{
		opw->clickOption();
	}else{
		int i;
		for(i=0;i<optionNum;i++)// all clear 
		{
			optionList[i]->setSelectStat(false);
			optionList[i]->paintWin();
		}
		opw->clickOption();//select
	}
}

void radioBtnWin::paintWin()
{
		
}

void radioBtnWin::registerWin()
{	  
		rootWin::registerWin();
}

void radioBtnWin::unregisterWin()
{
		rootWin::unregisterWin();
	
}

void radioBtnWin::destroyWin()
{
		delete nameList;
		delete optionList;
		rootWin::destroyWin();
}

//---------------------------------------
static  void optionWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	switch(mt)
	{
		case MSG_RELEASECLICK:
		{
			if(rw->isInArea(d1,d2))//若为空间内部松开-->执行应有的程序
			{
				((radioBtnWin*)(rw->getParent()))->optionSelect(((optionWin*)rw));
				message* msg = new message();
					msg->type = MSG_RADIOBTN;
					msg->data1 = (uint32_t)(rw->getWinName());
					msg->data2 = 0;
					msg->destWin = rw->getParent();
					msg->fromWin = fw; //
					rw->sendMSGtoBack(msg,rw->getQueue());
			}
		}break;
		default:break;
	}
}

