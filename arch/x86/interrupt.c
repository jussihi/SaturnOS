#include "../../include/arch/x86/interrupt.h"
#include "../../include/stdint.h"
#include "../../include/display/display.h"
#include "../../include/arch/x86/pic.h"

static void(*irq_handler[16])();

void interrupt_init()
{
  for(uint8_t i = 0; i < 16; i++)
  {
    irq_handler[i] = NULL;
  }
  return;
}

void set_irq(uint8_t irq_num, void(*handler)())
{
  irq_handler[irq_num] = handler;
  kprintf("Interrupt handler for IRQ %d set to point to 0x%x \n", irq_num, handler);
  return;
}

void interrupt_relay(interrupt_context* ctx)
{
  if(ctx->int_no < 32)
  {
    // handle interrupts here
    // isr handler
    kprintf("int\n");
  }
  else if(ctx->int_no > 31 && ctx->int_no < 48)
  {
    // handle irqs here !
    uint8_t irqno = ctx->int_no - 32;

    // https://wiki.osdev.org/PIC#Spurious_IRQs
    if(irqno == 7 && !(pic_get_isr() & (1 << 7)))
    {
      return;
    }
    if(irqno == 15 && !(pic_get_isr() & (1 << 15)))
    {
      return;
    }

    if(irq_handler[irqno] != NULL)
    {
      irq_handler[irqno]();
    }

    // send the EOI
    if(irqno > 7)
    {
      pic_end_slave();
    }
    pic_end_master();
  }
  else
  {
    // panic, can we even get here???
  }
  return;
}