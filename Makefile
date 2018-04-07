#
# SaturnOS makefile
#

AS=nasm
ASFLAGS=-f bin
CC=gcc
CFLAGS=-ffreestanding -fno-pie -c -m32 -I./include
KERNOBJ=kernel/kernel.o kernel/io.o sys/display/display.o sys/display/consolemode.o

all: SaturnOS.bin 

SaturnOS.bin: bootloader/bootsector.bin kernel/kernel.bin
	cat bootloader/bootsector.bin kernel/kernel.bin > SaturnOS.bin && truncate SaturnOS.bin -s 10240

bootloader/bootsector.bin: bootloader/bootsector.asm
	$(AS) $(ASFLAGS) bootloader/bootsector.asm -o bootloader/bootsector.bin

kernel/kernel.bin: $(KERNOBJ)
	ld -o kernel/kernel.bin -Ttext 0x7e00 $(KERNOBJ) -m elf_i386 --oformat binary

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

sys/display/%.o: sys/display/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	find . -name *.o -exec rm -rf '{}' \;
	find . -name *.bin -exec rm -rf '{}' \;