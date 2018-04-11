#
# SaturnOS makefile
#

AS=nasm
ASFLAGS=-f elf32
CC=gcc
CFLAGS=-ffreestanding -fno-stack-protector -fno-pie -m32 -c -I./include
KERNOBJ=kernel/kernel.o sys/io.o sys/display/display.o sys/display/consolemode.o arch/x86/gdt.o arch/x86/idt-asm.o arch/x86/idt.o arch/x86/pic.o arch/x86/hal.o

all: SaturnOS.bin 

SaturnOS.bin: bootloader/bootsector.bin kernel/kernel.bin
	cat bootloader/bootsector.bin kernel/kernel.bin > SaturnOS.bin && truncate SaturnOS.bin -s 10240

bootloader/bootsector.bin: bootloader/bootsector.asm
	$(AS) -f bin bootloader/bootsector.asm -o bootloader/bootsector.bin

kernel/kernel.bin: $(KERNOBJ)
	ld -o kernel/kernel.bin -Ttext 0x7e00 $(KERNOBJ) -m elf_i386 --oformat binary

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

sys/display/%.o: sys/display/%.c
	$(CC) $(CFLAGS) $< -o $@

arch/x86/idt-asm.o: arch/x86/idt.asm
	$(AS) $(ASFLAGS) arch/x86/idt.asm -o arch/x86/idt-asm.o

arch/x86/%.o: arch/x86/%.c
	$(CC) $(CFLAGS) $< -o $@

sys/%.o: sys/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	find . -name *.o -exec rm -rf '{}' \;
	find . -name *.bin -exec rm -rf '{}' \;