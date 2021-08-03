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
 * @file    GPIOv1/hal_pal_lld.h
 * @brief   WB32 PAL low level driver header.
 *
 * @addtogroup PAL
 * @{
 */

#ifndef HAL_PAL_LLD_H
#define HAL_PAL_LLD_H

#if HAL_USE_PAL || defined(__DOXYGEN__)

/*===========================================================================*/
/* Unsupported modes and specific modes                                      */
/*===========================================================================*/


/*===========================================================================*/
/* I/O Ports Types and constants.                                            */
/*===========================================================================*/

/**
 * @name    Port related definitions
 * @{
 */
/**
 * @brief   Width, in bits, of an I/O port.
 */
#define PAL_IOPORTS_WIDTH 16U

/**
 * @brief   Whole port mask.
 * @details This macro specifies all the valid bits into a port.
 */
#define PAL_WHOLE_PORT ((ioportmask_t)0xFFFFU)
/** @} */

/**
 * @name    Line handling macros
 * @{
 */
/**
 * @brief   Forms a line identifier.
 * @details A port/pad pair are encoded into an @p ioline_t type. The encoding
 *          of this type is platform-dependent.
 * @note    In this driver the pad number is encoded in the lower 4 bits of
 *          the GPIO address which are guaranteed to be zero.
 */
#define PAL_LINE(port, pad)                                                 \
  ((ioline_t)((uint32_t)(port)) | ((uint32_t)(pad)))

/**
 * @brief   Decodes a port identifier from a line identifier.
 */
#define PAL_PORT(line)                                                      \
  ((GPIO_TypeDef *)(((uint32_t)(line)) & 0xFFFFFFF0U))

/**
 * @brief   Decodes a pad identifier from a line identifier.
 */
#define PAL_PAD(line)                                                       \
  ((uint32_t)((uint32_t)(line) & 0x0000000FU))

/**
 * @brief   Value identifying an invalid line.
 */
#define PAL_NOLINE                      0U
/** @} */

/**
 * @brief   GPIO port setup info.
 */
typedef struct {
  uint16_t GPIO_Pin;
  uint32_t PinConfig;
} WB32_gpio_setup_t;

/**
 * @brief   WB32 GPIO static initializer.
 * @details An instance of this structure must be passed to @p palInit() at
 *          system startup time in order to initialize the digital I/O
 *          subsystem. This represents only the initial setup, specific pads
 *          or whole ports can be reprogrammed at later time.
 */
typedef struct {
  /** @brief Port A setup data.*/
  WB32_gpio_setup_t    PAData;
  /** @brief Port B setup data.*/
  WB32_gpio_setup_t    PBData;
  /** @brief Port C setup data.*/
  WB32_gpio_setup_t    PCData;
  /** @brief Port D setup data.*/
  WB32_gpio_setup_t    PDData;
} PALConfig;

/**
 * @brief Digital I/O port sized unsigned type.
 */
typedef uint32_t ioportmask_t;

/**
 * @brief   Digital I/O modes.
 */
typedef uint32_t iomode_t;

/**
 * @brief   Type of an I/O line.
 */
typedef uint32_t ioline_t;

/**
 * @brief   Type of an event mode.
 */
typedef uint32_t ioeventmode_t;

/**
 * @brief   Port Identifier.
 * @details This type can be a scalar or some kind of pointer, do not make
 *          any assumption about it, use the provided macros when populating
 *          variables of this type.
 */
typedef GPIO_TypeDef * ioportid_t;

/**
 * @brief   Type of an pad identifier.
 */
typedef uint32_t iopadid_t;

/** @defgroup GPIO_Pins_define
  * @{
  */
#define GPIO_Pin_0                  ((uint16_t)0x0001)    /*!< Pin 0    */
#define GPIO_Pin_1                  ((uint16_t)0x0002)    /*!< Pin 1    */
#define GPIO_Pin_2                  ((uint16_t)0x0004)    /*!< Pin 2    */
#define GPIO_Pin_3                  ((uint16_t)0x0008)    /*!< Pin 3    */
#define GPIO_Pin_4                  ((uint16_t)0x0010)    /*!< Pin 4    */
#define GPIO_Pin_5                  ((uint16_t)0x0020)    /*!< Pin 5    */
#define GPIO_Pin_6                  ((uint16_t)0x0040)    /*!< Pin 6    */
#define GPIO_Pin_7                  ((uint16_t)0x0080)    /*!< Pin 7    */
#define GPIO_Pin_8                  ((uint16_t)0x0100)    /*!< Pin 8    */
#define GPIO_Pin_9                  ((uint16_t)0x0200)    /*!< Pin 9    */
#define GPIO_Pin_10                 ((uint16_t)0x0400)    /*!< Pin 10   */
#define GPIO_Pin_11                 ((uint16_t)0x0800)    /*!< Pin 11   */
#define GPIO_Pin_12                 ((uint16_t)0x1000)    /*!< Pin 12   */
#define GPIO_Pin_13                 ((uint16_t)0x2000)    /*!< Pin 13   */
#define GPIO_Pin_14                 ((uint16_t)0x4000)    /*!< Pin 14   */
#define GPIO_Pin_15                 ((uint16_t)0x8000)    /*!< Pin 15   */
#define GPIO_Pin_All                ((uint16_t)0xFFFF)    /*!< All pins */

/**
  * @}
  */

/** @defgroup GPIO_Port_Sources
  * @{
  */
#define GPIO_PortSourceGPIOA       ((uint8_t)0x00)
#define GPIO_PortSourceGPIOB       ((uint8_t)0x01)
#define GPIO_PortSourceGPIOC       ((uint8_t)0x02)
#define GPIO_PortSourceGPIOD       ((uint8_t)0x03)
/**
  * @}
  */

/** @defgroup GPIO_Pin_sources
  * @{
  */
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

/**
  * @}
  */

/** @defgroup GPIO_MODE_define
  * @{
  */
#define GPIO_MODE_IN          0x00000000U     /*!< Input mode */
#define GPIO_MODE_OUT         0x10000000U     /*!< Output mode */
#define GPIO_MODE_AF          0x20000000U     /*!< Alternate function mode */
#define GPIO_MODE_ANA         0x30000000U     /*!< Analog mode */
/**
  * @}
  */

/** @defgroup GPIO_OTYPE_define
  * @{
  */
#define GPIO_OTYPE_PP         0x00000000U     /*!< Output push-pull */
#define GPIO_OTYPE_OD         0x01000000U     /*!< Output open-drain */
/**
  * @}
  */

/** @defgroup GPIO_SPEED_define
  * @{
  */
#define GPIO_SPEED_LOW        0x00100000U     /*!< Low speed */
#define GPIO_SPEED_HIGH       0x00000000U     /*!< High speed */
/**
  * @}
  */

/** @defgroup GPIO_PUPD_define
  * @{
  */
#define GPIO_PUPD_NOPULL      0x00000000U     /*!< No pull resistor */
#define GPIO_PUPD_UP          0x00010000U     /*!< Pull up resistor enabled */
#define GPIO_PUPD_DOWN        0x00020000U     /*!< Pull down resistor enabled */
/**
  * @}
  */

/** @defgroup GPIO_AF_define
  * @{
  */
#define GPIO_AF0      0
#define GPIO_AF1      1
#define GPIO_AF2      2
#define GPIO_AF3      3
#define GPIO_AF4      4
#define GPIO_AF5      5
#define GPIO_AF6      6
#define GPIO_AF7      7
#define GPIO_AF8      8
#define GPIO_AF9      9
#define GPIO_AF10     10
#define GPIO_AF11     11
#define GPIO_AF12     12
#define GPIO_AF13     13
#define GPIO_AF14     14
#define GPIO_AF15     15
/**
  * @}
  */

/**
 * @name    Standard I/O mode flags
 * @{
 */
/**
 * @brief   Implemented as input.
 */
#undef  PAL_MODE_RESET
#define PAL_MODE_RESET                  GPIO_MODE_IN

/**
 * @brief   Implemented as analog with analog switch disabled and lock.
 */
#undef  PAL_MODE_UNCONNECTED
#define PAL_MODE_UNCONNECTED            (GPIO_MODE_ANA )

/**
 * @brief   Regular input high-Z pad.
 */
#undef  PAL_MODE_INPUT
#define PAL_MODE_INPUT                  GPIO_MODE_IN

/**
 * @brief   Input pad with weak pull up resistor.
 */
#undef  PAL_MODE_INPUT_PULLUP
#define PAL_MODE_INPUT_PULLUP           (GPIO_MODE_IN |             \
                                         GPIO_PUPD_UP)

