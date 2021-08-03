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
 * @file    WB32F10x/wb32_registry.h
 * @brief   WB32F10x capabilities registry.
 *
 * @addtogroup HAL
 * @{
 */

#ifndef WB32_REGISTRY_H
#define WB32_REGISTRY_H

#if !defined(WB32F10x)
    #error "unsupported or unrecognized WB32F10x member"
#endif

/*===========================================================================*/
/* Platform capabilities.                                                    */
/*===========================================================================*/
#if defined(WB32F10x) || defined(__DOXYGEN__)
/**
 * @name    WB32F10x capabilities
 * @{
 */
/* GPIO attributes.*/
#define WB32_HAS_GPIOA                  TRUE
#define WB32_HAS_GPIOB                  TRUE
#define WB32_HAS_GPIOC                  TRUE
#define WB32_HAS_GPIOD                  TRUE

/* WWDG attributes */
#define WB32_HAS_WWDG                   TRUE

#define WB32_WWDG_IRQ_VECTOR         	Vector40
#define WB32_WWDG_NUMBER         	    0

/* PVD attributes */
#define WB32_HAS_PVD                    TRUE

#define WB32_PVD_IRQ_VECTOR          	Vector44
#define WB32_PVD_NUMBER          	    1

/* TAMPER attributes */
#define WB32_HAS_TAMPER                 TRUE

#define WB32_TAMPER_IRQ_VECTOR       	Vector48
#define WB32_TAMPER_NUMBER       	    2

/* RTC attributes */
#define WB32_HAS_RTC                    TRUE

#define WB32_RTC_IRQ_VECTOR          	Vector4C
#define WB32_RTC_NUMBER          	    3
#define WB32_RTCAlarm_IRQ_VECTOR     	VectorC8
#define WB32_RTCAlarm_NUMBER     	    34

/* FMC attributes */
#define WB32_HAS_FMC                    TRUE

#define WB32_FMC_IRQ_VECTOR          	Vector50
#define WB32_FMC_NUMBER          	    4
#define WB32_RCC_IRQ_VECTOR          	Vector54
#define WB32_RCC_NUMBER          	    5

/* EXTI attributes */
#define WB32_HAS_EXTI                   TRUE
#define WB32_HAS_EXTI0                  TRUE
#define WB32_HAS_EXTI1                  TRUE
#define WB32_HAS_EXTI2                  TRUE
#define WB32_HAS_EXTI3                  TRUE
#define WB32_HAS_EXTI4                  TRUE
#define WB32_HAS_EXTI9_5                TRUE
#define WB32_HAS_EXTI15_10              TRUE
#define WB32_EXTI_NUM_LINES             19

#define WB32_EXTI0_IRQ_VECTOR        	Vector58
#define WB32_EXTI0_NUMBER        	    6
#define WB32_EXTI1_IRQ_VECTOR        	Vector5C
#define WB32_EXTI1_NUMBER            	7
#define WB32_EXTI2_IRQ_VECTOR        	Vector60
#define WB32_EXTI2_NUMBER        	    8
#define WB32_EXTI3_IRQ_VECTOR        	Vector64
#define WB32_EXTI3_NUMBER        	    9
#define WB32_EXTI4_IRQ_VECTOR        	Vector68
#define WB32_EXTI4_NUMBER        	    10
#define WB32_EXTI9_5_IRQ_VECTOR      	Vector80
#define WB32_EXTI9_5_NUMBER      	    16
#define WB32_EXTI15_10_IRQ_VECTOR    	VectorC4
#define WB32_EXTI15_10_NUMBER    	    33

/* DMAC1 attributes */
#define WB32_HAS_DMAC                   TRUE
#define WB32_HAS_DMAC1                  TRUE
#define WB32_DMAC1_NUM_CHANNELS          3
#define WB32_HAS_DMAC2                  TRUE
#define WB32_DMAC2_NUM_CHANNELS          3

#define WB32_DMAC1_IRQ_VECTOR        	Vector6C
#define WB32_DMAC1_NUMBER           	11
#define WB32_DMAC2_IRQ_VECTOR        	Vector70
#define WB32_DMAC2_NUMBER           	12

/* ADC attributes */
#define WB32_HAS_ADC                    TRUE
#define WB32_ADC_IRQ_VECTOR          	Vector74
#define WB32_ADC_NUMBER          	    13

/* USB attributes */
#define WB32_HAS_USB                    TRUE
#define WB32_HAS_USB1                   TRUE
#define WB32_HAS_USB1_DMA               TRUE
#define WB32_HAS_USB1_WKUP              TRUE

#define WB32_USB1_IRQ_VECTOR          	Vector78
#define WB32_USB1_NUMBER             	14
#define WB32_USB1_DMA_IRQ_VECTOR      	Vector7C
#define WB32_USB1_DMA_NUMBER         	15
#define WB32_USBP1_WKUP_IRQ_VECTOR    	VectorCC
#define WB32_USBP1_WKUP_NUMBER    	    35

/* TIM attributes */
#define WB32_HAS_TIM                    TRUE
#define WB32_HAS_TIM1                   TRUE
#define WB32_HAS_TIM2                   TRUE
#define WB32_HAS_TIM3                   TRUE
#define WB32_HAS_TIM4                   TRUE

//#define WB32_TIM1_SUPPRESS_ISR          
//#define WB32_TIM2_SUPPRESS_ISR
//#define WB32_TIM3_SUPPRESS_ISR
//#define WB32_TIM4_SUPPRESS_ISR

#define WB32_TIM1_IS_32BITS                TRUE
#define WB32_TIM1_CHANNELS                 4
#define WB32_TIM2_IS_32BITS                TRUE
#define WB32_TIM2_CHANNELS                 4
#define WB32_TIM3_IS_32BITS                TRUE
#define WB32_TIM3_CHANNELS                 4
#define WB32_TIM4_IS_32BITS                TRUE
#define WB32_TIM4_CHANNELS                 4

#define WB32_TIM1_BRK_IRQ_VECTOR     	Vector84
#define WB32_TIM1_BRK_NUMBER        	17
#define WB32_TIM1_UP_IRQ_VECTOR      	Vector88
#define WB32_TIM1_UP_NUMBER      	    18
#define WB32_TIM1_TRG_COM_IRQ_VECTOR 	Vector8C
#define WB32_TIM1_TRG_COM_NUMBER 	    19
#define WB32_TIM1_CC_IRQ_VECTOR      	Vector90
#define WB32_TIM1_CC_NUMBER      	    20
#define WB32_TIM2_IRQ_VECTOR         	Vector94
#define WB32_TIM2_NUMBER         	    21
#define WB32_TIM3_IRQ_VECTOR         	Vector98
#define WB32_TIM3_NUMBER         	    22
#define WB32_TIM4_IRQ_VECTOR         	Vector9C
#define WB32_TIM4_NUMBER         	    23

/* I2C attributes */
#define WB32_HAS_I2C                    TRUE
#define WB32_HAS_I2C1                   TRUE
#define WB32_HAS_I2C2                   TRUE

#define WB32_I2C1_IRQ_VECTOR         	VectorA0
#define WB32_I2C1_NUMBER         	    24
#define WB32_I2C2_IRQ_VECTOR         	VectorA4
#define WB32_I2C2_NUMBER         	    25

/* SPI attributes */
#define WB32_HAS_SPI                    TRUE
#define WB32_HAS_QSPI                   TRUE
#define WB32_HAS_SPIM2                  TRUE
#define WB32_HAS_SPIS1                  TRUE
#define WB32_HAS_SPIS2                  TRUE

#define WB32_QSPI_IRQ_VECTOR         	VectorA8
#define WB32_QSPI_NUMBER         	    26
#define WB32_SPIM2_IRQ_VECTOR        	VectorAC
#define WB32_SPIM2_NUMBER        	    27
#define WB32_SPIS1_IRQ_VECTOR        	VectorB0
#define WB32_SPIS1_NUMBER        	    28
#define WB32_SPIS2_IRQ_VECTOR        	VectorB4
#define WB32_SPIS2_NUMBER        	    29

/* UART attributes */
#define WB32_HAS_UART                   TRUE
#define WB32_HAS_UART1                  TRUE
#define WB32_HAS_UART2                  TRUE
#define WB32_HAS_UART3                  TRUE

#define WB32_UART1_IRQ_VECTOR        	VectorB8
#define WB32_UART1_NUMBER        	    30
#define WB32_UART2_IRQ_VECTOR        	VectorBC
#define WB32_UART2_NUMBER        	    31
#define WB32_UART3_IRQ_VECTOR        	VectorC0
#define WB32_UART3_NUMBER        	    32

/* I2S attributes */
#define WB32_HAS_I2S                    TRUE

#define WB32_I2S_IRQ_VECTOR          	VectorD0
#define WB32_I2S_NUMBER          	    36

/* ISO attributes */
#define WB32_HAS_ISO                    TRUE

#define WB32_ISO_IRQ_VECTOR          	VectorD4
#define WB32_ISO_NUMBER          	    37

/* IWDG attributes.*/
#define WB32_HAS_IWDG                      TRUE

/* CRC attributes.*/
#define WB32_HAS_CRC                       TRUE
/** @} */
#endif /* defined(WB32F10x) */


#endif /* WB32_REGISTRY_H */

/** @} */
