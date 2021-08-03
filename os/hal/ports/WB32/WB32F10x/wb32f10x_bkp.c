/******************************************************************************
 * @file    wb32f10x_bkp.c
 * @author  WestberryTech Application Team
 * @version V0.1.5
 * @date    18-February-2021
 * @brief   This file provides all the BKP firmware functions.
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "wb32f10x_bkp.h"
#include "wb32f10x_rcc.h"

/** @addtogroup WB32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup BKP 
  * @brief BKP driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup BKP_Private_Defines
  * @{
  */

/* ------------ BKP registers bit address in the alias region --------------- */

/* --- CR Register ----*/

/* Alias word address of TPAL bit */
#define CR_TPAL_BB        BIT_BAND_ADDR(&BKP->CR, 1)

/* Alias word address of TPE bit */
#define CR_TPE_BB         BIT_BAND_ADDR(&BKP->CR, 0)

/* --- CSR Register ---*/

/* Alias word address of TPIE bit */
#define CSR_TPIE_BB       BIT_BAND_ADDR(&BKP->CSR, 2)

/* Alias word address of TIF bit */
#define CSR_TIF_BB        BIT_BAND_ADDR(&BKP->CSR, 9)

/* Alias word address of TEF bit */
#define CSR_TEF_BB        BIT_BAND_ADDR(&BKP->CSR, 8)

/* --- BDCR Register ---*/

/* Alias word address of RTCEN bit */
#define BDCR_RTCEN_BB     BIT_BAND_ADDR(&BKP->BDCR, 15)

/* Alias word address of LSERDY bit */
#define BDCR_LSERDY_BB    BIT_BAND_ADDR(&BKP->BDCR, 1)

/* ---------------------- BKP registers bit mask ------------------------ */

/* RTCCR register bit mask */
#define RTCCR_CAL_MASK    ((uint16_t)0xFF80)
#define RTCCR_MASK        ((uint16_t)0xFC7F)

/**
  * @}
  */ 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup BKP_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the BKP peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void BKP_DeInit(void)
{
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
}

/**
  * @brief  Configures the Tamper Pin active level.
  * @param  BKP_TamperPinLevel: specifies the Tamper Pin active level.
  *   This parameter can be one of the following values:
  *     @arg BKP_TamperPinLevel_High: Tamper pin active on high level
  *     @arg BKP_TamperPinLevel_Low: Tamper pin active on low level
  * @retval None
  */
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel)
{
  /* Check the parameters */
  assert_param(IS_BKP_TAMPER_PIN_LEVEL(BKP_TamperPinLevel));
  *(__IO uint32_t *) CR_TPAL_BB = BKP_TamperPinLevel;
}

/**
  * @brief  Enables or disables the Tamper Pin activation.
  * @param  NewState: new state of the Tamper Pin activation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BKP_TamperPinCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CR_TPE_BB = (uint32_t)NewState;
}

/**
  * @brief  Enables or disables the Tamper Pin Interrupt.
  * @param  NewState: new state of the Tamper Pin Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BKP_ITConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CSR_TPIE_BB = (uint32_t)NewState;
}

/**
  * @brief  Select the RTC output source to output on the Tamper pin.
  * @param  BKP_RTCOutputSource: specifies the RTC output source.
  *   This parameter can be one of the following values:
  *     @arg BKP_RTCOutputSource_None: no RTC output on the Tamper pin.
  *     @arg BKP_RTCOutputSource_CalibClock: output the RTC clock with frequency
  *                                          divided by 64 on the Tamper pin.
  *     @arg BKP_RTCOutputSource_Alarm: output the RTC Alarm pulse signal on
  *                                     the Tamper pin.
  *     @arg BKP_RTCOutputSource_Second: output the RTC Second pulse signal on
  *                                      the Tamper pin.  
  * @retval None
  */
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource)
{
  uint16_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BKP_RTC_OUTPUT_SOURCE(BKP_RTCOutputSource));
  tmpreg = BKP->RTCCR;
  /* Clear CCO, ASOE and ASOS bits */
  tmpreg &= RTCCR_MASK;
  
  /* Set CCO, ASOE and ASOS bits according to BKP_RTCOutputSource value */
  tmpreg |= BKP_RTCOutputSource;
  /* Store the new value */
  BKP->RTCCR = tmpreg;
}

/**
  * @brief  Sets RTC Clock Calibration value.
  * @param  CalibrationValue: specifies the RTC Clock Calibration value.
  *   This parameter must be a number between 0 and 0x7F.
  * @retval None
  */
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue)
{
  uint16_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_BKP_CALIBRATION_VALUE(CalibrationValue));
  tmpreg = BKP->RTCCR;
  /* Clear CAL[6:0] bits */
  tmpreg &= RTCCR_CAL_MASK;
  /* Set CAL[6:0] bits according to CalibrationValue value */
  tmpreg |= CalibrationValue;
  /* Store the new value */
  BKP->RTCCR = tmpreg;
}

