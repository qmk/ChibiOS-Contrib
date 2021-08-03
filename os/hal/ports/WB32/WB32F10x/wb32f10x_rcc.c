/**
 * @file    wb32f10x_rcc.c
 * @author  WestberryTech Application Team
 * @version V0.1.5
 * @date    18-February-2021
 * @brief   This file provides all the RCC firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32f10x_rcc.h"

/** @addtogroup WB32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC
  * @brief RCC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Private_Functions
  * @{
  */

/**
 * @brief  Configures the PLL clock source.
 * @param  RCC_PLLSource: specifies the PLL entry clock source.
 *    This parameter can be RCC_PLLSource_HSE_Divx or RCC_PLLSource_MHSI_Divx where x:[1, 16]
 * @param  NewState: new state of the PLL source clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_PLLSourceConfig(uint32_t RCC_PLLSource, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->PLLSRC = RCC_PLLSource >> 8;
    RCC->PLLPRE = RCC_PLLPRE_SRCEN;
    RCC->PLLPRE |= (RCC_PLLSource & RCC_PLLPRE_RATIO_Msk);
    RCC->PLLPRE |= (RCC_PLLSource & RCC_PLLPRE_DIVEN);
  }
  else {
    RCC->PLLPRE &= RCC_PLLPRE_SRCEN;
    RCC->PLLPRE = 0x00;
  }
}

/**
 * @brief  Configures the main clock (MAINCLK).
 * @param  RCC_MAINCLKSource: specifies the clock source used as main clock.
 *    This parameter can be one of the following values:
 *      @arg RCC_MAINCLKSource_MHSI: MHSI selected as main clock
 *      @arg RCC_MAINCLKSource_FHSI: FHSI selected as main clock
 *      @arg RCC_MAINCLKSource_PLLCLK: PLL selected as main clock
 *      @arg RCC_MAINCLKSource_HSE: HSE selected as main clock
 * @return None
 */
void RCC_MAINCLKConfig(uint32_t RCC_MAINCLKSource)
{
  RCC->MAINCLKSRC = RCC_MAINCLKSource;
  RCC->MAINCLKUEN = RCC_MAINCLKUEN_ENA;
}

/**
 * @brief  Configures the USB clock (USBCLK).
 * @param  RCC_USBCLKSource: specifies the USB clock source..
 *    This parameter can be one of the following values:
 *      @arg RCC_USBCLKSource_MAINCLK_Div1: main clock selected as USB clock source
 *      @arg RCC_USBCLKSource_MAINCLK_1Div5: main clock divided by 1.5 selected as USB clock source
 *      @arg RCC_USBCLKSource_MAINCLK_Div2: main clock divided by 2 selected as USB clock source
 *      @arg RCC_USBCLKSource_MAINCLK_Div3: main clock divided by 3 selected as USB clock source
 * @param  NewState: new state of the USB clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->USBCLKENR = RCC_USBCLKENR_CLKEN;
    RCC->USBPRE = RCC_USBPRE_SRCEN;
    RCC->USBPRE |= (RCC_USBCLKSource & RCC_USBPRE_RATIO_Msk);
    RCC->USBPRE |= (RCC_USBCLKSource & RCC_USBPRE_DIVEN);
  }
  else {
    RCC->USBPRE &= RCC_USBPRE_SRCEN;
    RCC->USBPRE = 0x00;
    RCC->USBCLKENR = 0x00;
  }
}

/**
 * @brief  Configures the AHB clock (AHBCLK).
 * @param  RCC_MAINCLK: defines the AHB clock divider. This clock is derived from
 *    the main clock (MAINCLK).
 *    This parameter can be RCC_MAINCLK_Divx where x:[1, 64]
 * @return None
 */
void RCC_AHBCLKConfig(uint32_t RCC_MAINCLK)
{
  RCC->AHBPRE = RCC_MAINCLK & RCC_AHBPRE_RATIO_Msk;
  RCC->AHBPRE |= (RCC_MAINCLK & RCC_AHBPRE_DIVEN);
}

