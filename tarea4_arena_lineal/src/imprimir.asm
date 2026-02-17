global print_arena

section .text

; Argumentos que vienen de C:
;   RDI = Puntero en la arena
;   RSI = Longitud del mensaje

print_arena:
    
    mov rdx, rsi        
    mov rsi, rdi                
    mov rax, 1
    mov rdi, 1            
    syscall             

    ret             ; retorno a C