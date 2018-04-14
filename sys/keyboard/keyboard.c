#include "../include/keyboard.h"
#include "../include/hal.h"
#include "../include/string.h"
#include "../include/stddef.h"
#include "../include/io.h"
#include "../include/display/display.h"


static char keyboard_raw_buf[128] = {0};
static char keyboard_ascii_buf[128] = {0};
static uint8_t curr_pos = 0;

void keyboard_init()
{
  hal_set_int(0x21, (uint32_t)&keyboard_irq);
}

void keyboard_get_buffer()
{
  keyboard_raw_buf[curr_pos] = 0;
  strcpy(keyboard_ascii_buf, keyboard_raw_buf);
  curr_pos = 0;
}

static char* _row1 = "qwertyuiop";
static char* _row2 = "asdfghjkl";
static char* _row3 = "zxcvbnm";

char* keyboard_get_ascii()
{
  keyboard_get_buffer();
  char key = 0;
  if(keyboard_ascii_buf[0] == 0)
  {
    return NULL;
  }
  for(uint8_t i = 0;; i++)
  {
    key = keyboard_ascii_buf[i];
    if(key == 0)
    {
      break;
    }
    if(key == 0x1C)
    {
      keyboard_ascii_buf[i] = '\n';
    }
    else if(key >= 0x10 && key <= 0x1C)
    {
      keyboard_ascii_buf[i] = _row1[key - 0x10];
    }
    else if(key >= 0x1E && key <= 0x26)
    {
      keyboard_ascii_buf[i] = _row2[key - 0x1E];
    }
    else if(key >= 0x2C && key <= 0x32)
    {
      keyboard_ascii_buf[i] = _row3[key - 0x2C];
    }
  }
  return keyboard_ascii_buf;
}

void keyboard_irq()
{
  kprintf("KB INTERRUPT\n");

  IRQ_START;

  if((in_port_byte(0x64) & 0x01) && curr_pos < 128);
  {
    keyboard_raw_buf[curr_pos++] = in_port_byte(0x60);

    //char a = in_port_byte(0x60);
  }

  hal_end_irq(1);

  IRQ_END;

}