#ifndef ARENA_STACK_H
#define ARENA_STACK_H

#include <stdint.h>
#include <stddef.h>

/* Base structure definition*/
typedef struct S_ARENA_STACK {
    size_t max_size;
    size_t offset;
    void* memory;
} s_arena_stack;

/* Item Header definition*/
typedef struct S_ITEM_STACK_HEADER {
    void* last_item;
    size_t size;
} s_item_stack_header;

/* Functions Signatures */
typedef s_arena_stack* (*f_arena_stack_create) (size_t);
typedef void* (*f_arena_stack_push) (s_arena_stack*, size_t, void*);
typedef void* (*f_arena_stack_pop) (s_arena_stack*, void*);
typedef void (*f_arena_stack_free)(s_arena_stack*);

/* Object definition*/
typedef struct OBJ_ARENA_STACK {

    s_arena_stack arena;

    struct  {
        f_arena_stack_create create;
        f_arena_stack_push push;
        f_arena_stack_pop pop;
        f_arena_stack_free free;
    } functions;
} obj_arena_stack;

/* Prototypes */
s_arena_stack* arena_stack_create(size_t item_size);
void* arena_stack_push(s_arena_stack* arena, size_t data_size, void* data);
void* arena_stack_pop(s_arena_stack* arena, void* data);
void arena_stack_free(s_arena_stack* arena);

#endif // ARENA_STACK_H