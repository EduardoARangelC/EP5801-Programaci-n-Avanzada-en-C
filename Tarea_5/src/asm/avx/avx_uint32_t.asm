[BITS 64]

section     .text
    global avx_uint32_t
    
    avx_uint32_t:
    
        ;Copy Vectors
        vmovdqu   ymm0,   [rdi]
        vmovdqu   ymm1,   [rsi]
        vmovdqu   ymm2,   [rdx]

        ;Sum Vectors
        vpaddd      ymm2,   ymm0
        vpaddd      ymm2,   ymm1

        ;Move vectors to result output
        vmovdqu   [rdx],  ymm2

        mov rax, 1
        ret

%ifidn __OUTPUT_FORMAT__,elf64
    section .note.GNU-stack noalloc nowrite progbits
%endif
