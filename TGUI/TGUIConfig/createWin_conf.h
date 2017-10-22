#ifndef __CREATEWIN_CONFIG_H_
#define __CREATEWIN_CONFIG_H_



#ifdef __cplusplus
extern "C"  {
#endif
	
#include "TGUIConfig/tgui_drv_conf.h"
	
#ifdef __cplusplus
}
#endif
#include "winClass.h"
extern uint16_t TouchX;
extern uint16_t TouchY;
extern uint8_t TouchUp;



void GUI_Run();




#endif //!__CREATEWIN_CONFIG_H_
