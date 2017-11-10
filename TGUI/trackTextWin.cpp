#include "winClass.hpp"

trackTextWin::trackTextWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
		trackWin = new trackBarWin(winXpos,winYpos,(winWidth-(getFont().Width)*5),winHigh,name,parent,queue,true);
		slidertext = new staticFrameWin((getWinWidth()-(getFont().Width)*5),0,getFont().Width*5,getWinHigh(),NULL,this,getQueue());
		textStr = new char[5];
}


trackTextWin::~trackTextWin()
{

}

void trackTextWin::paintText()
{
			int ge = trackWin->getSliderValue()%10;
			int shi = trackWin->getSliderValue()/10%10;
			int bai = trackWin->getSliderValue()/100;
			textStr[0] = bai+48;
			textStr[1] = shi+48;
			textStr[2] = ge+48;
			textStr[3] = '%';
			textStr[4] = '\0';
			((staticFrameWin*)slidertext)->displayStrCenter(getFont(),getTextColor(),getBackColor(),textStr);
}

void trackTextWin::sliderSliding(uint16_t xpos,uint16_t ypos)
{
	trackWin->sliderSliding(xpos,ypos);
	paintText();
}

void trackTextWin::releaseSlider()
{
	trackWin->releaseSlider();
}
void trackTextWin::paintWin()
{
	trackWin->paintWin();
	paintText();
}
void trackTextWin::registerWin()
{
	rootWin::registerWin();
}	
void trackTextWin::unregisterWin()
{
	rootWin::unregisterWin();
}
void trackTextWin::destroyWin()
{
	if(textStr != NULL)
	{delete textStr;}
	if(slidertext != NULL)
	{slidertext->destroyWin();}
	rootWin::destroyWin();
}



