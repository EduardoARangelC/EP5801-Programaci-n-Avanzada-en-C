#include "particula_mat.h"
#include "asm/avx/avx.h"
#include <stdio.h>

// Sumar partículas una a una
void particula_sumar_individual(s_particula* p1, s_particula* p2, s_particula* res) {
    if (!p1 || !p2 || !res) return;
    res->x = p1->x + p2->x;
    res->y = p1->y + p2->y;
    res->z = p1->z + p2->z;
    res->v = p1->v + p2->v;
}

// Suma N partículas
void particula_sumar_coleccion_avx(s_vector* v1, s_vector* v2, s_vector* res) {
    if (!v1 || !v2 || !res) return;
    res->item_used = v1->item_used;

    size_t n = v1->item_used;
    size_t ciclos = n / 2;

    for (size_t i = 0; i < ciclos; i++) {
        size_t idx = i * 2;
        float* ptr_a = (float*)vector_at(v1, idx);
        float* ptr_b = (float*)vector_at(v2, idx);
        float* ptr_res = (float*)vector_at(res, idx);

        if (ptr_a && ptr_b && ptr_res) {
            // Para sumar, inicializamos el destino en 0
            for(int j = 0; j < 8; j++) ptr_res[j] = 0.0f;
            avx_float32_t(ptr_a, ptr_b, ptr_res);
        }
    }

    // Por si hay residuo impar
    if (n % 2 != 0) {
        size_t last = n - 1;
        particula_sumar_individual(vector_at(v1, last), vector_at(v2, last), vector_at(res, last));
    }
}

// Calcula la distancia entre los ejes (V1 - V2) componente a componente
void particula_distancia_ejes_avx(s_vector* v1, s_vector* v2, s_vector* res) {
    if (!v1 || !v2 || !res) return;
    res->item_used = v1->item_used;

    size_t n = v1->item_used;
    size_t ciclos = n / 2;

    for (size_t i = 0; i < ciclos; i++) {
        size_t idx = i * 2;
        float* ptr_a = (float*)vector_at(v1, idx);
        float* ptr_b = (float*)vector_at(v2, idx);
        float* ptr_res = (float*)vector_at(res, idx);

        if (ptr_a && ptr_b && ptr_res) {
            // -(2*B) + A + B = A - B
            for(int j = 0; j < 8; j++) {
                ptr_res[j] = -(ptr_b[j] * 2.0f);
            }
            avx_float32_t(ptr_a, ptr_b, ptr_res);
        }
    }

    // Caso impar para la resta
    if (n % 2 != 0) {
        size_t last = n - 1;
        s_particula* pa = (s_particula*)vector_at(v1, last);
        s_particula* pb = (s_particula*)vector_at(v2, last);
        s_particula* pr = (s_particula*)vector_at(res, last);
        pr->x = pa->x - pb->x;
        pr->y = pa->y - pb->y;
        pr->z = pa->z - pb->z;
        pr->v = 0.0f; // No interesa la velocidad
    }
}