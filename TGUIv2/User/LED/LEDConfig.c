#include "LED/LEDConfig.h"


void LED_RED_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOH, &GPIO_InitStructure); 
	GPIO_WriteBit(GPIOH, GPIO_Pin_10, Bit_SET);
}

void LED_GREEN_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOH, GPIO_Pin_11, Bit_SET);
}

void LED_BLUE_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOH, GPIO_Pin_12, Bit_SET);
}

void LED_RED_ON()
{
	GPIO_WriteBit(GPIOH, GPIO_Pin_10, Bit_RESET);
}

void LED_RED_OFF()
{
	GPIO_WriteBit(GPIOH, GPIO_Pin_10, Bit_SET);
}

void LED_RED_Toggle()
{
	GPIO_ToggleBits(GPIOH, GPIO_Pin_10);
}
	

void LED_GREEN_ON()
{
	GPIO_WriteBit(GPIOH, GPIO_Pin_11, Bit_RESET);
}

void LED_GREEN_OFF()
{
	GPIO_WriteBit(GPIOH, GPIO_Pin_11, Bit_SET);
}

void LED_GREEN_Toggle()
{
	GPIO_ToggleBits(GPIOH, GPIO_Pin_11);
}


void LED_BLUE_ON()
{
	GPIO_WriteBit(GPIOH, GPIO_Pin_12, Bit_RESET);
}

void LED_BLUE_OFF()
{
	GPIO_WriteBit(GPIOH, GPIO_Pin_12, Bit_SET);
}

void LED_BLUE_Toggle()
{
	GPIO_ToggleBits(GPIOH, GPIO_Pin_12);
}