/**
 * @brief  Configures the APB1 clock (APB1CLK).
 * @param  RCC_MAINCLK: defines the APB1 clock divider. This clock is derived from
 *    the main clock (MAINCLK).
 *    This parameter can be RCC_MAINCLK_Divx where x:[1, 64]
 * @param  NewState: new state of the APB1 clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_APB1CLKConfig(uint32_t RCC_MAINCLK, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->APB1PRE = RCC_APB1PRE_SRCEN;
    RCC->APB1PRE |= (RCC_MAINCLK & RCC_APB1PRE_RATIO_Msk);
    RCC->APB1PRE |= (RCC_MAINCLK & RCC_APB1PRE_DIVEN);
  }
  else {
    RCC->APB1PRE &= RCC_APB1PRE_SRCEN;
    RCC->APB1PRE = 0x00;
  }
}

/**
 * @brief  Configures the APB2 clock (APB2CLK).
 * @param  RCC_MAINCLK: defines the APB2 clock divider. This clock is derived from
 *    the main clock (MAINCLK).
 *    This parameter can be RCC_MAINCLK_Divx where x:[1, 64]
 * @param  NewState: new state of the APB2 clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_APB2CLKConfig(uint32_t RCC_MAINCLK, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->APB2PRE = RCC_APB2PRE_SRCEN;
    RCC->APB2PRE |= (RCC_MAINCLK & RCC_APB2PRE_RATIO_Msk);
    RCC->APB2PRE |= (RCC_MAINCLK & RCC_APB2PRE_DIVEN);
  }
  else {
    RCC->APB2PRE &= RCC_APB2PRE_SRCEN;
    RCC->APB2PRE = 0x00;
  }
}

/**
 * @brief  Configures the I2S MCLK clock (MCLK).
 * @param  RCC_MCLKSource: specifies the I2S MCLK clock source..
 *    This parameter can be RCC_MCLKSource_MAINCLK_Divx or RCC_MCLKSource_FHSI_Divx where x:[1, 64]
 * @param  NewState: new state of the I2S MCLK clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_MCLKConfig(uint32_t RCC_MCLKSource, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->MCLKSRC = RCC_MCLKSource >> 8;
    RCC->MCLKPRE = RCC_MCLKPRE_SRCEN;
    RCC->MCLKPRE |= (RCC_MCLKSource & RCC_MCLKPRE_RATIO_Msk);
    RCC->MCLKPRE |= (RCC_MCLKSource & RCC_MCLKPRE_DIVEN);
  }
  else {
    RCC->MCLKPRE &= RCC_MCLKPRE_SRCEN;
    RCC->MCLKPRE = 0x00;
  }
}

/**
 * @brief  Configures the I2S SCLK clock (I2SCLK).
 * @param  RCC_MCLK: defines the I2S SCLK clock divider. This clock is derived from
 *    the MCLK clock (MCLK).
 *    This parameter can be RCC_MCLK_Divx where x:[1, 512]
 * @param  NewState: new state of the I2S SCLK clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_I2SCLKConfig(uint32_t RCC_MCLK, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->I2SPRE = RCC_I2SPRE_SRCEN;
    RCC->I2SPRE |= (RCC_MCLK & RCC_I2SPRE_RATIO_Msk);
    RCC->I2SPRE |= (RCC_MCLK & RCC_I2SPRE_DIVEN);
    RCC->I2SCLKENR = RCC_I2SCLKENR_CLKEN;
  }
  else {
    RCC->I2SCLKENR = 0x00;
    RCC->I2SPRE &= RCC_I2SPRE_SRCEN;
    RCC->I2SPRE = 0x00;
  }
}

/**
 * @brief  Forces or releases the I2S SCLK clock domain reset.
 * @param  NewState: new state of the I2S SCLK clock domain reset.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_I2SCLKResetCmd(FunctionalState NewState)
{
  RCC->I2SCLKRSTR = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the RNG clock (RNGCLK).
 * @param  NewState: new state of the RNG clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_RNGCLKCmd(FunctionalState NewState)
{
  RCC->RNGCLKENR = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the IWDG clock (IWDGCLK).
 * @note   This switch is invalid if the IWDG is running.
 * @param  NewState: new state of the IWDG clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_IWDGCLKCmd(FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->IWDGCLKENR |= RCC_IWDGCLKENR_IWDGCLKEN;
  }
  else {
    RCC->IWDGCLKENR &= ~RCC_IWDGCLKENR_IWDGCLKEN;
  }
}

/**
 * @brief  Enables or disables the DCSS clock.
 * @param  NewState: new state of the DCSS clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_DCSSCLKCmd(FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->IWDGCLKENR |= RCC_IWDGCLKENR_DCSSCLKEN;
  }
  else {
    RCC->IWDGCLKENR &= ~RCC_IWDGCLKENR_DCSSCLKEN;
  }
}

/**
 * @brief  Enables or disables the SPIS1 clock (SPIS1CLK).
 * @param  NewState: new state of the SPIS1 clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_SPIS1CLKCmd(FunctionalState NewState)
{
  RCC->SPIS1CLKENR = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the SPIS2 clock (SPIS2CLK).
 * @param  NewState: new state of the SPIS2 clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_SPIS2CLKCmd(FunctionalState NewState)
{
  RCC->SPIS2CLKENR = (uint32_t)NewState;
}

/**
 * @brief  Configures the USB FIFO clock (USBFIFOCLK).
 * @param  RCC_USBFIFOCLKSource: specifies the USB FIFO clock source.
 *    This parameter can be one of the following values:
 *      @arg RCC_USBFIFOCLKSource_AHBCLK: AHB clock selected as USB FIFO clock source
 *      @arg RCC_USBFIFOCLKSource_USBCLK: USB clock selected as USB FIFO clock source
 * @return None
 */
