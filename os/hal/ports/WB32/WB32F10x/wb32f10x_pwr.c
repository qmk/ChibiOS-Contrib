/**
 * @file    wb32f10x_pwr.c
 * @author  WestberryTech Application Team
 * @version V0.1.5
 * @date    18-February-2021
 * @brief   This file provides all the PWR firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32f10x_pwr.h"

/** @addtogroup WB32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR
  * @brief PWR driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup PWR_Private_Defines
  * @{
  */

#define CR0_DBP_BB    BIT_BAND_ADDR(&PWR->CR0, 0)
#define CR2_EWUP_BB   BIT_BAND_ADDR(&PWR->CR2, 0)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions
  * @{
  */

/**
 * @brief  Enables or disables access to the RTC and backup registers.
 * @param  NewState: new state of the access to the RTC and backup registers.
 *   This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void PWR_BackupAccessCmd(FunctionalState NewState)
{
  *(__IO uint32_t *) CR0_DBP_BB = (uint32_t)NewState;
}

/**
  * @brief  Enables or disables the WakeUp Pin functionality.
  * @param  NewState: new state of the WakeUp Pin functionality.
  *   This parameter can be: ENABLE or DISABLE.
  * @return None
  */
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  *(__IO uint32_t *) CR2_EWUP_BB = (uint32_t)NewState;
}

/**
 * @brief  Enters SLEEP mode.
 * @param  PWR_FCLK: specifies the M3 FCLK frequency in SLEEP mode.
 *    This parameter can be one of the following values:
 *      @arg PWR_FCLK_NoChange: the M3 FCLK frequency not change when enter SLEEP mode.
 *      @arg PWR_FCLK_Div2: the M3 FCLK frequency divide by 2 when enter SLEEP mode.
 * @param  PWR_EntryMode: specifies enter SLEEP mode with WFI or WFE instruction.
 *    This parameter can be one of the following values:
 *      @arg PWR_EntryMode_WFI: enter SLEEP mode with WFI instruction
 *      @arg PWR_EntryMode_WFE: enter SLEEP mode with WFE instruction
 * @return None
 */
void PWR_EnterSLEEPMode(uint8_t PWR_FCLK, uint8_t PWR_EntryMode)
{
  /* Clear all bits except DBP bit */
  PWR->CR0 &= 0x01U;

  if (PWR_FCLK == PWR_FCLK_Div2)
  {
    PWR->CR0 |= PWR_CR0_FCLKSD;
  }

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (~SCB_SCR_SLEEPDEEP_Msk);

  if (PWR_EntryMode == PWR_EntryMode_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }
}

/**
 * @brief  Enters STOP mode.
 * @param  PWR_STOPMode: specifies the STOP mode.
 *    This parameter can be one of the following values:
 *      @arg PWR_STOPMode_LP1: STOP LP1 mode.
 *      @arg PWR_STOPMode_LP2: STOP LP2 mode.
 *      @arg PWR_STOPMode_LP3_S32KON: STOP LP3 mode with 32K SRAM on.
 *      @arg PWR_STOPMode_LP3_S32KOFF: STOP LP3 mode with 32K SRAM off.
 *      @arg PWR_STOPMode_LP4_S32KON: STOP LP4 mode with 32K SRAM on.
 *      @arg PWR_STOPMode_LP4_S32KOFF: STOP LP4 mode with 32K SRAM off.
 * @param  PWR_EntryMode: specifies enter STOP mode with WFI or WFE instruction.
 *    This parameter can be one of the following values:
 *      @arg PWR_EntryMode_WFI: enter STOP mode with WFI instruction
 *      @arg PWR_EntryMode_WFE: enter STOP mode with WFE instruction
 * @return None
 */
void PWR_EnterSTOPMode(uint16_t PWR_STOPMode, uint8_t PWR_EntryMode)
{
  /* Clear all bits except DBP and FCLKSD bit */
  PWR->CR0 &= 0x09U;

  switch (PWR_STOPMode)
  {
  case PWR_STOPMode_LP1:
    PWR->CR0 |= 0x900U;
    PWR->CFGR = 0x3F;
    break;
  case PWR_STOPMode_LP2:
    PWR->CR0 |= 0x22002U;
    PWR->CFGR = 0x3BE;
    break;
  case PWR_STOPMode_LP3_S32KON:
    PWR->CR0 |= 0x63004U;
    PWR->CFGR = 0x3BF;
    break;
  case PWR_STOPMode_LP3_S32KOFF:
    PWR->CR0 |= 0x63004U | PWR_CR0_S32KMODE;
    PWR->CFGR = 0x3BF;
    break;
  case PWR_STOPMode_LP4_S32KON:
    PWR->CR0 |= 0x7B004U;
    PWR->CFGR = 0x3B3;
    break;
  case PWR_STOPMode_LP4_S32KOFF:
    PWR->CR0 |= 0x7B004U | PWR_CR0_S32KMODE;
    PWR->CFGR = 0x3B3;
    break;
  }

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  if (PWR_EntryMode == PWR_EntryMode_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE();
  }
  
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (~SCB_SCR_SLEEPDEEP_Msk);
}

/**
 * @brief  Enters STANDBY mode.
 * @param  None
 * @return None
 */
void PWR_EnterSTANDBYMode(void)
{
  /* Clear Wake-up flag */
  PWR->CR1 = PWR_CR1_CWUF;
  /* Select STANDBY mode */
  PWR->CR0 = (PWR->CR0 & (~PWR_CR0_PDDS_Msk)) | (0x02 << PWR_CR0_PDDS_Pos);

  PWR->CFGR = 0x13B3;
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  /* Request Wait For Interrupt */
  __WFI();
}

/**
 * @brief  Checks whether the specified PWR flag is set or not.
 * @param  PWR_FLAG: specifies the flag to check.
 *    This parameter can be one of the following values:
 *      @arg PWR_FLAG_PVDO: PVD Output
 *      @arg PWR_FLAG_WU: Wake Up flag
 *      @arg PWR_FLAG_SB: StandBy flag
 *      @arg PWR_FLAG_SP: Stop flag
 *      @arg PWR_FLAG_CK: Clock configuration reset flag
 * @return The new state of PWR_FLAG (SET or RESET).
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;

  tmp = PWR_FLAG >> 8;
  if (tmp == 1)
  {
    statusreg = PWR->SR1;
  }
  else
  {
    statusreg = PWR->SR0;
  }
  
  tmp = PWR_FLAG & 0x0F;
  if ((statusreg & tmp) != (uint32_t)RESET)
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
 * @brief  Clears the PWR's pending flags.
 * @param  PWR_FLAG: specifies the flag to clear.
 *    This parameter can be one of the following values:
 *      @arg PWR_FLAG_WU: Wake Up flag
 *      @arg PWR_FLAG_SB: StandBy flag
 *      @arg PWR_FLAG_SP: Stop flag
 *      @arg PWR_FLAG_CK: Clock configuration reset flag
 * @return None
 */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  PWR->CR1 |= PWR_FLAG;
}

/**
 * @brief  Disable ANCTL register write-protection function.
 * @param  None
 * @return None
 */
void PWR_UnlockANA(void)
{
  /* Unlocks write to ANCTL registers */
  PWR->ANAKEY1 = 0x03;
  PWR->ANAKEY2 = 0x0C;
}

/**
 * @brief  Enable ANCTL register write-protection function.
 * @param  None
 * @return None
 */
void PWR_LockANA(void)
{
  /* Locks write to ANCTL registers */
  PWR->ANAKEY1 = 0x00;
  PWR->ANAKEY2 = 0x00;
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
