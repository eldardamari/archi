section	.rodata
R:
	DB	"Number of calculations done:  %d", 10, 0	; Format string
section .bss

section .text
	align 16
	global main
	extern printf
	extern my_calc
main:
	call my_calc
	push eax
	push R
	call printf
	add esp,8
	mov ebx,0
	mov eax,1
	int 80h