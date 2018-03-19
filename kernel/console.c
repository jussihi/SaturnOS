#include "console.h"
#include "system.h"
#include "io.h"

#define SCREEN_START 0xb8000
#define SCREEN_END   0xc0000
#define LINES 25
#define COLUMNS 80

static unsigned long  origin=0xb80A0;
static unsigned long  scr_end=0xb8000+25*80*2;
static unsigned long  pos;
static unsigned char* pos_ptr;
static unsigned long  currline,currcol;
static unsigned long  top=0,bottom=LINES;
static unsigned long  lines=LINES,columns=COLUMNS;


void init_console()
{
	origin = SCREEN_START;
	scr_end = SCREEN_START+LINES*COLUMNS*2;
	pos = SCREEN_START;
	pos_ptr = (unsigned char *)SCREEN_START;
	currline = 0;
	currcol = 0;
	top = 0;
	bottom = LINES;
	lines = LINES;
	columns = COLUMNS;
}

void update_cursor(void)
{
	cli();
	out_port_byte(14, 0x3d4);
	out_port_byte(0xff & ((pos - SCREEN_START) >> 9), 0x3d5);
	out_port_byte(15, 0x3d4);
	out_port_byte(0xff & ((pos - SCREEN_START) >> 1), 0x3d5);
	sti();
}

void scroll_down(void)
{
	unsigned char* screenptr = (unsigned char*)SCREEN_START;
	for(unsigned short i = 0; i < (LINES*COLUMNS*2 - COLUMNS); i++)
	{
		screenptr[i] = screenptr[i + COLUMNS*2];
	}
}

void scroll_clear_screen(void)
{
	for(unsigned short i = 0; i < lines; i++)
	{
		scroll_down();
	}
}

void clear_screen(void)
{
	unsigned char* screenptr = (unsigned char*)SCREEN_START;
	for(unsigned int i; i < scr_end; i++)
	{
		*(screenptr) = 0;
		screenptr += 2;
	}
}

// no scrolling implemented (yet ;p )
void print_to_console(const char* w_text)
{
	while(*w_text)
	{
		if(*w_text == '\n')
		{
			pos = origin + (currline + 1) * COLUMNS * 2;
			pos_ptr = (unsigned char*)pos;
			currline++;
			currcol = 0;
			w_text++;
		}
		else
		{
			*pos_ptr = *(w_text++);
			pos_ptr += 2;
			pos += 2;
			currcol++;
		}
	}
}
