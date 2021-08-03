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
 * @file    SPIv1/hal_spi_lld.h
 * @brief   WB32 SPI subsystem low level driver header.
 *
 * @addtogroup SPI
 * @{
 */

#ifndef HAL_SPI_LLD_H
#define HAL_SPI_LLD_H

#if HAL_USE_SPI || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Circular mode support flag.
 */
#define SPI_SUPPORTS_CIRCULAR FALSE


/** @defgroup SPI_Exported_Constants
  * @{
  */

/** @defgroup SPI_transfer_mode
  * @{
  */
#define SPI_TransferMode_TxAndRx        ((uint16_t)SPI_CR0_TMOD_TX_AND_RX)
#define SPI_TransferMode_TxOnly         ((uint16_t)SPI_CR0_TMOD_TX_ONLY)
#define SPI_TransferMode_RxOnly         ((uint16_t)SPI_CR0_TMOD_RX_ONLY)
#define SPI_TransferMode_EepromRead     ((uint16_t)SPI_CR0_TMOD_EEPROM_READ)
/**
  * @}
  */


/** @defgroup SPI_data_size
  * @{
  */
#define SPI_DataSize_4b                 ((uint16_t)SPI_CR0_DFS_4BITS)
#define SPI_DataSize_5b                 ((uint16_t)SPI_CR0_DFS_5BITS)
#define SPI_DataSize_6b                 ((uint16_t)SPI_CR0_DFS_6BITS)
#define SPI_DataSize_7b                 ((uint16_t)SPI_CR0_DFS_7BITS)
#define SPI_DataSize_8b                 ((uint16_t)SPI_CR0_DFS_8BITS)
#define SPI_DataSize_9b                 ((uint16_t)SPI_CR0_DFS_9BITS)
#define SPI_DataSize_10b                ((uint16_t)SPI_CR0_DFS_10BITS)
#define SPI_DataSize_11b                ((uint16_t)SPI_CR0_DFS_11BITS)
#define SPI_DataSize_12b                ((uint16_t)SPI_CR0_DFS_12BITS)
#define SPI_DataSize_13b                ((uint16_t)SPI_CR0_DFS_13BITS)
#define SPI_DataSize_14b                ((uint16_t)SPI_CR0_DFS_14BITS)
#define SPI_DataSize_15b                ((uint16_t)SPI_CR0_DFS_15BITS)
#define SPI_DataSize_16b                ((uint16_t)SPI_CR0_DFS_16BITS)
/**
  * @}
  */


/** @defgroup SPI_Clock_Polarity
  * @{
  */
#define SPI_CPOL_Low                    ((uint16_t)0x00)
#define SPI_CPOL_High                   ((uint16_t)0x80)
/**
  * @}
  */


/** @defgroup SPI_Clock_Phase
  * @{
  */
#define SPI_CPHA_1Edge                  ((uint16_t)0x00)
#define SPI_CPHA_2Edge                  ((uint16_t)0x40)
/**
  * @}
  */


/** @defgroup SPI_Frame_Format
  * @{
  */
#define SPI_FrameFormat_SPI             ((uint16_t)SPI_CR0_FRF_SPI)
#define SPI_FrameFormat_SSP             ((uint16_t)SPI_CR0_FRF_SSP)
#define SPI_FrameFormat_Microwire       ((uint16_t)SPI_CR0_FRF_NS)
/**
  * @}
  */


/** @defgroup SPI_Microwire_Control_Frame_Size
  * @{
  */
#define SPI_MicrowireControlFrameSize_1b      ((uint16_t)SPI_CR0_CFS_01_BIT)
#define SPI_MicrowireControlFrameSize_2b      ((uint16_t)SPI_CR0_CFS_02_BIT)
#define SPI_MicrowireControlFrameSize_3b      ((uint16_t)SPI_CR0_CFS_03_BIT)
#define SPI_MicrowireControlFrameSize_4b      ((uint16_t)SPI_CR0_CFS_04_BIT)
#define SPI_MicrowireControlFrameSize_5b      ((uint16_t)SPI_CR0_CFS_05_BIT)
#define SPI_MicrowireControlFrameSize_6b      ((uint16_t)SPI_CR0_CFS_06_BIT)
#define SPI_MicrowireControlFrameSize_7b      ((uint16_t)SPI_CR0_CFS_07_BIT)
#define SPI_MicrowireControlFrameSize_8b      ((uint16_t)SPI_CR0_CFS_08_BIT)
#define SPI_MicrowireControlFrameSize_9b      ((uint16_t)SPI_CR0_CFS_09_BIT)
#define SPI_MicrowireControlFrameSize_10b     ((uint16_t)SPI_CR0_CFS_10_BIT)
#define SPI_MicrowireControlFrameSize_11b     ((uint16_t)SPI_CR0_CFS_11_BIT)
#define SPI_MicrowireControlFrameSize_12b     ((uint16_t)SPI_CR0_CFS_12_BIT)
#define SPI_MicrowireControlFrameSize_13b     ((uint16_t)SPI_CR0_CFS_13_BIT)
#define SPI_MicrowireControlFrameSize_14b     ((uint16_t)SPI_CR0_CFS_14_BIT)
#define SPI_MicrowireControlFrameSize_15b     ((uint16_t)SPI_CR0_CFS_15_BIT)
#define SPI_MicrowireControlFrameSize_16b     ((uint16_t)SPI_CR0_CFS_16_BIT)
/**
  * @}
  */


/** @defgroup SPI_Microwire_Transfer_Mode
  * @{
  */
#define SPI_MicrowireTransferMode_NonSequential   ((uint16_t)0x00)
#define SPI_MicrowireTransferMode_Sequential      ((uint16_t)0x01)
/**
  * @}
  */


/** @defgroup SPI_Microwire_Direction
  * @{
  */
#define SPI_MicrowireDirection_Receive        ((uint16_t)0x00)
#define SPI_MicrowireDirection_Transmit       ((uint16_t)0x02)
/**
  * @}
  */


/** @defgroup SPI_Microwire_Handshaking
  * @{
  */
#define SPI_MicrowireHandshaking_Enable       ((uint16_t)0x04)
#define SPI_MicrowireHandshaking_Disable      ((uint16_t)0x00)
/**
  * @}
  */


/** @defgroup SPI_SpiMode
  * @{
  */
#define SPI_SpiMode_Standard   (SPI_CR0_SPI_MODE_STD)
#define SPI_SpiMode_Dual       (SPI_CR0_SPI_MODE_DUAL)
#define SPI_SpiMode_Quad       (SPI_CR0_SPI_MODE_QUAD)
/**
  * @}
  */


/** @defgroup SPI_EnhancedSpi_TransferType
  * @{
  */
#define SPI_EnhancedSpiTransferType_0         ((uint16_t)0x00)
#define SPI_EnhancedSpiTransferType_1         ((uint16_t)0x01)
#define SPI_EnhancedSpiTransferType_2         ((uint16_t)0x02)
/**
  * @}
  */


/** @defgroup SPI_EnhancedSpi_InstructionLength
  * @{
  */
#define SPI_EnhancedSpiInstructionLength_0b   ((uint16_t)SPI_ESPICR_INSTL_0BIT)
#define SPI_EnhancedSpiInstructionLength_4b   ((uint16_t)SPI_ESPICR_INSTL_4BIT)
#define SPI_EnhancedSpiInstructionLength_8b   ((uint16_t)SPI_ESPICR_INSTL_8BIT)
#define SPI_EnhancedSpiInstructionLength_16b  ((uint16_t)SPI_ESPICR_INSTL_16BIT)
/**
  * @}
  */


/** @defgroup SPI_EnhancedSpi_AddressLength
  * @{
  */
#define SPI_EnhancedSpiAddressLength_0b       ((uint16_t)SPI_ESPICR_ADDRL_0BIT)
#define SPI_EnhancedSpiAddressLength_4b       ((uint16_t)SPI_ESPICR_ADDRL_4BIT)
#define SPI_EnhancedSpiAddressLength_8b       ((uint16_t)SPI_ESPICR_ADDRL_8BIT)
#define SPI_EnhancedSpiAddressLength_12b      ((uint16_t)SPI_ESPICR_ADDRL_12BIT)
#define SPI_EnhancedSpiAddressLength_16b      ((uint16_t)SPI_ESPICR_ADDRL_16BIT)
#define SPI_EnhancedSpiAddressLength_20b      ((uint16_t)SPI_ESPICR_ADDRL_20BIT)
#define SPI_EnhancedSpiAddressLength_24b      ((uint16_t)SPI_ESPICR_ADDRL_24BIT)
#define SPI_EnhancedSpiAddressLength_28b      ((uint16_t)SPI_ESPICR_ADDRL_28BIT)
#define SPI_EnhancedSpiAddressLength_32b      ((uint16_t)SPI_ESPICR_ADDRL_32BIT)
#define SPI_EnhancedSpiAddressLength_36b      ((uint16_t)SPI_ESPICR_ADDRL_36BIT)
#define SPI_EnhancedSpiAddressLength_40b      ((uint16_t)SPI_ESPICR_ADDRL_40BIT)
#define SPI_EnhancedSpiAddressLength_44b      ((uint16_t)SPI_ESPICR_ADDRL_44BIT)
#define SPI_EnhancedSpiAddressLength_48b      ((uint16_t)SPI_ESPICR_ADDRL_48BIT)
#define SPI_EnhancedSpiAddressLength_52b      ((uint16_t)SPI_ESPICR_ADDRL_52BIT)
#define SPI_EnhancedSpiAddressLength_56b      ((uint16_t)SPI_ESPICR_ADDRL_56BIT)
#define SPI_EnhancedSpiAddressLength_60b      ((uint16_t)SPI_ESPICR_ADDRL_60BIT)
/**
  * @}
  */


/** @defgroup SPI_NSS_definition
  * @{
  */
#define SPI_NSS_0       (0x01)
#define SPI_NSS_1       (0x02)
#define SPI_NSS_2       (0x04)
/**
  * @}
  */


/** @defgroup SPI_flags_definition
  * @{
  */
#define SPI_FLAG_BUSY   ((uint8_t)SPI_SR_BUSY)
#define SPI_FLAG_TFNF   ((uint8_t)SPI_SR_TFNF)
#define SPI_FLAG_TFE    ((uint8_t)SPI_SR_TFE)
#define SPI_FLAG_RFNE   ((uint8_t)SPI_SR_RFNE)
#define SPI_FLAG_RFF    ((uint8_t)SPI_SR_RFF)
#define SPI_FLAG_TXERR  ((uint8_t)SPI_SR_TXERR)
#define SPI_FLAG_DCOL   ((uint8_t)SPI_SR_DCOL)
/**
  * @}
  */


/** @defgroup SPI_interrupts_definition
  * @{
  */
#define SPI_IT_TXE      (0x1 << 0)
#define SPI_IT_TXO      (0x1 << 1)
#define SPI_IT_RXU      (0x1 << 2)
#define SPI_IT_RXO      (0x1 << 3)
#define SPI_IT_RXF      (0x1 << 4)
#define SPI_IT_MST      (0x1 << 5)
/**
  * @}
  */


/** @defgroup SPI_DMA_Requests
  * @{
  */
#define SPI_DMAReq_Rx             0x01
#define SPI_DMAReq_Tx             0x02
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
 * @brief   QSPI driver enable switch.
 * @details If set to @p TRUE the support for QSPI is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_SPI_USE_QSPI) || defined(__DOXYGEN__)
