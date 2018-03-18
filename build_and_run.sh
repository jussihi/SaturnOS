#!/bin/bash

#
# Clean up
#
if [ -f saturnOS.bin ]; then
	rm saturnOS.bin
fi

if [ -f bootloader/bootsector.bin ]; then
	rm bootloader/bootsector.bin
fi

if [ -f kernel/kernel.bin ]; then
	rm kernel/kernel.bin
fi

if [ -f kernel/kernel.o ]; then
	rm kernel/kernel.o
fi

if [ $1 == "clean" ]; then
	exit 0
fi

#
# Create bootloader
#
nasm bootloader/bootsector.asm -f bin -o bootloader/bootsector.bin

#
# Compile kernel
#
gcc -ffreestanding -fno-pie -c kernel/kernel.c -o kernel/kernel.o -m32
ld -o kernel/kernel.bin -Ttext 0x7e00 kernel/kernel.o -m elf_i386 --oformat binary

#
# Combine bootloader and kernel
#
cat bootloader/bootsector.bin kernel/kernel.bin > saturnOS.bin
truncate saturnOS.bin -s 10240

if [ $1 == "run" ]; then
	qemu-system-x86_64 saturnOS.bin
fi