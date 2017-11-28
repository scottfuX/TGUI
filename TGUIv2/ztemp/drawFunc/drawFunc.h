#ifndef _DRAWFUNC_H_
#define _DRAWFUNC_H_


#include "winClass.h"
//#include "draw_class/drawingClass.h"
#include "GUIList.h"

#ifdef __cplusplus
extern "C"  {
#endif
	
#include "interface_conf/tgui_conf.h"
#include "DelayTemp/DelayTemp.h"
	
#ifdef __cplusplus
}
#endif

void drawRect(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,controlWin* cw,uint32_t textColor,uint32_t backColor,bool isFull);

#endif //!_DRAWFUNC_H_

