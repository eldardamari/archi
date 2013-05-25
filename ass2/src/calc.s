%define	STACK_SIZE 6
%define NUM_REPAIR 48
%define CHAR_REPAIR 55

section	.rodata
ERROR_OVERFLOW		DB	"Error: Stack Overflow. ",10,0
ERROR_ARGUMENTS		DB	"Error: Not Enough Arguments on Stack. ",10,0
CALC 			DB	"calc:", 0	; Format string
PRINT_C 		DB	"%X",0
PRINT_O 		DB	"%o",0
NEWLINE 		DB	"",10,0

section .data
	an:   DD 0	; counts the total number of calculations used

section .bss
INPUT		RESB 	80	;input from user
STACK		RESB 	24	;the stack holding all elements
INDEX		RESB 	4	;num of elements
INPUTMODE	RESB 	4	;0 = hex, 1=octal
OPERAND1	RESB	80	;holding all numbers in one array
OPERAND2	RESB	80	;holding all numbers in one array
ANSWER		RESB	82	;answer after calc
OPI1		RESB	4	
OPI2		RESB	4
ANI		RESB 	4
;EXPONENT	RESB	4	;saving the number that need to be operate on
;EFLAG		RESB	4

section .text
	align 16
	global my_calc
	extern printf
	extern gets
	extern malloc
	extern free

my_calc:
	push	ebp
	mov	ebp, esp	
	pusha			
	
	mov	byte [INDEX],1
	mov	byte [INPUTMODE],0

calc:
	mov	eax,0
	mov	ebx,0

	push	CALC
	call	printf
	add	esp,4
	
	push	dword INPUT
	call	gets
	add	esp,4
	
	mov	bl,[INPUT]	;checking the first char
	inc 	dword [an]
	
	cmp 	bl,'q'		;quit
	je	quit
	
	cmp	bl,'p'		;pop and print
	je	print

	cmp	bl,'o'		;octal
	je	octal

	cmp	bl,'h'		;hexadecimal
	je	hexadecimal

	cmp	bl,'d'		;duplicate
	je	duplicate

	cmp	bl,'+'		;addition
	je	addition
	
	cmp	bl,'x'		;xor
	je	xor

	jmp	push_number	;number from user


quit:	
;	jmp	free_stack
;	
;continue:
	popa				
	mov	esp, ebp
	pop	ebp
	mov eax,[an]
	ret

error_overflow:		;message error overflow
		push	ERROR_OVERFLOW
		call	printf
		add	esp,4
		jmp	calc	

error_argu:		;message error arguments
		push	ERROR_ARGUMENTS
		call	printf
		add	esp,4
		jmp	calc	

push_number:
	dec 	dword [an]		;not yet to be counted
	cmp	byte [INDEX],STACK_SIZE ;max num of numbers should be STACK_SIZE-1
	jge	error_overflow
	mov	edi,0
	mov	esi,0
	mov	esi,[INDEX]
	imul	esi,4
	mov	edi,STACK
	add	edi,esi			;getting the index to place new number link in stack
	push	dword 0
	push	INPUT
	push	edi
	call	make_list		;make list for stack
	add	esp,12
	inc	byte [INDEX]	
	jmp	calc


addition:
	  mov	dword [OPI1],0
	  mov	dword [OPI2],0
          cmp	byte [INDEX],2
	  jle	error_argu
	  mov	esi,[INDEX]
	  dec	esi
	  mov	edi,[STACK+4*esi]	;the last argument in stack
	  mov	eax,0

op1_loop:			;gathering all numbers op operand 1 in array
	  mov   edx,0			
	  mov	dl,[edi]		;number to be calculate
	  mov	[OPERAND1+eax],dl	
	  inc	edi
	  inc	eax
	  mov	edi,[edi]
	  cmp	dl,'G'			;end of linked list - end with 'G'
	  jne	op1_loop
	  
	  dec	eax			;setting eax to size of elements ex. eax=8 -> 2 numbers  
	  mov	[OPI1],eax
	  dec	esi
	  mov	edi,[STACK+4*esi]
	  mov	eax,0
	  dec	byte [INDEX]


op2_loop:			;gathering all numbers op operand 2 in array
	  mov   edx,0
	  mov	dl,[edi]  
	  mov	[OPERAND2+eax],dl
	  inc	edi
	  inc	eax
	  mov	edi,[edi]
	  cmp	dl,'G'
	  jne	op2_loop   
	  
	  dec	eax
	  mov	[OPI2],eax
	  dec	byte [INDEX]
	  
	  mov	[ANI],eax	;setting the answer size by the bigger operands (align)
	  cmp	eax,[OPI1]
	  jge	build_ans
	  mov	eax,[OPI1]
	  mov	[ANI],eax


build_ans:			;building answer
	  inc	dword [ANI]
	  mov	esi,[ANI]
	  mov	byte [ANSWER+esi],'G'
	  mov	ecx,0
	  

add_loop:			;starting adding loop
	    mov	 eax,0 
	    mov	 ebx,0 
	    dec  dword [ANI]
	    dec	 dword [OPI1]
	    dec	 dword [OPI2]
	    cmp  dword [ANI],0
	    jl	 add_out
	    
	    mov	 esi,[OPI1]
	    cmp	 esi,0
	    jl	 opi1_empty

	    mov  al,[OPERAND1+esi]


