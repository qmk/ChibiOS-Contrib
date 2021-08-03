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
 * @file    USARTv1/hal_uart_lld.c
 * @brief   WB32 low level UART driver code.
 *
 * @addtogroup UART
 * @{
 */

#include "hal.h"

#if HAL_USE_UART || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief USART1 UART driver identifier.*/
#if WB32_UART_USE_USART1 || defined(__DOXYGEN__)
UARTDriver UARTD1;
#endif

/** @brief USART2 UART driver identifier.*/
#if WB32_UART_USE_USART2 || defined(__DOXYGEN__)
UARTDriver UARTD2;
#endif

/** @brief USART3 UART driver identifier.*/
#if WB32_UART_USE_USART3 || defined(__DOXYGEN__)
UARTDriver UARTD3;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Status bits translation.
 *
 * @param[in] sr        USART SR register value
 *
 * @return  The error flags.
 */
static uartflags_t translate_errors(uint16_t sr) {
  uartflags_t sts = 0;

  if (sr & UART_LINE_STATUS_OE)
    sts |= UART_OVERRUN_ERROR;
  if (sr & UART_LINE_STATUS_PE)
    sts |= UART_PARITY_ERROR;
  if (sr & UART_LINE_STATUS_FE)
    sts |= UART_FRAMING_ERROR;
  if (sr & UART_LINE_STATUS_DR)
    sts |= UART_NOISE_ERROR;
  if (sr & UART_LINE_STATUS_BI)
    sts |= UART_BREAK_DETECTED;
  return sts;
}

/**
 * @brief   Puts the receiver in the UART_RX_IDLE state.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 */
static void uart_enter_rx_idle_loop(UARTDriver *uartp) {

  uartp->g_uart_xfer_info.rx_len = 1;
  uartp->g_uart_xfer_info.rx_buf = (uint8_t *)&uartp->rxbuf;

  uartp->usart->IER |= UART_IT_RDA;
}

/**
 * @brief   USART de-initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 */
static void usart_stop(UARTDriver *uartp) {

  /* Disable the USART Interrupt.*/
  uartp->usart->IER &= ~(0xFF);
}

/**
 * @brief   USART initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 */
static void usart_start(UARTDriver *uartp) {
  uint32_t divider, apbclock;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  UART_TypeDef *u = uartp->usart;

  usart_stop(uartp);

  u->MCR = (u->MCR & 0x50) | uartp->config->UART_AutoFlowControl;

  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if (u == UART1)
  {
    apbclock = RCC_ClocksStatus.APB1CLK_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.APB2CLK_Frequency;
  }

  // round off
  divider = (apbclock + (uartp->config->UART_BaudRate >> 1)) / uartp->config->UART_BaudRate;

  u->DLF = divider & 0x0F;
  u->LCR = UART_LCR_DLAB;
  u->DLL = (uint8_t)(divider >> 4);
  u->DLH = (uint8_t)(divider >> 12);
  u->LCR = 0x00;
  u->LCR = uartp->config->UART_WordLength | uartp->config->UART_StopBits | uartp->config->UART_Parity;

  u->SRT = UART_RxFIFOThreshold_1;
  u->SFE = 0x01;

  /* Starting the receiver idle loop.*/
  uart_enter_rx_idle_loop(uartp);
}

/**
 * @brief   USART common service routine.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 */
static void serve_usart_irq(UARTDriver *uartp) {
  UART_TypeDef *u = uartp->usart;
  uint32_t sr;
  uint8_t rbyte;
  uint8_t int_id;

  int_id = (u->IIR & UART_IIR_INTID_Msk);
  
  if(int_id == UART_INTID_CTI)   //FIFO Time out
  {
    while((u->USR & UART_FLAG_RFNE) != RESET)
    {
      rbyte = (uint16_t)u->RBR;
      
      if (uartp->g_uart_xfer_info.rx_len) 
      {
        *uartp->g_uart_xfer_info.rx_buf = rbyte;
        uartp->g_uart_xfer_info.rx_buf++;
        uartp->g_uart_xfer_info.rx_len--;
        if(uartp->g_uart_xfer_info.rx_len == 0)
        {
          if (uartp->rxstate == UART_RX_IDLE) 
          {
            /* Receiver in idle state, a callback is generated, if enabled, for each
            received character and then the driver stays in the same state.*/
            _uart_rx_idle_code(uartp);
          }
          else 
          {
            _uart_rx_complete_isr_code(uartp);
            /* Disable rx interrupt */
  //          u->IER &= ~UART_IT_RDA;
          }
        }
      }
    }
    /* Timeout interrupt sources are only checked if enabled in IIR.*/
    _uart_timeout_isr_code(uartp);
  }
  else  if(int_id == UART_INTID_RDA)   //Receive One Byte
  {
    rbyte = (uint16_t)u->RBR;
    
    if (uartp->g_uart_xfer_info.rx_len) 
    {
      *uartp->g_uart_xfer_info.rx_buf = rbyte;
      uartp->g_uart_xfer_info.rx_buf++;
      uartp->g_uart_xfer_info.rx_len--;
      
      if(uartp->g_uart_xfer_info.rx_len == 0)
      {
        if (uartp->rxstate == UART_RX_IDLE) 
        {
          /* Receiver in idle state, a callback is generated, if enabled, for each
          received character and then the driver stays in the same state.*/
          _uart_rx_idle_code(uartp);
        }
        else 
        {
          _uart_rx_complete_isr_code(uartp);
          /* Disable rx interrupt */
  //        u->IER &= ~UART_IT_RDA;
        }        
      }
    }
  }
  else if (int_id == UART_INTID_THRE)   //Send One Byte
  {
    if (uartp->g_uart_xfer_info.tx_len) 
    {
      u->THR = (uint16_t)*uartp->g_uart_xfer_info.tx_buf;
      uartp->g_uart_xfer_info.tx_buf++;
      uartp->g_uart_xfer_info.tx_len--;
      if(uartp->g_uart_xfer_info.tx_len == 0)
      {
        /* A callback is generated, if enabled, after a completed transfer.*/
        _uart_tx1_isr_code(uartp);
        /* End of transmission, a callback is generated.*/
        _uart_tx2_isr_code(uartp);      
        /* Disable tx interrupt */
        u->IER &= ~UART_IT_THRE;
      }
    }
  }
  sr = (uint32_t) u->LSR;
  if(sr & (UART_LINE_STATUS_PE | UART_LINE_STATUS_FE | 
  UART_LINE_STATUS_OE | UART_LINE_STATUS_DR |UART_LINE_STATUS_BI))
  {
    _uart_rx_error_isr_code(uartp, translate_errors(sr));
  }
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if WB32_UART_USE_USART1 || defined(__DOXYGEN__)
#if !defined(WB32_UART1_IRQ_VECTOR)
#error "WB32_USART1_HANDLER not defined"
#endif
/**
 * @brief   USART1 IRQ handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(WB32_UART1_IRQ_VECTOR) {

  OSAL_IRQ_PROLOGUE();

  serve_usart_irq(&UARTD1);

  OSAL_IRQ_EPILOGUE();
}
#endif /* WB32_UART_USE_USART1 */

#if WB32_UART_USE_USART2 || defined(__DOXYGEN__)
#if !defined(WB32_UART2_IRQ_VECTOR)
#error "WB32_USART2_HANDLER not defined"
#endif
/**
 * @brief   USART2 IRQ handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(WB32_UART2_IRQ_VECTOR) {

  OSAL_IRQ_PROLOGUE();

  serve_usart_irq(&UARTD2);

  OSAL_IRQ_EPILOGUE();
}
#endif /* WB32_UART_USE_USART2 */

#if WB32_UART_USE_USART3 || defined(__DOXYGEN__)
#if !defined(WB32_UART3_IRQ_VECTOR)
#error "WB32_USART3_HANDLER not defined"
#endif
/**
 * @brief   USART3 IRQ handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(WB32_UART3_IRQ_VECTOR) {

  OSAL_IRQ_PROLOGUE();

  serve_usart_irq(&UARTD3);

  OSAL_IRQ_EPILOGUE();
}
#endif /* WB32_UART_USE_USART3 */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level UART driver initialization.
 *
 * @notapi
 */
void uart_lld_init(void) {

#if WB32_UART_USE_USART1
  uartObjectInit(&UARTD1);
  UARTD1.usart   = UART1;
#endif

#if WB32_UART_USE_USART2
  uartObjectInit(&UARTD2);
  UARTD2.usart   = UART2;
#endif

#if WB32_UART_USE_USART3
  uartObjectInit(&UARTD3);
  UARTD3.usart   = UART3;
#endif
}

/**
 * @brief   Configures and activates the UART peripheral.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 *
 * @notapi
 */
void uart_lld_start(UARTDriver *uartp) {

  if (uartp->state == UART_STOP) {
#if WB32_UART_USE_USART1
    if (&UARTD1 == uartp) {
       /* UART1 clock enable */
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_BMX1 | RCC_APB1Periph_UART1, ENABLE);

      /* UART1 DeInit */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, DISABLE);

      nvicEnableVector(UART1_IRQn, WB32_UART_USART1_IRQ_PRIORITY);
      
    }
#endif

#if WB32_UART_USE_USART2
    if (&UARTD2 == uartp) {
       /* UART2 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_BMX2 | RCC_APB2Periph_UART2, ENABLE);

      /* UART2 DeInit */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART2, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART2, DISABLE);

      nvicEnableVector(UART2_IRQn, WB32_UART_USART2_IRQ_PRIORITY);
    }
#endif

#if WB32_UART_USE_USART3
    if (&UARTD3 == uartp) {
       /* UART3 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_BMX2 | RCC_APB2Periph_UART3, ENABLE);

      /* UART3 DeInit */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART3, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART3, DISABLE);

      nvicEnableVector(UART3_IRQn, WB32_UART_USART3_IRQ_PRIORITY);
    }
