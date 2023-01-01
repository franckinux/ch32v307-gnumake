#ifndef __LOG_H
#define __LOG_H

#define ENABLE_LOGS 1

#include <stdbool.h>
#include "fifos.h"

typedef enum {
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR,
  LOG_CRITICAL
} log_level_t;

bool insert_in_log_fifo(char *msg);

#if (LOG_LEVEL >= LOG_DEBUG) && ENABLE_LOGS
#define log_debug(m) insert_in_log_fifo(m)
#else
#define log_debug(m) {}
#endif

#if (LOG_LEVEL >= LOG_INFO) && ENABLE_LOGS
#define log_info(m) insert_in_log_fifo(m)
#else
#define log_info(m) {}
#endif

#if (LOG_LEVEL >= LOG_WARNING) && ENABLE_LOGS
#define log_warning(m) insert_in_log_fifo(m)
#else
#define log_warning(m) {}
#endif

#if (LOG_LEVEL >= LOG_ERROR) && ENABLE_LOGS
#define log_error(m) insert_in_log_fifo(m)
#else
#define log_error(m) {}
#endif

#if (LOG_LEVEL >= LOG_CRITICAL) && ENABLE_LOGS
#define log_critical(m) insert_in_log_fifo(m)
#else
#define log_critical(m) {}
#endif

#endif
