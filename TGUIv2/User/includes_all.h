#ifndef __INCLUDESALL_H__
#define __INCLUDESALL_H__


/*------------------------------#include----------------------------------*/
#include "stm32f4xx.h"
//>>>>>>>>>>-FreeRTOS->>>>>>>>>>>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "portable.h"
#include "FreeRTOSConfig.h"

/*------------------------------#define---------------------------------- */
//链接外部SDRAM
#define __EXRAM   __attribute__ ((section ("EXRAM")))
//例如:uint8_t a[40] __EXRAM={0};



#endif //!__INCLUDESALL_H__
