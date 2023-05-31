Board: Keil MCB4300
-------------------

The tables below list the device configuration for this board. This board layer is composed of components selected using the RTE (Run Time Environment) and configured by adapting:
- `startup_LPC43xx.s` (Device:Startup)
- `system_LPC43xx.c` (Device:Startup)
- `RTE_Device.h` (Device:Startup)

The heap/stack setup and the CMSIS-Driver assignment is in configuration files of related software components.

### System Configuration

| System Component        | Setting
|:------------------------|:----------------------------------------
| Device                  | LPC4357:Cortex-M4
| Board                   | MCB4300
| Heap                    | 64 kB (configured in startup file)
| Stack (MSP)             | 1 kB (configured in startup file)

### Clock Configuration

| Clock                   | Setting
|:------------------------|:----------------------------------------
| PLL0USB                 | 480 MHz
| PLL1                    | 180 MHz
| CPU                     | 180 MHz
| IDIV A                  |  60 MHz
| IDIV B                  |  25 MHz
| IDIV C                  |  12 MHz
| IDIV D                  |  12 MHz
| IDIV E                  | 5.3 MHz

**Note:** configured in system file

### GPIO Configuration and usage

| Peripheral              | Signal          | Pin      | Usage
|:------------------------|:----------------|:---------|:-----
| CAN0                    | CAN0_TD         | P3_1     | CAN0 transmit line
| CAN0                    | CAN0_RD         | P3_2     | CAN0 receive line
| ENET RMII               | ENET_TXD0       | P1_18    | DP83848 TXD_0 line
| ENET RMII               | ENET_TXD1       | P1_20    | DP83848 TXD_1 line
| ENET RMII               | ENET_TX_EN      | P0_1     | DP83848 TX_EN line
| ENET RMII               | ENET_REF_CLK    | P1_19    | DP83848 X1 line
| ENET RMII               | ENET_RXD0       | P1_15    | DP83848 RXD_0 line
| ENET RMII               | ENET_RXD1       | P0_0     | DP83848 RXD_1 line
| ENET RMII               | ENET_RX_DV      | P1_16    | DP83848 RX_DV line
| ENET MIIM               | ENET_MDIO       | P1_17    | DP83848 MDIO line
| ENET MIIM               | ENET_MDC        | PC_1     | DP83848 MDC line
| I2C0                    | I2C0_SCL        | I2C0_SCL | I2C0 serial clock line
| I2C0                    | I2C0_SDA        | I2C0_SDA | I2C0 serial data line
| I2S0                    | I2S0_RX_SCK     | P6_0     | I2S0 receive serial clock line 
| I2S0                    | I2S0_RX_WS      | P6_1     | I2S0 receive word selection line
| I2S0                    | I2S0_RX_SDA     | P6_2     | I2S0 receive serial data line
| I2S0                    | I2S0_TX_SCK     | P3_0     | I2S0 transmit serial clock line 
| I2S0                    | I2S0_TX_WS      | P7_1     | I2S0 transmit word selection line
| I2S0                    | I2S0_TX_SDA     | P7_2     | I2S0 transmit serial data line
| SD/MMC                  | SD_CLK          | PC_0     | SD Card socket CLK line
| SD/MMC                  | SD_CMD          | PC_10    | SD Card socket CMD line
| SD/MMC                  | SD_DATA0        | PC_4     | SD Card socket D0 line
| SD/MMC                  | SD_DATA1        | PC_5     | SD Card socket D1 line
| SD/MMC                  | SD_DATA2        | PC_6     | SD Card socket D2 line
| SD/MMC                  | SD_DATA3        | PC_7     | SD Card socket D3 line
| SD/MMC                  | SD_CD           | PC_8     | SD Card socket CD line
| SSP0                    | SSP0_SSEL       | PF_1     | SSP0 slave select line
| SSP0                    | SSP0_SCK        | PF_0     | SSP0 serial clock line
| SSP0                    | SSP0_MISO       | PF_2     | SSP0 master in slave out line
| SSP0                    | SSP0_MOSI       | PF_3     | SSP0 master out slave in line
| USART0                  | USART0_TX       | P2_0     | USART0 transmit line
| USART0                  | USART0_RX       | P2_1     | USART0 receive line
| USB0                    | USB0_PPWR       | P6_3     | USB0 power line (USB Host)
| USB0                    | USB0_PWR_FAULT  | P6_6     | USB0 overcurrent line (USB Host)
| USB0                    | USB0_IND0       | P8_2     | USB0 port indicator 0 line (USB Host)
| USB0                    | USB0_IND1       | P8_1     | USB0 port indicator 1 line (USB Host)
| GLCD                    | LCD_EN          | P4_6     | Graphic LCD data enable line
| GLCD                    | LCD_VSYNC       | P4_5     | Graphic LCD vertical sync line 
| GLCD                    | LCD_HSYNC       | P7_6     | Graphic LCD horizontal sync line
| GLCD                    | LCD_DOTCLK      | P4_7     | Graphic LCD dot clock signal line
| GLCD                    | LCD_BL_EN       | P7_0     | Graphic LCD backlight enable line
| GLCD                    | LCD_VD19        | P4_1     | Graphic LCD data line 1
| GLCD                    | LCD_VD20        | PB_3     | Graphic LCD data line 2
| GLCD                    | LCD_VD21        | PB_2     | Graphic LCD data line 3
| GLCD                    | LCD_VD22        | PB_1     | Graphic LCD data line 4
| GLCD                    | LCD_VD23        | PB_0     | Graphic LCD data line 5
| GLCD                    | LCD_VD10        | P4_10    | Graphic LCD data line 6
| GLCD                    | LCD_VD11        | P4_9     | Graphic LCD data line 7
| GLCD                    | LCD_VD12        | P8_3     | Graphic LCD data line 8
| GLCD                    | LCD_VD13        | PB_6     | Graphic LCD data line 9
| GLCD                    | LCD_VD14        | PB_5     | Graphic LCD data line 10
| GLCD                    | LCD_VD15        | PB_4     | Graphic LCD data line 11
| GLCD                    | LCD_VD3         | P4_2     | Graphic LCD data line 13
| GLCD                    | LCD_VD4         | P8_7     | Graphic LCD data line 14
| GLCD                    | LCD_VD5         | P8_6     | Graphic LCD data line 15
| GLCD                    | LCD_VD6         | P8_5     | Graphic LCD data line 16
| GLCD                    | LCD_VD7         | P8_4     | Graphic LCD data line 17

