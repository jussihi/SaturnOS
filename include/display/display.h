#ifndef _SATURNOS_DISPLAY_HH
#define _SATURNOS_DISPLAY_HH

#include "string.h"
#include "stdint.h"

#define DIPLAY_MAX_DISPLAYS 8

typedef struct {
  uint32_t x;
  uint32_t y;
} SatrunCONSOLE;

typedef struct {
  // display properties
  uint16_t width;
  uint16_t height;
  SatrunCONSOLE console;
  // print functionality
  void (*puts)(const char*);
  void (*putc)(const char);
  // events
  void (*after_register)();
  void (*after_set)(uint8_t id);
} SaturnDISPLAY;



#endif