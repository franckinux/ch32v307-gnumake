#include <stddef.h>
#include "thread.h"

#include "ch32v30x.h"
#include "log.h"

#define LOG_LEVEL LOG_DEBUG

static uint8_t green_led_state = 1;


static thread_action_t thread_loop(void)
{
  GPIO_WriteBit(GPIOB, GPIO_Pin_4, (green_led_state == 0) ? (green_led_state = Bit_SET) : (green_led_state = Bit_RESET));

  log_debug("+");

  return THREAD_LOOP;
}


thread_t led_thread = {
  .active = true,
  .thread_init = NULL,
  .thread_loop = &thread_loop,
  .delay = 500 / MAIN_DELAY,  //toggle every 500ms : 1s period
};

