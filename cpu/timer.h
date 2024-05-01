#ifndef TIMER_H
#define TIMER_H

#include "types.h"

#define HARDWARE_TIMER_FREQUENCY 1193180

// Initializes the system timer with the specified frequency (in Hz).
void init_timer(uint32_t freq);

// Returns the system uptime in seconds since the system was started.
uint32_t get_system_uptime(void);


#endif