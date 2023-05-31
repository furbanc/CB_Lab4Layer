/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2022 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    FTP_Server.c
 * Purpose: FTP Server example
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "main.h"

#include "cmsis_os2.h"
#include "cmsis_vio.h"

#include "rl_net.h"
#include "rl_fs.h"

static const osThreadAttr_t app_main_attr = {
  .stack_size = 4096U
};

/* Network interface */
uint32_t net_if = NET_IF_CLASS_ETH | 0;

/* Thread IDs */
static osThreadId_t TID_Display;

/* Thread declarations */
static void BlinkLed (void *arg);
static void Display  (void *arg);

/* IP address change notification */
void netDHCP_Notify (uint32_t if_id, uint8_t option, const uint8_t *val, uint32_t len) {
  (void)if_id;
  (void)val;
  (void)len;

  if (option == NET_DHCP_OPTION_IP_ADDRESS) {
    osThreadFlagsSet (TID_Display, 0x01);
  }
}

/*----------------------------------------------------------------------------
  Thread 'Display': LCD display handler
 *---------------------------------------------------------------------------*/
__NO_RETURN static void Display (void *arg) {
  uint8_t ip_addr[NET_ADDR_IP6_LEN];
  uint32_t net_if;
  netStatus rc;
  (void)arg;

  vioPrint (vioLevelHeading, "FTP Server example");

  /* Check if IPv6 is supported */
  rc = netIF_GetOption (net_if, netIF_OptionIP6_LinkLocalAddress, ip_addr, sizeof(ip_addr));
  if (rc == netOK) {
    /* Print Link-local IPv6 address */
    vioSetIPv6 (0U, *(vioAddrIPv6_t *)ip_addr);
  }
  while(1) {
    /* Wait for signal from DHCP */
    osThreadFlagsWait (0x01U, osFlagsWaitAny, osWaitForever);

    /* Retrieve and print IPv4 address */
    netIF_GetOption (net_if, netIF_OptionIP4_Address, ip_addr, sizeof(ip_addr));
    vioSetIPv4 (0U, *(vioAddrIPv4_t *)ip_addr);
  }
}

/*----------------------------------------------------------------------------
  Thread 'BlinkLed': Blink the LEDs on an eval board
 *---------------------------------------------------------------------------*/
__NO_RETURN static void BlinkLed (void *arg) {
  (void)arg;

  while(1) {
    vioSetSignal(vioLED0, vioLEDon);
    vioSetSignal(vioLED1, vioLEDoff);
    osDelay (1000U);
    vioSetSignal(vioLED0, vioLEDoff);
    vioSetSignal(vioLED1, vioLEDon);
    osDelay (1000U);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'main': Run Network
 *---------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *arg) {
  (void)arg;

  if (finit("") == fsOK) {
    fmount("");
  }

  vioInit       ();
  netInitialize ();

                osThreadNew (BlinkLed, NULL, NULL);
  TID_Display = osThreadNew (Display,  NULL, NULL);

  osThreadExit();
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, &app_main_attr);
}
