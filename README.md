# SaturnOS, the very simple one

My personal project for OS development. 

## Changelog

8.4.2018 - Very buggy and badly implemented GDT, also IDT added. It is done properly, but some interrupts seems to hang the system completely (for example the clock interrupt 0x20 ...)

7.4.2018 - Finally had some time to get further with this OS dev project .. Display driver WORKS. 
Using levOS as my inspiration here. 

20.3.2018 - Add string.h - It is ISO C compicant, as far as it is implemented - 
some of the functions are still missing.

19.3.2018 - Add Makefile, add very basic console write functionality. 
Divide code into smaller modules... Inline assembly is pretty hard ...

18.3.2018 - Initial commit, simple bootloader (which took most of the 
time, and simple kernel which uses the VGA compatible text mode to 
write data to the screen.)

## Build instructions

` # ./build_and_run run `
