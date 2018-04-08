#include "../../include/display/display.h"
#include "../../include/display/consolemode.h"
#include "../../include/string.h"
#include "../../include/stdint.h"

// later on we will get this memory from the memory manager,
// no heap yet
static SaturnDISPLAY display = { 0 };

// this is the function our display calls
// after it is registered ..
// because we are using textmode, there's 
// no setup needed to be done here
void consolemode_after_register()
{
  return;
}

void consolemode_after_set(uint8_t _id)
{
  // call the clear function (consolemode_clear for now)
  display.clear();
  // print a nice little text on the screen :)
  display.puts("Console mode init!\n");
  return;
}

uint16_t consolemode_create_printable(char _c)
{
  uint16_t c = (uint16_t)_c;
  return c | (0x0F) << 8;
}

// initial initialization of a console
SaturnDISPLAY consolemode_init()
{
  display.width  = CONSOLE_WIDTH;
  display.height = CONSOLE_HEIGHT;
  display.console.x = 0;
  display.console.y = 0;
  display.puts = consolemode_puts;
  display.putc = consolemode_putc;
  display.clear = consolemode_clear;
  display.after_register = consolemode_after_register;
  display.after_set = consolemode_after_set;
  return display;
}

// clears the screen by filling it with spaces
void consolemode_clear()
{
  for(uint16_t y = 0; y < CONSOLE_HEIGHT; y++)
  {
    for(uint16_t x = 0; x < CONSOLE_WIDTH; x++)
    {
      *(uint16_t*)(CONSOLE_VGA_START + (y * 2 * CONSOLE_WIDTH + x * 2)) = consolemode_create_printable(' ');
    }
  }
  display.console.x = 0;
  display.console.y = 0;
}


// copy row by row, insert last row full of spaces
void consolemode_scroll_up()
{
  for(uint32_t y = 0; y < CONSOLE_HEIGHT; y++)
  {
    memcpy((int8_t*)(CONSOLE_VGA_START + (y * 2 * CONSOLE_WIDTH)), (int8_t*)(CONSOLE_VGA_START + ((y+1) * 2 * CONSOLE_WIDTH)), CONSOLE_WIDTH*2);
  }
  memset(((char*)(CONSOLE_VGA_START + (CONSOLE_HEIGHT * 2 * CONSOLE_WIDTH))), consolemode_create_printable(' '), CONSOLE_WIDTH * 2);
}

void consolemode_putc(const char _c)
{
  // newline check, much better than in the old version!
  if(_c == '\n' || display.console.x >= CONSOLE_WIDTH)
  {
    display.console.x = 0;
    display.console.y++;
  }

  // do we need to scroll the console?
  if(display.console.y >= CONSOLE_HEIGHT - 1)
  {
    consolemode_scroll_up();
    display.console.y --;
  }

  // is the string terminated?
  if(_c == 0 || _c == '\n')
  {
    return;
  }
  // print the next char to the screen
  *(uint16_t*)(CONSOLE_VGA_START + (display.console.y * 2 * CONSOLE_WIDTH + display.console.x * 2)) = consolemode_create_printable(_c);
  display.console.x++;
}

void consolemode_puts(const char* _s)
{
  while(*_s != 0)
  {
    consolemode_putc(*_s++);
  }
}