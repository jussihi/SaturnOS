#include "../include/stdint.h"
#include "../include/stddef.h"
#include "../include/display/display.h"
#include "../include/display/consolemode.h"
#include "../include/arch/x86/gdt.h"
#include "../include/arch/x86/idt.h"
#include "../include/arch/x86/interrupt.h"
#include "../include/pic.h"
#include "../include/pit.h"
#include "../include/keyboard.h"


static SaturnDISPLAY* main_display = NULL;
static char* keyboard_buf = NULL;

extern struct gdt_entry gdt[];

extern IDT_t idt_table[256];

void kernel_entry()
{
	// create the display driver and set it active. Also print something through it.
	SaturnDISPLAY disp = consolemode_init();
	uint8_t disp_id = display_add(disp);
	uint8_t a = display_change(disp_id);

	main_display = display_get_current();
	main_display->puts("Hello world from protected (32bit) mode ...\n");

	kprintf("%s %d 0x%x \n", "Testing the kprintf functionality!", 100, 16);

  kprintf("GDT Location set to   0x%x !\n", gdt);

  // __asm__ ("int $0x20"::);

  idt_init();

  interrupt_init();

  pic_init();

  //pit_init();

  keyboard_init();

  kprintf("Everything init.\n");

  kprintf("IDT 0: %x%x\n", idt_table[0].offset_lo, idt_table[0].offset_hi);
  kprintf("ISR0:  %x", (uint32_t)isr0);


  // __asm__ ("int $0x0"::);

  // __asm__ ("int $0x20"::);

  __asm__ ("sti"::);

  kprintf("Interrupts enabled, be careful.\n");

	while(1)
  {
    keyboard_buf = keyboard_get_ascii();
    if(keyboard_buf[0] != 0)
    {
      kprintf("%s", keyboard_buf);
      keyboard_buf[0] = 0;
    }
  }
	return;
}