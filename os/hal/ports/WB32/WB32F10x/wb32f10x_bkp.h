/**
 * @file    wb32f10x_bkp.h
 * @author  WestberryTech Application Team
 * @version V0.1.5
 * @date    18-February-2021
 * @brief   This file contains all the functions prototypes for the BKP firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32F10x_BKP_H
#define __WB32F10x_BKP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32f10x.h"

/** @addtogroup WB32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup BKP
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup BKP_Exported_Constants
  * @{
  */

/** @defgroup Tamper_Pin_active_level 
  * @{
  */
#define BKP_TamperPinLevel_High           ((uint16_t)0x0000)
#define BKP_TamperPinLevel_Low            ((uint16_t)0x0001)
#define IS_BKP_TAMPER_PIN_LEVEL(LEVEL) (((LEVEL) == BKP_TamperPinLevel_High) || \
                                        ((LEVEL) == BKP_TamperPinLevel_Low))
/**
  * @}
  */

/** @defgroup RTC_output_source_to_output_on_the_Tamper_pin 
  * @{
  */
#define BKP_RTCOutputSource_None          ((uint16_t)0x0000)
#define BKP_RTCOutputSource_CalibClock    ((uint16_t)0x0080)
#define BKP_RTCOutputSource_Alarm         ((uint16_t)0x0100)
#define BKP_RTCOutputSource_Second        ((uint16_t)0x0300)
#define IS_BKP_RTC_OUTPUT_SOURCE(SOURCE) (((SOURCE) == BKP_RTCOutputSource_None) || \
                                          ((SOURCE) == BKP_RTCOutputSource_CalibClock) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Alarm) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Second))
/**
  * @}
  */

/** @defgroup Data_Backup_Register 
  * @{
  */
#define BKP_DR1                           ((uint32_t)0x00000010)
#define BKP_DR2                           ((uint32_t)0x00000014)
#define BKP_DR3                           ((uint32_t)0x00000018)
#define BKP_DR4                           ((uint32_t)0x0000001C)
#define BKP_DR5                           ((uint32_t)0x00000020)
#define BKP_DR6                           ((uint32_t)0x00000024)
#define BKP_DR7                           ((uint32_t)0x00000028)
#define BKP_DR8                           ((uint32_t)0x0000002C)
#define BKP_DR9                           ((uint32_t)0x00000030)
#define BKP_DR10                          ((uint32_t)0x00000034)
#define BKP_DR11                          ((uint32_t)0x00000038)
#define BKP_DR12                          ((uint32_t)0x0000003C)
#define BKP_DR13                          ((uint32_t)0x00000040)
#define BKP_DR14                          ((uint32_t)0x00000044)
#define BKP_DR15                          ((uint32_t)0x00000048)
#define BKP_DR16                          ((uint32_t)0x0000004C)
#define BKP_DR17                          ((uint32_t)0x00000050)
#define BKP_DR18                          ((uint32_t)0x00000054)
#define BKP_DR19                          ((uint32_t)0x00000058)
#define BKP_DR20                          ((uint32_t)0x0000005C)
#define BKP_DR21                          ((uint32_t)0x00000060)

#define IS_BKP_DR(DR) (((DR) == BKP_DR1)  || ((DR) == BKP_DR2)  || ((DR) == BKP_DR3)  || \
                       ((DR) == BKP_DR4)  || ((DR) == BKP_DR5)  || ((DR) == BKP_DR6)  || \
                       ((DR) == BKP_DR7)  || ((DR) == BKP_DR8)  || ((DR) == BKP_DR9)  || \
                       ((DR) == BKP_DR10) || ((DR) == BKP_DR11) || ((DR) == BKP_DR12) || \
                       ((DR) == BKP_DR13) || ((DR) == BKP_DR14) || ((DR) == BKP_DR15) || \
                       ((DR) == BKP_DR16) || ((DR) == BKP_DR17) || ((DR) == BKP_DR18) || \
                       ((DR) == BKP_DR19) || ((DR) == BKP_DR20) || ((DR) == BKP_DR21))

#define IS_BKP_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x7F)
/**
  * @}
  */

/** @defgroup RTC_Clock_Source 
  * @{
  */
#define BKP_RTCCLKSource_LSE             ((uint32_t)0x00000100)
#define BKP_RTCCLKSource_LSI             ((uint32_t)0x00000200)
#define BKP_RTCCLKSource_HSE_Div128      ((uint32_t)0x00000300)
/**
  * @}
  */

/** @defgroup LSE_Configuration 
  * @{
  */
#define BKP_LSE_OFF     ((uint32_t)0x00000000)
#define BKP_LSE_ON      ((uint32_t)0x00000001)
#define BKP_LSE_Bypass  ((uint32_t)0x00000004)
/**
  * @}
  */

/**
  * @}
  */
  
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue);
void BKP_WriteBackupRegister(uint32_t BKP_DR, uint32_t Data);
uint32_t BKP_ReadBackupRegister(uint32_t BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);

void BKP_RTCCLKConfig(uint32_t BKP_RTCCLKSource);
void BKP_RTCCLKCmd(FunctionalState NewState);
void BKP_LSEConfig(uint32_t BKP_LSE);
FlagStatus BKP_GetLSEReadyFlagStatus(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32F10x_BKP_H */