#define WB32_SPI_USE_QSPI FALSE
#endif

/**
 * @brief   SPIM2 driver enable switch.
 * @details If set to @p TRUE the support for SPIM2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_SPI_USE_SPIM2) || defined(__DOXYGEN__)
#define WB32_SPI_USE_SPIM2 FALSE
#endif

/**
 * @brief   SPIS1 driver enable switch.
 * @details If set to @p TRUE the support for SPIS1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_SPI_USE_SPIS1) || defined(__DOXYGEN__)
#define WB32_SPI_USE_SPIS1 FALSE
#endif

/**
 * @brief   SPIS2 driver enable switch.
 * @details If set to @p TRUE the support for SPIS2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_SPI_USE_SPIS2) || defined(__DOXYGEN__)
#define WB32_SPI_USE_SPIS2 FALSE
#endif

/**
 * @brief   QSPI interrupt priority level setting.
 */
#if !defined(WB32_SPI_QSPI_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_QSPI_IRQ_PRIORITY 10
#endif

/**
 * @brief   SPIM2 interrupt priority level setting.
 */
#if !defined(WB32_SPI_SPIM2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_SPIM2_IRQ_PRIORITY 10
#endif

/**
 * @brief   SPIS1 interrupt priority level setting.
 */
#if !defined(WB32_SPI_SPIS1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_SPIS1_IRQ_PRIORITY 10
#endif

