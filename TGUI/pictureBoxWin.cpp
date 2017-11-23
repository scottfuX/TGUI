#include "winClass.h"

pictureBoxWin::pictureBoxWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	):controlWin(winXpos,winYpos,winWidth,winHigh,name,parent,queue)
{
	BmpAddress = 0;
}
pictureBoxWin::~pictureBoxWin()
{
	
}

void pictureBoxWin::paintWin()
{
	if(BmpAddress)
	{
		LCD_WriteBMP(BmpAddress);
	}
}

void pictureBoxWin::registerWin()
{
	rootWin::registerWin();
}	
void pictureBoxWin::unregisterWin()
{
	rootWin::unregisterWin();
}
void pictureBoxWin::destroyWin()
{
	rootWin::destroyWin();
}
