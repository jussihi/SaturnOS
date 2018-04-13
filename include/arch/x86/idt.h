#ifndef _SATURNOS_IDT_HH
#define _SATURNOS_IDT_HH

#include "../../stdint.h"

typedef struct {
  uint16_t offset_lo;
  uint16_t selector;
  uint8_t zero_byte;
  uint8_t type;
  uint16_t offset_hi;
} __attribute__((__packed__)) IDT_t;

#define IDT_32BIT_INTERRUPT_GATE 0xE
#define IDT_STORAGE_SEGMENT    0x20
#define IDT_DPL_3      0x60
#define IDT_PRESENT      0x80

#define INT_START asm volatile("pusha");
#define INT_END asm volatile("popa"); \
 asm volatile("iret");

extern void _set_idtr(void);

extern void _default_idt_handler();

void idt_init();

void idt_clock_try();

void idt_add_handler(uint8_t interrupt_num, uint32_t callback);

void idt_add_not_present(uint8_t interrupt_num, uint32_t callback);

void idt_default_handler();

void idt_test_handler();

#endif