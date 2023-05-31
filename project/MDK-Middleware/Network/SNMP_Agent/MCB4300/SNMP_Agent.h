/*------------------------------------------------------------------------------
 * SNMP_Agent header module
 * Copyright (c) 2022 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    SNMP_Agent.h
 * Purpose: SNMP_Agent header 
 *----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SNMP_AGENT
#define __SNMP_AGENT

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2

extern uint32_t net_if;

extern void register_mib_table (void);
extern char lcd_text[2][20+1];
extern osThreadId_t TID_Display;

#endif /* __SNMP_AGENT */
