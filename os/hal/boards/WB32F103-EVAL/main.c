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

#include "ch.h"
#include "hal.h"
#include "board.h"

/*===========================================================================*/
/* Private variables.                                                        */
/*===========================================================================*/


I2CConfig i2cconfig = { I2C_IT_TX_EMPTY | I2C_IT_TX_ABRT | I2C_IT_STOP_DET | I2C_IT_RX_FULL,
                        I2C_CON_SLAVE_DISABLE | I2C_CON_RESTART_EN | I2C_CON_SPEED_STANDARD | I2C_CON_MASTER_MODE,
                        0xA0 >> 1,  
                        0,  
                        0,  
                        373,  /* tHIGH = (373 + FS_SPKLEN + 7) / 96MHz = 4us */
                        451,  /* tLOW = (451 + 1) / 96MHz = 4.708us */
                        4,    /* tSP = 4 / 96MHz = 41.67ns */
                        24,   /* tSU;DAT = 24 / 96MHz = 250ns */
                        29 }; /* tHD;DAT = 29 / 96MHz = 302.08ns */ 
UARTConfig uartconfig = { NULL,NULL,NULL,NULL,NULL,NULL,
                          115200,
                          UART_WordLength_8b,
                          UART_StopBits_One,
                          UART_Parity_None,
                          UART_AutoFlowControl_None };
SPIConfig spiconfig = { NULL,NULL,NULL,
                        SPI_IT_TXE | SPI_IT_RXF,
                        SPI_TransferMode_TxAndRx,
                        SPI_DataSize_8b,
                        SPI_CPOL_Low,
                        SPI_CPHA_1Edge,
                        96,
                        SPI_FrameFormat_SPI,
                        2,
                        1,
                        SPI_NSS_0 };
/*===========================================================================*/
/* Generic code.                                                             */
/*===========================================================================*/

#define PORTAB_LINE_LED1 PAL_LINE(GPIOB, 14U)
#define PORTAB_LINE_LED2 PAL_LINE(GPIOB, 13U)
#define PORTAB_LED_OFF PAL_HIGH
#define PORTAB_LED_ON PAL_LOW

#define PORTAB_LINE_BUTTON PAL_LINE(GPIOA, 0U)
#define PORTAB_BUTTON_PRESSED PAL_LOW

#if defined(PORTAB_LINE_LED2)
/*
 * LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg)
{
  (void)arg;
  chRegSetThreadName("blinker");
  while (true)
  {
    systime_t time = palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED ? 250 : 500;
    palToggleLine(PORTAB_LINE_LED2);
    chThdSleepMilliseconds(time);
  }
}
#endif

#if PAL_USE_WAIT || defined(__DOXYGEN__)

/**
  * @brief  Configure PA0 in interrupt mode
  * @param  None
  * @return None
  */
void EXTI0_Config(void)
{
  /* Enable GPIOA clock */
  RCC->APB1ENR |= (1 << 15) | (1 << 5);

  // _pal_lld_setgroupmode(GPIOA, GPIO_Pin_0, GPIO_MODE_IN | GPIO_PUPD_DOWN);

  pal_lld_setgroupmode(GPIOA, 1, 0, GPIO_MODE_IN | GPIO_PUPD_DOWN);

  /* Enable AFIO clock */
  RCC->APB1ENR |= (1 << 15) | (1 << 9) | (1 << 10);

  /* Enabling events on both edges of the button line.*/
  palEnableLineEvent(PORTAB_LINE_BUTTON, PAL_EVENT_MODE_RISING_EDGE);

  nvicEnableVector(EXTI0_IRQn, WB32_IRQ_EXTI0_PRIORITY);
}

uint8_t rx_buffer[256];
uint8_t tx_buffer[256]={0x06,0x07,0x08,0x09,0x0a};
const uint8_t spi_master_tx_data[20] =
{
  0x97, 0x8D, 0x38, 0xDA, 0xDB, 0x54, 0xBF, 0x6D, 0x1C, 0xFF,
  0x54, 0xEF, 0x82, 0x5C, 0x40, 0xAC, 0x68, 0xA0, 0x91, 0xEC
};
uint8_t spi_master_rx_buf[20] = {0};
/*
 * Application entry point.
 */
