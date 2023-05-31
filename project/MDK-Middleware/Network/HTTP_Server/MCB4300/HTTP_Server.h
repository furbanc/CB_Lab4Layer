/*------------------------------------------------------------------------------
 * HTTP_Server header module
 * Copyright (c) 2022 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    HTTP_Server.h
 * Purpose: HTTP_Server header 
 *----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HTTP_SERVER
#define __HTTP_SERVER

#include <stdbool.h>
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2

extern bool LEDrun;
extern char lcd_text[2][20+1];
extern uint32_t net_if;
extern bool net_ip6;

extern osThreadId_t TID_Display;
extern osThreadId_t TID_Led;

#endif /* __HTTP_SERVER */
