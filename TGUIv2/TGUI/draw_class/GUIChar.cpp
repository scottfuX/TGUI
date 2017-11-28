#include "drawingClass.h"


GUIChar::GUIChar(uint16_t x1,uint16_t y1,sFONT* font,uint32_t textColor,uint32_t backColor,GUIList<GUIArea> * tempList)
	:GUIShape(backColor,tempList)
{
	this->textColor = textColor;
	this->charX = x1;
	this->charY = y1;
	this->font = font;
}

GUIChar::~GUIChar()
{

}


void GUIChar::displayChar(uint8_t Ascii)
{
	Ascii -= 32;
	if(getInvalidList() && getInvalidList()->getNum())//有覆盖区
	{
		getInvalidList()->resetCurrNode(); //重制当前下标
		rectCut(charX,charY,charX+font->Width,charY+font->Height,
		&font->table[Ascii * font->Height]);//递归
	}
	else
	{
		drawChar(&font->table[Ascii * font->Height]);
	}
}


void GUIChar::drawChar(const uint16_t *c)
{
	uint32_t index = 0, counter = 0, xpos =0;
	uint32_t  Xaddress = 0;
	uint16_t line = charY;
	uint16_t col = charX;
 xpos = line*GUI_WIDTH*GUI_PIXELSIZE;
 Xaddress += col;

 for(index = 0; index < font->Height; index++)
 {
	 for(counter = 0; counter <font->Width; counter++)
	 {
	 //(0x80 << ((font->Width / 12 ) * 8 ) ) >> counter)获取细节上的点
		 if(((font->Width <= 12) && ((c[index] & ((0x80 << ((font->Width / 12 ) * 8 ) ) >> counter)) == 0x00))||
			 ((font->Width > 12 ) && ((c[index] & (0x1 << counter)) == 0x00)))
		 {
			 if(getIsFull())//有无背景
			 {
				 /* Write data value to all SDRAM memory */
				*(__IO uint16_t*) ((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos) = (0x00FFFF &getBackColor());
#if (GUI_PIXELSIZE-2)
				*(__IO uint8_t*)((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos+2) = (0xFF0000 & getBackColor()) >> 16; //R
#endif
			 }
		 }
		 else
		 {
				 /* Write data value to all SDRAM memory */
				*(__IO uint16_t*) ((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos) = (0x00FFFF &getTextColor());
#if (GUI_PIXELSIZE-2)
			 *(__IO uint8_t*)((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos+2) = (0xFF0000 & getTextColor()) >> 16; //R
#endif		 
		 }
		 Xaddress++;
	 }
		 Xaddress += (GUI_WIDTH - font->Width);
	}
}


void GUIChar::drawChar(uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2, const uint16_t *c)
{
	 uint32_t index = 0, counter = 0, xpos =0;
	 uint32_t  Xaddress = 0;
	 uint16_t line = charY;
	 uint16_t col = charX;
	 xpos = (line+y1)*GUI_WIDTH*GUI_PIXELSIZE;
	 Xaddress += col+x1;

	 for(index = y1; index < y2; index++)
	 {

		 for(counter = x1; counter < x2; counter++)
		 {
				//(0x80 << ((font->Width / 12 ) * 8 ) ) >> counter)获取细节上的点
			 if(((font->Width <= 12) && ((c[index] & ((0x80 << ((font->Width / 12 ) * 8 ) ) >> counter)) == 0x00))||
				 ((font->Width > 12 ) && ((c[index] & (0x1 << counter)) == 0x00)))
			 {
					if(getIsFull())
				 {
					 /* Write data value to all SDRAM memory */
					*(__IO uint16_t*) ((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos) = (0x00FFFF &getBackColor());
#if 	(GUI_PIXELSIZE-2)
			*(__IO uint8_t*)((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos+2) = (0xFF0000 & getBackColor()) >> 16; //R
#endif
			 }
		 }
		 else
		 {
				 /* Write data value to all SDRAM memory */
				*(__IO uint16_t*) ((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos) = (0x00FFFF &getTextColor());
#if (GUI_PIXELSIZE-2)
				*(__IO uint8_t*)((uint32_t)GUI_BUFADDR + (GUI_PIXELSIZE*Xaddress) + xpos+2) = (0xFF0000 & getTextColor()) >> 16; //R
#endif		 
			 }
			 Xaddress++;
		 }
		 Xaddress += (GUI_WIDTH - (x2-x1));
	}
}


/*
*|---------------| 5个矩形----进行递归
*|--|---------|--|	
*|	| invlidal|	 |
*|--|---------|--|
*|---------------|	
*/
void GUIChar::rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,const uint16_t *c)
{
	//记下当前的位置节点位置
	GUIArea* inarea = NULL;
	GUINode<GUIArea>* node = NULL;
	while(getInvalidList()->getNextData() != NULL)
	{
		GUIArea* a1 = new GUIArea(x1,y1,x2,y2);
		inarea = rectIntersect(a1,getInvalidList()->getCurrData());
		delete a1;
		if(inarea != NULL)//有交界区
		{
			node = getInvalidList()->getCurrNode();
			break;
		}
	}
	//遍历链表，出现交界就进入矩形切割，若为出现继续遍历，最后还是未出现，说明没有交界，全部画出
	if(inarea != NULL)
	{
		uint16_t xt1,yt1,xt2,yt2;
		//绘画上面部分的区域
		xt1 = x1;
		yt1 = y1;
		xt2 = x2;
		yt2 = inarea->getY1();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,c);
		}
		//绘画左边部分的区域
		
		xt1 = x1;
		yt1 = inarea->getY1();
		xt2 = inarea->getX1();
		yt2 = inarea->getY2();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,c);
		}
		//绘画右边部分的区域
		xt1 = inarea->getX2();
		yt1 = inarea->getY1();
		xt2 = x2;
		yt2 = inarea->getY2();
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,c);
		}
		//绘画下面部分的区域
		xt1 = x1;
		yt1 = inarea->getY2();
		xt2 = x2;
		yt2 = y2;
		if(xt2 - xt1 != 0 && yt2 - yt1 != 0)
		{
			//设置当前位置
			getInvalidList()->setCurrNode(node);
			//遍历无效区链表 进行
			rectCut(xt1,yt1,xt2,yt2,c);
		}
		delete inarea;
	}
	else//没有就直接画出来
	{
		drawChar(x1-charX,y1-charY,x2-charX,y2-charY,c);
	}
}
