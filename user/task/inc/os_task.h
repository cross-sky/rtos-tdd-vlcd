#ifndef __OS_TASK_H
#define __OS_TASK_H

#define USE_FreeRTOS 1

#if USE_FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#define DISABLE_INT()    taskENTER_CRITICAL()
#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

#include "task_button.h"

#endif
