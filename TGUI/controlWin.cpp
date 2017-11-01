#include "winClass.hpp"

controlWin::controlWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
):rootWin(winXpos,winYpos,winWidth,winHigh,name,wsStyle,parent,queue)
{

}

controlWin::~controlWin()
{

}
