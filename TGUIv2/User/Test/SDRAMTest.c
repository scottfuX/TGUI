#include "Test/SDRAMTest.h"

//SDRAM
#define __EXRAM   __attribute__ ((section ("EXRAM")))
/*绝对定位方式访问SDRAM,这种方式必须定义成全局变量*/
//uint8_t testValue __attribute__((at(SDRAM_BANK_ADDR)));
uint8_t  testValue __EXRAM;

void SDRAM_Demo()
{
	/*对SDRAM进行读写测试，检测SDRAM是否正常*/
	if (SDRAM_Test() == 1)
	{
		  //测试正常 绿灯亮
		LED_GREEN_ON();			  
	}
	else
	{
		//测试失败 红灯亮
		LED_RED_ON();
	}
	
	//指针方式访问SDRAM
	{	
		uint32_t temp;
	
		printf("\r\npoint way to visit SDRAM\r\n");
	   //向SDRAM写入8位数据
		*(uint8_t*)(SDRAM_BANK_ADDR) = (uint8_t)0xAA;
		printf("\r\nponit visit SDRAM,write data 0xAA \r\n");

			 //从SDRAM读取数据
		temp =  *(uint8_t*)(SDRAM_BANK_ADDR);
		printf("read data: 0x%X \r\n", temp);

			 //写/读 16位数据
		*(uint16_t*)(SDRAM_BANK_ADDR + 10) = (uint16_t)0xBBBB;
		printf("ponit visit SDRAM,write data 0xBBBB \r\n");
	 
		temp =  *(uint16_t*)(SDRAM_BANK_ADDR + 10);
		printf("read data:0x%X \r\n", temp);


			 //写/读 32位数据
		*(uint32_t*)(SDRAM_BANK_ADDR + 20) = (uint32_t)0xCCCCCCCC;
		printf("ponit visit SDRAM,write data 0xCCCCCCCC \r\n");	 
		temp =  *(uint32_t*)(SDRAM_BANK_ADDR + 20);
		printf("read data:0x%X \r\n", temp);

	}

	//绝对定位方式访问SDRAM,这种方式必须定义成全局变量
	{
		testValue = 0xDD;
		printf("\r\nAbsolute positioning access SDRAM, write data 0xDD, read data 0x%X, variable address for %X\r\n", testValue, (uint32_t)&testValue);	 
	}
	
	
}
