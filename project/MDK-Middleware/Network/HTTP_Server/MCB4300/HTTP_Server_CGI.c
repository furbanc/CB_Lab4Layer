/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network:Service
 * Copyright (c) 2004-2022 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    HTTP_Server_CGI.c
 * Purpose: HTTP Server CGI Module
 * Rev.:    V7.0.0
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE
#include "cmsis_vio.h"
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "HTTP_Server.h"

#if      defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma  clang diagnostic push
#pragma  clang diagnostic ignored "-Wformat-nonliteral"
#endif

// External reference
extern const char *net_tcp_ntoa (netTCP_State state);

// Local variables.
static uint8_t P2;
static uint8_t ip_addr[NET_ADDR_IP6_LEN];
static char    ip_ascii[40];

// My structure of CGI status variable.
typedef struct {
  uint8_t idx;
  uint8_t unused[3];
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)

// Convert TCP socket state into a string.
static const char *tcp_ntoa (netTCP_State state) {
  static const char *const sa[11] = {
    "UNUSED",
    "CLOSED",
    "LISTEN",
    "SYN_REC",
    "SYN_SENT",
    "FIN_WAIT_1",
    "FIN_WAIT_2",
    "CLOSING",
    "LAST_ACK",
    "TIME_WAIT",
    "ESTABLISHED"
  };
  return (sa[state]);
}

// \brief Process query string received by GET request.
// \param[in]     qstr          pointer to the query string.
// \return        none.
void netCGI_ProcessQuery (const char *qstr) {
  char var[44];

  do {
    // Loop through all the parameters
    qstr = netCGI_GetEnvVar (qstr, var, sizeof (var));

    // Check return string, 'qstr' now points to the next parameter
    if (strncmp (var, "i4=", 3) == 0) {
      // Local IP4 address
      netIP_aton (&var[3], NET_ADDR_IP4, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP4_Address, ip_addr, NET_ADDR_IP4_LEN);
    }
    else if (strncmp (var, "i6=", 3) == 0) {
      // Local IP6 address
      netIP_aton (&var[3], NET_ADDR_IP6, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP6_StaticAddress, ip_addr, NET_ADDR_IP6_LEN);
    }
    else if (strncmp (var, "m=", 2) == 0) {
      // Local network mask
      netIP_aton (&var[2], NET_ADDR_IP4, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP4_SubnetMask, ip_addr, NET_ADDR_IP4_LEN);
    }
    else if (strncmp (var, "g4=", 3) == 0) {
      // Default gateway IP4 address
      netIP_aton (&var[3], NET_ADDR_IP4, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP4_DefaultGateway, ip_addr, NET_ADDR_IP4_LEN);
    }
    else if (strncmp (var, "g6=", 3) == 0) {
      // Default gateway IP6 address
      netIP_aton (&var[3], NET_ADDR_IP6, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP6_DefaultGateway, ip_addr, NET_ADDR_IP6_LEN);
    }
    else if (strncmp (var, "p4=", 3) == 0) {
      // Primary DNS server IP4 address
      netIP_aton (&var[3], NET_ADDR_IP4, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP4_PrimaryDNS, ip_addr, NET_ADDR_IP4_LEN);
    }
    else if (strncmp (var, "p6=", 3) == 0) {
      // Primary DNS server IP6 address
      netIP_aton (&var[3], NET_ADDR_IP6, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP6_PrimaryDNS, ip_addr, NET_ADDR_IP6_LEN);
    }
    else if (strncmp (var, "s4=", 3) == 0) {
      // Secondary DNS server IP4 address
      netIP_aton (&var[3], NET_ADDR_IP4, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP4_SecondaryDNS, ip_addr, NET_ADDR_IP4_LEN);
    }
    else if (strncmp (var, "s6=", 3) == 0) {
      // Secondary DNS server IP6 address
      netIP_aton (&var[3], NET_ADDR_IP6, ip_addr);
      netIF_SetOption (net_if, netIF_OptionIP6_SecondaryDNS, ip_addr, NET_ADDR_IP6_LEN);
    }
  } while (qstr);
}

