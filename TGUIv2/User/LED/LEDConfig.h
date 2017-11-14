#ifndef _LEDCONFIG_H_
#define _LEDCONFIG_H_

//#include "stm32f4xx.h"
#include "includes_all.h"

//ºì
#define LED_RED  \
					LED_RED_ON();\
					LED_GREEN_OFF();\
					LED_BLUE_OFF()

//ÂÌ
#define LED_GREEN		\
					LED_RED_OFF();\
					LED_GREEN_ON();\
					LED_BLUE_OFF()

//À¶
#define LED_BLUE	\
					LED_RED_OFF();\
					LED_GREEN_OFF();\
					LED_BLUE_ON()

					
//»Æ(ºì+ÂÌ)					
#define LED_YELLOW	\
					LED_RED_ON();\
					LED_GREEN_ON();\
					LED_BLUE_OFF()
//×Ï(ºì+À¶)
#define LED_PURPLE	\
					LED_RED_ON();\
					LED_GREEN_OFF();\
					LED_BLUE_ON()

//Çà(ÂÌ+À¶)
#define LED_CYAN \
					LED_RED_OFF();\
					LED_GREEN_ON();\
					LED_BLUE_ON()
					
//°×(ºì+ÂÌ+À¶)
#define LED_WHITE	\
					LED_RED_ON();\
					LED_GREEN_ON();\
					LED_BLUE_ON()
					
//ºÚ(È«²¿¹Ø±Õ)
#define LED_RGBOFF	\
					LED_RED_OFF();\
					LED_GREEN_OFF();\
					LED_BLUE_OFF()
					
					

extern void LED_RED_Config(void);
extern void LED_GREEN_Config(void);
extern void LED_BLUE_Config(void);

extern void LED_RED_ON(void);
extern void LED_RED_OFF(void);
extern void LED_RED_Toggle(void);
	
extern void LED_GREEN_ON(void);
extern void LED_GREEN_OFF(void);
extern void LED_GREEN_Toggle(void);

extern void LED_BLUE_ON(void);
extern void LED_BLUE_OFF(void);
extern void LED_BLUE_Toggle(void);




#endif // !_LEDCONFIG_H_

