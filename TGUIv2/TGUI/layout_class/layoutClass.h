#ifndef _LAYOUTCLASS_H_
#define _LAYOUTCLASS_H_

#include "winClass.h"

#ifdef __cplusplus
extern "C"  {
#endif

#include "interface_conf/tgui_conf.h"
#include "includes_all.h"
	
#ifdef __cplusplus
}
#endif

//布局窗口类 -- 方便控件布局
class layoutWin
{
public:
	layoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围
		uint16_t Y,
		uint16_t Width,
		uint16_t High
	);
	virtual ~layoutWin();

	rootWin* getBackWin(){return backWin;}
	uint16_t getLayoutX(){return layoutX;}
	uint16_t getLayoutY(){return layoutY;}
	uint16_t getLayoutWidth(){return layoutWidth;}
	uint16_t getLayoutHigh(){return layoutHigh;}
	
	uint16_t getHorizGap(){return horizGap;}
	uint16_t getVertGap(){return vertGap;}
	void setHorizGap(uint16_t horizGap){this->horizGap = horizGap;}
	void setVertGap(uint16_t vertGap){this->vertGap = vertGap;}
	virtual void addWin(rootWin* rw) = 0;
private:
	rootWin* backWin;//要被布局的对象
	uint16_t layoutX;//所要布局的范围
	uint16_t layoutY;
	uint16_t layoutWidth;
	uint16_t layoutHigh;

	uint16_t horizGap; //horizontal间隙
	uint16_t vertGap; //vertical间隙
};

//流式布局
class flowLayoutWin:public layoutWin
{
public:
	flowLayoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围
		uint16_t Y,
		uint16_t Width,
		uint16_t High,
		uint16_t Hgap,
		uint16_t Vgap
	);
	virtual ~flowLayoutWin();

	virtual void addWin(rootWin* rw);
private:
	uint16_t residualW;//剩余宽度
	uint16_t residualH;//剩余高度
	uint16_t maxH; //一行中最长的高

};

//边界布局
class borderLayoutWin:public layoutWin
{
public:
	borderLayoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围
		uint16_t Y,
		uint16_t Width,
		uint16_t High
	);
	virtual ~borderLayoutWin();
	virtual void addWin(rootWin* rw);
	void addWin(rootWin* rw,uint16_t seat);
	void setBorderSize(uint16_t northH,uint16_t southH,uint16_t westW,uint16_t eastW);
private:	
	uint16_t northH;
	uint16_t southH;
	uint16_t westW;
	uint16_t eastW;
	uint8_t layoutStat;//布局状态 那几个已经布局了

};

//网格布局
class gridLayoutWin:public layoutWin
{
public:
	gridLayoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围相对位移
		uint16_t Y,
		uint16_t Width,
		uint16_t High,
		uint8_t  row,
		uint8_t  column
	);
	virtual ~gridLayoutWin();
	virtual void addWin(rootWin* rw);
	void generateGridWH(uint16_t horizGap,uint16_t vertGap);
private:
	uint8_t row; //行
	uint8_t column; //列
	uint8_t currSeat;
	uint16_t gridW;
	uint16_t gridH;
};





#endif //_LAYOUTCLASS_H_

