/**
 * @file    wb32f10x_anctl.h
 * @author  WestberryTech Application Team
 * @version V0.1.5
 * @date    18-February-2021
 * @brief   This file contains all the functions prototypes for the ANCTL firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32F10x_ANCTL_H
#define __WB32F10x_ANCTL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32f10x.h"

/** @addtogroup WB32F10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup ANCTL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup ANCTL_Exported_Constants 
  * @{
  */

/** @defgroup HSE_configuration 
  * @{
  */
#define ANCTL_HSE_OFF       ((uint32_t)0x00000000)
#define ANCTL_HSE_ON        ((uint32_t)0x00000201)
#define ANCTL_HSE_Bypass    ((uint32_t)0x00000002)
/**
  * @}
  */


/** @defgroup PLL_multiplication_factor 
  * @{
  */
#define ANCTL_PLLMul_12   ((uint32_t)0x000000C0)
#define ANCTL_PLLMul_16   ((uint32_t)0x00000080)
#define ANCTL_PLLMul_20   ((uint32_t)0x00000040)
#define ANCTL_PLLMul_24   ((uint32_t)0x00000000)
/**
  * @}
  */


/** @defgroup ANCTL_Flag 
  * @{
  */
#define ANCTL_FLAG_MHSIRDY    ((uint16_t)0x3001)
#define ANCTL_FLAG_FHSIRDY    ((uint16_t)0x3C01)
#define ANCTL_FLAG_LSIRDY     ((uint16_t)0x4801)
#define ANCTL_FLAG_HSERDY     ((uint16_t)0x5801)
#define ANCTL_FLAG_PLLRDY     ((uint16_t)0x7C03)
/**
  * @}
  */


/** @defgroup PVD_detection_level 
  * @{
  */
#define ANCTL_PVDLevel_0    ANCTL_PVDCR_PLS_LEV0
#define ANCTL_PVDLevel_1    ANCTL_PVDCR_PLS_LEV1
#define ANCTL_PVDLevel_2    ANCTL_PVDCR_PLS_LEV2
#define ANCTL_PVDLevel_3    ANCTL_PVDCR_PLS_LEV3
#define ANCTL_PVDLevel_4    ANCTL_PVDCR_PLS_LEV4
#define ANCTL_PVDLevel_5    ANCTL_PVDCR_PLS_LEV5
#define ANCTL_PVDLevel_6    ANCTL_PVDCR_PLS_LEV6
#define ANCTL_PVDLevel_7    ANCTL_PVDCR_PLS_LEV7
/**
  * @}
  */


/** @defgroup USB_PHY_configuration 
  * @{
  */
#define ANCTL_USBPHY_DPPU      ((uint32_t)0x00000002)
#define ANCTL_USBPHY_HIGHRES   ((uint32_t)0x00000004)
#define ANCTL_USBPHY_DMST      ((uint32_t)0x00000008)
#define ANCTL_USBPHY_DPST      ((uint32_t)0x00000010)
/**
  * @}
  */


/** @defgroup CMPA_PSEL_NSEL 
  * @{
  */
#define CMPA_PSEL_PA8       0x00
#define CMPA_PSEL_PB4       0x01
#define CMPA_PSEL_PB5       0x02
#define CMPA_PSEL_PA13      0x03

#define CMPA_NSEL_PA9       0x00
#define CMPA_NSEL_PB6       0x01
#define CMPA_NSEL_PB7       0x02
#define CMPA_NSEL_PA14      0x03
/**
  * @}
  */


/** @defgroup CMPB_PSEL_NSEL 
  * @{
  */
#define CMPB_PSEL_PD2       0x00
#define CMPB_PSEL_PC10      0x01
#define CMPB_PSEL_PC11      0x02
#define CMPB_PSEL_PA15      0x03

#define CMPB_NSEL_PC12      0x00
#define CMPB_NSEL_PB8       0x01
#define CMPB_NSEL_PB9       0x02
#define CMPB_NSEL_PB3       0x03
/**
  * @}
  */


/** @defgroup ANCTL_Interrupt_source 
  * @{
  */
#define ANCTL_IT_MHSI       ((uint8_t)0x01)
#define ANCTL_IT_FHSI       ((uint8_t)0x02)
#define ANCTL_IT_LSI        ((uint8_t)0x04)
#define ANCTL_IT_HSE        ((uint8_t)0x08)
#define ANCTL_IT_LSE        ((uint8_t)0x10)
#define ANCTL_IT_PLL        ((uint8_t)0x20)
#define ANCTL_IT_DCSS       ((uint8_t)0x80)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ANCTL_MHSICmd(FunctionalState NewState);
void ANCTL_FHSICmd(FunctionalState NewState);
void ANCTL_LSICmd(FunctionalState NewState);
void ANCTL_HSEConfig(uint32_t ANCTL_HSE);
ErrorStatus ANCTL_WaitForHSEStartUp(void);
void ANCTL_PLLConfig(uint32_t ANCTL_PLLMul);
void ANCTL_PLLCmd(FunctionalState NewState);
FlagStatus ANCTL_GetFlagStatus(uint16_t ANCTL_FLAG);
void ANCTL_PVDLevelConfig(uint32_t ANCTL_PVDLevel);
void ANCTL_PVDCmd(FunctionalState NewState);
void ANCTL_SARADCCmd(FunctionalState NewState);
void ANCTL_USBPHYDeInit(void);
void ANCTL_USBPHYConfig(uint32_t ANCTL_USBPHY, FunctionalState NewState);
void ANCTL_USBPHYCmd(FunctionalState NewState);
void ANCTL_PORCmd(FunctionalState NewState);
void ANCTL_CMPAConfig(uint32_t CMPA_PSEL, uint32_t CMPA_NSEL);
void ANCTL_CMPACmd(FunctionalState NewState);
uint32_t ANCTL_CMPAGetOutputLevel(void);
void ANCTL_CMPBConfig(uint32_t CMPB_PSEL, uint32_t CMPB_NSEL);
void ANCTL_CMPBCmd(FunctionalState NewState);
uint32_t ANCTL_CMPBGetOutputLevel(void);
void ANCTL_ITConfig(uint8_t ANCTL_IT, FunctionalState NewState);
ITStatus ANCTL_GetITStatus(uint8_t ANCTL_IT);
void ANCTL_ClearITPendingBit(uint8_t ANCTL_IT);
void ANCTL_ClockSecuritySystemCmd(FunctionalState NewState);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32F10x_ANCTL_H */
