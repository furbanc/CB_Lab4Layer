/*---------------------------------------------------------------------------
 * Copyright (c) 2021 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "cmsis_vio.h"
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

#ifdef    RTE_USB_Device_0 
#include "SCU_LPC43xx.h"
#endif
#include "main.h"

int main (void) {

  NVIC_SetPriority(C_CAN0_IRQn,   4U);
  NVIC_SetPriority(ETHERNET_IRQn, 4U);
  NVIC_SetPriority(I2C0_IRQn,     4U);
  NVIC_SetPriority(I2S0_IRQn,     4U);
  NVIC_SetPriority(SDIO_IRQn,     4U);
  NVIC_SetPriority(SSP0_IRQn,     4U);
  NVIC_SetPriority(USART0_IRQn,   4U);
  NVIC_SetPriority(USB0_IRQn,     4U);

#ifdef RTE_USB_Device_0 
  // Disable pull-ups on pins used for USB Host VBUS control (P6_3, P9_5)
  SCU_PinConfigure(6U, 3U, SCU_CFG_MODE_FUNC0 | SCU_PIN_CFG_PULLUP_DIS);
  SCU_PinConfigure(9U, 5U, SCU_CFG_MODE_FUNC0 | SCU_PIN_CFG_PULLUP_DIS);
#endif

  SystemCoreClockUpdate();

  vioInit();                            // Initialize Virtual I/O

#if defined(RTE_Compiler_EventRecorder) && \
    (defined(__MICROLIB) || \
    !(defined(RTE_CMSIS_RTOS2_RTX5) || defined(RTE_CMSIS_RTOS2_FreeRTOS)))
  EventRecorderInitialize(EventRecordAll, 1U);
#endif

  osKernelInitialize();                 // Initialize CMSIS-RTOS2
  app_initialize();                     // Initialize application
  osKernelStart();                      // Start thread execution

  for (;;) {}
}
