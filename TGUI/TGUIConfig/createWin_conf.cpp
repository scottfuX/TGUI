#include "TGUIConfig/createWin_conf.h"

//全局变量 --- 指出当前的窗口
rootWin* currentWin;

void createDesktop()
{
	//创建窗口对象
	mainWin* mwt = new mainWin();
	mwt->setWinStyle(WS_DESKTOP) ;
	mwt->layoutWin();
	
	//APP
	uint8 tital[] = "new window";
	controlWin* bt1 = new button(tital,0,mwt->getWinHigh()/5,mwt->getWinHigh()/5,mwt->getWinHigh()/5);
	bt1->setBackColor(BLACK);
	if(mwt->addControl(bt1)!=GUI_OK)
	{printf("bt1 error!");}
	//重绘
	mwt->layoutWin();
	
	//循环win
	mwt->execWin();
	
	delete mwt;
	vTaskDelete(NULL);//删除自己	
}

void createWin1()
{
	//创建窗口对象
	mainWin* mwt = new mainWin();
	
	//根据风格 添加控件
	if(mwt->getWinStyle() == WS_DEFAULT)
	{
		//设定默认的控件
		uint8 tital1[] = "b1";
		uint8 tital2[] = "b2";
		controlWin* bt1 = new button(tital1,0,0,mwt->getWinHigh()/15,mwt->getWinHigh()/15);
		controlWin* bt2 = new button(tital2,(mwt->getWinWidth()-(mwt->getWinHigh()/15)),0,mwt->getWinHigh()/15,mwt->getWinHigh()/15);
		bt1->setBackColor(DESTROYCOLOR);
		bt2->setBackColor(CLOSECOLOR);
		//添加到控件列表
		if(mwt->addControl(bt1)!=GUI_OK)
		{printf("bt1 error!");}
		if(mwt->addControl(bt2)!=GUI_OK)
		{printf("bt2 error!");}
	}
	//重绘
	mwt->layoutWin();
	
	//循环win
	mwt->execWin();
	
	delete mwt;
	vTaskDelete(NULL);//删除自己
}

