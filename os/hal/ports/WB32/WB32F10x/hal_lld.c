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
 * @file    WB32F10x/hal_lld.c
 * @brief   WB32F10x HAL subsystem low level driver source.
 *
 * @addtogroup HAL
 * @{
 */

#include "hal.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
extern void SystemCoreClockUpdate (void);
/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */ 
// #define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0    /*!< Vector Table base offset field. 
                                     This value must be a multiple of 0x100. */


#if defined(MAINCLK_FREQ_32MHz) && (HSE_VALUE != 6000000) && (HSE_VALUE != 8000000) && (HSE_VALUE != 12000000)
  #error "The MAINCLK_FREQ_32MHz macro can only be defined if the external crystal is 6MHz/8MHz/12MHz!"
#endif

#if defined(MAINCLK_FREQ_48MHz) && (HSE_VALUE != 6000000) && (HSE_VALUE != 8000000) && (HSE_VALUE != 12000000)
  #error "The MAINCLK_FREQ_48MHz macro can only be defined if the external crystal is 6MHz/8MHz/12MHz!"
#endif

#if defined(MAINCLK_FREQ_72MHz) && (HSE_VALUE != 6000000) && (HSE_VALUE != 12000000)
  #error "The MAINCLK_FREQ_72MHz macro can only be defined if the external crystal is 6MHz/12MHz!"
#endif

#if defined(MAINCLK_FREQ_96MHz) && (HSE_VALUE != 6000000) && (HSE_VALUE != 8000000) && (HSE_VALUE != 12000000)
  #error "The MAINCLK_FREQ_96MHz macro can only be defined if the external crystal is 6MHz/8MHz/12MHz!"
#endif

#if defined(MAINCLK_FREQ_128MHz) && (HSE_VALUE != 8000000)
  #error "The MAINCLK_FREQ_128MHz macro can only be defined if the external crystal is 8MHz!"
#endif

/**
 * @brief   CMSIS system core clock variable.
 * @note    It is declared in system_wb32f10x.h.
 */
#ifdef MAINCLK_FREQ_HSE
  uint32_t SystemCoreClock = HSE_VALUE;       /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_32MHz
  uint32_t SystemCoreClock = 32000000;        /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_48MHz
  uint32_t SystemCoreClock = 48000000;        /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_72MHz
  uint32_t SystemCoreClock = 72000000;        /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_96MHz
  uint32_t SystemCoreClock = 96000000;        /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_128MHz
  uint32_t SystemCoreClock = 128000000;       /*!< System Clock Frequency (Core Clock) */
#else
  uint32_t SystemCoreClock = MHSI_VALUE;      /*!< System Clock Frequency (Core Clock) */
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level HAL driver initialization.
 *
 * @notapi
 */
void hal_lld_init(void) {
  SystemCoreClockUpdate();
}

/**
 * @brief   WB32 clocks and PLL initialization.
 * @note    All the involved constants come from the file @p board.h.
 * @note    This function should be invoked just after the system reset.
 *
 * @special
 */
#if defined(WB32F10x)
/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 *         The SystemCoreClock variable contains the core clock (HCLK), it can
 *         be used by the user application to setup the SysTick timer or configure
 *         other parameters.
 * @note   Each time the core clock (HCLK) changes, this function must be called
 *         to update SystemCoreClock variable value. Otherwise, any configuration
 *         based on this variable will be incorrect.   
 * @param  None
 * @return None
 */
void SystemCoreClockUpdate (void)
{
  uint32_t ahbprediv, pllprediv, pllmul, mainclk;

  switch (RCC->MAINCLKSRC)
  {
    case 0x00:  /* MHSI used as main clock */
      mainclk = MHSI_VALUE;
      break;
    case 0x01:  /* FHSI used as main clock */
      mainclk = FHSI_VALUE;
      break;
    case 0x03:  /* HSE used as main clock */
      mainclk = HSE_VALUE;
      break;
    case 0x02:  /* PLL used as main clock */
      pllprediv = (((RCC->PLLPRE & (RCC_PLLPRE_RATIO_Msk | RCC_PLLPRE_DIVEN)) + 1) >> 1) + 1;
      pllmul = (0x03 - ((ANCTL->PLLCR >> 6) & 0x03)) * 4 + 12;
      if (RCC->PLLSRC == RCC_PLLSRC_HSE)
      {
        mainclk = HSE_VALUE * pllmul / pllprediv;
      }
      else
      {
        mainclk = MHSI_VALUE * pllmul / pllprediv;
      }
      break;
    default:
      mainclk = MHSI_VALUE;
      break;
  }
  
  ahbprediv = (((RCC->AHBPRE & (RCC_AHBPRE_RATIO_Msk | RCC_AHBPRE_DIVEN)) + 1) >> 1) + 1;
  SystemCoreClock = mainclk / ahbprediv;
}

#ifdef MAINCLK_FREQ_96MHz
/**
 * @brief  Sets main clock frequency to 96MHz and configure AHBCLK, APB1CLK 
 *         and APB2CLK prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @return None
 */
static void SetSysClockTo96(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* Unlocks write to ANCTL registers */
  PWR->ANAKEY1 = 0x03;
  PWR->ANAKEY2 = 0x0C;

  /* APB1CLK = MAINCLK */
  RCC->APB1PRE = RCC_APB1PRE_SRCEN;
  RCC->APB1PRE |= 0x00;

  /* Configure PD0 and PD1 to analog mode */
  RCC->APB1ENR = RCC_APB1ENR_BMX1EN | RCC_APB1ENR_GPIODEN;
  GPIOD->CFGMSK = 0xFFFC;
  GPIOD->MODER = 0x0F;

  /* Enable HSE */
  ANCTL->HSECR1 = ANCTL_HSECR1_PADOEN;
  ANCTL->HSECR0 = ANCTL_HSECR0_HSEON;

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = ANCTL->HSESR & ANCTL_HSESR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if (HSEStatus != 0)
  {
    /* Configure Flash prefetch, Cache and wait state */
    CACHE->CR = CACHE_CR_CHEEN | CACHE_CR_PREFEN_ON | CACHE_CR_LATENCY_3WS;

    /* AHBCLK = MAINCLK */
    RCC->AHBPRE = 0x00;

    /* APB2CLK = MAINCLK */
    RCC->APB2PRE = RCC_APB2PRE_SRCEN;
    RCC->APB2PRE |= 0x00;

#if (WB32_HSECLK == 6000000)
    /* PLL configuration: PLLCLK = 6MHz * 16 = 96 MHz */
    RCC->PLLSRC = RCC_PLLSRC_HSE;
    RCC->PLLPRE = RCC_PLLPRE_SRCEN;
    RCC->PLLPRE |= 0x00;
    ANCTL->PLLCR = ANCTL_PLLCR_PLLMUL_16;
#elif (WB32_HSECLK == 8000000)
    /* PLL configuration: PLLCLK = 8MHz * 12 = 96 MHz */
    RCC->PLLSRC = RCC_PLLSRC_HSE;
    RCC->PLLPRE = RCC_PLLPRE_SRCEN;
    RCC->PLLPRE |= 0x00;
    ANCTL->PLLCR = ANCTL_PLLCR_PLLMUL_12;
#elif (WB32_HSECLK == 12000000)
    /* PLL configuration: PLLCLK = 12MHz / 2 * 16 = 96 MHz */
    RCC->PLLSRC = RCC_PLLSRC_HSE;
    RCC->PLLPRE = RCC_PLLPRE_SRCEN;
    RCC->PLLPRE |= RCC_PLLPRE_RATIO_2;
    RCC->PLLPRE |= RCC_PLLPRE_DIVEN;
    ANCTL->PLLCR = ANCTL_PLLCR_PLLMUL_16;
#endif

    /* Enable PLL */
    ANCTL->PLLENR = ANCTL_PLLENR_PLLON;

    /* Wait till PLL is ready */
    while(ANCTL->PLLSR != 0x03)
    {
    }

    /* Select PLL as system clock source */
    RCC->MAINCLKSRC = RCC_MAINCLKSRC_PLLCLK;
    RCC->MAINCLKUEN = RCC_MAINCLKUEN_ENA;
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    while (1);
  }

  /* Locks write to ANCTL registers */
  PWR->ANAKEY1 = 0x00;
  PWR->ANAKEY2 = 0x00;
}
#endif

#ifdef MAINCLK_FREQ_72MHz
/**
 * @brief  Sets main clock frequency to 72MHz and configure AHBCLK, APB1CLK
 *         and APB2CLK prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @return None
 */
static void SetSysClockTo72(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* Unlocks write to ANCTL registers */
  PWR->ANAKEY1 = 0x03;
  PWR->ANAKEY2 = 0x0C;

  /* APB1CLK = MAINCLK */
  RCC->APB1PRE = RCC_APB1PRE_SRCEN;
  RCC->APB1PRE |= 0x00;

  /* Configure PD0 and PD1 to analog mode */
  RCC->APB1ENR = RCC_APB1ENR_BMX1EN | RCC_APB1ENR_GPIODEN;
  GPIOD->CFGMSK = 0xFFFC;
  GPIOD->MODER = 0x0F;

  /* Enable HSE */
  ANCTL->HSECR1 = ANCTL_HSECR1_PADOEN;
  ANCTL->HSECR0 = ANCTL_HSECR0_HSEON;

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = ANCTL->HSESR & ANCTL_HSESR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if (HSEStatus != 0)
  {
    /* Configure Flash prefetch, Cache and wait state */
    CACHE->CR = CACHE_CR_CHEEN | CACHE_CR_PREFEN_ON | CACHE_CR_LATENCY_2WS;

    /* AHBCLK = MAINCLK */
    RCC->AHBPRE = 0x00;

    /* APB2CLK = MAINCLK */
    RCC->APB2PRE = RCC_APB2PRE_SRCEN;
    RCC->APB2PRE |= 0x00;

#if (WB32_HSECLK == 6000000)
    /* PLL configuration: PLLCLK = 6MHz * 12 = 72 MHz */
    RCC->PLLSRC = RCC_PLLSRC_HSE;
    RCC->PLLPRE = RCC_PLLPRE_SRCEN;
    RCC->PLLPRE |= 0x00;
    ANCTL->PLLCR = ANCTL_PLLCR_PLLMUL_12;
#elif (WB32_HSECLK == 12000000)
    /* PLL configuration: PLLCLK = 12MHz / 2 * 12 = 72 MHz */
    RCC->PLLSRC = RCC_PLLSRC_HSE;
    RCC->PLLPRE = RCC_PLLPRE_SRCEN;
    RCC->PLLPRE |= RCC_PLLPRE_RATIO_2;
    RCC->PLLPRE |= RCC_PLLPRE_DIVEN;
    ANCTL->PLLCR = ANCTL_PLLCR_PLLMUL_12;
#endif

    /* Enable PLL */
    ANCTL->PLLENR = ANCTL_PLLENR_PLLON;

    /* Wait till PLL is ready */
    while(ANCTL->PLLSR != 0x03)
    {
    }

    /* Select PLL as system clock source */
    RCC->MAINCLKSRC = RCC_MAINCLKSRC_PLLCLK;
    RCC->MAINCLKUEN = RCC_MAINCLKUEN_ENA;
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    while (1);
  }

  /* Locks write to ANCTL registers */
  PWR->ANAKEY1 = 0x00;
  PWR->ANAKEY2 = 0x00;
}
#endif

/**
 * @brief  Configures the main clock frequency, AHBCLK, APB1CLK and APB2CLK prescalers.
 * @note   This function should be used only after reset.
 * @param  None
 * @return None
 */
static void SetSysClock(void)
{
#ifdef MAINCLK_FREQ_96MHz
  SetSysClockTo96();
#elif defined MAINCLK_FREQ_72MHz
  SetSysClockTo72();
#endif
}

/*
 * Clocks initialization for all sub-families except CL.
 */
void wb32_clock_init(void) {
  /* Unlocks write to ANCTL registers */
  PWR->ANAKEY1 = 0x03;
  PWR->ANAKEY2 = 0x0C;

  /* Turn off POR */
  ANCTL->PORCR = 0x7BE;

  /* Locks write to ANCTL registers */
  PWR->ANAKEY1 = 0x00;
  PWR->ANAKEY2 = 0x00;

  SetSysClock();

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif
}
#else
 #error "not defined wb32_clock_init"
#endif

/** @} */
