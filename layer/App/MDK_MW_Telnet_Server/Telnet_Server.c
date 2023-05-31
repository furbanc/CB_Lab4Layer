/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2022 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    Telnet_Server.c
 * Purpose: Telnet Server example
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "main.h"

#include "cmsis_os2.h"
#include "cmsis_vio.h"

#include "rl_net.h"
#include "Telnet_Server.h"

static const osThreadAttr_t app_main_attr = {
  .stack_size = 4096U
};

bool LEDrun;
char lcd_text[2][20+1] = { "LCD line 1",
                           "LCD line 2" };
bool net_ip6;

/* Network interface */
uint32_t net_if = NET_IF_CLASS_ETH | 0;

/* Thread IDs */
osThreadId_t TID_Display;
osThreadId_t TID_Led;

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
  netStatus rc;
  (void)arg;

  vioPrint (vioLevelHeading, "Telnet Serv. example");

  /* Check if IPv6 is supported */
  rc = netIF_GetOption (net_if, netIF_OptionIP6_LinkLocalAddress, ip_addr, sizeof(ip_addr));
  net_ip6 = (rc == netOK) ? true : false;

  if (net_ip6 == true) {
    /* Print Link-local IPv6 address */
    vioSetIPv6 (0U, *(vioAddrIPv6_t *)ip_addr);
  }
  while(1) {
    /* Wait for signal from DHCP */
    osThreadFlagsWait (0x01U, osFlagsWaitAny, osWaitForever);

    /* Retrieve IPv4 address */
    netIF_GetOption (net_if, netIF_OptionIP4_Address, ip_addr, sizeof(ip_addr));
    vioSetIPv4 (0U, *(vioAddrIPv4_t *)ip_addr);

    /* Display user text lines */
    vioPrint (vioLevelMessage, "[%s][%s]", lcd_text[0], lcd_text[1]);
  }
}

/*----------------------------------------------------------------------------
  Thread 'BlinkLed': Blink the LEDs on an eval board
 *---------------------------------------------------------------------------*/
__NO_RETURN static void BlinkLed (void *arg) {
  (void)arg;

  LEDrun = true;
  while(1) {
    if (LEDrun == true) {
      vioSetSignal(vioLED0, vioLEDon);
      vioSetSignal(vioLED1, vioLEDoff);
    }
    osDelay (1000U);
    if (LEDrun == true) {
      vioSetSignal(vioLED0, vioLEDoff);
      vioSetSignal(vioLED1, vioLEDon);
    }
    osDelay (1000U);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'app_main': Run Network
 *---------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *arg) {
  (void)arg;

  vioInit       ();
  netInitialize ();

  TID_Led     = osThreadNew (BlinkLed, NULL, NULL);
  TID_Display = osThreadNew (Display,  NULL, NULL);

  osThreadExit();
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, &app_main_attr);
}
