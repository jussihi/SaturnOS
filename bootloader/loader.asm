ALIGNFG equ 1<<0
MEMINFOFG equ 1<<1
FLAGSFG equ ALIGNFG|MEMINFOFG
MAGICFG equ 0x1BADB002
CHECKSUMFG equ -(MAGICFG+FLAGSFG)


SECTION .multiboot
ALIGN 4
	dd MAGICFG
	dd FLAGSFG
	dd CHECKSUMFG

SECTION .text
GLOBAL start
extern kernel_entry
_start:
	cli
	mov esp, kern_stack
	call kernel_entry

_hanger:
	cli
	hlt
	jmp _hanger

SECTION .bss
	RESB 64*1024    ; 64 KB stack for kernel
kern_stack:
