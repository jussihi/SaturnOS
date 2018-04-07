#include "../include/stdint.h"
#include "../include/stddef.h"
#include "../include/display/display.h"
#include "../include/display/consolemode.h"

static SaturnDISPLAY* main_display = NULL;

void kernel_entry()
{
	// create the display driver and set it active. Also print something through it.
	SaturnDISPLAY disp = consolemode_init();
	uint8_t disp_id = display_add(disp);
	display_change(disp_id);

	main_display = display_get_current();

	main_display->puts("Hello world!\nFrom SaturnOS...");

	while(1) {  }
	return;
}