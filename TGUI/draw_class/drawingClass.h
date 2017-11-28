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
	GUIShape(uint32_t color,GUIList<GUIArea> * tempList);
	virtual ~GUIShape();

	virtual void draw() = 0;
	virtual void drawInArea(GUIArea * tarea)=0;		//绘画无效区域
	
	bool getIsFull(){return isFull;}
	void setIsFull(bool isfull){this->isFull = isfull;}
	
	uint32_t getColor(){return color;}

	void setColor(uint32_t color){this->color = color;}
	GUIList<GUIArea> * getInvalidList(){return invalidList;}
	void drawShape(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint32_t color);
	void putPixel(uint16_t x,uint16_t y);
	
	GUIArea* rectIntersect(GUIArea* area1,GUIArea* area2);
	void rectIntersect(GUIArea* area1,GUIArea* area2,GUIArea* out);

private:
	uint32_t color;
	GUIList<GUIArea> *invalidList;
	bool isFull;

	uint16_t max(uint16_t n,uint16_t m);
	uint16_t min(uint16_t n,uint16_t m);
};

//字
class GUIChar:public GUIShape
{
public:
	GUIChar(uint16_t x,uint16_t y,sFONT* font,uint32_t textColor
			,uint32_t backColor,GUIList<GUIArea> * tempList);
	virtual~GUIChar();

	virtual void draw(){}; //--------------------------------还未实现---到时需要都修改
	virtual void drawInArea(GUIArea * tarea){};		//绘画无效区域
	sFONT* getFont(){return font;}
	uint32_t getBackColor(){return getColor();}
	uint32_t getTextColor(){return textColor;}
	void setFont(sFONT* font){this->font = font;}
	void setCharXY(uint16_t x,uint16_t y){charX = x;charY = y;}
	void displayChar(uint8_t Ascii);
private:
	uint16_t charX;
	uint16_t charY;
	uint32_t textColor;
	sFONT* font;
	void drawChar(const uint16_t *c);
	void drawChar(uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2, const uint16_t *c);
	void rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,const uint16_t *c);
};

//线段
class GUILine:public GUIShape
{
public:
	GUILine(
		uint16_t x1,
		uint16_t y1,
		uint16_t x2,
		uint16_t y2,
		uint32_t color,
		GUIList<GUIArea> * tempList
	);
	virtual~GUILine();
	virtual void draw();
	virtual void drawInArea(GUIArea * tarea);

	void setX1(uint16_t x1){this->x1 = x1;}
	void setY1(uint16_t y1){this->y1 = y1;}
	void setX2(uint16_t x2){this->x2 = x2;}
	void setY2(uint16_t y2){this->y2 = y2;}

private:
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;

	uint16_t ABSreduce(uint16_t x,uint16_t y);
	void lineDrawPixel(uint16_t x,uint16_t y,GUIArea *tarea);
	void lineDraw(GUIArea *tarea);
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
		uint32_t color,
		GUIList<GUIArea> * tempList
	);
	virtual~GUIRectangle();
	virtual void draw();
	virtual void drawInArea(GUIArea * tarea);
	void setX(uint16_t x){this->x1 = x;}
	void setY(uint16_t y){this->y1 = y;}
	void setW(uint16_t w){this->x2 = x1+w;}
	void setH(uint16_t h){this->y2 = y1+h;}

private:
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;

	void rectCut(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
};

//圆形
class GUICircle:public GUIShape
{
public:
	GUICircle(
		uint16_t x,
		uint16_t y,
		uint16_t r,
		uint32_t color,
		GUIList<GUIArea> * tempList
	);
	virtual~GUICircle();
	virtual void draw();
	virtual void drawInArea(GUIArea * tarea);
	void setX(uint16_t x){this->x = x;}
	void setY(uint16_t y){this->y = y;}
	void setR(uint16_t r){this->r = r;}

private:
	uint16_t x;
	uint16_t y;
	uint16_t r;

	void drawCircle();
	void drawFullCircle();
	void drawFullCirInvalid(GUIArea* area);
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
		uint32_t backColor,
		GUIList<GUIArea> * tempList
	);
	virtual ~GUITriangle();
	virtual void draw();
	virtual void drawInArea(GUIArea * tarea);

private:
		uint16_t x1;
		uint16_t y1;
		uint16_t x2;
		uint16_t y2;
		uint16_t x3;
		uint16_t y3;
};



#endif //! _DRAWCLASS_H_ 
