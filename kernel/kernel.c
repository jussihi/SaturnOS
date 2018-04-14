#include "../include/stdint.h"
#include "../include/stddef.h"
#include "../include/display/display.h"
#include "../include/display/consolemode.h"
#include "../include/arch/x86/gdt.h"
#include "../include/arch/x86/idt.h"
#include "../include/hal.h"
#include "../include/pic.h"
#include "../include/pit.h"
#include "../include/keyboard.h"


static SaturnDISPLAY* main_display = NULL;
static char* keyboard_buf = NULL;

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

  // __asm__ ("int $0x20"::);

  idt_init();

  hal_init();

  pic_init();

  pit_init();

  keyboard_init();

  // while(1) {}
  kprintf("a");
  kprintf("b");
  kprintf("c");
  kprintf("d");
  kprintf("e");
  kprintf("f");
  kprintf("a");

  

  kprintf("Everything init.\n");

  __asm__ ("int $0x21"::);

  // __asm__ ("int $0x20"::);

  //__asm__ ("sti"::);

  kprintf("Interrupts enabled, be careful.\n");

  

	while(1)
  {
    //keyboard_buf = keyboard_get_ascii();
    //if(keyboard_buf[0] != 0)
    //{
    //  kprintf("jippikai");
    //  kprintf("%s", keyboard_buf);
    //  keyboard_buf[0] = 0;
    //}
  }
	return;
}