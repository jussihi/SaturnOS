; these might get lost as well once the code is cleaned up ...

GLOBAL _set_idtr:function
_set_idtr:
	push ebp
    mov  ebp, esp

	lidt [0x401F00]

    mov esp, ebp
	pop ebp
    ret


GLOBAL _default_idt_handler:function
_default_idt_handler:
	pushal
	mov al, 0x20
	mov dx, 0x20
	out dx, al
	popal
	iretl