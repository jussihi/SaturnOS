#ifndef _SATURNOS_GDT_HH
#define _SATURNOS_GDT_HH

#include "../../stdint.h"

typedef struct {
  uint16_t limit_lo;
  uint16_t base_lo;
  uint8_t base_mid;
  uint8_t type;
  uint8_t flags_limit_nibbles;
  uint8_t base_hi;
} __attribute__((__packed__)) GDT_t;

extern void _reload_segments(void);

extern void _set_gdtr();

void gdt_init();

int gdt_set_descriptors();

int gdt_add_descriptor(GDT_t descriptor);

GDT_t gdt_create_descriptor(uint32_t base, uint32_t limit, uint8_t type);

#endif