#include "createWin.hpp"
static void win0(void *pvParameters);

void GUI_Run()
{
	xTaskCreate( win0, "win0", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();		// 启动调度器，任务开始执行	
}


//用孩子兄弟二叉树的第一个孩子作为当前界面的

xQueueHandle queue =  xQueueCreate( MSG_QUENUM, sizeof( message));
rootWin* curClickWin;  

static void ClickHandle(uint16_t x , uint16_t y ,rootWin* mw,uint8_t* stat);
static void winDefaultProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc0(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc1(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc2(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc3(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc4(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc5(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc61(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc6(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc7(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);
static void winWeakProc71(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2);

progressBarWin* tempWin;
static void win0(void *pvParameters)
{
	//----------------这里开始配置窗口-------------------
	char t0[] = "IS TEST WIN !";
	char t1[] = "x";
	char t2[] = "-";
	char t3[] = "Lin Ying ";
	char t4[] = "listBar";
	char* item[] = {"item1","item2","item3"};
	char* o1[] = {"option1","option2","option3"};
	//mainWin
	rootWin* mw = new mainWin(0,0,GUI_WIDTH,GUI_HIGH,NULL,NULL,queue,WS_DEFAULT);
	//content
	rootWin* sf1 = new staticFrameWin(0,GUI_HIGH/15,GUI_WIDTH,GUI_HIGH-GUI_HIGH/15,NULL,mw,queue);
	//bar
	rootWin* sf2 = new staticFrameWin(0,0,GUI_WIDTH,GUI_HIGH/15,t0,mw,queue);
	rootWin* bt1 = new buttonWin(2,2,GUI_WIDTH/15,GUI_HIGH/15-4,t1,sf2,queue);
	rootWin* bt2 = new buttonWin(4+GUI_WIDTH/15,2,GUI_WIDTH/15,GUI_HIGH/15-4,t2,sf2,queue);
	rootWin* lbw1 = new listBarWin(50,50,180,30,t4,sf1,queue);
	rootWin* bt3 = new buttonWin(50,100,180,100,t3,sf1,queue);
	radioBtnWin* rbw1 = new radioBtnWin(50,230,180,100,NULL,sf1,queue);
	optionWin* opw1 = new optionWin(50,350,180,30,"check1",sf1,queue,false);
	optionWin* opw2 = new optionWin(50,400,180,30,"check2",sf1,queue,false);
	trackTextWin* tbw1 = new trackTextWin(280,50,380,30,NULL,sf1,queue);
	rootWin* tbw2 = new trackBarWin(750,30,30,400,NULL,sf1,queue,false);
	progressBarWin* pbw1 = new progressBarWin(280,110,300,30,NULL,sf1,queue);
	//------注册&打印-------
	mw->registerWin();
	mw->setWinProc(winWeakProc0);

	sf1->registerWin();
	sf1->setWinProc(winWeakProc1);
	
	((staticFrameWin*)sf2)->setTextColor(WHITE);
	((staticFrameWin*)sf2)->setBackColor(BLACK);
	sf2->registerWin();
	
	((buttonWin*)bt1)->setTextColor(BLACK);
	((buttonWin*)bt1)->setBackColor(RED);
	bt1->registerWin();
	bt1->setWinProc(winWeakProc2);
	((buttonWin*)bt2)->setTextColor(BLACK);
	((buttonWin*)bt2)->setBackColor(YELLOW);
	bt2->registerWin();
	bt2->setWinProc(winWeakProc3);
	
	
	((buttonWin*)bt3)->setTextColor(BLACK);
	((buttonWin*)bt3)->setBackColor(CYAN);
	bt3->registerWin();
	bt3->setWinProc(winWeakProc4);
	
	((listBarWin*)lbw1)->setTextColor(BLACK);
	((listBarWin*)lbw1)->setBackColor(GREEN);
	lbw1->setWinProc(winWeakProc5);
	((listBarWin*)lbw1)->itemInit(item,3);
	lbw1->registerWin();
	
	rbw1->radioBtnInit(o1,3,false);
	rbw1->registerWin();
	rbw1->setWinProc(winWeakProc6);
	
	opw1->registerWin();
	opw1->setWinProc(winWeakProc61);
	opw2->registerWin();
	opw2->setWinProc(winWeakProc61);
	
	
	tbw1->registerWin();
	tbw1->setWinProc(winWeakProc71);
	
	tbw2->registerWin();
	tbw2->setWinProc(winWeakProc7);

	pbw1->registerWin();
	tempWin = (progressBarWin*)pbw1;
	
	mw->paintAll();
	//------------------------窗口介绍------------------------
	
	//----------------------信息处理函数----------------------
	uint16_t x,y;
	rootWin* rw;
	uint8_t thouchStat = 0;//确定是否按下 以及脱手
	
	message* buffer; 
	buffer = (message*)pvPortMalloc(sizeof(message));
	printf("message = %d\n",sizeof( message));
	while(1)//获取msg
	{
		ClickHandle(x,y,mw,&thouchStat); //点击处理函数
		portBASE_TYPE xStatus = xQueueReceive(queue,buffer,0); //获取信息
		if(xStatus == pdPASS )
		{
			printf("-------have msg \ntype = %d\n",buffer->type);
			rw = buffer->destWin;
			//这里应该判断是否有窗口过程，没有就使用默认winProc函数
			if(rw->isHaveWinProc())
			{
				rw->winProc(buffer->destWin,buffer->fromWin,buffer->type,buffer->data1,buffer->data2);
				printf("-------end\n");
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
		case MSG_CLICK: break;
		case MSG_RELEASECLICK: break;
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
		case MSG_CLICK: break;
		case MSG_RELEASECLICK: break;
		case MSG_CLOSE: 
		{
			printf("close\n");
			
		}break;
		case MSG_OTHER:
		{
			printf("data1 = %d \n",d1);
			printf("data2 = %d \n",d2);	
		}
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
			printf("undefinition msg\n");
		}break;
	}
}

//窗口过程1
static void winWeakProc1(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 1\n");
	switch(mt)
	{
		case MSG_CLICK: break;
		case MSG_RELEASECLICK: break;
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
			if(rw->isInArea(d1,d2))
			{
				message* msg = new message();
				msg->type = MSG_CLOSE;
				msg->data1 = d1;
				msg->data2 = d2;
				msg->destWin = rw->getParent();
				msg->fromWin = rw;
				rw->sendMSGtoBack(msg,queue);
			}
		}
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
			if(rw->isInArea(d1,d2))
			{
				message* msg = new message();
				msg->type = MSG_OTHER;
				msg->data1 =  5201314;
				msg->data2 =  950219;
				msg->destWin = rw->getParent();
				msg->fromWin = rw;
				rw->sendMSGtoBack(msg,queue);
			}
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
			if(rw->isInArea(d1,d2))
			{
				LCD_SetColors(RED,RED);
				LCD_FillTriangle(300,500,400,240,240,340);
				LCD_DrawFullCircle(350,190,70);
				LCD_DrawFullCircle(450,190,70);
			}
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

static void winWeakProc5(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 5\n");
	switch(mt)
	{
		case MSG_CLICK: 
		{
			if(rw->isInArea((uint16_t)d1,(uint16_t)d2))
			{
				((listBarWin*)rw)->pressListBar();//显示被按下
			}else{
				((listBarWin*)rw)->releaseListBar();
			}
			
		}break;
		case MSG_RELEASECLICK:
		{
			((listBarWin*)rw)->releaseListBar();//松开 
			if(rw->isInArea(d1,d2))//若为空间内部松开-->执行应有的程序
			{
				((listBarWin*)rw)->changeOpenList();
			}
		}break;
		case MSG_ITEM:
		{
			char* temp = (char*)d1;
			printf("--%s\n",temp);
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
static void winWeakProc61(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 61\n");
	switch(mt)
	{
		case MSG_RELEASECLICK:
		{
			((optionWin*)rw)->clickOption();
			printf("check>>>>>>>>>>%d",((optionWin*)rw)->isSelect());
		}
		default:break;
	}
}

static void winWeakProc6(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 6\n");
	switch(mt)
	{
		case MSG_RADIOBTN: 
		{
			//显示被按下
			printf(">>>>>>>>>>>>>>%s\n",(char*)d1);
		}break;
		default:break;
	}
}

static void winWeakProc71(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 71\n");
	switch(mt)
	{
		case MSG_CLICK: 
		{//显示被按下
			((trackTextWin*)rw)->sliderSliding(d1,d2);
		}break;
		case MSG_RELEASECLICK:
		{
			((trackTextWin*)rw)->releaseSlider();//显示松开
		}break;
		default:break;
	}
}
static void winWeakProc7(rootWin* rw , rootWin* fw , MsgType mt, uint32_t d1, uint32_t d2)
{
	printf("winproc 7\n");
	switch(mt)
	{
		case MSG_CLICK: 
		{//显示被按下
			((trackBarWin*)rw)->sliderSliding(d1,d2);
				printf("slider---------->>>>>%d",((trackBarWin*)rw)->getSliderValue());
				tempWin->setProgressValue(((trackBarWin*)rw)->getSliderValue());
		}break;
		case MSG_RELEASECLICK:
		{
			((trackBarWin*)rw)->releaseSlider();//显示松开
		}break;
		default:break;
	}
}



static void ClickHandle(uint16_t x , uint16_t y ,rootWin* mw,uint8_t* stat)
{
	//--------- 获取点按情况 ---------
	//stat 这里有点绝对 按下就不再获取x ，y值了 像滑块就无法实现了需改进
	if(getTouchUP() == 0) //&& (*stat) == 0)
	{
		GUIGetPoint(&x,&y);
		if(x < GUI_WIDTH && y < GUI_HIGH)
		{	
			//若被按下为松开 且位置出了当前的窗口区，向之前的对象发送click信号
			if(*stat == 1)
			{		
				if(curClickWin != NULL)
				{
					message* msg = new message();
					msg->type = MSG_CLICK;
					msg->data1 = x;
					msg->data2 = y;
					msg->destWin = curClickWin;
					msg->fromWin = NULL;
					if(xQueueSendToBack(queue,msg,0) == pdPASS)
					{delete msg;}
				}
			}
			else//第一次点击时 寻找到其窗口 并发送click信号
			{
				printf("touch up = 0\n");
				rootWin* dw = mw->locateWin(x,y);
				*stat = 1;
				if(dw != NULL){curClickWin = dw;}
				message* msg = new message();
				msg->type = MSG_CLICK;
				msg->data1 = x;
				msg->data2 = y;
				msg->destWin = curClickWin;
				msg->fromWin = NULL;
				if(xQueueSendToBack(queue,msg,0) == pdPASS)
				{delete msg;}
			}
		}
	}
	else if(getTouchUP() != 0 && (*stat) == 1)//之前按下的 松开
	{
		//获取 松开后的下x,y
		printf("touch up = 1\n");
		*stat = 0;
		GUIGetPoint(&x,&y);
			message* msg =  new message();
			msg->type = MSG_RELEASECLICK;
			msg->data1 = x;
			msg->data2 = y;
			msg->destWin = curClickWin;
			msg->fromWin = NULL;
			if(xQueueSendToBack(queue,msg,0) == pdPASS)
			{delete msg;}
		curClickWin = NULL;
	}
}

