#include "winClass.h"

controlWin::controlWin():rootWin()
{
	
}
	
controlWin::controlWin(uint8* winTitle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh)\
:rootWin(winTitle,winXpos,winYpos,winWidth,winHigh)
{

}

controlWin::~controlWin(){
}

