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

//¾ÓÖÐ´òÓ¡×Ö·û´®
void controlWin::displayStrCenter(sFONT font,uint32_t textColor,uint32_t backColor,char* str)
{
	if(str != NULL){
		uint16_t temp = 'L';
		uint8_t i = 0,num  = 0;
		while(str[num] != '\0' )
		{
			num++;
			if((getWinWidth()- font.Width*num) <= 0)
			{
				num--;
				break;
			}
		}
		uint16_t line = getAbsoluteY() + ((getWinHigh()- font.Height)/2);
		uint16_t column = getAbsoluteX() + ((getWinWidth()- font.Width*num)/2);
		LCD_SetFont(&font);
		LCD_SetColors(textColor,backColor);
		while(i < num )
		{
			temp = (uint16_t) str[i];
			LCD_DisplayChar(line,column,temp);
			column += font.Width;
			i++;
		}
	}
}
