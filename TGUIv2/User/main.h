#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef __cplusplus
extern "C"  {
#endif


#include <string.h>
#include <stdlib.h>
#include "includes_all.h"
//#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "DelayTemp/DelayTemp.h"
#include "LED/LEDConfig.h"
#include "USART/USARTConfig.h"
#include "FLASH/FLASHConfig.h"
#include "SDRAM/SDRAMConfig.h"
#include "LCD/LCDConfig.h"
#include "TOUCH/gt9xx.h"
#include "TOUCH/palette.h"
#include "FATFS/ff.h"


//Test
#include "Test/FsTest.h"
#include "Test/SDRAMTest.h"
#include "Test/LCDTest.h"
#include "Test/LCDPalette.h"
	

#ifdef __cplusplus
}
#endif
#include "createWin.hpp"



#endif // !_MAIN_H_