/**
  * @brief  Writes user data to the specified Data Backup Register.
  * @param  BKP_DR: specifies the Data Backup Register.
  *   This parameter can be BKP_DRx where x:[1, 21]
  * @param  Data: data to write
  * @retval None
  */
void BKP_WriteBackupRegister(uint32_t BKP_DR, uint32_t Data)
{
  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));

  *(__IO uint32_t *) (BKP_BASE + BKP_DR) = Data;
}

/**
  * @brief  Reads data from the specified Data Backup Register.
  * @param  BKP_DR: specifies the Data Backup Register.
  *   This parameter can be BKP_DRx where x:[1, 21]
  * @retval The content of the specified Data Backup Register
  */
uint32_t BKP_ReadBackupRegister(uint32_t BKP_DR)
{
  /* Check the parameters */
  assert_param(IS_BKP_DR(BKP_DR));

  return (*(__IO uint32_t *) (BKP_BASE + BKP_DR));
}

/**
  * @brief  Checks whether the Tamper Pin Event flag is set or not.
  * @param  None
  * @retval The new state of the Tamper Pin Event flag (SET or RESET).
  */
FlagStatus BKP_GetFlagStatus(void)
{
  return (FlagStatus)(*(__IO uint32_t *) CSR_TEF_BB);
}

/**
  * @brief  Clears Tamper Pin Event pending flag.
  * @param  None
  * @retval None
  */
void BKP_ClearFlag(void)
{
  /* Set CTE bit to clear Tamper Pin Event flag */
  BKP->CSR |= BKP_CSR_CTE;
}

/**
  * @brief  Checks whether the Tamper Pin Interrupt has occurred or not.
  * @param  None
  * @retval The new state of the Tamper Pin Interrupt (SET or RESET).
  */
ITStatus BKP_GetITStatus(void)
{
  return (ITStatus)(*(__IO uint32_t *) CSR_TIF_BB);
}

/**
  * @brief  Clears Tamper Pin Interrupt pending bit.
  * @param  None
  * @retval None
  */
void BKP_ClearITPendingBit(void)
{
  /* Set CTI bit to clear Tamper Pin Interrupt pending bit */
  BKP->CSR |= BKP_CSR_CTI;
}


/**
 * @brief  Configures the RTC clock (RTCCLK).
 * @note   Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
 * @param  BKP_RTCCLKSource: specifies the RTC clock source.
 *   This parameter can be one of the following values:
 *     @arg BKP_RTCCLKSource_LSE: LSE selected as RTC clock
 *     @arg BKP_RTCCLKSource_LSI: LSI selected as RTC clock
 *     @arg BKP_RTCCLKSource_HSE_Div128: HSE clock divided by 128 selected as RTC clock
 * @return None
 */
void BKP_RTCCLKConfig(uint32_t BKP_RTCCLKSource)
{
  if (BKP_RTCCLKSource == BKP_RTCCLKSource_LSI) {
    RCC->LSI2RTCENR = 1;
  }
  else if (BKP_RTCCLKSource == BKP_RTCCLKSource_HSE_Div128) {
    RCC->HSE2RTCENR = 1;
  }

  /* Select the RTC clock source */
  BKP->BDCR = (BKP->BDCR & (~(0x03U << 8))) | BKP_RTCCLKSource;
}

/**
 * @brief  Enables or disables the RTC clock.
 * @note   This function must be used only after the RTC clock was selected using the BKP_RTCCLKConfig function.
 * @param  NewState: new state of the RTC clock. This parameter can be: ENABLE or DISABLE.
 * @return None
 */
void BKP_RTCCLKCmd(FunctionalState NewState)
{
  *(__IO uint32_t *) BDCR_RTCEN_BB = (uint32_t)NewState;
}

/**
 * @brief  Configures the External Low Speed oscillator (LSE).
 * @param  BKP_LSE: specifies the new state of the LSE.
 *   This parameter can be one of the following values:
 *     @arg BKP_LSE_OFF: LSE oscillator OFF
 *     @arg BKP_LSE_ON: LSE oscillator ON
 *     @arg BKP_LSE_Bypass: LSE oscillator bypassed with external clock
 * @return None
 */
void BKP_LSEConfig(uint32_t BKP_LSE)
{
  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  BKP->BDCR = BKP_LSE_OFF;
  /* Reset LSEBYP bit */
  BKP->BDCR = BKP_LSE_OFF;
  /* Configure LSE (BKP_LSE_OFF is already covered by the code section above) */
  switch(BKP_LSE)
  {
    case BKP_LSE_ON:
      /* Set LSEON bit */
      BKP->BDCR = BKP_LSE_ON;
      break;
      
    case BKP_LSE_Bypass:
      /* Set LSEBYP and LSEON bits */
      BKP->BDCR = BKP_LSE_Bypass;
      break;
      
    default:
      break;
  }
}

/**
  * @brief  Checks whether the LSE Ready flag is set or not.
  * @param  None
  * @retval The new state of the LSE Ready flag (SET or RESET).
  */
FlagStatus BKP_GetLSEReadyFlagStatus(void)
{
  return (FlagStatus)(*(__IO uint32_t *) BDCR_LSERDY_BB);
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
