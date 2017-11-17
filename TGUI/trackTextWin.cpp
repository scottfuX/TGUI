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
		
}


trackTextWin::~trackTextWin()
{

}
void trackTextWin::trackTextInit()
{
	setRwNum(2);
	comboBoxInit();
	getRwList()[0] = new trackBarWin(getWinXpos(),getWinYpos(),(getWinWidth()-(getFont().Width)*5),getWinHigh(),\
		getWinName(),getParent(),getQueue(),true);
	getRwList()[1] = new staticFrameWin((getWinXpos()+getWinWidth()-(getFont().Width)*5),getWinYpos(),getFont().Width*5,\
		getWinHigh(),NULL,getParent(),getQueue());
		textStr = new char[5];
}

void trackTextWin::paintText()
{
			int ge = ((trackBarWin*)getRwList()[0])->getSliderValue()%10;
			int shi = ((trackBarWin*)getRwList()[0])->getSliderValue()/10%10;
			int bai = ((trackBarWin*)getRwList()[0])->getSliderValue()/100;
			textStr[0] = bai+48;
			textStr[1] = shi+48;
			textStr[2] = ge+48;
			textStr[3] = '%';
			textStr[4] = '\0';
			((staticFrameWin*)getRwList()[1])->displayStrCenter(getFont(),getTextColor(),getBackColor(),textStr);
}

void trackTextWin::sliderSliding(uint16_t xpos,uint16_t ypos)
{
	((trackBarWin*)getRwList()[0])->sliderSliding(xpos,ypos);
	paintText();
}

void trackTextWin::releaseSlider()
{
	((trackBarWin*)getRwList()[0])->releaseSlider();
}
void trackTextWin::paintWin()
{
	((trackBarWin*)getRwList()[0])->paintWin();
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
	comboBoxDestroy();
	rootWin::destroyWin();
}



