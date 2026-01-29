global imprimir

section .text

imprimir:
    
    push rbx            ; guarda el valor original de rbx en la pila
    mov rbx, rdi        ; rbx = copia del puntero al string
    mov r8,  rsi        ; r8 = copia del contador

.loop:
    cmp r8, 0           ; Quedan caracteres?
    je .fin             ; Si no quedan caracteres termina el ciclo

    mov rax, 1          ; quiero imprimir algo
    mov rdi, 1          ; imprimelo en pantalla
    mov rsi, rbx        ; este es el carácter a imprimir
    mov rdx, 1          ; imprime 1 byte
    syscall             ; hazlo

    inc rbx             ; avanza el puntero
    dec r8              ; reduce el contador
    jmp .loop

.fin:
    pop rbx             ; restaurar el valor original de rbx
    ret                 ; retorno a C

