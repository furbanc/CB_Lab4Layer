/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2022 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    BSD_Server.c
 * Purpose: BSD socket server example
 *----------------------------------------------------------------------------*/

#include <string.h>
#include "main.h"

#include "cmsis_os2.h"
#include "cmsis_vio.h"

#include "rl_net.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <o>Local Port <1-65535>
//   <i>Local port number.
//   <i> Default: 1001
#define SOCK_PORT      1001

//   <q>Use IPv4
//   <i>Use IPv4 Protocol to accept connections.
#define IP4_ENABLE      0

//   <q>Use IPv6
//   <i>Use IPv6 Protocol to accept connections.
#define IP6_ENABLE      1

//------------- <<< end of configuration section >>> -----------------------

#if (!(IP4_ENABLE ^ IP6_ENABLE))
  #error Select IPv4 only or IPv6 only!
#endif

#define BLINKLED        0x01

static const osThreadAttr_t app_main_attr = {
  .stack_size = 4096U
};

/* Network interface */
uint32_t net_if = NET_IF_CLASS_ETH | 0;

/* Thread declarations */
static void Stream_Server (void *arg);
static void Dgram_Server (void *arg);

/// Stream socket server thread
__NO_RETURN static void Stream_Server (void *arg) {
  int32_t sock, sd, retv;
  char dbuf[4];
  (void)arg;

  while (1) {

#if (IP4_ENABLE)
    /* Create IPv4 socket address */
    SOCKADDR_IN  addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons (SOCK_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    sock = socket (AF_INET, SOCK_STREAM, 0);
    retv = bind (sock, (SOCKADDR *)&addr, sizeof (addr));
#endif

#if (IP6_ENABLE)
    /* Create IPv6 socket address (MDK-Pro only) */
    SOCKADDR_IN6 addr6;
    addr6.sin6_family    = AF_INET6;
    addr6.sin6_port      = htons (SOCK_PORT);
    addr6.sin6_flowinfo  = 0;
    memset (&addr6.sin6_addr, 0, sizeof (addr6.sin6_addr));

    sock = socket (AF_INET6, SOCK_STREAM, 0);
    retv = bind (sock, (SOCKADDR *)&addr6, sizeof (addr6));
#endif

    if (retv < 0) {
      closesocket (sock);
      continue;
    }
    retv = listen (sock, 1);
    if (retv < 0) {
      closesocket (sock);
      continue;
    }
    sd = accept (sock, NULL, NULL);
    closesocket (sock);

    while (1) {
      retv = recv (sd, dbuf, sizeof (dbuf), 0);
      if (retv <= 0) {
        break;
      }
      if (dbuf[0] == BLINKLED) {
        vioSetSignal( dbuf[1], vioLEDon);
        vioSetSignal(~dbuf[1], vioLEDoff);
      }
    }
    closesocket (sd);
  }
}

/// Datagram socket server thread
__NO_RETURN static void Dgram_Server (void *arg) {
  int32_t sock, retv;
  char dbuf[4];
  (void)arg;

  while (1) {

#if (IP4_ENABLE)
    /* Create IPv4 socket address */
    SOCKADDR_IN  addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons (SOCK_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    sock = socket (AF_INET, SOCK_DGRAM, 0);
    retv = bind (sock, (SOCKADDR *)&addr, sizeof (addr));
#endif

#if (IP6_ENABLE)
    /* Create IPv6 socket address (MDK-Pro only) */
    SOCKADDR_IN6 addr6;
    addr6.sin6_family    = AF_INET6;
    addr6.sin6_port      = htons (SOCK_PORT);
    addr6.sin6_flowinfo  = 0;
    memset (&addr6.sin6_addr, 0, sizeof (addr6.sin6_addr));

    sock = socket (AF_INET6, SOCK_DGRAM, 0);
    retv = bind (sock, (SOCKADDR *)&addr6, sizeof (addr6));
#endif

    if (retv < 0) {
      closesocket (sock);
      continue;
    }

    while (1) {
      retv = recv (sock, dbuf, sizeof (dbuf), 0);
      if (retv == BSD_ETIMEDOUT) {
        continue;
      }
      if (retv <= 0) {
        break;
      }
      if (dbuf[0] == BLINKLED) {
        vioSetSignal( dbuf[1], vioLEDon);
        vioSetSignal(~dbuf[1], vioLEDoff);
      }
    }
    closesocket (sock);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'app_main': Run Network
 *---------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *arg) {
  uint8_t ip_addr[NET_ADDR_IP6_LEN];
  (void)arg;

  vioInit       ();
  netInitialize ();

#if (IP4_ENABLE)
  vioPrint (vioLevelHeading, "BSD Server IPv4");
  if (netIF_GetOption (net_if, netIF_OptionIP4_Address,
                               ip_addr, sizeof(ip_addr)) == netOK) {
    vioSetIPv4 (0U, *(vioAddrIPv4_t *)ip_addr);
  }
#endif

#if (IP6_ENABLE)
  vioPrint (vioLevelHeading, "BSD Server IPv6");
  if (netIF_GetOption (net_if, netIF_OptionIP6_LinkLocalAddress,
                               ip_addr, sizeof(ip_addr)) == netOK) {
    vioSetIPv6 (0U, *(vioAddrIPv6_t *)ip_addr);
  }
  else {
    vioPrint (vioLevelError, "IPv6 not supported");
    for (;;);
  }
#endif

  /* Create server threads */
  osThreadNew (Stream_Server, NULL, NULL);
  osThreadNew (Dgram_Server, NULL, NULL);

  osThreadExit();
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, &app_main_attr);
}
