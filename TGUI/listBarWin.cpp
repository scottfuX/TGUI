#include "winClass.hpp"
static void mainWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);
static void itemWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);

listBarWin::listBarWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue,
			char**  itemList, 
			uint8_t num
):controlWin(winXpos,winYpos,winWidth,winHigh,name,wsStyle,parent,queue)
{
	this->itemHigh = winHigh; //保存当前的高 作为之后每一个item的高
	this->itemList = itemList;
	this->itemNum = num;
	this->openStat = false;
	this->setWinHigh ((num+1)*itemHigh);
}

listBarWin::~listBarWin()
{
	
}

//原理是一个按钮 一按 会出现很多按钮，每个按钮就是一个item
//多个item 是兄弟 都是 listBar 的孩子 
//改改 自己本身就是一个按钮

// |---------|>|
//       V
// |---------|V| 
// |item------1|
// |item------2|
// |item------3|
void listBarWin::initItem()
{
	rwList = new rootWin*[itemNum];
	int i,max = itemNum;
	for(i=0;i<max;i++)
	{
		//更具上一个进行 y ++；   ----getWinXpos ---还未改
		rootWin* temp = new buttonWin(0,(i+1)*getItemHigh(),getWinWidth(),getItemHigh(),itemList[i],WS_DEFAULT,this,getQueue());
		temp->setWinProc(itemWinProc);
		((controlWin*)temp)->setTextColor(getTextColor());
		((controlWin*)temp)->setBackColor(GREY2);
		//并存入相应的列表里
		rwList[i] = temp;
	}
}

//改变状态标志位
void listBarWin::changeOpenState()
{
	if(isOpen())
		{this->openStat = false;}
	else
		{this->openStat = true;}
}

//按钮释放
void listBarWin::releaseListBar()
{
	//重绘
	paintWin();
}


//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
void listBarWin::registerWin()
{
	rootWin::registerWin();
	rootWin* mainbt = new buttonWin(0,0,getWinWidth(),getItemHigh(),getWinName(),WS_DEFAULT,this,getQueue());
	mainbt->registerWin();
	mainbt->setWinProc(mainWinProc);
	((controlWin*)mainbt)->setTextColor(getTextColor());
	((controlWin*)mainbt)->setBackColor(getBackColor());
	initItem();
}



//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
void listBarWin::unregisterWin()
{
	rootWin::unregisterWin();
}

//摧毁控件
void listBarWin::destroyWin()
{
	rootWin::destroyWin();
	delete rwList;
}


//---------------------------------------
//主按钮的窗口过程
static void mainWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	switch(mt)
	{
		case MSG_CLICK: 
		{
			((buttonWin*)rw)->pressButton();//显示被按下
		}break;
		case MSG_UNCLICK: 
		{
			if(((listBarWin*)(rw->getParent()))->isOpen() == false)
			{ // 若未打开 -->  遍历列表 注册
				int i,max=((listBarWin*)(rw->getParent()))->getItemNum();
				for(i=0;i<max;i++)
				{
					((listBarWin*)(rw->getParent()))->getRwList()[i]->registerWin();
				}
				
				(rw->getParent())->paintAll();//重绘listBar
				((listBarWin*)(rw->getParent())) -> changeOpenState();//改变打开状态
			}
			else
			{// 若打开 -->  遍历列表 注销
				int i,max=((listBarWin*)(rw->getParent()))->getItemNum();
				for(i=0;i<max;i++)
				{
					((listBarWin*)(rw->getParent()))->getRwList()[i]->unregisterWin();
				}
				(rw->getParent()->getParent())->paintAll();//重绘listBar的父亲窗口 因为打开时把父亲的给覆盖了
				((listBarWin*)(rw->getParent())) -> changeOpenState();//改变打开状态
			}
		}break;
		default:
		if(rw->getParent() != NULL){
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

static void itemWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	switch(mt)
	{
		case MSG_CLICK: 
		{
			((buttonWin*)rw)->pressButton();//显示被按下
		}break;
		case MSG_UNCLICK: 
		{
			((buttonWin*)rw)->releaseButton();
			//按下  存储数据
			message* msg = new message();
				msg->type = MSG_ITEM;
				msg->data1 = (uint32_t)rw->getWinName();//存储为uint32_t 到时需要强行转换为char*
				msg->data2 =  0;
				msg->destWin = rw->getParent();
				msg->fromWin = rw;
			//测试
			char* x = (char*)(msg->data1);
			for(int i = 0;x[i]!='\0';i++)
			{
				printf("----%c------",x[i]);
			}
			printf("\n");
			rw->sendMSGtoBack(msg,rw->getQueue());
		}break;
		default:
		if(rw->getParent() != NULL){
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

