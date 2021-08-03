/**
 * @file    wb32f10x_anctl.c
 * @author  WestberryTech Application Team
 * @version V0.1.5
 * @date    18-February-2021
 * @brief   This file provides all the ANCTL firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32f10x_anctl.h"

/** @addtogroup WB32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup ANCTL
  * @brief ANCTL driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup ANCTL_Private_Defines
  * @{
  */

#define SARENR_SAREN_BB     BIT_BAND_ADDR(&ANCTL->SARENR, 0)
#define PVDENR_PVDE_BB      BIT_BAND_ADDR(&ANCTL->PVDENR, 0)
#define USBPCR_USBPEN_BB    BIT_BAND_ADDR(&ANCTL->USBPCR, 0)
#define CMPA_CMPAEN_BB      BIT_BAND_ADDR(&ANCTL->CMPACR, 8)
#define CMPB_CMPBEN_BB      BIT_BAND_ADDR(&ANCTL->CMPBCR, 8)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ANCTL_Private_Functions
  * @{
  */

/**
 * @brief  Enables or disables the Internal 8MHz oscillator (MHSI).
 * @param  NewState: new state of the MHSI.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_MHSICmd(FunctionalState NewState)
{
  ANCTL->MHSIENR = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the Internal 48MHz oscillator (FHSI).
 * @param  NewState: new state of the FHSI.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_FHSICmd(FunctionalState NewState)
{
  ANCTL->FHSIENR = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
 * @param  NewState: new state of the LSI.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_LSICmd(FunctionalState NewState)
{
  ANCTL->LSIENR = (uint32_t)NewState;
}

/**
 * @brief  Configures the External High Speed oscillator (HSE).
 * @param  ANCTL_HSE: specifies the new state of the HSE.
 *    This parameter can be one of the following values:
 *      @arg ANCTL_HSE_OFF: HSE oscillator OFF
 *      @arg ANCTL_HSE_ON: HSE oscillator ON
 *      @arg ANCTL_HSE_Bypass: HSE oscillator bypassed with external clock
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_HSEConfig(uint32_t ANCTL_HSE)
{
  ANCTL->HSECR1 = ANCTL_HSE >> 8;
  ANCTL->HSECR0 = ANCTL_HSE & 0xFF;
}

/**
 * @brief  Waits for HSE start-up.
 * @param  None
 * @return An ErrorStatus enumuration value:
 *    - SUCCESS: HSE oscillator is stable and ready to use
 *    - ERROR: HSE oscillator not yet ready
 */
ErrorStatus ANCTL_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = ANCTL_GetFlagStatus(ANCTL_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  if (ANCTL_GetFlagStatus(ANCTL_FLAG_HSERDY) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
  return (status);
}

/**
 * @brief  Configures the PLL multiplication factor.
 * @param  ANCTL_PLLMul: specifies the PLL multiplication factor.
 *    This parameter can be one of the following values:
 *      @arg ANCTL_PLLMul_12
 *      @arg ANCTL_PLLMul_16
 *      @arg ANCTL_PLLMul_20
 *      @arg ANCTL_PLLMul_24
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_PLLConfig(uint32_t ANCTL_PLLMul)
{
  ANCTL->PLLCR = (ANCTL->PLLCR & (~ANCTL_PLLCR_PLLMUL_Msk)) | ANCTL_PLLMul;
}

/**
 * @brief  Enables or disables the PLL.
 * @param  NewState: new state of the PLL.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_PLLCmd(FunctionalState NewState)
{
  ANCTL->PLLENR = (uint32_t)NewState;
}

/**
 * @brief  Checks whether the specified ANCTL flag is set or not.
 * @param  ANCTL_FLAG: specifies the flag to check.
 *    This parameter can be one of the following values:
 *      @arg ANCTL_FLAG_MHSIRDY: MHSI oscillator clock ready
 *      @arg ANCTL_FLAG_FHSIRDY: FHSI oscillator clock ready
 *      @arg ANCTL_FLAG_LSIRDY: LSI oscillator clock ready
 *      @arg ANCTL_FLAG_HSERDY: HSE oscillator clock ready
 *      @arg ANCTL_FLAG_PLLRDY: PLL clock ready
 * @return The new state of ANCTL_FLAG (SET or RESET).
 */
FlagStatus ANCTL_GetFlagStatus(uint16_t ANCTL_FLAG)
{
  uint32_t tmp, statusreg;
  FlagStatus bitstatus = RESET;

  statusreg = *(__IO uint32_t*)(ANCTL_BASE + (ANCTL_FLAG >> 8));

  tmp = ANCTL_FLAG & 0xFF;
  if ((statusreg & tmp) == tmp)
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
 * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
 * @param  ANCTL_PVDLevel: specifies the PVD detection level.
 *    This parameter can be one of the following values:
 *      @arg ANCTL_PVDLevel_0
 *      @arg ANCTL_PVDLevel_1
 *      @arg ANCTL_PVDLevel_2
 *      @arg ANCTL_PVDLevel_3
 *      @arg ANCTL_PVDLevel_4
 *      @arg ANCTL_PVDLevel_5
 *      @arg ANCTL_PVDLevel_6
 *      @arg ANCTL_PVDLevel_7
 * @note   Refer to the electrical characteristics of your device datasheet for
 *         more details about the voltage threshold corresponding to each 
 *         detection level.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_PVDLevelConfig(uint32_t ANCTL_PVDLevel)
{
  ANCTL->PVDCR = ANCTL_PVDLevel;
}

/**
 * @brief  Enables or disables the Power Voltage Detector (PVD).
 * @param  NewState: new state of the PVD.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_PVDCmd(FunctionalState NewState)
{
  *(__IO uint32_t*) PVDENR_PVDE_BB = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the SAR ADC.
 * @param  NewState: new state of the SAR ADC.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_SARADCCmd(FunctionalState NewState)
{
  *(__IO uint32_t*) SARENR_SAREN_BB = (uint32_t)NewState;
}

/**
 * @brief  Deinitializes the USB PHY register to default reset values.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_USBPHYDeInit(void)
{
  ANCTL->USBPCR &= 0xFFFFFFE0;
}

/**
 * @brief  Configures the USB PHY function.
 * @param  ANCTL_USBPHY: specifies the USB PHY configuration.
 *    This parameter can be any combination of the following values:
 *      @arg ANCTL_USBPHY_DPPU: D+ pull-up resistor
 *      @arg ANCTL_USBPHY_HIGHRES: USB PHY input high resistance
 *      @arg ANCTL_USBPHY_DMST: USB PHY D- input schmitt channel
 *      @arg ANCTL_USBPHY_DPST: USB PHY D+ input schmitt channel
 * @param  NewState: new state of the USB PHY function.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_USBPHYConfig(uint32_t ANCTL_USBPHY, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    ANCTL->USBPCR |= ANCTL_USBPHY;
  }
  else {
    ANCTL->USBPCR &= ~ANCTL_USBPHY;
  }
}

/**
 * @brief  Enables or disables the USB PHY.
 * @param  NewState: new state of the USB PHY.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_USBPHYCmd(FunctionalState NewState)
{
  *(__IO uint32_t*) USBPCR_USBPEN_BB = (uint32_t)NewState;
}

/**
 * @brief  Enables or disables the Power-on Reset function.
 * @param  NewState: new state of the Power-on Reset function.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_PORCmd(FunctionalState NewState)
{
  if (NewState != DISABLE) {
    ANCTL->PORCR = 0x841;
  }
  else {
    ANCTL->PORCR = 0x000;
  }
}

/**
 * @brief  Configures the Comparator A.
 * @param  CMPA_PSEL: specifies the comparator positive input.
 * @param  CMPA_NSEL: specifies the comparator negative input.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_CMPAConfig(uint32_t CMPA_PSEL, uint32_t CMPA_NSEL)
{
  uint32_t tmpreg;
  tmpreg = (CMPA_PSEL & 0x0F) | ((CMPA_NSEL & 0x0F) << 4);
  ANCTL->CMPACR = (ANCTL->CMPACR & 0xFFFFFF00) | tmpreg;
}

/**
 * @brief  Enables or disables the Comparator A.
 * @param  NewState: new state of the Comparator A.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_CMPACmd(FunctionalState NewState)
{
  *(__IO uint32_t*) CMPA_CMPAEN_BB = (uint32_t)NewState;
}

/**
 * @brief  Returns the Comparator A output level.
 * @param  None
 * @return Comparator A output level.
 *    - 0: Comparator positive input voltage < negative input voltage
 *    - 1: Comparator positive input voltage > negative input voltage
 */
uint32_t ANCTL_CMPAGetOutputLevel(void)
{
  return ANCTL->CMPASR;
}

/**
 * @brief  Configures the Comparator B.
 * @param  CMPB_PSEL: specifies the comparator positive input.
 * @param  CMPB_NSEL: specifies the comparator negative input.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_CMPBConfig(uint32_t CMPB_PSEL, uint32_t CMPB_NSEL)
{
  uint32_t tmpreg;
  tmpreg = (CMPB_PSEL & 0x0F) | ((CMPB_NSEL & 0x0F) << 4);
  ANCTL->CMPBCR = (ANCTL->CMPBCR & 0xFFFFFF00) | tmpreg;
}

/**
 * @brief  Enables or disables the Comparator B.
 * @param  NewState: new state of the Comparator B.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_CMPBCmd(FunctionalState NewState)
{
  *(__IO uint32_t*) CMPB_CMPBEN_BB = (uint32_t)NewState;
}

/**
 * @brief  Returns the Comparator B output level.
 * @param  None
 * @return Comparator B output level.
 *    - 0: Comparator positive input voltage < negative input voltage
 *    - 1: Comparator positive input voltage > negative input voltage
 */
uint32_t ANCTL_CMPBGetOutputLevel(void)
{
  return ANCTL->CMPBSR;
}

/**
 * @brief  Enables or disables the specified ANCTL interrupts.
 * @param  ANCTL_IT: specifies the ANCTL interrupt sources to be enabled or disabled.
 *    This parameter can be any combination of the following values:
 *      @arg ANCTL_IT_MHSI: MHSI ready interrupt
 *      @arg ANCTL_IT_FHSI: FHSI ready interrupt
 *      @arg ANCTL_IT_LSI: LSI ready interrupt
 *      @arg ANCTL_IT_HSE: HSE ready interrupt
 *      @arg ANCTL_IT_LSE: LSE ready interrupt
 *      @arg ANCTL_IT_PLL: PLL ready interrupt
 * @param  NewState: new state of the specified ANCTL interrupts.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_ITConfig(uint8_t ANCTL_IT, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    ANCTL->IER |= ANCTL_IT;
  }
  else {
    ANCTL->IER &= (~ANCTL_IT);
  }
}

/**
 * @brief  Checks whether the specified ANCTL interrupt has occurred or not.
 * @param  ANCTL_IT: specifies the ANCTL interrupt source to check.
 *    This parameter can be one of the following values:
 *      @arg ANCTL_IT_MHSI: MHSI ready interrupt
 *      @arg ANCTL_IT_FHSI: FHSI ready interrupt
 *      @arg ANCTL_IT_LSI: LSI ready interrupt
 *      @arg ANCTL_IT_HSE: HSE ready interrupt
 *      @arg ANCTL_IT_LSE: LSE ready interrupt
 *      @arg ANCTL_IT_PLL: PLL ready interrupt
 *      @arg ANCTL_IT_DCSS: Clock Security System interrupt
 * @return The new state of ANCTL_IT (SET or RESET).
 */
ITStatus ANCTL_GetITStatus(uint8_t ANCTL_IT)
{
  ITStatus bitstatus = RESET;

  if (ANCTL->ISR & ANCTL_IT)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
 * @brief  Clears the ANCTL's interrupt pending bits.
 * @param  ANCTL_IT: specifies the interrupt pending bit to clear.
 *    This parameter can be any combination of the following values:
 *      @arg ANCTL_IT_MHSI: MHSI ready interrupt
 *      @arg ANCTL_IT_FHSI: FHSI ready interrupt
 *      @arg ANCTL_IT_LSI: LSI ready interrupt
 *      @arg ANCTL_IT_HSE: HSE ready interrupt
 *      @arg ANCTL_IT_LSE: LSE ready interrupt
 *      @arg ANCTL_IT_PLL: PLL ready interrupt
 *      @arg ANCTL_IT_DCSS: Clock Security System interrupt
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_ClearITPendingBit(uint8_t ANCTL_IT)
{
  ANCTL->ICR = ANCTL_IT;
}

/**
 * @brief  Enables or disables the Clock Security System.
 * @param  NewState: new state of the Clock Security System.
 *    This parameter can be: ENABLE or DISABLE.
 * @note   The ANCTL register write-protection function should be disabled before using this function.
 * @return None
 */
void ANCTL_ClockSecuritySystemCmd(FunctionalState NewState)
{
  ANCTL->DCSSCR = 3;
  ANCTL->DCSSENR = (uint32_t)NewState;
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
