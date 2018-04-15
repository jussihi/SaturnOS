#include "../../include/hal.h"

void hal_init()
{
  return;
}

void hal_end_irq(uint8_t irq)
{
  pic_end_int(irq);
}

void hal_set_int(uint8_t interrupt_num, uint32_t callback)
{
  // idt_add_handler(interrupt_num, callback);
}