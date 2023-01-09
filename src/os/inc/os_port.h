#ifndef OS_PORT_H_
#define OS_PORT_H_

#include <ch32v30x.h>

#define os_enable_interrupts()  __enable_irq()
#define os_disable_interrupts() __disable_irq()

#endif
