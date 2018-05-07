#include "../include/mutex.h"

// note that if a lock will be acquired by IRQ handlers and foreground threads, you should disable 
//                 interrupts while holding that lock to make sure that the thread holding the lock won't be 
//                 interrupted by that IRQ handler and deadlock

void mutex_init(mutex* m)
{
  m->lock = 0;
}

void mutex_lock(mutex* m)
{
  // deadlocks EVERY TIME, because interrupt interrupts the execution between lock-unlock ...
  // ???
  if(!m->lock)
  {
    m->lock = 1;
    return;
  }
  while(m->lock);
}

void mutex_unlock(mutex* m)
{
  m->lock = 0;
}