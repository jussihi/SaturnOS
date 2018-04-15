#ifndef _SATURNOS_INT_X86_HH
#define _SATURNOS_INT_X86_HH

#include "../../stdint.h"
#include "idt.h"

typedef struct 
{
  uint32_t cr2;
  uint32_t gs;
  uint32_t fs;
  uint32_t ds;
  uint32_t es;
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;
  uint32_t int_no;
  uint32_t err_code;
  uint32_t eip;
  uint32_t cs;
  uint32_t eflags;
  uint32_t esp; /* If (cs & 0x3) != 0 */
  uint32_t ss;  /* If (cs & 0x3) != 0 */
} __attribute__((__packed__)) interrupt_context;

void interrupt_relay(interrupt_context* ctx);

#endif