// \brief Process data received by POST request.
// \param[in]     code          callback context:
//                              - 0 = www-url-encoded form data,
//                              - 1 = filename for file upload (null-terminated string),
//                              - 2 = file upload raw data,
//                              - 3 = end of file upload (file close requested),
//                              - 4 = any other type of POST data (single or last stream),
//                              - 5 = the same as 4, but with more data to follow.
// \param[in]     data          pointer to POST data.
// \param[in]     len           length of POST data.
// \return        none.
void netCGI_ProcessData (uint8_t code, const char *data, uint32_t len) {
  char var[40],passw[12];

  if (code != 0) {
    // Ignore all other codes
    return;
  }

  P2 = 0;
  LEDrun = true;
  if (len == 0) {
    // No data or all items (radio, checkbox) are off
    vioSetSignal( P2, vioLEDon);
    vioSetSignal(~P2, vioLEDoff);
    return;
  }
  passw[0] = 1;
  do {
    // Parse all parameters
    data = netCGI_GetEnvVar (data, var, sizeof (var));
    if (var[0] != 0) {
      // First character is non-null, string exists
      if (strcmp (var, "led0=on") == 0) {
        P2 |= 0x01;
      }
      else if (strcmp (var, "led1=on") == 0) {
        P2 |= 0x02;
      }
      else if (strcmp (var, "led2=on") == 0) {
        P2 |= 0x04;
      }
      else if (strcmp (var, "led3=on") == 0) {
        P2 |= 0x08;
      }
      else if (strcmp (var, "led4=on") == 0) {
        P2 |= 0x10;
      }
      else if (strcmp (var, "led5=on") == 0) {
        P2 |= 0x20;
      }
      else if (strcmp (var, "led6=on") == 0) {
        P2 |= 0x40;
      }
      else if (strcmp (var, "led7=on") == 0) {
        P2 |= 0x80;
      }
      else if (strcmp (var, "ctrl=Browser") == 0) {
        LEDrun = false;
      }
      else if ((strncmp (var, "pw0=", 4) == 0) ||
               (strncmp (var, "pw2=", 4) == 0)) {
        // Change password, retyped password
        if (netHTTPs_LoginActive()) {
          if (passw[0] == 1) {
            strcpy (passw, var+4);
          }
          else if (strcmp (passw, var+4) == 0) {
            // Both strings are equal, change the password
            netHTTPs_SetPassword (passw);
          }
        }
      }
      else if (strncmp (var, "lcd1=", 5) == 0) {
        // LCD Module line 1 text
        strcpy (lcd_text[0], var+5);
        osThreadFlagsSet (TID_Display, 0x01);
      }
      else if (strncmp (var, "lcd2=", 5) == 0) {
        // LCD Module line 2 text
        strcpy (lcd_text[1], var+5);
        osThreadFlagsSet (TID_Display, 0x01);
      }
    }
  } while (data);
  vioSetSignal( P2, vioLEDon);
  vioSetSignal(~P2, vioLEDoff);
}

