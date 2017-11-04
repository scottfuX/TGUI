#include "winClass.hpp"

listBarWin::listBarWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
):controlWin(winXpos,winYpos,winWidth,winHigh,name,wsStyle,parent,queue)
{
	itemNum = 0;
}

listBarWin::~listBarWin()
{

}




//绘画 就自己 不同的窗口实现不同
void listBarWin::paintWin()
{	
	LCD_SetColors(winColor,winColor);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	displayStrCenter(Font16x24,getTextColor(),getBackColor(),getWinName());
}

//按钮失焦
void listBarWin::defocusListBar()
{
	//绘画成纯灰色
	LCD_SetColors(GREY,GREY);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	displayStrCenter(Font16x24,getTextColor(),getBackColor(),getWinName());
}

//按钮按下
void listBarWin::pressListBar()
{
	LCD_SetColors(WHITE,WHITE);
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	displayStrCenter(Font16x24,getTextColor(),getBackColor(),getWinName());
	
	//
}

//原理是一个按钮 一按 会出现很多按钮，每个按钮就是一个item
//多个item 是兄弟 都是 listBar 的孩子 

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
		rootWin* temp = new buttonWin(getWinXpos(),getWinYpos(),getWinWidth(),getWinHigh(),getWinName(),WS_DEFAULT,this,getQueue());
		//并存入相应的列表里
		rwList[i] = temp;
	}
}




//按钮释放
void listBarWin::releaseListBar()
{
	//重绘
	paintWin();
}

static void mainWinproc(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	switch(mt)
	{
		case MSG_CLICK: 
		{
			((buttonWin*)rw)->pressButton();//显示被按下
		}break;
		case MSG_UNCLICK: 
		{
			//遍历列表 并注册 或者 注销
			int i,max=((listBarWin*)rw)->getItemNum();
			for(i=0;i<max;i++)
			{
				
			}
			//
			rw->paintAll();
		}break;
		default:break;
	}
}
//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
void listBarWin::registerWin()
{
	rootWin::registerWin();
	rootWin* mainbt = new buttonWin(getWinXpos(),getWinYpos(),getWinWidth(),getWinHigh(),getWinName(),WS_DEFAULT,this,getQueue());
	mainbt->registerWin();
	mainbt->setWinProc(mainWinproc);
	((controlWin*)mainbt)->setTextColor(BLACK);
	((controlWin*)mainbt)->setBackColor(CYAN);
	paintWin();
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
}
