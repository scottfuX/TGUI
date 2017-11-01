#include "winClass.hpp"
rootWin::rootWin(
	uint16_t winXpos,
	uint16_t winYpos,
	uint16_t winWidth,
	uint16_t winHigh,
	char* name,
	uint8_t wsStyle,
	rootWin* parent,
	xQueueHandle queue
)
{
	this->winXpos = winXpos;
	this->winYpos = winYpos;
	this->winWidth = winWidth;
	this->winHigh = winHigh;
	this->name = name;
	this->wsStyle = wsStyle;
	this->parent = parent;
	this->queue = queue;
	this->brother = NULL;
	this->child = NULL;
};

rootWin::~rootWin()
{
	
};

void rootWin::setWinProc(void (*winProc)(rootWin*, MsgType, uint32_t, uint32_t))
{
	this->winProc = winProc;
}

//是否在区域内 传进来的是减去父边框的 相对位移
bool rootWin::isInArea(uint16_t wXpos,uint16_t wYpos)
{
		if(wXpos >= getWinXpos() && wXpos <=(getWinXpos()+ getWinWidth()) && \
		wYpos >= getWinYpos() && wYpos <=(getWinYpos()+ getWinHigh()))
	{
		return true;
	}
	return false;
}

//每个注册时都必须设置setAbsoluteXY
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

void rootWin::preTraversePaint(rootWin* rw)
{//先序重绘所有
	if(rw)
	{
		rw->paintWin();
		preTraversePaint(rw->getChild());
		preTraversePaint(rw->getBrother());
	}
}


//注销 这个节点 以及下面的所有节点 配合析构函数使用
void rootWin::destroyWin()
{
	if(this->getParent() != NULL) //第一个一定是没有兄弟节点的
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
	this->destroyCAndB();
}

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
	delete this;
}

//创建窗口 -- 即加入树中
void rootWin::createWin()
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


//发送消息到队尾
retStatus rootWin::sendMSGtoBack(message* msg,xQueueHandle que)
{	
		if(xQueueSendToBack(que,msg,0)!= pdPASS)//等待时间为0
	{
			return GUI_QFULL;
	}
	return GUI_OK;
}

//发送消息到队头
retStatus rootWin::sendMSGtoFront(message* msg,xQueueHandle que)
{	
		if(xQueueSendToFront(que,msg,0)!= pdPASS)//等待时间为0
	{
			return GUI_QFULL;
	}
	return GUI_OK;
}
