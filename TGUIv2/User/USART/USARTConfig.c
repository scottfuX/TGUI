#include "USART/USARTConfig.h"


void USART1Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	
	/* TX PA9 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 /* RX PA10 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*  连接 PXx 到 USARTx__Rx*/
	/*  连接 PXx 到 USARTx__Tx*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART1, &USART_InitStructure); 
	
	/* 嵌套向量中断控制器NVIC配置 */
	USART1_NVICConfig();
	/* 使能串口 */
	USART_Cmd(USART1, ENABLE);
	
    /* Enable the EVAL_COM1 Receive interrupt: this interrupt is generated when the 
       EVAL_COM1 receive data register is not empty */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

void USART1_NVICConfig()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}




/*----------------------------------*/
void USART_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx, ch);
	/* 等待发送数据寄存器为空 当 TDR 寄存器的内容已传输到移位寄存器时，该位由硬件置 1*/
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == 0);
}

void USART_SendString(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k = 0;
	do 
	{
		USART_SendByte(pUSARTx, *(str + k));
		k++;
	} while (*(str + k) != '\0');
  
	/* 等待发送完成 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

//发16位
void USART_SendHalfWord(USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	/* 取出高八位 */
	temp_h = (ch & 0XFF00) >> 8;
	/* 取出低八位 */
	temp_l = ch & 0XFF;
	/* 发送高八位 */
	USART_SendData(pUSARTx, temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	/* 发送低八位 */
	USART_SendData(pUSARTx, temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*----------------------------printf-------------------------------*/
//重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
	USART_SendData(USART1, (uint8_t) ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	return (ch);
}

//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}

/*--------------------------------User------------------------------------*/

void USART1_TX(int*buf, int bufnum)
{
	int *q;
	q = buf;
	for (int i = 0; i < bufnum; i++)
	{
		USART_SendByte(USART1, *(q + i));
	}
	
}

int USART1_RX()
{
	/* 等待串口输入数据 当 RDR 移位寄存器的内容已传输到 USART_DR 寄存器时，该位由硬件置 1。*/
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == 0);
	return USART_ReceiveData(USART1);
}

void USART1_TXByte(uint8_t ch)
{
	USART_SendByte(USART1, ch);
}

void USART1_TXString(char *str)
{
	USART_SendString(USART1, str);
}

void USART1_TXHalfWord(uint16_t ch)
{
	USART_SendHalfWord(USART1, ch);
}

