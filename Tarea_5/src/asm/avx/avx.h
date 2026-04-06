#ifndef AVX_H
#define AVX_H

#include <stdint.h>

extern int avx_uint8_t(uint8_t vector_1[32], uint8_t vector_2[32], uint8_t vector_result[32]);
extern int avx_uint16_t(uint16_t vector_1[16], uint16_t vector_2[16], uint16_t vector_result[16]);
extern int avx_uint32_t(uint32_t vector_1[8], uint32_t vector_2[8], uint32_t vector_result[8]);
extern int avx_uint64_t(uint64_t vector_1[4], uint64_t vector_2[4], uint64_t vector_result[4]);

extern int avx_float32_t(float vector_1[8], float vector_2[8], float vector_result[8]);

#endif