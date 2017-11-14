#ifndef _USARTCONFIG_H_
#define _USARTCONFIG_H_

#include "stm32f4xx.h"
#include <stdio.h>
//#include "stm32f4xx.h"


//USART1_IS_ARRIVAL != 0 mean data arrical
#define USART1_IS_ARRIVAL USART_GetITStatus(USART1,USART_IT_RXNE)

extern int fputc(int ch, FILE *f);
extern int fgetc(FILE *f);

extern void USART1Config(void);
static void USART1_NVICConfig(void);

extern void USART1_TX(int*buf, int bufnum);
extern int USART1_RX(void);

extern void USART1_TXByte(uint8_t ch);
extern void USART1_TXString(char *str);
extern void USART1_TXHalfWord(uint16_t ch);

extern void USART_SendByte(USART_TypeDef * pUSARTx, uint8_t ch);
extern void USART_SendString(USART_TypeDef * pUSARTx, char *str);
extern void USART_SendHalfWord(USART_TypeDef * pUSARTx, uint16_t ch);


#endif // !_USARTCONFIG_H_

