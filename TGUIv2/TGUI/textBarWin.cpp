#include "winClass.h"

textBarWin::textBarWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	bufSize = winHigh/(getFont().Height) * winWidth/(getFont().Width)-1;
	textBuf = new char[bufSize];
	bufIndicator = 0;
	charX = getAbsoluteX();
	charY = getAbsoluteY();
}
textBarWin::~textBarWin()
{
	
}

void textBarWin::writeChar(char c)
{
	switch(c)
	{ 
		case 46:deleteChar();/*delete*/break;
		case 16:/*shift*/break;
		case 8 :returnLine();/*enter*/break;
		case 9 :/*tab*/break;
		case 20:/*caps lock*/break;
		case 17:/*ctrl*/break;
		case 18:/*alt*/break;
		case 0 :/*other*/break;
		default:
		if(bufIndicator <= bufSize)
		{
			textBuf[bufIndicator] = c;
			displayChar(c);
			bufIndicator++;
		}
	}
}

void textBarWin::deleteChar()
{
	if(bufIndicator > 0)
	{
		bufIndicator--;
		textBuf[bufIndicator] = 0;
		paintAll();
	}
}
void textBarWin::returnLine()//回车换行  ---这里应该设置一些符号换行符
{
	if((charY+getFont().Height) <= getAbsoluteY()+getWinHigh())
	{
		charX = getAbsoluteX();
		charY += getFont().Height;
	}
}

void textBarWin::writeString(char* s,uint16_t n)//会打印出来
{
	if((bufIndicator + n - 1) <= bufSize)
	{	
		int i;
		for(i = 0 ; i < n ; i++)
		{
			writeChar(s[i]);
		}
	}
}

void textBarWin::setTextBuf(char* s,uint16_t n)
{
	if((n - 1) <= bufSize)
	{
		int i;
		for(i = 0 ; i < n ; i++)
		{
			textBuf[i] = s[i];
		}
		bufIndicator = i;
	}
	paintAll();
}

void textBarWin::paintWin()
{
	GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),getBackColor(),getInvalidList());
	a.setIsFull(true);
	a.draw();
	int i;
	charX = getAbsoluteX();
	charY = getAbsoluteY();
	for(i=0;i < bufIndicator ; i++)
	{displayChar(textBuf[i]);}
}


void textBarWin::paintInvalid(GUIArea * tarea)
{
	GUIRectangle a(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh(),getBackColor(),getInvalidList());
	a.setIsFull(true);
	a.drawInArea(tarea);
	int i;
	charX = getAbsoluteX();
	charY = getAbsoluteY();
	for(i=0;i < bufIndicator ; i++)
	{displayChar(textBuf[i]);}
}

void textBarWin::registerWin()
{
	rootWin::registerWin();

}

void textBarWin::unregisterWin()
{
	rootWin::unregisterWin();
}

void textBarWin::destroyWin()
{
	delete textBuf;
	rootWin::destroyWin();
}

void textBarWin::displayChar(char c)
{
	sFONT f =getFont();
	GUIChar guichar(charX,charY,&f, getTextColor(),getBackColor(),getInvalidList());
	guichar.displayChar(c);
	charX += getFont().Width;
	if(charX >= getAbsoluteX()+getWinWidth())
	{
		charX = getAbsoluteX();
		charY += getFont().Height;
		if(charY > getAbsoluteY()+getWinHigh())
		{
			charX = getAbsoluteX();
			charY = getAbsoluteY();//溢出就从头打
		}
	}
}
