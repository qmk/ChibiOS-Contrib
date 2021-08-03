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

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#include "hal.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   WB32 GPIO static initialization data.
 */
#if (HAL_USE_PAL == TRUE) || defined(__DOXYGEN__)
const PALConfig pal_default_config = {
#if WB32_HAS_GPIOA
  {GPIO_Pin_8 , GPIO_MODE_AF | GPIO_AF0},
#endif
#if WB32_HAS_GPIOB
  {GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14, GPIO_MODE_OUT | GPIO_OTYPE_PP | GPIO_PUPD_NOPULL |GPIO_SPEED_HIGH},
#endif
#if WB32_HAS_GPIOC
  {GPIO_Pin_14 | GPIO_Pin_15, GPIO_MODE_OUT | GPIO_OTYPE_PP | GPIO_PUPD_NOPULL |GPIO_SPEED_HIGH},
#endif
#if WB32_HAS_GPIOD
  {GPIO_Pin_13 | GPIO_Pin_14, GPIO_MODE_OUT | GPIO_OTYPE_PP | GPIO_PUPD_NOPULL |GPIO_SPEED_HIGH},
#endif
};
#endif

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/
/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {

  wb32_clock_init();
}
/**
 * @brief   Board-specific initialization code.
 * @note    You can add your board-specific code here.
 */
void boardInit(void) {

}