opi1_empty:
	    mov	 esi,[OPI2]
	    cmp	 esi,0
	    jl	 opi2_empty

	    mov  bl,[OPERAND2+esi]

opi2_empty:			
	    add  al,bl
	    add  al,cl			;cl represents the carry from the previous iteration
	    
	    cmp	 byte [INPUTMODE],1
	    je	 check_octal_carry
	    
	    cmp	 al,16     
	    jl	 nocarry
	    
	    mov	 cl,1
	    sub	 al,16     
	    jmp	 after_carry

check_octal_carry:			;setting carry for octal
	    cmp	 al,8     
	    jl	 nocarry
	    mov	 cl,1
	    sub	 al,8     
	    jmp	 after_carry

nocarry:    
	    mov	 cl,0

after_carry:
	    mov	esi,[ANI]
	    mov	[ANSWER+esi],al
	    jmp add_loop
    
add_out:			;taking answer and adding to stack
	mov	edi,0
	mov	esi,0
	mov	esi,[INDEX]
	imul	esi,4
        mov	edi,STACK
        add	edi,esi
	push	dword 1    
	push	ANSWER
	push	edi
	call	make_list
	add 	esp,12
	inc	byte [INDEX]
;	cmp	EFLAG,1
;	je	exponent_loop		;keep looping to exponent
	
	jmp	calc

duplicate:			;duplicating last element
	  mov	esi,0
	  mov	esi,[INDEX]

	  cmp	esi,STACK_SIZE
	  jge	error_overflow

	  cmp	esi,1
	  jle	error_argu

	  dec	esi
	  mov	edi,[STACK+4*esi]

	  inc	esi
	  mov	[STACK+4*esi],edi
	  inc	byte [INDEX]

	  jmp	calc


print:				;printing function, by octal/hex and removing leading zeros
	cmp	byte [INDEX],1
	jle	error_argu
	mov	eax, 0
	
	mov	esi,0
	mov	edi,0
	
	mov	esi,[INDEX]
	dec	esi
	mov	edi,[STACK+4*esi]

print_loop:
	mov	edx,0
	mov	dl,[edi]
	
	cmp	byte dl,'G'
	je	print_out

	cmp 	eax, 0
	jne 	non_zero_print
 
	add     eax, 1
	cmp	edx, 0		;first node is 0(zero) so don't need to print
	je	next_print

non_zero_print:
	cmp	byte [INPUTMODE],0
	je	hex

	push	edx
	push	PRINT_O
	jmp	Apush

hex:
	push	edx
	push	PRINT_C
  

Apush:
	call	printf
	add 	esp,8

  
next_print:
	inc	edi
	mov	edi,[edi]
	jmp	print_loop
  

print_out:			;printing newline
	dec	byte [INDEX]
	push	NEWLINE
	call	printf
	add	esp,4
	jmp 	calc	

make_list:			;making list - for storing all digits/letters in operands. ending list node in 'G'
	  push	ebp
	  mov	ebp, esp	
	  pusha

	  mov	edi,0
	  mov	eax,0
	  mov	ebx,0
	  mov	edx,0
	  
	  mov	edi,[ebp+8]
	  mov	ebx,[ebp+12]
	  mov	esi,[ebp+16]
	  
	  cmp	esi, 1
	  je	loop1

	  cmp	byte [INPUTMODE],1
	  je	loop_octal


loop1:				;hex loop
	  push 	ebx
	  push 	dword 5
	  call  malloc
	  add	esp,4
	  pop 	ebx

	  mov	edx,0
	  mov	dl,[ebx]

	  cmp	byte dl,'G'	
	  je	out
	  
	  cmp	esi,1
	  je	after_repair

	  cmp	byte dl,0	
	  je	out

	  cmp	dl,'9'
	  jle	num_repair
	  sub	dl,CHAR_REPAIR

after_repair:
	  mov	[eax],dl	;assigning data to heap
	  mov	[edi],eax	;set pointer of node in stack

	  inc	eax
	  inc	ebx
	  mov	edi,eax

	  cmp	byte [INPUTMODE],1
	  je	loop_octal
	  
	  jmp	loop1

out:    
	  mov	dl,'G'
	  mov	[eax],dl
	  mov	[edi],eax
	  
	  inc	eax
	  inc	ebx
	  mov	edi,eax

	  popa
	  mov	esp, ebp	
	  pop	ebp
	  ret

loop_octal:  		;loop for octal
	  push 	ebx              
	  push 	dword 5
	  call  malloc
	  add	esp,4
	  pop 	ebx

	  mov	edx,0
	  mov 	dl,  [ebx]
	  
	  cmp	byte dl,'G'	
	  je	out
	  
	  cmp	esi,1
	  je	after_repair

	  cmp	byte dl,0	
	  je	out

	  cmp	dl,'7'
	  jle	num_repair
	  
	  
octal:
	  mov	byte [INPUTMODE],1
	  jmp	calc


