#ifndef TYPES_H
#define TYPES_H

//Define useful types
#include <stdint.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

