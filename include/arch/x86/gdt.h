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

#define GDT_ENTRY(base, limit, access, granularity) \
  { (limit) & 0xFFFF,                                 \
    (base) >> 0 & 0xFFFF,                             \
    (base) >> 16 & 0xFF,                              \
    (access) & 0xFF,                                  \
    ((limit) >> 16 & 0x0F) | ((granularity) & 0xF0),  \
    (base) >> 24 & 0xFF,  }


#endif