void RCC_USBFIFOCLKConfig(uint32_t RCC_USBFIFOCLKSource)
{
  RCC->USBFIFOCLKSRC = RCC_USBFIFOCLKSource;
}

/**
 * @brief  Enables or disables the USB FIFO clock (USBFIFOCLK).
 * @param  NewState: new state of the USB FIFO clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_USBFIFOCLKCmd(FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->USBFIFOCLKENR = RCC_USBFIFOCLKENR_CLKEN;
  }
  else {
    RCC->USBFIFOCLKENR = 0x0000;
  }
}

/**
 * @brief  Selects the clock source to output on MCO pin.
 * @param  RCC_MCO: specifies the clock source to output.
 *    This parameter can be one of the following values:
 *      @arg RCC_MCO_NoClock: No clock selected
 *      @arg RCC_MCO_AHBCLK: AHB clock selected
 *      @arg RCC_MCO_HSE: HSE oscillator clock selected
 *      @arg RCC_MCO_MHSI: MHSI oscillator clock selected
 *      @arg RCC_MCO_PLLCLK_Div2: PLL clock divided by 2 selected
 *      @arg RCC_MCO_MCLK: I2S MCLK clock selected
 * @return None
 */
void RCC_MCOConfig(uint32_t RCC_MCO)
{
  RCC->MCOSEL = 0x0000;
  RCC->MCOSEL = RCC_MCO;
}

/**
 * @brief  Returns the frequencies of different on chip clocks.
 * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
 *         the clocks frequencies.
 * @return None
 */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  uint32_t mainclk;
  uint32_t pllprediv, pllmul;
  uint32_t ahbprediv, apb1prediv, apb2prediv;

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
  apb1prediv = (((RCC->APB1PRE & (RCC_APB1PRE_RATIO_Msk | RCC_APB1PRE_DIVEN)) + 1) >> 1) + 1;
  apb2prediv = (((RCC->APB2PRE & (RCC_APB2PRE_RATIO_Msk | RCC_APB2PRE_DIVEN)) + 1) >> 1) + 1;

  RCC_Clocks->MAINCLK_Frequency = mainclk;
  RCC_Clocks->AHBCLK_Frequency = mainclk / ahbprediv;
  RCC_Clocks->APB1CLK_Frequency = mainclk / apb1prediv;
  RCC_Clocks->APB2CLK_Frequency = mainclk / apb2prediv;
}