/**
 * @brief   SPIS2 interrupt priority level setting.
 */
#if !defined(WB32_SPI_SPIS2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_SPIS2_IRQ_PRIORITY 10
#endif

/**
 * @brief   QSPI DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(WB32_SPI_QSPI_DMA_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_QSPI_DMA_PRIORITY 1
#endif

/**
 * @brief   SPIM2 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(WB32_SPI_SPIM2_DMA_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_SPIM2_DMA_PRIORITY 1
#endif

/**
 * @brief   SPIS1 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(WB32_SPI_SPIS1_DMA_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_SPIS1_DMA_PRIORITY 1
#endif

/**
 * @brief   SPIS2 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(WB32_SPI_SPIS2_DMA_PRIORITY) || defined(__DOXYGEN__)
#define WB32_SPI_SPIS2_DMA_PRIORITY 1
#endif

/**
 * @brief   SPI DMA error hook.
 */
#if !defined(WB32_SPI_DMA_ERROR_HOOK) || defined(__DOXYGEN__)
#define WB32_SPI_DMA_ERROR_HOOK(spip) osalSysHalt("DMA failure")
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if WB32_SPI_USE_QSPI && !WB32_HAS_QSPI
#error "QSPI not present in the selected device"
#endif

#if WB32_SPI_USE_SPIM2 && !WB32_HAS_SPIM2
#error "SPIM2 not present in the selected device"
#endif

