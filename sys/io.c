#include "io.h"
#include "stdint.h"

// wow, this is almost identical to Linux 0.01 from 20 years ago!
// TODO: change these to universal uint-types !

uint8_t in_port_byte(uint16_t w_port)
{
	uint8_t ret;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "dN" (w_port));
	return ret;
}

void out_port_byte(uint16_t w_port, uint8_t w_byte)
{
	__asm__ __volatile__ ("outb %1, %0" :: "dN" (w_port), "a" (w_byte));
}

uint16_t in_port_short(uint16_t w_port)
{
  uint16_t ret;
  __asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (w_port));
  return ret;
}

void out_port_short(uint16_t w_port, uint16_t w_short)
{
  __asm__ __volatile__ ("outw %1, %0" :: "dN" (w_port), "a" (w_short));
}

uint32_t in_port_long(uint16_t w_port)
{
  uint32_t ret;
  __asm__ __volatile__ ("inl %1, %0" : "=a" (ret) : "dN" (w_port));
  return ret;
}

void out_port_long(uint16_t w_port, uint32_t w_long)
{
  __asm__ __volatile__ ("outl %1, %0" :: "dN" (w_port), "a" (w_long));
}