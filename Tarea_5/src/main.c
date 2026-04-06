#include <stdio.h>
#include <stdint.h>
#include "vector/vector.h"
#include "particula.h"
#include "particula_mat.h"


// Función para imprimir cada coordenada de una partícula
void imprimir_particula(s_particula* p, const char* label) {
    if (p) {
        printf("%s ->  X:%6.2f  Y:%6.2f  Z:%6.2f  V:%6.2f \n", 
                label, p->x, p->y, p->z, p->v);
    }
}

int main() {
    // Inicialización de Colecciones de partículas
    s_vector* sistema_A = vector_new(sizeof(s_particula), custom, 10);
    s_vector* sistema_B = vector_new(sizeof(s_particula), custom, 10);
    s_vector* res_suma  = vector_new(sizeof(s_particula), custom, 10);
    s_vector* res_dist  = vector_new(sizeof(s_particula), custom, 10);

    // Definición de partículas de ejemplo
    s_particula p1 = {10.0f, 20.0f, 30.0f, 100.0f};
    s_particula p2 = {5.0f,  5.0f,  5.0f,  50.0f};
    s_particula p_extra = {1.0f, 1.0f, 1.0f, 10.0f};

    // Demostración de Suma Individual
    s_particula p_indiv_res;
    particula_sumar_individual(&p1, &p2, &p_indiv_res);
    printf("DEMOSTRACION: SUMA DE PARTICULAS\n");
    imprimir_particula(&p1, "P1        ");
    imprimir_particula(&p2, "P2        ");
    imprimir_particula(&p_indiv_res, "Resultado ");

    // Llenado de colecciones con N=3 para probar el caso impar
    vector_push(sistema_A, &p1);
    vector_push(sistema_A, &p2);
    vector_push(sistema_A, &p_extra);

    vector_push(sistema_B, &p2);
    vector_push(sistema_B, &p1);
    vector_push(sistema_B, &p_extra);

    // Suma de Colecciones
    printf("\nDEMOSTRACION: SUMA DE COLECCIONES DE PARTICULAS\n");
    particula_sumar_coleccion_avx(sistema_A, sistema_B, res_suma);
    for(size_t i = 0; i < res_suma->item_used; i++) {
        char buf[64];
        sprintf(buf, "Suma Index %lu", i);
        imprimir_particula(vector_at(res_suma, i), buf);
    }

    //Distancia entre ejes
    printf("\nDEMOSTRACION: DISTANCIA POR EJE ENTRE PARTICULAS\n");
    particula_distancia_ejes_avx(sistema_A, sistema_B, res_dist);
    for(size_t i = 0; i < res_dist->item_used; i++) {
        s_particula* d = (s_particula*)vector_at(res_dist, i);
        printf("Ejes P%lu -> X:%6.2f  Y:%6.2f  Z:%6.2f\n", 
                i, d->x, d->y, d->z);
    }

    // Sacamos una Partícula
    s_particula p_sacada;
    vector_pop(sistema_A, &p_sacada);
    printf("\nDEMOSTRACION: SACAR PARTICULA \n");
    imprimir_particula(&p_sacada, "Extraida de A");
    printf("Items restantes en sistema_A: %lu\n", sistema_A->item_used);

    // Limpieza de memoria
    vector_delete(sistema_A);
    vector_delete(sistema_B);
    vector_delete(res_suma);
    vector_delete(res_dist);

    return 0;
}