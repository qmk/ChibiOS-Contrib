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
 * @file    DMAv1/wb32_dma.h
 * @brief   DMA helper driver header.
 * @note    This driver uses the new naming convention used for the WB32F2xx
 *          so the "DMA channels" are referred as "DMA streams".
 *
 * @addtogroup WB32_DMA
 * @{
 */

#ifndef WB32_DMA_H
#define WB32_DMA_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Total number of DMA streams.
 * @details This is the total number of streams among all the DMA units.
 */
#define WB32_DMAC_CHANNELS (WB32_DMAC1_NUM_CHANNELS + \
                            WB32_DMAC2_NUM_CHANNELS)

/**
 * @brief   Mask of the ISR bits passed to the DMA callback functions.
 */
#define WB32_DMA_ISR_MASK 0x0E

/**
 * @brief   Returns the request line associated to the specified stream.
 * @note    In some WB32 manuals the request line is named confusingly
 *          channel.
 *
 * @param[in] id        the unique numeric stream identifier
 * @param[in] c         a stream/request association word, one request per
 *                      nibble
 * @return              Returns the request associated to the stream.
 */
#define WB32_DMA_GETCHANNEL(id, c) \
  (((uint32_t)(c) >> (((uint32_t)(id) % (uint32_t)WB32_DMAC1_NUM_CHANNELS) * 4U)) & 15U)

/**
 * @brief   Checks if a DMA priority is within the valid range.
 * @param[in] prio      DMA priority
 *
 * @retval              The check result.
 * @retval false        invalid DMA priority.
 * @retval true         correct DMA priority.
 */
#define WB32_DMA_IS_VALID_PRIORITY(prio) (((prio) >= 0U) && ((prio) <= 3U))

#if (WB32_DMA_SUPPORTS_DMAMUX == FALSE) || defined(_DOXYGEN__)
/**
 * @brief   Checks if a DMA stream id is within the valid range.
 *
 * @param[in] id        DMA stream id
 * @retval              The check result.
 * @retval false        invalid DMA channel.
 * @retval true         correct DMA channel.
 */
#define WB32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) && \
                                      ((id) < WB32_DMAC_CHANNELS))
#else /* WB32_DMA_SUPPORTS_DMAMUX == FALSE */
#if WB32_DMAC2_NUM_CHANNELS > 0
#define WB32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) && \
                                      ((id) <= (WB32_DMAC_CHANNELS + 2)))
#else
#define WB32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) && \
                                      ((id) <= (WB32_DMAC_CHANNELS + 1)))
#endif
#endif /* WB32_DMA_SUPPORTS_DMAMUX == FALSE */

/**
 * @brief   Returns an unique numeric identifier for a DMA stream.
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              An unique numeric stream identifier.
 */
#define WB32_DMA_STREAM_ID(dma, stream) \
  ((((dma)-1) * WB32_DMAC1_NUM_CHANNELS) + (stream))

/**
 * @brief   Returns a DMA stream identifier mask.
 *
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              A DMA stream identifier mask.
 */
#define WB32_DMA_STREAM_ID_MSK(dma, stream) \
  (1U << WB32_DMA_STREAM_ID(dma, stream))

/**
 * @brief   Checks if a DMA stream unique identifier belongs to a mask.
 *
 * @param[in] id        the stream numeric identifier
 * @param[in] mask      the stream numeric identifiers mask
 *
 * @retval              The check result.
 * @retval false        id does not belong to the mask.
 * @retval true         id belongs to the mask.
 */
#define WB32_DMA_IS_VALID_ID(id, mask) (((1U << (id)) & (mask)))

#if (WB32_DMA_SUPPORTS_DMAMUX == TRUE) || defined(_DOXYGEN__)
/**
 * @name    Special stream identifiers
 * @{
 */
#define WB32_DMA_STREAM_ID_ANY WB32_DMAC_CHANNELS
#define WB32_DMA_STREAM_ID_ANY_DMA1 (WB32_DMA_STREAM_ID_ANY + 1)
#if WB32_DMAC2_NUM_CHANNELS > 0
#define WB32_DMA_STREAM_ID_ANY_DMA2 (WB32_DMA_STREAM_ID_ANY_DMA1 + 1)
#endif
/** @} */
#endif

/**
 * @name    DMA streams identifiers
 * @{
 */
