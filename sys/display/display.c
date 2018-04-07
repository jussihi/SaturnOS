#include <stdarg.h>
#include "../../include/stdint.h"
#include "../../include/stddef.h"
#include "../../include/string.h"
#include "../../include/stdlib.h"
#include "../../include/display/display.h"

static uint8_t _latest_added = 1;
static SaturnDISPLAY displaylist[DISPLAY_MAX_DISPLAYS];
static uint8_t current_display = 0;


// kprintf helpers !
static SaturnDISPLAY* p_display;

// add new display, return its ID
uint8_t display_add(SaturnDISPLAY _d)
{
  displaylist[_latest_added] = _d;
  // trigger the register event function
  displaylist[_latest_added].after_register();
  return _latest_added++;
}

// change the current display
uint8_t display_change(uint8_t _id)
{
  
  // sanity check, is the display the current one?
  // is there a display corresponding this ID ?
  if(_latest_added != 1 && current_display != 0)
  {
    if (current_display == _id)
    {
      return 0;
    }
  }
  
  // change the current display
  current_display = _id;
  // trigger the display set event, it handles
  // the clearing and filling
  displaylist[current_display].after_set(_id);
  // also set pointer to current display
  p_display = &displaylist[current_display];
  return 1;
}

// return the current display pointer
SaturnDISPLAY* display_get_current()
{
  return &displaylist[current_display];
}

int kprintf(const char* _s, ...)
{
  if(!_s)
  {
    return 0;
  }
  uint32_t len = strlen(_s);
  va_list ap;
  va_start(ap, _s);
  for(uint32_t i = 0; i < len; i++)
  {
    if(_s[i] == '%')
    {
      // decimal
      if(_s[i+1] == 'd')
      {
        int32_t d = va_arg(ap, int);
        char buf[16] = {0};
        itoa(d, buf, 10);
        p_display->puts(buf);
        i++;
        continue;
      }
      // hex
      if(_s[i+1] == 'x')
      {
        int32_t d = va_arg(ap, int);
        char buf[16] = {0};
        itoa(d, buf, 16);
        p_display->puts(buf);
        i++;
        continue;
      }
      // string
      if(_s[i+1] == 's')
      {
        char* s = va_arg(ap, char*);
        p_display->puts(s);
        i++;
        continue;
      }
      // character
      if(_s[i+1] == 'c')
      {
        char c = va_arg(ap, int);
        p_display->putc(c);
        i++;
        continue;
      }
      // just in case there was a wrong type input.
      // otherwise we would be stuck in an endless loop
      i++;
    }
    else
    {
      p_display->putc(_s[i]);
    }
  }
  va_end(ap);
  return 1;
}