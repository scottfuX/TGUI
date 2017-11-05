#include "createWin.hpp"
static void win0(void *pvParameters);

void GUI_Run()
{
	xTaskCreate( win0, "win0", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();		// 启动调度器，任务开始执行	
}


//用孩子兄弟二叉树的第一个孩子作为当前界面的

xQueueHandle queue =  xQueueCreate( MSG_QUENUM, sizeof( message));
rootWin* tempWin;//定义现在按下（为松开）的控件  

static void ClickHandle(uint16_t x , uint16_t y ,uint32_t *data1,uint32_t *data2,rootWin* mw,uint8_t* stat);
static void winDefaultProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc0(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc1(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc2(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc3(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc4(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);


static void win0(void *pvParameters)
{
	//----------------这里开始配置窗口-------------------
	char t0[] = "IS TEST WIN !";
	char t1[] = "x";
	char t2[] = "-";
	char t3[] = "Lin Ying ";
	char t4[] = "listBar";
	char* item[] = {"ab","cd","ef"};
	rootWin* mw = new mainWin(0,0,GUI_WIDTH,GUI_HIGH,NULL,WS_DEFAULT,NULL,queue);
	rootWin* sf1 = new staticFrameWin(0,GUI_HIGH/15,GUI_WIDTH,GUI_HIGH-GUI_HIGH/15,NULL,WS_DEFAULT,mw,queue);
	rootWin* sf2 = new staticFrameWin(0,0,GUI_WIDTH,GUI_HIGH/15,t0,WS_DEFAULT,mw,queue);
	rootWin* bt1 = new buttonWin(2,2,GUI_WIDTH/15,GUI_HIGH/15-4,t1,WS_DEFAULT,sf2,queue);
	rootWin* bt2 = new buttonWin(4+GUI_WIDTH/15,2,GUI_WIDTH/15,GUI_HIGH/15-4,t2,WS_DEFAULT,sf2,queue);
	rootWin* bt3 = new buttonWin(50,100,GUI_WIDTH/5,100,t3,WS_DEFAULT,sf1,queue);	
	rootWin* lbw1 = new listBarWin(400,100,GUI_WIDTH/5,50,t4,WS_DEFAULT,sf1,queue,item,3);
	//------注册&打印-------
	mw->registerWin();
	mw->setWinProc(winWeakProc0);

	sf1->registerWin();
	sf1->setWinProc(winWeakProc1);
	((staticFrameWin*)sf1)->setTextColor(BLACK);
	((staticFrameWin*)sf1)->setBackColor(GREY);
	sf2->registerWin();
	((staticFrameWin*)sf2)->setTextColor(WHITE);
	((staticFrameWin*)sf2)->setBackColor(BLACK);
	bt1->registerWin();
	bt1->setWinProc(winWeakProc2);
	((buttonWin*)bt1)->setTextColor(BLACK);
	((buttonWin*)bt1)->setBackColor(RED);
	bt2->registerWin();
	bt2->setWinProc(winWeakProc3);
	((buttonWin*)bt2)->setTextColor(BLACK);
	((buttonWin*)bt2)->setBackColor(YELLOW);
	
	bt3->registerWin();
	bt3->setWinProc(winWeakProc4);
	((buttonWin*)bt3)->setTextColor(BLACK);
	((buttonWin*)bt3)->setBackColor(CYAN);
	
	
	((listBarWin*)lbw1)->setTextColor(BLACK);
	((listBarWin*)lbw1)->setBackColor(GREEN);
	lbw1->registerWin();
	
	mw->paintAll();
	//------------------------窗口介绍------------------------
	
	//----------------------信息处理函数----------------------
	uint16_t x,y;
	rootWin* rw;
	uint32_t data1;
	uint32_t data2;
	uint8_t stat = 0;//确定是否按下 以及脱手
	message* buffer; 
	buffer = (message*)pvPortMalloc(sizeof(message));
	printf("message = %d\n",sizeof( message));
	while(1)//获取msg
	{
		ClickHandle(x,y,&data1,&data2,mw,&stat); //点击处理函数
		portBASE_TYPE xStatus = xQueueReceive(queue,buffer,0); //获取信息
		if(xStatus == pdPASS )
		{
			printf("have msg -- type = %d",buffer->type);
			rw = buffer->destWin;
			//这里应该判断是否有窗口过程，没有就使用默认winProc函数
			if(rw->isHaveWinProc())
			{
				rw->winProc(buffer->destWin,buffer->fromWin,buffer->type,buffer->data1,buffer->data2);
				printf("end\n");
			}
			else
			{
				rw->setWinProc(winDefaultProc);
				rw->winProc(buffer->destWin,buffer->fromWin,buffer->type,buffer->data1,buffer->data2);
			}
		}
	}
}

//------------------------------------static function------------------------------------

static void winDefaultProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2)
{ //默认没有参数 可以添加这个 把数据原封不动的给父类
	switch(mt)
	{
		default: 
			if(rw->getParent() != NULL){
				message* msg = new message();
				msg->type = mt;
				msg->data1 = d1;
				msg->data2 = d2;
				msg->destWin = rw->getParent();
				msg->fromWin = fw; //
				rw->sendMSGtoBack(msg,queue);
			}break; 
	}
}	

//窗口过程0
static void winWeakProc0(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 0\n");
	switch(mt)
	{
		
		default:	//处理不了就给父类
		if(rw->getParent() != NULL){
			message* msg = new message();
			msg->type = mt;
			msg->data1 = d1;
			msg->data2 = d2;
			msg->destWin = rw->getParent();
			msg->fromWin = fw; //
			rw->sendMSGtoBack(msg,queue);
		}else{
			printf("undefinition msg");
		}break;
	}
}

//窗口过程1
static void winWeakProc1(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 1\n");
	switch(mt)
	{
		case MSG_CLOSE: 
		{
			printf("close\n");
			
			//这里可能会画出去  在内部还需要调整 
			rw->setWinXpos(100);
			rw->setWinYpos(0);
			rw->setWinWidth(700);
			rw->setWinHigh(480);
			rw->paintAll();
			
		}break;
		case MSG_OTHER:
		{
			rw->setWinXpos(0);
			rw->setWinYpos(0);
			rw->setWinWidth(800);
			rw->setWinHigh(480);
			rw->paintAll();
			printf("data1 = %d \n",d1);
			printf("data2 = %d \n",d2);	
		}
		default:
		if(rw->getParent() != NULL)
		{
			message* msg = new message();
			msg->type = mt;
			msg->data1 = d1;
			msg->data2 = d2;
			msg->destWin = rw->getParent();
			msg->fromWin = fw; //
			rw->sendMSGtoBack(msg,queue);
		}break;
	}
}

//窗口过程2
static void winWeakProc2(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 2\n");
	switch(mt)
	{
		case MSG_CLICK: 
		{
			((buttonWin*)rw)->pressButton();//显示被按下
		}break;
		case MSG_UNCLICK:
		{
			((buttonWin*)rw)->releaseButton();//显示松开
			d1 = d2 = 0;
			message* msg = new message();
			msg->type = MSG_CLOSE;
			msg->data1 = d1;
			msg->data2 = d2;
			msg->destWin = rw->getParent();
			msg->fromWin = rw;
			rw->sendMSGtoBack(msg,queue);
		}break;
		default:	//处理不了就给父类
		if(rw->getParent() != NULL){
			message* msg = new message();
			msg->type = mt;
			msg->data1 = d1;
			msg->data2 = d2;
			msg->destWin = rw->getParent();
			msg->fromWin = fw; //
			rw->sendMSGtoBack(msg,queue);
		}break;
	}
} 
static void winWeakProc3(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 3\n");
	switch(mt)
	{
		case MSG_CLICK: 
		{
			((buttonWin*)rw)->pressButton();//显示被按下
		}break;
		case MSG_UNCLICK:
		{ 
			((buttonWin*)rw)->releaseButton();//显示松开 
			message* msg = new message();
			msg->type = MSG_OTHER;
			msg->data1 =  5201314;
			msg->data2 =  950219;
			msg->destWin = rw->getParent();
			msg->fromWin = rw;
			rw->sendMSGtoBack(msg,queue);
		}break;
		default:	//处理不了就给父类
		if(rw->getParent() != NULL){
			message* msg = new message();
			msg->type = mt;
			msg->data1 = d1;
			msg->data2 = d2;
			msg->destWin = rw->getParent();
			msg->fromWin = fw; //
			rw->sendMSGtoBack(msg,queue);
		}break;
	}
} 

static void winWeakProc4(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 4\n");
	switch(mt)
	{
		case MSG_CLICK: 
		{
			((buttonWin*)rw)->pressButton();//显示被按下
		}break;
		case MSG_UNCLICK:
		{
			((buttonWin*)rw)->releaseButton();//显示松开
			LCD_SetColors(RED,RED);
			LCD_FillTriangle(300,500,400,240,240,340);
			LCD_DrawFullCircle(350,190,70);
			LCD_DrawFullCircle(450,190,70);
		}break;
		default:	//处理不了就给父类
		if(rw->getParent() != NULL){
			message* msg = new message();
			msg->type = mt;
			msg->data1 = d1;
			msg->data2 = d2;
			msg->destWin = rw->getParent();
			msg->fromWin = fw; //
			rw->sendMSGtoBack(msg,queue);
		}break;
	}
} 

 
static void ClickHandle(uint16_t x , uint16_t y ,uint32_t *data1,uint32_t *data2,rootWin* mw,uint8_t* stat)
{
	//--------- 获取点按情况 ---------
	//stat 这里有点绝对 按下就不再获取x ，y值了 像滑块就无法实现了需改进
	if(getTouchUP() == 0 && (*stat) == 0)
	{
		GUIGetPoint(&x,&y);
		if(x < GUI_WIDTH && y < GUI_HIGH)
		{	
			printf("touch up = 0\n");
			*data1 = x;
			*data2 = y;
			*stat = 1;
			rootWin* dw = mw->locateWin(x,y);
			if(dw!=NULL){tempWin = dw;}
			message* msg = new message();
				msg->type = MSG_CLICK;
				msg->data1 = *data1;
				msg->data2 = *data2;
				msg->destWin = tempWin;
				msg->fromWin = NULL;
			if(xQueueSendToBack(queue,msg,0) == pdPASS)
			{
				delete msg;
			}
		}
	}
	else if(getTouchUP() != 0 && (*stat) == 1 )//之前按下的 松开
	{
		//获取 松开后的下x,y
		
		//
		printf("touch up = 1\n");
		*stat = 0;
		message* msg =  new message();
			msg->type = MSG_UNCLICK;
			msg->data1 = *data1;
			msg->data2 = *data2;
			msg->destWin = tempWin;
			msg->fromWin = NULL;
		if(xQueueSendToBack(queue,msg,0) == pdPASS)
		{
			delete msg;
		}
	}
}


