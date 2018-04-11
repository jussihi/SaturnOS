#include "../../include/arch/x86/idt.h"
#include "../../include/display/display.h"
#include "../../include/pic.h"

static uint32_t idt_location = 0;
static uint32_t idtr_location = 0;

static uint8_t idt_test = 0;
static uint32_t test_timeout = 0x1000;


void idt_init()
{
  test_timeout = 0x1000;
  // same idtr location as set up in the assembly file!
  idt_location = 0x402000;
  idtr_location = 0x401F00;

  // PLAYGROUND
  //idt_add_handler(0x20, (uint32_t)&idt_clock_try);
  //_set_idtr();
  //__asm__ ("sti"::);
  //while(1) {}
  // END PLAYGROUND


  for(uint16_t i = 0; i <= 255; i++)
  {
    idt_add_handler(i, (uint32_t)&idt_default_handler);
  }
  idt_add_handler(0x20, (uint32_t)&idt_clock_try);
  idt_add_handler(0x2f, (uint32_t)&idt_test_handler);
  *(uint16_t*)idtr_location = 0x800 - 1;
  *(uint32_t*)(idtr_location + 2) = idt_location;
  _set_idtr();
  __asm__ ("sti"::);
  __asm__ __volatile__ ("int $0x2f");
  for(uint8_t i = 0; i < 100; i++)
  {
    // for some reason, the insides of this if is being run twice ?
    // something still messed up with the stack  ....
    if(idt_test == 1)
    {
      kprintf("IDT successfully initialized.\n");
      idt_add_handler(0x2f, (uint32_t)idt_default_handler);
      break;
    }
  }
  if(!idt_test)
  {
    kprintf("IDT doesn't work!\n");
  }
  __asm__ ("cli"::);
  return;
}

void idt_add_handler(uint8_t interrupt_num, uint32_t callback)
{
  IDT_t interrupt = {0, 0, 0, 0, 0};
  interrupt.offset_lo = (uint16_t)(callback & 0x0000FFFF);
  interrupt.selector = 0x10; // This is kind of the POINTER to the right entry from the beginning of the GDT. We use GDT code segment (3rd one)
  interrupt.zero_byte = 0;
  interrupt.type = IDT_32BIT_INTERRUPT_GATE | IDT_DPL_3 | IDT_PRESENT; // ok access rights .. 
  interrupt.offset_hi = (uint16_t)(callback >> 16);
  *(IDT_t*)(idt_location + sizeof(IDT_t) * interrupt_num) = interrupt;
  return;
}

void idt_clock_try()
{
  INT_START;
  //kprintf("kello");
  pic_end_int(0x20);
  INT_END;
  return;
}

void idt_default_handler()
{
  __asm__ __volatile__ ("pusha");
  __asm__ __volatile__ ("mov $0x20, %al");
  __asm__ __volatile__ ("mov $0x20, %dx");
  __asm__ __volatile__ ("out %al, %dx");
  __asm__ __volatile__ ("popa");
  __asm__ __volatile__ ("iret");
  return;
}


void idt_test_handler()
{
  INT_START;
  idt_test = 1;
  pic_end_int(0x2f);
  INT_END;
  kprintf("Interrupt loppui!");
  return;
}