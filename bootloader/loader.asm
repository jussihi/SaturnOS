ALIGNFG equ 1<<0
MEMINFOFG equ 1<<1
FLAGSFG equ ALIGNFG|MEMINFOFG
MAGICFG equ 0x1BADB002
CHECKSUMFG equ -(MAGICFG+FLAGSFG)

; multiboot header
SECTION .multiboot
ALIGN 4
	dd MAGICFG
	dd FLAGSFG
	dd CHECKSUMFG


SECTION .text
GLOBAL _start
; These externs come from the C code.
extern kernel_entry
extern gdt_size_for_asm
extern gdt
_start:
	cli ; disable interrupts
	mov esp, kern_stack ; move stack pointer to somewhere hopefully safe

	; load GDT (Global Descriptor Table) super early!
	sub esp, 6
	mov cx, [gdt_size_for_asm] ; fetch this from gdt.c
	mov [esp+0], cx
	mov ecx, gdt ; fetch this also from gdt.c
	mov [esp+2], ecx
	lgdt [esp]
	add esp, 6
	jmp 0x08:l1

l1:
	mov cx, 0x10
	mov ds, cx
	mov es, cx
	mov fs, cx
	mov gs, cx
	mov ss, cx
	; GDT loading done
	
	; Call HLL kernel
	call kernel_entry

_hanger:
	cli
	hlt
	jmp _hanger

SECTION .bss
	RESB 64*1024    ; 64 KB stack for kernel
kern_stack:
