#include "../../include/stdint.h"
#include "../../include/arch/x86/pit.h"
#include "../../include/arch/x86/hal.h"
#include "../../include/display/display.h"

void pit_irq()
{
  asm volatile("add 0x1c, %esp");
  asm volatile("pusha");
  kprintf("PIT IRQ!\n");
  hal_end_irq(0);
  asm volatile("popa");
  asm volatile("iret");
}

static inline void __pit_send_cmd(uint8_t cmd)
{
  out_port_byte(cmd, PIT_REG_COMMAND);
}

static inline void __pit_send_data(uint16_t data, uint8_t counter)
{
  uint8_t port = (counter==PIT_OCW_COUNTER_0) ? PIT_REG_COUNTER0 :
    ((counter==PIT_OCW_COUNTER_1) ? PIT_REG_COUNTER1 : PIT_REG_COUNTER2);

  out_port_byte((uint8_t)data, port);
}

static inline uint8_t __pit_read_data(uint16_t counter)
{

  uint8_t port = (counter==PIT_OCW_COUNTER_0) ? PIT_REG_COUNTER0 :
    ((counter==PIT_OCW_COUNTER_1) ? PIT_REG_COUNTER1 : PIT_REG_COUNTER2);

  return in_port_byte(port);
}

static void pit_start_counter(uint32_t freq, uint8_t counter, uint8_t mode)
{

  if (freq==0)
    return;
  kprintf("Starting counter %d with frequency %dHz\n", counter/0x40, freq);
  uint16_t divisor = (uint16_t)( 1193181 / (uint16_t)freq);

  // send operational command words
  uint8_t ocw = 0;
  ocw = (ocw & ~PIT_OCW_MASK_MODE) | mode;
  ocw = (ocw & ~PIT_OCW_MASK_RL) | PIT_OCW_RL_DATA;
  ocw = (ocw & ~PIT_OCW_MASK_COUNTER) | counter;
  __pit_send_cmd(ocw);

  // set frequency rate
  __pit_send_data(divisor & 0xff, 0);
  __pit_send_data((divisor >> 8) & 0xff, 0);
}

void pit_init()
{
  hal_set_int(32, (uint32_t)pit_irq);
  pit_start_counter(200,PIT_OCW_COUNTER_0, PIT_OCW_MODE_SQUAREWAVEGEN);
  kprintf("PIT init done.\n");
}