hexadecimal:
	  mov	byte [INPUTMODE],0
	  jmp	calc
	  

num_repair:			;reparing number from assci to decimal
	  cmp	dl,'0'
	  jge	legal_num
	  jmp	after_repair


legal_num:	  
	  sub	dl,NUM_REPAIR
	  jmp	after_repair

	  
xor:				;xor between to operands
	  mov	dword [OPI1],0
	  mov	dword [OPI2],0
          cmp	byte [INDEX],2
	  jle	error_argu
	  mov	esi,[INDEX]
	  dec	esi
	  mov	edi,[STACK+4*esi]
	  mov	eax,0

op1_loop_xor:			;going through the first list and add the numbers to one array OPERAND1
	  mov   edx,0			
	  mov	dl,[edi]		
	  mov	[OPERAND1+eax],dl	
	  inc	edi
	  inc	eax
	  mov	edi,[edi]
	  cmp	dl,'G'
	  jne	op1_loop_xor
	  
	  dec	eax
	  mov	[OPI1],eax	;displacement of operand1 to 'G'
	  dec	esi
	  mov	edi,[STACK+4*esi]
	  mov	eax,0
	  dec	byte [INDEX]	;"remove" old number from stack

op2_loop_xor:			;going through the second list and add the numbers to one array OPERAND2
	  mov   edx,0
	  mov	dl,[edi]  
	  mov	[OPERAND2+eax],dl
	  inc	edi
	  inc	eax
	  mov	edi,[edi]
	  cmp	dl,'G'
	  jne	op2_loop_xor   
	  
	  dec	eax
	  mov	[OPI2],eax	;displacement of operand2 to 'G'
	  dec	byte [INDEX]	;"remove" old number from stack
	  
	  mov	[ANI],eax	; comparing the two sizes of OPI1 vs OPI2, and let the bigger be the size of answer
	  cmp	eax,[OPI1]
	  jge	build_ans_xor
	  mov	eax,[OPI1]
	  mov	[ANI],eax

build_ans_xor:
	  mov	esi,[ANI]
	  mov	byte [ANSWER+esi],'G'
	  mov	ecx,0
	  
xor_loop:
	    mov	 eax,0 
	    mov	 ebx,0 
	    dec  dword [ANI]
	    dec	 dword [OPI1]
	    dec	 dword [OPI2]
	    cmp  dword [ANI],0
	    jl	 xor_out
	    
	    mov	 esi,[OPI1]
	    cmp	 esi,0
	    jl	 xor_opi1_empty		
	    
	    mov  al,[OPERAND1+esi]	;OPPERAND1 is not empty yet

xor_opi1_empty:
	    mov	 esi,[OPI2]
	    cmp	 esi,0
	    jl	 xor_opi2_empty
	    
	    mov  bl,[OPERAND2+esi]	;OPPERAND1 is not empty yet

xor_opi2_empty:			
	    xor  eax,ebx
	    
	    mov	esi,[ANI]
	    mov	[ANSWER+esi],al
	    jmp xor_loop
	
xor_out:				;creating a new link list with answer
	mov	edi,0
	mov	esi,0
	mov	esi,[INDEX]
	imul	esi,4
        mov	edi,STACK
        add	edi,esi
	push	dword 1    
	push	ANSWER
	push	edi
	call	make_list
	add 	esp,12
	inc	byte [INDEX]
	jmp	calc
	
;duplicate_exponent:
;	  mov	esi,0
;	  mov	esi,[INDEX]
;	  
;	  cmp	esi,1		;checking that there's at least one number in stack
;	  jle	error_argu
;
;	  dec	esi
;	  mov	edi,[STACK+4*esi]
;	  
;	  inc	esi
;	  mov	[STACK+4*esi],edi
;	  inc	byte [INDEX]
;	  mov 	eax,0		; counter for link value
;link_value:
;	  mov   edx,0
;	  mov	dl,[edi]  
;	  add	eax,dl
;	  inc	edi
;	  mov	edi,[edi]
;	  cmp	dl,'G'
;	  jne	link_value
;	  mov	EFLAG,1	  
;exponent_loop:

;free_stack:			;going through all elements in stack and deallocating all memory
;	  mov	esi,0
;	  mov	esi,[INDEX]

;	  cmp	esi,1		;checking that there's at least one number in stack
;	  jle	continue
;
;	  dec	esi
;	  mov	edi,[STACK+4*esi]
	  
;free_single_list:
;	  mov   ebx,0
;	  mov	ebx,edi		
;	  inc   ebx		; getting the next node address 

;	  push	ebx
	  
;	  push	edi		; free memory of node
;	  call	free
;	  add	esp,4
	  
;	  pop	ebx

	  
;	  mov 	edi,0
;	  mov	edi, [ebx]
;	  ;mov	ebx,0
 ;	  mov	dl,[edi] 
	  
;	  cmp	dl,'G'
;	  jne	free_single_list
	  
	  ;push ecx
	  
;	  push	edi		;free last node
;	  call	free
;	  add 	esp,4
;	  ;pop ecx
	  
;	  dec	byte [INDEX]
	  
;	  jmp free_stack