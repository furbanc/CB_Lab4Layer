/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2022 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    BSD_Client.c
 * Purpose: BSD socket client example
 *----------------------------------------------------------------------------*/

#include "main.h"

#include "cmsis_os2.h"
#include "cmsis_vio.h"

#include "rl_net.h"

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <o>Socket type <0=>Stream <1=>Datagram
//   <i>Stream (TCP) or Datagram (UDP) socket type.
#define SOCK_TYPE       0

//   <o>Remote Port <1-65535>
//   <i>Remote port number.
//   <i> Default: 1001
#define SOCK_PORT       1001

//   <e>Use IPv4
//   <i>Use IPv4 Protocol to connect.
#define IP4_ENABLE      1

//     <s.15>Remote IP Address
//     <i>Remote IPv4 Address in text representation.
//     <i>Default: "192.168.0.100"
#define IP4_ADDR        "192.168.0.100"

//   </e>
//   <e>Use IPv6
//   <i>Use IPv6 Protocol to connect
#define IP6_ENABLE      0

//     <s.40>Remote IP Address
//     <i>Remote IPv6 Address in text representation.
//     <i>Default: "fe80::1c30:6cff:fea2:455e"
#define IP6_ADDR        "fe80::1c30:6cff:fea2:455e"

//   </e>

//------------- <<< end of configuration section >>> -----------------------

#if (!(IP4_ENABLE ^ IP6_ENABLE))
  #error Select IPv4 only or IPv6 only!
#endif

#define BLINKLED        0x01
#define SOCKTYPE  ((SOCK_TYPE == 0) ? SOCK_STREAM : SOCK_DGRAM)

static const osThreadAttr_t app_main_attr = {
  .stack_size = 4096U
};

/* Network interface */
uint32_t net_if = NET_IF_CLASS_ETH | 0;

/* Thread declarations */
static void Client (void *arg);

/* IP address change notification */
void netDHCP_Notify (uint32_t if_id, uint8_t option, const uint8_t *val, uint32_t len) {
  (void)if_id;
  (void)len;

  if (option == NET_DHCP_OPTION_IP_ADDRESS) {
    vioSetIPv4 (0U, *(const vioAddrIPv4_t *)val);
  }
}

/*----------------------------------------------------------------------------
  Thread 'Client': BSD Client socket process
 *---------------------------------------------------------------------------*/
__NO_RETURN static void Client (void *arg) {
  int32_t sock, retv;
  char dbuf[4];
  (void)arg;

  /* Connect and send LED state */
  while (1) {
    osDelay (2000U);

#if (IP4_ENABLE)
    /* Create IPv4 socket address */
    SOCKADDR_IN  addr;
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(SOCK_PORT);
    if (!inet_pton (AF_INET, IP4_ADDR, &addr.sin_addr)) {
      /* Address configuration error */
      for (;;);
    }

    sock = socket (AF_INET, SOCKTYPE, 0);
    retv = connect (sock, (SOCKADDR *)&addr, sizeof(addr));
#endif

#if (IP6_ENABLE)
    /* Create IPv6 socket address (MDK-Pro only) */
    SOCKADDR_IN6 addr6;
    addr6.sin6_family   = AF_INET6;
    addr6.sin6_port     = htons(SOCK_PORT);
    addr6.sin6_flowinfo = 0;
    if (!inet_pton (AF_INET6, IP6_ADDR, &addr6.sin6_addr)) {
      /* Address configuration error or IPv6 not supported */
      for (;;);
    }

    sock = socket (AF_INET6, SOCKTYPE, 0);
    retv = connect (sock, (SOCKADDR *)&addr6, sizeof(addr6));
#endif

    if (retv < 0) {
      closesocket (sock);
      continue;
    }

    while (1) {
      /* LED0 on */
      vioSetSignal(vioLED0, vioLEDon);
      // Send data to BSD Server
      dbuf[0] = BLINKLED;
      dbuf[1] = 1;
      retv = send (sock, dbuf, 2, 0);
      if (retv < 0) {
        break;
      }
      osDelay (1000U);
      vioSetSignal(vioLED0, vioLEDoff);

      /* LED1 on */
      vioSetSignal(vioLED1, vioLEDon);
      // Send data to BSD Server
      dbuf[0] = BLINKLED;
      dbuf[1] = 2;
      retv = send (sock, dbuf, 2, 0);
      if (retv < 0) {
        break;
      }
      osDelay (1000U);
      vioSetSignal(vioLED1, vioLEDoff);
    }
    closesocket (sock);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'main': Run Network
 *---------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *arg) {
  uint8_t ip_addr[NET_ADDR_IP6_LEN];
  (void)arg;

  vioInit       ();
  netInitialize ();

#if (IP4_ENABLE)
  vioPrint (vioLevelHeading, "BSD Client IPv4");
  if (netIF_GetOption (net_if, netIF_OptionIP4_Address,
                               ip_addr, sizeof(ip_addr)) == netOK) {
    vioSetIPv4 (0U, *(vioAddrIPv4_t *)ip_addr);
  }
#endif
#if (IP6_ENABLE)
  vioPrint (vioLevelHeading, "BSD Client IPv6");
  if (netIF_GetOption (net_if, netIF_OptionIP6_LinkLocalAddress,
                               ip_addr, sizeof(ip_addr)) == netOK) {
    /* Print IPv6 network address (MDK-Pro only) */
    vioSetIPv6 (0U, *(vioAddrIPv6_t *)ip_addr);
  }
#endif

  // Create networking task
  osThreadNew (Client, NULL, NULL);

  osThreadExit();
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, &app_main_attr);
}
