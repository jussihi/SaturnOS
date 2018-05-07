#ifndef _SATURNOS_IO_HH
#define _SATURNOS_IO_HH

#include "stdint.h"

uint8_t in_port_byte(uint16_t w_port);

void out_port_byte(uint16_t w_port, uint8_t w_val);

uint16_t in_port_short(uint16_t w_port);

void out_port_short(uint16_t w_port, uint16_t w_short);

uint32_t in_port_long(uint16_t w_port);

void out_port_long(uint16_t w_port, uint32_t w_long);

#endif 
