#include "winClass.hpp"

textBarWin::textBarWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue,
		uint16_t bufSize
	):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	
		this->bufSize = bufSize;
	  textBuf = new char[bufSize];
		bufIndicator = 0;
}
textBarWin::~textBarWin()
{
	
}

void textBarWin::writeChar(char c)
{
	if(bufIndicator <= bufSize)
	{
		textBuf[bufIndicator] = c;
		displayChar(c);
	}
	bufIndicator++;
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
	paintWin();
}

void textBarWin::paintWin()
{
	LCD_SetColors(getBackColor(),getBackColor());
	LCD_DrawFullRect(getAbsoluteX(),getAbsoluteY(),getWinWidth(),getWinHigh());
	displayStrNormal(getFont(),getTextColor(),getBackColor(),textBuf);
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
	LCD_SetFont(&f);
	LCD_SetColors(getTextColor(),getBackColor());
	LCD_DisplayChar(charX,charY,c);
	charX += getFont().Width;
	if(charX > getAbsoluteX()+getWinWidth())
	{
		charX = getAbsoluteX();
		charY += getFont().Height;
		if(charY > getAbsoluteY()+getWinHigh())
		{
			charY =  getAbsoluteY();//溢出就从头打
		}
	}
}
