#ifndef _SATURNOS_CONSOLEMODE_HH
#define _SATURNOS_CONSOLEMODE_HH

#include "display.h"

#define CONSOLE_VGA_START 0xb8000
#define CONSOLE_VGA_END   0xc0000

#define CONSOLE_WIDTH  80
#define CONSOLE_HEIGHT 25

void consolemode_after_register();

void consolemode_after_set(uint8_t _id);

uint16_t consolemode_create_printable(char _c);

SaturnDISPLAY consolemode_init();

void consolemode_clear();

void consolemode_putc(const char _c);

void consolemode_puts(const char* _s);



#endif