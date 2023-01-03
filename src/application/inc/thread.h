#ifndef THREAD_H_
#define THREAD_H_

#include <stdbool.h>
#include <stdint.h>

#define IDLE_PERIOD 5   //ms


typedef enum {
  THREAD_LOOP,
  THREAD_RESTART,
  THREAD_STOP,
  THREAD_LOOP_ON_ERROR,
  THREAD_RESTART_ON_ERROR,
  THREAD_STOP_ON_ERROR
} thread_action_t;


typedef bool (*thread_init_t)(void);
typedef thread_action_t (*thread_loop_t)(void);


typedef struct thread {
  bool active;
  thread_init_t thread_init;
  thread_loop_t thread_loop;
  uint32_t running_delay;
  uint32_t delay;
  uint32_t error_count;
  void *arg;
} thread_t;

#endif
