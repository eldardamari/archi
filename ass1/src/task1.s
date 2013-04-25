section	.rodata
LC0:
	DB	"The result is:  %u", 10, 0	; Format string

section .bss
LC1:
	RESD	1

section .text
	align 16
	global my_func
	extern printf

my_func:
    mov eax, ecx
    mov cl, 0

loop:
    mov edx, eax
    shl edx, cl
    add cl, 4
    add ebx,[ecx]

    inc eax
    cmp byte[eax], 0
    jnz loop

    mov ebx,1
	
	push	dword[LC1]		; Call printf with 2 arguments: pointer to str
	push	LC0		; and pointer to format string.
	call	printf
	add 	esp, 8		; Clean up stack after call

	popa			; Restore registers
	mov	esp, ebp	; Function exit code
	pop	ebp
	ret

