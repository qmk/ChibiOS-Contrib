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
 * @file    UARTv1/hal_serial_lld.c
 * @brief   WB32 low level serial driver code.
 *
 * @addtogroup SERIAL
 * @{
 */

#include "hal.h"

#if HAL_USE_SERIAL || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief UART1 serial driver identifier.*/
#if WB32_SERIAL_USE_UART1 || defined(__DOXYGEN__)
SerialDriver SD1;
#endif

/** @brief UART2 serial driver identifier.*/
#if WB32_SERIAL_USE_UART2 || defined(__DOXYGEN__)
SerialDriver SD2;
#endif

/** @brief UART3 serial driver identifier.*/
#if WB32_SERIAL_USE_UART3 || defined(__DOXYGEN__)
SerialDriver SD3;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/** @brief Driver default configuration.*/
static const SerialConfig default_config =
{
  SERIAL_DEFAULT_BITRATE,
  UART_WordLength_8b,
  UART_StopBits_One,
  UART_Parity_None,
  UART_AutoFlowControl_None
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   UART initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 * @param[in] config    the architecture-dependent serial driver configuration
 */
static void uart_init(SerialDriver *sdp, const SerialConfig *config) {
  uint32_t divider, apbclock;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  UART_TypeDef *u = uartp->usart;

  u->MCR = (u->MCR & 0x50) | uartp->config->UART_AutoFlowControl;

   /* Baud rate setting.*/
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

  /* Note that some bits are enforced.*/
  u->IER |= UART_IT_RDA | UART_IT_THRE | UART_IT_RLS;

  /* Deciding mask to be applied on the data register on receive, this is
     required in order to mask out the parity bit.*/
  sdp->rxmask = 0xFF;
}

/**
 * @brief   UART de-initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] u         pointer to an UART I/O block
 */
static void uart_deinit(UART_TypeDef *u) {

#if WB32_SERIAL_USE_UART1
  if(u == UART1)
  {
    /* UART1 DeInit */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, DISABLE);
  }
#endif

#if WB32_SERIAL_USE_UART2
  else if(u == UART2)
  {
    /* UART2 DeInit */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART2, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART2, DISABLE);
  }
#endif

#if WB32_SERIAL_USE_UART3
  else if(u == UART3)
  {
    /* UART3 DeInit */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART3, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART3, DISABLE);
  }
#endif
}

/**
 * @brief   Error handling routine.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 * @param[in] sr        UART SR register value
 */
static void set_error(SerialDriver *sdp, uint16_t sr) {
  eventflags_t sts = 0;

  if (sr & UART_LINE_STATUS_OE)
    sts |= SD_OVERRUN_ERROR;
  if (sr & UART_LINE_STATUS_PE)
    sts |= SD_PARITY_ERROR;
  if (sr & UART_LINE_STATUS_FE)
    sts |= SD_FRAMING_ERROR;
  if (sr & UART_LINE_STATUS_DR)
    sts |= SD_NOISE_ERROR;
  chnAddFlagsI(sdp, sts);
}

/**
 * @brief   Common IRQ handler.
 *
 * @param[in] sdp       communication channel associated to the UART
 */
static void serve_interrupt(SerialDriver *sdp) {
  UART_TypeDef *u = sdp->uart;
  uint32_t sr,ier;
  uint8_t rbyte;
  uint8_t int_id;

  int_id = (u->IIR & UART_IIR_INTID_Msk);
  sr = (uint32_t) u->LSR;
  ier = u->IER;

  /* Special case, LIN break detection.*/
  if ((int_id & UART_INTID_RLS) == UART_INTID_RLS) {
    osalSysLockFromISR();
    chnAddFlagsI(sdp, SD_BREAK_DETECTED);
    osalSysUnlockFromISR();
  }

  /* Data available.*/
  osalSysLockFromISR();
  while ((sr & (UART_LINE_STATUS_PE | UART_LINE_STATUS_FE | UART_LINE_STATUS_OE |
               UART_LINE_STATUS_DR |UART_LINE_STATUS_BI)) | 
               ((u-USR & UART_FLAG_RFNE) != RESET)) {
    uint8_t b;

    /* Error condition detection.*/
    if (sr & (UART_SR_ORE | UART_SR_NE | UART_SR_FE  | UART_SR_PE))
      set_error(sdp, sr);
    b = (uint8_t)u->RBR & sdp->rxmask;
    if ((u->USR & UART_FLAG_RFNE) != RESET)
      sdIncomingDataI(sdp, b);
    sr = (uint32_t) u->LSR;
  }
  osalSysUnlockFromISR();

  /* Transmission buffer empty.*/
  if ((ier & UART_IT_THRE) && ((sr & UART_LINE_STATUS_THRE) != RESET)) {
    msg_t b;
    osalSysLockFromISR();
    b = oqGetI(&sdp->oqueue);
    if (b < MSG_OK) {
      chnAddFlagsI(sdp, CHN_OUTPUT_EMPTY);
      u->IER &= ~(UART_IT_THRE);
    }
    else
      u->THR = b;
    osalSysUnlockFromISR();
  }

  /* Physical transmission end.*/
  if ((ier & UART_IT_THRE) && ((sr & UART_LINE_STATUS_TEMT) != RESET)) {
    osalSysLockFromISR();
    if (oqIsEmptyI(&sdp->oqueue)) {
      chnAddFlagsI(sdp, CHN_TRANSMISSION_END);
      u->CR1 = cr1 & ~UART_CR1_TCIE;
    }
    osalSysUnlockFromISR();
  }
}

