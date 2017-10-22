#include "winClass.h"

controlWin::controlWin(Message* controlMsg):rootWin()
{
	this->controlMsg = controlMsg;
}
	
controlWin::controlWin(uint8_t* winTitle,uint16_t winXpos,uint16_t winYpos,uint16_t winWidth,uint16_t winHigh,Message* controlMsg)\
:rootWin(winTitle,winXpos,winYpos,winWidth,winHigh)
{
	this->controlMsg = controlMsg;
}

controlWin::~controlWin(){
}

void controlWin::setControlMsg(Message* MsgTemp)
{
	this->controlMsg = MsgTemp;
}

Message* controlWin::getControlMsg()
{
	return this->controlMsg;
}

