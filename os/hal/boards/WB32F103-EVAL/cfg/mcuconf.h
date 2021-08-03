/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef MCUCONF_H
#define MCUCONF_H

#define WB32F10x_MCUCONF  TRUE

/*
 * WB32F103 drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 15...0       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

/**
 * @name    Internal clock sources
 * @{
 */
#define WB32_HSECLK            HSE_VALUE
#define WB32_MHSICLK           MHSI_VALUE     /**< High speed internal clock. */
#define WB32_FHSICLK           FHSI_VALUE     /**< High speed internal clock. */
#define WB32_LSICLK            32000          /**< Low speed internal clock.  */
#define WB32_LSECLK            32768          /**< High speed internal clock.  */

/*
 * HAL driver system settings.
 */
#define MAINCLK_FREQ_96MHz                 TRUE

#define WB32_NO_INIT                       FALSE
#define WB32_MHSI_ENABLED                  TRUE
#define WB32_FHSI_ENABLED                  FALSE
#define WB32_LSI_ENABLED                   FALSE
#define WB32_HSE_ENABLED                   TRUE
#define WB32_LSE_ENABLED                   FALSE
#define WB32_SW                            RCC_MAINCLKSRC_PLLCLK
#define WB32_PLLSRC                        RCC_PLLSRC_HSE
#define WB32_PLLXTPRE                      RCC_PLLPRE_DIVEN
#define WB32_PLLMUL_VALUE                  12     //The allowed range is 12,16,20,24.

#define WB32_HPRE                          RCC_AHBPRE_DIVEN
#define WB32_PPRE                          RCC_APB1PRE_DIVEN
#define WB32_PPRE1                         RCC_APB1PRE_DIVEN
#define WB32_PPRE2                         RCC_APB2PRE_DIVEN
#define WB32_MCOSEL                        RCC_MCOSEL_NOCLOCK
#define WB32_RTCSEL                        WB32_RTCSEL_NOCLOCK
#define WB32_PVD_ENABLE                    FALSE
#define WB32_PLS                           WB32_PLS_LEV0

/*
 * IRQ system settings.
 */
#define WB32_IRQ_EXTI0_PRIORITY            6
#define WB32_IRQ_EXTI1_PRIORITY            6
#define WB32_IRQ_EXTI2_PRIORITY            6
#define WB32_IRQ_EXTI3_PRIORITY            6
#define WB32_IRQ_EXTI4_PRIORITY            6
#define WB32_IRQ_EXTI5_9_PRIORITY          6
#define WB32_IRQ_EXTI10_15_PRIORITY        6
#define WB32_IRQ_EXTI16_PRIORITY           6
#define WB32_IRQ_EXTI17_PRIORITY           6
#define WB32_IRQ_EXTI18_PRIORITY           6
#define WB32_IRQ_EXTI19_PRIORITY           6

/*
 * ADC driver system settings.
 */
#define WB32_ADC_USE_ADC1                  FALSE
#define WB32_ADC_ADC1_DMA_PRIORITY         2
#define WB32_ADC_ADC1_IRQ_PRIORITY         6

/*
 * CAN driver system settings.
 */
#define WB32_CAN_USE_CAN1                  FALSE
#define WB32_CAN_CAN1_IRQ_PRIORITY         11

/*
 * GPT driver system settings.
 */
#define WB32_GPT_USE_TIM1                  FALSE
#define WB32_GPT_USE_TIM2                  FALSE
#define WB32_GPT_USE_TIM3                  FALSE
#define WB32_GPT_USE_TIM4                  FALSE
#define WB32_GPT_USE_TIM5                  FALSE
#define WB32_GPT_USE_TIM8                  FALSE
#define WB32_GPT_TIM1_IRQ_PRIORITY         7
#define WB32_GPT_TIM2_IRQ_PRIORITY         7
#define WB32_GPT_TIM3_IRQ_PRIORITY         7
#define WB32_GPT_TIM4_IRQ_PRIORITY         7
#define WB32_GPT_TIM5_IRQ_PRIORITY         7
#define WB32_GPT_TIM8_IRQ_PRIORITY         7

/*
 * I2C driver system settings.
 */