/**
 * @brief  Enables or disables the AHB peripheral clock.
 * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
 *    This parameter can be any combination of the following values:
 *      @arg RCC_AHBPeriph_IWDG
 *      @arg RCC_AHBPeriph_USB
 *      @arg RCC_AHBPeriph_ISO
 *      @arg RCC_AHBPeriph_FLASH
 *      @arg RCC_AHBPeriph_CACHE
 *      @arg RCC_AHBPeriph_SYS
 *      @arg RCC_AHBPeriph_DMAC1Bridge
 *      @arg RCC_AHBPeriph_DMAC2Bridge
 *      @arg RCC_AHBPeriph_CRC_SFM
 *      @arg RCC_AHBPeriph_BKP
 * @param  NewState: new state of the specified peripheral clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->AHBENR0 |= RCC_AHBPeriph & 0xFF;
    RCC->AHBENR1 |= (RCC_AHBPeriph >> 8) & 0xFFFF;
    RCC->AHBENR2 |= RCC_AHBPeriph >> 24;
  }
  else {
    RCC->AHBENR0 &= ~(RCC_AHBPeriph & 0xFF);
    RCC->AHBENR1 &= ~((RCC_AHBPeriph >> 8) & 0xFFFF);
    RCC->AHBENR2 &= ~(RCC_AHBPeriph >> 24);
  }
}

/**
 * @brief  Enables or disables the APB1 peripheral clock.
 * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
 *    This parameter can be any combination of the following values:
 *      @arg RCC_APB1Periph_DMAC1
 *      @arg RCC_APB1Periph_TIM1
 *      @arg RCC_APB1Periph_TIM2
 *      @arg RCC_APB1Periph_TIM3
 *      @arg RCC_APB1Periph_TIM4
 *      @arg RCC_APB1Periph_GPIOA
 *      @arg RCC_APB1Periph_GPIOB
 *      @arg RCC_APB1Periph_GPIOC
 *      @arg RCC_APB1Periph_GPIOD
 *      @arg RCC_APB1Periph_EXTI
 *      @arg RCC_APB1Periph_AFIO
 *      @arg RCC_APB1Periph_ADC
 *      @arg RCC_APB1Periph_QSPI
 *      @arg RCC_APB1Periph_SPIS1
 *      @arg RCC_APB1Periph_UART1
 *      @arg RCC_APB1Periph_BMX1
 * @param  NewState: new state of the specified peripheral clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

/**
 * @brief  Enables or disables the APB2 peripheral clock.
 * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
 *    This parameter can be any combination of the following values:
 *      @arg RCC_APB2Periph_DMAC2
 *      @arg RCC_APB2Periph_WWDG
 *      @arg RCC_APB2Periph_UART2
 *      @arg RCC_APB2Periph_UART3
 *      @arg RCC_APB2Periph_SPIM2
 *      @arg RCC_APB2Periph_SPIS2
 *      @arg RCC_APB2Periph_I2S
 *      @arg RCC_APB2Periph_I2C1
 *      @arg RCC_APB2Periph_I2C2
 *      @arg RCC_APB2Periph_RNG
 *      @arg RCC_APB2Periph_LED
 *      @arg RCC_APB2Periph_BMX2
 * @param  NewState: new state of the specified peripheral clock.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/**
 * @brief  Forces or releases AHB peripheral reset.
 * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
 *    This parameter can be any combination of the following values:
 *      @arg RCC_AHBPeriph_USB
 *      @arg RCC_AHBPeriph_ISO
 *      @arg RCC_AHBPeriph_FLASH
 *      @arg RCC_AHBPeriph_CACHE
 *      @arg RCC_AHBPeriph_SYS
 *      @arg RCC_AHBPeriph_CRC_SFM
 * @param  NewState: new state of the specified peripheral reset.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  uint32_t tmp = RCC_AHBPeriph >> 8;

  if (NewState != DISABLE) {
    RCC->AHBRSTR1 |= tmp;
  }
  else {
    RCC->AHBRSTR1 &= ~tmp;
  }
}

/**
 * @brief  Forces or releases APB1 peripheral reset.
 * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
 *    This parameter can be any combination of the following values:
 *      @arg RCC_APB1Periph_DMAC1
 *      @arg RCC_APB1Periph_TIM1
 *      @arg RCC_APB1Periph_TIM2
 *      @arg RCC_APB1Periph_TIM3
 *      @arg RCC_APB1Periph_TIM4
 *      @arg RCC_APB1Periph_GPIOA
 *      @arg RCC_APB1Periph_GPIOB
 *      @arg RCC_APB1Periph_GPIOC
 *      @arg RCC_APB1Periph_GPIOD
 *      @arg RCC_APB1Periph_EXTI
 *      @arg RCC_APB1Periph_AFIO
 *      @arg RCC_APB1Periph_ADC
 *      @arg RCC_APB1Periph_QSPI
 *      @arg RCC_APB1Periph_SPIS1
 *      @arg RCC_APB1Periph_UART1
 *      @arg RCC_APB1Periph_BMX1
 * @param  NewState: new state of the specified peripheral reset.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/**
 * @brief  Forces or releases APB2 peripheral reset.
 * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
 *    This parameter can be any combination of the following values:
 *      @arg RCC_APB2Periph_DMAC2
 *      @arg RCC_APB2Periph_WWDG
 *      @arg RCC_APB2Periph_UART2
 *      @arg RCC_APB2Periph_UART3
 *      @arg RCC_APB2Periph_SPIM2
 *      @arg RCC_APB2Periph_SPIS2
 *      @arg RCC_APB2Periph_I2S
 *      @arg RCC_APB2Periph_I2C1
 *      @arg RCC_APB2Periph_I2C2
 *      @arg RCC_APB2Periph_RNG
 *      @arg RCC_APB2Periph_LED
 *      @arg RCC_APB2Periph_BMX2
 * @param  NewState: new state of the specified peripheral reset.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/**
 * @brief  Forces or releases the Backup domain reset.
 * @param  NewState: new state of the Backup domain reset.
 *    This parameter can be: ENABLE or DISABLE.
 * @return None
 */

