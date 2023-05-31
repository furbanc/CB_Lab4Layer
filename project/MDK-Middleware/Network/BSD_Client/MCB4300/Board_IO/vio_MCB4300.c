/******************************************************************************
 * @file     vio_MCB4300.c
 * @brief    Virtual I/O implementation for Keil MCB4300 board
 * @version  V1.0.0
 * @date     20. September 2021
 ******************************************************************************/
/*
 * Copyright (c) 2019-2021 Arm Limited. All rights reserved.
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
 */

/*! \page vio_MCB4300 Physical I/O Mapping

The table below lists the physical I/O mapping of this CMSIS-Driver VIO implementation.

Virtual Resource  | Variable       | Physical Resource on MCB4300                   |
:-----------------|:---------------|:-----------------------------------------------|
vioBUTTON0        | vioSignalIn.0  | P4_0 : Button P4_0                             |
vioBUTTON1        | vioSignalIn.1  | P4_3 : Button P4_3                             |
vioBUTTON2        | vioSignalIn.2  | P4_4 : Button P4_4                             |
vioBUTTON3        | vioSignalIn.3  | WAKEUP0: Button WAKEUP0                        |
vioLED0           | vioSignalOut.0 | PD_10 : LED PD_10                              |
vioLED1           | vioSignalOut.1 | PD_11 : LED PD_11                              |
vioLED2           | vioSignalOut.2 | PD_12 : LED PD_12                              |
vioLED3           | vioSignalOut.3 | PD_13 : LED PD_13                              |
vioLED4           | vioSignalOut.4 | PD_14 : LED PD_14                              |
vioLED5           | vioSignalOut.5 | P9_0 : LED P9_0                                |
vioLED6           | vioSignalOut.6 | P9_1 : LED P9_1                                |
vioLED7           | vioSignalOut.7 | P9_2 : LED P9_2                                |
virtual terminal  | vioPrintMem    | Graphical LCD                                  |
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "cmsis_vio.h"

#include "RTE_Components.h"             // Component selection
#include CMSIS_device_header

#if !defined CMSIS_VOUT
#include "cmsis_os2.h"

#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_GLCD.h"                 // ::Board Support:Graphic LCD
#include "GLCD_Config.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;
#endif
#if !defined CMSIS_VIN
#include "Board_Buttons.h"              // ::Board Support:Buttons
#endif

// VIO input, output definitions
#define VIO_PRINT_MAX_SIZE      64U     // maximum size of print memory
#define VIO_PRINTMEM_NUM         4U     // number of print memories
#define VIO_VALUE_NUM            3U     // number of values
#define VIO_VALUEXYZ_NUM         3U     // number of XYZ values
#define VIO_IPV4_ADDRESS_NUM     2U     // number of IPv4 addresses
#define VIO_IPV6_ADDRESS_NUM     2U     // number of IPv6 addresses

extern uint32_t      vioSignalIn;
extern uint32_t      vioSignalOut;
extern char          vioPrintMem[VIO_PRINTMEM_NUM][VIO_PRINT_MAX_SIZE];
extern int32_t       vioValue   [VIO_VALUE_NUM];
extern vioValueXYZ_t vioValueXYZ[VIO_VALUEXYZ_NUM];
extern vioAddrIPv4_t vioAddrIPv4[VIO_IPV4_ADDRESS_NUM];
extern vioAddrIPv6_t vioAddrIPv6[VIO_IPV6_ADDRESS_NUM];

// VIO input, output variables
__USED uint32_t      vioSignalIn;                                       // Memory for incoming signal
__USED uint32_t      vioSignalOut;                                      // Memory for outgoing signal
__USED char          vioPrintMem[VIO_PRINTMEM_NUM][VIO_PRINT_MAX_SIZE]; // Memory for the last value for each level
__USED int32_t       vioValue   [VIO_VALUE_NUM];                        // Memory for value used in vioGetValue/vioSetValue
__USED vioValueXYZ_t vioValueXYZ[VIO_VALUEXYZ_NUM];                     // Memory for XYZ value for 3-D vector
__USED vioAddrIPv4_t vioAddrIPv4[VIO_IPV4_ADDRESS_NUM];                 // Memory for IPv4 address value used in vioSetIPv4/vioGetIPv4
__USED vioAddrIPv6_t vioAddrIPv6[VIO_IPV6_ADDRESS_NUM];                 // Memory for IPv6 address value used in vioSetIPv6/vioGetIPv6

#if !defined CMSIS_VOUT
static osMutexId_t   mutex_id_GLCD;     // Mutex ID of GLCD mutex
#endif

// Initialize test input, output.
void vioInit (void) {

  vioSignalIn  = 0U;
  vioSignalOut = 0U;

  memset (vioPrintMem, 0, sizeof(vioPrintMem));
  memset (vioValue,    0, sizeof(vioValue));
  memset (vioValueXYZ, 0, sizeof(vioValueXYZ));
  memset (vioAddrIPv4, 0, sizeof(vioAddrIPv4));
  memset (vioAddrIPv6, 0, sizeof(vioAddrIPv6));

#if !defined CMSIS_VOUT
  LED_Initialize();
  LED_SetOut(0U);

  mutex_id_GLCD = osMutexNew(NULL);     // Create GLCD mutex
  if (mutex_id_GLCD != NULL) {
    GLCD_Initialize();
    GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
    GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
    GLCD_ClearScreen();
  }
#endif

#if !defined CMSIS_VIN
  Buttons_Initialize();
#endif
}

// Print formated string to test terminal.
int32_t vioPrint (uint32_t level, const char *format, ...) {
  va_list args;
  int32_t ret;
#if !defined CMSIS_VOUT
  uint16_t cursor_x, cursor_y;
  uint16_t font_w, font_h;
  uint8_t  i;
  char     ch;
#endif

  if (level > vioLevelError) {
    return (-1);
  }

  if (level > VIO_PRINTMEM_NUM) {
    return (-1);
  }

  va_start(args, format);

  ret = vsnprintf((char *)vioPrintMem[level], sizeof(vioPrintMem[level]), format, args);

  va_end(args);

#if !defined CMSIS_VOUT
  if (mutex_id_GLCD != NULL) {
    osMutexAcquire(mutex_id_GLCD, osWaitForever);
    switch (level) {
      case vioLevelHeading:             // Heading text
        font_w   = GLCD_Font_16x24.width;
        font_h   = GLCD_Font_16x24.height;
        cursor_x = 0U;                  // Heading text starting position
        cursor_y = font_h;              // 2nd text row
        GLCD_SetFont            (&GLCD_Font_16x24);
        GLCD_SetForegroundColor (GLCD_COLOR_GREEN);
        break;
      case vioLevelMessage:             // Message text
        font_w   = GLCD_Font_16x24.width;
        font_h   = GLCD_Font_16x24.height;
        cursor_x = 0U;                  // Message text starting position
        cursor_y = font_h * 5U;         // 6th text row
        GLCD_SetFont            (&GLCD_Font_16x24);
        GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
        break;
      case vioLevelError:               // Error text
        font_w   = GLCD_Font_16x24.width;
        font_h   = GLCD_Font_16x24.height;
        cursor_x = 0U;                  // Error text starting position
        cursor_y = font_h * 9U;         // 10th text row
        GLCD_SetFont            (&GLCD_Font_16x24);
        GLCD_SetForegroundColor (GLCD_COLOR_RED);
        break;
      case vioLevelNone:                // Normal text
      default:
        font_w   = GLCD_Font_6x8.width;
        font_h   = GLCD_Font_6x8.height;
        cursor_x = 0U;                  // Normal text starting position
        cursor_y = 0U;                  // 1st text row
        GLCD_SetFont            (&GLCD_Font_6x8);
        GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
        break;
    }

    i = 0U;
    while (vioPrintMem[level][i] != 0) {
      ch = vioPrintMem[level][i];
      i++;

      switch (ch) {
        case 0x0A:                      // Line Feed ('\n')
          cursor_y += font_h;
          if (cursor_y >= GLCD_HEIGHT) {
            // If cursor is out of screen vertically then rollover to vertical 0 
            cursor_y = 0U;
          }
          break;
        case 0x0D:                      // Carriage Return ('\r')
          // Move the cursor to horizontal 0
          cursor_x = 0U;
          break;
        default:                        // Any other character
          // Display current character at the cursor position
          GLCD_DrawChar(cursor_x, cursor_y, ch);
          // Move the cursor to the next character on the right
          cursor_x += font_w;
          if (cursor_x >= GLCD_WIDTH) {
            // If cursor is out of screen horizontally then rollover to horizontal 0
            // and into new line
            cursor_x  = 0U;
            cursor_y += font_h;
            if (cursor_y >= GLCD_HEIGHT) {
              // If cursor is out of screen vertically then rollover to vertical 0
              cursor_y = 0U;
            }
          }
          break;
      }
    }

    osMutexRelease(mutex_id_GLCD);
  }
#endif

  return (ret);
}

// Set signal output.
void vioSetSignal (uint32_t mask, uint32_t signal) {

  vioSignalOut &= ~mask;
  vioSignalOut |=  mask & signal;

#if !defined CMSIS_VOUT
  LED_SetOut(vioSignalOut);
#endif
}

// Get signal input.
uint32_t vioGetSignal (uint32_t mask) {
  uint32_t signal;

#if !defined CMSIS_VIN
  vioSignalIn = Buttons_GetState();
#endif

  signal = vioSignalIn;

  return (signal & mask);
}

// Set value output.
void vioSetValue (uint32_t id, int32_t value) {
  uint32_t index = id;

  if (index >= VIO_VALUE_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValue[index] = value;
}

// Get value input.
int32_t vioGetValue (uint32_t id) {
  uint32_t index = id;
  int32_t  value = 0;

  if (index >= VIO_VALUE_NUM) {
    return value;                       /* return default in case of out-of-range index */
  }

  value = vioValue[index];

  return value;
}