#endif
  }
  uartp->rxstate = UART_RX_IDLE;
  uartp->txstate = UART_TX_IDLE;
  usart_start(uartp);
}

/**
 * @brief   Deactivates the UART peripheral.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 *
 * @notapi
 */
void uart_lld_stop(UARTDriver *uartp) {

  if (uartp->state == UART_READY) {
    uartp->g_uart_xfer_info.tx_len = 0;
    uartp->g_uart_xfer_info.rx_len = 0;
    uartp->g_uart_xfer_info.tx_buf = NULL;
    uartp->g_uart_xfer_info.rx_buf = NULL;
    uartp->g_uart_xfer_info.tx_abrt_source = 0;

    usart_stop(uartp);
    
#if WB32_UART_USE_USART1
    if (&UARTD1 == uartp) {
      nvicDisableVector(UART1_IRQn);
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_BMX1 | RCC_APB1Periph_UART1, DISABLE);
      return;
    }
#endif

#if WB32_UART_USE_USART2
    if (&UARTD2 == uartp) {
      nvicDisableVector(UART2_IRQn);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_BMX2 | RCC_APB2Periph_UART2, DISABLE);
      return;
    }
#endif

#if WB32_UART_USE_USART3
    if (&UARTD3 == uartp) {
      nvicDisableVector(UART3_IRQn);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_BMX2 | RCC_APB2Periph_UART3, DISABLE);
      return;
    }
