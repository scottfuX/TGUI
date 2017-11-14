#include "main.h"


//设置存储在SDRAM上 由.sct文件修改配置 .map文件可用于查看文件存储情况
//#define __EXRAM   __attribute__ ((section ("EXRAM")))
//例如：uint8_t a[40] __EXRAM={0};

int BufMaxNum = 10; 
int USART1_Buf[10];


int main(void)
{
	LED_RED_Config();
	LED_GREEN_Config();
	LED_BLUE_Config(); 
	USART1Config();
	FLASHConfig();
	GTP_Init_Panel(); //初始化触摸屏 
	LCDConfig();
	
	GUI_Run();
	//每个函数都要用while结尾
	
	while(1);
}
