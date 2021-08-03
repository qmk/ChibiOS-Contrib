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
   Concepts and parts of this file have been contributed by Uladzimir Pylinsky
   aka barthess.
 */

/**
 * @file    I2Cv1/hal_i2c_lld.h
 * @brief   WB32 I2C subsystem low level driver header.
 *
 * @addtogroup I2C
 * @{
 */

#ifndef HAL_I2C_LLD_H
#define HAL_I2C_LLD_H

#if HAL_USE_I2C || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Peripheral clock frequency.
 */
#define I2C_CLK_FREQ ((WB32_PCLK1) / 1000000)

/** @defgroup I2C_Exported_Constants
  * @{
  */

/** @defgroup I2C_TargetAddress_definition 
  * @{
  */
#define I2C_TARGETADDRESS_GENERAL_CALL (I2C_TAR_SPECIAL)
#define I2C_TARGETADDRESS_START_BYTE (I2C_TAR_SPECIAL | I2C_TAR_GC_OR_START)
#define I2C_TARGETADDRESS_DEVICE_ID (I2C_TAR_SPECIAL | I2C_TAR_DEVICE_ID)
#define I2C_TARGETADDRESS_SMBUS_QUICK_CMD (I2C_TAR_SPECIAL | I2C_TAR_SMBUS_QUICK_CMD)
/**
  * @}
  */

/** @defgroup I2C_flags_definition 
  * @{
  */
#define I2C_FLAG_ACTIVITY I2C_STATUS_ACTIVITY
#define I2C_FLAG_TFNF I2C_STATUS_TFNF
#define I2C_FLAG_TFE I2C_STATUS_TFE
#define I2C_FLAG_RFNE I2C_STATUS_RFNE
#define I2C_FLAG_RFF I2C_STATUS_RFF
#define I2C_FLAG_MST_ACTIVITY I2C_STATUS_MST_ACTIVITY
#define I2C_FLAG_SLV_ACTIVITY I2C_STATUS_SLV_ACTIVITY
#define I2C_FLAG_MST_HOLD_TX_FIFO_EMPTY I2C_STATUS_MST_HOLD_TX_FIFO_EMPTY
#define I2C_FLAG_MST_HOLD_RX_FIFO_FULL I2C_STATUS_MST_HOLD_RX_FIFO_FULL
#define I2C_FLAG_SLV_HOLD_TX_FIFO_EMPTY I2C_STATUS_SLV_HOLD_TX_FIFO_EMPTY
#define I2C_FLAG_SLV_HOLD_RX_FIFO_FULL I2C_STATUS_SLV_HOLD_RX_FIFO_FULL
#define I2C_FLAG_SDA_STUCK_NOT_RECOVERED I2C_STATUS_SDA_STUCK_NOT_RECOVERED
#define I2C_FLAG_SMBUS_QUICK_CMD_BIT I2C_STATUS_SMBUS_QUICK_CMD_BIT
#define I2C_FLAG_SMBUS_SLAVE_ADDR_VALID I2C_STATUS_SMBUS_SLAVE_ADDR_VALID
#define I2C_FLAG_SMBUS_SLAVE_ADDR_RESOLVED I2C_STATUS_SMBUS_SLAVE_ADDR_RESOLVED
#define I2C_FLAG_SMBUS_SUSPEND_STATUS I2C_STATUS_SMBUS_SUSPEND_STATUS
#define I2C_FLAG_SMBUS_ALERT_STATUS I2C_STATUS_SMBUS_ALERT_STATUS
/**
  * @}
  */

/** @defgroup I2C_interrupts_definition 
  * @{
  */
#define I2C_IT_RX_UNDER I2C_INTR_RX_UNDER
#define I2C_IT_RX_OVER I2C_INTR_RX_OVER
#define I2C_IT_RX_FULL I2C_INTR_RX_FULL
#define I2C_IT_TX_OVER I2C_INTR_TX_OVER
#define I2C_IT_TX_EMPTY I2C_INTR_TX_EMPTY
#define I2C_IT_RD_REQ I2C_INTR_RD_REQ
#define I2C_IT_TX_ABRT I2C_INTR_TX_ABRT
#define I2C_IT_RX_DONE I2C_INTR_RX_DONE
#define I2C_IT_ACTIVITY I2C_INTR_ACTIVITY
#define I2C_IT_STOP_DET I2C_INTR_STOP_DET
#define I2C_IT_START_DET I2C_INTR_START_DET
#define I2C_IT_GEN_CALL I2C_INTR_GEN_CALL
#define I2C_IT_RESTART_DET I2C_INTR_RESTART_DET
#define I2C_IT_SCL_STUCK_AT_LOW I2C_INTR_SCL_STUCK_AT_LOW
/**
  * @}
  */

/** @defgroup I2C_SMBus_interrupts_definition 
  * @{
  */
