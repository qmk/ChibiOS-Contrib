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

/**
 * @file    WB32F10x/hal_lld.h
 * @brief   WB32F10x HAL subsystem low level driver header.
 * @pre     This module requires the following macros to be defined in the
 *          @p board.h file:
 *          - WB32_LSECLK.
 *          - WB32_LSE_BYPASS (optionally).
 *          - WB32_HSECLK.
 *          - WB32_HSE_BYPASS (optionally).
 *          .
 *
 * @addtogroup HAL
 * @{
 */

#ifndef HAL_LLD_H
#define HAL_LLD_H

#include "wb32_registry.h"
#include "wb32f10x_rcc.h"
#include "wb32f10x_bkp.h"
#include "wb32f10x_anctl.h"
#include "wb32f10x_pwr.h"
#include "wb32_tim.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Platform identification
 * @{
 */
#define PLATFORM_NAME           "WB32F10x"

/**
 * @brief   Sub-family identifier.
 */
#if !defined(WB32F10x) || defined(__DOXYGEN__)
#define WB32F10x
#endif
/** @} */

/**
 * @name    Absolute Maximum Ratings
 * @{
 */
/**
 * @brief   Maximum system clock frequency.
 */
#define WB32_SYSCLK_MAX        128000000

/**
 * @brief   Maximum HSE clock frequency.
 */
#define WB32_HSECLK_MAX        25000000

/**
 * @brief   Minimum HSE clock frequency.
 */
#define WB32_HSECLK_MIN        1000000

/**
 * @brief   Maximum LSE clock frequency.
 */
#define WB32_LSECLK_MAX        1000000

/**
 * @brief   Minimum LSE clock frequency.
 */
#define WB32_LSECLK_MIN        32768

/**
 * @brief   Maximum PLLs input clock frequency.
 */
#define WB32_PLLIN_MAX         25000000

/**
 * @brief   Minimum PLLs input clock frequency.
 */
#define WB32_PLLIN_MIN         1000000

/**
 * @brief   Maximum PLL output clock frequency.
 */
#define WB32_PLLOUT_MAX        128000000

/**
 * @brief   Minimum PLL output clock frequency.
 */
#define WB32_PLLOUT_MIN        16000000

/**
 * @brief   Maximum APB1 clock frequency.
 */
#define WB32_PCLK1_MAX         128000000

/**
 * @brief   Maximum APB2 clock frequency.
 */
#define WB32_PCLK2_MAX         128000000

/**
 * @brief   Maximum ADC clock frequency.
 */
#define WB32_ADCCLK_MAX        14000000
/** @} */

/**
 * @name    PWR_CR register bits definitions
 * @{
 */
#define ANCTL_PVDCR_PLS_Msk             (0x7U)
#define ANCTL_PVDCR_PLS_LEV0            (0x0U)
#define ANCTL_PVDCR_PLS_LEV1            (0x1U)
#define ANCTL_PVDCR_PLS_LEV2            (0x2U)
#define ANCTL_PVDCR_PLS_LEV3            (0x3U)
#define ANCTL_PVDCR_PLS_LEV4            (0x4U)
#define ANCTL_PVDCR_PLS_LEV5            (0x5U)
#define ANCTL_PVDCR_PLS_LEV6            (0x6U)
#define ANCTL_PVDCR_PLS_LEV7            (0x7U)

#define WB32_PLS_MASK          ANCTL_PVDCR_PLS_Msk    /**< PLS bits mask.             */
#define WB32_PLS_LEV0          ANCTL_PVDCR_PLS_LEV0    /**< PVD level 0.               */
#define WB32_PLS_LEV1          ANCTL_PVDCR_PLS_LEV1    /**< PVD level 1.               */
#define WB32_PLS_LEV2          ANCTL_PVDCR_PLS_LEV2    /**< PVD level 2.               */
#define WB32_PLS_LEV3          ANCTL_PVDCR_PLS_LEV3    /**< PVD level 3.               */
#define WB32_PLS_LEV4          ANCTL_PVDCR_PLS_LEV4    /**< PVD level 4.               */
#define WB32_PLS_LEV5          ANCTL_PVDCR_PLS_LEV5    /**< PVD level 5.               */
#define WB32_PLS_LEV6          ANCTL_PVDCR_PLS_LEV6    /**< PVD level 6.               */
#define WB32_PLS_LEV7          ANCTL_PVDCR_PLS_LEV7    /**< PVD level 7.               */
/** @} */

/**
 * @name    RCC_CFGR register bits definitions
 * @{
 */
#define WB32_SW_MHSI            (0)           /**< SYSCLK source is MHSI.     */
#define WB32_SW_FHSI            (1)           /**< SYSCLK source is FHSI.     */
#define WB32_SW_PLL             (2)           /**< SYSCLK source is PLL.      */
#define WB32_SW_HSE             (3)           /**< SYSCLK source is HSE.      */

#define WB32_HPRE_MASK          (0x3FU << 1)  /**< AHP PRE source mask.       */
#define WB32_HPRE_DIV1          (0x0U)        /**< SYSCLK divided by 1.       */
#define WB32_HPRE_DIV2          (0x1U)        /**< SYSCLK divided by 2.       */
#define WB32_HPRE_DIV4          (0x5U)        /**< SYSCLK divided by 4.       */
#define WB32_HPRE_DIV8          (0xDU)        /**< SYSCLK divided by 8.       */
#define WB32_HPRE_DIV16         (0x1DU)       /**< SYSCLK divided by 16.      */
#define WB32_HPRE_DIV64         (0x7DU)       /**< SYSCLK divided by 64.      */

#define WB32_PPRE1_MASK         (0x3FU << 1) /**< APB1 PRE source mask.       */
#define WB32_PPRE1_DIV1         (0x0U)       /**< APB1 divided by 1.          */
#define WB32_PPRE1_DIV2         (0x1U)       /**< APB1 divided by 2.          */
#define WB32_PPRE1_DIV4         (0x5U)       /**< APB1 divided by 4.          */
#define WB32_PPRE1_DIV8         (0xDU)       /**< APB1 divided by 8.          */
#define WB32_PPRE1_DIV16        (0x1DU)      /**< APB1 divided by 16.         */
#define WB32_PPRE1_DIV64        (0x7DU)      /**< APB1 divided by 64.         */

#define WB32_PPRE2_MASK         (0x3FU << 1)    /**< APB2 PRE source mask.    */
#define WB32_PPRE2_DIV1         (0x0U)          /**< APB2 divided by 1.       */
#define WB32_PPRE2_DIV2         (0x1U)          /**< APB2 divided by 2.       */
#define WB32_PPRE2_DIV4         (0x5U)          /**< APB2 divided by 4.       */
#define WB32_PPRE2_DIV8         (0xDU)          /**< APB2 divided by 8.       */
#define WB32_PPRE2_DIV16        (0x1DU)         /**< APB2 divided by 16.      */
#define WB32_PPRE2_DIV64        (0x7DU)         /**< APB2 divided by 64.      */

// #define WB32_ADCPRE_DIV2       (0 << 14)   /**< PPRE2 divided by 2.        */
// #define WB32_ADCPRE_DIV4       (1 << 14)   /**< PPRE2 divided by 4.        */
// #define WB32_ADCPRE_DIV6       (2 << 14)   /**< PPRE2 divided by 6.        */
// #define WB32_ADCPRE_DIV8       (3 << 14)   /**< PPRE2 divided by 8.        */

#define WB32_PLLSRC_MHSI       (0x0U)         /**< PLL clock source is MHSI.  */
#define WB32_PLLSRC_HSE        (0x1U)         /**< PLL clock source is HSE.   */

#define WB32_PLLXPRE_MASK      (0xFU << 1)    /**< HSE PRE divided mask.      */
#define WB32_PLLXTPRE_DIV1     (0x100U)       /**< HSE divided by 1.          */
#define WB32_PLLXTPRE_DIV2     (0x101U)       /**< HSE divided by 2.          */
#define WB32_PLLXTPRE_DIV4     (0x105U)       /**< HSE divided by 4.          */
#define WB32_PLLXTPRE_DIV8     (0x10DU)       /**< HSE divided by 8.          */
#define WB32_PLLXTPRE_DIV16    (0x11DU)       /**< HSE divided by 16.         */

#define WB32_USBPRE_MASK       (0x3U << 1)    /**< USB PRE source mask.       */
#define WB32_USBPRE_DIV1       (0x0U)         /**< PLLOUT divided by 1.       */
#define WB32_USBPRE_DIV1P5     (0x5U)         /**< PLLOUT divided by 1.5.     */
#define WB32_USBPRE_DIV2       (0x1U)         /**< PLLOUT divided by 2.       */
#define WB32_USBPRE_DIV3       (0x3U)         /**< PLLOUT divided by 3.       */

#define WB32_MCOSEL_NOCLOCK    (0x0U)         /**< No clock on MCO pin.       */
#define WB32_MCOSEL_SYSCLK     (0x1U)         /**< SYSCLK on MCO pin.         */
#define WB32_MCOSEL_HSE        (0x1U << 1)    /**< HSE clock on MCO pin.      */
#define WB32_MCOSEL_MHSI       (0x1U << 2)    /**< MHSI clock on MCO pin.     */
#define WB32_MCOSEL_PLLDIV2    (0x1U << 3)    /**< PLL/2 clock on MCO pin.    */ 
#define WB32_MCOSEL_MCLK       (0x1U << 4)    /**< MCLK clock on MCO pin.     */ 
/** @} */

/**
 * @name    RCC_BDCR register bits definitions
 * @{
 */
#define WB32_RTCSEL_MASK       (3 << 8)      /**< RTC clock source mask.     */
#define WB32_RTCSEL_NOCLOCK    (0 << 8)      /**< No clock.                  */
#define WB32_RTCSEL_LSE        (1 << 8)      /**< LSE used as RTC clock.     */
#define WB32_RTCSEL_LSI        (2 << 8)      /**< LSI used as RTC clock.     */
#define WB32_RTCSEL_HSEDIV     (3 << 8)      /**< HSE divided by 128 used as
                                                 RTC clock.                 */
/** @} */

/*===========================================================================*/
/* Platform capabilities.                                                    */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   Disables the PWR/RCC initialization in the HAL.
 */
#if !defined(WB32_NO_INIT) || defined(__DOXYGEN__)
#define WB32_NO_INIT                       FALSE
#endif

/**
 * @brief   Enables or disables the programmable voltage detector.
 */
#if !defined(WB32_PVD_ENABLE) || defined(__DOXYGEN__)
#define WB32_PVD_ENABLE                    FALSE
#endif

/**
 * @brief   Sets voltage level for programmable voltage detector.
 */
#if !defined(WB32_PLS) || defined(__DOXYGEN__)
#define WB32_PLS                           WB32_PLS_LEV0
#endif

/**
 * @brief   Enables or disables the HSI8 clock source.
 */
#if !defined(WB32_MHSI_ENABLED) || defined(__DOXYGEN__)
#define WB32_MHSI_ENABLED                 TRUE
#endif

/**
 * @brief   Enables or disables the HSI48 clock source.
 */
#if !defined(WB32_FHSI_ENABLED) || defined(__DOXYGEN__)
#define WB32_FHSI_ENABLED                 FALSE
#endif

/**
 * @brief   Enables or disables the LSI clock source.
 */
#if !defined(WB32_LSI_ENABLED) || defined(__DOXYGEN__)
#define WB32_LSI_ENABLED                   FALSE
#endif

/**
 * @brief   Enables or disables the HSE clock source.
 */
#if !defined(WB32_HSE_ENABLED) || defined(__DOXYGEN__)
#define WB32_HSE_ENABLED                   TRUE
#endif

/**
 * @brief   Enables or disables the LSE clock source.
 */
#if !defined(WB32_LSE_ENABLED) || defined(__DOXYGEN__)
#define WB32_LSE_ENABLED                   FALSE
#endif

/**
 * @brief   Main clock source selection.
 * @note    If the selected clock source is not the PLL then the PLL is not
 *          initialized and started.
 * @note    The default value is calculated for a 96MHz system clock from
 *          a 8MHz crystal using the PLL.
 */
#if !defined(WB32_SW) || defined(__DOXYGEN__)
#define WB32_SW                            RCC_MAINCLKSRC_PLLCLK
#endif

/**
 * @brief   Clock source for the PLL.
 * @note    This setting has only effect if the PLL is selected as the
 *          system clock source.
 * @note    The default value is calculated for a 96MHz system clock from
 *          a 8MHz crystal using the PLL.
 */
#if !defined(WB32_PLLSRC) || defined(__DOXYGEN__)
#define WB32_PLLSRC                        RCC_PLLSRC_HSE
#endif

/**
 * @brief   Crystal PLL pre-divider.
 * @note    This setting has only effect if the PLL is selected as the
 *          system clock source.
 * @note    The default value is calculated for a 96MHz system clock from
 *          a 8MHz crystal using the PLL.
 */
#if !defined(WB32_PLLXTPRE) || defined(__DOXYGEN__)
#define WB32_PLLXTPRE              RCC_PLLPRE_DIVEN
#endif

/**
 * @brief   PLL multiplier value.
 * @note    The allowed range is 12 16 20 24.
 * @note    The default value is calculated for a 96MHz system clock from
 *          a 8MHz crystal using the PLL.
 */
#if !defined(WB32_PLLMUL_VALUE) || defined(__DOXYGEN__)
#define WB32_PLLMUL_VALUE                  ANCTL_PLLCR_PLLMUL_12
#endif

/**
 * @brief   AHB prescaler value.
 * @note    The default value is calculated for a 96MHz system clock from
 *          a 8MHz crystal using the PLL.
 */
#if !defined(WB32_HPRE) || defined(__DOXYGEN__)
#define WB32_HPRE                          RCC_AHBPRE_DIVEN
#endif

/**
 * @brief   APB1 prescaler value.
 */
#if !defined(WB32_PPRE) || defined(__DOXYGEN__)
#define WB32_PPRE                          RCC_APB1PRE_DIVEN
#endif

/**
 * @brief   MCO pin setting.
 */
#if !defined(WB32_MCOSEL) || defined(__DOXYGEN__)
#define WB32_MCOSEL                        RCC_MCOSEL_NOCLOCK
#endif

/**
 * @brief   RTC clock source.
 */
#if !defined(WB32_RTCSEL) || defined(__DOXYGEN__)
#define WB32_RTCSEL                        WB32_RTCSEL_LSI
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/



/*
 * Configuration-related checks.
 */
#if !defined(WB32F10x_MCUCONF)
#error "Using a wrong mcuconf.h file, WB32F10x_MCUCONF not defined"
#endif

/*
 * MHSI related checks.
 */
#if WB32_MHSI_ENABLED
#else /* !WB32_MHSI_ENABLED */

#if (WB32_SW == RCC_MAINCLKSRC_MHSI)
#error "MHSI not enabled, required by WB32_SW"
#endif

#if (WB32_SW == RCC_MAINCLKSRC_PLLCLK) && (WB32_PLLSRC == RCC_PLLSRC_MHSI)
#error "MHSI not enabled, required by WB32_SW and WB32_PLLSRC"
#endif

#if (WB32_MCOSEL == RCC_MCOSEL_MHSI) ||                                   \
    ((WB32_MCOSEL == RCC_MCOSEL_PLLDIV2) &&                              \
     (WB32_PLLSRC == RCC_PLLSRC_MHSI))
#error "MHSI not enabled, required by WB32_MCOSEL"
#endif
#endif

/*
 * FHSI related checks.
 */
#if WB32_FHSI_ENABLED
#else /* !WB32_FHSI_ENABLED */

#if (WB32_SW == RCC_MAINCLKSRC_FHSI)
#error "FHSI not enabled, required by WB32_SW"
#endif

#endif /* !WB32_FHSI_ENABLED */

/*
 * HSE related checks.
 */
#if WB32_HSE_ENABLED

#if WB32_HSECLK == 0
#error "HSE frequency not defined"
#elif (WB32_HSECLK < WB32_HSECLK_MIN) || (WB32_HSECLK > WB32_HSECLK_MAX)
#error "WB32_HSECLK outside acceptable range (WB32_HSECLK_MIN...WB32_HSECLK_MAX)"
#endif

#else /* !WB32_HSE_ENABLED */

#if (WB32_SW == RCC_MAINCLKSRC_HSE)
#error "HSE not enabled, required by WB32_SW"
#endif

#if ((WB32_SW == RCC_MAINCLKSRC_PLLCLK) && (WB32_PLLSRC == RCC_PLLSRC_HSE))
#error "HSE not enabled, required by WB32_SW and WB32_PLLSRC"
#endif

#if (WB32_MCOSEL == RCC_MCOSEL_HSE) ||                                   \
    ((WB32_MCOSEL == RCC_MCOSEL_PLLDIV2) &&                              \
     (WB32_PLLSRC == RCC_PLLSRC_HSE))
#error "HSE not enabled, required by WB32_MCOSEL"
#endif

#if (WB32_RTCSEL == BKP_RTCCLKSource_HSE_Div128)
#error "HSE not enabled, required by WB32_RTCSEL"
#endif

#endif /* !WB32_HSE_ENABLED */

/*
 * LSI related checks.
 */
#if WB32_LSI_ENABLED
#else /* !WB32_LSI_ENABLED */

#if (WB32_RTCSEL == WB32_RTCSEL_LSI)
#error "LSI not enabled, required by WB32_RTCSEL"
#endif

#endif /* !WB32_LSI_ENABLED */

/*
 * LSE related checks.
 */
#if WB32_LSE_ENABLED

#if (WB32_LSECLK == 0)
#error "LSE frequency not defined"
#endif

#if (WB32_LSECLK < WB32_LSECLK_MIN) || (WB32_LSECLK > WB32_LSECLK_MAX)
#error "WB32_LSECLK outside acceptable range (WB32_LSECLK_MIN...WB32_LSECLK_MAX)"
#endif

#else /* !WB32_LSE_ENABLED */

#if (WB32_RTCSEL == WB32_RTCSEL_LSE)
#error "LSE not enabled, required by WB32_RTCSEL"
#endif

#endif /* !WB32_LSE_ENABLED */

/* PLL activation conditions.*/
#if WB32_USB_CLOCK_REQUIRED ||                                             \
    (WB32_SW == RCC_MAINCLKSRC_PLLCLK) ||                                           \
    (WB32_MCOSEL == RCC_MCOSEL_PLLDIV2) ||                               \
    defined(__DOXYGEN__)
/**
 * @brief   PLL activation flag.
 */
#define WB32_ACTIVATE_PLL          TRUE
#else
#define WB32_ACTIVATE_PLL          FALSE
#endif

/* HSE prescaler setting check.*/
#if (!(WB32_PLLXTPRE & RCC_PLLPRE_RATIO_Msk)) &&  \
      (WB32_PLLXTPRE != RCC_PLLPRE_DIVEN) &&  \
      (WB32_PLLXTPRE != RCC_PLLPRE_RATIO_2)
#error "invalid WB32_PLLXTPRE value specified"
#endif

/**
 * @brief   PLLMUL field.
 */
#if ((WB32_PLLMUL_VALUE >= 12) && (WB32_PLLMUL_VALUE <= 24)) ||            \
    defined(__DOXYGEN__)
#define WB32_PLLMUL                WB32_PLLMUL_VALUE
#else
#error "invalid WB32_PLLMUL_VALUE value specified"
#endif

/**
 * @brief   PLL input clock frequency.
 */
#if (WB32_PLLSRC == RCC_PLLSRC_HSE) || defined(__DOXYGEN__)
#if (WB32_PLLXTPRE == RCC_PLLPRE_DIVEN)
#define WB32_PLLCLKIN              (WB32_HSECLK / 1)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_2)
#define WB32_PLLCLKIN              (WB32_HSECLK / 2)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_3)
#define WB32_PLLCLKIN              (WB32_HSECLK / 3)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_4)
#define WB32_PLLCLKIN              (WB32_HSECLK / 4)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_5)
#define WB32_PLLCLKIN              (WB32_HSECLK / 5)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_6)
#define WB32_PLLCLKIN              (WB32_HSECLK / 6)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_7)
#define WB32_PLLCLKIN              (WB32_HSECLK / 7)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_8)
#define WB32_PLLCLKIN              (WB32_HSECLK / 8)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_9)
#define WB32_PLLCLKIN              (WB32_HSECLK / 9)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_10)
#define WB32_PLLCLKIN              (WB32_HSECLK / 10)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_11)
#define WB32_PLLCLKIN              (WB32_HSECLK / 11)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_12)
#define WB32_PLLCLKIN              (WB32_HSECLK / 12)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_13)
#define WB32_PLLCLKIN              (WB32_HSECLK / 13)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_14)
#define WB32_PLLCLKIN              (WB32_HSECLK / 14)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_15)
#define WB32_PLLCLKIN              (WB32_HSECLK / 15)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_16)
#define WB32_PLLCLKIN              (WB32_HSECLK / 16)
#else
#error "invalid WB32_PLLPRE value specified"
#endif
#elif (WB32_PLLSRC == WB32_PLLSRC_HSI)

#if (WB32_PLLXTPRE == RCC_PLLPRE_DIVEN)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 1)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_2)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 2)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_3)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 3)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_4)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 4)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_5)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 5)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_6)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 6)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_7)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 7)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_8)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 8)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_9)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 9)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_10)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 10)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_11)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 11)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_12)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 12)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_13)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 13)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_14)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 14)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_15)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 15)
#elif (WB32_PLLXTPRE == RCC_PLLPRE_RATIO_16)
#define WB32_PLLCLKIN              (WB32_MHSICLK / 16)
#else
#error "invalid WB32_PLLPRE value specified"
#endif
#else
#error "invalid WB32_PLLSRC value specified"
#endif

/* PLL input frequency range check.*/
#if (WB32_PLLCLKIN < WB32_PLLIN_MIN) || (WB32_PLLCLKIN > WB32_PLLIN_MAX)
#error "WB32_PLLCLKIN outside acceptable range (WB32_PLLIN_MIN...WB32_PLLIN_MAX)"
#endif

/**
 * @brief   PLL output clock frequency.
 */
#define WB32_PLLCLKOUT             (WB32_PLLCLKIN * WB32_PLLMUL_VALUE)

/* PLL output frequency range check.*/
#if (WB32_PLLCLKOUT < WB32_PLLOUT_MIN) || (WB32_PLLCLKOUT > WB32_PLLOUT_MAX)
#error "WB32_PLLCLKOUT outside acceptable range (WB32_PLLOUT_MIN...WB32_PLLOUT_MAX)"
#endif

/**
 * @brief   System clock source.
 */
#if (WB32_SW == RCC_MAINCLKSRC_PLLCLK) || defined(__DOXYGEN__)
#define WB32_SYSCLK                WB32_PLLCLKOUT
#elif (WB32_SW == RCC_MAINCLKSRC_MHSI)
#define WB32_SYSCLK                WB32_MHSICLK
#elif (WB32_SW == RCC_MAINCLKSRC_FHSI)
#define WB32_SYSCLK                WB32_FHSICLK
#elif (WB32_SW == RCC_MAINCLKSRC_HSE)
#define WB32_SYSCLK                WB32_HSECLK
#else
#error "invalid WB32_SW value specified"
#endif

/* Check on the system clock.*/
#if WB32_SYSCLK > WB32_SYSCLK_MAX
#error "WB32_SYSCLK above maximum rated frequency (WB32_SYSCLK_MAX)"
#endif

/**
 * @brief   AHB frequency.
 */
#if (WB32_HPRE == RCC_AHBPRE_DIVEN) || defined(__DOXYGEN__)
#define WB32_HCLK                  (WB32_SYSCLK / 1)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_2)
#define WB32_HCLK                  (WB32_SYSCLK / 2)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_3)
#define WB32_HCLK                  (WB32_SYSCLK / 3)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_4)
#define WB32_HCLK                  (WB32_SYSCLK / 4)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_5)
#define WB32_HCLK                  (WB32_SYSCLK / 5)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_6)
#define WB32_HCLK                  (WB32_SYSCLK / 6)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_7)
#define WB32_HCLK                  (WB32_SYSCLK / 7)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_8)
#define WB32_HCLK                  (WB32_SYSCLK / 8)
#elif (WB32_HPRE == RCC_AHBPRE_RATIO_9)
#define WB32_HCLK                  (WB32_SYSCLK / 9)
#else
#error "invalid WB32_HPRE value specified"
#endif

/* AHB frequency check.*/
#if WB32_HCLK > WB32_SYSCLK_MAX
#error "WB32_HCLK exceeding maximum frequency (WB32_SYSCLK_MAX)"
#endif

/**
 * @brief   APB1 frequency.
 */
#if (WB32_PPRE1 == RCC_APB1PRE_DIVEN) || defined(__DOXYGEN__)
#define WB32_PCLK1                 (WB32_HCLK / 1)
#elif (WB32_PPRE1 == RCC_APB1PRE_RATIO_2)
#define WB32_PCLK1                 (WB32_HCLK / 2)
#elif (WB32_PPRE1 == RCC_APB1PRE_RATIO_3)
#define WB32_PCLK1                 (WB32_HCLK / 3)
#elif (WB32_PPRE1 == RCC_APB1PRE_RATIO_4)
#define WB32_PCLK1                 (WB32_HCLK / 4)
#elif (WB32_PPRE1 == RCC_APB1PRE_RATIO_5)
#define WB32_PCLK1                 (WB32_HCLK / 5)
#else
#error "invalid WB32_PPRE1 value specified"
#endif

/* APB1 frequency check.*/
#if WB32_PCLK1 > WB32_PCLK1_MAX
#error "WB32_PCLK1 exceeding maximum frequency (WB32_PCLK1_MAX)"
#endif

/**
 * @brief   APB2 frequency.
 */
#if (WB32_PPRE2 == RCC_APB2PRE_DIVEN) || defined(__DOXYGEN__)
#define WB32_PCLK2                 (WB32_HCLK / 1)
#elif (WB32_PPRE2 == RCC_APB2PRE_RATIO_2)
#define WB32_PCLK2                 (WB32_HCLK / 2)
#elif (WB32_PPRE2 == RCC_APB2PRE_RATIO_3)
#define WB32_PCLK2                 (WB32_HCLK / 3)
#elif (WB32_PPRE2 == RCC_APB2PRE_RATIO_4)
#define WB32_PCLK2                 (WB32_HCLK / 4)
#elif (WB32_PPRE2 == RCC_APB2PRE_RATIO_5)
#define WB32_PCLK2                 (WB32_HCLK / 5)
#else
#error "invalid WB32_PPRE2 value specified"
#endif

/* APB2 frequency check.*/
#if WB32_PCLK2 > WB32_PCLK2_MAX
#error "WB32_PCLK2 exceeding maximum frequency (WB32_PCLK2_MAX)"
#endif

/**
 * @brief   RTC clock.
 */
#if (WB32_RTCSEL == WB32_RTCSEL_LSE) || defined(__DOXYGEN__)
#define WB32_RTCCLK                WB32_LSECLK
#elif WB32_RTCSEL == WB32_RTCSEL_LSI
#define WB32_RTCCLK                WB32_LSICLK
#elif WB32_RTCSEL == WB32_RTCSEL_HSEDIV
#define WB32_RTCCLK                (WB32_HSECLK / 128)
#elif WB32_RTCSEL == WB32_RTCSEL_NOCLOCK
#define WB32_RTCCLK                0
#else
#error "invalid source selected for RTC clock"
#endif


/**
 * @brief   USB frequency.
 */
#if (WB32_USBPRE == WB32_USBPRE_DIV1P5) || defined(__DOXYGEN__)
#define WB32_USBCLK                ((WB32_PLLCLKOUT * 2) / 3)
#elif (WB32_USBPRE == WB32_USBPRE_DIV1)
#define WB32_USBCLK                WB32_PLLCLKOUT
#elif (WB32_USBPRE == WB32_USBPRE_DIV2)
#define WB32_USBCLK                (WB32_PLLCLKOUT / 2)
#elif (WB32_USBPRE == WB32_USBPRE_DIV3)
#define WB32_USBCLK               ( WB32_PLLCLKOUT / 3)
#else
#error "invalid WB32_USBPRE value specified"
#endif

/**
 * @brief   Timers 2, 3, 4 clock.
 */
#if (WB32_PPRE1 == RCC_APB1PRE_DIVEN) || defined(__DOXYGEN__)
#define WB32_TIMCLK1               (WB32_PCLK1 * 1)
#else
#define WB32_TIMCLK1               (WB32_PCLK1 * 2)
#endif

/**
 * @brief   Timers 1 clock.
 */
#if (WB32_PPRE2 == RCC_APB1PRE_DIVEN) || defined(__DOXYGEN__)
#define WB32_TIMCLK2               (WB32_PCLK2 * 1)
#else
#define WB32_TIMCLK2               (WB32_PCLK2 * 2)
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/* Various helpers.*/
#include "nvic.h"

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void wb32_clock_init(void);
#ifdef __cplusplus
}
#endif

#endif /* HAL_LLD_H */

/** @} */
