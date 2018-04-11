#include "../include/stdint.h"
#include "../include/stddef.h"
#include "../include/display/display.h"
#include "../include/display/consolemode.h"
#include "../include/arch/x86/gdt.h"
#include "../include/arch/x86/idt.h"
#include "../include/hal.h"
#include "../include/pic.h"


static SaturnDISPLAY* main_display = NULL;

void kernel_entry()
{
	// create the display driver and set it active. Also print something through it.
	SaturnDISPLAY disp = consolemode_init();
	uint8_t disp_id = display_add(disp);
	uint8_t a = display_change(disp_id);

	main_display = display_get_current();
	main_display->puts("Hello world from protected (32bit) mode ...\n");

	kprintf("%s %d 0x%x \n", "Testing the kprintf functionality!", 100, 16);

  gdt_init();

  idt_init();

  hal_init();

  pic_init();

  kprintf("Everything init.\n");

	while(1) {  }
	return;
}