/**
 * @file    wb32f10x_pwr.h
 * @author  WestberryTech Application Team
 * @version V0.1.5
 * @date    18-February-2021
 * @brief   This file contains all the functions prototypes for the PWR firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32F10x_PWR_H
#define __WB32F10x_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32f10x.h"

/** @addtogroup WB32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants 
  * @{
  */

/** @defgroup PWR_entry_mode 
  * @{
  */
#define PWR_EntryMode_WFI         ((uint8_t)0x01)
#define PWR_EntryMode_WFE         ((uint8_t)0x02)
/**
  * @}
  */

/** @defgroup PWR_FCLK 
  * @{
  */
#define PWR_FCLK_NoChange          0x00
#define PWR_FCLK_Div2              0x01
/**
  * @}
  */

/** @defgroup PWR_stop_mode 
  * @{
  */
#define PWR_STOPMode_LP1              0x0001
#define PWR_STOPMode_LP2              0x0002
#define PWR_STOPMode_LP3_S32KON       0x0003
#define PWR_STOPMode_LP3_S32KOFF      0x0103
#define PWR_STOPMode_LP4_S32KON       0x0004
#define PWR_STOPMode_LP4_S32KOFF      0x0104
/**
  * @}
  */

/** @defgroup PWR_Flag 
  * @{
  */
#define PWR_FLAG_PVDO   ((uint32_t)0x00000001)
#define PWR_FLAG_WU     ((uint32_t)0x00000101)
#define PWR_FLAG_SB     ((uint32_t)0x00000102)
#define PWR_FLAG_SP     ((uint32_t)0x00000104)
#define PWR_FLAG_CK     ((uint32_t)0x00000108)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_EnterSLEEPMode(uint8_t PWR_FCLK, uint8_t PWR_EntryMode);
void PWR_EnterSTOPMode(uint16_t PWR_STOPMode, uint8_t PWR_EntryMode);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);
void PWR_UnlockANA(void);
void PWR_LockANA(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32F10x_PWR_H */
