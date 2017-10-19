#ifndef __TGUI_DRV_CONFIG_H_
#define __TGUI_DRV_CONFIG_H_

#ifdef __cplusplus
extern "C"  {
#endif

#include "includes_all.h"
#include "FreeRTOS.h"
#include "LCD/LCDConfig.h"


typedef  uint8_t uint8;
typedef  uint16_t uint16;
typedef  uint32_t uint32;

//#define RGB_565
//#define RGB_888
//#define RGB_1555
//#define RGB_8888
	
#define MSG_QUENUM		5 //娑堟伅闃熷垪瀛樻斁娑堟伅涓暟
	
#define GUI_COLORMODE		RGB_565	
	
#define GUI_BUFADDR 		LCD_FRAME_BUFFER 
#define GUI_BUFSIZE 		BUFFER_OFFSET
#define GUI_WIDTH			LCD_PIXEL_WIDTH
#define GUI_HIGH			LCD_PIXEL_HEIGHT

	


#define BACK_COLOR RGB888ToRGB565(0xe0e0e0)//window back
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





#ifdef __cplusplus
}
#endif

/*
void	 LCDConfig(void);	
void     LCD_Init(void);
void     LCD_LayerInit(void);
void     LCD_ChipSelect(FunctionalState NewState);
void     LCD_SetLayer(uint32_t Layerx);
void     LCD_SetColors(uint32_t _TextColor, uint32_t _BackColor); 
void     LCD_GetColors(uint32_t *_TextColor, uint32_t *_BackColor);
void     LCD_SetTextColor(uint32_t Color);
void     LCD_SetBackColor(uint32_t Color);
void     LCD_SetTransparency(uint8_t transparency);
void     LCD_ClearLine(uint16_t Line);
void     LCD_Clear(uint32_t Color);
uint32_t LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void     LCD_SetColorKeying(uint32_t RGBValue);
void     LCD_ReSetColorKeying(void);
void     LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint16_t *c);
void     LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii);
void     LCD_SetFont(sFONT *fonts);
sFONT *  LCD_GetFont(void);
void     LCD_DisplayStringLine(uint16_t Line, uint8_t *ptr);
void     LCD_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width);
void     LCD_WindowModeDisable(void);
void     LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction);
void     LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     LCD_DrawEllipse(int Xpos, int Ypos, int Radius, int Radius2);
void     LCD_DrawFullEllipse(int Xpos, int Ypos, int Radius, int Radius2);
void     LCD_DrawMonoPict(const uint32_t *Pict);
void     LCD_WriteBMP(uint32_t BmpAddress);
void     LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     LCD_PolyLine(pPoint Points, uint16_t PointCount);
void     LCD_PolyLineRelative(pPoint Points, uint16_t PointCount);
void     LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount);
void     LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount);
void     LCD_FillPolyLine(pPoint Points, uint16_t PointCount);
void     LCD_Triangle(pPoint Points, uint16_t PointCount);
void     LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);
void     LCD_WriteCommand(uint8_t LCD_Reg);
void     LCD_WriteData(uint8_t value);
void     LCD_PowerOn(void);
void     LCD_DisplayOn(void);
void     LCD_DisplayOff(void);
void     LCD_CtrlLinesWrite(GPIO_TypeDef* GPIOx, uint16_t CtrlPins, BitAction BitVal);
void     PutPixel(int16_t x, int16_t y);


//汉字
void LCD_DispChar_CH ( uint16_t usX, uint16_t usY, uint16_t usChar);
void LCD_DispString_EN_CH( uint16_t usX, uint16_t usY, const uint8_t * pStr );
void LCD_DisplayStringLine_EN_CH(uint16_t Line, uint8_t *ptr);
void LCD_DispString_EN_CH ( uint16_t usX, uint16_t usY, const uint8_t * pStr );


void LCD_DisplayStringLineEx(uint16_t x, 		//字符显示位置x
	uint16_t y, 				//字符显示位置y
	uint16_t Font_width,	//要显示的字体宽度，英文字符在此基础上/2。注意为偶数
	uint16_t Font_Heig,	//要显示的字体高度，注意为偶数
	uint8_t *ptr,					//显示的字符内容
	uint16_t DrawModel);  //是否反色显示
void LCD_DrawChar_Ex(uint16_t Xpos, //字符显示位置x
	uint16_t Ypos, //字符显示位置y
	uint16_t Font_width, //字符宽度
	uint16_t Font_Heig,  //字符高度 
	uint8_t *c,						//字模数据
	uint16_t DrawModel);		//是否反色显示
void LCD_zoomChar(uint16_t in_width,	//原始字符宽度
	uint16_t in_heig,		//原始字符高度
	uint16_t out_width,	//缩放后的字符宽度
	uint16_t out_heig,	//缩放后的字符高度
	uint8_t *in_ptr,	//字库输入指针	注意：1pixel 1bit
	uint8_t *out_ptr, //缩放后的字符输出指针 注意: 1pixel 8bit
	uint8_t en_cn);		//0为英文，1为中文	

*/





#endif //!__TGUI_DRV_CONFIG_H_
