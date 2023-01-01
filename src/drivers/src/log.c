#include <stdbool.h>
#include <string.h>
#include "ch32v30x.h"
#include "fifos.h"

static bool fifo_emptied = true;

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));


void insert_in_log_fifo(char *msg)
{
  int len = strlen(msg);

  __disable_irq();
  if (len + 2 <= fifo_space(&log_fifo)) {
    for (int i=0; i < len; i++) {
      fifo_putc(&log_fifo, msg[i]);
    }
    fifo_putc(&log_fifo, '\r');
    fifo_putc(&log_fifo, '\n');

    /* send the first char if needed */
    if (fifo_emptied) {
      uint8_t c = fifo_getc(&log_fifo);
      if (c != EOF) {
        USART_SendData(USART2, c);
        USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
        fifo_emptied = false;
      }
    }
  }
  __enable_irq();
}


void USART2_IRQHandler(void)
{
  if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) {
    uint8_t c = fifo_getc(&log_fifo);
    if (c == EOF) {
      /* nothing more to send, the fifo has been emptied */
      USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
      fifo_emptied = true;
    } else {
      /* send next char */
      USART_SendData(USART2, c);
    }
  }
}

