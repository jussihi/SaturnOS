#include "io.h"

// wow, this is almost identical to Linux 0.01 from 20 years ago!
// TODO: change these to universal uint-types !

unsigned char in_port_byte(unsigned short w_port)
{
	unsigned char ret;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "dN" (w_port));
	return ret;
}

void out_port_byte(unsigned char w_byte, unsigned short w_port)
{
	__asm__ __volatile__ ("outb %1, %0" :: "dN" (w_port), "a" (w_byte));
}

unsigned short in_port_short(unsigned short w_port)
{
  unsigned short ret;
  __asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (w_port));
  return ret;
}

void out_port_short(unsigned short w_byte, unsigned short w_port)
{
  __asm__ __volatile__ ("outw %1, %0" :: "dN" (w_port), "a" (w_byte));
}

unsigned long in_port_long(unsigned short w_port)
{
  unsigned long ret;
  __asm__ __volatile__ ("inl %1, %0" : "=a" (ret) : "dN" (w_port));
  return ret;
}

void out_port_long(unsigned long w_byte, unsigned short w_port)
{
  __asm__ __volatile__ ("outl %1, %0" :: "dN" (w_port), "a" (w_byte));
}