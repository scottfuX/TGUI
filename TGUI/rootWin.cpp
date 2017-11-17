#include "winClass.hpp"
rootWin::rootWin(
	uint16_t winXpos,
	uint16_t winYpos,
	uint16_t winWidth,
	uint16_t winHigh,
	char* name,
	rootWin* parent,
	xQueueHandle queue
)
{
	this->winXpos = winXpos;
	this->winYpos = winYpos;
	this->winWidth = winWidth;
	this->winHigh = winHigh;
	this->name = name;
	this->parent = parent;
	this->queue = queue;
	this->brother = NULL;
	this->child = NULL;
	//setID
	this->winID = ++win_id;
	this->WinProcSign = false;//默认没有窗口过程
	winSelectedStat = false;//默认未被选中
	isAddTree = false;//未加入树
	//根据相对位置 确定 绝对路径
	isMutable = false;
	coverHead = NULL;
	
	rootWin* rw  = this;
	this->absoluteX = winXpos;
	this->absoluteY = winYpos;
	if(rw->getParent() != NULL)
	{
		rw = rw->getParent();
		absoluteX += rw->getAbsoluteX();
		absoluteY += rw->getAbsoluteY();
	}
};

rootWin::~rootWin()
{
};

//设置窗口过程
void rootWin::setWinProc(void (*winProc)(rootWin*, rootWin*,MsgType, uint32_t, uint32_t))
{
	this->winProc = winProc;
	this->WinProcSign = true;
}

//是否在区域内 绝对地址
bool rootWin::isInArea(uint16_t wXpos,uint16_t wYpos)
{
	if(wXpos >= getAbsoluteX() && wXpos <=(getAbsoluteX()+ getWinWidth()) && \
		wYpos >= getAbsoluteY() && wYpos <=(getAbsoluteY()+ getWinHigh()))
	{
		return true;
	}
	return false;
}

//每次修改相对位置时都必须重新设置setAbsoluteXY
void rootWin::setAbsoluteXY()
{
	rootWin* rw  = this;
	this->absoluteX = winXpos;
	this->absoluteY = winYpos;
	if(rw->getParent() != NULL)
	{
		rw = rw->getParent();
		absoluteX += rw->getAbsoluteX();
		absoluteY += rw->getAbsoluteY();
	}
}

//查找 这个点下 x,y 的最好的位置窗口,但是先不考虑win相互叠加 
//互相叠加的话就 改变树的兄弟链表的排列顺序
rootWin* rootWin::locateWin(uint16_t x,uint16_t y)
{
	rootWin* rw = this;
	if(rw->isInArea(x,y))//是否在区域内
	{
		if(rw->getChild() != NULL)//若孩子不为空 -- 则进入循环
		{
			rw = rw->getChild();
			while(1)
			{
				if(rw->isInArea(x,y))
				{
					if(rw->getChild() != NULL)
					{
						rw = rw->getChild();
					}
					else
					{
						return rw;
					}
				}
				else if(rw->getBrother() != NULL)
				{
					rw = rw->getBrother();
				}
				else
				{
					rw = rw->getParent();
					return rw;
				}
			}
		}
		else
		{
			return rw;
		}
	}
	return NULL;
}


//先序重绘所有自己和子窗口
void rootWin::paintAll()
{
	paintWin();
	preTraversePaint(this->child);
	if(getCoverHead() != NULL)
	{
		printf("come in %d\n",winHigh);
		winListNode* temp = getCoverHead();
		while(temp != NULL)
		{
			printf("paint next\n");
			temp->win->paintAll();
			if(temp!=NULL)
				temp = temp->next;
			printf("paint end...\n");
		}
	}
}


//注册 
void rootWin::registerWin()
{
	if(!isAddTree)// no added tree
	{
		if(isMutable)
		{
			markCovered();
		}
		addWintoTree();//added
		isAddTree = true;
	}
}

//注销
void rootWin::unregisterWin()
{
	if(isAddTree)// added tree
	{
		if(isMutable)
		{
			markDelete();
		}
		remWinfromTree(); //remove
		isAddTree = false; 
	}
}

//先移出树，然后再删除
void rootWin::destroyWin()
{
	unregisterWin();
	destroyCAndB();
}


