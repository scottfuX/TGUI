/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
  *
*
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) ||defined(__GUNC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

#define configUSE_PREEMPTION			1															//设为 1则采用抢占式调度器, 设为 0则采用协作式调度器。
#define configUSE_IDLE_HOOK				0															//设为1则使能 idle hook，设为0则禁止idle hook。
#define configUSE_TICK_HOOK				0															//设为1则使能 tick hook，设为0则禁止tick hook。
#define configCPU_CLOCK_HZ				( SystemCoreClock )						//设置为 MCU 内核的工作频率，以Hz为单位。配置FreeRTOS的时钟Tick时会用到。180M
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )				//FreeRTOS的时钟Tick的频率，也就是FreeRTOS用到的定时中断的产生频率。这个频率越高则定时的精度越高，但是由此带来的开销也越大。FreeRTOS 自带的Demo 程序中将TickRate 设为了1000Hz只是用来测试内核的性能的。实际的应用程序应该根据需要改为较小的数值。
#define configMAX_PRIORITIES			( 5 )													//程序中可以使用的最大优先级。FreeRTOS 会为每个优先级建立一个链表，因此没多一个优先级都会增加些RAM 的开销。所以，要根据程序中需要多少种不同的优先级来设置这个参数。
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 130 )	//任务堆栈的最小大小，FreeRTOS根据这个参数来给idle task 分配堆栈空间。这个值如果设置的比实际需要的空间小，会导致程序挂掉。因此，最好不要减小Demo 程序中给出的大小。
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 75 * 1024 ) )	//设置堆空间（Heap）的大小。只有当程序中采用FreeRTOS 提供的内存分配算法时才会用到。
#define configMAX_TASK_NAME_LEN			( 10 )											//任务名称最大的长度，这个长度是以字节为单位的，并且包括最后的 NULL 结束字节。
#define configUSE_TRACE_FACILITY		1														//如果程序中需要用到TRACE功能，则需将这个宏设为1。否则设为0。开启TRACE功能后，RAM占用量会增大许多，因此在设为1之前请三思。
#define configUSE_16_BIT_TICKS			0														//将 configUSE_16_BIT_TICKS设为 1后portTickType 将被定义为无符号的16位整形类型，configUSE_16_BIT_TICKS 设为0 后portTickType 则被定义为无符号的32位整型。
#define configIDLE_SHOULD_YIELD			1														//这个参数控制那些优先级与idle 任务相同的任务的行为，并且只有当内核被配置为抢占式任务调度时才有实际作用。
#define configUSE_MUTEXES				1																//设为 1 则程序中会包含mutex 相关的代码，设为 0 则忽略相关的代码。
#define configQUEUE_REGISTRY_SIZE		8														//队列注册表有两个作用，但是这两个作用都依赖于调试器的支持：
																																			//1.        给队列一个名字，方便调试时辨认是哪个队列。
																																			//2.        包含调试器需要的特定信息用来定位队列和信号量。
																																			//如果你的调试器没有上述功能，哪个这个注册表就毫无用处，还占用的宝贵的RAM空间。
#define configCHECK_FOR_STACK_OVERFLOW	0												//堆栈溢出检查
#define configUSE_RECURSIVE_MUTEXES		1													//设为 1 则程序中会包含recursive mutex 相关的代码，设为 0 则忽略相关的代码。
#define configUSE_MALLOC_FAILED_HOOK	0													//这里钩子还未定义
#define configUSE_APPLICATION_TASK_TAG	0
#define configUSE_COUNTING_SEMAPHORES	1													//设为 1 则程序中会包含semaphore 相关的代码，设为 0 则忽略相关的代码。
#define configGENERATE_RUN_TIME_STATS	0													//设置是否产生运行时的统计信息，这些信息只对调试有用，会保存在RAM 中，占用RAM空间。因此，最终程序建议配置成不产生运行时统计信息。

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0  														//设置为1则包含co-routines 功能，如果包含了co-routines功能，则编译时需包含croutine.c 文件
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 ) 									//co-routines 可以使用的优先级的数量。

/* Software timer definitions. */
#define configUSE_TIMERS				1 															//设置为1则包含软件定时器功能。
#define configTIMER_TASK_PRIORITY		( 2 ) 											//设置软件定时器任务的优先级。
#define configTIMER_QUEUE_LENGTH		10 													//设置软件定时器任务中用到的命令队列的长度。
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 ) //设置软件定时器任务需要的任务堆栈大小。

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
/*中断优先级数大于(优先级低于)这个的,ISR不能调用interrupt  safe FreeRTOS API functions*/
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