#define WB32_I2C_USE_I2C1                  FALSE
#define WB32_I2C_USE_I2C2                  TRUE
#define WB32_I2C_BUSY_TIMEOUT              50
#define WB32_I2C_I2C1_IRQ_PRIORITY         5
#define WB32_I2C_I2C2_IRQ_PRIORITY         5
#define WB32_I2C_I2C1_DMA_PRIORITY         3
#define WB32_I2C_I2C2_DMA_PRIORITY         3
#define WB32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 */
#define WB32_ICU_USE_TIM1                  FALSE
#define WB32_ICU_USE_TIM2                  FALSE
#define WB32_ICU_USE_TIM3                  FALSE
#define WB32_ICU_USE_TIM4                  FALSE
#define WB32_ICU_USE_TIM5                  FALSE
#define WB32_ICU_USE_TIM8                  FALSE
#define WB32_ICU_TIM1_IRQ_PRIORITY         7
#define WB32_ICU_TIM2_IRQ_PRIORITY         7
#define WB32_ICU_TIM3_IRQ_PRIORITY         7
#define WB32_ICU_TIM4_IRQ_PRIORITY         7
#define WB32_ICU_TIM5_IRQ_PRIORITY         7
#define WB32_ICU_TIM8_IRQ_PRIORITY         7

/*
 * PWM driver system settings.
 */
#define WB32_PWM_USE_ADVANCED              FALSE
#define WB32_PWM_USE_TIM1                  FALSE
#define WB32_PWM_USE_TIM2                  FALSE
#define WB32_PWM_USE_TIM3                  FALSE
#define WB32_PWM_USE_TIM4                  FALSE
#define WB32_PWM_USE_TIM5                  FALSE
#define WB32_PWM_USE_TIM8                  FALSE
#define WB32_PWM_TIM1_IRQ_PRIORITY         7
#define WB32_PWM_TIM2_IRQ_PRIORITY         7
#define WB32_PWM_TIM3_IRQ_PRIORITY         7
#define WB32_PWM_TIM4_IRQ_PRIORITY         7
#define WB32_PWM_TIM5_IRQ_PRIORITY         7
#define WB32_PWM_TIM8_IRQ_PRIORITY         7

/*
 * RTC driver system settings.
 */
#define WB32_RTC_IRQ_PRIORITY              15

/*
 * SERIAL driver system settings.
 */
#define WB32_SERIAL_USE_USART1             FALSE
#define WB32_SERIAL_USE_USART2             FALSE
#define WB32_SERIAL_USE_USART3             FALSE
#define WB32_SERIAL_USE_UART4              FALSE
#define WB32_SERIAL_USE_UART5              FALSE
#define WB32_SERIAL_USART1_PRIORITY        12
#define WB32_SERIAL_USART2_PRIORITY        12
#define WB32_SERIAL_USART3_PRIORITY        12
#define WB32_SERIAL_UART4_PRIORITY         12
#define WB32_SERIAL_UART5_PRIORITY         12

/*
 * SPI driver system settings.
 */
#define WB32_SPI_USE_QSPI                   TRUE
#define WB32_SPI_USE_SPIM2                  FALSE
#define WB32_SPI_USE_SPIS1                  FALSE
#define WB32_SPI_USE_SPIS2                  FALSE
#define WB32_SPI_QSPI_DMA_PRIORITY           1
#define WB32_SPI_SPIM2_DMA_PRIORITY          1
#define WB32_SPI_SPIS1_DMA_PRIORITY          1
#define WB32_SPI_SPIS2_DMA_PRIORITY          1
#define WB32_SPI_QSPI_IRQ_PRIORITY          10
#define WB32_SPI_SPIM2_IRQ_PRIORITY         10
#define WB32_SPI_SPIS1_IRQ_PRIORITY         10
#define WB32_SPI_SPIS2_IRQ_PRIORITY         10
#define WB32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define WB32_ST_IRQ_PRIORITY               8
#define WB32_ST_USE_TIMER                  2

/*
 * UART driver system settings.
 */
#define WB32_UART_USE_USART1               TRUE
#define WB32_UART_USE_USART2               FALSE
#define WB32_UART_USE_USART3               FALSE
#define WB32_UART_UART1_IRQ_PRIORITY      12
#define WB32_UART_UART2_IRQ_PRIORITY      12
#define WB32_UART_UART3_IRQ_PRIORITY      12
#define WB32_UART_UART1_DMA_PRIORITY      0
#define WB32_UART_UART2_DMA_PRIORITY      0
#define WB32_UART_UART3_DMA_PRIORITY      0
#define WB32_UART_DMA_ERROR_HOOK(uartp)    osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 */
#define WB32_USB_USE_USB1                  TRUE
#define WB32_USB_LOW_POWER_ON_SUSPEND      FALSE
#define WB32_USB_USB1_IRQ_PRIORITY         13
#define WB32_USB_USB1_DMA_IRQ_PRIORITY     14
#define WB32_USB_HOST_WAKEUP_DURATION      2
#define WB32_USBPRE                        WB32_USBPRE_DIV2

/*
 * WDG driver system settings.
 */
#define WB32_WDG_USE_IWDG                  FALSE

#endif /* MCUCONF_H */
