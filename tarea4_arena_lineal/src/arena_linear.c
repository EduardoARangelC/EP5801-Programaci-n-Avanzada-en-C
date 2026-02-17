#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arena_linear.h"

/* Functions definitions */
s_arena_linear* arena_linear_create(size_t item_size){

    /* Allocate memory for arena*/
    s_arena_linear* arena_ptr = malloc(sizeof(s_arena_linear) + item_size);

    /* Check memory allocation was valid */
    if(arena_ptr == NULL){
        exit(-1);
    }

    /* Populate structure for arena */
    arena_ptr->max_size = item_size;
    arena_ptr->offset = 0x00;
    arena_ptr->memory =  memset((void *)((uint8_t *)(arena_ptr) + sizeof(s_arena_linear)), 0x00, item_size);

    /* Return arena*/
    return arena_ptr;
}

void* arena_linear_allocate(s_arena_linear* arena, size_t data_size, void* data){
    
    /* Check arena exists */
    if(arena == NULL){
        return NULL;
    }

    /* Check data size is less than remaining arena size */
    size_t available_memory = arena->max_size - arena->offset;

    if(data_size > available_memory){
        return NULL;
    }

    /* Copy items to memory and get offset */
    void* data_ptr = memcpy((void *)(arena->memory + arena->offset), data, data_size);

    /* add offset to values */
    arena->offset += data_size;

    return data_ptr;
}

void arena_linear_free(s_arena_linear* arena){

    /* Check valid arena */
    if(arena == NULL){
        return;
    }

    free(arena);
}

/* Testing area */
//int main(){
//    s_arena_linear* arena_ptr = arena_linear_create(10);
//    
//    uint8_t x = 0xff;
//    int y = 99;
//    float z = 50.5;
//
//    void* uint8_t_ptr = arena_linear_allocate(arena_ptr, sizeof(uint8_t),(void*) &x);
//    void* int_ptr = arena_linear_allocate(arena_ptr, sizeof(int),(void*) &y);
//    void* float_ptr = arena_linear_allocate(arena_ptr, sizeof(float),(void*) &z);
//
//    printf("%u\n",*((uint8_t *) uint8_t_ptr));
//    printf("%i\n",*((int *) int_ptr));
//    printf("%f\n",*((float *) float_ptr));
//
//    arena_linear_free(arena_ptr);
//}