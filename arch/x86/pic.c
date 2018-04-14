#include "../../include/pic.h"
#include "../../include/stdint.h"
#include "../../include/io.h"
#include "../../include/display/display.h"


void pic_init()
{
  // pic initialization , by https://wiki.osdev.org/PIC
  uint8_t a1 = in_port_byte(PIC1_DATA);
  uint8_t a2 = in_port_byte(PIC2_DATA);

  // start init in cascading mode
  out_port_byte(ICW1_INIT + ICW1_ICW4, PIC1);
  out_port_byte(ICW1_INIT + ICW1_ICW4, PIC2);

  // set the master PIC's offset to 0x20 and the slave's to 0x28
  // this is from the wiki as well
  out_port_byte(0x20, PIC1_DATA);
  out_port_byte(0x28, PIC2_DATA);

  // inform the master about the slave they have now
  out_port_byte(4, PIC1_DATA);
  out_port_byte(2, PIC2_DATA);

  // set the mode 8086
  out_port_byte(0x01, PIC1_DATA);
  out_port_byte(0x01, PIC2_DATA);

  // finally, reset the masks
  out_port_byte(0, PIC1_DATA);
  out_port_byte(0, PIC2_DATA);

  kprintf("PIC initialized!\n");

  return;
}

void pic_end_int(uint8_t int_num)
{
  if(int_num > 7)
  {
    out_port_byte(PIC_END, PIC2_COMMAND);
  }
  out_port_byte(PIC_END, PIC1_COMMAND);
}