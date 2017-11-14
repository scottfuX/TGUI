#ifndef _ST32F4XXIT_H_
#define _ST32F4XXIT_H_

//#include "stm32f4xx.h"
#include "includes_all.h"
#include "LED/LEDConfig.h"
#include "USART/USARTConfig.h"
#include "TOUCH/touch_i2c.h"



extern int TimeCount;
extern int BufMaxNum;
extern int USART1_Buf[];


#if defined ADCTEMP1
extern __IO uint16_t ADC_ConvertedValue;
#endif

void GTP_TouchProcess(void);

#ifdef __cplusplus
 extern "C" {
#endif 


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
 
void USART1_IRQHandler(void);
void EXTI15_10_IRQHandler(void);


#ifdef __cplusplus
}
#endif




#endif // !_INTERRUPTHANDLER_H_


