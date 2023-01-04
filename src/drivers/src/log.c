#include <stdbool.h>
#include <string.h>
#include "ch32v30x.h"
#include "fifos.h"

static bool fifo_emptied = true;

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void insert_in_log_fifo(char*module, char *msg)
{
  int module_len = strlen(module);
  int msg_len = strlen(msg);

  __disable_irq();
  if (module_len + msg_len + 5 <= fifo_space(&log_fifo)) { // "() \r\n" : 5 extra chars
    int i;
    fifo_putc(&log_fifo, '(');
    for (i = 0; i < module_len; i++) {
      fifo_putc(&log_fifo, module[i]);
    }
    fifo_putc(&log_fifo, ')');
    fifo_putc(&log_fifo, ' ');
    for (i = 0; i < msg_len; i++) {
      fifo_putc(&log_fifo, msg[i]);
    }
    fifo_putc(&log_fifo, '\r');
    fifo_putc(&log_fifo, '\n');

    if (fifo_emptied) {
      USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
      fifo_emptied = false;
    }
    /* if (fifo_emptied) { */
    /*   uint8_t c = fifo_getc(&log_fifo); */
    /*   if (c != EOF) { */
    /*     USART_SendData(USART2, c); */
    /*     USART_ITConfig(USART2, USART_IT_TXE, ENABLE); */
    /*     fifo_emptied = false; */
    /*   } */
    /* } */
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

