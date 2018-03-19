#ifndef _SATURNOS_CONSOLE_HH
#define _SATURNOS_CONSOLE_HH

#define CONSOLE_BUFFER_SIZE 1024

typedef struct {
	//bufferii jne
} console_st;

void init_console();

void update_cursor(void);

void scroll_down(void);

void scroll_clear_screen(void);

void clear_screen(void);

void print_to_console(const char* w_text);

#endif 