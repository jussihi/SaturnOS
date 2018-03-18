#!/bin/bash

gcc -ffreestanding -fno-pie -c kernel.c -o kernel.o -m32
ld -o kernel.bin -Ttext 0x7e00 kernel.o -m elf_i386 --oformat binary