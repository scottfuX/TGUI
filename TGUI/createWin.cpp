#include "createWin.hpp"

static void win0(void *pvParameters);
void GUI_Run()
{
	xTaskCreate( win0, "win0", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();		// 启动调度器，任务开始执行	
}

static void win0(void *pvParameters)
{
	xQueueHandle queue =  xQueueCreate( MSG_QUENUM, sizeof( message));
	char t1[] = "as";
	rootWin* mw = new mainWin(0,0,GUI_WIDTH,GUI_HIGH,t1,1,NULL,queue);
	rootWin* sf1 = new staticFrameWin(0,0,GUI_WIDTH,GUI_HIGH,t1,1,mw,queue,GREY);
	rootWin* sf2 = new staticFrameWin(0,0,GUI_WIDTH,GUI_HIGH/15,t1,1,mw,queue,BLACK);
	rootWin* sf3 = new staticFrameWin(0,GUI_HIGH/15+2,GUI_WIDTH,GUI_HIGH-GUI_HIGH/15-2,t1,1,NULL,queue,BLUE);
	
	mw->registerWin();
	sf1->registerWin();
	sf2->registerWin();
	
	mw->preTraversePaint(mw);
	Delay(0xffffff);
	mw->unregisterWin();
	
	sf3->registerWin();
	//mw->preTraversePaint(mw);
	//sf3->preTraversePaint(sf3);
	sf3->paintWin();
	message* buffer[1];
	while(1)
	{
		portBASE_TYPE xStatus = xQueueReceive(queue,buffer,0);
	}


}