/**
 * @brief   Input pad with weak pull down resistor.
 */
#undef  PAL_MODE_INPUT_PULLDOWN
#define PAL_MODE_INPUT_PULLDOWN         (GPIO_MODE_IN |             \
                                         GPIO_PUPD_DOWN)

/**
 * @brief   Analog input mode.
 */
#undef  PAL_MODE_INPUT_ANALOG
#define PAL_MODE_INPUT_ANALOG           (GPIO_MODE_ANA )

/**
 * @brief   Push-pull output pad.
 */
#undef  PAL_MODE_OUTPUT_PUSHPULL
#define PAL_MODE_OUTPUT_PUSHPULL        (GPIO_MODE_OUT |            \
                                         GPIO_SPEED_HIGH |          \
                                         GPIO_OTYPE_PP)

/**
 * @brief   Open-drain output pad.
 */
#undef  PAL_MODE_OUTPUT_OPENDRAIN
#define PAL_MODE_OUTPUT_OPENDRAIN       (GPIO_MODE_OUT |            \
                                         GPIO_SPEED_HIGH |          \
                                         GPIO_OTYPE_OD)
/** @} */

/*===========================================================================*/
/* I/O Ports Identifiers.                                                    */
/* The low level driver wraps the definitions already present in the WB32   */
/* firmware library.                                                         */
/*===========================================================================*/

