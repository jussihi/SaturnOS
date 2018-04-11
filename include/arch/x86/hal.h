#ifndef _SATURNOS_HAL_X86_HH
#define _SATURNOS_HAL_X86_HH

#include "../../stdint.h"
#include "../../pic.h"
#include "idt.h"

#define IRQ_START __asm__ __volatile__ ("add $12, %esp"); \
                  __asm__ __volatile__ ("pushal");

#define IRQ_END   __asm__ __volatile__ ("popal"); \
                  __asm__ __volatile__ ("iretl");


void hal_init();

void hal_end_irq(uint8_t irq);

void hal_set_int(uint8_t interrupt_num, uint32_t callback);


#endif