/**
 * @brief   Returns a pointer to a wb32_dma_stream_t structure.
 *
 * @param[in] id        the stream numeric identifier
 * @return              A pointer to the wb32_dma_stream_t constant structure
 *                      associated to the DMA stream.
 */
#define WB32_DMA_STREAM(id) (&_WB32_DMAC_CHANNELS[id])

#if WB32_DMAC1_NUM_CHANNELS > 0
#define WB32_DMA1_STREAM1 WB32_DMA_STREAM(0)
#endif
#if WB32_DMAC1_NUM_CHANNELS > 1
#define WB32_DMA1_STREAM2 WB32_DMA_STREAM(1)
#endif
#if WB32_DMAC1_NUM_CHANNELS > 2
#define WB32_DMA1_STREAM3 WB32_DMA_STREAM(2)
#endif
#if WB32_DMAC2_NUM_CHANNELS > 0
#define WB32_DMA2_STREAM1 WB32_DMA_STREAM(WB32_DMAC1_NUM_CHANNELS + 0)
#endif
#if WB32_DMAC2_NUM_CHANNELS > 1
#define WB32_DMA2_STREAM2 WB32_DMA_STREAM(WB32_DMAC1_NUM_CHANNELS + 1)
#endif
#if WB32_DMAC2_NUM_CHANNELS > 2
#define WB32_DMA2_STREAM3 WB32_DMA_STREAM(WB32_DMAC1_NUM_CHANNELS + 2)
#endif
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !defined(WB32_DMAC1_NUM_CHANNELS)
#error "WB32_DMAC1_NUM_CHANNELS not defined in registry"
#endif

#if !defined(WB32_DMAC2_NUM_CHANNELS)
#error "WB32_DMAC2_NUM_CHANNELS not defined in registry"
#endif

#if (WB32_DMAC1_NUM_CHANNELS < 0) || (WB32_DMAC1_NUM_CHANNELS > 3)
#error "unsupported channels configuration"
#endif

#if (WB32_DMAC2_NUM_CHANNELS < 0) || (WB32_DMAC2_NUM_CHANNELS > 3)
#error "unsupported channels configuration"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a DMA callback.
 *
 * @param[in] p         parameter for the registered function
 * @param[in] flags     pre-shifted content of the ISR register, the bits
 *                      are aligned to bit zero
 */
// typedef void (*wb32_dmaisr_t)(DMAC_TypeDef *DMACx, uint8_t DMAC_Channel, uint16_t DMAC_IT);
typedef void (*wb32_dmaisr_t)(void *p, uint32_t flags);

/**
 * @brief   WB32 DMA stream descriptor structure.
 */
typedef struct
{
  DMAC_TypeDef *dmac;   /**< @brief Associated DMA.         */
  uint8_t dmac_channel; /**< @brief Associated DMA channel. */
  uint32_t cmask;       /**< @brief Mask of streams sharing
                                             the same ISR.  */
  uint8_t selfindex;    /**< @brief Index to self in array. */
  uint8_t vector;       /**< @brief Associated IRQ vector.  */
} wb32_dma_stream_t;

/** @defgroup DMAC_Interrupt 
  * @{
  */
