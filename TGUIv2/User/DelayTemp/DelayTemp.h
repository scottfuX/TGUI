#ifndef _DELAY_H_
#define _DELAY_H_

//#include "stm32f4xx.h"
#include "includes_all.h"

/*
void Delay10MSConfig(void);
void DelayMSConfig(void);
void Delay10USConfig(void);
void DelayUSConfig(void);
// Systick—”≥Ÿ –Ë“™œ»≈‰÷√ ±÷”
void DelayHandler(int num);
*/

//∆’Õ®—”≥Ÿ —≠ª∑—”≥Ÿ
void Delay(__IO uint32_t nCount);

#endif //!_DELAY_H_

