#
# SaturnOS makefile
#

AS=nasm
ASFLAGS=-f bin
CC=gcc
CFLAGS=-ffreestanding -fno-pie -c -m32 -I./include
KERNOBJ=kernel/kernel.o kernel/console.o kernel/io.o kernel/string.o

all: SaturnOS.bin 

SaturnOS.bin: bootloader/bootsector.bin kernel/kernel.bin
	cat bootloader/bootsector.bin kernel/kernel.bin > SaturnOS.bin && truncate SaturnOS.bin -s 10240

bootloader/bootsector.bin: bootloader/bootsector.asm
	$(AS) $(ASFLAGS) bootloader/bootsector.asm -o bootloader/bootsector.bin

kernel/kernel.bin: $(KERNOBJ)
	ld -o kernel/kernel.bin -Ttext 0x7e00 $(KERNOBJ) -m elf_i386 --oformat binary

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm bootloader/bootsector.bin kernel/*.o kernel/kernel.bin SaturnOS.bin