// \brief Generate dynamic web data based on a CGI script.
// \param[in]     env           environment string.
// \param[out]    buf           output data buffer.
// \param[in]     buf_len       size of output buffer (from 536 to 1440 bytes).
// \param[in,out] pcgi          pointer to a session's local buffer of 4 bytes.
//                              - 1st call = cleared to 0,
//                              - 2nd call = not altered by the system,
//                              - 3rd call = not altered by the system, etc.
// \return        number of bytes written to output buffer.
//                - return len | (1U<<31) = repeat flag, the system calls this function
//                                          again for the same script line.
//                - return len | (1U<<30) = force transmit flag, the system transmits
//                                          current packet immediately.
uint32_t netCGI_Script (const char *env, char *buf, uint32_t buf_len, uint32_t *pcgi) {
  uint32_t len = 0U;
  int32_t socket;
  netTCP_State state;
  NET_ADDR client;
  const char *lang;
  uint8_t id;
  static uint32_t adv;

  ip_ascii[0] = 0;
  switch (env[0]) {
    // Analyze a 'c' script line starting position 2
    case 'a' :
      // Network parameters from 'network.cgi'
      switch (env[2]) {
        case 'l':
          // Link-local address
          if (net_ip6) {
            netIF_GetOption (net_if, netIF_OptionIP6_LinkLocalAddress, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));
          }
          len = (uint32_t)sprintf (buf, &env[4], ip_ascii);
          break;

        case 'i':
          // Local IP address
          if (env[3] == '4') {
            netIF_GetOption (net_if, netIF_OptionIP4_Address, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));
          }           
          else if (net_ip6) {
            netIF_GetOption (net_if, netIF_OptionIP6_StaticAddress, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));
          }
          len = (uint32_t)sprintf (buf, &env[5], ip_ascii, (net_ip6) ? "" : "disabled");
          break;   

        case 'm':
          // Local network mask
          netIF_GetOption (net_if, netIF_OptionIP4_SubnetMask, ip_addr, sizeof(ip_addr));
          netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));
          len = (uint32_t)sprintf (buf, &env[4], ip_ascii);
          break;

        case 'd':
          // Dynamic IPv6 address
          netIF_GetOption (net_if, netIF_OptionIP6_DynamicAddress, ip_addr, sizeof(ip_addr));
          netIP_ntoa (NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));
          len = (uint32_t)sprintf (buf, &env[4], ip_ascii);
          break;

        case 'g':
          // Default gateway address
          if (env[3] == '4') {
            netIF_GetOption (net_if, netIF_OptionIP4_DefaultGateway, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));
          }           
          else if (net_ip6) {
            netIF_GetOption (net_if, netIF_OptionIP6_DefaultGateway, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));
          }
          len = (uint32_t)sprintf (buf, &env[5], ip_ascii, (net_ip6) ? "" : "disabled");
          break;

        case 'p':
          // Primary DNS server address
          if (env[3] == '4') {
            netIF_GetOption (net_if, netIF_OptionIP4_PrimaryDNS, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));
          }           
          else if (net_ip6) {
            netIF_GetOption (net_if, netIF_OptionIP6_PrimaryDNS, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));
          }
          len = (uint32_t)sprintf (buf, &env[5], ip_ascii, (net_ip6) ? "" : "disabled");
          break;

        case 's':
          // Secondary DNS server address
          if (env[3] == '4') {
            netIF_GetOption (net_if, netIF_OptionIP4_SecondaryDNS, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));
          }           
          else if (net_ip6) {
            netIF_GetOption (net_if, netIF_OptionIP6_SecondaryDNS, ip_addr, sizeof(ip_addr));
            netIP_ntoa (NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));
          }
          len = (uint32_t)sprintf (buf, &env[5], ip_ascii, (net_ip6) ? "" : "disabled");
          break;
      }
      break;

    case 'b':
      // LED control from 'led.cgi'
      if (env[2] == 'c') {
        // Select Control
        len = (uint32_t)sprintf (buf, &env[4], LEDrun ?     ""     : "selected",
                                               LEDrun ? "selected" :    ""     );
        break;
      }
      // LED CheckBoxes
      id = env[2] - '0';
      if (id > 7) {
        id = 0;
      }
      id = (uint8_t)(1U << id);
      len = (uint32_t)sprintf (buf, &env[4], (P2 & id) ? "checked" : "");
      break;

    case 'c':
      // TCP status from 'tcp.cgi'
      while ((uint32_t)(len + 150) < buf_len) {
        socket = ++MYBUF(pcgi)->idx;
        state  = netTCP_GetState (socket);
        if (state == netTCP_StateINVALID) {
          /* Invalid socket, we are done */
          return ((uint32_t)len);
        }
        // 'sprintf' format string is defined here
        len += (uint32_t)sprintf (buf+len,   "<tr align=\"center\">");
        len += (uint32_t)sprintf (buf+len,   "<td>%d</td><td>%s</td>",
                                             socket, tcp_ntoa (state));
        if (state <= netTCP_StateCLOSED) {
          len += (uint32_t)sprintf (buf+len, "<td>-</td><td>-</td>"
                                             "<td>-</td><td>-</td></tr>\r\n");
        }
        else if (state == netTCP_StateLISTEN) {
          len += (uint32_t)sprintf (buf+len, "<td>%d</td><td>-</td>"
                                             "<td>-</td><td>-</td></tr>\r\n",
                                             netTCP_GetLocalPort(socket));
        }
        else {
          netTCP_GetPeer (socket, &client, sizeof(client));
          netIP_ntoa (client.addr_type, client.addr, ip_ascii, sizeof (ip_ascii));
          len += (uint32_t)sprintf (buf+len, "<td>%d</td><td>%d</td>"
                                             "<td>%s</td><td>%d</td></tr>\r\n",
                                             netTCP_GetLocalPort(socket),
                                             netTCP_GetTimer(socket), ip_ascii, client.port);
        }
      }
      /* More sockets to go, set a repeat flag */
      len |= (1u << 31);
      break;

    case 'd':
      // System password from 'system.cgi'
      switch (env[2]) {
        case '1':
          len = (uint32_t)sprintf (buf, &env[4], netHTTPs_LoginActive() ? "Enabled" : "Disabled");
          break;
        case '2':
          len = (uint32_t)sprintf (buf, &env[4], netHTTPs_GetPassword());
          break;
      }
      break;

    case 'e':
      // Browser Language from 'language.cgi'
      lang = netHTTPs_GetLanguage();
      if      (strncmp (lang, "en", 2) == 0) {
        lang = "English";
      }
      else if (strncmp (lang, "de", 2) == 0) {
        lang = "German";
      }
      else if (strncmp (lang, "fr", 2) == 0) {
        lang = "French";
      }
      else if (strncmp (lang, "sl", 2) == 0) {
        lang = "Slovene";
      }
      else {
        lang = "Unknown";
      }
      len = (uint32_t)sprintf (buf, &env[2], lang, netHTTPs_GetLanguage());
      break;

    case 'f':
      // LCD Module control from 'lcd.cgi'
      switch (env[2]) {
        case '1':
          len = (uint32_t)sprintf (buf, &env[4], lcd_text[0]);
          break;
        case '2':
          len = (uint32_t)sprintf (buf, &env[4], lcd_text[1]);
          break;
      }
      break;

    case 'g':
      // AD Input from 'ad.cgi'
      switch (env[2]) {
        case '1':
          adv = (uint32_t)vioGetValue (0);
          len = (uint32_t)sprintf (buf, &env[4], adv);
          break;
        case '2':
          len = (uint32_t)sprintf (buf, &env[4], (double)((float)adv*3.3f)/4096);
          break;
        case '3':
          adv = (adv * 100) / 4096;
          len = (uint32_t)sprintf (buf, &env[4], adv);
          break;
      }
      break;

    case 'x':
      // AD Input from 'ad.cgx'
      adv = (uint32_t)vioGetValue (0);
      len = (uint32_t)sprintf (buf, &env[1], adv);
      break;

    case 'y':
      // Button state from 'button.cgx'
      len = (uint32_t)sprintf (buf, "<checkbox><id>button%c</id><on>%s</on></checkbox>",
                               env[1], (vioGetSignal (0xFF) & (1 << (env[1]-'0'))) ? "true" : "false");
      break;
  }
  return (len);
}

#if      defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma  clang diagnostic pop
#endif
