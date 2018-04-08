[org 0x7c00] ; bootsector position in memory

mov ah, 0x0e ; BIOS teletype, print to the screen

mov si, GREETER
; mov dx, 0x1234
; call print_16bit_hex

mov al, 15            ; read next 9 sectors (containing our mini kernel)
mov bx, kernel_entry ; read data to the kernel_entry
call disk_read

call switch_to_pm

[bits 32]

BEGIN_PM:
	jmp kernel_entry
	
[bits 16]

disk_read:
	pusha

	mov ah, 0x02 ; read sectors from the disk drive
	mov ch, 0x00 ; select first cylinder / track 
	mov dh, 0x00 ; use the first write head
	mov cl, 0x02 ; select sector (index starts from 1 here!)
	
	push bx
	mov bx, 0x00
	mov es, bx
	pop bx

	int 0x13 ; interrupt

	jc error ; did the interrupt return error?

	popa
	ret

error:
	mov si, ERROR
	call print_string
	ret

print_string:
	_loop:
		lodsb
		cmp al, 0
		je _end	
		int 0x10 ; interrupt
		jmp _loop
	_end:
	ret

print_16bit_hex:
	mov si, HEX_TEMPLATE

	mov bx, dx ; mov to b
	shr bx, 12 ; shift b right by 12 BITS
	add bx, 48 ; add 48 regarding ASCII table
	mov [HEX_TEMPLATE+2], bl

	mov bx, dx
	shr bx, 8
	and bx, 0x000f
	add bx, 48
	mov [HEX_TEMPLATE+3], bl

	mov bx, dx
	shr bx, 4
	and bx, 0x000f
	add bx, 48
	mov [HEX_TEMPLATE+4], bl

	mov bx, dx
	and bx, 0x000f
	add bx, 48
	mov [HEX_TEMPLATE+5], bl

	call print_string
	ret

HEX_TEMPLATE:
	db '0x???? ',0

GREETER:
	db 'Boot',0

ERROR:
	db 'error!',0

call print_16bit_hex

jmp $ ; loop forever

[bits 16]

switch_to_pm:

	cli                   ; switch off interrupts

	lgdt [gdt_descriptor] ; load the descriptor table

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:init_pm

[bits 32]

init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_PM         ; Boot the OS

[bits 16]

gdt_start:

gdt_null:
	dd 0x0
	dd 0x0

gdt_code: ; https://en.wikipedia.org/wiki/Global_Descriptor_Table
	dw 0xffff    ; limit
	dw 0x0       ; base
	db 0x0       ; base
	db 10011010b ; type flags
	db 11001111b ; limit flags
	db 0x0       ; base

gdt_data:
	dw 0xffff    ; limit
	dw 0x0       ; base
	db 0x0       ; base
	db 10010010b ; type flags
	db 11001111b ; limit flags
	db 0x0       ; base

gdt_end:

gdt_descriptor:
	dw gdt_end -gdt_start -1
	dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0 ; fill bytes until 510 bytes with 0 for magic
dw 0xaa55

kernel_entry:
	; kernel code will be loaded here