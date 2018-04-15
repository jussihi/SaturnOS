#ifndef _SATURNOS_IDT_HH
#define _SATURNOS_IDT_HH

#include "../../stdint.h"

typedef struct {
  uint16_t offset_lo;
  uint16_t selector;
  uint8_t zero_byte;
  uint8_t type;
  uint16_t offset_hi;
}__attribute__((__packed__)) IDT_t;

#define IDT_32BIT_INTERRUPT_GATE 0xE
#define IDT_STORAGE_SEGMENT    0x20
#define IDT_DPL_3      0x60
#define IDT_PRESENT      (1 <<7 )
#define IDT_TYPE_INTERRUPT 0xE


void call_lidt(uint32_t base, uint16_t limit);

void idt_init();

void idt_set_handler(IDT_t* entry, void(*handler)(void), uint8_t type, uint8_t access);


/*
 * Interrupt handler stubs, I can't come up with a better solution
 * These are defined in the assembly code which is almost as 
 * sophisticated as this is ....
 */
void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();
void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();


#endif