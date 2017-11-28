#include "interface_conf/tgui_conf.h"

//id 数值 设置其实ID
volatile uint16_t win_id = 0;

volatile uint16_t TouchX_pre = 65535;
volatile uint16_t TouchY_pre = 65535;
volatile uint16_t TouchX = 65535;
volatile uint16_t TouchY = 65535;
volatile uint8_t TouchUp = 0;//检查按键是否释放

void GUIDma2d(uint16_t x ,uint16_t y,uint16_t w,uint16_t h,
	uint32_t textColor,uint32_t backColor)
{
	//LCD_SetColors(textColor,backColor);
	//LCD_DrawFullRect(x,y,w,h);
	DMA2D_InitTypeDef      DMA2D_InitStruct;

	uint32_t  Xaddress = 0;
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0;

	Red_Value = (0xF800 & textColor) >> 11;
	Blue_Value = 0x001F & textColor;
	Green_Value = (0x07E0 & textColor) >> 5;

	Xaddress = (uint32_t)GUI_BUFADDR + 2*(LCD_PIXEL_WIDTH*y + x);

	/* configure DMA2D */
	DMA2D_DeInit();
	DMA2D_InitStruct.DMA2D_Mode = DMA2D_R2M;
	DMA2D_InitStruct.DMA2D_CMode = DMA2D_RGB565;
	DMA2D_InitStruct.DMA2D_OutputGreen = Green_Value;
	DMA2D_InitStruct.DMA2D_OutputBlue = Blue_Value;
	DMA2D_InitStruct.DMA2D_OutputRed = Red_Value;
	DMA2D_InitStruct.DMA2D_OutputAlpha = 0x0F;
	DMA2D_InitStruct.DMA2D_OutputMemoryAdd = Xaddress;
	DMA2D_InitStruct.DMA2D_OutputOffset = (LCD_PIXEL_WIDTH - w);
	DMA2D_InitStruct.DMA2D_NumberOfLine = h;
	DMA2D_InitStruct.DMA2D_PixelPerLine = w;
	DMA2D_Init(&DMA2D_InitStruct);

	/* Start Transfer */
	DMA2D_StartTransfer();

	/* Wait for CTC Flag activation */
	while(DMA2D_GetFlagStatus(DMA2D_FLAG_TC) == RESET)
	{
	}
}

void GUIPutPixel(uint16_t xpos,uint16_t ypos)
{//提供一个绘画一个点的驱动
	PutPixel(xpos,ypos);
}

void GUISetPoint(uint16_t x,uint16_t y)
{
	TouchX = x;
	TouchY = y;
}

void GUIGetPoint(uint16_t* x,uint16_t* y)
{
	*x = TouchX;
	*y = TouchY;
}

void GUIGetPrePoint(uint16_t* x,uint16_t* y)
{
	*x = TouchX_pre;
	*y = TouchY_pre;
}

void GUITouchDown(uint16_t pre_x,uint16_t pre_y,uint16_t x,uint16_t y)
{
	TouchX_pre = pre_x;
	TouchY_pre = pre_y;
	TouchX = x;
	TouchY = y;
	TouchUp = 0;
}

void GUITouchUp(int16_t xid,int16_t yid)
{
	TouchUp = 1 ;
}


//暂时是单点触控
uint8_t getTouchUP()
{
	return TouchUp;
}



