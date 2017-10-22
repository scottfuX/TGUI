#include "TGUIConfig/createWin_conf.h"

//全局变量 --- 指出当前的窗口
uint8_t currentWin = 251;

//最多app数量
xTaskHandle app[APP_MAX_NUM] ;
xTaskHandle pxCTask;

deskWin* desktop;
mainWin* mw0;
mainWin* mw1;

static void desk(void *pvParameters);
static void win0(void *pvParameters);
static void win1(void *pvParameters);
void GUI_Run()
{
	if(xTaskCreate( desk, "desktop", configMINIMAL_STACK_SIZE, NULL, 2, NULL )!=pdTRUE)
	{return;}
	if(xTaskCreate( win0, "win0", configMINIMAL_STACK_SIZE, NULL, 1, &pxCTask )==pdTRUE)
	{
		app[0] = pxCTask;
	}
	if(xTaskCreate( win1, "win1", configMINIMAL_STACK_SIZE, NULL, 1, &pxCTask )==pdTRUE)
	{
		app[1] = pxCTask;
	}
	
	vTaskStartScheduler();		// 启动调度器，任务开始执行	
}

void createDesktop()
{
	desktop = new deskWin();
	mw0 = new mainWin(/*这里可以添加相应的执行函数*/);
	mw1 = new mainWin(/*这里可以添加相应的执行函数*/);
	desktop->addAPP(mw0,0);
	desktop->addAPP(mw1,1);

	desktop->execDesk();
	delete desktop;
	vTaskDelete(NULL);//删除自己
}
static void desk(void *pvParameters)
{
	createDesktop();
	while(1){};
}


void createWin0()
{
	mw0->setWinID(0);	
	//循环win
	mw0->execWin();
	
	delete mw0;
	vTaskDelete(NULL);//删除自己
}

static void win0(void *pvParameters)
{
	createWin0();
	while(1){};
}

void createWin1()
{
	mw1->setWinID(1);	
	//循环win
	mw1->execWin();
	
	delete mw1;
	vTaskDelete(NULL);//删除自己
}

static void win1(void *pvParameters)
{
	createWin1();
	while(1){};
}