//移到最前端 -- 保证该对象在兄弟对象中最先被访问 
void rootWin::movtoFront()
{
	if(this->parent->getChild() != this)
	{
		rootWin* temp = this->parent->getChild();
		while(temp->getBrother() != this)
		{
			temp = temp->getBrother();
		}
		if(temp->getBrother() == this)
		{
			temp->setBrother(this->brother);
			this->brother = this->parent->getChild();
			this->parent->setChild(this);	
		}
	}
}
//移到最后 -- 保证该对象在兄弟对象中最后被访问 
void rootWin::movtoBack()
{
	rootWin* temp = this->parent->getChild();
	if(this->parent->getChild() != this)
	{
		while(temp->getBrother() != this)
		{
			temp = temp->getBrother();
		}
		temp->setBrother(this->getBrother());
		while(temp->brother != NULL )
		{
			temp = temp->getBrother();
		}
		temp->setBrother(this);
		this->setBrother(NULL);
	}else{
		if(this->getBrother() != NULL)
		{
			temp = this->getBrother();
			this->parent->setChild(temp);
			while(temp->getBrother() != NULL)
			{
				temp = temp->getBrother();
			}
			temp->setBrother(this);
			this->setBrother(NULL);
		}
		
	}
	
}

void rootWin::changSelectedStat()
{
	if(winSelectedStat)
	{winSelectedStat = false;}
	else
	{winSelectedStat = true;}
}
//发送消息到队尾
retStatus rootWin::sendMSGtoBack(message* msg,xQueueHandle que)
{	
	if(xQueueSendToBack(que,msg,QUE_WAIT_TIME)!= pdPASS)//等待时间为0
	{
			return GUI_QFULL;
	}
	delete msg;
	return GUI_OK;
}

//发送消息到队头
retStatus rootWin::sendMSGtoFront(message* msg,xQueueHandle que)
{	
	if(xQueueSendToFront(que,msg,QUE_WAIT_TIME)!= pdPASS)//等待时间为0
	{
			return GUI_QFULL;
	}
	delete msg;
	return GUI_OK;
}


void rootWin::markCovered()
{
	uint16_t x,y;
	int i,j;
	rootWin* rw;
	for(j=0;j<4;j++)	//采样
	{
		if(j == 0)
		{
			y = getAbsoluteY();//上边框
			for(i=0;i<winWidth/SAMPLING_POINT;i++)
			{
				x = getAbsoluteX()+i*SAMPLING_POINT;
				travMark(rw,x,y); //遍历标记 -- 只标记兄弟
			}
		}else if(j == 1){
			y = getAbsoluteY()+getWinHigh();//下边框
			for(i=0;i<winWidth/SAMPLING_POINT;i++)
			{
				x = getAbsoluteX()+i*SAMPLING_POINT;
				travMark(rw,x,y);	//遍历标记 -- 只标记兄弟
			}
		}else if(j == 2){
			x =  getAbsoluteX();//左边框
			for(i=0;i<winHigh/SAMPLING_POINT;i++)
			{
				y = getAbsoluteY()+i*SAMPLING_POINT;
				travMark(rw,x,y);	//遍历标记 -- 只标记兄弟
			}
		}else{
			x =  getAbsoluteX()+getWinWidth();//右边框
			for(i=0;i<winHigh/SAMPLING_POINT;i++)
			{
				y = getAbsoluteY()+i*SAMPLING_POINT;
				travMark(rw,x,y);	//遍历标记 -- 只标记兄弟
			}
		}
	}
}

void rootWin::markDelete()
{
	uint16_t x,y;
	int i,j;
	rootWin* rw;
	for(j=0;j<4;j++)//采样
	{
		if(j == 0)
		{
			y = getAbsoluteY();						//上边框
			for(i=0;i<winWidth/SAMPLING_POINT;i++)
			{
				x = getAbsoluteX()+i*SAMPLING_POINT;
				travDelMark(rw,x,y);  //遍历 并删除标记
			}
		}else if(j == 1){
			y = getAbsoluteY()+getWinHigh();//下边框
			for(i=0;i<winWidth/SAMPLING_POINT;i++)
			{
				x = getAbsoluteX()+i*SAMPLING_POINT;
				travDelMark(rw,x,y);  //遍历 并删除标记
			}
		}else if(j == 2)
		{
			x =  getAbsoluteX();						//左边框
			for(i=0;i<winHigh/SAMPLING_POINT;i++)
			{
				y = getAbsoluteY()+i*SAMPLING_POINT;
				travDelMark(rw,x,y);   //遍历 并删除标记
			}
		}else{
			x =  getAbsoluteX()+getWinWidth();//右边框
			for(i=0;i<winHigh/SAMPLING_POINT;i++)
			{
				y = getAbsoluteY()+i*SAMPLING_POINT;
				travDelMark(rw,x,y);   //遍历 并删除标记
			}
		}
	}
}

