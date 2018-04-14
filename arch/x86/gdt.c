#include "../../include/arch/x86/gdt.h"
#include "../../include/display/display.h"

// https://wiki.osdev.org/GDT_Tutorial


struct gdt_entry gdt[] = 
{
  // 0x00 null seg
  GDT_ENTRY(0, 0, 0, 0),

  // 0x08 kernel code segment
  GDT_ENTRY(0, 0xFFFFFFFF, 0x9A, GDT_FLAG_32_BIT_MODE | GDT_FLAG_4KB_BLOCKSIZE),

  // 0x10 Kernel data segment
  GDT_ENTRY(0, 0xFFFFFFFF, 0x92, GDT_FLAG_32_BIT_MODE | GDT_FLAG_4KB_BLOCKSIZE),

  // user code segment
  GDT_ENTRY(0, 0xFFFFFFFF, 0xFA, GDT_FLAG_32_BIT_MODE | GDT_FLAG_4KB_BLOCKSIZE),

  // user data segment
  GDT_ENTRY(0, 0xFFFFFFFF, 0xF2, GDT_FLAG_32_BIT_MODE | GDT_FLAG_4KB_BLOCKSIZE),

};

uint16_t gdt_size_for_asm = sizeof(gdt) - 1;