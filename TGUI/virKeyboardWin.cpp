#include "winClass.h"

static void keyboardProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2);

virKeyboardWin::virKeyboardWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	destWorkWin = NULL;
	shiftStat = 0;
	capsLockStat = 0;
	setIsMutable(true);
}


virKeyboardWin::~virKeyboardWin()
{

}
 
void virKeyboardWin::keyBoardInit()
{
	char* keyb[] ={"`~","1!","2@","3#","4$","5%","6^","7&","8*","9(","0)","-_","=+","delete",
	 "tab" ,"q","w","e","r","t","y","u","i","o","p","[{","]}","\\|",
		"caps lock" ,"a","s","d","f","g","h","j","k","l",";:","'\"", "return" ,
	 "shift" ,"z","x","c","v","b","n","m",",<",".>","/?","shift",
	 "ctrl" , "alt" ,"space", "alt" ,"ctrl" };
	int i,j,temp;
	setRwNum(60);
	comboBoxInit();
	uint16_t w = (getWinWidth()- getWinWidth()/29)/14;
	uint16_t h = getWinHigh()/5;
	uint8_t n ;//中间按键数量
	uint16_t x;//x的位置
	uint16_t wt;
	for(i=0;i<4;i++) //1-3 line
	{
		wt = w ;
		switch(i)
		{
			case 0:{n = 12;temp = 0;}break;
			case 1:{
				wt += w/2;
				n = 12;
			} ;break;
			case 2:{
				wt += w*3/4;
				n = 11;
			}break;
			case 3:{
				wt += w+w/4;
				n = 10;
			}break;
			default:break;
		}	
		getRwList()[temp] = new buttonWin(0,i*h,wt,h,keyb[temp],this,getQueue());
		((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
		((controlWin*)getRwList()[temp])->setBackColor(getBackColor());
		getRwList()[temp]->setWinProc(keyboardProc);
		getRwList()[temp]->registerWin();
		for(j=0;j<n;j++)
		{
			temp ++;
			getRwList()[temp] = new buttonWin(wt,i*h,w,h,keyb[temp],this,getQueue());
			((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
			((controlWin*)getRwList()[temp])->setBackColor(getBackColor());
			getRwList()[temp]->setWinProc(keyboardProc);
			getRwList()[temp]->registerWin();
			wt += w;	
		}
		x = wt;
		temp ++;//每一行最后一个
		wt = w;
		switch(i)
		{
			case 0:{wt += w/2;}break;
			case 1:{wt = w;}break;
			case 2:{wt += w*3/4;}break;
			case 3:{wt += w+w/4;}break;
			default:break;
		}	
		getRwList()[temp] = new buttonWin(x,i*h,wt,h,keyb[temp],this,getQueue());
		((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
		((controlWin*)getRwList()[temp])->setBackColor(getBackColor());
		getRwList()[temp]->setWinProc(keyboardProc);
		getRwList()[temp]->registerWin();
		temp ++;
	}
	//line 4
	x = 2*w;
	for(i=0;i<5;i++)
	{
		if(i==2)
		{
			getRwList()[temp] = new buttonWin(x,4*h,w*5,h,keyb[temp],this,getQueue());
			((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
			((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
			getRwList()[temp]->setWinProc(keyboardProc);
			getRwList()[temp]->registerWin();
			x+=w*5;
		}else{
			getRwList()[temp] = new buttonWin(x,4*h,w,h,keyb[temp],this,getQueue());
			((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
			((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
			getRwList()[temp]->setWinProc(keyboardProc);
			getRwList()[temp]->registerWin();
			x += w;
		}
		temp++;
	}
	getRwList()[temp] = new buttonWin(0,4*h,2*w,h,"V",this,getQueue());
	((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
	((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
	getRwList()[temp]->setWinProc(keyboardProc);
	getRwList()[temp]->registerWin();
	temp++;
	getRwList()[temp] = new buttonWin(x,4*h,3*w+w/2,h,"V",this,getQueue());
	((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
	((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
	getRwList()[temp]->setWinProc(keyboardProc);
	getRwList()[temp]->registerWin();
	temp++;
}

//数值转换为字符
void virKeyboardWin::intConverChar(uint32_t data1,uint32_t data2,char *c)
{
		*c = 0;
		switch(((char)data1))
		{
			case 's':
				if(((char)data2) == 'h'){*c = 16;shiftStat = 1;break;}//shift	
				if(((char)data2) == 'p'){*c = 32;};break;//space
			case 'd':
				if(((char)data2) == 'e'){*c = 46;};break;//delete
			case 'r':
				if(((char)data2) == 'e'){*c = 8;};break;//return	
			case 't':
				if(((char)data2) == 'a'){*c = 9;};break;//tab
			case 'c':
				if(((char)data2) == 'a')
				{*c = 20;
					if(capsLockStat){capsLockStat =0;}
					else {capsLockStat =1;}
				;break;}//caps lock
				if(((char)data2) == 't'){*c = 17;break;}//Control 待定
				;break;
			case 'a':	
				if(((char)data2) == 'l'){*c = 18;};break;//alt 待定
			case 'V': {unregisterWin();
				readFromBuf();//>>>从缓冲区中读取出来
			*c = 0;return;}//回收
		}
		if(*c == 0)
		{
			if(shiftStat == 0)//shift 
			{//未用shift
				if(capsLockStat != 0 && ((char)data2) == '\0')
				{
					*c = ((char)data1) - 32;
				}else{
					*c  = ((char)data1);
				}	
			}else if(((char)data2) != '\0')
			{//其他 --use shift
				*c = ((char)data2);
				shiftStat = 0;
			}else
			{//字母 --use shift
				if(capsLockStat == 0)
					{*c = ((char)data1) - 32;}
				else
					{*c = ((char)data1);}
				shiftStat = 0;
			}
		}
}
//唤醒并链接
void virKeyboardWin::wakeupAndConnect(rootWin*rw)
{
		setDestWorkWin(rw);//设置目标对象
		registerWin();//注册
		paintAll();//绘制
}

//键盘发送器
void virKeyboardWin::keyboardSendChar(char c)
{
		message* msg = new message();
		msg->type = MSG_CHAR;
		msg->data1 = c;
		msg->data2 = 0;
		msg->destWin = destWorkWin;
		msg->fromWin = this; //目标
		sendMSGtoBack(msg,getQueue());
}
void virKeyboardWin::paintWin()
{
	movtoFront();
}

void virKeyboardWin::registerWin()
{
	if(!isRegisterWin())
	{
		saveToBuf();//先把要覆盖的数据保存到缓冲区
		rootWin::registerWin();
	}
	
}

void virKeyboardWin::unregisterWin()
{
	rootWin::unregisterWin();
}

void virKeyboardWin::destroyWin()
{
	comboBoxDestroy();
	rootWin::destroyWin();
}

//显示器存到缓冲区
void virKeyboardWin::saveToBuf()
{
	uint16_t i,j;
	uint16_t lineWidth = (getWinWidth()+1)*GUI_PIXELSIZE;//每行宽度
	uint16_t lineNum = getWinHigh()+1;//多少行
	uint16_t offset;
	uint32_t cP;
	cP	= (getAbsoluteX()+(getAbsoluteY())*GUI_WIDTH)*GUI_PIXELSIZE;//可能不是h衡向存储的
	uint16_t nextLine = GUI_WIDTH*GUI_PIXELSIZE;
	for(i=0;i<lineNum;i++)
	{	
		for(j=0;j<lineWidth;j++)
		{
			offset = j;
			win_buffer[cP+offset] = GUI_BUFADDR[cP+offset];
		}
			cP +=nextLine;
	}
}

//缓冲区读到显示器
void virKeyboardWin::readFromBuf()
{
	uint16_t i,j;
	uint16_t lineWidth = (getWinWidth()+1)*GUI_PIXELSIZE;//每行宽度
	uint16_t lineNum = getWinHigh()+1;//多少行
	uint16_t offset;
	uint32_t cP;
	cP = (getAbsoluteX()+(getAbsoluteY())*GUI_WIDTH)*GUI_PIXELSIZE;//可能不是h衡向存储的
	uint16_t nextLine = GUI_WIDTH*GUI_PIXELSIZE;
	for(i=0;i<lineNum;i++)
	{
		for(j=0;j<lineWidth;j++)
		{
			offset = j;
			GUI_BUFADDR[cP+offset] = win_buffer[cP+offset];
		}
			cP +=nextLine;
		
	}
}
static void keyboardProc(rootWin* rw,rootWin* fw, MsgType mt, uint32_t d1, uint32_t d2)
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
			if(rw->isInArea(d1,d2))
			{
				message* msg = new message();
				msg->type = MSG_KEYBOARD;
				msg->data1 = (uint32_t)(rw->getWinName()[0]);
				msg->data2 = (uint32_t)(rw->getWinName()[1]);
				msg->destWin = rw->getParent();
				msg->fromWin = fw; //
				rw->sendMSGtoBack(msg,rw->getQueue());
			}
		}break;
		default:break;
	}
}




//A <--------> 65
//B <--------> 66
//C <--------> 67
//D <--------> 68
//E <--------> 69
//F <--------> 70
//G <--------> 71
//H <--------> 72
//I <--------> 73
//J <--------> 74
//K <--------> 75
//L <--------> 76
//M <--------> 77
//N <--------> 78
//O <--------> 79
//P <--------> 80
//Q <--------> 81
//R <--------> 82
//S <--------> 83
//T <--------> 84
//U <--------> 85
//V <--------> 86
//W <--------> 87
//X <--------> 88
//Y <--------> 89
//Z <--------> 90
//0 <--------> 48
//1 <--------> 49
//2 <--------> 50
//3 <--------> 51
//4 <--------> 52
//5 <--------> 53
//6 <--------> 54
//7 <--------> 55
//8 <--------> 56
//9 <--------> 57
//数字键盘 1 <--------> 96
//数字键盘 2 <--------> 97
//数字键盘 3 <--------> 98
//数字键盘 4 <--------> 99
//数字键盘 5 <--------> 100
//数字键盘 6 <--------> 101
//数字键盘 7 <--------> 102
//数字键盘 8 <--------> 103
//数字键盘 9 <--------> 104
//数字键盘 0 <--------> 105
//乘号 <--------> 106
//加号 <--------> 107
//Enter <--------> 108
//减号 <--------> 109
//小数点 <--------> 110
//除号 <--------> 111
//F1 <--------> 112
//F2 <--------> 113
//F3 <--------> 114
//F4 <--------> 115
//F5 <--------> 116
//F6 <--------> 117
//F7 <--------> 118
//F8 <--------> 119
//F9 <--------> 120
//F10 <--------> 121
//F11 <--------> 122
//F12 <--------> 123
//F13 <--------> 124
//F14 <--------> 125
//F15 <--------> 126
//Backspace <--------> 8
//Tab <--------> 9
//Clear <--------> 12
//Enter <--------> 13
//Shift <--------> 16
//Control <--------> 17
//Alt <--------> 18
//Caps Lock <--------> 20
//Esc <--------> 27
//空格键 <--------> 32
//Page Up <--------> 33
//Page Down <--------> 34
//End <--------> 35
//Home <--------> 36
//左箭头 <--------> 37
//向上箭头 <--------> 38
//右箭头 <--------> 39
//向下箭头 <--------> 40
//Insert <--------> 45
//Delete <--------> 46
//Help <--------> 47
//Num Lock <--------> 144
//; : <--------> 186
//= + <--------> 187
//- _ <--------> 189
/// ? <--------> 191
//` ~ <--------> 192
//[ { <--------> 219
//| <--------> 220
//] } <--------> 221
//'' ' <--------> 222

//	char keyboard[][2] = {
//	{'`','~'},{'1','!'},{'2','@'},{'3','#'},{'4','$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'=','+'},{ 1 ,'d'},
//	{ 2 ,'t'},{'q','Q'},{'w','W'},{'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},{'\\','|'},
//	{ 3 ,'l'},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'},{';',':'},{'\'','"'},{ 4 ,'r'},
//	{ 5 ,'s'},{'z','Z'},{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'},{',','<'},{'.','>'},{'/','?'},{6,'s'},
//	{ 7 ,'c'},{ 8 ,'a'},{' ',' '},{ 9 ,'a'},{10 ,'c'}
//	};
