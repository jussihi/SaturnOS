#include "../../include/arch/x86/interrupt.h"
#include "../../include/stdint.h"
#include "../../include/display/display.h"

void interrupt_relay(interrupt_context* ctx)
{
  if(ctx->int_no < 32)
  {
    kprintf("int\n");
  }
  else if(ctx->int_no > 31 && ctx->int_no < 48)
  {
    kprintf("irq\n");
  }
  else
  {
    // panic, can we even get here???
  }
  return;
}