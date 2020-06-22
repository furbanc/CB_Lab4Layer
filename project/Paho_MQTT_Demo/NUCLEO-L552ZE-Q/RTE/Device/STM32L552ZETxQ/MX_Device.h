/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 19/05/2020 11:43:31
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            32000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            16000000
#define MX_HSE_VALUE                            16000000
#define MX_SYSCLKFreq_VALUE                     110000000
#define MX_HCLKFreq_Value                       110000000
#define MX_FCLKCortexFreq_Value                 110000000
#define MX_CortexFreq_Value                     110000000
#define MX_AHBFreq_Value                        110000000
#define MX_APB1Freq_Value                       110000000
#define MX_APB2Freq_Value                       110000000
#define MX_APB1TimFreq_Value                    110000000
#define MX_APB2TimFreq_Value                    110000000
#define MX_PWRFreq_Value                        110000000
#define MX_RTCFreq_Value                        32000
#define MX_USBFreq_Value                        16000000
#define MX_WatchDogFreq_Value                   32000
#define MX_MCO1PinFreq_Value                    110000000

/*-------------------------------- DMA        --------------------------------*/

#define MX_DMA                                  1

/* NVIC Configuration */

/* NVIC DMA1_Channel1_IRQn */
#define MX_DMA1_Channel1_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Channel1_IRQn_PriorityGroup     NVIC_PRIORITYGROUP_3
#define MX_DMA1_Channel1_IRQn_Subriority        0

/* NVIC DMA1_Channel2_IRQn */
#define MX_DMA1_Channel2_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Channel2_IRQn_PriorityGroup     NVIC_PRIORITYGROUP_3
#define MX_DMA1_Channel2_IRQn_Subriority        0

/*-------------------------------- ICACHE     --------------------------------*/

#define MX_ICACHE                               1

/* GPIO Configuration */

/*-------------------------------- PWR        --------------------------------*/

#define MX_PWR                                  1

/* GPIO Configuration */

/*-------------------------------- SPI1       --------------------------------*/

#define MX_SPI1                                 1

/* GPIO Configuration */

/* Pin PA6 */
#define MX_SPI1_MISO_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI1_MISO_Pin                        PA6
#define MX_SPI1_MISO_GPIOx                      GPIOA
#define MX_SPI1_MISO_GPIO_PuPd                  GPIO_NOPULL
#define MX_SPI1_MISO_GPIO_Pin                   GPIO_PIN_6
#define MX_SPI1_MISO_GPIO_AF                    GPIO_AF5_SPI1
#define MX_SPI1_MISO_GPIO_Mode                  GPIO_MODE_AF_PP

/* Pin PA7 */
#define MX_SPI1_MOSI_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI1_MOSI_Pin                        PA7
#define MX_SPI1_MOSI_GPIOx                      GPIOA
#define MX_SPI1_MOSI_GPIO_PuPd                  GPIO_NOPULL
#define MX_SPI1_MOSI_GPIO_Pin                   GPIO_PIN_7
#define MX_SPI1_MOSI_GPIO_AF                    GPIO_AF5_SPI1
#define MX_SPI1_MOSI_GPIO_Mode                  GPIO_MODE_AF_PP

/* Pin PA5 */
#define MX_SPI1_SCK_GPIO_Speed                  GPIO_SPEED_FREQ_VERY_HIGH
#define MX_SPI1_SCK_Pin                         PA5
#define MX_SPI1_SCK_GPIOx                       GPIOA
#define MX_SPI1_SCK_GPIO_PuPd                   GPIO_NOPULL
#define MX_SPI1_SCK_GPIO_Pin                    GPIO_PIN_5
#define MX_SPI1_SCK_GPIO_AF                     GPIO_AF5_SPI1
#define MX_SPI1_SCK_GPIO_Mode                   GPIO_MODE_AF_PP

/* DMA Configuration */

/* DMA SPI1_RX */
#define MX_SPI1_RX_DMA_Instance                 DMA1_Channel1
#define MX_SPI1_RX_DMA_Priority                 DMA_PRIORITY_LOW
#define MX_SPI1_RX_DMA_MemDataAlignment         DMA_MDATAALIGN_BYTE
#define MX_SPI1_RX_DMA_Mode                     DMA_NORMAL
#define MX_SPI1_RX_DMA_SyncRequestNumber        1
#define MX_SPI1_RX_DMA_Request                  DMA_REQUEST_SPI1_RX
#define MX_SPI1_RX_DMA_SyncPolarity             HAL_DMAMUX_SYNC_NO_EVENT
#define MX_SPI1_RX_DMA_Channel_PRIV_NPRIV       DMA_CHANNEL_NPRIV_DISABLE
#define MX_SPI1_RX_DMA_Direction                DMA_PERIPH_TO_MEMORY
#define MX_SPI1_RX_DMA_SignalID                 NONE
#define MX_SPI1_RX_DMA_MemInc                   DMA_MINC_ENABLE
#define MX_SPI1_RX_DMA_IpInstance               
#define MX_SPI1_RX_DMA_RequestNumber            1
#define MX_SPI1_RX_DMA_EventEnable              DISABLE
#define MX_SPI1_RX_DMA_SyncEnable               DISABLE
#define MX_SPI1_RX_DMA_Src_SEC_NSEC             NONE
#define MX_SPI1_RX_DMA_DMA_Handle               
#define MX_SPI1_RX_DMA_PeriphDataAlignment      DMA_PDATAALIGN_BYTE
#define MX_SPI1_RX_DMA_Channel_SEC_NSEC         NONE
#define MX_SPI1_RX_DMA_Polarity                 HAL_DMAMUX_REQ_GEN_RISING
#define MX_SPI1_RX_DMA_SyncSignalID             NONE
#define MX_SPI1_RX_DMA_PeriphInc                DMA_PINC_DISABLE
#define MX_SPI1_RX_DMA_Dest_SEC_NSEC            NONE

