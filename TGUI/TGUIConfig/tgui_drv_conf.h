#ifndef __TGUI_DRV_CONFIG_H_
#define __TGUI_DRV_CONFIG_H_


#include "includes_all.h"
#include "USART/USARTConfig.h"
#include "LCD/LCDConfig.h"
#include "FreeRTOS.h"

typedef  uint8_t uint8;
typedef  uint16_t uint16;
typedef  uint32_t uint32;
typedef	 int8_t int8;
typedef  int16_t int16;

//#define RGB_565
//#define RGB_888
//#define RGB_1555
//#define RGB_8888
	
#define MSG_QUENUM		5 //消息队列存放消息个数
	
#define GUI_COLORMODE		RGB_565	
	
#define GUI_BUFADDR 		LCD_FRAME_BUFFER 
#define GUI_BUFSIZE 		BUFFER_OFFSET
#define GUI_WIDTH			LCD_PIXEL_WIDTH
#define GUI_HIGH			LCD_PIXEL_HEIGHT

#define DESTROYCOLOR RGB888ToRGB565(0xFB4A4A)
#define CLOSECOLOR RGB888ToRGB565(0xFDB324)


#define BACK_COLOR RGB888ToRGB565(0xE0E0E0)//window back
#define STAT_COLOR RGB888ToRGB565(0xCFCFCF)//status bar
	
#define WHITE  	LCD_COLOR_WHITE          
#define BLACK 	LCD_COLOR_BLACK          
#define GREY 		LCD_COLOR_GREY           
#define BLUE 		LCD_COLOR_BLUE           
#define BLUE2 	LCD_COLOR_BLUE2          
#define RED 		LCD_COLOR_RED            
#define MAGENTA LCD_COLOR_MAGENTA        
#define GREEN 	LCD_COLOR_GREEN          
#define CYAN 		LCD_COLOR_CYAN           
#define YELLOW 	LCD_COLOR_YELLOW    



void GUISetPoint(uint16 x,uint16 y);
void GUIGetPoint(uint16* x,uint16* y);
void GUITouchUp(int16 xid,int16 yid);
void GUITouchDown(uint16 x,uint16 y);

#endif //!__TGUI_DRV_CONFIG_H_
