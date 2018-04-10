#include "../../include/arch/x86/gdt.h"
#include "../../include/display/display.h"

// https://wiki.osdev.org/GDT_Tutorial

static GDT_t* gdt_pdescriptors;
static uint8_t gdt_num = 0;

static uint32_t gdt_info[2] = {0};



void gdt_init()
{
  gdt_info[0] = 0;
  gdt_num = 0;
  GDT_t temp;
  // start the gdt table from 4MiB memory
  gdt_pdescriptors = (GDT_t*)0x401000;
  kprintf("GDT was relocated to address 0x%x\n", gdt_pdescriptors);

  // create one null segment
  temp = gdt_create_descriptor(0, 0, 0);
  gdt_add_descriptor(temp);

  // create one dummy segment for possible future use
  temp = gdt_create_descriptor(0, 0, 0);
  gdt_add_descriptor(temp);

  // create code segment with code 0x9A, 64 MiB!
  temp = gdt_create_descriptor(0, 64*1024*1024, 0x9A);
  gdt_add_descriptor(temp);

  // create one data segment with code 0x92
  temp = gdt_create_descriptor(0, 64*1024*1024, 0x92);
  gdt_add_descriptor(temp);

  gdt_set_descriptors();

  kprintf("GDT initialized.\n");
}

int gdt_set_descriptors()
{
  gdt_info[0] = ((sizeof(GDT_t) * gdt_num) - 1) << 16;
  gdt_info[1] = (uint32_t)gdt_pdescriptors;

  kprintf("The GDT size in memory: %d\n", (uint16_t)*(((uint8_t*)gdt_info)+2));

  __asm__ __volatile__ ("lgdt (%0)" : : "p" (((uint8_t*)gdt_info)+2));

  _reload_segments();
  kprintf("Segments reloaded. \n");
}


int gdt_add_descriptor(GDT_t descriptor)
{
  gdt_pdescriptors[gdt_num++] = descriptor;
  return 1;
}

GDT_t gdt_create_descriptor(uint32_t base, uint32_t limit, uint8_t type)
{
  GDT_t descriptor = { 0, 0, 0, 0, 0, 0 };

  // sanity check for multiplication check
  if(limit > 65536 && (limit & 0xFFF) != 0xFFF)
  {
    // panic here !
  }

  if(limit > 65536)
  {
    limit = limit >> 12;
    descriptor.flags_limit_nibbles = 0xC0;
  }
  else
  {
    descriptor.flags_limit_nibbles = 0x40;
  }

  // put limit into right place
  descriptor.limit_lo = limit & 0xFFFF;
  descriptor.flags_limit_nibbles |= (limit >> 16) & 0xF;

  // put base to the right place

  descriptor.base_lo  = base & 0xFFFF;
  descriptor.base_mid = (base >> 16) & 0xFF;
  descriptor.base_hi  = (base >> 24) & 0xFF; 

  // type
  descriptor.type = type;

  return descriptor;
}