/* DMA SPI1_TX */
#define MX_SPI1_TX_DMA_Instance                 DMA1_Channel2
#define MX_SPI1_TX_DMA_Priority                 DMA_PRIORITY_LOW
#define MX_SPI1_TX_DMA_MemDataAlignment         DMA_MDATAALIGN_BYTE
#define MX_SPI1_TX_DMA_Mode                     DMA_NORMAL
#define MX_SPI1_TX_DMA_SyncRequestNumber        1
#define MX_SPI1_TX_DMA_Request                  DMA_REQUEST_SPI1_TX
#define MX_SPI1_TX_DMA_SyncPolarity             HAL_DMAMUX_SYNC_NO_EVENT
#define MX_SPI1_TX_DMA_Channel_PRIV_NPRIV       DMA_CHANNEL_NPRIV_DISABLE
#define MX_SPI1_TX_DMA_Direction                DMA_MEMORY_TO_PERIPH
#define MX_SPI1_TX_DMA_SignalID                 NONE
#define MX_SPI1_TX_DMA_MemInc                   DMA_MINC_ENABLE
#define MX_SPI1_TX_DMA_IpInstance               
#define MX_SPI1_TX_DMA_RequestNumber            1
#define MX_SPI1_TX_DMA_EventEnable              DISABLE
#define MX_SPI1_TX_DMA_SyncEnable               DISABLE
#define MX_SPI1_TX_DMA_Src_SEC_NSEC             NONE
#define MX_SPI1_TX_DMA_DMA_Handle               
#define MX_SPI1_TX_DMA_PeriphDataAlignment      DMA_PDATAALIGN_BYTE
#define MX_SPI1_TX_DMA_Channel_SEC_NSEC         NONE
#define MX_SPI1_TX_DMA_Polarity                 HAL_DMAMUX_REQ_GEN_RISING
#define MX_SPI1_TX_DMA_SyncSignalID             NONE
#define MX_SPI1_TX_DMA_PeriphInc                DMA_PINC_DISABLE
#define MX_SPI1_TX_DMA_Dest_SEC_NSEC            NONE

/* NVIC Configuration */

/* NVIC SPI1_IRQn */
#define MX_SPI1_IRQn_interruptPremptionPriority 0
#define MX_SPI1_IRQn_PriorityGroup              NVIC_PRIORITYGROUP_3
#define MX_SPI1_IRQn_Subriority                 0

/*-------------------------------- SYS        --------------------------------*/

#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- USART3     --------------------------------*/

#define MX_USART3                               1

#define MX_USART3_VM                            VM_ASYNC

/* GPIO Configuration */

/* Pin PD8 */
#define MX_USART3_TX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART3_TX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART3_TX_Pin                        PD8
#define MX_USART3_TX_GPIOx                      GPIOD
#define MX_USART3_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART3_TX_GPIO_Pin                   GPIO_PIN_8
#define MX_USART3_TX_GPIO_AF                    GPIO_AF7_USART3

/* Pin PD9 */
#define MX_USART3_RX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART3_RX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART3_RX_Pin                        PD9
#define MX_USART3_RX_GPIOx                      GPIOD
#define MX_USART3_RX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART3_RX_GPIO_Pin                   GPIO_PIN_9
#define MX_USART3_RX_GPIO_AF                    GPIO_AF7_USART3

/* NVIC Configuration */

/* NVIC USART3_IRQn */
#define MX_USART3_IRQn_interruptPremptionPriority 0
#define MX_USART3_IRQn_PriorityGroup            NVIC_PRIORITYGROUP_3
#define MX_USART3_IRQn_Subriority               0

/*-------------------------------- NVIC       --------------------------------*/

#define MX_NVIC                                 1

/*-------------------------------- GPIO       --------------------------------*/

#define MX_GPIO                                 1

/* GPIO Configuration */

/* Pin PD14 */
#define MX_PD14_GPIO_Speed                      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_PD14_Pin                             PD14
#define MX_PD14_GPIOx                           GPIOD
#define MX_PD14_PinState                        GPIO_PIN_SET
#define MX_PD14_GPIO_PuPd                       GPIO_NOPULL
#define MX_ARDUINO_SPI_A_CS                     PD14
#define MX_PD14_GPIO_Pin                        GPIO_PIN_14
#define MX_PD14_GPIO_ModeDefaultOutputPP        GPIO_MODE_OUTPUT_PP

/* Pin PD15 */
#define MX_PD15_Pin                             PD15
#define MX_PD15_GPIOx                           GPIOD
#define MX_PD15_GPIO_PuPd                       GPIO_NOPULL
#define MX_ARDUINO_IO_D9                        PD15
#define MX_PD15_GPIO_Pin                        GPIO_PIN_15
#define MX_PD15_GPIO_Mode                       GPIO_MODE_INPUT

#endif  /* __MX_DEVICE_H */