#define I2C_SMBUS_IT_SLV_CLOCK_EXTND_TIMEOUT I2C_SMBUS_INTR_SLV_CLOCK_EXTND_TIMEOUT
#define I2C_SMBUS_IT_MST_CLOCK_EXTND_TIMEOUT I2C_SMBUS_INTR_MST_CLOCK_EXTND_TIMEOUT
#define I2C_SMBUS_IT_QUICK_CMD_DET I2C_SMBUS_INTR_QUICK_CMD_DET
#define I2C_SMBUS_IT_HOST_NTFY_MST_DET I2C_SMBUS_INTR_HOST_NTFY_MST_DET
#define I2C_SMBUS_IT_ARP_PREPARE_CMD_DET I2C_SMBUS_INTR_ARP_PREPARE_CMD_DET
#define I2C_SMBUS_IT_ARP_RST_CMD_DET I2C_SMBUS_INTR_ARP_RST_CMD_DET
#define I2C_SMBUS_IT_ARP_GET_UDID_CMD_DET I2C_SMBUS_INTR_ARP_GET_UDID_CMD_DET
#define I2C_SMBUS_IT_ARP_ASSGN_ADDR_CMD_DET I2C_SMBUS_INTR_ARP_ASSGN_ADDR_CMD_DET
#define I2C_SMBUS_IT_SLV_RX_PEC_NACK I2C_SMBUS_INTR_SLV_RX_PEC_NACK
#define I2C_SMBUS_IT_SMBUS_SUSPEND_DET I2C_SMBUS_INTR_SMBUS_SUSPEND_DET
#define I2C_SMBUS_IT_SMBUS_ALERT_DET I2C_SMBUS_INTR_SMBUS_ALERT_DET
/**
  * @}
  */

/** @defgroup I2C_DMA_Requests 
  * @{
  */
#define I2C_DMAReq_Rx I2C_DMA_CR_RDMAE
#define I2C_DMAReq_Tx I2C_DMA_CR_TDMAE
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
 * @brief   I2C1 driver enable switch.
 * @details If set to @p TRUE the support for I2C1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_I2C_USE_I2C1) || defined(__DOXYGEN__)
#define WB32_I2C_USE_I2C1 FALSE
#endif

/**
 * @brief   I2C2 driver enable switch.
 * @details If set to @p TRUE the support for I2C2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(WB32_I2C_USE_I2C2) || defined(__DOXYGEN__)
#define WB32_I2C_USE_I2C2 FALSE
#endif

/**
 * @brief   I2C timeout on busy condition in milliseconds.
 */
#if !defined(WB32_I2C_BUSY_TIMEOUT) || defined(__DOXYGEN__)
#define WB32_I2C_BUSY_TIMEOUT 50
#endif

/**
 * @brief   I2C1 interrupt priority level setting.
 */
#if !defined(WB32_I2C_I2C1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_I2C_I2C1_IRQ_PRIORITY 10
#endif

/**
 * @brief   I2C2 interrupt priority level setting.
 */
#if !defined(WB32_I2C_I2C2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define WB32_I2C_I2C2_IRQ_PRIORITY 10
#endif

/**
* @brief   I2C1 DMA priority (0..3|lowest..highest).
* @note    The priority level is used for both the TX and RX DMA streams but
*          because of the streams ordering the RX stream has always priority
*          over the TX stream.
*/
#if !defined(WB32_I2C_I2C1_DMA_PRIORITY) || defined(__DOXYGEN__)
#define WB32_I2C_I2C1_DMA_PRIORITY 1
#endif

/**
* @brief   I2C2 DMA priority (0..3|lowest..highest).
* @note    The priority level is used for both the TX and RX DMA streams but
*          because of the streams ordering the RX stream has always priority
*          over the TX stream.
*/
#if !defined(WB32_I2C_I2C2_DMA_PRIORITY) || defined(__DOXYGEN__)
#define WB32_I2C_I2C2_DMA_PRIORITY 1
#endif

/**
 * @brief   I2C DMA error hook.
 * @note    The default action for DMA errors is a system halt because DMA
 *          error can only happen because programming errors.
 */
#if !defined(WB32_I2C_DMA_ERROR_HOOK) || defined(__DOXYGEN__)
#define WB32_I2C_DMA_ERROR_HOOK(i2cp) osalSysHalt("DMA failure")
#endif

/* Fixed streams for platforms using the old DMA peripheral, the values are
   valid for both WB32F10x */
#define WB32_I2C_I2C1_RX_DMA_STREAM WB32_DMA_STREAM_ID(2, 0)
#define WB32_I2C_I2C1_TX_DMA_STREAM WB32_DMA_STREAM_ID(2, 1)
#define WB32_I2C_I2C2_RX_DMA_STREAM WB32_DMA_STREAM_ID(2, 0)
#define WB32_I2C_I2C2_TX_DMA_STREAM WB32_DMA_STREAM_ID(2, 1)

#if defined(WB32F10x)
#define WB32F10x_I2C
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/** @brief  error checks */
#if WB32_I2C_USE_I2C1 && !WB32_HAS_I2C1
#error "I2C1 not present in the selected device"
#endif

