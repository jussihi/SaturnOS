#include "console.h"

void kernel_entry()
{
	init_console();

	clear_screen();

	char* hellotext = "Hello from the SaturnOS!\n";

	print_to_console(hellotext);

	char* context = "Console initialized...\n";

	print_to_console(context);

	while(1) {  }
	return;
}