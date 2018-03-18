#!/bin/bash

nasm bootsector.asm -f bin -o bootsector.bin
qemu-system-x86_64 bootsector.bin