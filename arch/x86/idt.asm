GLOBAL _set_idtr:function
_set_idtr:
	push ebp
    mov  ebp, esp

	lidt [0x401F00]

    mov esp, ebp
	pop ebp
    ret

; https://wiki.osdev.org/GDT_Tutorial
; 0x10 and 0x18 meaning the code and data segment descriptors (IDs)
GLOBAL _reload_segments:function
_reload_segments:
	jmp 0x10:reload_CS

reload_CS:
	mov ax, 0x18
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret


;GLOBAL _reload_segments:function
;_reload_segments:
;	push ebp
;	mov ebp, esp
;
;	push eax
;	mov ax, 0x18
;	mov ds, ax
;	mov es, ax
;	mov fs, ax
;	mov gs, ax
;	mov ss, ax
;	pop eax
;
;	jmp 0x10:me
;
;me:
;	mov esp, ebp
;	pop ebp
;	ret

GLOBAL _set_gdtr:function
_set_gdtr:
	push ebp
	mov ebp, esp

	lgdt [0x400000]
	mov esp, ebp
	pop ebp
	ret