/**
 * @brief   GPIO port A identifier.
 */
#if WB32_HAS_GPIOA || defined(__DOXYGEN__)
#define IOPORT1         GPIOA
#endif

/**
 * @brief   GPIO port B identifier.
 */
#if WB32_HAS_GPIOB || defined(__DOXYGEN__)
#define IOPORT2         GPIOB
#endif

/**
 * @brief   GPIO port C identifier.
 */
#if WB32_HAS_GPIOC || defined(__DOXYGEN__)
#define IOPORT3         GPIOC
#endif

/**
 * @brief   GPIO port D identifier.
 */
#if WB32_HAS_GPIOD || defined(__DOXYGEN__)
#define IOPORT4         GPIOD
#endif

/*===========================================================================*/
/* Implementation, some of the following macros could be implemented as      */
/* functions, if so please put them in pal_lld.c.                            */
/*===========================================================================*/

/**
 * @brief   Alternate mode 0
 */
#define PAL_WB32F10X_ALTERNATE_0 (GPIO_MODE_AF | GPIO_AF0)

/**
 * @brief   Alternate mode 1
 */
#define PAL_WB32F10X_ALTERNATE_1 (GPIO_MODE_AF | GPIO_AF1)

/**
 * @brief   Alternate mode 2
 */
#define PAL_WB32F10X_ALTERNATE_2 (GPIO_MODE_AF | GPIO_AF2)

/**
 * @brief   Alternate mode 3
 */
#define PAL_WB32F10X_ALTERNATE_3 (GPIO_MODE_AF | GPIO_AF3)

/**
 * @brief   Alternate mode 4
 */
#define PAL_WB32F10X_ALTERNATE_4 (GPIO_MODE_AF | GPIO_AF4)

/**
 * @brief   Alternate mode 5
 */
#define PAL_WB32F10X_ALTERNATE_5 (GPIO_MODE_AF | GPIO_AF5)

/**
 * @brief   Alternate mode 6
 */
#define PAL_WB32F10X_ALTERNATE_6 (GPIO_MODE_AF | GPIO_AF6)

/**
 * @brief   Alternate mode 7
 */
#define PAL_WB32F10X_ALTERNATE_7 (GPIO_MODE_AF | GPIO_AF7)

#define ALTERNATE_HELP(n) (PAL_WB32F10X_ALTERNATE_##n)
/**
 * @brief   Alternate function.
 *
 * @param[in] n   alternate function selector - 1 through 3
 */
#define PAL_MODE_ALTERNATE(n) (ALTERNATE_HELP(n))

/**
 * @brief   GPIO ports subsystem initialization.
 *
 * @notapi
 */
#define pal_lld_init(config) _pal_lld_init(config)

/**
 * @brief   Reads an I/O port.
 * @details This function is implemented by reading the GPIO IDR register, the
 *          implementation has no side effects.
 * @note    This function is not meant to be invoked directly by the application
 *          code.
 *
 * @param[in] port      port identifier
 * @return              The port bits.
 *
 * @notapi
 */
#define pal_lld_readport(port) ((ioportmask_t)((port)->IDR))

/**
 * @brief   Reads the output latch.
 * @details This function is implemented by reading the GPIO ODR register, the
 *          implementation has no side effects.
 * @note    This function is not meant to be invoked directly by the application
 *          code.
 *
 * @param[in] port      port identifier
 * @return              The latched logical states.
 *
 * @notapi
 */
#define pal_lld_readlatch(port) ((ioportmask_t)((port)->ODR))

/**
 * @brief   Writes on a I/O port.
 * @details This function is implemented by writing the GPIO ODR register, the
 *          implementation has no side effects.
 * @note    Writing on pads programmed as pull-up or pull-down has the side
 *          effect to modify the resistor setting because the output latched
 *          data is used for the resistor selection.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be written on the specified port
 *
 * @notapi
 */
#define pal_lld_writeport(port, bits) ((port)->ODR = (ioportmask_t)(bits))

/**
 * @brief   Sets a bits mask on a I/O port.
 * @details This function is implemented by writing the GPIO BSRR register, the
 *          implementation has no side effects.
 * @note    Writing on pads programmed as pull-up or pull-down has the side
 *          effect to modify the resistor setting because the output latched
 *          data is used for the resistor selection.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be ORed on the specified port
 *
 * @notapi
 */
