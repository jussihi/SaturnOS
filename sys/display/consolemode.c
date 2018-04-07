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
  return char | (0x0F) << 8;
}

SaturnDISPLAY consolemode_init()
{
  display.width  = CONSOLE_WIDTH;
  display.height = CONSOLE_HEIGHT;
  display.console.x = 0;
  display.console.y = 0;

}

// clears the screen by filling it with spaces
void consolemode_clear()
{
  uint32_t index = 0;
  for(uint16_t y = 0; y < CONSOLE_HEIGHT; y++)
  {
    for(uint16_t x = 0; x < CONSOLE_WIDTH; x++)
    {
      index = y * 2 * CONSOLE_WIDTH + x * 2;
      *(uint16_t*)(CONSOLE_VGA_START + index) = consolemode_create_printable(' ');
    }
  }
  display.console.x = 0;
  display.console.y = 0;
}

