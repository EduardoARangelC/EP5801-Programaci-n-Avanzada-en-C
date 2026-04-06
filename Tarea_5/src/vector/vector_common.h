#ifndef VECTOR_COMMON_H
#define VECTOR_COMMON_H

#include <stddef.h>

/* Enumeration for vector type */
typedef enum E_VECTOR_TYPE{
    custom = 0x00,
    u8 = 0x01,
    u16 = 0x02,
    u32 = 0x04,
    u64 = 0x08,
    f32 = 0x14,
    f64 = 0x18
}e_vector_type;

/* Definition of base vector structure */
typedef struct S_VECTOR{
    size_t item_size;
    size_t item_count;
    size_t item_used;
    e_vector_type type;

    void* memory;
}s_vector;

#endif