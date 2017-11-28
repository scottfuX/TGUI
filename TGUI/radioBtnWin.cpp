#include "winClass.h"

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

}


radioBtnWin::~radioBtnWin()
{

}


//传入名字值，数量，横竖排列
void radioBtnWin::radioBtnInit(char** list,uint8_t num,bool hv)
{
	nameList = list;
	setRwNum(num);
	comboBoxInit();
	HorizorVert = hv;
	int i,temp=0;
	
	if(HorizorVert)
	{
		for(i=0;i < getRwNum();i++)
		{//未优化
			getRwList()[i] = new optionWin(temp,0,getWinWidth()/getRwNum(),getWinHigh(),\
				list[i],this,getQueue(),true);
			getRwList()[i]->registerWin();
			getRwList()[i]->setWinProc(optionWinProc);
			temp += getWinWidth()/getRwNum();
		}
	}else{
		temp = getRwNum()*2+getRwNum()-1;//控件空出控件
		for(i=0;i < getRwNum();i++)
		{
			getRwList()[i] = new optionWin(0,3*i*getWinHigh()/temp,getWinWidth(),2*getWinHigh()/temp,\
				list[i],this,getQueue(),true);
			getRwList()[i]->registerWin();
			getRwList()[i]->setWinProc(optionWinProc);
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
		for(i=0;i<getRwNum();i++)// all clear 
		{
			((optionWin*) getRwList()[i])->setSelectStat(false);
		}
		opw->clickOption();//select
		paintAll();
	}
}

void radioBtnWin::addInvalidArea(GUIArea * tarea)
{
	controlWin::addInvalidArea(tarea);
	//更新子覆盖链表
	if(getInvalidList()->getNum() == 1)
	{
		for(int i=0;i < getRwNum();i++)
		{
			((controlWin*)getRwList()[i])->setInvalidList(getInvalidList());
		}
	}
}

void radioBtnWin::paintInvalid(GUIArea * tarea)
{
	for(int i=0;i< getRwNum();i++)
	{	
		((controlWin*)getRwList()[i])->paintInvalid(tarea);
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
		comboBoxDestroy();
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