// Set XYZ value output.
void vioSetXYZ (uint32_t id, vioValueXYZ_t valueXYZ) {
  uint32_t index = id;

  if (index >= VIO_VALUEXYZ_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValueXYZ[index] = valueXYZ;
}

// Get XYZ value input.
vioValueXYZ_t vioGetXYZ (uint32_t id) {
  uint32_t index = id;
  vioValueXYZ_t valueXYZ = {0, 0, 0};

  if (index >= VIO_VALUEXYZ_NUM) {
    return valueXYZ;                    /* return default in case of out-of-range index */
  }

  valueXYZ = vioValueXYZ[index];

  return valueXYZ;
}

// Set IPv4 address output.
void vioSetIPv4 (uint32_t id, vioAddrIPv4_t addrIPv4) {
  uint32_t index = id;

  if (index >= VIO_IPV4_ADDRESS_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioAddrIPv4[index] = addrIPv4;
}

// Get IPv4 address input.
vioAddrIPv4_t vioGetIPv4 (uint32_t id) {
  uint32_t index = id;
  vioAddrIPv4_t addrIPv4 = {0U, 0U, 0U, 0U};

  if (index >= VIO_IPV4_ADDRESS_NUM) {
    return addrIPv4;                    /* return default in case of out-of-range index */
  }

  addrIPv4 = vioAddrIPv4[index];

  return addrIPv4;
}

// Set IPv6 address output.
void vioSetIPv6 (uint32_t id, vioAddrIPv6_t addrIPv6) {
  uint32_t index = id;

  if (index >= VIO_IPV6_ADDRESS_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioAddrIPv6[index] = addrIPv6;
}

// Get IPv6 address input.
vioAddrIPv6_t vioGetIPv6 (uint32_t id) {
  uint32_t index = id;
  vioAddrIPv6_t addrIPv6 = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
                            0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};

  if (index >= VIO_IPV6_ADDRESS_NUM) {
    return addrIPv6;                    /* return default in case of out-of-range index */
  }

  addrIPv6 = vioAddrIPv6[index];

  return addrIPv6;
}
