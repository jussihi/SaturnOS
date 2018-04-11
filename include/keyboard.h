#ifndef _SATURNOS_KEYBOARD_HH
#define _SATURNOS_KEYBOARD_HH

void keyboard_init();

void keyboard_get_buffer();

char* keyboard_get_ascii();

void keyboard_irq();

#endif