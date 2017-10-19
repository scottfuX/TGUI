#include "winClass.h"

button::button():controlWin()
{
	
}
button::button(uint8* winTitle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh)\
:controlWin(winTitle,winXpos,winYpos,winWidth,winHigh)
{

}

bool button::isInArea(uint16 Xpos,uint16 Ypos)
{
	return true;
}
retStatus button::sendMessage(Message msg)
{
	return GUI_OK;
}
void button::layoutControl()
{

}
void button::createControl()
{

}
retStatus button::execControl()
{
		return GUI_OK;
}