#if WB32_SERIAL_USE_UART1 || defined(__DOXYGEN__)
static void notify1(io_queue_t *qp) {

  (void)qp;
  UART1->IER |= UART_IT_THRE;
}
#endif

#if WB32_SERIAL_USE_UART2 || defined(__DOXYGEN__)
static void notify2(io_queue_t *qp) {

  (void)qp;
  UART2->IER |= UART_IT_THRE;
}
#endif

#if WB32_SERIAL_USE_UART3 || defined(__DOXYGEN__)
static void notify3(io_queue_t *qp) {

  (void)qp;
  UART3->IER |= UART_IT_THRE;
}
#endif

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if WB32_SERIAL_USE_UART1 || defined(__DOXYGEN__)
#if !defined(WB32_UART1_HANDLER)
#error "WB32_UART1_HANDLER not defined"
#endif
/**
 * @brief   UART1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(WB32_UART1_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  serve_interrupt(&SD1);

  OSAL_IRQ_EPILOGUE();
}
#endif

#if WB32_SERIAL_USE_UART2 || defined(__DOXYGEN__)
#if !defined(WB32_UART2_HANDLER)
#error "WB32_UART2_HANDLER not defined"
#endif
/**
 * @brief   UART2 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(WB32_UART2_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  serve_interrupt(&SD2);

  OSAL_IRQ_EPILOGUE();
}
#endif

#if WB32_SERIAL_USE_UART3 || defined(__DOXYGEN__)
#if !defined(WB32_UART3_HANDLER)
#error "WB32_UART3_HANDLER not defined"
#endif
/**
 * @brief   UART3 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(WB32_UART3_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  serve_interrupt(&SD3);

  OSAL_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level serial driver initialization.
 *
 * @notapi
 */
void sd_lld_init(void) {

#if WB32_SERIAL_USE_UART1
  sdObjectInit(&SD1, NULL, notify1);
  SD1.uart = UART1;
#endif

#if WB32_SERIAL_USE_UART2
  sdObjectInit(&SD2, NULL, notify2);
  SD2.uart = UART2;
#endif

#if WB32_SERIAL_USE_UART3
  sdObjectInit(&SD3, NULL, notify3);
  SD3.uart = UART3;
#endif
}

/**
 * @brief   Low level serial driver configuration and (re)start.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 * @param[in] config    the architecture-dependent serial driver configuration.
 *                      If this parameter is set to @p NULL then a default
 *                      configuration is used.
 *
 * @notapi
 */
void sd_lld_start(SerialDriver *sdp, const SerialConfig *config) {

  if (config == NULL)
    config = &default_config;

  if (sdp->state == SD_STOP) {
#if WB32_SERIAL_USE_UART1
    if (&SD1 == sdp) {
      /* UART1 clock enable */
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_BMX1 | RCC_APB1Periph_UART1, ENABLE);
      nvicEnableVector(WB32_UART1_NUMBER, WB32_SERIAL_UART1_PRIORITY);
    }
#endif
#if WB32_SERIAL_USE_UART2
    if (&SD2 == sdp) {
       /* UART2 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_BMX2 | RCC_APB2Periph_UART2, ENABLE);
      nvicEnableVector(WB32_UART2_NUMBER, WB32_SERIAL_UART2_PRIORITY);
    }
#endif
#if WB32_SERIAL_USE_UART3
    if (&SD3 == sdp) {
      /* UART3 clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_BMX2 | RCC_APB2Periph_UART3, ENABLE);
      nvicEnableVector(WB32_UART3_NUMBER, WB32_SERIAL_UART3_PRIORITY);
    }
#endif
  }
  uart_init(sdp, config);
}

/**
 * @brief   Low level serial driver stop.
 * @details De-initializes the UART, stops the associated clock, resets the
 *          interrupt vector.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 *
 * @notapi
 */
void sd_lld_stop(SerialDriver *sdp) {

  if (sdp->state == SD_READY) {
    uart_deinit(sdp->uart);
#if WB32_SERIAL_USE_UART1
    if (&SD1 == sdp) {
      /* UART1 DeInit */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART1, DISABLE);
      nvicDisableVector(WB32_UART1_NUMBER);
      return;
    }
#endif
#if WB32_SERIAL_USE_UART2
    if (&SD2 == sdp) {
      /* UART2 DeInit */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART2, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART2, DISABLE);
      nvicDisableVector(WB32_UART2_NUMBER);
      return;
    }
#endif
#if WB32_SERIAL_USE_UART3
    if (&SD3 == sdp) {
      /* UART3 DeInit */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART3, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_UART3, DISABLE);
      nvicDisableVector(WB32_UART3_NUMBER);
      return;
    }
#endif
  }
}

#endif /* HAL_USE_SERIAL */

/** @} */
