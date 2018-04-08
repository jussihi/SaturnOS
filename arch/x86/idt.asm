GLOBAL _set_idtr:function
_set_idtr:
	push ebp
    mov  ebp,esp

	lidt [0x401F00]

    mov esp,ebp
	pop ebp
    ret
