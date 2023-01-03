#include <stddef.h>
#include "thread.h"

#include "ch32v30x.h"
#include "log.h"

#define LOG_LEVEL LOG_DEBUG
#define LOG_MODULE_NAME "led"
#define CYCLE_PERIOD 500  // 500 ms

static uint8_t green_led_state = 1;


static thread_action_t thread_loop(void)
{
  GPIO_WriteBit(GPIOB, GPIO_Pin_4, (green_led_state == 0) ? (green_led_state = Bit_SET) : (green_led_state = Bit_RESET));

  log_debug("test log");

  return THREAD_LOOP;
}


thread_t led_thread = {
  .active = true,
  .thread_init = NULL,
  .thread_loop = &thread_loop,
  .delay = CYCLE_PERIOD / IDLE_PERIOD,
};

