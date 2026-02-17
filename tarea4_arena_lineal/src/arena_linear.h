#ifndef ARENA_LINEAR_H
#define ARENA_LINEAR_H

#include <stdint.h>
#include <stddef.h>

/* Base structure definition*/
typedef struct S_ARENA_LINEAR {
    size_t max_size;
    size_t offset;
    void* memory;
} s_arena_linear;

/* Functions Signatures */
typedef s_arena_linear* (*f_arena_create) (size_t);
typedef void* (*f_arena_allocate) (s_arena_linear*, size_t, void*);
typedef void (*f_arena_free)(s_arena_linear*);

/* Object definition*/
typedef struct OBJ_ARENA_LINEAR {

    s_arena_linear arena;

    struct  {
        f_arena_create create;
        f_arena_allocate allocate;
        f_arena_free free;
    } functions;
} obj_arena_linear;

/* Prototypes */
s_arena_linear* arena_linear_create(size_t item_size);
void* arena_linear_allocate(s_arena_linear* arena, size_t data_size, void* data);
void arena_linear_free(s_arena_linear* arena);

#endif /* ARENA_LINEAR_H */