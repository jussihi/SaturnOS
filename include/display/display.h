#ifndef _SATURNOS_DISPLAY_HH
#define _SATURNOS_DISPLAY_HH

#include "string.h"
#include "stdint.h"

#define DISPLAY_MAX_DISPLAYS 8

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
  void (*clear)();
  // events
  void (*after_register)();
  void (*after_set)(uint8_t id);
} SaturnDISPLAY;

uint8_t display_add(SaturnDISPLAY _d);

uint8_t display_change(uint8_t _id);

SaturnDISPLAY* display_get_current();

int kprintf(const char* _s, ...);


#endif