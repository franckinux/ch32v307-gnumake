#include <stdbool.h>
#include <stddef.h>
#include "os_applAPI.h"

#include "ch32v30x.h"
#include "log.h"

#define LOG_LEVEL LOG_DEBUG
#define LOG_MODULE_NAME "led"
#define CYCLE_PERIOD 500  // 500 ms

static uint8_t green_led_state = 1;


void led_task(void)
{
  task_open();

  while(true) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_4, (green_led_state == 0) ? (green_led_state = Bit_SET) : (green_led_state = Bit_RESET));
    log_debug("test log");
    task_wait(CYCLE_PERIOD);
  }

  task_close();
}