//--------------------------private------------------------


void rootWin::preTraversePaint(rootWin* rw)
{//先序重绘
	if(rw)
	{
		//每次都要刷新一下绝对地址
		rw->setAbsoluteXY();
		rw->paintWin();
		preTraversePaint(rw->getChild());
		preTraversePaint(rw->getBrother());
	}
}

//删除 这个节点 以及下面的所有节点 配合析构函数使用
void rootWin::destroyCAndB()
{
	while(this->child != NULL)
	{
		this->child->destroyCAndB();
		this->child = NULL;
	}
	while(this->brother != NULL)
	{
		this->brother->destroyCAndB();
		this->brother = NULL;
	}
	this->parent = NULL;
	delete this;
	printf("\ndestroy\n");
}

//加入树中
void rootWin::addWintoTree()
{
	if(this->parent != NULL)
	{
		//设置完之后 把自己放到相应队列里
		if(this->parent->getChild() == NULL)
		{
			this->brother = NULL; //如果将这个改为this 就是循环链表 析构也需要改变
			this->parent->setChild(this);
		}
		else
		{//否则 把自己插入到链表里
			this->brother = this->parent->getChild()->getBrother();
			this->parent->getChild()->setBrother(this) ;
		}
	}
}

//从树中删除
void rootWin::remWinfromTree()
{
	//第一个一定是没有兄弟节点的
	//如果没有父亲节点 自己就是根节点
	if(this->getParent() != NULL) 
	{
		rootWin* c = this->parent->getChild();
		if(c != this)
		{
			while(c->getBrother()!= this)
			{
				c = c->getBrother();
			}
			if(c->getBrother() == this)
			{
					c->setBrother(this->brother);
					this->brother = NULL;
			}
		}
		else
		{
			this->parent->setChild(this->brother);
			this->brother = NULL;
		}
	}
}

//遍历 标记--只检查他的兄弟
void rootWin::travMark(rootWin* rw,uint16_t x,uint16_t y)
{
	rw = this->parent->getChild();
	winListNode* temp ;
	while(rw != NULL)
	{
		if(rw->isInArea(x,y)&&rw != this)
		{
			//标识
			if(rw->getCoverHead()==NULL)
			{
				temp = new winListNode();
				rw->setCoverHead(temp);
				rw->getCoverHead()->win = this;
				rw->getCoverHead()->next = NULL;
				rw = rw->getBrother();
				continue;
			}else{
				winListNode* t = rw->getCoverHead();
				if(t->win != this)
				{
					while(t->next != NULL && t->next->win != this)
					{
						t = t->next;
					}
					if(t->next == NULL)
					{
						temp = new winListNode();
						t->next = temp;
						temp->next = NULL;
						temp->win = this;
					}
				}
			}
		}
		rw = rw->getBrother();
	}
}

//遍历 并删除标记
void rootWin::travDelMark(rootWin* rw,uint16_t x,uint16_t y)
{
	rw = this->parent->getChild();
	while(rw != NULL)
	{
		if(rw->isInArea(x,y) && rw != this)//说明有标记过
		{//标识
			winListNode*temp = rw->getCoverHead();
			if(temp->win == this)//如果是第一个就是
			{
				rw->setCoverHead(temp->next);
				delete temp;//删除
				rw->paintAll();
				rw = rw->getBrother();
				continue;
			}
			if(temp!=NULL)
			{
				while(temp->next != NULL && temp->next->win != this )
				{
					temp = temp->next;
				}
				if(temp->next !=NULL)	//找到了
				{
					winListNode * t = temp->next;
					temp->next = t->next;
					delete t;
					rw->paintAll();
				}
			}
		}
		rw = rw->getBrother();
	}
}


