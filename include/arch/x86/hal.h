#ifndef _SATURNOS_HAL_X86_HH
#define _SATURNOS_HAL_X86_HH

#include "../../stdint.h"
#include "../../pic.h"
#include "idt.h"

#define IRQ_START __asm__ __volatile__ ("add $0x1c, %esp"); \
                  __asm__ __volatile__ ("pusha");

//#define IRQ_START __asm__ __volatile__ ("pusha");

#define IRQ_END   __asm__ __volatile__ ("popa"); \
                  __asm__ __volatile__ ("iret");


void hal_init();

void hal_end_irq(uint8_t irq);

void hal_set_int(uint8_t interrupt_num, uint32_t callback);


#endif