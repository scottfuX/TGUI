#include "drawingClass.h"

GUILine::GUILine(
		uint16_t x1,
		uint16_t y1,
		uint16_t x2,
		uint16_t y2,
		uint32_t color,
		GUIList<GUIArea> * tempList
		):GUIShape(color,tempList)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}
	

GUILine::~GUILine()
{

}

void GUILine::draw()
{
	lineDraw(NULL);//未实现 虚区间不绘画的方法
}

void GUILine::drawInArea(GUIArea * tarea)
{
	lineDraw(tarea);
}

void GUILine::lineDrawPixel(uint16_t x,uint16_t y,GUIArea *tarea)
{
	if(tarea != NULL)
	{//区域内画
		if(x >= tarea->getX1() && x <= tarea->getX2() &&
			y >= tarea->getY1() && y <= tarea->getY2())
		{
			putPixel(x, y);
		}
	}
	else
	{
			putPixel(x, y);             /* Draw the current pixel */
	}
}

void GUILine::lineDraw(GUIArea *tarea)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;

	deltax = ABSreduce(x2 , x1);        /* The difference between the x's */
	deltay = ABSreduce(y2 , y1);        /* The difference between the y's */
	x = x1;                       /* Start x off at the first pixel */
	y = y1;                       /* Start y off at the first pixel */

	if (x2 >= x1)                 /* The x-values are increasing */
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else                          /* The x-values are decreasing */
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)                 /* The y-values are increasing */
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else                          /* The y-values are decreasing */
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)         /* There is at least one x-value for every y-value */
	{
		xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
		yinc2 = 0;                  /* Don't change the y for every iteration */
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         /* There are more x-values than y-values */
	}
	else                          /* There is at least one y-value for every x-value */
	{
		xinc2 = 0;                  /* Don't change the x for every iteration */
		yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         /* There are more y-values than x-values */
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		lineDrawPixel(x, y,tarea);             /* Draw the current pixel */
		num += numadd;              /* Increase the numerator by the top of the fraction */
		if (num >= den)             /* Check if numerator >= denominator */
		{
			num -= den;               /* Calculate the new numerator value */
			x += xinc1;               /* Change the x as appropriate */
			y += yinc1;               /* Change the y as appropriate */
		}
		x += xinc2;                 /* Change the x as appropriate */
		y += yinc2;                 /* Change the y as appropriate */
	}
}

uint16_t GUILine::ABSreduce(uint16_t x,uint16_t y)
{
	return x > y ? x-y : y-x;
}
