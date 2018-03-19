#include "io.h"

// wow, this is almost identical to Linux 0.01 from 20 years ago!

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