void RCC_BackupResetCmd(FunctionalState NewState)
{
  RCC->BDRSTR = (uint32_t)NewState;
}

/**
 * @brief  Checks whether the specified RCC reset flag is set or not.
 * @param  RCC_RSTFLAG: specifies the flag to check.
 *    This parameter can be one of the following values:
 *      @arg RCC_RSTFLAG_LPWRRST: Low Power reset
 *      @arg RCC_RSTFLAG_WWDGRST: Window Watchdog reset
 *      @arg RCC_RSTFLAG_IWDGRST: Independent Watchdog reset
 *      @arg RCC_RSTFLAG_SFTRST: Software reset
 *      @arg RCC_RSTFLAG_PORRST: POR/PDR reset
 *      @arg RCC_RSTFLAG_PINRST: Pin reset
 * @return The new state of RCC_RSTFLAG (SET or RESET).
 */
FlagStatus RCC_GetResetFlagStatus(uint32_t RCC_RSTFLAG)
{
  FlagStatus bitstatus = RESET;

  if ((RCC->RSTSTAT & RCC_RSTFLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

/**
 * @brief  Clears the RCC reset flags.
 * @note   The reset flags are RCC_RSTFLAG_LPWRRST, RCC_RSTFLAG_WWDGRST, RCC_RSTFLAG_IWDGRST
 *    RCC_RSTFLAG_SFTRST, RCC_RSTFLAG_PORRST, RCC_RSTFLAG_PINRST
 * @param  None
 * @return None.
 */
void RCC_ClearResetFlags(void)
{
  RCC->CLRRSTSTAT = 0x01;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
