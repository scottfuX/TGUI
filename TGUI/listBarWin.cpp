#include "winClass.h"
static void itemWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);

listBarWin::listBarWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue
			):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	this->itemHigh = winHigh; //保存当前的高 作为之后每一个item的高
	this->openStat = false;
	this->itemList = NULL;
	setIsMutable(true);
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
void listBarWin::itemInit(char**  itemList, uint8_t num)
{
	this->itemList = itemList;
	setRwNum(num);
	comboBoxInit();

	int i,max = getRwNum();
	for(i=0;i<max;i++)
	{
		//更具上一个进行 y ++；   ----getWinXpos ---还未改
		rootWin* temp = new buttonWin(0,(i+1)*getItemHigh(),getWinWidth(),getItemHigh(),itemList[i],this,getQueue());
		temp->setWinProc(itemWinProc);
		((controlWin*)temp)->setTextColor(getTextColor());
		((controlWin*)temp)->setBackColor(GREY1);
		//并存入相应的列表里
		getRwList()[i] = temp;
	}
}


//按钮失焦
void listBarWin::defocusListBar()	 	
{
	
}

//列表按下
void listBarWin::pressListBar() 	 	
{
	if(!isWinSelected())//之前未被选中 改为选中
	{
		changSelectedStat();
		GUIRectangle grect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getItemHigh(),WHITE,getInvalidList());
		grect.setIsFull(true);
		grect.draw();
		grect.setColor(getTextColor());
		grect.setIsFull(false);
		grect.draw();
		
		stringChar();
	}
}

//按钮释放
void listBarWin::releaseListBar()	 	
{
	if(isWinSelected())//若之前选中 改为未选中
	{
		paintAll();	
		changSelectedStat();
	}
}

void listBarWin::changeOpenList()
{
	if(getRwList() != NULL)
	{
		if(!isOpen())
		{ // 若未打开 -->  遍历列表 注册
			int i,max = getRwNum();
			for(i=0;i<max;i++)
			{
				getRwList()[i]->registerWin();
			}
			movtoFront(); //打开的话 就把这个列表推到最前 保证最新被访问
			setWinHigh(getItemHigh()*(max+1));
			if(getIsMutable())
			{
					addCoverArea();
			}
			changeOpenState();//改变打开状态
			paintAll();
		}else
		{// 若打开 -->  遍历列表 注销
			int i,max = getRwNum();
			for(i=0;i<max;i++)
			{
					getRwList()[i]->unregisterWin();
			}
			if(getIsMutable())
			{
					delCoverArea();
			}
			setWinHigh(getItemHigh());
			paintWin();
			changeOpenState();//改变打开状态
		}	
	}
}

void listBarWin::paintWin()
{
	GUIRectangle grect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getItemHigh(),getBackColor(),getInvalidList());
	grect.setIsFull(true);
	grect.draw();
	grect.setColor(getTextColor());
	grect.setIsFull(false);
	grect.draw();
	stringChar();
}

//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
void listBarWin::registerWin()
{
	rootWin::registerWin();
}

//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
void listBarWin::unregisterWin()
{
	rootWin::unregisterWin();
}

//摧毁控件
void listBarWin::destroyWin()
{
	delete itemList;
	comboBoxDestroy();
	rootWin::destroyWin();
}

void listBarWin::addInvalidArea(GUIArea * tarea)
{
	controlWin::addInvalidArea(tarea);
	//更新子覆盖链表
	GUIRectangle grect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getItemHigh(),getBackColor(),getInvalidList());
	grect.setIsFull(true);
	grect.drawInArea(tarea);
	grect.setColor(getTextColor());
	grect.setIsFull(false);
	grect.drawInArea(tarea);
	stringChar();
	if(getInvalidList()->getNum() == 1)
	{
		for(int i=0;i< getRwNum();i++)
		{
			((controlWin*)getRwList()[i])->setInvalidList(this->getInvalidList());
		}
	}
}
void listBarWin::paintInvalid(GUIArea * tarea)
{
	for(int i=0;i< getRwNum();i++)
	{
		((controlWin*)getRwList()[i])->paintInvalid(tarea);
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

//---------------------------------------
void listBarWin::stringChar()
{
	if(getWinName() != NULL)
	{
		uint16_t temp;
		uint8_t i = 0,num  = 0;
		sFONT f =getFont();
		while(getWinName()[num] != '\0' )
		{
			num++;
			if((getWinWidth()- getFont().Width*num) <= 0)
			{
				num--;
				break;
			}
		}
		uint16_t line = getAbsoluteY() + ((getItemHigh()- getFont().Height)/2);
		uint16_t column = getAbsoluteX() + ((getWinWidth()- getFont().Width*num)/2);
		GUIChar gchar(column,line,&f,getTextColor(),getTextColor(),getInvalidList());
		while(i < num )
		{
			temp = (uint16_t) getWinName()[i];
			gchar.setCharXY(column,line);
			gchar.setIsFull(false);
			gchar.displayChar(temp);
			column += getFont().Width;
			i++;
		}
	}

}
				

static void itemWinProc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
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
			if(rw->isInArea(d1,d2))//若为空间内部松开-->执行应有的程序
			{
				//按下  存储数据
				message* msg = new message();
				msg->type = MSG_ITEM;
				msg->data1 = (uint32_t)rw->getWinName();//存储为uint32_t 到时需要强行转换为char*
				msg->data2 =  0;
				msg->destWin = rw->getParent();
				msg->fromWin = rw;
				rw->sendMSGtoBack(msg,rw->getQueue());
			}
		}break;
		default:break;
	}
}