#if WB32_SPI_USE_SPIS1 && !WB32_HAS_SPIS1
#error "SPIS1 not present in the selected device"
#endif

#if WB32_SPI_USE_SPIS2 && !WB32_HAS_SPIS2
#error "SPIS2 not present in the selected device"
#endif

#if !WB32_SPI_USE_QSPI && !WB32_SPI_USE_SPIM2 && !WB32_SPI_USE_SPIS1 && \
    !WB32_SPI_USE_SPIS2
#error "SPI driver activated but no SPI peripheral assigned"
#endif

#if WB32_SPI_USE_QSPI && \
   !OSAL_IRQ_IS_VALID_PRIORITY(WB32_SPI_QSPI_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to QSPI"
#endif

#if WB32_SPI_USE_SPIM2 && \
   !OSAL_IRQ_IS_VALID_PRIORITY(WB32_SPI_SPIM2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPIM2"
#endif

#if WB32_SPI_USE_SPIS1 && \
   !OSAL_IRQ_IS_VALID_PRIORITY(WB32_SPI_SPIS1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPIS1"
#endif

#if WB32_SPI_USE_SPIS2 && \
   !OSAL_IRQ_IS_VALID_PRIORITY(WB32_SPI_SPIS2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPIS2"
#endif

#ifdef WB32_USE_SPI_DMA
#if WB32_SPI_USE_QSPI && \
   !WB32_DMA_IS_VALID_PRIORITY(WB32_SPI_QSPI_DMA_PRIORITY)
#error "Invalid DMA priority assigned to QSPI"
#endif

#if WB32_SPI_USE_SPIM2 && \
   !WB32_DMA_IS_VALID_PRIORITY(WB32_SPI_SPIM2_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SPIM2"
#endif

#if WB32_SPI_USE_SPIS1 && \
   !WB32_DMA_IS_VALID_PRIORITY(WB32_SPI_SPIS1_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SPIS1"
#endif

#if WB32_SPI_USE_SPIS2 && \
   !WB32_DMA_IS_VALID_PRIORITY(WB32_SPI_SPIS2_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SPIS2"
#endif
#endif

/* The following checks are only required when there is a DMA able to
   reassign streams to different channels.*/
#if WB32_ADVANCED_DMA
/* Check on the presence of the DMA streams settings in mcuconf.h.*/
#if WB32_SPI_USE_QSPI && (!defined(WB32_SPI_QSPI_RX_DMA_STREAM) || \
                          !defined(WB32_SPI_QSPI_TX_DMA_STREAM))
#error "QSPI DMA streams not defined"
#endif

#if WB32_SPI_USE_SPIM2 && (!defined(WB32_SPI_SPIM2_RX_DMA_STREAM) || \
                           !defined(WB32_SPI_SPIM2_TX_DMA_STREAM))
#error "SPIM2 DMA streams not defined"
#endif

#if WB32_SPI_USE_SPIS1 && (!defined(WB32_SPI_SPIS1_RX_DMA_STREAM) || \
                           !defined(WB32_SPI_SPIS1_TX_DMA_STREAM))
#error "SPIS1 DMA streams not defined"
#endif

#if WB32_SPI_USE_SPIS2 && (!defined(WB32_SPI_SPIS2_RX_DMA_STREAM) || \
                           !defined(WB32_SPI_SPIS2_TX_DMA_STREAM))
#error "SPIS2 DMA streams not defined"
#endif

/* Check on the validity of the assigned DMA channels.*/
#if WB32_SPI_USE_QSPI && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_QSPI_RX_DMA_STREAM, WB32_QSPI_RX_DMA_MSK)
#error "invalid DMA stream associated to QSPI RX"
#endif

#if WB32_SPI_USE_QSPI && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_QSPI_TX_DMA_STREAM, WB32_QSPI_TX_DMA_MSK)
#error "invalid DMA stream associated to QSPI TX"
#endif

#if WB32_SPI_USE_SPIM2 && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_SPIM2_RX_DMA_STREAM, WB32_SPIM2_RX_DMA_MSK)
#error "invalid DMA stream associated to SPIM2 RX"
#endif

#if WB32_SPI_USE_SPIM2 && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_SPIM2_TX_DMA_STREAM, WB32_SPIM2_TX_DMA_MSK)
#error "invalid DMA stream associated to SPIM2 TX"
#endif

#if WB32_SPI_USE_SPIS1 && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_SPIS1_RX_DMA_STREAM, WB32_SPIS1_RX_DMA_MSK)
#error "invalid DMA stream associated to SPIS1 RX"
#endif

#if WB32_SPI_USE_SPIS1 && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_SPIS1_TX_DMA_STREAM, WB32_SPIS1_TX_DMA_MSK)
#error "invalid DMA stream associated to SPIS1 TX"
#endif

#if WB32_SPI_USE_SPIS2 && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_SPIS2_RX_DMA_STREAM, WB32_SPIS2_RX_DMA_MSK)
#error "invalid DMA stream associated to SPIS2 RX"
#endif

#if WB32_SPI_USE_SPIS2 && \
    !WB32_DMA_IS_VALID_ID(WB32_SPI_SPIS2_TX_DMA_STREAM, WB32_SPIS2_TX_DMA_MSK)
#error "invalid DMA stream associated to SPIS2 TX"
#endif

#endif /* WB32_ADVANCED_DMA */

#if !defined(WB32_DMA_REQUIRED)
#define WB32_DMA_REQUIRED
#endif

#if SPI_SELECT_MODE == SPI_SELECT_MODE_LLD
#error "SPI_SELECT_MODE_LLD not supported by this driver"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

typedef struct _spi_xfer_info_t {
  const uint8_t* tx_buf;
  volatile uint32_t tx_len;
           uint8_t* rx_buf;
  volatile uint32_t rx_len;
           uint8_t  tx_dummy;
           uint8_t  rx_dummy;
} spi_xfer_info_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Low level fields of the SPI driver structure.
 */
#define spi_lld_driver_fields                 \
    /* Pointer to the SPIx registers block.*/ \
    SPI_TypeDef *spi ;                        \
    spi_xfer_info_t g_spi_xfer_info

/**
 * @brief   Low level fields of the SPI configuration structure.
 */
#define spi_lld_config_fields                                      \
    /* Enable SPI interrupts. */                                   \
    uint8_t SPI_IT;                                                \
    /* SPI Transfer & receive. */                                  \
    uint16_t SPI_TransferMode;                                     \
    /* SPI serial data transfer. */                                \
    uint16_t SPI_DataSize;                                         \
    /* SPI_Clock_Polarity. */                                      \
    uint16_t SPI_CPOL;                                             \
    /* SPI_Clock_Phase. */                                         \
    uint16_t SPI_CPHA;                                             \
    /* SPI In order to avoid TX FIFO underflow or */               \
    /* RX FIFO overflow, SPI_BaudRatePrescaler needs to bigger. */ \
    uint16_t SPI_BaudRatePrescaler;                                \
    /* SPI Frame Format . */                                       \
    uint16_t SPI_FrameFormat;                                      \
    /* SPI specifies the slave select line. */                     \
    uint32_t SPI_NSS

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if WB32_SPI_USE_QSPI && !defined(__DOXYGEN__)
extern SPIDriver SPIDQ;
#endif

#if WB32_SPI_USE_SPIM2 && !defined(__DOXYGEN__)
extern SPIDriver SPIDM2;
#endif

#if WB32_SPI_USE_SPIS1 && !defined(__DOXYGEN__)
extern SPIDriver SPIDS1;
#endif

#if WB32_SPI_USE_SPIS2 && !defined(__DOXYGEN__)
extern SPIDriver SPIDS2;
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    void spi_lld_init(void);
    void spi_lld_start(SPIDriver *spip);
    void spi_lld_stop(SPIDriver *spip);
#if (SPI_SELECT_MODE == SPI_SELECT_MODE_LLD) || defined(__DOXYGEN__)
    void spi_lld_select(SPIDriver *spip);
    void spi_lld_unselect(SPIDriver *spip);
#endif
    void spi_lld_ignore(SPIDriver *spip, size_t n);
    void spi_lld_exchange(SPIDriver *spip, size_t n,
                          const void *txbuf, void *rxbuf);
    void spi_lld_send(SPIDriver *spip, size_t n, const void *txbuf);
    void spi_lld_receive(SPIDriver *spip, size_t n, void *rxbuf);
#if (SPI_SUPPORTS_CIRCULAR == TRUE) || defined(__DOXYGEN__)
    void spi_lld_abort(SPIDriver *spip);
#endif
    uint16_t spi_lld_polled_exchange(SPIDriver *spip, uint16_t frame);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SPI */

#endif /* HAL_SPI_LLD_H */

/** @} */