#define DMAC_Interrupt_Enable ((uint32_t)0x00000001)
#define DMAC_Interrupt_Disable ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMAC_SourceTransferWidth 
  * @{
  */
#define DMAC_SourceTransferWidth_8b DMAC_CTLL_SRC_TR_WIDTH_8
#define DMAC_SourceTransferWidth_16b DMAC_CTLL_SRC_TR_WIDTH_16
#define DMAC_SourceTransferWidth_32b DMAC_CTLL_SRC_TR_WIDTH_32
/**
  * @}
  */

/** @defgroup DMAC_DestinationTransferWidth 
  * @{
  */
#define DMAC_DestinationTransferWidth_8b DMAC_CTLL_DST_TR_WIDTH_8
#define DMAC_DestinationTransferWidth_16b DMAC_CTLL_DST_TR_WIDTH_16
#define DMAC_DestinationTransferWidth_32b DMAC_CTLL_DST_TR_WIDTH_32
/**
  * @}
  */

/** @defgroup DMAC_SourceAddrInc 
  * @{
  */
#define DMAC_SourceAddrInc_Increment DMAC_CTLL_SINC_INC
#define DMAC_SourceAddrInc_Decrement DMAC_CTLL_SINC_DEC
#define DMAC_SourceAddrInc_NoChange DMAC_CTLL_SINC_NO
/**
  * @}
  */

/** @defgroup DMAC_DestinationAddrInc 
  * @{
  */
#define DMAC_DestinationAddrInc_Increment DMAC_CTLL_DINC_INC
#define DMAC_DestinationAddrInc_Decrement DMAC_CTLL_DINC_DEC
#define DMAC_DestinationAddrInc_NoChange DMAC_CTLL_DINC_NO
/**
  * @}
  */

/** @defgroup DMAC_SourceTransactionLength 
  * @{
  */
#define DMAC_SourceTransactionLength_1 DMAC_CTLL_SRC_MSIZE_1
#define DMAC_SourceTransactionLength_4 DMAC_CTLL_SRC_MSIZE_4
#define DMAC_SourceTransactionLength_8 DMAC_CTLL_SRC_MSIZE_8
/**
  * @}
  */

/** @defgroup DMAC_DestinationTransactionLength 
  * @{
  */
#define DMAC_DestinationTransactionLength_1 DMAC_CTLL_DEST_MSIZE_1
#define DMAC_DestinationTransactionLength_4 DMAC_CTLL_DEST_MSIZE_4
#define DMAC_DestinationTransactionLength_8 DMAC_CTLL_DEST_MSIZE_8
/**
  * @}
  */

/** @defgroup DMAC_TransferTypeAndFlowControl 
  * @{
  */
#define DMAC_TransferTypeAndFlowControl_MemoryToMemory_DMAC DMAC_CTLL_TT_FC_M2M_DMAC
#define DMAC_TransferTypeAndFlowControl_MemoryToPeripheral_DMAC DMAC_CTLL_TT_FC_M2P_DMAC
#define DMAC_TransferTypeAndFlowControl_PeripheralToMemory_DMAC DMAC_CTLL_TT_FC_P2M_DMAC
#define DMAC_TransferTypeAndFlowControl_PeripheralToPeripheral_DMAC DMAC_CTLL_TT_FC_P2P_DMAC
/* The following definitions is only used for DMACx channel0. */
#define DMAC_TransferTypeAndFlowControl_PeripheralToMemory_Peripheral DMAC_CTLL_TT_FC_P2M_PERIPH
#define DMAC_TransferTypeAndFlowControl_PeripheralToPeripheral_SourcePeripheral DMAC_CTLL_TT_FC_P2P_SRC_PERIPH
#define DMAC_TransferTypeAndFlowControl_MemoryToPeripheral_Peripheral DMAC_CTLL_TT_FC_M2P_PERIPH
#define DMAC_TransferTypeAndFlowControl_PeripheralToPeripheral_DestinationPeripheral DMAC_CTLL_TT_FC_P2P_DST_PERIPH
/**
  * @}
  */

/** @defgroup DMAC_SourceMasterInterface 
  * @{
  */
#define DMAC_SourceMasterInterface_APB (0x0U << 25)
#define DMAC_SourceMasterInterface_AHB (0x1U << 25)
/**
  * @}
  */

/** @defgroup DMAC_DestinationMasterInterface 
  * @{
  */
#define DMAC_DestinationMasterInterface_APB (0x0U << 23)
#define DMAC_DestinationMasterInterface_AHB (0x1U << 23)
/**
  * @}
  */

/** @defgroup DMAC_SourceHandshakingInterfaceSelect 
  * @{
  */
#define DMAC_SourceHandshakingInterfaceSelect_Hardware (0x0U << 11)
#define DMAC_SourceHandshakingInterfaceSelect_Software (0x1U << 11)
/**
  * @}
  */

/** @defgroup DMAC_DestinationHandshakingInterfaceSelect 
  * @{
  */
#define DMAC_DestinationHandshakingInterfaceSelect_Hardware (0x0U << 10)
#define DMAC_DestinationHandshakingInterfaceSelect_Software (0x1U << 10)
/**
  * @}
  */

/** @defgroup DMAC_SourceHandshakingInterfacePolarity 
  * @{
  */
#define DMAC_SourceHandshakingInterfacePolarity_High (0x0U << 19)
#define DMAC_SourceHandshakingInterfacePolarity_Low (0x1U << 19)
/**
  * @}
  */

/** @defgroup DMAC_DestinationHandshakingInterfacePolarity 
  * @{
  */
#define DMAC_DestinationHandshakingInterfacePolarity_High (0x0U << 18)
#define DMAC_DestinationHandshakingInterfacePolarity_Low (0x1U << 18)
/**
  * @}
  */

/** @defgroup DMAC_AutomaticSourceReload 
  * @{
  */
#define DMAC_AutomaticSourceReload_Enable (DMAC_CFGL_RELOAD_SRC)
#define DMAC_AutomaticSourceReload_Disable ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMAC_AutomaticDestinationReload 
  * @{
  */
#define DMAC_AutomaticDestinationReload_Enable (DMAC_CFGL_RELOAD_DST)
#define DMAC_AutomaticDestinationReload_Disable ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup DMAC_FlowControlMode 
  * @{
  */
#define DMAC_FlowControlMode_0 (0x0U << 0)
#define DMAC_FlowControlMode_1 (0x1U << 0)
/**
  * @}
  */

/** @defgroup DMAC_FIFOMode 
  * @{
  */
#define DMAC_FIFOMode_0 (0x0U << 1)
#define DMAC_FIFOMode_1 (0x1U << 1)
/**
  * @}
  */

/** @defgroup DMAC_HardwareHandshakingInterface 
  * @{
  */
/* The following definitions is only used for DMAC1. */
#define DMAC_HardwareHandshakingInterface_TIM1_CH1__TIM2_UP__TIM3_CH3 0
#define DMAC_HardwareHandshakingInterface_TIM1_CH4__TIM1_TRIG__TIM1_COM__TIM4_CH2 1
#define DMAC_HardwareHandshakingInterface_TIM1_UP__TIM2_CH1__TIM4_CH3 2
#define DMAC_HardwareHandshakingInterface_TIM1_CH3__TIM3_CH1__TIM3_TRIG 3
#define DMAC_HardwareHandshakingInterface_TIM2_CH3__TIM4_CH1 4
#define DMAC_HardwareHandshakingInterface_TIM2_CH2__TIM2_CH4__TIM4_UP 5
#define DMAC_HardwareHandshakingInterface_TIM3_CH4__TIM3_UP__TIM1_CH2 6
#define DMAC_HardwareHandshakingInterface_QSPI_RX 7
#define DMAC_HardwareHandshakingInterface_QSPI_TX 8
#define DMAC_HardwareHandshakingInterface_SPIS1_RX 9
#define DMAC_HardwareHandshakingInterface_SPIS1_TX 10
#define DMAC_HardwareHandshakingInterface_UART1_RX 11
#define DMAC_HardwareHandshakingInterface_UART1_TX 12
#define DMAC_HardwareHandshakingInterface_ADC_Regular 13
#define DMAC_HardwareHandshakingInterface_ADC_Injected 14

/* The following definitions is only used for DMAC2. */
#define DMAC_HardwareHandshakingInterface_SPIM2_RX 0
#define DMAC_HardwareHandshakingInterface_SPIM2_TX 1
#define DMAC_HardwareHandshakingInterface_SPIS2_RX 2
#define DMAC_HardwareHandshakingInterface_SPIS2_TX 3
#define DMAC_HardwareHandshakingInterface_UART2_RX 4
#define DMAC_HardwareHandshakingInterface_UART2_TX 5
#define DMAC_HardwareHandshakingInterface_UART3_RX 6
#define DMAC_HardwareHandshakingInterface_UART3_TX 7
#define DMAC_HardwareHandshakingInterface_I2C1_RX 8
#define DMAC_HardwareHandshakingInterface_I2C1_TX 9
#define DMAC_HardwareHandshakingInterface_I2C2_RX 10
#define DMAC_HardwareHandshakingInterface_I2C2_TX 11
/**
  * @}
  */

/** @defgroup DMAC_channel 
  * @{
  */
#define DMAC_Channel_0 ((uint8_t)0x00)
#define DMAC_Channel_1 ((uint8_t)0x01)
#define DMAC_Channel_2 ((uint8_t)0x02)
/**
  * @}
  */

/** @defgroup DMAC_interrupts_definitions 
  * @{
  */
#define DMAC_IT_TFR ((uint16_t)0x0000)     /* Transfer complete interrupt */
#define DMAC_IT_BLOCK ((uint16_t)0x0008)   /* Block complete interrupt */
#define DMAC_IT_SRCTRAN ((uint16_t)0x0010) /* Source transaction complete interrupt */
#define DMAC_IT_DSTTRAN ((uint16_t)0x0018) /* Destination transaction complete interrupt */
#define DMAC_IT_ERR ((uint16_t)0x0020)     /* Error interrupt */
/**
  * @}
  */

/**
 * @brief   WB32 DMA channel configuration structure.
 */
typedef struct
{
  /*!< Specifies the source base address. */
  uint32_t DMAC_SourceBaseAddr;
  /*!< Specifies the destination base address. */
  uint32_t DMAC_DestinationBaseAddr;
  /*!< Specifies the global interrupt enable/disable for the channel.
  This parameter can be a value of @ref DMAC_Interrupt */
  uint32_t DMAC_Interrupt;
  /*!< Specifies the source transfer width.
  This parameter can be a value of @ref DMAC_SourceTransferWidth */
  uint32_t DMAC_SourceTransferWidth;
  /*!< Specifies the destination transfer width.
  This parameter can be a value of @ref DMAC_DestinationTransferWidth */
  uint32_t DMAC_DestinationTransferWidth;
  /*!< Specifies whether to increment or decrement the source address on every source transfer.
  This parameter can be a value of @ref DMAC_SourceAddrInc */
  uint32_t DMAC_SourceAddrInc;
  /*!< Specifies whether to increment or decrement the destination address on every destination transfer.
  This parameter can be a value of @ref DMAC_DestinationAddrInc */
  uint32_t DMAC_DestinationAddrInc;
  /*!< Specifies the source burst transaction length.
  This parameter can be a value of @ref DMAC_SourceTransactionLength */
  uint32_t DMAC_SourceTransactionLength;
  /*!< Specifies the destination burst transaction length.
  This parameter can be a value of @ref DMAC_DestinationTransactionLength */
  uint32_t DMAC_DestinationTransactionLength;
  /*!< Specifies the transfer type and flow control.
  This parameter can be a value of @ref DMAC_TransferTypeAndFlowControl */
  uint32_t DMAC_TransferTypeAndFlowControl;
  /*!< Specifies the Master Interface layer from which the source device (peripheral or memory) is accessed.
  This parameter can be a value of @ref DMAC_SourceMasterInterface */
  uint32_t DMAC_SourceMasterInterface;
  /*!< Specifies the Master Interface layer where the destination device (peripheral or memory) resides.
  This parameter can be a value of @ref DMAC_DestinationMasterInterface */
  uint32_t DMAC_DestinationMasterInterface;
  /*!< Specifies the block transfer size when the DMAC is the flow controller, in data unit.
  The data unit is equal to the configuration set in DMAC_SourceTransferWidth. */
  uint32_t DMAC_BlockTransferSize;
  /*!< Specifies which of the handshaking interfaces - hardware or software - is active for
  source requests on this channel. 
  This parameter can be a value of @ref DMAC_SourceHandshakingInterfaceSelect */
  uint32_t DMAC_SourceHandshakingInterfaceSelect;
  /*!< Specifies which of the handshaking interfaces - hardware or software - is active for
  destination requests on this channel.
  This parameter can be a value of @ref DMAC_DestinationHandshakingInterfaceSelect */
  uint32_t DMAC_DestinationHandshakingInterfaceSelect;
  /*!< Specifies the source handshaking interface polarity.
  This parameter can be a value of @ref DMAC_SourceHandshakingInterfacePolarity */
  uint32_t DMAC_SourceHandshakingInterfacePolarity;
  /*!< Specifies the destination handshaking interface polarity.
  This parameter can be a value of @ref DMAC_DestinationHandshakingInterfacePolarity */
  uint32_t DMAC_DestinationHandshakingInterfacePolarity;
  /*!< Specifies the automatic source reload feature enable or not.
  This parameter can be a value of @ref DMAC_AutomaticSourceReload */
  uint32_t DMAC_AutomaticSourceReload;
  /*!< Specifies the automatic destination reload feature enable or not.
  This parameter can be a value of @ref DMAC_AutomaticDestinationReload */
  uint32_t DMAC_AutomaticDestinationReload;
  /*!< Specifies the flow control mode.
  This parameter can be a value of @ref DMAC_FlowControlMode */
  uint32_t DMAC_FlowControlMode;
  /*!< Specifies the FIFO mode.
  This parameter can be a value of @ref DMAC_FIFOMode */
  uint32_t DMAC_FIFOMode;
  /*!< Specifies the channel priority. A priority of 2 is the highest priority, and 0 is the lowest. */
  uint8_t DMAC_ChannelPriority;
  /*!< Specifies the protection control, used to drive the AHB HPROT[3:1] bus.
  The AMBA Specification recommends that the default value of HPROT
  indicates a non-cached, non-buffered, privileged data access. */
  uint8_t DMAC_ProtectionControl;
  /*!< Specifies the hardware handshaking interface to the source of this channel if
  the configuration DMAC_SourceHandshakingInterfaceSelect is DMAC_SourceHandshakingInterfaceSelect_Hardware.
  This parameter can be a value of @ref DMAC_HardwareHandshakingInterface */
  uint8_t DMAC_SourceHardwareHandshakingInterfaceAssign;
  /*!< Specifies the hardware handshaking interface to the source of this channel if
  the configuration DMAC_DestinationHandshakingInterfaceSelect is DMAC_DestinationHandshakingInterfaceSelect_Hardware.
  This parameter can be a value of @ref DMAC_HardwareHandshakingInterface */
  uint8_t DMAC_DestinationHardwareHandshakingInterfaceAssign;
  /*!< Specifies the Maximum AMBA burst length that is used for DMA transfers on this channel.
  A value of 0 indicates that software is not limiting the maximum AMBA burst length
  for DMA transfers on this channel. */
  uint16_t DMAC_MaximumAMBABurstLength;
} DMAC_Channel_InitTypeDef;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Associates a peripheral data register to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @param[in] addr      value to be written in the SAR register
 *
 * @special
 */
#define dmaStreamSetSource(dmastp, addr)                               \
  {                                                                    \
    (dmastp)->dmac->Ch[(dmastp)->dmac_channel].SAR = (uint32_t)(addr); \
  }

/**
 * @brief   Associates a memory destination to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @param[in] addr      value to be written in the DAR register
 *
 * @special
 */
#define dmaStreamSetDestination(dmastp, addr)                          \
  {                                                                    \
    (dmastp)->dmac->Ch[(dmastp)->dmac_channel].DAR = (uint32_t)(addr); \
  }

/**
 * @brief   Sets the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @param[in] size      value to be written in the CTLH register   Size must be less than 511
 *
 * @special
 */
#define dmaStreamSetTransactionSize(dmastp, size)                               \
  {                                                                             \
    (dmastp)->dmac->Ch[(dmastp)->dmac_channel].CTLH = (uint32_t)((size)&0x1FF); \
  }

/**
 * @brief   Returns the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @return              The number of transfers to be performed.
 *
 * @special
 */
#define dmaStreamGetTransactionSize(dmastp) ((size_t)((dmastp)->dmac->Ch[(dmastp)->dmac_channel].CTLH))

/**
 * @brief   Programs the stream mode settings.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @param[in] mode      value to be written in that CTLL/CFGL/CFGH register
 *
 * @special
 */
#define dmaStreamSetMode(dmastp, mode)                                                                                      \
  {                                                                                                                         \
    (dmastp)->dmac->Ch[(dmastp)->dmac_channel].CTLL = (mode).DMAC_Interrupt |                                               \
                                                      (mode).DMAC_DestinationTransferWidth |                                \
                                                      (mode).DMAC_SourceTransferWidth |                                     \
                                                      (mode).DMAC_DestinationAddrInc |                                      \
                                                      (mode).DMAC_SourceAddrInc |                                           \
                                                      (mode).DMAC_DestinationTransactionLength |                            \
                                                      (mode).DMAC_SourceTransactionLength |                                 \
                                                      (mode).DMAC_TransferTypeAndFlowControl |                              \
                                                      (mode).DMAC_DestinationMasterInterface |                              \
                                                      (mode).DMAC_SourceMasterInterface;                                    \
    (dmastp)->dmac->Ch[(dmastp)->dmac_channel].CFGL = ((mode).DMAC_ChannelPriority << 5) |                                  \
                                                      (mode).DMAC_DestinationHandshakingInterfaceSelect |                   \
                                                      (mode).DMAC_SourceHandshakingInterfaceSelect |                        \
                                                      (mode).DMAC_DestinationHandshakingInterfacePolarity |                 \
                                                      (mode).DMAC_SourceHandshakingInterfacePolarity |                      \
                                                      ((mode).DMAC_MaximumAMBABurstLength << 20) |                          \
                                                      (mode).DMAC_AutomaticSourceReload |                                   \
                                                      (mode).DMAC_AutomaticDestinationReload;                               \
    (dmastp)->dmac->Ch[(dmastp)->dmac_channel].CFGH = (mode).DMAC_FlowControlMode |                                      \
                                                         (mode).DMAC_FIFOMode |                                             \
                                                         ((mode).DMAC_ProtectionControl << 2) |                             \
                                                         ((mode).DMAC_SourceHardwareHandshakingInterfaceAssign << 7) |      \
                                                         ((mode).DMAC_DestinationHardwareHandshakingInterfaceAssign << 11); \
  }

/**
 * @brief   DMA stream enable interrupt configuration.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @param[in] it_flag   specifies the DMAC interrupt source to be enabled or disabled.
 *
 * @special
 */
#define dmaStreamEnableInterrupt(dmastp, it_flag)                          \
  {                                                                        \
    uint32_t mask = (uint32_t)(0x01U << ((dmastp)->dmac_channel));         \
    uint32_t regaddr = ((uint32_t)(&((dmastp)->dmac->MaskTfr)) + it_flag); \
    *((__O uint32_t *)(regaddr)) = (mask << 8) | mask;                     \
  }

/**
 * @brief   DMA stream disable interrupt configuration.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @param[in] it_flag   specifies the DMAC interrupt source to be enabled or disabled.
 *
 * @special
 */
#define dmaStreamDisableInterrupt(dmastp, it_flag)                         \
  {                                                                        \
    uint32_t mask = (uint32_t)(0x01U << ((dmastp)->dmac_channel));         \
    uint32_t regaddr = ((uint32_t)(&((dmastp)->dmac->MaskTfr)) + it_flag); \
    *((__O uint32_t *)(regaddr)) = (mask << 8);                            \
  }

/**
 * @brief   DMA stream enable interrupt configuration all.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamEnableInterruptAll(dmastp)            \
  {                                                    \
    dmaStreamEnableInterrupt(dmastp, DMAC_IT_TFR);     \
    dmaStreamEnableInterrupt(dmastp, DMAC_IT_BLOCK);   \
    dmaStreamEnableInterrupt(dmastp, DMAC_IT_SRCTRAN); \
    dmaStreamEnableInterrupt(dmastp, DMAC_IT_DSTTRAN); \
    dmaStreamEnableInterrupt(dmastp, DMAC_IT_ERR);     \
  }

/**
 * @brief   DMA stream disable interrupt configuration all.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamDisableInterruptAll(dmastp)            \
  {                                                     \
    dmaStreamDisableInterrupt(dmastp, DMAC_IT_TFR);     \
    dmaStreamDisableInterrupt(dmastp, DMAC_IT_BLOCK);   \
    dmaStreamDisableInterrupt(dmastp, DMAC_IT_SRCTRAN); \
    dmaStreamDisableInterrupt(dmastp, DMAC_IT_DSTTRAN); \
    dmaStreamDisableInterrupt(dmastp, DMAC_IT_ERR);     \
  }

/**
 * @brief   DMA stream interrupt sources clear.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamClearInterrupt(dmastp)                                         \
  {                                                                             \
    uint32_t mask = (uint32_t)(0x01U << ((dmastp)->dmac_channel));              \
    uint32_t regaddr = ((uint32_t)(&((dmastp)->dmac->ClearTfr)) + DMAC_IT_TFR); \
    *((__O uint32_t *)(regaddr)) = mask;                                        \
    regaddr = ((uint32_t)(&((dmastp)->dmac->ClearTfr)) + DMAC_IT_BLOCK);        \
    *((__O uint32_t *)(regaddr)) = mask;                                        \
    regaddr = ((uint32_t)(&((dmastp)->dmac->ClearTfr)) + DMAC_IT_SRCTRAN);      \
    *((__O uint32_t *)(regaddr)) = mask;                                        \
    regaddr = ((uint32_t)(&((dmastp)->dmac->ClearTfr)) + DMAC_IT_DSTTRAN);      \
    *((__O uint32_t *)(regaddr)) = mask;                                        \
    regaddr = ((uint32_t)(&((dmastp)->dmac->ClearTfr)) + DMAC_IT_ERR);          \
    *((__O uint32_t *)(regaddr)) = mask;                                        \
  }

/**
 * @brief   DMA stream enable.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamEnable(dmastp)                                    \
  {                                                                \
    uint32_t mask = (uint32_t)(0x01U << ((dmastp)->dmac_channel)); \
    (dmastp)->dmac->ChEnReg = (mask << 8) | mask;                  \
  }

/**
 * @brief   DMA stream disable.
 * @details The function disables the specified stream and then clears any
 *          pending interrupt.
 * @note    This function can be invoked in both ISR or thread context.
 * @note    Interrupts enabling flags are set to zero after this call, see
 *          bug 3607518.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamDisable(dmastp)                                   \
  {                                                                \
    uint32_t mask = (uint32_t)(0x01U << ((dmastp)->dmac_channel)); \
    (dmastp)->dmac->ChEnReg = (mask << 8);                         \
    dmaStreamDisableInterruptAll(dmastp);                          \
    dmaStreamClearInterrupt(dmastp);                               \
  }

/**
 * @brief   Starts a memory to memory operation using the specified stream.
 * @note    The default transfer data mode is "byte to byte" but it can be
 *          changed by specifying extra options in the @p mode parameter.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 * @param[in] mode      value to be written in the CCR register, this value
 *                      is implicitly ORed with:
 *                      - @p DMAC_DestinationAddrInc_Increment
 *                      - @p DMAC_SourceAddrInc_Increment
 *                      - @p DMAC_TransferTypeAndFlowControl_MemoryToMemory_DMAC
 *                      .
 * @param[in] src       source address
 * @param[in] dst       destination address
 * @param[in] n         number of data units to copy
 */
#define dmaStartMemCopy(dmastp, mode, src, dst, n)                                     \
  {                                                                                    \
    dmaStreamSetSource(dmastp, src);                                                   \
    dmaStreamSetDestination(dmastp, dst);                                              \
    dmaStreamSetTransactionSize(dmastp, n);                                            \
    dmaStreamSetMode(dmastp, (mode) |                                                  \
                                 DMAC_DestinationAddrInc_Increment |                   \
                                 DMAC_SourceAddrInc_Increment |                        \
                                 DMAC_TransferTypeAndFlowControl_MemoryToMemory_DMAC); \
    dmaStreamEnable(dmastp);                                                           \
  }

/**
 * @brief   Polled wait for DMA transfer end.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamRelease().
 *
 * @param[in] dmastp    pointer to a wb32_dma_stream_t structure
 */
#define dmaWaitCompletion(dmastp)                                                \
  {                                                                              \
    while (((dmastp)->dmac->Ch[(dmastp)->dmac_channel].CTLH & 0x00000FFFU) > 0U) \
      ;                                                                          \
    dmaStreamDisable(dmastp);                                                    \
  }
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
extern const wb32_dma_stream_t _WB32_DMAC_CHANNELS[WB32_DMAC_CHANNELS];
#endif

#ifdef __cplusplus
extern "C"
{
#endif
  void dmaInit(void);
  const wb32_dma_stream_t *dmaStreamAllocI(uint32_t id,
                                           uint32_t priority,
                                           wb32_dmaisr_t func,
                                           void *param);
  const wb32_dma_stream_t *dmaStreamAlloc(uint32_t id,
                                          uint32_t priority,
                                          wb32_dmaisr_t func,
                                          void *param);
  void dmaStreamFreeI(const wb32_dma_stream_t *dmastp);
  void dmaStreamFree(const wb32_dma_stream_t *dmastp);
  void dmaServeInterrupt(const wb32_dma_stream_t *dmastp);
#if WB32_DMA_SUPPORTS_DMAMUX == TRUE
  void dmaSetRequestSource(const wb32_dma_stream_t *dmastp, uint32_t per);
#endif
#ifdef __cplusplus
}
#endif

#endif /* WB32_DMA_H */

/** @} */