#if WB32_I2C_USE_I2C2 && !WB32_HAS_I2C2
#error "I2C2 not present in the selected device"
#endif

#if !WB32_I2C_USE_I2C1 && !WB32_I2C_USE_I2C2
#error "I2C driver activated but no I2C peripheral assigned"
#endif

#if WB32_I2C_USE_I2C1 && \
    !OSAL_IRQ_IS_VALID_PRIORITY(WB32_I2C_I2C1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to I2C1"
#endif

#if WB32_I2C_USE_I2C2 && \
    !OSAL_IRQ_IS_VALID_PRIORITY(WB32_I2C_I2C2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to I2C2"
#endif

#if !defined(WB32_DMA_REQUIRED)
#define WB32_DMA_REQUIRED
#endif

/* Check clock range. */

#if defined(WB32F10x)
#if !(I2C_CLK_FREQ >= 2) && (I2C_CLK_FREQ <= 24)
#error "I2C peripheral clock frequency out of range."
#endif
#else
#error "unspecified, unsupported or invalid WB32 platform"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type representing an I2C address.
 */
typedef uint16_t i2caddr_t;

/**
 * @brief   Type of I2C driver condition flags.
 */
typedef uint32_t i2cflags_t;

typedef struct _i2c_xfer_info_t {
  const    uint8_t* tx_buf;
  volatile uint32_t tx_len;
           uint8_t* rx_buf;
  volatile uint32_t rx_len;
  volatile uint32_t rx_cmd_len;  
           uint32_t tx_abrt_source;
} i2c_xfer_info_t;

/**
 * @brief   Type of I2C driver configuration structure.
 */
typedef struct
{
  /* End of the mandatory fields.*/

  uint16_t I2C_IT;             /**< @brief specifies the I2C interrupt source.*/
  uint32_t op_mode;          /**< @brief Specifies the I2C mode.*/
  uint32_t TargetAddress;    /*< @brief In host mode set the slave address */
  uint8_t tx_fifo_Threshold; /**< @brief The Transmit FIFO threshold to set.*/
  uint8_t rx_fifo_Threshold; /**< @brief The Receive FIFO threshold to set.*/

  uint32_t ss_scl_hcnt;      /**< @brief tHIGH = (ss_scl_hcnt + FS_SPKLEN + 7) / PCLK2 */
  uint32_t ss_scl_lcnt;      /**< @brief tLOW = (ss_scl_lcnt + 1) / PCLK2 */
  uint32_t fs_spklen;        /**< @brief  fs_spklen / PCLK2  */
  uint32_t sda_setup;        /**< @brief tSU;DAT = sda_setup / PCLK2 */
  uint32_t sda_hold;         /**< @brief tHD;DAT = sda_hold / PCLK2 */

} I2CConfig;

/**
 * @brief   Type of a structure representing an I2C driver.
 */
typedef struct I2CDriver I2CDriver;

/**
 * @brief   Structure representing an I2C driver.
 */
struct I2CDriver
{
  /**
   * @brief   Driver state.
   */
  i2cstate_t state;
  /**
   * @brief   Current configuration data.
   */
  const I2CConfig *config;
  /**
   * @brief   Error flags.
   */
  i2cflags_t errors;
#if I2C_USE_MUTUAL_EXCLUSION || defined(__DOXYGEN__)
  /**
   * @brief   Mutex protecting the bus.
   */
  mutex_t mutex;
#endif /* I2C_USE_MUTUAL_EXCLUSION */
#if defined(I2C_DRIVER_EXT_FIELDS)
  I2C_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief   Thread waiting for I/O completion.
   */
  thread_reference_t thread;
  /**
   * @brief     Current slave address without R/W bit.
   */
  i2caddr_t addr;
  /**
   * @brief     Data processing.
   */
  i2c_xfer_info_t g_i2c_xfer_info;
  /**
   * @brief     Pointer to the I2Cx registers block.
   */
  I2C_TypeDef *i2c;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Get errors from I2C driver.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define i2c_lld_get_errors(i2cp) ((i2cp)->errors)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
#if WB32_I2C_USE_I2C1
extern I2CDriver I2CD1;
#endif

#if WB32_I2C_USE_I2C2
extern I2CDriver I2CD2;
#endif

#endif /* !defined(__DOXYGEN__) */

#ifdef __cplusplus
extern "C"
{
#endif
  void i2c_lld_init(void);
  void i2c_lld_start(I2CDriver *i2cp);
  void i2c_lld_stop(I2CDriver *i2cp);
  msg_t i2c_lld_master_transmit_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                        const uint8_t *txbuf, size_t txbytes,
                                        uint8_t *rxbuf, size_t rxbytes,
                                        sysinterval_t timeout);
  msg_t i2c_lld_master_receive_timeout(I2CDriver *i2cp, i2caddr_t addr,
                                       uint8_t *rxbuf, size_t rxbytes,
                                       sysinterval_t timeout);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_I2C  */

#endif /* HAL_I2C_LLD_H */

/** @} */