int main(void)
{
  __IO msg_t msg;

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  
  pal_lld_setgroupmode(GPIOB, 3, 10, GPIO_MODE_AF |GPIO_OTYPE_OD |GPIO_PUPD_UP |GPIO_SPEED_HIGH |GPIO_AF4);
  pal_lld_setgroupmode(GPIOA, 3,  9, GPIO_MODE_AF |GPIO_OTYPE_PP |GPIO_PUPD_UP |GPIO_SPEED_HIGH |GPIO_AF7);
  pal_lld_setgroupmode(GPIOA, 0xF,  4, GPIO_MODE_AF | GPIO_OTYPE_PP | GPIO_PUPD_NOPULL | GPIO_SPEED_HIGH | GPIO_AF5);
  
  i2cStart(&I2CD2 , &i2cconfig);
  uartStart(&UARTD1 , &uartconfig);
  spiStart(&SPIDQ , &spiconfig);

  /*
   * Configure PA0 in interrupt mode 
   */
  EXTI0_Config();

  /*
   * Configure MCO output 
   */
  RCC->MCOSEL = 0;
  RCC->MCOSEL = 1 << 1;
  
  msg = i2c_lld_master_transmit_timeout(&I2CD2,0x06,tx_buffer,5,rx_buffer,0,WB32_I2C_BUSY_TIMEOUT);
  
  msg = i2c_lld_master_transmit_timeout(&I2CD2,0,tx_buffer,0,rx_buffer,0,WB32_I2C_BUSY_TIMEOUT);
  
  msg = i2c_lld_master_transmit_timeout(&I2CD2,0x06,NULL,0,rx_buffer,5,WB32_I2C_BUSY_TIMEOUT);
  
  msg = i2c_lld_master_receive_timeout(&I2CD2,0x06,rx_buffer,5,WB32_I2C_BUSY_TIMEOUT);

  spi_lld_send(&SPIDQ,20,spi_master_tx_data);
  
  uartStartSend(&UARTD1 , 10 , "abcdefghijklmn");
  
  uartStartReceive(&UARTD1 , 10 ,rx_buffer);

#if defined(PORTAB_LINE_LED2)
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
#endif

  /*
   * Normal main() thread activity.
   */
  while (true)
  {
    /* Waiting for an edge on the button.*/
    palWaitLineTimeout(PORTAB_LINE_BUTTON, TIME_INFINITE);
    
    palToggleLine(PORTAB_LINE_LED1);

//    /* Action depending on button state.*/
//    if (palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED)
//    {
//      palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_ON);
//    }
//    else
//    {
//      palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_OFF);
//    }
  }
}

#endif /* PAL_USE_WAIT */

#if !PAL_USE_WAIT && PAL_USE_CALLBACKS

static event_source_t button_pressed_event;
static event_source_t button_released_event;

static void button_cb(void *arg)
{

  (void)arg;

  chSysLockFromISR();
  if (palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED)
  {
    chEvtBroadcastI(&button_pressed_event);
  }
  else
  {
    chEvtBroadcastI(&button_released_event);
  }
  chSysUnlockFromISR();
}

/*
 * Application entry point.
 */
int main(void)
{
  event_listener_t el0, el1;

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /* Events initialization and registration.*/
  chEvtObjectInit(&button_pressed_event);
  chEvtObjectInit(&button_released_event);
  chEvtRegister(&button_pressed_event, &el0, 0);
  chEvtRegister(&button_released_event, &el1, 1);

#if defined(PORTAB_LINE_LED2)
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
#endif

  /* Enabling events on both edges of the button line.*/
  palEnableLineEvent(PORTAB_LINE_BUTTON, PAL_EVENT_MODE_BOTH_EDGES);
  palSetLineCallback(PORTAB_LINE_BUTTON, button_cb, NULL);

  /*
   * Normal main() thread activity.
   */
  while (true)
  {
    eventmask_t events;

    events = chEvtWaitOne(EVENT_MASK(0) | EVENT_MASK(1));
    if (events & EVENT_MASK(0))
    {
      palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_ON);
    }
    if (events & EVENT_MASK(1))
    {
      palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_OFF);
    }
  }
}
#endif /* !PAL_USE_WAIT && PAL_USE_CALLBACKS */

#if !PAL_USE_WAIT && !PAL_USE_CALLBACKS
/*
 * Application entry point.
 */
int main(void)
{

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

#if defined(PORTAB_LINE_LED2)
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
#endif

  /*
   * Normal main() thread activity.
   */
  while (true)
  {
    palToggleLine(PORTAB_LINE_LED1);
    chThdSleepMilliseconds(500);
  }
}
#endif /* !PAL_USE_WAIT && !PAL_USE_CALLBACKS */
