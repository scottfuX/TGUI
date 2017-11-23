#ifndef _DRAWCLASS_H_
#define _DRAWCLASS_H_ 

#include "GUIList.h"

#ifdef __cplusplus
extern "C"  {
#endif

#include "interface_conf/tgui_conf.h"
#include "includes_all.h"
	
extern uint16_t win_id;
extern uint8_t win_buffer[];	
extern uint8_t LCD_BUFADDR[];
#ifdef __cplusplus
}
#endif

//区域矩形
class GUIArea
{
public:
	GUIArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	~GUIArea(){};
	uint16_t getX1(){return x1;}
	uint16_t getY1(){return y1;}
	uint16_t getX2(){return x2;}
	uint16_t getY2(){return y2;}
	void setX1(uint16_t x1){this->x1 = x1;}
	void setX2(uint16_t x2){this->x2 = x2;}
	void setY1(uint16_t y1){this->y1 = y1;}
	void setY2(uint16_t y2){this->y2 = y2;}
	
private:
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
};


//图形基类
class GUIShape
{
public:
	GUIShape(uint32_t textColor,uint32_t backColor)
	{
		this->textColor = textColor;
		this->backColor = backColor;
		this->invalidList = NULL;
	}
	virtual ~GUIShape(){if(invalidList) invalidList->destroyList();}
	
	uint32_t getTextColor(){return textColor;}
	uint32_t getBackColor(){return backColor;}
	void setTextColor(uint32_t textColor){this->textColor = textColor;}
	void setBackColor(uint32_t backColor){this->backColor = backColor;}

	virtual void draw() = 0;
	virtual void drawFull() = 0;

	void drawInArea();		//绘画无效区域
	
	void addInvalidArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
	{
		if(invalidList == NULL)
		{
				invalidList = new GUIList<GUIArea>();
		}
		GUIArea * tarea =  new GUIArea(x1,y1,x2,y2);					//创建无效区
		invalidList->addNode(tarea);
	}
	
	GUIList<GUIArea>* getInvalidList()
	{return invalidList; }

private:
	uint32_t textColor;
	uint32_t backColor;
  GUIList<GUIArea>* invalidList;
};

//矩形
class GUIRectangle:public GUIShape
{
public:
	GUIRectangle(
		uint16_t x,
		uint16_t y,
		uint16_t w,
		uint16_t h,
		uint32_t textColor,
		uint32_t backColor
	);
	virtual~GUIRectangle();
	virtual void drawFull();
	virtual void draw();
	void putPixel(uint16_t x,uint16_t y);

private:
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;

void rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
GUIArea* rectIntersect(GUIArea* area1,GUIArea* area2);
uint16_t max(uint16_t n,uint16_t m);
uint16_t min(uint16_t n,uint16_t m);
};

//圆形
class GUICircle:public GUIShape
{
public:
	GUICircle(
		uint16_t x,
		uint16_t y,
		uint16_t r,
		uint32_t textColor,
		uint32_t backColor
	);
	virtual~GUICircle();
virtual void drawFull();
virtual void draw();

private:
	uint16_t x;
	uint16_t y;
	uint16_t r;
};

//三角形
class GUITriangle:public GUIShape
{
public:
	GUITriangle(
		uint16_t x1,
		uint16_t y1,
		uint16_t x2,
		uint16_t y2,
		uint16_t x3,
		uint16_t y3,
		uint32_t textColor,
		uint32_t backColor
	);
virtual ~GUITriangle();
virtual void drawFull();
virtual void draw();

private:
		uint16_t x1;
		uint16_t y1;
		uint16_t x2;
		uint16_t y2;
		uint16_t x3;
		uint16_t y3;
};



#endif //! _DRAWCLASS_H_ 