#endif
  }
}

/**
 * @brief   Starts a transmission on the UART peripheral.
 * @note    The buffers are organized as uint8_t arrays for data sizes below
 *          or equal to 8 bits else it is organized as uint16_t arrays.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 * @param[in] n         number of data frames to send
 * @param[in] txbuf     the pointer to the transmit buffer
 *
 * @notapi
 */
void uart_lld_start_send(UARTDriver *uartp, size_t n, const void *txbuf) {

  uartp->g_uart_xfer_info.tx_len = n;
  uartp->g_uart_xfer_info.tx_buf = txbuf;

  uartp->usart->IER |= UART_IT_THRE;
}

/**
 * @brief   Stops any ongoing transmission.
 * @note    Stopping a transmission also suppresses the transmission callbacks.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 *
 * @return              The number of data frames not transmitted by the
 *                      stopped transmit operation.
 *
 * @notapi
 */
size_t uart_lld_stop_send(UARTDriver *uartp) {

  uartp->usart->IER &= ~(UART_IT_THRE);

  return (size_t)(uartp->g_uart_xfer_info.tx_len);
}

/**
 * @brief   Starts a receive operation on the UART peripheral.
 * @note    The buffers are organized as uint8_t arrays for data sizes below
 *          or equal to 8 bits else it is organized as uint16_t arrays.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 * @param[in] n         number of data frames to send
 * @param[out] rxbuf    the pointer to the receive buffer
 *
 * @notapi
 */
void uart_lld_start_receive(UARTDriver *uartp, size_t n, void *rxbuf) {

  uartp->g_uart_xfer_info.rx_len = n;
  uartp->g_uart_xfer_info.rx_buf = rxbuf;

  uartp->usart->IER |= UART_IT_RDA;
}

/**
 * @brief   Stops any ongoing receive operation.
 * @note    Stopping a receive operation also suppresses the receive callbacks.
 *
 * @param[in] uartp     pointer to the @p UARTDriver object
 *
 * @return              The number of data frames not received by the
 *                      stopped receive operation.
 *
 * @notapi
 */
size_t uart_lld_stop_receive(UARTDriver *uartp) {
  uartp->usart->IER &= ~(UART_IT_RDA);

  return (size_t)(uartp->g_uart_xfer_info.rx_len);
}

#endif /* HAL_USE_UART */

/** @} */