#define pal_lld_setport(port, bits) ((port)->BSRR = (ioportmask_t)(bits))

/**
 * @brief   Clears a bits mask on a I/O port.
 * @details This function is implemented by writing the GPIO BRR register, the
 *          implementation has no side effects.
 * @note    Writing on pads programmed as pull-up or pull-down has the side
 *          effect to modify the resistor setting because the output latched
 *          data is used for the resistor selection.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be cleared on the specified port
 *
 * @notapi
 */
#define pal_lld_clearport(port, bits) ((port)->BSRR = (ioportmask_t)((bits)<<16))

/**
 * @brief   Toggles a bits mask on a I/O port.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be XORed on the specified port
 *
 * @notapi
 */
#define pal_lld_toggleport(port, bits)    ((port)->ODR ^= (ioportmask_t)(bits))

/**
 * @brief   Reads a group of bits.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @return              The group logical states.
 *
 * @notapi
 */
#define pal_lld_readgroup(port, mask, offset) (((port)->IDR & !(mask << offset)) >> offset)

/**
 * @brief   Writes a group of bits.
 * @details This function is implemented by writing the GPIO BSRR register, the
 *          implementation has no side effects.
 * @note    Writing on pads programmed as pull-up or pull-down has the side
 *          effect to modify the resistor setting because the output latched
 *          data is used for the resistor selection.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    the group bit offset within the port
 * @param[in] bits      bits to be written. Values exceeding the group
 *                      width are masked.
 *
 * @notapi
 */
#define pal_lld_writegroup(port, mask, offset, bits) {                      \
  uint32_t w = ((~(ioportmask_t)(bits) & (ioportmask_t)(mask)) << (16U + (offset))) | \
               ((ioportmask_t)(bits) & (ioportmask_t)(mask)) << (offset);           \
  (port)->BSRR = w;                                                         \
}

/**
 * @brief   Pads group mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 * @note    Writing on pads programmed as pull-up or pull-down has the side
 *          effect to modify the resistor setting because the output latched
 *          data is used for the resistor selection.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @param[in] mode      group mode
 *
 * @notapi
 */
#define pal_lld_setgroupmode(port, mask, offset, mode)                      \
  _pal_lld_setgroupmode(port, mask << offset, mode)

/**
 * @brief   Writes a logical state on an output pad.
 * @note    Writing on pads programmed as pull-up or pull-down has the side
 *          effect to modify the resistor setting because the output latched
 *          data is used for the resistor selection.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @param[in] bit       logical value, the value must be @p PAL_LOW or
 *                      @p PAL_HIGH
 *
 * @notapi
 */
#define pal_lld_writepad(port, pad, bit) pal_lld_writegroup(port, 1, pad, bit)

/**
 * @brief   Pad event enable.
 * @note    Programming an unknown or unsupported mode is silently ignored.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @param[in] mode      pad event mode
 *
 * @notapi
 */
#define pal_lld_enablepadevent(port, pad, mode)                             \
  _pal_lld_enablepadevent(port, pad, mode)

/**
 * @brief   Pad event disable.
 * @details This function disables previously programmed event callbacks.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 *
 * @notapi
 */
#define pal_lld_disablepadevent(port, pad)                                  \
  _pal_lld_disablepadevent(port, pad)

/**
 * @brief   Returns a PAL event structure associated to a pad.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 *
 * @notapi
 */
#define pal_lld_get_pad_event(port, pad)                                    \
  &_pal_events[pad]; (void)(port)

/**
 * @brief   Returns a PAL event structure associated to a line.
 *
 * @param[in] line      line identifier
 *
 * @notapi
 */
#define pal_lld_get_line_event(line)                                        \
  &_pal_events[PAL_PAD(line)]

/**
 * @brief   Pad event enable check.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @return              Pad event status.
 * @retval false        if the pad event is disabled.
 * @retval true         if the pad event is enabled.
 *
 * @notapi
 */
#define pal_lld_ispadeventenabled(port, pad)                                \
  (bool)((EXTI->IMR & (1U << (uint32_t)pad)) != 0U)

#if !defined(__DOXYGEN__)
extern const PALConfig pal_default_config;
#if (PAL_USE_WAIT == TRUE) || (PAL_USE_CALLBACKS == TRUE)
extern palevent_t _pal_events[16];
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void _pal_lld_init(const PALConfig *config);
  void _pal_lld_setgroupmode(ioportid_t port,
                             ioportmask_t mask,
                             iomode_t mode);
#if PAL_USE_CALLBACKS || PAL_USE_WAIT
  void _pal_lld_enablepadevent(ioportid_t port,
                               iopadid_t pad,
                               ioeventmode_t mode);
  void _pal_lld_disablepadevent(ioportid_t port, iopadid_t pad);
#endif
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_PAL */

#endif /* HAL_PAL_LLD_H */

/** @} */
