#ifndef _TGUICONF_H_
#define _WINCLASS_H_ 

#include "includes_all.h"
#include "USART/USARTConfig.h"
#include "LCD/LCDConfig.h"
#include "Font/fonts.h"
#include "FreeRTOS.h"


//#define RGB_565
//#define RGB_888
//#define RGB_1555
//#define RGB_8888
extern uint8_t LCD_BUFADDR[];

//基本LCD	
#define GUI_COLORMODE		RGB_565	
#define GUI_PIXELSIZE		2          		 //每个像素2字节
#define GUI_BUFADDR 	LCD_BUFADDR //lcd存储基地址 
#define GUI_BUFSIZE 	BUFFER_OFFSET
#define GUI_WIDTH			LCD_PIXEL_WIDTH
#define GUI_HIGH			LCD_PIXEL_HEIGHT

//采用的颜色
#define DESTROYCOLOR RGB888ToRGB565(0xFB4A4A)
#define CLOSECOLOR RGB888ToRGB565(0xFDB324)

#define GREY1 RGB888ToRGB565(0xE0E0E0)
#define GREY2 RGB888ToRGB565(0xCFCFCF)
	
#define WHITE  		LCD_COLOR_WHITE          
#define BLACK 		LCD_COLOR_BLACK          
#define GREY 			LCD_COLOR_GREY           
#define BLUE 			LCD_COLOR_BLUE           
#define BLUE2 		LCD_COLOR_BLUE2          
#define RED 			LCD_COLOR_RED            
#define MAGENTA 	LCD_COLOR_MAGENTA        
#define GREEN 		LCD_COLOR_GREEN          
#define CYAN 			LCD_COLOR_CYAN           
#define YELLOW 		LCD_COLOR_YELLOW    

//队列
#define QUEUETYPE xQueueHandle
#define SENDQUEUE  xQueueSendToBack
//消息队列存放消息个数 
#define MSG_QUENUM	   10 //适度调大
//队列满时的等待时间  单位freertos的tisk周期（tisk默认1ms）
#define QUE_WAIT_TIME  10 //10ms

//优先级
#define HUP_TASK_PRIORITY 1 //Hang up
#define RUN_TASK_PRIORITY 2

//采样点数
#define SAMPLING_POINT 20

//像素位置
#define STAT_BAR  32
#define SYS_BTN_W 53
#define CONTENT_AREA_X 			0
#define CONTENT_AREA_Y STAT_BAR

#define APP_MAX_NUM 10
//app像素种类
#define APP_HIGH 			150//APP总大小 约150
#define APP_ETR_HIGH  25 	//外边框高度
#define APP_INT_HIGH 	100	//内边框高度
#define APP_LINE_NUM  5 //800/APP_HIGH //一行的APP数


void GUISetPoint(uint16_t x,uint16_t y);
void GUIGetPrePoint(uint16_t* x,uint16_t* y);
void GUIGetPoint(uint16_t* x,uint16_t* y);
void GUITouchUp(int16_t xid,int16_t yid);
void GUITouchDown(uint16_t pre_x,uint16_t pre_y,uint16_t x,uint16_t y);
uint8_t getTouchUP(void);
#endif //!  _TGUICONF_H_ 
