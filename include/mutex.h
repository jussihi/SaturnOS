#ifndef _SATURNOS_MUTEX_HH
#define _SATURNOS_MUTEX_HH

#include "stdint.h"

typedef struct {
  uint8_t lock;
} mutex;

void mutex_init(mutex* m);

void mutex_lock(mutex* m);

void mutex_unlock(mutex* m);

#endif