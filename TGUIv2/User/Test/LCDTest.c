#include "Test/LCDTest.h"


/*用于测试各种液晶的函数*/
void LCDTest(void)
{
	/*演示显示变量*/
	static uint8_t testCNT = 0;	
	char dispBuff[100];
	
	testCNT++;
	Delay(0xFF);
	/*使用不透明前景层*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER);  
	LCD_SetTransparency(0xff);
	
	LCD_Clear(LCD_COLOR_BLACK);	/* 清屏，显示全黑 */

	/*设置字体颜色及字体的背景颜色(此处的背景不是指LCD的背景层！注意区分)*/
	LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	  /*选择字体*/
	LCD_SetFont(&Font16x24);

	LCD_DisplayStringLine(LINE(1), (uint8_t*)"BH 5.0 inch LCD para:");
	LCD_DisplayStringLine(LINE(2), (uint8_t*)"Image resolution:800x480 px");
	LCD_DisplayStringLine(LINE(3), (uint8_t*)"Touch pad:5 point touch supported");
	LCD_DisplayStringLine(LINE(4), (uint8_t*)"Use STM32-LTDC directed driver,");
	LCD_DisplayStringLine(LINE(5), (uint8_t*)"no extern lcd driver needed,RGB888,24bits data bus");
	LCD_DisplayStringLine(LINE(6), (uint8_t*)"Touch pad use IIC to communicate");
  
	
	
	  /*使用c标准库把变量转化成字符串*/
	sprintf(dispBuff, "Display value demo: testCount = %d ", testCNT);
	LCD_ClearLine(LINE(7));
	
	/*然后显示该字符串即可，其它变量也是这样处理*/
	LCD_DisplayStringLine(LINE(7), (uint8_t*)dispBuff);

  /* 画直线 */
	LCD_SetTextColor(LCD_COLOR_BLUE);
  
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw line:");
  
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawUniLine(50, 250, 750, 250);  
	LCD_DrawUniLine(50, 300, 750, 300);
  
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawUniLine(300, 250, 400, 400);  
	LCD_DrawUniLine(600, 250, 600, 400);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
  
  
	/*画矩形*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw Rect:");
	
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawRect(200, 250, 200, 100);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawRect(350, 250, 200, 50);
	
	LCD_SetColors(LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	LCD_DrawRect(200, 350, 50, 200);
  
	Delay(0xFFFFFF);
  
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
  

	  /*填充矩形*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw Full Rect:");

	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawFullRect(200, 250, 200, 100);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawFullRect(350, 250, 200, 50);
	
	LCD_SetColors(LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	LCD_DrawFullRect(200, 350, 50, 200);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
	
	/* 画圆 */
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw circle:");
  
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_RED);
	LCD_DrawCircle(200, 350, 50);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_GREEN);
	LCD_DrawCircle(350, 350, 75);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);


	  /*填充圆*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine(LINE(8), (uint8_t*)"Draw full circle:");
  
	LCD_SetColors(LCD_COLOR_RED, LCD_COLOR_BLACK);
	LCD_DrawFullCircle(300, 350, 50);
	
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
	LCD_DrawFullCircle(450, 350, 75);
  
	Delay(0xFFFFFF);
  
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
	
	LCD_ClearLine(LINE(8));
	
//这种操作效果会有花屏现象，不推荐使用。一般背景混合使用ARGB格式的颜色来混合	
//	/*透明效果 前景层操作*/
//	{
//		LCD_SetTextColor(LCD_COLOR_BLUE);
//		LCD_ClearLine(LINE(8));
//		LCD_DisplayStringLine(LINE(8),(uint8_t* )"Transparency effect:");
//		
//		/*设置前景层不透明度*/
//		LCD_SetLayer(LCD_FOREGROUND_LAYER); 	
//		LCD_SetTransparency(200);
//		
//		/*在前景画一个红色圆*/
//		LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(400,350,75);
//	
//	}
//	
//	/*透明效果 背景层操作*/
//	{		
//		/*设置背景层不透明*/
//		LCD_SetLayer(LCD_BACKGROUND_LAYER); 	
//		LCD_SetTransparency(0xff);
//		LCD_Clear(LCD_COLOR_BLACK);

//		/*在背景画一个绿色圆*/
//		LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(450,350,75);
//		
//		/*在背景画一个蓝色圆*/
//		LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(350,350,75);
//	}
  
	Delay(0xFFFFFF);
	
	LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_BLACK);
	LCD_DrawFullRect(0, 200, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT - 200);
	
	LCD_SetFont(&Font16x24); 	

	LCD_Clear(LCD_COLOR_BLACK);	/* 清屏，显示全黑 */

	/*设置字体颜色及字体的背景颜色(此处的背景不是指LCD的背景层！注意区分)*/
	LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	//LCD_DisplayStringLineEx(0, 5, 16, 16, (uint8_t*)"傅429 16*16 ", 0);
	//LCD_DisplayStringLine_EN_CH(LINE(1), (uint8_t*)"广F429 24*24 ");
	//LCD_DisplayStringLineEx(0, 50, 32, 32, (uint8_t*)"涛F429 32*32 ", 0);
	//LCD_DisplayStringLineEx(0, 82, 48, 48, (uint8_t*)"--F429 48*48 ", 0);
	Delay(0xFFFFFF);

	/*经过LCD_SetLayer(LCD_FOREGROUND_LAYER)函数后，
	以下液晶操作都在前景层刷新，除非重新调用过LCD_SetLayer函数设置背景层*/		
	//使用不透明前景层
	
	
	LCD_SetLayer(LCD_FOREGROUND_LAYER);  
	LCD_SetTransparency(0xff);
	LCD_Clear(LCD_COLOR1555_YELLOW);	// 清屏，显示全黑 
	LCD_SetFont(&Font16x24); 
	LCD_SetColors(LCD_COLOR1555_GREEN, LCD_COLOR1555_RED);
	//LCD_DispString_EN_CH(LINE(1),0,"涛哥最帅！！！");
	//LCD_DisplayStringLineEx(0, 100, 100, 100, (uint8_t*)"涂文凯是大傻逼！！", 0);
	//LCD_DisplayStringLineEx(0, 240, 100, 100, (uint8_t*)"叶承昊也是大傻逼", 0);
	
	Delay(0xFFFFFF);


}
