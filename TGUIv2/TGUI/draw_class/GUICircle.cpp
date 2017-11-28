#include "drawingClass.h"


GUICircle::GUICircle(
		uint16_t x,
		uint16_t y,
		uint16_t r,
		uint32_t color,
		GUIList<GUIArea> * tempList
		):GUIShape(color,tempList)
	{
		this->x = x;
		this->y = y;
		this->r = r;
	}

	
GUICircle::~GUICircle()
{

}

void GUICircle::draw()
{
	if(getIsFull())
	{
		drawFullCircle();
	}
	else
	{
		drawCircle();
	}
}

void GUICircle::drawInArea(GUIArea * tarea)
{
	if(getIsFull())
	{
		drawFullCirInvalid(tarea);
	}
	else
	{//暂时无法做到
		drawCircle();
	}
}


void GUICircle::drawCircle()
{
	int xt = -r, yt = 0, err = 2-2*r, e2;
	do {
		*(__IO uint16_t*) (GUI_BUFADDR + (GUI_PIXELSIZE*((x-xt) + GUI_WIDTH*(y+yt))))= (0x00FFFF & getColor());       //GB
		*(__IO uint16_t*) (GUI_BUFADDR + (GUI_PIXELSIZE*((x+xt) + GUI_WIDTH*(y+yt)))) = (0x00FFFF & getColor());      //GB
		*(__IO uint16_t*) (GUI_BUFADDR + (GUI_PIXELSIZE*((x+xt) + GUI_WIDTH*(y-yt)))) = (0x00FFFF & getColor());      //GB
		*(__IO uint16_t*) (GUI_BUFADDR + (GUI_PIXELSIZE*((x-xt) + GUI_WIDTH*(y-yt)))) = (0x00FFFF & getColor());      //GB

#if (GUI_PIXELSIZE-2)       
		*(__IO uint8_t*)(GUI_BUFADDR + (GUI_PIXELSIZE*((x-xt) + GUI_WIDTH*(y+yt))+2))= (0xFF0000 & getColor()) >> 16; //R
		*(__IO uint8_t*)(GUI_BUFADDR + (GUI_PIXELSIZE*((x+xt) + GUI_WIDTH*(y+yt))+2))= (0xFF0000 & getColor()) >> 16; //R
		*(__IO uint8_t*)(GUI_BUFADDR + (GUI_PIXELSIZE*((x+xt) + GUI_WIDTH*(y-yt))+2))= (0xFF0000 & getColor()) >> 16; //R
		*(__IO uint8_t*)(GUI_BUFADDR + (GUI_PIXELSIZE*((x-xt) + GUI_WIDTH*(y-yt))+2))= (0xFF0000 & getColor()) >> 16; //R
#endif      
		e2 = err;
		if (e2 <= yt) 
		{
			err += ++yt*2+1;
			if (-xt == yt && e2 <= xt) e2 = 0;
		}
		if (e2 > xt) err += ++xt*2+1;
	}
	while (xt <= 0);
}


void GUICircle::drawFullCircle()
{
	int32_t  D;    /* Decision Variable */
	uint32_t  CurX;	/* Current X Value */
	uint32_t  CurY;	/* Current Y Value */
	uint16_t	Xpos = x;
	uint16_t 	Ypos = y;
	D = 3 - (r << 1);

	CurX = 0;
	CurY = r;

	GUIRectangle rect(0,0,100,100,getColor(),getInvalidList());
	while (CurX <= CurY)
	{
		if(CurY > 0)
		{//有问题
			rect.setX(Xpos - CurX);
			rect.setY(Ypos - CurY);
			rect.setW(1);
			rect.setH(2*CurY);
			rect.draw();
			rect.setX(Xpos + CurX);
			rect.setY(Ypos - CurY);
			rect.setW(1);
			rect.setH(2*CurY);
			rect.draw();
		}
		if(CurX > 0)
		{
			rect.setX(Xpos - CurY);
			rect.setY(Ypos - CurX);
			rect.setW(1);
			rect.setH(2*CurX);
			rect.draw();
			rect.setX(Xpos + CurY);
			rect.setY(Ypos - CurX);
			rect.setW(1);
			rect.setH(2*CurX);
			rect.draw();
		}
		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}

void GUICircle::drawFullCirInvalid(GUIArea* area)
{
	int32_t  D;    /* Decision Variable */
	uint32_t  CurX;/* Current X Value */
	uint32_t  CurY;/* Current Y Value */
	uint16_t	Xpos = x;
	uint16_t 	Ypos = y;
	
	D = 3 - (r << 1);
	CurX = 0;
	CurY = r;
	GUIRectangle rect(0,0,100,100,getColor(),getInvalidList());
	while (CurX <= CurY)
	{
		if(CurY > 0)
		{
			rect.setX(Xpos - CurX);
			rect.setY(Ypos - CurY);
			rect.setW(1);
			rect.setH(2*CurY);
			//rect.drawInArea(area);//-------------------//有问题
			rect.draw();
			rect.setX(Xpos + CurX);
			rect.setY(Ypos - CurY);
			rect.setW(1);
			rect.setH(2*CurY);
			//rect.drawInArea(area);
			rect.draw();
		}
		if(CurX > 0)
		{
			rect.setX(Xpos - CurY);
			rect.setY(Ypos - CurX);
			rect.setW(1);
			rect.setH(2*CurX);
			//rect.drawInArea(area);
			rect.draw();
			rect.setX(Xpos + CurY);
			rect.setY(Ypos - CurX);
			rect.setW(1);
			rect.setH(2*CurX);
			//rect.drawInArea(area);
			rect.draw();
		}
		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
	//drawCircle();  
}

