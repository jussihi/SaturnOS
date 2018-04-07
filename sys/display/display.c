#include "../../include/stdint.h"
#include "../../include/stddef.h"
#include "../../include/display/display.h"

static SaturnDISPLAY displaylist[DISPLAY_MAX_DISPLAYS];
static uint8_t current_display = 0;
static uint8_t latest_added = 1;

// add new display, return its ID
uint8_t display_add(SaturnDISPLAY _d)
{
  displaylist[latest_added] = _d;
  // trigger the register event function
  displaylist[latest_added].after_register();
  return latest_added++;
}

// change the current display
uint8_t display_change(uint8_t _id)
{
  // sanity check, is the display the current one?
  // is there a display corresponding this ID ?
  if (current_display == _id || latest_added < _id)
  {
    return 0;
  } 
  // change the current display
  current_display = _id;
  // trigger the display set event, it handles
  // the clearing and filling
  displaylist[current_display].after_set(_id);
  return 1;
}

// return the current display pointer
SaturnDISPLAY display_get_current()
{
  return &displaylist[current_display];
}