/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2021 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    HID.c
 * Purpose: USB Device - Human Interface Device example
 *----------------------------------------------------------------------------*/

#include "main.h"

#include "cmsis_os2.h"
#include "cmsis_vio.h"

#include "rl_usb.h"

static const osThreadAttr_t app_main_attr = {
  .stack_size = 4096U
};

/*---------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
__NO_RETURN static void app_main (void *argument) {
  uint8_t btn, btn_old = 0U;

  (void)argument;

  vioPrint(vioLevelHeading, "USB HID");

  USBD_Initialize(0U);                  // USB Device 0 Initialization
  USBD_Connect   (0U);                  // USB Device 0 Connect

  for (;;) {                            // Loop forever
    btn = vioGetSignal(0xFFU) & 0xFFU;
    if (btn != btn_old) {
      btn_old = btn;
      USBD_HID_GetReportTrigger(0U, 0U, &btn, 1U);
    }
    osDelay(100U);                      // 100 ms delay for sampling buttons
  }
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, &app_main_attr);
}
