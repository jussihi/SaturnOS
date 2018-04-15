#include "../../include/arch/x86/idt.h"
#include "../../include/display/display.h"
#include "../../include/pic.h"

IDT_t idt_table[256];

void call_lidt(uint32_t base, uint16_t limit)
{
  __asm__ __volatile__ ("subl $6, %%esp\n\t"
                        "movw %w0, 0(%%esp)\n\t"
                        "movl %1, 2(%%esp)\n\t"
                        "lidt (%%esp)\n\t"
                        "addl $6, %%esp" : : "rN"(limit), "r"(base));
}

void idt_init()
{
  memset(idt_table, 0, sizeof(idt_table));
  idt_set_handler(&idt_table[0],  isr0,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[1],  isr1,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[2],  isr2,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[3],  isr3,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[4],  isr4,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[5],  isr5,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[6],  isr6,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[7],  isr7,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[8],  isr8,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[9],  isr9,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[10], isr10, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[11], isr11, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[12], isr12, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[13], isr13, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[14], isr14, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[15], isr15, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[16], isr16, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[17], isr17, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[18], isr18, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[19], isr19, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[20], isr20, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[21], isr21, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[22], isr22, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[23], isr23, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[24], isr24, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[25], isr25, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[26], isr26, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[27], isr27, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[28], isr28, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[29], isr29, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[30], isr30, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[31], isr31, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[32], irq0,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[33], irq1,  IDT_TYPE_INTERRUPT, 0x0);
  // IRQ 2 is the cascade of IRQ 8 to 15
  idt_set_handler(&idt_table[35], irq3,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[36], irq4,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[37], irq5,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[38], irq6,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[39], irq7,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[40], irq8,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[41], irq9,  IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[42], irq10, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[43], irq11, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[44], irq12, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[45], irq13, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[46], irq14, IDT_TYPE_INTERRUPT, 0x0);
  idt_set_handler(&idt_table[47], irq15, IDT_TYPE_INTERRUPT, 0x0);
  call_lidt((uint32_t)idt_table, sizeof(idt_table) - 1);
  return;
}

void idt_set_handler(IDT_t* entry, void(*handler)(void), uint8_t type, uint8_t access)
{
  entry->offset_lo = (uint32_t)handler & 0xFFFF;
  entry->selector = 0x8;
  entry->zero_byte = 0;
  entry->type = IDT_PRESENT | access << 5 | type;
  entry->offset_hi = (uint32_t)handler >> 16 & 0xFFFF;
  return;
}

