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
extern kernel_entry
extern gdt_size_for_asm
extern gdt
extern tss
GLOBAL _start
_start:
	cli ; disable interrupts
	mov esp, kern_stack ; move stack pointer to somewhere hopefully safe

	; move TSS to its correct place in the GDT table
	mov ecx, tss
	mov [gdt+0x28+2], cx
	shr ecx, 16
	mov [gdt+0x28+4], cl
	shr ecx, 8
	mov [gdt+0x28+7], cl


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

	; load the task switch segment register
	mov cx, (0x28|0x3) ; segment number | privilege level
	ltr cx
	
	; Call HLL kernel
	call kernel_entry

_hanger:
	cli
	hlt
	jmp _hanger

SECTION .bss
	RESB 64*1024    ; 64 KB stack for kernel
kern_stack:
