#ifndef _TGUICONF_H_
#define _WINCLASS_H_ 

#include "includes_all.h"
#include "USART/USARTConfig.h"
#include "LCD/LCDConfig.h"
#include "FreeRTOS.h"


//#define RGB_565
//#define RGB_888
//#define RGB_1555
//#define RGB_8888
	

//基本LCD	
#define GUI_COLORMODE		RGB_565	
#define GUI_BUFADDR 		LCD_FRAME_BUFFER 
#define GUI_BUFSIZE 		BUFFER_OFFSET
#define GUI_WIDTH				LCD_PIXEL_WIDTH
#define GUI_HIGH				LCD_PIXEL_HEIGHT

//采用的颜色
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

//队列
#define QUEUETYPE xQueueHandle
#define SENDQUEUE  xQueueSendToBack
#

//优先级
#define HUP_TASK_PRIORITY 1 //Hang up
#define RUN_TASK_PRIORITY 2

#define MSG_QUENUM		5 //消息队列存放消息个数

//像素位置
#define STAT_BAR  GUI_HIGH/15
#define CONTENT_AREA_X 			0
#define CONTENT_AREA_Y STAT_BAR

#define APP_MAX_NUM 10
//app像素种类
#define APP_HIGH (GUI_HIGH-STAT_BAR)/3 //APP总大小 约150
#define APP_ETR_HIGH  APP_HIGH/6   	//外边框高度
#define APP_INT_HIGH  APP_HIGH/3*2 	//内边框高度
#define APP_LINE_NUM  5//800/APP_HIGH //一行的APP数


void GUISetPoint(uint16_t x,uint16_t y);
void GUIGetPoint(uint16_t* x,uint16_t* y);
void GUITouchUp(int16_t xid,int16_t yid);
void GUITouchDown(uint16_t x,uint16_t y);

#endif //!  _TGUICONF_H_ 
