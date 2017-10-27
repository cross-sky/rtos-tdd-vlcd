#ifndef __BSP_HW_H
#define __BSP_HW_H

#include <stdint.h>
#ifdef __dsb_vs
void __dsb(uint8_t);
#endif // __dsb_vs

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif

#endif
