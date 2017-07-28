#ifndef __BSP_H
#define __BSP_H

#define STM32_VLCD

#define __STM32F1_BSP_VERSION "1.1"

#ifdef __dsb_vs
void __dsb(uint8_t);
#endif // __dsb_vs

#define USE_FreeRTOS 1

#if USE_FreeRTOS
	#include "FreeRTOS.h"
	#include "task.h"
	#define DISABLE_INT()    taskENTER_CRITICAL()
	#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
	/* ����ȫ���жϵĺ� */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
	#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */
#endif

#define BSP_Printf printf

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <stdint.h>

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif

#include "bsp_led.h"

void BSP_init(void);


#endif

