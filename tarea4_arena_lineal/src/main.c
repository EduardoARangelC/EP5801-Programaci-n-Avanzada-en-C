#include <stdio.h>
#include <stdlib.h>
#include "arena_linear.h"

void print_arena(void* buffer, size_t longitud);

int main() {
    char* buffer_entrante = NULL; 
    size_t tamano_buffer = 0;    
    long caract_leidos;        

    printf("Escribe un mensaje: ");
    caract_leidos = getline(&buffer_entrante, &tamano_buffer, stdin);

    if (caract_leidos == -1) {
        printf("Error al leer la entrada\n");
        free(buffer_entrante);
        return -1;
    }

    // Creamos una arena a la medida exacta
    s_arena_linear* mi_arena = arena_linear_create((size_t)caract_leidos);
    void* arena_msg_ptr = arena_linear_allocate(mi_arena, (size_t)caract_leidos, (void*)buffer_entrante);

    if (arena_msg_ptr != NULL) {
        printf("Imprimiendo desde Assembly: \n");
        print_arena(arena_msg_ptr, (size_t)caract_leidos);
    }

    free(buffer_entrante);
    arena_linear_free(mi_arena);

    return 0;
}