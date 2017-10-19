#include "winClass.h"

rootWin::rootWin()
{
	uint8 defaultTitle[]= "default Title";
	this->winTitle = defaultTitle;
	this->winXpos = 0;
	this->winYpos = 0;
	this->winWidth = GUI_WIDTH;
	this->winHigh = GUI_HIGH;
	this->backColor = BACK_COLOR;
	this->statBarColor = STAT_COLOR;
}

rootWin::rootWin(uint8* winTitle,uint16 winXpos,uint16 winYpos,\
	uint16 winWidth,uint16 winHigh)
{
	this->winTitle = winTitle;
	this->winXpos = winXpos;
	this->winYpos = winYpos;
	this->winWidth = winWidth;
	this->winHigh = winHigh;
	this->backColor = BACK_COLOR;
	this->statBarColor = STAT_COLOR;
}

rootWin::~rootWin(){
	
}

//rootWin rootWin::createWin()
//{
//	//创建窗口对象
//	rootWin winTemp;
//	//设置消息传输队列
//	//createQueue();
//	//设定默认的控件
//	//createControl
//	//添加到控件列表
//	//addList
//	//建立线程
//	//xTaskCreate( task1_lcd_palette, "LCDPalette", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
//	//返回指定对象
//	return winTemp;
//	
//}


void rootWin::updateWin()
{
	uint8_t spr[]="                   hello world!";
	LCD_SetTextColor(backColor);
	LCD_DrawFullRect(winXpos,winYpos,winWidth,winHigh);
	LCD_SetTextColor(statBarColor);
	LCD_DrawFullRect(winXpos,winYpos,winWidth,winHigh/15);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,statBarColor);
	LCD_DisplayStringLine(LCD_LINE_0,spr );
	
	LCD_SetTextColor(RED);
	LCD_DrawFullRect(winXpos,winYpos,winHigh/15,winHigh/15);
	LCD_SetTextColor(YELLOW);
	LCD_DrawFullRect(winXpos+winHigh/15,winYpos,winHigh/15,winHigh/15);
	LCD_SetTextColor(GREEN);
	LCD_DrawFullRect(winXpos+winHigh/15*2,winYpos,winHigh/15,winHigh/15);
	
}

