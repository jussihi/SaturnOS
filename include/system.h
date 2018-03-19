#ifndef _SATURNOS_SYSTEM_HH
#define _SATURNOS_SYSTEM_HH

#define cli() __asm__ ("cli"::)
#define sti() __asm__ ("sti"::)

#endif 