section .data                    	; data section, read-write
        an:    DD 0              	; this is a temporary var

section .text                    	; our code is always in the .text section
       
        global do_str            	; makes the function appear in global scope
        extern printf            	; tell linker that printf is defined elsewhere 				; (not used in the program)

do_str:                          	; functions are defined as labels
        push    ebp              	; save Base Pointer (bp) original value
        mov     ebp, esp         	; use base pointer to access stack contents
        pushad                   	; push all variables onto stack
        mov ecx, dword [ebp+8]	    ; get function argument

    	mov	dword [an], 0		; initialize answer

label_here:
    
    ; **** - Check if letter is upper case - ****
    cmp byte [ecx], 65
    jge .ltIsGreater
    jl .checkNumbers

.ltIsGreater:
    cmp byte [ecx], 90
    jle .incAn
    jmp .checkLetters

.incAn:
    inc dword [an]
    add dword [ecx], 1
    jmp .checkNumbers    

.checkNumbers:
    cmp byte [ecx], 48
    jge .NumIsGrater
    jl .checkBrackets 

.NumIsGrater:
    cmp byte [ecx], 57
    jle .NumbersInc
    jmp .checkLetters 

.NumbersInc:
    add dword [ecx], 1
    jmp .continue

.checkLetters:
    cmp byte [ecx], 'a'
    jge .letterIsGrater
    jmp .checkBrackets

.letterIsGrater:
    cmp byte [ecx], 'z'
    jle .LettersInc
    jmp .checkBrackets

.LettersInc:
    add dword [ecx], 1
    jmp .continue

.checkBrackets:
    cmp byte [ecx], '('
    je .changeLeftBracket
    jne .checkRightBracket
    jmp .continue

.changeLeftBracket:
    add dword [ecx], 51
    jmp .continue

.checkRightBracket:
    cmp byte [ecx], ')'
    je .changeRightBracket
    jmp .continue

.changeRightBracket:
    add dword [ecx], 52
    jmp .continue

.continue:
    inc	ecx              		; increment pointer
	cmp	byte [ecx], 0    		; check if byte pointed to is zero
	jnz	label_here       		; keep looping until it is null terminated

; Destroying Stack

         popad                    ; restore all previously used registers
         mov     eax,[an]         ; return an (returned values are in eax)
         mov     esp, ebp
         pop     dword ebp
         ret
