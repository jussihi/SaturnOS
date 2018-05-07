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
  out_port_byte(PIC1, ICW1_INIT + ICW1_ICW4);
  out_port_byte(PIC2, ICW1_INIT + ICW1_ICW4);

  // set the master PIC's offset to 0x20 (32) and the slave's to 0x28
  // this is from the wiki as well
  out_port_byte(PIC1_DATA, 0x20);
  out_port_byte(PIC2_DATA, 0x28);

  // inform the master about the slave they have now
  // slave pic is located at IRQ2
  out_port_byte(PIC1_DATA, 4);
  out_port_byte(PIC2_DATA, 2);

  // set the mode 8086 (0x01)
  out_port_byte(PIC1_DATA, 0x01);
  out_port_byte(PIC2_DATA, 0x01);

  // finally, reset the masks
  out_port_byte(PIC1_DATA, a1);
  out_port_byte(PIC2_DATA, a2);

  kprintf("PIC initialized!\n");

  return;
}

void pic_end_master()
{
  out_port_byte(PIC1_COMMAND, PIC_END);
}

void pic_end_slave()
{
  out_port_byte(PIC2_COMMAND, PIC_END);
}

uint16_t pic_get_irr()
{
  // 0x0A is the "read irr" command
  out_port_byte(PIC1_COMMAND, 0x0A);
  out_port_byte(PIC2_COMMAND, 0x0A);
  return in_port_byte(PIC2_COMMAND) << 8 | in_port_byte(PIC1_COMMAND);
}

uint16_t pic_get_isr()
{
  // 0x0B is the "read isr" command
  out_port_byte(PIC1_COMMAND, 0x0B);
  out_port_byte(PIC2_COMMAND, 0x0B);
  return in_port_byte(PIC2_COMMAND) << 8 | in_port_byte(PIC1_COMMAND);
}