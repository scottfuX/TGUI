#include "stm32f4xx_it.h"
/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    06-March-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup FMC_SDRAM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}
	
	
//在 portable中port.c 与这些重复  这里需要注释
//SVC_Handler、PendSV_Handler、SysTick_Handler
/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                         */
/******************************************************************************/

/**
  * @}
  */ 

/**
  * @}
  */ 
	


void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(GTP_INT_EXTI_LINE) != RESET) //确保是否产生了EXTI Line中断
	{
		LED_GREEN_Toggle();
		GTP_TouchProcess(); //鑾峰彇point鐐圭殑鍑芥暟		
		EXTI_ClearITPendingBit(GTP_INT_EXTI_LINE);     //清除中断标志位
	}
//	if (KEY2Read != 0)
//	{
//		LED_BLUE_Toggle();
//	}
//	//Note clear
//	EXTI_ClearITPendingBit(EXTI_Line13);
	
}

int USART1BufCount = 0;

void USART1_IRQHandler()
{
	//主要用于接收数据
	//单缓冲--双缓冲
	if (USART1_IS_ARRIVAL != 0)
	{
		USART1_Buf[USART1BufCount++] = USART1_RX();
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		if (USART1BufCount == BufMaxNum)
		{
			USART1BufCount = 0;
			USART1_TX(USART1_Buf, BufMaxNum);
			for (int i = 0; i < BufMaxNum; i++)
			{
				printf(" %d--%c \n",i ,USART1_Buf[i]);
			}
		}
	}	
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/




//void NMI_Handler()                    __attribute__((weak, alias("Default_Handler")));
//void HardFault_Handler()              __attribute__((weak, alias("Default_Handler")));
//void MemManage_Handler()              __attribute__((weak, alias("Default_Handler")));
//void BusFault_Handler()               __attribute__((weak, alias("Default_Handler")));
//void UsageFault_Handler()             __attribute__((weak, alias("Default_Handler")));
//void SVC_Handler()                    __attribute__((weak, alias("Default_Handler")));
//void DebugMon_Handler()               __attribute__((weak, alias("Default_Handler")));
//void PendSV_Handler()                 __attribute__((weak, alias("Default_Handler")));
/*
extern void xPortSysTickHandler(void);
void SysTick_Handler()    
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//??????
    {
        xPortSysTickHandler();  
    }
	TimeCount--;
}

*/


//void PVD_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void TAMP_STAMP_IRQHandler()          __attribute__((weak, alias("Default_Handler")));
//void RTC_WKUP_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void FLASH_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void RCC_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));


//void EXTI1_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void EXTI2_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void EXTI3_IRQHandler()               __attribute__((weak, alias("Default_Handler")));





//void DMA1_Stream0_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream1_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream2_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream3_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream4_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream5_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream6_IRQHandler()        __attribute__((weak, alias("Default_Handler")));

//void CAN1_TX_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void CAN1_RX0_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN1_RX1_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN1_SCE_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void EXTI9_5_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void TIM1_BRK_TIM9_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void TIM1_UP_TIM10_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void TIM1_TRG_COM_TIM11_IRQHandler()  __attribute__((weak, alias("Default_Handler")));
//void TIM1_CC_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void TIM2_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void TIM3_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void TIM4_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void I2C1_EV_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C1_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C2_EV_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C2_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void SPI1_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI2_IRQHandler()                __attribute__((weak, alias("Default_Handler")));

		
//void USART2_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void USART3_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void EXTI15_10_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
//void RTC_Alarm_IRQHandler()           __attribute__((weak, alias("Default_Handler")));
//void OTG_FS_WKUP_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
//void TIM8_BRK_TIM12_IRQHandler()      __attribute__((weak, alias("Default_Handler")));
//void TIM8_UP_TIM13_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void TIM8_TRG_COM_TIM14_IRQHandler()  __attribute__((weak, alias("Default_Handler")));
//void TIM8_CC_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void DMA1_Stream7_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void FMC_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void SDIO_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void TIM5_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI3_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void UART4_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void UART5_IRQHandler()               __attribute__((weak, alias("Default_Handler")));


//void TIM7_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream0_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream1_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream2_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream3_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream4_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void ETH_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void ETH_WKUP_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN2_TX_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void CAN2_RX0_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN2_RX1_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void CAN2_SCE_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void OTG_FS_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream5_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream6_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void DMA2_Stream7_IRQHandler()        __attribute__((weak, alias("Default_Handler")));
//void USART6_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void I2C3_EV_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void I2C3_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_EP1_OUT_IRQHandler()      __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_EP1_IN_IRQHandler()       __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_WKUP_IRQHandler()         __attribute__((weak, alias("Default_Handler")));
//void OTG_HS_IRQHandler()              __attribute__((weak, alias("Default_Handler")));
//void DCMI_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void HASH_RNG_IRQHandler()            __attribute__((weak, alias("Default_Handler")));
//void FPU_IRQHandler()                 __attribute__((weak, alias("Default_Handler")));
//void UART7_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void UART8_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
//void SPI4_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI5_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SPI6_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void SAI1_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void LTDC_IRQHandler()                __attribute__((weak, alias("Default_Handler")));
//void LTDC_ER_IRQHandler()             __attribute__((weak, alias("Default_Handler")));
//void DMA2D_IRQHandler()               __attribute__((weak, alias("Default_Handler")));
