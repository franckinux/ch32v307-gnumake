#ifndef __FIFO_H
#define __FIFO_H

#include <stdint.h>

#define FIFO_BUFFER_SIZE 256

// FIFO struct
typedef struct
{
  volatile uint8_t data[FIFO_BUFFER_SIZE];
  volatile uint16_t size;
  volatile uint16_t raddr;
  volatile uint16_t waddr;
} fifo;

// FIFO access routines
void fifo_init(fifo *_fifo);
int fifo_getc(fifo *_fifo);
int fifo_putc(fifo *_fifo, int c);
uint16_t fifo_space(fifo *_fifo);

#endif
