#
# SaturnOS makefile
#

AS=nasm
ASFLAGS=-f elf32
CC=gcc
CFLAGS=-ffreestanding -fno-stack-protector -fno-pie -m32 -c -I./include
LDFLAGS=-melf_i386
KERNOBJ=bootloader/loader.o kernel/kernel.o sys/io.o sys/display/display.o sys/display/consolemode.o arch/x86/gdt.o arch/x86/idt-asm.o arch/x86/idt.o arch/x86/pic.o arch/x86/hal.o arch/x86/pit.o sys/keyboard/keyboard.o

all: SaturnOS.iso

run: SaturnOS.iso
	virtualbox --startvm "SaturnOS"

SaturnOS.iso: SaturnOS.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "Saturn" {' >> iso/boot/grub/grub.cfg
	echo 'multiboot /boot/SaturnOS.bin' >> iso/boot/grub/grub.cfg
	echo 'boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso

SaturnOS.bin: linker.ld $(KERNOBJ)
	ld $(LDFLAGS) -T $< -o $@ $(KERNOBJ)

bootloader/bootsector.bin: bootloader/bootsector.asm
	$(AS) -f bin bootloader/bootsector.asm -o bootloader/bootsector.bin

bootloader/loader.o: bootloader/loader.asm
	$(AS) $(ASFLAGS) bootloader/loader.asm -o bootloader/loader.o

kernel/kernel.bin: $(KERNOBJ)
	ld -o kernel/kernel.bin -Ttext 0x7e00 $(KERNOBJ) -m elf_i386 --oformat binary

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

sys/keyboard/%.o: sys/keyboard/%.c
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
	rm -rf iso
	rm *.iso