**Note:** configured in `RTE_Device.h`

### NVIC Configuration

| NVIC Interrupt      | Priority
|:--------------------|:--------
| C_CAN0              | 4
| Ethernet            | 4
| I2C0                | 4
| I2S0                | 4
| SDIO                | 4
| SSP0                | 4
| USART0              | 4
| USB0                | 4

### CMSIS-Driver mapping

| CMSIS-Driver | Peripheral
|:-------------|:----------
| CAN0         | C_CAN0
| ETH_MAC0     | Ethernet (ENET)
| ETH_PHY0     | DP83848 (external)
| I2C0         | I2C0
| MCI0         | SD/MMC
| SAI0         | I2S0
| SPI0         | SSP0
| USART0       | USART0
| USBD0        | USB0
| USBH0        | USB0

| CMSIS-Driver VIO  | Physical board hardware
|:------------------|:-----------------------
| vioBUTTON0        | Button P4_0
| vioBUTTON1        | Button P4_3
| vioBUTTON2        | Button P4_4
| vioBUTTON3        | Button WAKEUP0
| vioLED0           | LED PD_10
| vioLED1           | LED PD_11
| vioLED2           | LED PD_12
| vioLED3           | LED PD_13
| vioLED4           | LED PD_14
| vioLED5           | LED P9_0
| vioLED6           | LED P9_1
| vioLED7           | LED P9_2
| virtual terminal  | Graphic LCD

**STDIO** is routed to ITM
