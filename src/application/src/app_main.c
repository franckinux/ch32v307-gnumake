#include <stddef.h>
#include <stdbool.h>

#include "thread.h"

extern thread_t led_thread;


static thread_t *threads[] = {
  &led_thread,
  NULL
};


bool app_init()
{
  bool ok = true;
  thread_t **thread = threads;
  while (*thread != NULL) {
    thread_t *p_thread = *thread;
    if (p_thread->thread_init != NULL) {
      ok = ok && p_thread->thread_init();
    }
    p_thread->running_delay = p_thread->delay;
    p_thread->error_count = 0;
    thread++;
  }

  return ok;
}


void app_loop(void)
{
  thread_t **thread = threads;
  while (*thread != NULL) {
    thread_t *p_thread = *thread;
    if (p_thread->active && p_thread->thread_loop != NULL) {
      if (--p_thread->running_delay == 0) {
        thread_action_t thread_action = p_thread->thread_loop();
        if (thread_action >= THREAD_LOOP_ON_ERROR && thread_action <= THREAD_STOP_ON_ERROR) {
            p_thread->error_count++;
        };
        if (thread_action == THREAD_STOP || thread_action == THREAD_STOP_ON_ERROR) {
            p_thread->active = false;
        } else if (thread_action == THREAD_RESTART || thread_action == THREAD_RESTART_ON_ERROR) {
          p_thread->thread_init();
        }
        p_thread->running_delay = p_thread->delay;
      }
    }
    thread++;
  }
}
