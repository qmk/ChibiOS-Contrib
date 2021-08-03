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
 * @file    USARTv1/hal_uart_lld.h
 * @brief   WB32 low level UART driver header.
 *
 * @addtogroup UART
 * @{
 */

#ifndef HAL_UART_LLD_H
#define HAL_UART_LLD_H

#if HAL_USE_UART || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/** @defgroup UART_Exported_Constants
  * @{
  */

/** @defgroup UART_Word_Length 
  * @{
  */
#define UART_WordLength_5b          UART_LCR_WLS_5BIT
#define UART_WordLength_6b          UART_LCR_WLS_6BIT
#define UART_WordLength_7b          UART_LCR_WLS_7BIT
#define UART_WordLength_8b          UART_LCR_WLS_8BIT
/**
  * @}
  */


/** @defgroup UART_Stop_Bits 
  * @{
  */
#define UART_StopBits_One           UART_LCR_SBS_1BIT
#define UART_StopBits_Two           UART_LCR_SBS_2BIT
#define UART_StopBits_OnePointFive  UART_LCR_SBS_2BIT
/**
  * @}
  */


/** @defgroup UART_Parity 
  * @{
  */
#define UART_Parity_None            (0x00U)
#define UART_Parity_Odd             (UART_LCR_PARITY_ODD)
#define UART_Parity_Even            (UART_LCR_PARITY_EVEN)
#define UART_Parity_Mark            (UART_LCR_PARITY_MARK)
#define UART_Parity_Space           (UART_LCR_PARITY_SPACE)
/**
  * @}
  */


/** @defgroup UART_AutoFlowControl 
  * @{
  */
#define UART_AutoFlowControl_None       (0x00)
#define UART_AutoFlowControl_CTS        (UART_MCR_AFCE)
#define UART_AutoFlowControl_RTS_CTS    (UART_MCR_AFCE | UART_MCR_RTS)
/**
  * @}
  */


/** @defgroup UART_RxFIFOThreshold 
  * @{
  */
#define UART_RxFIFOThreshold_1    0x00
#define UART_RxFIFOThreshold_4    0x01
#define UART_RxFIFOThreshold_8    0x02
#define UART_RxFIFOThreshold_14   0x03
/**
  * @}
  */


/** @defgroup UART_TxFIFOThreshold 
  * @{
  */
#define UART_TxFIFOThreshold_0    0x00
#define UART_TxFIFOThreshold_2    0x01
#define UART_TxFIFOThreshold_4    0x02
#define UART_TxFIFOThreshold_8    0x03
/**
  * @}
  */


/** @defgroup UART_IT 
  * @{
  */
#define UART_IT_RDA                 UART_IER_RDAIE
#define UART_IT_THRE                UART_IER_THREIE
#define UART_IT_RLS                 UART_IER_RLSIE
#define UART_IT_MSI                 UART_IER_MSIE
/**
  * @}
  */



/** @defgroup UART_INTID 
  * @{
  */
#define UART_INTID_MSI              UART_IIR_INTID_MSI    /*!< Modem status interrupt */
#define UART_INTID_NONE             UART_IIR_INTID_NONE   /*!< No interrupt pending */
#define UART_INTID_THRE             UART_IIR_INTID_THRE   /*!< Transmitter holding register empty */
#define UART_INTID_RDA              UART_IIR_INTID_RDA    /*!< Received data available interrupt */
#define UART_INTID_RLS              UART_IIR_INTID_RLS    /*!< Receiver line status interrupt */
#define UART_INTID_BUSY             UART_IIR_INTID_BUSY   /*!< Busy detect */
#define UART_INTID_CTI              UART_IIR_INTID_CTI    /*!< character timeout indicator */
/**
  * @}
  */


/** @defgroup UART_Flags 
  * @{
  */
#define UART_FLAG_BUSY              UART_USR_BUSY
#define UART_FLAG_TFNF              UART_USR_TFNF
#define UART_FLAG_TFE               UART_USR_TFE
#define UART_FLAG_RFNE              UART_USR_RFNE
#define UART_FLAG_RFF               UART_USR_RFF
/**
  * @}
  */


/** @defgroup UART_LINE_STATUS 
  * @{
  */
#define UART_LINE_STATUS_DR         UART_LSR_DR
#define UART_LINE_STATUS_OE         UART_LSR_OE
#define UART_LINE_STATUS_PE         UART_LSR_PE
#define UART_LINE_STATUS_FE         UART_LSR_FE
#define UART_LINE_STATUS_BI         UART_LSR_BI
#define UART_LINE_STATUS_THRE       UART_LSR_THRE
#define UART_LINE_STATUS_TEMT       UART_LSR_TEMT
#define UART_LINE_STATUS_RFE        UART_LSR_RFE
#define UART_LINE_STATUS_ADDR_RCVD  UART_LSR_ADDR_RCVD
/**
  * @}
  */


/** @defgroup UART_MODEM_STATUS 
  * @{
  */
#define UART_MODEM_STATUS_DCTS      UART_MSR_DCTS
#define UART_MODEM_STATUS_CTS       UART_MSR_CTS
/**
  * @}
  */

/**
  * @}
  */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   UART driver on USART1 enable switch.
 * @details If set to @p TRUE the support for USART1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_UART_USE_USART1) || defined(__DOXYGEN__)
#define WB32_UART_USE_USART1               FALSE
#endif

/**
 * @brief   UART driver on USART2 enable switch.
 * @details If set to @p TRUE the support for USART2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_UART_USE_USART2) || defined(__DOXYGEN__)
#define WB32_UART_USE_USART2               FALSE
#endif

/**
 * @brief   UART driver on USART3 enable switch.
 * @details If set to @p TRUE the support for USART3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_UART_USE_USART3) || defined(__DOXYGEN__)
#define WB32_UART_USE_USART3               FALSE
#endif

/**
 * @brief   USART1 interrupt priority level setting.
 */
#if !defined(WB32_UART_USART1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_UART_USART1_IRQ_PRIORITY      12
#endif

/**
 * @brief   USART2 interrupt priority level setting.
 */
#if !defined(WB32_UART_USART2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_UART_USART2_IRQ_PRIORITY      12
#endif

/**
 * @brief   USART3 interrupt priority level setting.
 */
#if !defined(WB32_UART_USART3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_UART_USART3_IRQ_PRIORITY      12
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if WB32_UART_USE_USART1 && !WB32_HAS_UART1
#error "USART1 not present in the selected device"
#endif

#if WB32_UART_USE_USART2 && !WB32_HAS_UART2
#error "USART2 not present in the selected device"
#endif

#if WB32_UART_USE_USART3 && !WB32_HAS_UART3
#error "USART3 not present in the selected device"
#endif

#if !WB32_UART_USE_USART1 && !WB32_UART_USE_USART2 &&                     \
    !WB32_UART_USE_USART3 
#error "UART driver activated but no USART/UART peripheral assigned"
#endif

#if WB32_UART_USE_USART1 &&                                                \
    !OSAL_IRQ_IS_VALID_PRIORITY(WB32_UART_UART1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to USART1"
#endif

#if WB32_UART_USE_USART2 &&                                                \
    !OSAL_IRQ_IS_VALID_PRIORITY(WB32_UART_UART2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to USART2"
#endif

#if WB32_UART_USE_USART3 &&                                                \
    !OSAL_IRQ_IS_VALID_PRIORITY(WB32_UART_UART3_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to USART3"
#endif

#if !defined(WB32_DMA_REQUIRED)
#define WB32_DMA_REQUIRED
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   UART driver condition flags type.
 */
typedef uint32_t uartflags_t;

/**
 * @brief   Structure representing an UART driver.
 */
typedef struct UARTDriver UARTDriver;

/**
 * @brief   Generic UART notification callback type.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 */
typedef void (*uartcb_t)(UARTDriver *uartp);

/**
 * @brief   Character received UART notification callback type.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 * @param[in] c         received character
 */
typedef void (*uartccb_t)(UARTDriver *uartp, uint16_t c);

/**
 * @brief   Receive error UART notification callback type.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 * @param[in] e         receive error mask
 */
typedef void (*uartecb_t)(UARTDriver *uartp, uartflags_t e);

typedef struct _uart_xfer_info_t {
  const    uint8_t* tx_buf;
  volatile uint32_t tx_len;
           uint8_t* rx_buf;
  volatile uint32_t rx_len;
           uint32_t tx_abrt_source;
} uart_xfer_info_t;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
  /**
   * @brief End of transmission buffer callback.
   */
  uartcb_t                  txend1_cb;
  /**
   * @brief Physical end of transmission callback.
   */
  uartcb_t                  txend2_cb;
  /**
   * @brief Receive buffer filled callback.
   */
  uartcb_t                  rxend_cb;
  /**
   * @brief Character received while out if the @p UART_RECEIVE state.
   */
  uartccb_t                 rxchar_cb;
  /**
   * @brief Receive error callback.
   */
  uartecb_t                 rxerr_cb;
  /* End of the mandatory fields.*/
  /**
   * @brief   Receiver timeout callback.
   * @details Handles idle interrupts depending on configured
   *          flags in CR registers and supported hardware features.
   */
  uartcb_t                  timeout_cb;
  /**
   * @brief This member configures the UART communication baud rate.
   */
  uint32_t UART_BaudRate;   
  /**
   * @brief Specifies the number of data bits transmitted or received in a frame.
   * This parameter can be a value of @ref UART_Word_Length
   */     
  uint8_t  UART_WordLength;       
   /**
   * @brief Specifies the number of stop bits transmitted.
   * This parameter can be a value of @ref UART_Stop_Bits
   */                                        
  uint8_t  UART_StopBits;        
  /**
   * @brief Specifies the parity mode.
   * This parameter can be a value of @ref UART_Parity                                       
   */   
  uint8_t  UART_Parity;          
  /**
   * @brief Specifies the auto flow control mode is enabled or disabled.
   * This parameter can be a value of @ref UART_AutoFlowControl
   */   
  uint8_t  UART_AutoFlowControl;  
} UARTConfig;

/**
 * @brief   Structure representing an UART driver.
 */
struct UARTDriver {
  /**
   * @brief Driver state.
   */
  uartstate_t               state;
  /**
   * @brief Transmitter state.
   */
  uarttxstate_t             txstate;
  /**
   * @brief Receiver state.
   */
  uartrxstate_t             rxstate;
  /**
   * @brief Current configuration data.
   */
  const UARTConfig          *config;
#if (UART_USE_WAIT == TRUE) || defined(__DOXYGEN__)
  /**
   * @brief   Synchronization flag for transmit operations.
   */
  bool                      early;
  /**
   * @brief   Waiting thread on RX.
   */
  thread_reference_t        threadrx;
  /**
   * @brief   Waiting thread on TX.
   */
  thread_reference_t        threadtx;
#endif /* UART_USE_WAIT */
#if (UART_USE_MUTUAL_EXCLUSION == TRUE) || defined(__DOXYGEN__)
  /**
   * @brief   Mutex protecting the peripheral.
   */
  mutex_t                   mutex;
#endif /* UART_USE_MUTUAL_EXCLUSION */
#if defined(UART_DRIVER_EXT_FIELDS)
  UART_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the USART registers block.
   */
  UART_TypeDef             *usart;
  /**
   * @brief Default receive buffer while into @p UART_RX_IDLE state.
   */
  volatile uint16_t         rxbuf;
  uart_xfer_info_t  g_uart_xfer_info;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if WB32_UART_USE_USART1 && !defined(__DOXYGEN__)
extern UARTDriver UARTD1;
#endif

#if WB32_UART_USE_USART2 && !defined(__DOXYGEN__)
extern UARTDriver UARTD2;
#endif

#if WB32_UART_USE_USART3 && !defined(__DOXYGEN__)
extern UARTDriver UARTD3;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void uart_lld_init(void);
  void uart_lld_start(UARTDriver *uartp);
  void uart_lld_stop(UARTDriver *uartp);
  void uart_lld_start_send(UARTDriver *uartp, size_t n, const void *txbuf);
  size_t uart_lld_stop_send(UARTDriver *uartp);
  void uart_lld_start_receive(UARTDriver *uartp, size_t n, void *rxbuf);
  size_t uart_lld_stop_receive(UARTDriver *uartp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_UART */

#endif /* HAL_UART_LLD_H */

/** @} */
