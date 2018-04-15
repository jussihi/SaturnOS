#ifndef _SATURNOS_GDT_HH
#define _SATURNOS_GDT_HH

#include "../../stdint.h"

#define GDT_FLAG_64_BIT_MODE   (1 << 5)
#define GDT_FLAG_32_BIT_MODE   (1 << 6)
#define GDT_FLAG_4KB_BLOCKSIZE (1 << 7)

struct gdt_entry {
  uint16_t limit_lo;
  uint16_t base_lo;
  uint8_t base_mid;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_hi;
} __attribute__((__packed__));

struct tss_entry
{
  uint32_t prev_tss;
  uint32_t esp0;
  uint32_t ss0;
  uint32_t esp1;
  uint32_t ss1;
  uint32_t esp2;
  uint32_t ss2;
  uint32_t cr3;
  uint32_t eip;
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint32_t es;
  uint32_t cs;
  uint32_t ss;
  uint32_t ds;
  uint32_t fs;
  uint32_t gs;
  uint32_t ldt;
  uint16_t trap;
  uint16_t iomap_base;
} __attribute__((__packed__));


#define GDT_ENTRY(base, limit, access, granularity) \
  { (limit) & 0xFFFF,                                 \
    (base) >> 0 & 0xFFFF,                             \
    (base) >> 16 & 0xFF,                              \
    (access) & 0xFF,                                  \
    ((limit) >> 16 & 0x0F) | ((granularity) & 0xF0),  \
    (base) >> 24 & 0xFF,  }


#endif