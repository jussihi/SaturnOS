#include "../include/keyboard.h"
#include "../include/string.h"
#include "../include/stddef.h"
#include "../include/io.h"
#include "../include/display/display.h"
#include "../include/arch/x86/interrupt.h"
#include "../include/mutex.h"



static char keyboard_raw_buf[128] = {0};
static char keyboard_ascii_buf[128] = {0};
static uint8_t curr_pos = 0;
static mutex kb_mutex;

void keyboard_init()
{
  kprintf("setting irq to 0x%x\n", keyboard_irq);
  set_irq(1, keyboard_irq);
  curr_pos = 0;
  //mutex_init(&kb_mutex);
}

void keyboard_get_buffer()
{
  //mutex_lock(&kb_mutex);
  keyboard_raw_buf[curr_pos] = 0;
  strcpy(keyboard_ascii_buf, keyboard_raw_buf);
  curr_pos = 0;
  //mutex_unlock(&kb_mutex);
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
  if((in_port_byte(0x64) & 0x01) && curr_pos < 128);
  {
    //mutex_lock(&kb_mutex);
    keyboard_raw_buf[curr_pos++] = in_port_byte(0x60);
    //mutex_unlock(&kb_mutex);
  }
}
