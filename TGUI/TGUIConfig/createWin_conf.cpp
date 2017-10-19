#include "TGUIConfig/createWin_conf.h"

void createWin1(void *pvParameters)
{
	//创建窗口对象
	mainWin* mwt = new mainWin();
	
	//根据风格 添加控件
	if(mwt->getWinStyle() == WS_DEFAULT)
	{
		//设定默认的控件
		controlWin* bt1 = new button();
		controlWin* bt2 = new button();
		controlWin* bt3 = new button();
	
		//添加到控件列表
		mwt->addControl(bt1);
		mwt->addControl(bt2);
		mwt->addControl(bt3);
	}
	
	//循环win
	mwt->execWin();
}


