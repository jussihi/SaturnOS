#ifndef _SATURNOS_IO_HH
#define _SATURNOS_IO_HH

unsigned char in_port_byte(unsigned short w_port);

void out_port_byte(unsigned char w_val, unsigned short w_port);

unsigned short in_port_short(unsigned short w_port);

void out_port_short(unsigned short w_byte, unsigned short w_port);

unsigned long in_port_long(unsigned short w_port);

void out_port_long(unsigned long w_byte, unsigned short w_port);

#endif 
