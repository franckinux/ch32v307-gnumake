#include <stdbool.h>
#include <string.h>
#include "ch32v30x.h"
#include "fifos.h"

bool insert_in_log_fifo(char *msg)
{
  int len = strlen(msg);

  __disable_irq();
  if (len + 1 <= fifo_space(&log_fifo)) {
    for (int i; i < len; i++) {
      fifo_putc(&log_fifo, msg[i]);
    }
    fifo_putc(&log_fifo, '\n');
    __enable_irq();
    return true;
  } else {
    __enable_irq();
    return false;
  }
}
